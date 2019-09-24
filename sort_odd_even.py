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

def microsoft_sort(a):
	length = len (a)
	i = 0
	j = length -1
	while (i <= j):
		print('HERE1', a, str(i), str(j))
		if (a[i] % 2 == 1):
			k = i - 1
			while (k >= 0):
				print ('HERE3', a[k], '<', a[i])
				if (a[k] < a[i]):
					print ('HERE2', k, i)
					k -= 1
					continue

				temp = a[i]
				del(a[i])
				print ('DEL', i, temp)
				a.insert(k, temp)
				print ('INSERT', a, k, temp)
				break
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

if __name__ == "__main__":
	inp = input('Input: ');
	output = microsoft_sort ([int(x) for x in inp.split(' ')])
	print ('Output: ' + ' '.join([str(x) for x in output]))

