from transformers import BertTokenizer, BertModel
import torch
import os
import json
import numpy as np
from transformers import AutoTokenizer, BertForMaskedLM

longtxt = """
The capital of France is [MASK]. The capital of France is [MASK]. The capital of France is [MASK]. The capital of France is [MASK].
The capital of China is [MASK]. The capital of China is [MASK]. The capital of China is [MASK]. The capital of China is [MASK]. 
The capital of UK is [MASK]. The capital of UK is [MASK]. The capital of UK is [MASK]. The capital of UK is [MASK]. The capital of UK is [MASK].
"""

tokenizer = AutoTokenizer.from_pretrained("google-bert/bert-large-uncased")
model = BertForMaskedLM.from_pretrained("google-bert/bert-large-uncased")
inputs = tokenizer(longtxt, return_tensors="pt")
logits = model(**inputs).logits
out = logits.argmax(axis=-1)[0]
out_text = tokenizer.decode(out)

print("\n\nOUTPUT:\n")
print(out) 
print(out_text) 







