/*
*   TICTACTOE in Turbo C; Run from DOSBOX..
*   Graphical...
*   Make sure path to .BGI files are set correctly in initgraph();
*	  Adjust wait property to alter time interval for delay();
*/

#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>

//639 479
const int row=6,col=30,move=85;

void pause(int);
void kbreset(void);

void x(int,int,int);
void o(int,int,int);
void box(int,int,int);
void arena(int,int);

void cross(int,int,int);
void crossNS(int,int);
void crossEW(int,int);
void crossNE(int,int);
void crossSE(int,int);

void tictoc(void);
void welcome(int);     				  //y=85 ,85
void new_game(int);
void options(void);
void credits(void);
void rules(void);
void quit(void);

void pvp();


void heading(int,int,int,char [col]);
int display(int,int,char [row][col]);
void cleardisplay(int,int,char [row][col]);
int getkey(int,int,int,char [row][col]);
void highlight(int,int,int,char [row][col]);
void nohighlight(int,int,int,char [row][col]);
void center(int,int,char [150]);

void main()
{
	int gdrive=DETECT,gm;
	int i;
	char msg[10];

	initgraph(&gdrive,&gm,"C:\\tc\\bgi\\");

	tictoc();
	welcome(0);

	closegraph();
}

void pause(int time)
{
	if(!kbhit())
		delay(time);
}

void kbreset()
{
	if(kbhit())
		getch();
}

void cleardisplay(int x,int y,char a[row][col])
{
	settextjustify(1,0);
	setcolor(BLACK);

	for(int no=0;a[no][0]!='\0';no++)
		outtextxy(x,y+no*40,a[no]);

	settextjustify(0,0);
	setcolor(LIGHTGRAY);
}

void x(int x,int y,int color=1)
{
	const int l=25;

	if(color==1)
		setcolor(BLUE);
	else
		setcolor(BLACK);
	for(int i=-5;i<5;i++)
	{
		line(x-l+i,y-l,x+l+i,y+l);
		line(x+l+i,y-l,x-l+i,y+l);
	}
	setcolor(LIGHTGRAY);
}

void o(int x,int y,int color=1)
{
	const int r=20;
	if(color==1)
		setcolor(GREEN);
	else
		setcolor(BLACK);
	for(int i=0;i<10;i++)
	{
		circle(x,y,r+i);
	}
	setcolor(LIGHTGRAY);
}

void box(int x,int y,int color=1)
{
	const int l=33;

	if(color==1)
		setcolor(RED);
	else
		setcolor(BLACK);

	setlinestyle(2,1,1);

	for(int i=0;i<3;i++)
		rectangle(x-l-i,y-l-i,x+l+i,y+l+i);

	setlinestyle(0,1,1);
	setcolor(LIGHTGRAY);
}

void arena(int x,int y)
{
	const int l=35,m=85;
	setcolor(YELLOW);
	for(int i=0;i<15;i++)
	{
		line(x-l-m,y-l-i,x+l+m,y-l-i);
		line(x+l+i,y-l-m,x+l+i,y+l+m);
		line(x+l+m,y+l+i,x-l-m,y+l+i);
		line(x-l-i,y+l+m,x-l-i,y-l-m);
	}
	setcolor(LIGHTGRAY);
}

void cross(int x,int y,int choice)
{
	setcolor(BROWN);

	switch(choice)
	{
		case 1:   crossNS(x,y);	break;
		case 2:	crossEW(x,y);	break;
		case 3: 	crossNE(x,y);	break;
		case 4:	crossSE(x,y);	break;
		default:	outtext("\n NO SUCH CASE IN CROSS FUNCTION FOUND");
	}
	setcolor(LIGHTGRAY);
}

void crossNS(int x,int y)
{
	const int l=120;
	for(int i=-3;i<3;i++)
		line(x+i,y-l,x+i,y+l);
}

void crossEW(int x,int y)
{
	const int l=120;
	for(int i=-3;i<3;i++)
		line(x-l,y+i,x+l,y+i);
}

void crossSE(int x,int y)
{
	const int l=120;
	for(int i=-3;i<3;i++)
		line(x-l+i,y-l,x+l+i,y+l);
}

void crossNE(int x,int y)
{
	const int l=120;
	for(int i=-3;i<3;i++)
		line(x+l+i,y-l,x-l+i,y+l);
}

