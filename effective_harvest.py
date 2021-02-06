#!/usr/bin/env python3

"""
Effective Harvest.

A farmer uses pivot irrigation to water a circular field of crops.
Due to varying conditions, the field does not produce consistently.
The farmer wants to achieve maximum profit using limited resources for harvest.
The field is sgemented into a number of equal segments,
and profit is calculated for each segments. 

This profit is the cost to harvest versus the slae price of the produce.
The farmer will harvest a number of contiguous segements along with those opposite.
Determine the maximum profit the farmer can achieve.

For example, the field is divided into n=6 sections and will select k=2 contiguous
sections and those opposite for harvest. The profit estimates are profit =
[1, 5, 1, 3, 7, -3] respectively. The diagrams below show the possible choices
with profits[0] at the 9 o'clock position and filling counterclockwise.

             _.-'''''-._
           .'\ -3 |    /`.
          /   \   | 7 /   \
         |      \ |  /     |
         |  1     */   3   |
         |      / |\       |
          \   / 5 | 1\    /
           `._    |   \_.'
              `-.....-'

Assume the above is circle and split into equal parts, and the profit is marked inside.
We need to pick K consecutive parts and its opposites for the sprinkler. 

The profit levels, from the above pic are, 
1+5+ 7+3 = 16,
5+1+ 7+(-3) = 10, and
1+3+ -3+1 = 2. 

So the max profit is 16.
"""

"""
Actually the question isnt bit clear. If we are to choose only one K section, 
its fairly simple. But what if the field is divided into 12 segments, and k=2.
We can choose {1,2}, {4,5}  or {2,3}, {5,6}. That needs to be handled by recursion.
"""

if __name__ == "__main__":


