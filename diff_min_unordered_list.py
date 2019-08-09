#!/usr/bin/env python3

## Finds difference between min element in the list
def diff_min_list(num_list):
	if len(num_list) < 2:
		return 0

	if (num_list[0] < num_list[1]):
		min1,min2 = num_list[0], num_list[1]
	else:
		min1,min2 = num_list[1], num_list[0]

	for num in num_list[2:]:
		if (num < min1):
			min2,min1 = min1,num
		elif (num < min2):
			min2 = num

	#print ("{} {}".format(min1, min2))
	return (min2-min1)

## Main program begins here
if __name__ == "__main__":
	string = input('Enter numbers (sep by ,): ')
	num_list = [int(x) for x in string.split(',')]
	print ('Difference is : ' + str(diff_min_list(num_list)))
