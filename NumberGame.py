#!/usr/bin/env python3

## Solve, 
##     A +
##     A + 
##    BB =
## =======
##   CCC
## =======
##
## Ans,
##  A + A + (10B + B) = (100C + 10C + C)
##      2A+11B - 111C = 0

print ('ANS: (A,B,C):')
for i in range(100, 1000):
 A,B,C = i%10, (i//10)%10, (i//100)%10
 #print (A, B, C)
 ans = 2*A +11*B-111*C
 if (ans == 0):
  print ('     ({},{},{})'.format(A, B, C));

