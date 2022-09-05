#!/usr/bin/env python3

'''
Here is a crazy little coding / problem solving challenge. Given this list of integers:-
[18, 23, 17, 30, 6, 33, 32, 24, 12, 17, 36, 19, 35, 12, 17, 14, 15, 31, 38, 26]
the task is to multiply each even integer by the number of odd integers that follow it in the list. Then add up all these products to give an overall total. Tell me the event in history that occurred in the year represented by that total (or just tell me the total!)
For example, the integer 14 has 2 odd integers after it, so that contributes 28 to the total. The integer 36 is followed by 5 odd integers, so that contributes 180 to the total.
'''

inp_list = [18, 23, 17, 30, 6, 33, 32, 24,
			12, 17, 36, 19, 35, 12, 17, 14,
			15, 31, 38, 26]

def total_sum(inp_list):
	total = 0
	n_odd = 0
	for i in range (len(inp_list)-1, -1, -1):
		if (inp_list[i] % 2):
			## odd
			n_odd += 1
		else:
			## even 
			total += n_odd * inp_list[i]
	return (total)

print (total_sum(inp_list))

