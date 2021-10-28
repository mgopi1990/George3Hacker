/* 
 * leetcode.com/problems/two-sum/
 *
 * 1. Two Sum
 * Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 *
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 *
 * You can return the answer in any order.
 *
 *  Example 1:
 *
 *  Input: nums = [2,7,11,15], target = 9
 *  Output: [0,1]
 *  Output: Because nums[0] + nums[1] == 9, we return [0, 1].
 *  Example 2:
 *
 *  Input: nums = [3,2,4], target = 6
 *  Output: [1,2]
 *  Example 3:
 *
 *  Input: nums = [3,3], target = 6
 *  Output: [0,1]
 */

#include <stdio.h>
#include <stdlib.h>

int *twoSum (int *nums, int numsSize, int target, int *returnSize)
{
	int i, j;
	int *retArray = NULL;

	for (i = 0; i < numsSize-1; i++)
	{
		for (j = i+1; j < numsSize; j++)
		{
			if ((nums[i] + nums[j]) == target)
			{
				retArray  = (int *) malloc (sizeof(int) *2);
				if (retArray == NULL)
				{
					*returnSize = 0;
					return NULL;
				}

				retArray[0] = i;
				retArray[1] = j;
				*returnSize = 2;

				return retArray;
			}			
		}
	}

	*returnSize = 0;
	return retArray;	
}

int main()
{
	int nums[] = {2, 7,	11, 15}, target = 9, returnSize;
	int *index;
   
	index = twoSum(nums, 4, target, &returnSize);	
	printf ("\r [%d %d]\r\n", index[0], index[1]);	

	return 0;	
}
