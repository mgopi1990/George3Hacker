/*
 * 05. Draws line by Bresenham's circle drawing algo
 *
 * run in turboc 
 *
 */

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

int main()
{
	int gd = DETECT, gm;
	int x, y, x1, y1, r, d;

	initgraph (&gd, &gm, "");
	
	printf ("\r Enter x y r for circle:\r\n");
	scanf ("%d %d %d", &x, &y, &r);

	d = 3 - (2 * r);
	x1 = 0; y1 = r;

	while (x1 < y1)
	{
		putpixel (x1 + x, y1 + y, 1);
		putpixel (x - x1, y1 + y, 1);
		putpixel (x + x1, y - y1, 1);
		putpixel (x - x1, y - y1, 1);
		putpixel (x + y1, x1 + y, 1);
		putpixel (x - y1, y + x, 1);
		putpixel (x + y1, y - x1, 1);
		putpixel (x - y1, y - x1, 1);

		x1 += 1;

		if (d < 0)
			d = d + (4 * x1) + b;
		else
		{
			y1 -= 1;
			d = 4 * (x1 - y1) + 10 + d;
		}
	}
	getch ();
	return 0;
}