void tictoc()
{
	const int maxx=getmaxx();

	int i,j,style[4]={70,72,180,182};
	char a[12]="TIC TAC TOE",b[2];

	cleardevice();

	settextstyle(5,0,3);
	outtextxy(30,30,"WELCOME TO");

	settextstyle(1,0,9);
	setcolor(WHITE);

	moveto(40,60);
	for(i=0;i<12;i++)
	{
		pause(15);

		b[0]=a[i];
		b[1]='\0';

		outtext(b);
	}

	for(i=0;i<maxx;i++)
	{
		for(j=0;j<4;j++)
		{
			moveto(0,style[j]);
			lineto(i,style[j]);
		}

		pause(10);
	}
	kbreset();

	settextstyle(5,0,3);
	outtextxy(250,185,"-BY TEAM TRIUMVIRATES");

	settextstyle(0,0,2);
	setcolor(LIGHTGRAY);
}

void welcome(int i)
{
	char dis[row][col]={"NEW GAME","OPTIONS","HELP","CREDITS","QUIT"};
	int opt;

	if(i==1)
	{
		cleardevice();
		heading(100,100,380,"TIC TAC TOE");

		setcolor(WHITE);
		settextstyle(5,0,3);
		outtextxy(250,145,"-BY TEAM TRIUMVIRATES");
		settextstyle(0,0,2);
		setcolor(LIGHTGRAY);
	}

	opt=display(280,260,dis);

	switch(opt)
	{
		case 0:   cleardisplay(280,260,dis);
				new_game(1);
				break;

		case 1:	options();
				break;

		case 2:	rules();
				break;

		case 3:	credits();
				break;

		case 4:	quit();
				break;
	}
}

void new_game(int i)
{
	int out;
	char dis[row][col]={"1 PLAYER(PLAYER VS COM)","2 PLAYER(PLAYER VS PLAYER)","BACK TO MAIN SCREEN"};

	if(i==1)
	{
		cleardevice();
		heading(100,100,380,"TIC TAC TOE");

		setcolor(WHITE);
		settextstyle(5,0,3);
		outtextxy(350,145,"-BY MITHUN GANESH");
		settextstyle(0,0,2);
		setcolor(LIGHTGRAY);
	}

	out=display(280,260,dis);

	switch(out)
	{
		case 0:
		case 1:   pvp();
				break;
		case 2:	welcome(1);
				break;
	}
}

void rules()
{
	const int l=150;
	cleardevice();
	heading(200,60,160,"HELP");

	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);

	outtextxy(0,0+l,"     Tic toc toe is a game of thinking. It is played between two players.");
	outtextxy(0,15+l,"Each player has a symbol either O or X. Each player makes a single move.");
	outtextxy(0,30+l,"The player first to make three symbols in horizontal,vertical or diagonal");
	outtextxy(0,45+l,"is the winner.");

	outtextxy(0,75+l,"    In NEW GAME you have two modes. In one you can play with computer. In");
	outtextxy(0,90+l,"In another you can play with computer. Overall you can use the cursor keys");
	outtextxy(0,105+l,"to navigate and enter or space key to accept.");

	outtextxy(0,135+l,"   You can check the keyboard settings in the OPTION. Please check the controls");
	outtextxy(0,150+l,"for the players when 2 PLAYER is selected.");

	settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
	outtextxy(250,400,"OK");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	getch();

	welcome(1);
}

void credits()
{
	cleardevice();
	heading(100,50,380,"TIC TAC TOE");
	heading(180,135,240,"CREDITS");

	setcolor(RED);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
	center(0,190,"PROGRAMMERS");
	center(0,320,"DEDICATION");
	center(0,430,"OK");

	setcolor(WHITE);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	center(0,220,"MITHUN GANESH");
	center(0,250,"PRATAP SURYA CHANDER");
	center(0,280,"ARVIND");

	center(0,350,"DEDICATED TO PROTEGEE");

	settextstyle(DEFAULT_FONT,HORIZ_DIR,4);

	getch();
	welcome(1);
}

