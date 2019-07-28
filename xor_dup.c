#include<stdio.h>
#define ARRAY_LEN 15
	
int find_unique(int *array, int n)
{
	int i, ans;
	ans = array[0];
	for (i = 1; i < n; i++)
		ans ^= array[i];
	return ans;
}

int main()
{
	int array[] = {1,1,2,3,4,5,4,3,2,5,6,7,7,9,9};
	printf ("\r %d\r\n", find_unique(array, ARRAY_LEN));
	return 0;
}
