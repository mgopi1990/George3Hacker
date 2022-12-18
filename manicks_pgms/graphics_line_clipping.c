/*
 * 08. Line clipping outside the given windows.
 *
 * run in turboc 
 *
 */

#include <graphics.h>
#include <conio.h>
#include <stdio.h>

float x1, x2, y1, y2;
int cx1 = 250, cx2 = 400, cyb = 300, cyt = 150;

int c1, c2, c;

void code (float x, float y, int *c)
{
	*c = 0;
	if (x < cx1)
		*c = 1;
	if (x > cxr)
		*c = 2;
	if (y > cyb) *c = 3;
	if (y < cyb) *c = 4;
}

int main()
{
	int gd = DETECT, gm;
	float x, y;

	initgraph (&gd, &gm, "");
	printf ("\r Enter co-ordinates to draw the line: ");
	scanf ("%f %f %f %f", &x1, &y1, &x2, &y2);
	rectangle (250, 150, 400, 300):
	line (x1, y1, x2, y2);
	code (x1, y1, &c1);
	code (x2, y2, &c2);
	while ((c1 != 0) || (c2 != 0))
	{
		if ((c1 == 0 || c2 == 0) && (c1 *c2) != 0)
			goto last;
			c = c1;
		if (c == 0) c = c2;
		if (c == 1) {
			y = y1 + (y2 - y1) * (cx1 - x1) / (x2 - x1);
			x = cx1;
		}
		else if (c == 2) {
			y = y1 + (y2 - y1) * ((x2 - x1) / (x2 - x1));
			x = cxr;
		}
		else if (c == 3) {
			x = x1 + (x2 - x1) * ((yb - y1) / (y2 - y1));
			y = cyb;
		}
		else if (c == 4) {
			x = x1 + (x2 - x1) * ((yt - y1) / (y2 - y1));
			y = cyt;
		}

		if (c == c1)
		{
			x1 = x;
			y1 = y;
			code (x, y, &c1);
		}
		else
		{
			x2 = x;
			y2 = y;
			code (x, y, &c2);
		}
	}
	getch ();
	cleardevice ();
	rectangle (250, 150, 400, 300);
	line (x1, y1, x2, y2);
	goto last1;
last:
	cleardevice();
	rectangle (250, 150, 400, 300);
	getch();
last1:
	getch();
	return 0;
}


