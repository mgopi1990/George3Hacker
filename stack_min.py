#!/usr/bin/env python3

## Push/Pop and returns min element with O(1)
## But what about space complexity ???

print (" Enter number to push; 'p' to pop; 'd' to display; 'q' to quit")
num_list = []
n_elements = 0
min = '-'
while (1):
	inp = input('>')
	if inp == 'p':
		## Pop scenario
		if n_elements:
			num_list.pop()
			n_elements -= 1
			if (n_elements == 0):
				min = '-'
			else:
				min = num_list[-1][1]
	elif inp == 'q':
		## Quit
		break
	elif inp == 'd':
		## Display
		temp_list = [ x for x,y in num_list ]
		print (str(temp_list))
	else:
		## Push
		try:
			num = int(inp)
		except:
			break
	
		if n_elements == 0:
			min = num
		else:
			if num < min:
				min = num	

		num_list.append((num, min))
		n_elements += 1

	print (' Min: {}'.format(min))

print ('BYE BYE')

