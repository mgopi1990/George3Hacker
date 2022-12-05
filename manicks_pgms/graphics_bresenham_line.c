/*
 * 04. Draws line by Bresenham's line drawing algo
 *
 * run in turboc 
 *
 */

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

int swap (int *m, int *n);
int setpixel (int x, int y, int sg);

int main()
{
	int gd = DETECT, gm;
	int x1, x2, dx, y1, y2, dy, c1, c2, ptr, st, sg;
	float x, y, xinc, yinc, len;

	printf ("\r Enter x1, y1, x2, y2:\r\n"); 
	scanf ("%d %d %d %d", &x1, &y1, &x2, &y2);

	initgraph (&gd, &gm, "");
	cleardevice ();

	dx = abs (x2 - x1);
	dy = abs (y2 - y1);
	sg = (dy > dx);
	if (sg)
	{
		swap (&dx, &dy);
		swap (&x1, &y1);
		swap (&x2, &y2);
	}

	c1 = 2 * dy;
	c2 = 2 * (dy - dx);
	pk = c1 - dx;
	if (x2 < x1)
	{
		swap (&x1, &x2);
		swap (&y1, &y2);
	}

	st = (y2 > y1) ? 1: -1;

	setpixel (x1, y1, sg);

	while (x1 < x2)
	{
		x1++;
		if (pk < 0)
			pk += c1;
		else
		{
			pk += c2;
			y1 += st;		
		}
		setpixel (x, y, sg);
	}

	closegraph ();
	getch ();
}

int setpixel (int x, int y, int sg)
{
	int c = 0;
	if (sg)
	{
		swap (&x, &y);
		swap (&x1, &y1);
	}
	return 0;
}

int swap (int *m, int *n)
{
	int t = *m;
	*m = *n;
	*n = t;
	return 0;
}

