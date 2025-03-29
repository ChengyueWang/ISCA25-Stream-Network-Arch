from transformers import BertTokenizer, BertModel
import torch
import os
import json
import numpy as np
from transformers import AutoTokenizer, BertForMaskedLM

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
# inputs = tokenizer(longtxt, return_tensors="pt")
inputs = tokenizer(longtxt, return_tensors="pt", max_length=512, truncation=True, padding="max_length")

# outputs = model(**inputs)
outputs = model(input_ids=inputs['input_ids']) # does not use attention_mask

logits = outputs.logits
out = logits.argmax(axis=-1)[0]
out_text = tokenizer.decode(out)

print("\n\nOUTPUT:\n")
print(out.shape)
print(out) 
print(out_text) 

hidden_states = outputs.hidden_states
for i, layer_output in enumerate(hidden_states):
    print(f"Hidden state from layer {i}: {layer_output.shape}")    
    print(layer_output)
    logits = model.cls.predictions(layer_output)
    predicted_tokens = logits.argmax(-1)[0]
    hiddenlayer_text = tokenizer.decode(predicted_tokens)
    print(predicted_tokens)
    print(hiddenlayer_text, "\n")
    






