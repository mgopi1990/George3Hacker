#!/usr/bin/env python3

'''

Given an array A of positive integers,
Write a program to sort them in such a way
that the first part of the array contains odd
numbers stored in descending order, rest
portion contains even numbers sorted in 
ascending order.

Example:
Input: 0 4 5 3 7 2 1
Output: 7 5 3 1 0 2 4

'''

## Approach1:
##  Just like quick sort, 
##  move odd to one end,
##  even to another end.
##  now sort.
##  This function, we tried to sort,
##  we put the number in the correct position
##  like in insertion sort
def microsoft_sort(a):
	length = len (a)
	i = 0
	j = length -1
	while (i <= j):
		#print('HERE1', a, str(i), str(j))
		if (a[i] % 2 == 1):
			k = i - 1
			while (k >= 0):
				#print ('HERE3', a[k], '<', a[i])
				if (a[k] < a[i]):
					#print ('HERE2', k, i)
					k -= 1
					continue
				break

			if (k < 0):
				k = 0
			else:
				k += 1

			if (k != i):
				temp = a[i]
				del(a[i])
				#print ('DEL', i, temp)
				a.insert(k, temp)
				#print ('INSERT', a, k, temp)
		else:
			k = length -1
			while (k > j):
				if (a[i] > a[k]):
					break
				k -= 1
			temp = a[i]
			del(a[i])
			a.insert(k, temp)
			i -= 1
			j -= 1
		i += 1
	return (a)

## Since its told that all numbers are positive.
## Lets just multiply -1 with odd numbers.
## Naturally biggest odd number will become
## smallest negative number
def microsoft_sort2(a):
	## Oneliner :-P  But worst. Initializes two array
	return [-x if (x&0x01) else x for x in sorted([-x if (x&0x01) else x for x in a ])]

## Better version of sort2
## should use 2's complement ?? for -x ?
## just one list with few extra lines
def microsoft_sort3(a):
	i = 0
	while (i < len(a)):
		## odd number
		if (a[i] & 0x01):
			temp = -a[i]
		else:
			temp = a[i]

		## perform insertion sort
		j = 0
		while (j < i):
			if (a[j] > temp):
				del(a[i])
				a.insert(j, temp)
				break
			j += 1
		i += 1

	## now remove - for odd numbers
	j = 0
	while (j < len(a)):
		if (a[j] & 0x01 == 0):
			break;
		a[j] = -a[j]
		j += 1

	return a

if __name__ == "__main__":
	inp = input('Input: ');
	output = microsoft_sort3 ([int(x) for x in inp.split(' ')])
	print ('Output: ' + ' '.join([str(x) for x in output]))

