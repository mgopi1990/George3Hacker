#!/bin/env python
"""
To check whether an account number is genuinely a 
number allocated by the bank, the Pomme Bank of 
Paris uses the following technique. All the non-zero 
digits in the number are multiplied by each other. All 
the non-zero digits of the resulting number are again 
multiplied by each other - and so on until a single 
digit is left. That is the security digit.

Write a program that will provide the security digit 
for any number with up to 20 digits.

Example 1:
Input: Number? 469795 
Output: Security digit = 8
"""

# Let us assume that python int could hold 20 digits :-P
def find_security_digit(number):
	while (number > 9):
		new_num = 1
		for digit in str(number):
			if digit != '0':
				new_num *= int(digit)
		number = new_num
	return number


# Pgm begins here
number = input (' Number? ')
print (' Security digit = ' + str(find_security_digit(int(number))))
