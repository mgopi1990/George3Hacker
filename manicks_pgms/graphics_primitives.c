/*
 * 02. Graphics primitives
 * Draws line, circle, ellipse, 3dbar, polygon
 * run in turboc 
 *
 */

#include <stdio.h>
#include <graphics.h>

int main()
{
	int gd = DETECT, gm;
	int x1, x2, y1, y2, z1, z2, r1, r2, n, mx, my;
	int poly[10];
	
	initgraph (&gd, &gm, "");

	while (1)
	{
		cleardevice();
		printf ("\r 1. Line\r\n 2. Circle\r\n 3. Ellipse\r\n 4. 3d Bar\r\n"
				"\r 5. Polygon\r\n 6. Exit\r\n");
		scanf ("%d", &n);

		switch (n)
		{
			case 1: /* line */
				printf ("\r Enter coordinates for line\r\n");
				scanf ("%d %d %d %d", &x1, &y1, &x2, &y2);
				cleardevice();
				line (x1, y1, x2, y2);
				break;

			case 2: /* circle */
				printf ("\r Enter x, y, r for circle\r\n");
				scanf ("%d %d %d", &x1, &y1, &r1);
				cleardevice();
				circle (x1, y1, r1);
				break;

			case 3: /* ellipse */
				printf ("\r Enter x, y, r1, r2 for ellipse\r\n");
				scanf ("%d %d %d %d", &x1, &y1, &r1, &r2);
				cleardevice();
				ellipse (x1, y1, r1, r2);
				break;

			case 4: /* 3dbar */
				printf ("\r Enter x1, y1, z1, x2, y2, z2 for 3dbar\r\n");
				scanf ("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
				cleardevice();
				3dbar (x1, y1, x2, y2, z1, z2);
				break;
	
			case 5: /* polygon */
				mx = getmaxx();
				my = getmaxy();

				poly[0] = 20;
				poly[1] = my / 2;
				poly[2] = mx - 20;
				poly[3] = 20;
			   	poly[4] = mx - 50;
			   	poly[5] = my - 20;
			   	poly[6] = mx / 2;
			   	poly[7] = my / 2;
			   	poly[8] = 20;
			   	poly[9] = my / 2;
			   
				drawpoly (5, poly);
				fillpoly (5, poly);
				break;

			default: 
				return;
		}
	}
}


