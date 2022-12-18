/*
 * 09. Complex transformation
 *
 * run in turboc 
 *
 */

#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

int main()
{
	int gd = DETECT, gm;
	int x1, y1, x2, y2, x3, y3, x4, y4, sy, sx, x, y;

	initgraph (&gd, &gm, "");
	scanf ("%d %d %d %d", &x1, &y1, &x2, &y2);
	x3 = x1;
	y3 = y1;
	x4 = x2;
	y4 = y2;
	line (x1, y1, x2, y2);
	getch();

	printf ("\r Enter the translation factor ");
	scanf ("%d %d", &x, &y);

	x1 += x;
	x2 += x;
	y1 += y;
	y2 += y;
	line (x1, y1, x2, y2);

	printf ("\r Enter scaling factor ");
	scanf ("%d %d", &sx, &sy);

	x1 *= sx;
	x2 *= sx;
	y1 *= sy;
	y2 *= sy;
	line (x1, y1, x2, y2);
	printf ("\r Complex transformation ");
	line ((x3 + x) * sx, (y3 + y) * sy, (x4 + x)  * sx, (y4 + y) * sy);
	getch();
	return 0;
}


