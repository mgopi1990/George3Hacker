#!/usr/bin/env python3

'''
Minimal Pairs Product Sum

Write a funtion that receives an array of 
integers and returns the minimal sum of the
array (sum of produts of each two adjacent
numbers).

For Example:
Without sorting the array [40,25,10,5,1], the
sum is:
(40*25) + (25*10) + (10*5) + (5*1) = 1305

The challenge is to find the best possible sort 
of the array elements, to have the minimal
sum result

The expected output for the array 
[40, 25, 10, 5, 1] is 225
'''

## Input: [40, 25, 10, 5, 1]
## Output: 1305
## Finds (40*25) + (25*10) + (10*5) + (5*1)
def sum_of_product_of_adjacent(num_list):
	sum_of_product = 0
	for i in range(0,len(num_list)-1):
		sum_of_product += num_list[i] * num_list[i+1]
	return sum_of_product

## We move the large numbers to the extremes
## Then we fill small numbers between the large numbers
## Input: [40, 25, 10, 5, 1]
## Output: [40, 1, 10, 5, 25]
def prepare_list(num_list):
	## sort the numbers in reverse
	num_list.sort(reverse=True)

	length = len(num_list)
	if (length >= 3):
		## Ensure max numbers get to the extremes
		## z y x ... a
		## z a x ... y
		num_list[1],num_list[-1] = num_list[-1], num_list[1]

		## we are done with 4 numbers already
		## z a x .... y
		length -= 4

		if (length > 0):
			## find how many min numbers we need between max numbers
			length /= 2
			length -= 1

			i = 3
			while (length > 0):
				## keep inserting min numbers between max numbers
				num_list.insert(i, num_list[-2])
				del num_list[-2]
				i += 2
				length -= 1

	print (str(num_list))
	return num_list

def min_sum_of_product_of_adjacent(num_list):
	return (sum_of_product_of_adjacent(prepare_list(num_list)))

if __name__ == "__main__":
	num_list = input ('Enter num (sep by <space>): ')
	num_list = [int(x) for x in num_list.split(' ')]
	print (min_sum_of_product_of_adjacent(num_list))
