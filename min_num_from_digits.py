#!/usr/bin/env python3

## find the min number from the given digits
## eg. Input: 83230001
##    Output: 10002338
def min_number(digits):
	digits_count = {
		'0':0, '1':0, '2':0, '3':0, '4':0, 
		'5':0, '6':0, '7':0, '8':0, '9':0
	}

	for i in digits:
		#digits_count.setdefault(i, 0)
		digits_count[i] += 1
	
	# we dont want 0 at MSB
	for i in "123456789":
		if digits_count[i]:
			result = i
			digits_count[i] -= 1
			break
	
	for i in "0123456789":
		result += i * digits_count[i]

	return result

if __name__ == "__main__":
	digits = input('Enter digits: ')
	print (min_number(digits))


