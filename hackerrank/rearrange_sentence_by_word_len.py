#!/usr/bin/env python3

## input: Cats and hats.
## output: And cats hats.

'''
Converts input sentence by sorting them in ascending order by word length.
Then capitalize the start of the sentence and end the sentence with .
'''
def arrange(sentence):
    temp_string = sentence[0].lower() + sentence[1:-1]
    
    temp_dict = {}
    for word in temp_string.split(' '):
        temp_dict.setdefault(len(word), [])
        temp_dict[len(word)].append(word)

    output_str = ''
    keys= sorted(temp_dict.keys())
    for k in keys:
        output_str += ' '.join(temp_dict[k]) + ' '
    output_str = output_str[:-1] + '.'

    return output_str.capitalize()



print(arrange('Cats and hats.'))

