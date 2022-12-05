/*
 * 06. Draws 2d polygon and performs translation, scaling and rotation.
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
	int poly[50], poly1[50], n, q, i, x1, y1, c;
	flaot ang, x2, y2;

	initgraph (&gd, &gm, "");
	
	printf ("\r Enter the no. of vertices\r\n");
	scanf ("%d", &n);
	a = (n * 2) + 2;

	printf ("\r Enter the co-ordinates of the polygon\r\n");
	for (i = 0; i < a; i++)
	{
		scanf ("%d", &poly[i]);
		cleardevice();
		poly[i] += (i % 2 == 0) ? 320: 240;
	}
	
	line (320, 0, 320, 480);
	line (0, 240, 680, 240);
	setcolor (1);
	drawpoly (n + 1, poly);
	getch ();

	while (1)
	{
		cleardevice();
		printf ("\r 1. Transformation\r\n 2. Scaling\r\n"
				" 3. Rotation\r\n 4. Exit\r\n"
				"\r Enter your choice: ");
		scanf ("%d", &c);

		switch (c)
		{
			case 1: /* transformation */
				printf ("\r Enter tx, ty\r\n"); 
				scanf ("%d %d", &x1, &y1);
				
				for (i = 0; i < a; i++)
				{
					if (i % 2 == 0)
					{
						poly[i] = poly[i] + x1;
					}
					else
					{
						poly[i] = poly[i] + y1;
					}
				}
				draw ();
				break;

			case 2: /* scaling */
				printf ("\r Enter sx, sy\r\n");
				scanf ("%f %f", &x2, &y2);

				for (i = 0; i < a; i++)
				{
					if (i % 2 == 0)
					{
						poly[i] = poly[i] * x2;
					}
					else
					{
						poly[i] = poly[i] * y2;
					}
				}


				drawpoly (5, poly);
				break;

			case 3: /* rotation */
				int t, xf, yf;

				printf ("\r Enter deg: ");
				scanf ("%f", &ang);

				ang *= (3.14/180);
				xf = poly[0];
				yf = poly[1];

				for (i = 2; i < a-2 ; i += 2)
				{
					poly1[i] = (int) abs ((xf + ((poly[i] - xf) * cos(ang))) -
									((poly[i+1] -yf) * sin(ang));
					poly[i+1] = (int) abs ((yf + ((poly[i] - xf) * sin(ang))) +
									((poly[i+1] -yf) * cos(ang));
				}

				for (i = a - 2; i < a; i++)
					poly1[i] = poly[i];

				for (i = 0; i < a; i++)
					poly[i] = poly1[i];

				drawpoly (5, poly1);
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
	
