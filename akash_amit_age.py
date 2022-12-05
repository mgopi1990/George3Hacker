#!/usr/bin/env python3

'''
Scalar test:
Akash is twice as old as Aman was,when Akash was as old as Aman now. If the sum of present age of akash and aman is 112 years, find the present age of Akash and Aman.
'''

SUM_OF_AGES = 112

# rule1: this year, Akash + Aman = 112
for akash in range (0, SUM_OF_AGES):
 aman = SUM_OF_AGES - akash
 # Akash is twice as old as Aman was, when Akash was as old as Aman now,
 for a in range(0,aman):
  if (((akash-a) == 2*(aman-a)) and ((akash-a) == aman)):
   print (f' {a} ago, Akash:{akash-a}, Aman:{aman-a}')
   print (f' current age of Akash:{akash}, Aman:{aman}')

