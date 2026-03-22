/*
 *  gcd(m, n), is defined as the largest integer that divides
 *  both m and n evenly, i.e., with a remainder of zero. 
 *
 *  Euclid’s algorithm:
 *  gcd(m, n) = gcd(n, m mod n)
 *
 *  eg: ./a.out 24 60 
 *  ./a.out 31415 14142
 */

#include <stdio.h>
#include <stdlib.h>

int gcd_euclid (int m, int n) 
{
	int temp, r;

	/* works even n > m */
	while (n > 0)
	{
		r = m % n;
		m = n;
		n = r;
	}

	return m;
}

int main(int argc, char *argv[])
{
	int num1, num2;

	if (argc != 3)
	{
		printf ("Usage: %s <num1> <num2>\r\n", argv[0]);
		return 0;
	}

	num1 = atoi(argv[1]);
	num2 = atoi(argv[2]);
	
	printf ("\r gcd(%d,%d): %d\r\n", num1, num2, gcd_euclid(num1, num2));
	return 0;
}
