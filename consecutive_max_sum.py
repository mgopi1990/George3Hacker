#!/usr/bin/env python3

'''
Given a list of numbers arr, consecutive numbers k, find the max sum.

eg:
Input:
4
1 2 3 4
2
Output:
7
Explanation: 3 and 4 are the k consecutive elements which gives the max_sum

'''

def consecutive_max_sum(arr, k):
    limit = len(arr) if (len(arr) < k) else k
    max_sum = 0
    i = 0
    for i in range(0, limit):
        max_sum += arr[i]

    local_sum = max_sum
    for i in range(i+1, len(arr)):
        local_sum += arr[i] - arr[i-k]
        max_sum = max_sum if (local_sum < max_sum) else local_sum

    return max_sum

if __name__ == "__main__":
    print (consecutive_max_sum([1,4,2,3,4,5,8,9], 3))
    # expected o/p 22

    print (consecutive_max_sum([], 0))
    # expected o/p 0

    print (consecutive_max_sum([], 3))
    # expected o/p 0

    print (consecutive_max_sum([1,4,2,3,4,5,8,9], 0))
    # expected o/p 0
    
    print (consecutive_max_sum([1,4,2,3,4,5,8,9], 1))
    # expected o/p 9

    print (consecutive_max_sum([10,4,2,3,4,5,8,9], 1))
    # expected o/p 10 
    
    print (consecutive_max_sum([10,7,10,8,4,5,8,9], 2))
    # expected o/p 18 

    print (consecutive_max_sum([1,4,2,3,4,5,8,9], 10))
    # expected o/p 36


