/*
*   FLAMES in Turbo C; Run from DOSBOX..
*   Graphical...
*   Make sure path to .BGI files are set correctly in initgraph();
*	  Adjust wait property to alter time interval for delay();
*/

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>

int cwidth(char a)
{
	char tmp[2]=" ";
	tmp[0]=a;
	return(textwidth(tmp));
}

void display(int x,int y,int color,int space,char *text)
{
	int i,dx,t;
	char tmp[]=" ";
	setcolor(color);

	for(i=0;text[i]!='\0';i++)
	{
		tmp[0]=text[i];
		outtextxy(x,y,tmp);
		x+=space+textwidth(tmp);
	}
}

void main()
{
	int gd=DETECT,gm,width=75,space1=5,under=12,wait=100,stop=0;
	char fire[2][7]={"flames","flames"},msg[2][7]={"thanks","sorry"};
	int t,t1,t2,u,i,j,k,l,m,space,x,y,x2,y2,x3,dx,dx2,maxx,maxy,len[2];
	char a,name[3][30];

	initgraph(&gd,&gm,"E:\\gopi\\tc\\bgi");

	maxx=getmaxx();
	maxy=getmaxy();
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR,4);
	t=textwidth("_");
	u=textwidth("\\");

	while(stop==0)
	{
		cleardevice();
		space=space1;

		for(i=0;fire[1][i]!='\0';i++)
			fire[0][i]=fire[1][i];

		for(i=0;i<2;i++)
		{
			if(stop==1)	break;

			x=maxx/2;
			y=maxy/4;
			m=0;
			l=0;
			j=0;
			while(1)
			{
				if(m==1)	display(x+l+space*j,y+i*width,WHITE,space,"|");
				else if(m==50) display(x+l+space*j,y+i*width,BLACK,space,"|");
				m=m++%100;

				if(kbhit())
				{
					display(x+l+space*j,y+i*width,BLACK,space,"|");
					a=getch();
					if(((a>='A'&&a<='Z')||(a>='a'&&a<='z')||a==' '||a==8||a==13))//8 backspace, 13 enter
					{
						display(x,y+i*width,BLACK,space,name[i]);

						if(a>='A'&&a<='Z')	a|=0x20;

						if(a==8)
						{
							if(j!=0) name[i][--j]='\0';
						}
						else
						{
							if(a!=13) name[i][j++]=a;
							name[i][j]='\0';
						}

						l=textwidth(name[i]);
						x=(maxx-l-space*(j-1))/2;

						display(x,y+i*width,WHITE,space,name[i]);
						if(a==13||j>=30)
						{
							len[i]=j;
							break;
						}
					}
					else
					{
						stop=1;
						break;
					}
				}
				else delay(10);
			}
		}

		if(stop==0)
		{
			for(i=0;i<len[1];i++)
				name[2][i]=name[1][i];
			name[2][i]='\0';

			m=wait;
			x=(maxx-textwidth(name[0])-space*len[0]+space)/2;
			x3=(maxx-textwidth(name[1])-space*len[1]+space)/2;

			y=under+maxy/4;
			y2=under+width+maxy/4;
			for(i=0;i<len[0];i++)
			{
				t1=cwidth(name[0][i]);
				if(name[0][i]!=' ')
				{
					dx=(t1-t)/2;
					display(x+dx,y,WHITE,space,"_");

					x2=x3;
					for(j=0;j<len[1];j++)
					{
						t2=cwidth(name[2][j]);

						if(kbhit())
						{
							m=0;
							getch();
						}

						if(name[1][j]!=' ')
						{
							dx2=(t2-t)/2;
							display(x2+dx2,y2,WHITE,space,"_");

							if(name[0][i]==name[1][j])
							{
								l=(cwidth(name[0][i])-u)/2;
								delay(m);
								display(x+l,y-10,WHITE,space,"\\");
								display(x2+l,y2-10,WHITE,space,"\\");
								name[0][i]=name[1][j]=' ';
								k=1;
							}
							delay(m);
						}
						display(x2+dx2,y2,BLACK,space,"_");
						x2+=t2+space;

						if(k==1)
						{
							k=0;
							break;
						}
					}
				}
				display(x+dx,y,BLACK,space,"_");
				x+=t1+space;
			}

			if(kbhit())
			{   m=wait;
				getch();
			}

			for(i=0,l=0;i<2;i++)
			{
				for(j=0;j<len[i];j++)
				{
					if(name[i][j]!=' ')
					l++;
				}
			}

			space*=3;
			y=y+2.5*width;
			if(l!=0)
			{
				for(i=0;fire[1][i]!='\0';i++);
				x=(maxx-textwidth(fire[1])-space*i)/2;
				display(x,y,WHITE,space,fire[1]);

				i=0;
				k=5;
				x2=x;
				y2=y+under;
				while(i<5)
				{
					for(j=0;j<l;j++)
					{
						if(kbhit())
						{
							m=0;
							getch();
						}

						while(fire[0][++k%6]==' ');

						for(t2=0,x2=x;t2<k%6;t2++)
							x2+=cwidth(fire[1][t2])+space;

						dx=(cwidth(fire[1][k%6])-t)/2;
						display(x2+dx,y2,WHITE,space,"_");
						if(kbhit())
						{
							m=0;
							getch();
						}
						delay(m*1.2);
						display(x2+dx,y2,BLACK,space,"_");
					}
					fire[0][k%6]=' ';
					i++;
					dx=(cwidth(fire[1][k%6])-u)/2;
					display(x2+dx,y2-10,WHITE,space,"\\");
				}


				while(fire[0][++k%6]==' ');

				for(t2=0,x2=x;t2<k%6;t2++)
					x2+=cwidth(fire[1][t2])+space;


				fire[0][0]=fire[1][k%6];
				fire[0][1]='\0';

				delay(m*2);
				dx=(cwidth(fire[1][k%6])-t)/2;
				display(x2+dx,y+under,WHITE,space,"_");
				display(x2,y,GREEN,space,fire[0]);
			}
			else
			{
				for(i=0;msg[1][i]!='\0';i++);
				x=(maxx-textwidth(msg[1])-i*space*4)/2;
				display(x,y,WHITE,space*4,msg[1]);
			}
		}
		else
		{
			for(i=0;msg[0][i]!='\0';i++);
			x=(maxx-textwidth(msg[0])-i*space*4)/2;
			cleardevice();
			display(x,y,WHITE,space*4,msg[0]);
		}
		getch();
	}
	closegraph();
}
