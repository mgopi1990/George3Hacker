#!/usr/bin/env python3

'''
Here's a fun little encryption task. Encode a string, changing alphabetic characters only. Letters will be replaced by a letter the same distance in a reversed alphabet... and in the alternate case. Some examples should help:
	'a' becomes 'Z' (the first letter in lowercase becomes the last letter in uppercase)
	'Y' becomes 'b' (the 25th uppercase character becomes the 2nd lowercase) 
	abcd would become ZYXW
	DCBA would become wxyz

Best solution:
	print ("".join([chr(187 - ord(c)) if c.isalpha() else c for c in s]))
'''

class transform:

	def __init__(self, original='', transform=''):
		self.transform_dict = {}
		## lets avoid errors as much as possible
		if len(original) <= len(transform):
			for i in range(0, len(original)):
				self.transform_dict[original[i]] = transform[i]
	
	def perform_transform(self, inp_string):
		temp_buf = []
		for i in range(0, len(inp_string)):
			temp_buf.append(self.transform_dict.get(inp_string[i], inp_string[i]))
		return ''.join(temp_buf)


t=transform('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ',
			 'ZYXWVUTSRQPONMLKJIHGFEDBCAzyxwvutsrqponmlkjihgfedcba')
print(t.perform_transform('ABcDfQ14GH'))


