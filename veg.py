#!/usr/bin/env python3

# Riddle:
# cost of 1 valakai is Rs.1, 
# cost of 1 poosani is Rs.5, 
# 20 Kathrika costs Rs.1.
# Gotta fill 100 items in basket for Rs.100.

# Lets take it a bit logically,
# 
# cost of 1 valakai Rs.1 
# cost of 1 poosani Rs.5
# cost of 1 kathrikaa Rs.1/20
#
# Let,
#  a - no. of valakai
#  b - no. of poosani
#  c - no. of kathrikai
#
# numberwise:
#  a + b + c = 100 
# costwise:
# a*1 + b*5 + c*(1/20) = 100
#
# 3variables, but only 2 equations,
# Gotta reduce it a bit logically,
#   c can be 20,40,60,80 (cant buy half kathrika)
#   a can be 1..99
#   b is rest

for c in [20,40,60,80]:
 for a in range(1,100):
  b = 100 - c - a
  if ((a + b*5 + c/20) == 100):
  	print ('valaka:{} poosani:{} kathrika:{}'.format(a,b,c))

