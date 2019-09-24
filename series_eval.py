#!/usr/bin/env python3

## Calculate the sum of htat range based,
## on the given expression and output the result.
## input 24*2
## output 18 (2*2 + 3*2 + 4*2)

def python_series(inp):
	low,high,op = (int(inp[0]), int(inp[1]), inp[2:])
	series = ' + '.join([ str(i) + op for i in range (low, high+1) ])
	ans = eval(series)
	return ('{} ({})'.format(ans, series))

if __name__ == "__main__":
	inp = input("input: ")
	mystr = python_series (inp)
	print ('output: ' + mystr)
