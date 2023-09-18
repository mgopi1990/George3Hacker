#!/usr/bin/env python3

'''
Simple script to calculate numerology
'''

import sys

## numerology chart
alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
score = '12345835112345781234666517'
dict_numerology = dict(zip(alpha,score))


for name in sys.argv[1:]:
 score = 0
 score_list = []
 for letter in name.upper():
  score += int(dict_numerology.get(letter, '0'))
  score_list.append(dict_numerology.get(letter, ' '))
 score_text = ''.join(score_list)
 print(f'{name}\n{score_text} - {score}\n---')

