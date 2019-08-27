#!/usr/bin/env python3

## Read a number and then print the series,
## 1+2+3+...+n = 
## and then print the answer

num = int (input("Please enter your number:"))
mystr = '+'.join([str(x) for x in range(1,num+1)])
tot = eval(mystr)
print ('{} = {}'.format(mystr, tot))

