from transformers import BertTokenizer, BertModel
import torch
import os
import json
import numpy as np
from transformers import AutoTokenizer, BertForMaskedLM


tokenizer = AutoTokenizer.from_pretrained("google-bert/bert-large-uncased")
model = BertForMaskedLM.from_pretrained("google-bert/bert-large-uncased")

inputs = tokenizer("The capital of France is [MASK].", return_tensors="pt")

with torch.no_grad():
    logits = model(**inputs).logits

print("\n\noutput")
out = logits.argmax(axis=-1)
out_text = tokenizer.decode(out[0])
print(out) 
print(out_text)  # tensor([[1012, 1996, 3007, 1997, 2605, 2003, 3000, 1012, 1012]])


print(inputs)
# [ 101, 1996, 3007, 1997, 2605, 2003,  103, 1012,  102]
tensor = torch.tensor([ 101, 1996, 3007, 1997, 2605, 2003,  103, 1012,  102])
print(tokenizer.decode(tensor))
# [CLS] the capital of france is [MASK]. [SEP]
# 101 is [CLS], 102 is [SEP], 103 is [MASK]
print(tokenizer.mask_token_id)
# mask_token_id = 103, which labeled [MASK]


# get the index of [MASK], the BERT will predict the token for this position, and only print out this position
mask_token_index = (inputs.input_ids == tokenizer.mask_token_id)[0].nonzero(as_tuple=True)[0]
print(mask_token_index)
print(logits.shape) #torch.Size([1, 9, 30522])
print(logits[0, mask_token_index].shape)
print(logits[0, mask_token_index])
# one hot encoding, return the the position of the max value
print(logits[0, mask_token_index].argmax()) 
predicted_token_id = logits[0, mask_token_index].argmax(axis=-1)
print(predicted_token_id)

print(tokenizer.decode(predicted_token_id))

tensor = torch.tensor([3000])
print(tokenizer.decode(tensor))










