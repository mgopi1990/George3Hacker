/*
 * 11. Beizier curve
 *
 * run in turboc 
 *
 */

#include <stdio.h>
#include <graphics.h>

int main()
{
	double numsteps, i, t;
	float stepsize;
	int x0, y0, x1, y1, x2, y2, x3, y3;
	int ax, ay, bx, by, cx, cy, dx, dy;
	int gd = DETECT, gm;
	
	initgraph (&gd, &gm, "");
	scanf ("%d %d %d %d %d %d %d %d", &x0, &y0, &x1, &y1, &x2, &y2, &x3, &y3);

	cleardevice();
	ax = -x0 + 3 * x1 + (-3 * x2) + x3;
	ay = -y0 + 3 * y1 + (-3 * y2) + y3;
	bx = 3 * x0 + (-6 * x1) + 3 * x2;
	by = 3 * y0 + (-6 * y1) + 3 * y2;
	cx = -3 * x0 + 3 *x1;
	cy = -3 * y0 + 3 *y1;

	dx = x0;
	dy = y0;

	setcolor (Blue);
	numsteips = 100;
	stepsize = 1.0 / (double) numsteps;
	moveto (dx, dy);
	
	for (i = 1; i < numsteps; i++)
	{
		t = stepsize * (double) *i;
		x = ax * t3 + b * t2 + c * t;
		y = ay * (t*t*t) + by * (t * t) + c *t + dy;
		lineto (x, y);
	}
	getch();
	closegraph();
	restoreCRTmode();
}



