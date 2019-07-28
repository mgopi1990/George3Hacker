/*
 * Finds the sum of digits
 * 
 * eg.
 *
 * INPUT: 
 * 123456
 *
 * OUTPUT:
 * 3
 *
 * EXPLANATION:
 * 1+2+3+4+5+6 = 21
 * 2 + 1       = 3
 *
 */

#include <stdio.h>

int sumOf(unsigned long int num);

int main()
{
	unsigned long int num;

	scanf("%ld", &num);
	printf("%d\r\n", sumOf(num));

	return 0;
}

int sumOf(unsigned long int num)
{
	int sum;

	while(num > 9)
	{
		sum = 0;
		while (num > 0)
		{
			sum += num%10;
			num /= 10;
		}
		num = sum;
	}

	return num;
}
