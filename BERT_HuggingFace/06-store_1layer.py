from transformers import BertTokenizer, BertModel
import torch
import os
import json
import numpy as np
from transformers import AutoTokenizer, BertForMaskedLM

import shutil

output_dir = 'output/python_out'
if os.path.exists(output_dir):
    shutil.rmtree(output_dir)
os.makedirs(output_dir)

output_dir = 'output/encoder_layer_0'
if os.path.exists(output_dir):
    shutil.rmtree(output_dir)
os.makedirs(output_dir)

output_dir = 'output/06-python_gold'
if os.path.exists(output_dir):
    shutil.rmtree(output_dir)
os.makedirs(output_dir)

print_enable = 0
order = 0 
def print_and_save_tensor(data, name, type):
    global print_enable
    if print_enable == 0:
        return
    print(type)
    print(data.shape)
    print(data)
    np_data = data.detach().numpy()
    if (type == "weight" and data.dim() >= 2):
        np_data = np_data.T
        print("Transposed")
    global order 
    f_name = f"output/encoder_layer_0/{order}-{name}-{type}.txt"
    with open(f_name, 'w') as f:
        f.write(f"Shape: {np_data.shape}\n")
        np.savetxt(f, np_data, fmt='%s')
    f_name = f"output/06-python_gold/{order}-{name}-{type}.txt"
    np.savetxt(f_name, np_data)
    if type == "output": 
        order = order + 1


def save_hook(name):
    def hook(module, input, output):
        if (name == "attention.self.query" or name == "attention.self.key" or name == "attention.self.value"):
            print("name: ", name)
            print("module: ", module)
            print_and_save_tensor(input[0][0], name, "input")
            for param_name, param in module.named_parameters():
                print_and_save_tensor(param, name, param_name)
            print_and_save_tensor(output[0], name, "output")
        # elif (name == "attention.self.dropout" or name == "attention.output.dropout" or name == "output.dropout"): 
        #     print("name: ", name)
        #     print("module: ", module)
        #     print_and_save_tensor(input[0][0][0], name, "input")
        #     print_and_save_tensor(output[0][0], name, "output")
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

for name, submodule in model.bert.encoder.layer[1].named_modules():
    submodule.register_forward_hook(save_hook(name))

# inputs = tokenizer(longtxt, return_tensors="pt")
inputs = tokenizer(longtxt, return_tensors="pt", max_length=512, truncation=True, padding="max_length")

print_enable = 1
# outputs = model(input_ids=inputs['input_ids'], attention_mask=inputs['attention_mask'])
outputs = model(input_ids=inputs['input_ids']) # does not use attention_mask
print_enable = 0

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
np.savetxt('output/python_out/01-embedding.txt', numpy_array)


# embeddings = torch.ones(1, 512, 1024)
# model.bert.encoder.layer[0].attention.self.query.weight.data.fill_(1) # Set all query weights to 1
# # for i in range(1024):
# #     for j in range(1024):
# #             model.bert.encoder.layer[0].attention.self.query.weight.data[i][j] = i
# model.bert.encoder.layer[0].attention.self.key.weight.data.fill_(1) # Set all key weights to 1
# model.bert.encoder.layer[0].attention.self.value.weight.data.fill_(1) # Set all value weights to 1
# model.bert.encoder.layer[0].attention.output.dense.weight.data.fill_(1)
# model.bert.encoder.layer[0].attention.output.LayerNorm.weight.data.fill_(1)
# for name, param in model.bert.named_parameters():
#     if 'weight' in name:
#         param.data.fill_(1)
# for name, param in model.bert.named_parameters():
#     if 'bias' in name:
#         param.data.zero_()
# model.bert.encoder.layer[0].attention.output.LayerNorm.bias.data.fill_(1)
# model.bert.encoder.layer[0].attention.self.dropout.p = 0.0
# model.bert.encoder.layer[0].attention.output.dropout.p = 0.0
# model.bert.encoder.layer[0].output.dropout.p = 0.0


print("\nFirst Encoding Layer:")
print_enable = 1
first_encoder_out = model.bert.encoder.layer[0](embeddings)
print_enable = 0
print(first_encoder_out[0].shape)
print(first_encoder_out[0])