void options()
{
	char text[5][6]={"UP","DOWN","LEFT","RIGHT","SPACE"};
	char text1[3][6][9]={
						{"ACTION","UP","DOWN","LEFT","RIGHT","SELECT"},
						{"PLAYER 1","W","S","A","D","SPACE"},
						{"PLAYER 2","8","5","4","6","+"}
					};
	char dis[row][col]={"PLAYER 1","PLAYER 2","BACK TO MAIN SCREEN"};
	int i,j,opt;

	cleardevice();
	heading(150,80,250,"OPTIONS");
	o(200,150);
	x(400,150);
	opt=display(300,250,dis);

	switch(opt)
	{
		case 0:	cleardevice();

				heading(0,90,650,"KEYBOARD CONTROLS");
				settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
				outtextxy(200,170,"1 PLAYER");

				settextstyle(DEFAULT_FONT,HORIZ_DIR,2);

				for(i=0;i<4;i++)
				{
					outtextxy(100,230+i*30,text[i]);
					outtextxy(400,230+i*30,text[i]);
				}

				outtextxy(100,230+i*30,"SELECT");
				outtextxy(400,230+i*30,"SPACE");

				settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
				outtextxy(250,430,"OK");
				settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
				getch();
				options();
				break;

		case 1:   cleardevice();
				heading(0,50,650,"KEYBOARD CONTROLS");
				settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
				outtextxy(200,110,"2 PLAYERS");

				settextstyle(DEFAULT_FONT,HORIZ_DIR,2);

				for(i=0;i<6;i++)
				{
					outtextxy(50,180+i*30,text1[0][i]);
					outtextxy(300,180+i*30,text1[1][i]);
					outtextxy(500,180+i*30,text1[2][i]);
				}

				settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
				outtextxy(250,430,"OK");
				settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
				getch();
				options();
				break;

		case 2:   welcome(1);
				break;
	}
}

void quit()
{

	const int x1=200,y1=200;
	int i,j;
	int pos[][2]=	{
					{x1-move,y1-move},
					{x1,y1},
					{x1+move,y1+move},
					{x1-move,y1+move},
					{x1+move,y1-move},
					{x1+move,y1},
					{x1,y1-move}
				};

	cleardevice();
	outtextxy(30,30," THANKS FOR RUNNING TIC TAC TOE.");

	pause(100);
	arena(x1,y1);

	for(i=0;i<7;i++)
	{
		if(i%2==0)
			o(pos[i][0],pos[i][1]);
		else
			x(pos[i][0],pos[i][1]);

		pause(500);
	}
	cross(x1,y1-move,2);

	box(x1-move,y1+2*move);
	o(x1-move,y1+2*move);
	outtextxy(x1,y1+2*move," WINS");
	pause(500);
}

void heading(int x,int y,int x1,char a[col])
{
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,7);
	setcolor(WHITE);
	outtextxy(x,y,a);

	for(int i=5;i<10;i=i+2)
		line(x,y+i,x+x1,y+i);

	setcolor(LIGHTGRAY);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
}

int display(int x,int y,char a[row][col])
{
	int opt;

	settextjustify(1,0);

	for(int no=0;a[no][0]!='\0';no++)
		outtextxy(x,y+no*40,a[no]);

	opt=getkey(x,y,no,a);

	settextjustify(0,0);

	return(opt);
}

int getkey(int x,int y,int no_opt,char words[row][col])
{
	const int UP=72,DOWN=80,LEFT=75,RIGHT=77,SPACE=32,ENTER=13;
	char a;
	int num=0,old;

	highlight(x,y,num,words);
	do
	{
		old=num;
		a=getch();

		if(a==0)
		{
			a=getch();

			if(a==UP)   //UP
			{
				if(num==0)
					num=no_opt-1;
				else
					num-=1;
			}
			else if(a==DOWN)
			{
				if(num==(no_opt-1))
					num=0;
				else
					num+=1;
			}
			nohighlight(x,y,old,words);
			highlight(x,y,num,words);
		}

	}while(a!=SPACE && a!=ENTER);
	return(num);
}

void highlight(int x,int y,int opt,char choice[row][col])
{
	setcolor(RED);
	outtextxy(x,y+opt*40,choice[opt]);
	setcolor(LIGHTGRAY);
}

void nohighlight(int x,int y,int opt,char choice[row][col])
{
	setcolor(LIGHTGRAY);
	outtextxy(x,y+opt*40,choice[opt]);
}

void center(int x,int y,char a[150])
{
	int maxx,width,midx;

	maxx=getmaxx();
	width=textwidth(a);

	midx=(maxx+x-width)/2;
	outtextxy(midx,y,a);
}

void pvp()
{
	const int l=35,m=85;
	int cell[3][3]={{0,0,0},{0,0,0},{0,0,0}};
	int x=300,y=250,j,k;

	char a;
	cleardevice();

	setcolor(WHITE);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);

	outtextxy(10,30,"PLAYER 1: ");
	outtextxy(10,60,"PLAYER 2: ");

	setcolor(BLUE);
	outtextxy(200,30,"X");

	setcolor(LIGHTGREEN);
	outtextxy(200,60,"O");

	arena(x,y);
	getch();
	welcome(1);
}

void key()
{
	const int l=85;
	char key[2][6]={"WSAD ","8546+"};
	int x=300,y=250,i,j,k;
	int cell[3][3]={{0,0,0},{0,0,0},{0,0,0}};

}