from transformers import BertTokenizer, BertModel
import torch
import os
import json
import numpy as np
from transformers import AutoTokenizer, BertForMaskedLM

order = 0 
def print_and_save_tensor(data, name, type):
    print(type)
    print(data)
    np_data = data.detach().numpy()
    global order 
    f_name = f"encoder_layer_0/{order}-{name}-{type}.txt"
    order = order + 1
    with open(f_name, 'w') as f:
        f.write(f"Shape: {np_data.shape}\n")
        np.savetxt(f, np_data, fmt='%s')

def save_hook(name):
    def hook(module, input, output):
        if (name == "attention.self.query" or name == "attention.self.key" or name == "attention.self.value"):
            print("name: ", name)
            print("module: ", module)
            print_and_save_tensor(input[0][0], name, "input")
            for param_name, param in module.named_parameters():
                print_and_save_tensor(param, name, param_name)
            print_and_save_tensor(output[0], name, "output")
        elif (name == "attention.self.dropout" or name == "attention.output.dropout" or name == "output.dropout"): 
            print("name: ", name)
            print("module: ", module)
            print_and_save_tensor(input[0][0][0], name, "input")
            print_and_save_tensor(output[0][0], name, "output")
        elif (name == "attention.output.dense" or name == "intermediate.dense" or name == "output.dense"):
            print("name: ", name)
            print("module: ", module)
            print_and_save_tensor(input[0][0], name, "input")
            for param_name, param in module.named_parameters():
                print_and_save_tensor(param, name, param_name)
            print_and_save_tensor(output[0], name, "output")

            # if (name == "attention.output.dense"):
            #     output[0] = torch.ones(512, 1024) # to test attention.output.LayerNorm

        elif (name == "attention.output.LayerNorm" or name == "output.LayerNorm"):
            print("name: ", name)
            print("module: ", module)
            print_and_save_tensor(input[0][0], name, "input")
            for param_name, param in module.named_parameters():
                print_and_save_tensor(param, name, param_name)
            print_and_save_tensor(output[0], name, "output")


        # elif (name == "intermediate.intermediate_act_fn"):
        #     print("name: ", name)
        #     print("module: ", module)
        #     print_and_save_tensor(input[0][0], name, "input")
        #     for param_name, param in module.named_parameters():
        #         print_and_save_tensor(param, name, param_name)
        #     print_and_save_tensor(output[0], name, "output")
        print("\n\n")
    return hook


longtxt = """
The capital of France is [MASK]. 
The capital of China is [MASK].
The capital of US is [MASK].
The capital of UK is [MASK].
"""

tokenizer = AutoTokenizer.from_pretrained("google-bert/bert-large-uncased")
model = BertForMaskedLM.from_pretrained("google-bert/bert-large-uncased")
model.config.output_hidden_states = True
model.max_position_embeddings = 512
model.eval() # Ensure model is in evaluation mode (disables dropout layers)

for name, submodule in model.bert.encoder.layer[0].named_modules():
    submodule.register_forward_hook(save_hook(name))

# inputs = tokenizer(longtxt, return_tensors="pt")
inputs = tokenizer(longtxt, return_tensors="pt", max_length=512, truncation=True, padding="max_length")

# outputs = model(input_ids=inputs['input_ids'], attention_mask=inputs['attention_mask'])
outputs = model(input_ids=inputs['input_ids']) # does not use attention_mask

logits = outputs.logits
out = logits.argmax(axis=-1)[0]
out_text = tokenizer.decode(out)

print("\nINPUT:")
print(inputs)

print("\nOUTPUT:")
print(out.shape)
print(out) 
print(out_text) 


print("\nEmbedding Layer:")
# size 512 * 1024
embeddings = model.bert.embeddings(inputs['input_ids']) # same as outputs.hidden_states[0]
print(embeddings)
print(outputs.hidden_states[0])
numpy_array = embeddings[0].detach().numpy()
np.savetxt('python_out/01-embedding.txt', numpy_array)


print("\nFirst Encoding Layer:")
first_encoder_out = model.bert.encoder.layer[0](embeddings)
print(first_encoder_out[0].shape)
print(first_encoder_out[0])
numpy_array = first_encoder_out[0][0].detach().numpy()
np.savetxt('python_out/02-first_encoder_out.txt', numpy_array)




