/* solve using C 
How many way to reach the end point from start.
You can only move right and down 

start
.- + - + -.
|  |   |  |
.- + - + -.
|  |   |  |
.- + - + -.
|  |   |  |
.- + - + -.
         end
*/

#include <stdio.h>

#define BITS_PER_BYTE 8

int solve_numeric(int nrow, int ncol);
int print_path (unsigned int num, int nrow, int ncol);
int bit_match(unsigned int num, int n);

char *sym = "DR";

int main(int argc, int *argv[])
{
	int nrow, ncol;

	if (argc != 3) 
	{
		printf ("\r Usage:\n %s <nrow> <ncol>\r\n", argv[0]);
		return -1;
	}

	nrow = atoi(argv[1]);
	ncol = atoi(argv[2]);
	if (!(1<<(nrow+ncol+1)))
	{
		printf ("\r Try dimension below %d\r\n", (sizeof(int)*BITS_PER_BYTE)-1);
		return -1;
	}

	solve_numeric(nrow, ncol);
	return 0;
}

int solve_numeric(int nrow, int ncol)
{
	unsigned int min = 0, max, i;
	int nsol = 0;
	for (i = 0; i < ncol; i++)
	{
		min <<= 1;
		min |= 0x01;
	}

	max = min;
	max <<= nrow;
	for (i = min; i <= max; i++)
	{
		if(bit_match(i, ncol))
		{
			nsol++;
			print_path(i, nrow, ncol);		
		}
	}
	printf ("\r %d solutions found\r\n", nsol);
	return 0;
}

int solve_graph(int nrow, int ncol)
{
	/* ToDo: Complete this function 
	   Someday gotta construct a tree here and find the ans 	
	*/
	return 0;
}

/* Checks if exact number of 1s are present */
int bit_match(unsigned int num, int n)
{
	unsigned int nbit = 0;
	while (num)
	{
		nbit += num & 0x01;
		num >>= 1;	
	}
	return (nbit == n);
}

/* Prints the path */
int print_path (unsigned int num, int nrow, int ncol)
{
	char temp_str[sizeof(int)*BITS_PER_BYTE+1];
	int i = 0;
	for (i = 0; num || (i < (nrow+ncol)); i++)
	{
		temp_str[i] = sym[num & 0x01];	
		num >>= 1;
	}
	temp_str[i] = '\0';
	printf ("\r %s\r\n", temp_str);
	return 0;	
}
