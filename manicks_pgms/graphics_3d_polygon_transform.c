/*
 * 07. Draws 3d polygon and performs translation, scaling and rotation.
 *
 * run in turboc 
 *
 */

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

void draw ();

int main()
{
	int gd = DETECT, gm;
	int i, n, x1, y1, x2, y2, d, t, a, b;

	initgraph (&gd, &gm, "");
	
	printf ("\r Enter x1, y1, x2, y2, d, t:\r\n");
	scanf ("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &d, &t);

	while (1)
	{
		bar3d (x1, y1, x2, y2, d, t);

		scanf ("%d", &n);
		
		switch (n)
		{
			case 1: /* transformation */
				printf ("\r Enter transformation x, y\r\n");
				scanf ("%d %d", &a, &b);
				bar3d (x1 + a, y1 + b, x2 + a, y2 + b, d, t);
				break;

			case 2: /* scaling */
				printf ("\r Enter scaling x, y\r\n");
				scanf ("%f %f", &a, &b);
				bar3d (x1 * a, y1 * b, x2 * a, y2 * b, d * a, t * a);
				break;

			case 3: /* rotation */
				printf ("\r Enter rotation:\r\n");
				scanf ("%f", &a);

				x1 = x1 * cos (a) + y1 * sin (a);
				x2 = x2 * cos (a) + y2 * sin (a);
				y1 = x1 * sin (a) - y1 * cos (a);
				y2 = x2 * sin (a) - y2 * cos (a);

				bar3d (x1, y1, x2, y2, d, t);
				break;
					
			default:
				return 0;
		}
	}

	getch ();
	return 0;
}

void draw ()
{
	cleardevice();
	line (320, 0, 30, 480);
	line (0, 240, 680, 240);
	setcolor (1);
	drawpoly (n+1, poly);
	setcolor (2);
	drawpoly (n+1, poly1);
	getch();
}
	
