#!/usr/bin/env python3

## Just inputs a file and prints the below results,
## 1- Print all three letter words.
## 2- Print all the words that start with gn or kn.
## 3- Determine what percentage of words start with a vowel.
## 4- Print all 7-letter words that start with th and end in ly.
## 5- print the first ten words that start with q.
## 6- Find the longest word that can be made using only the letters a, b, c, d, and e.

import sys
import re

## find words with specific len
def match_len (word_list, min_len, max_len=-1):
	if (max_len == -1):
		max_len = min_len

	match_list = []
	for word in word_list:
		if len(word) >= min_len and len(word) <= max_len:
			match_list.append(word)
	return match_list

## print all the words that start with or end with
def match_start_end (word_list, start_with, end_with=[]):
	match_list = []
	for word in word_list:
		for start_word in start_with:
			if word.startswith(start_word):
				break
		else:
			if (len(start_with) != 0):
				continue

		for end_word in end_with:
			if word.endswith(end_word):
				break
		else:
			if (len(end_with) != 0):
				continue

		match_list.append(word)

	return match_list	

## % of vowels
def vowel_start_percent (word_list):
	match_list = match_start_end (word_list, ['a','e','i','o','u'])
	return ((len(match_list) * 100)/len(word_list))

## all 7-letter words that start with th and end in ly.
def match_len_start_end(word_list, start_with=[], end_with=[], min_len=1, max_len=-1):
	return (match_start_end(match_len(word_list, min_len, max_len), start_with, end_with))

## n words start with q
def match_first_n_words(word_list, n=1, start_with=[], end_with=[]):
	match_list = match_start_end(word_list, start_with, end_with)
	return match_list[:n]

## 6- Find the longest word that can be made using only the letters a, b, c, d, and e.
def word_with_only_letters(word_list, letter_list):
	match_word = ''
	match_word_len = 0
	for word in word_list:
		for letter in word:
			if letter not in letter_list:
				break
		else:
			length = len(word)
			if (length > match_word_len):
				match_word = word
				match_word_len = length

	return match_word			
		
## reads from file, and creates word_list
def parse_word_file(files):
	word_reg = re.compile (r'\w+')
	word_list = []
	for file in files:
		with open(file, 'r') as fp:
			for line in fp:
				for word in word_reg.findall(line):
					lword = word.lower()
					if lword not in word_list:
						word_list.append(lword)
	# word_list.sort()
	return (word_list)	

if __name__ == "__main__":
	if len(sys.argv) <= 1:
		print ('Usage: {} file1.txt file2.txt ... fileN.txt'.format(sys.argv[0]))
		exit(0)
	
	word_list = parse_word_file(sys.argv[1:])

	print (' 1. All 3 letter word: ' 
					+ ','.join (match_len (word_list, 3)))
	print (' 2. All word start with gn or kn: ' 
					+ ','.join(match_start_end (word_list, ['gn', 'kn'])))
	print (' 3. % of words start with a vowel: {:0.2f}%'
					.format(vowel_start_percent(word_list)))
	print (' 4. All 7-letter words start with th ad end in ly: ' 
					+ ','.join(match_start_end (word_list, ['th'], ['ly'])))
	print (' 5. First 10 words start with q: ' 
					+ ','.join(match_first_n_words(word_list, 10, ['q'])))
	print (' 6. Longest word that can be made using a, b, c, d, and e: ' 
					+ word_with_only_letters(word_list, 'abcde'))
