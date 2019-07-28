#include <stdio.h>

int bits_on(unsigned long n);

int main()
{
	int n;
	scanf ("%d", &n);
	printf ("%d", bits_on(n));
	return 0;
}

int bits_on(unsigned long n)
{
	int bits = 0;
	while(n)
	{
		bits += n & 0x1;
		n >>= 1;
	}
	return bits;
}
