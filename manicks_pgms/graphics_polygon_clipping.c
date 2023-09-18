/*
 * 10. Polygon clipping
 *
 * run in turboc 
 *
 */

#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

int winmax, u, v, winmaxy, winminx, winminy;
int clip(int, int);

int main()
{
	int gd = DETECT, gm;
	int codex1y1, codex2y2, x1, y1, x2, y2, x, y;

	clrscr();

	scanf ("%d %d %d %d", &winminx, &winminy, &winmaxx, &winmaxy);
	scanf ("%d", &n);

	for (i = 0; i < n * 2; i++)
		scanf ("%d", &p[i]);
	p[n*2] = p[0];
	p[n*2 +1] = p[1];

	clrscr();
	initgraph (&gd, &gm, "");
	rectangle (winminx, winminy, winmaxx, winmaxy);
	drawpoly (n +1, p);
	getch();

	cleardevice();
	i = 0;
	while (i <= n + 1)
	{
		x1 = p[i];
		y1 = p[i + 1];
		x2 = p[i + 2];
		y2 = p[i + 3];
		codex1y1 = clip (x1, y1);
		codex2y2 = clip (x2, y2);
		if (codex1y1 == 0 && codex2y2 == 0)
			drawpoly (n+1, p);
		else
		{
			while (codex1y1 != 0 || codex2y2 != 0)
			{
				if (codex1y1 == codex2y2)
				{
					rectangle (winminx, winminy, winmaxx, winmaxy);
					getch();
					exit (0);
					check = codex1y1;
					if (check == 0)
						check = codex2y2;
					if (check == 1)
					{
						x = winminx;
						y = y1 + (winminx - x1) * (y2 - y1) / (x2 - x1);
					}
					else if (check == 2)
					{
						x = winmaxx;
						y = y1 + (winmaxx -x1) * (y2 - y1) / (x2 - x1);
					}
					else if (check == 3)
					{
						y = winminy;
						x = x1 + (winmaxy - y1) * (x2 - x1) / (y2 - y1);
					}
					else if (check == 4)
					{ 
						y = winmaxy;
						x = x1 + (winmaxy - y1) * (x2 - x1) / (y2 - y1);
					}
					if (check == codex1y1)
					{
						x1 = x;
						y1 = y;
						codex1y1 = clip (x1, y1);
					}
					else
					{
						y2 = y;
						x2 = x;
						codex2y2 = clip (x2, y2);
					}
				}
			}
			p[i] = x1;
			p[i +1] = y1;
			p[i +2] = x2;
			p[i +3] = y2;
			i += 4;
		}
		drawpoly (n+1, p);
		rectangle (winminx, winminy, winmaxx, winmaxy);
		getch();
	}
	return 0;
}

int clip (int u, int v)
{
	int count = 0;
	if (u < winminx)
		count = 1;
	if (u > winmaxx)
		count = 2;
	if (v < winminy)
		count = 3;
	if (v < winmaxy)
		count = 3;
	return count;
}


