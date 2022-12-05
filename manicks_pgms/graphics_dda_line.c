/*
 * 03. Draws line by DDA line drawing algo
 *  y2 - y1 > x2 - x1 then length = abs (x2 - x1)
 *  xinc = (x2 - x1) / len
 *  yinc = (y2 - y1) / len
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
	int x1, x2, y1, y2, gd = DETECT, gm;
	float x, y, xinc, yinc, len;

	printf ("\r Enter x1, y1, x2, y2:\r\n"); 
	scanf ("%d %d %d %d", &x1, &y1, &x2, &y2);

	initgraph (&gd, &gm, "");
	cleardevice ();

	len = abs (x2 - x1);
	if (abs (y2 - y1) > len)
		len = abs (y2 - y1);

	xinc = ((float) (x2 - x1)) / len;
	yinc = ((float) (y2 - y1)) / len;

	x = x1 + 0.5;
	y = y1 + 0.5;

	for (i = 1; i <= 10; i++)
	{
		putpixel (float (x), float (y), 1);
		x += xinc;
		y += yinc;
	}

	closegraph ();
	getch ();
}
