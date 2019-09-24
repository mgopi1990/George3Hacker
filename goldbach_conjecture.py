#!/usr/bin/env python3

'''
Goldbach's conjecture is a rule in math that states the following:
every even number greater than 2 can be expressed as the
sum of two prime numbers.

Write a program that finds every possible pair of prime numbers,
whose sum equals the given number or a set of numbers within a range
'''
def goldbach (series):

if __name__ == "__main__":
	series = input("input: ")
	mystr = goldbach (series)
	print ('output: ' + mystr)
