/* 
4. Median of Two Sorted Arrays
Hard
Topics
premium lock icon
Companies
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

 

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
*/

#include <stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size,
							  int* nums2, int nums2Size)
{
	int last;
	int totSize = num1Size + num2Size;
	int medianIndex1;
	int medianIndex2 = totSize/2;
	int filled = 0;
	int i = 0, j = 0;
	double median;

	/* 
	 * we dont have to sort the entire array.
	 * we just need the mid elements
	 * so lets just move i, j until we reach median index
	 * this leads to 3 cases,
	 * 1. filled reached median.
	 *   - nums1 & nums2 still have elements; last would point to median
	 * 2. if either of nums1 or nums2 is over
	 *   - calculate the position of median in non exhausted array
	 */
	while ((filled < medianIndex2) &&
		   (i < nums1Size) && 
		   (j < nums2Size))
	{
		if (nums1[i] < nums2[j]) 
		{
			i++;
			last = 1;
		}
		else
		{
			j++;
			last = 2;
		}
	
		filled++;
	}

	/* filled reached median */
	if (filled == medianIndex2) 
	{

	}
	return median;
}


int main()
{
	int nums1 = {1,2};
	int nums2 = {3,4};

	printf ("\r %lf\r\n", findMedianSortedArrays(nums1, sizeof(nums1),
												 nums2, sizeof(nums2)));
	return 0;
}
