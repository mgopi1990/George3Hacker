#!/usr/bin/env python3

'''
Scalar test:
How many ways are there to collect 8Rs when you have an infinite number of 1 and 2 Rs coins.
'''

SUM = 8

## i, j -> no of 1rs and 2rs coins respectively
sno = 0
for i in range(0, SUM+1):
 for j in range(0, SUM//2 + 1):
  sum = i + j * 2
  if (sum == SUM):
   sno += 1
   print (' {:3}: 1Rs coins:{:3}    2Rscoins:{:3}'.format(sno, i, j))
print ('Totally {} ways'.format(sno))

