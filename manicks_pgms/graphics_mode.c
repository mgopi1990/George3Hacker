/*
 * 01. Displays various graphics modes 
 * run in turboc 
 *
 */

#include <stdio.h>
#include <graphics.h>

int main()
{
	int gd, gm, l, h;

	gd = DETECT;
	initgraph (&gd, &gm, "");
	outtextxy (10, 10, "GRAPHICS MODE");
	closegraph();

	printf ("\r TEXT MODES\r\n");

	for (gd = 1; gd <= 10; gd++)
	{
		initgraph (&gd, &gm, "");
		printf ("\r Driver name = %s\r\n", getdrivername());
		printf ("\r Driver no = %d\r\n", gd);
		printf ("\r MODE Name = %s\r\n", getmodename(gm));
		getmoderange (gd, &l, &h);
		printf ("\r MODE range: LOW:%d HIGH:%d\r\n", l, h);
		closegraph();
	}
	return 0;
}
