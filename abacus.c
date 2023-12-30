/*
 * abacus program
 *
 * prints abacus output in screen
 *
 * eg:

 * ./a.out 33.442
 *
 *  33.442:
 * -----------------
 * 00000000000000000
 * 
 * --+--+--+--+--+--
 *        00000
 * 00000000000000000
 * 00000000000 00000
 * 0000000  00000000
 * 000000000  000000
 * -----------------
 *
 */

#include <stdio.h>

#define BEAD_DIGITS 17
#define BEAD_GROUP  3
#define DECIMAL_START  9

#define BEAD	"0"
#define NO_BEAD	" "

#define HEAVEN_VALUE 5

/* bead set position */
enum {
	BEAD_BIT_HEAVEN0 = 0x40,
	BEAD_BIT_HEAVEN1 = 0x20,
	BEAD_BIT_EARTH0  = 0x10,
	BEAD_BIT_EARTH1  = 0x08,
	BEAD_BIT_EARTH2  = 0x04,
	BEAD_BIT_EARTH3  = 0x02,
	BEAD_BIT_EARTH4  = 0x01,
};

/* bead bits */
enum {
	BEAD_HEAVEN0 = 0x40, /* <5 - 10 00000 */
	BEAD_HEAVEN1 = 0x20, /* >5 - 01 00000 */

	BEAD_EARTH0  = 0x0F, /* 0  - 00 01111 */
	BEAD_EARTH1  = 0x17, /* 1  - 00 10111 */
	BEAD_EARTH2  = 0x1B, /* 2  - 00 11011 */
	BEAD_EARTH3  = 0x1D, /* 3  - 00 11101 */
	BEAD_EARTH4  = 0x1E  /* 4  - 00 11110 */
};

/* bead arrangement for digit */
char digit_bit[] = {
	/* 0 */	BEAD_HEAVEN0 | BEAD_EARTH0,
	/* 1 */ BEAD_HEAVEN0 | BEAD_EARTH1,
	/* 2 */ BEAD_HEAVEN0 | BEAD_EARTH2,
	/* 3 */ BEAD_HEAVEN0 | BEAD_EARTH3,
	/* 4 */ BEAD_HEAVEN0 | BEAD_EARTH4,
	/* 5 */ BEAD_HEAVEN1 | BEAD_EARTH0,
	/* 6 */ BEAD_HEAVEN1 | BEAD_EARTH1,
	/* 7 */ BEAD_HEAVEN1 | BEAD_EARTH2,
	/* 8 */ BEAD_HEAVEN1 | BEAD_EARTH3,
	/* 9 */ BEAD_HEAVEN1 | BEAD_EARTH4
};

/* draws ------ */
void draw_line() 
{	
	int i;

	for (i = 0; i < BEAD_DIGITS; i++)
		printf ("-");
	printf ("\r\n");
}

/* draws ---*--- seperator */
void draw_seperator()
{
	int i, j; 

	for (i = 0; i < (BEAD_DIGITS/BEAD_GROUP); i++) 
	{
		for (j = 1; j < BEAD_GROUP; j++)
		{
			printf ("-");
		}
		printf ("+");
	}

	for (j = 1; j < BEAD_GROUP; j++)
	{
		printf ("-");
	}

	printf ("\r\n");
}

/* draw single row beads */
void draw_beads(int set_bit, char *bead_bits)
{
	int i;

	for (i = 0; i < BEAD_DIGITS; i++)
	{
		printf ((bead_bits[i] & set_bit)?BEAD:NO_BEAD);
	}
	printf ("\r\n");
}

/* converts input number into abacus bead representation */	
int set_bead_bits(char *bead_bits, char *num)
{
#define NO_DEC_POINT -1
	int i, j, len, num_start_pos;
	int dec_point = NO_DEC_POINT;

	/* verify if it is valid number */
	for (len = 0; num[len] != '\0'; len++) 
	{
		if (num[len] == '.')
		{
			if (dec_point != NO_DEC_POINT)
			{
				return -1;
			}

			dec_point = len;
		}
		else if (!(num[len] >= '0' && num[len] <= '9'))
		{
			return -1;
		}
	}

	/* input number cant fit in the abacus */
	if (len > BEAD_DIGITS)
	{
		return -1;
	}

	/* reset the beads */
	for (i = 0; i < BEAD_DIGITS; i++)
 	{
		bead_bits[i] = digit_bit[0];
	}

		
	num_start_pos = (dec_point == NO_DEC_POINT) ?
					DECIMAL_START - len :
					DECIMAL_START - dec_point;

	/* currently we place the decimal abacus middle */
	if (num_start_pos < 0)
	{
		return -1;
	}

	j = 0;
	i = num_start_pos;
	for (j = 0; j < len; j++)
	{
		/* skip . */
		if (num[j] == '.')
			continue;

		bead_bits[i++] = digit_bit[num[j] & 0x0F];
	}
	
	return 0;
}

/* draws abacus */
int draw_abacus(char *num) 
{
	int i;
	char bead_bits[BEAD_DIGITS];
	
	printf ("\r\n\n %s:\r\n", num);

	if (set_bead_bits(bead_bits, num) != 0)
	{
		printf ("\r Invalid Input:%s\r\n", num);
		return -1;
	}

	/* Draw heading */
	draw_line();
	
	/* Draw heaven */
	draw_beads (BEAD_BIT_HEAVEN0, bead_bits);
	draw_beads (BEAD_BIT_HEAVEN1, bead_bits);

	/* Draw seperator */
	draw_seperator();

	/* Draw earth */
	draw_beads (BEAD_BIT_EARTH0, bead_bits);
	draw_beads (BEAD_BIT_EARTH1, bead_bits);
	draw_beads (BEAD_BIT_EARTH2, bead_bits);
	draw_beads (BEAD_BIT_EARTH3, bead_bits);
	draw_beads (BEAD_BIT_EARTH4, bead_bits);

	/* Draw footer */
	draw_line();

	return 0;
}


/* start of main pgm */
int main(int argc, char *argv[])
{
	int i;

	if (argc <= 1) 
 	{
		printf ("\r Usage: %s <num1> <num2> .. <num>\r\n", argv[0]);
		return -1;
	}

	for (i = 1; i < argc; i++)
	{
		draw_abacus(argv[i]);
	}

	return 0;
}
