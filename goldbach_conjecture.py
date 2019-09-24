#!/usr/bin/env python3

'''
Goldbach's conjecture is a rule in math that states the following:
every even number greater than 2 can be expressed as the
sum of two prime numbers.

Write a program that finds every possible pair of prime numbers,
whose sum equals the given number or a set of numbers within a range

For example:
Input: 16
Output:
3 + 13
5 + 11

Input: 32
Output:
3 + 29
13 + 19

Input: 4,8
Output:
4: 2 + 2
6: 3 + 3
8: 3 + 5

'''

## Returns prime number between [2..max_num]
def prime_seive(max_num):

	## Return empty list
	if (max_num < 2):
		return []
	
	## Create an odd number list
	## why to waste space for even number
	num_list = [2] + list(range(3,max_num+1, 2))

	i = 1
	c = len (num_list)
	while (i < c):
		j = i+1
		while (j < c):
			if (num_list[j] % num_list[i] == 0):
				del(num_list[j])
				c -= 1	
			else:
				j += 1
		i += 1

	return num_list

## Expresses the number as sum of two prime numbers
def goldbach (num_range, skip_even_check=False):
	ans = {}

	prime_list = prime_seive(num_range[-1])
	for num in num_range:
		## It works for some odd numbers too
		## But only even numbers are allowed
		if (num%2 == 0 or skip_even_check):
			for prime_no in prime_list:
				other_num = num-prime_no

				if (prime_no > other_num):
					break

				if other_num in prime_list:
					ans.setdefault(num, [])
					ans[num].append((prime_no, other_num))
	return ans

## parses the input and convert it as a list of numbers
def prepare_range(inp):
	t1 = []
	for num in inp.split(','):
		try:
			t1.append(int(num))
		except e:
			return []	

	if len(t1) == 1:
		return [t1[0]]
	elif len(t1) == 2 and t1[0]<=t1[1]:
		return range(t1[0], t1[1]+1)

	return []

## prints the goldbach numbers
def print_goldbach(output):
	print ('Output:')
	for num in sorted(output.keys()):
		for (prime1, prime2) in output[num]:
			print('{}: {} + {}'.format(num, prime1, prime2))



if __name__ == "__main__":
	inp = input("input: ")
	num_range = prepare_range(inp)
	output = goldbach (num_range)
	print_goldbach(output)
