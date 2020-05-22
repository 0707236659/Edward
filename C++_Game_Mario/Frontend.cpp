#include "graphics.h"
#include <windows.h>
#include <process.h>
#include <dos.h>

#include <iostream>
#include <stdlib.h>
#include "PointColor.h"
#include "Struct_Point.h"
#include <math.h>

#pragma comment(lib,"graphics.lib")
using namespace std;
# define M_PI   3.14159265358979323846 

void FullScreen(DWORD screenWidth, DWORD screenHeight);
void MainIntroduce(DWORD screenWidth, DWORD screenHeight);//1
void Instruction(DWORD screenWidth, DWORD screenHeight);
void MainMenu(DWORD screenWidth, DWORD screenHeight);//2
void LvOne(DWORD screenWidth, DWORD screenHeight);//3
void LvTwo(DWORD screenWidth, DWORD screenHeight);//4
void Victory(DWORD screenWidth, DWORD screenHeight);
void PlayGame(DWORD screenWidth, DWORD screenHeight);
void GameOver(DWORD screenWidth, DWORD screenHeight);
void Score(DWORD screenWidth, DWORD screenHeight);
void bricks(int num, int x, int y, DWORD screenWidth, DWORD screenHeight);
void ExitGame(DWORD screenWidth, DWORD screenHeight);
void lineDDA(int x1, int y1, int x2, int y2,int color);
//void Sound(int song);

int main()
{		
		DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
		DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
		
		FullScreen(screenWidth, screenHeight);
		MainIntroduce(screenWidth,  screenHeight);
		MainMenu(screenWidth,  screenHeight);
		Victory(screenWidth, screenHeight);
}

//Caculate funtions
void FullScreen(DWORD screenWidth, DWORD screenHeight)
{	
	cout << "Width :" << screenWidth << endl;//1920
	cout << "Height :" << screenHeight << endl;;//1080
	initwindow(screenWidth, screenHeight);
}
void scanLine(Point arrow[])
{
	int xmin, xmax, ymin, ymax, c, arr[30];
	xmin = xmax = arrow[0].x;
	ymin = ymax = arrow[0].y;

	for (int i = 0; i<7; i++)
	{
		if (xmin>arrow[i].x)
			xmin = arrow[i].x;

		if (xmax<arrow[i].x)
			xmax = arrow[i].x;

		if (ymin>arrow[i].y)
			ymin = arrow[i].y;

		if (ymax<arrow[i].y)
			ymax = arrow[i].y;
	}

	double y;
	y = ymin + 0.01;
	while (y <= ymax) //duyệt từ đỉnh cận ymin tới đỉnh ymax
	{
		int x, x1, x2, y1, y2, tg;
		c = 0;    //chỉ số của mảng phần tử
		for (int i = 0; i<7; i++)
		{ //xét trên tất cả các đỉnh
		  //xét 2 đỉnh liền kề nhau
			x1 = arrow[i].x;
			y1 = arrow[i].y;
			x2 = arrow[i + 1].x;
			y2 = arrow[i + 1].y;
			if (y2<y1) // y điểm đầu tiên phải nhỏ hơn y điểm liền kề
			{
				tg = x1; x1 = x2; x2 = tg;
				tg = y1; y1 = y2; y2 = tg;
			}

			if (y >= y1 && y <= y2)// toạ độ 2 đỉnh nằm trong khoãng y đang xét
			{
				if (y1 == y2)  // trường hợp đặc biệt ngang hàng thì bỏ không xét
					x = x1;
				else
				{
					x = ((y - y1)*(x2 - x1)) / (y2 - y1); //hệ số góc
					x += x1;
				}
				if (x <= xmax && x >= xmin)
					arr[c++] = x;   //cho phần tử c = x sau đó c++
			}
		}
		//với mỗi y tồn tại giao điểm x thì ta vẽ đường nối
		for (int i = 0; i<c; i += 2)
		{
			delay(0);
			line(arr[i], y, arr[i + 1], y);
		}
		y++;
	}
}
void lineDDA(int x1, int y1, int x2, int y2,int color)
{
	int Dx = x2 - x1, Dy = y2 - y1;
	float x_inc, y_inc;
	float step = max(abs(Dx), abs(Dy));
	x_inc = Dx / step;
	y_inc = Dy / step;
	float x = x1, y = y1;// Khoi tao cac gia tri ban dau
	int k = 1;
	while (k <= step) {
		k++;
		delay(5); // thoi gian tre khi ve 1 diem anh
		x += x_inc;
		y += y_inc;
		/*cout << " x = " << x << "\t y = " << y << endl;*/
		putpixel(round(x), round(y), color);
	}
}
void RotatePoint(Point point1, Point point2,int goc,int color)
{
	//point 2 la tam xoay
	//180*=pi radian=> n*=n*pi/180 (radian)
	
	float r = point1.x - point2.x; //khoảng cách giua 2 diem;

	float gocRadian = M_PI*goc / 180;

	int x=0;
	int y=0;
	x = point1.x - point2.x;
	y = point1.y - point2.y;
	Point point3;
	point3.x = ceil((x * cos(gocRadian) - y * sin(gocRadian)) + point2.x);
	point3.y = ceil((x * sin(gocRadian) + y * cos(gocRadian)) + point2.y);

	lineDDA(point2.x, point2.y, point3.x, point3.y,color);
}

//Object funtions
int arrow1()
{
	Point arrow1[10];
	{
		arrow1[0].x =1300 ;
		arrow1[0].y = 340;

		arrow1[1].x = arrow1[0].x+20;
		arrow1[1].y = arrow1[0].y-20;

		arrow1[2].x = arrow1[0].x + 20;
		arrow1[2].y = arrow1[0].y - 10;

		arrow1[3].x = arrow1[0].x + 50;
		arrow1[3].y = arrow1[0].y - 10;

		arrow1[4].x = arrow1[0].x + 50;
		arrow1[4].y = arrow1[0].y + 10;

		arrow1[5].x = arrow1[0].x + 20;
		arrow1[5].y = arrow1[0].y + 10;

		arrow1[6].x = arrow1[0].x + 20;
		arrow1[6].y = arrow1[0].y + 20;

		arrow1[7] = arrow1[0];
	}
	for (int i = 0; i < 7; i++)
	{
		delay(0);
		line(arrow1[i].x, arrow1[i].y, arrow1[i + 1].x, arrow1[i + 1].y);
	}
	scanLine(arrow1);
	return 300;
}
int arrow2()
{
	Point arrow2[10];
	{
		arrow2[0].x = 1300;
		arrow2[0].y = 440;

		arrow2[1].x = arrow2[0].x + 20;
		arrow2[1].y = arrow2[0].y - 20;

		arrow2[2].x = arrow2[0].x + 20;
		arrow2[2].y = arrow2[0].y - 10;

		arrow2[3].x = arrow2[0].x + 50;
		arrow2[3].y = arrow2[0].y - 10;

		arrow2[4].x = arrow2[0].x + 50;
		arrow2[4].y = arrow2[0].y + 10;

		arrow2[5].x = arrow2[0].x + 20;
		arrow2[5].y = arrow2[0].y + 10;

		arrow2[6].x = arrow2[0].x + 20;
		arrow2[6].y = arrow2[0].y + 20;

		arrow2[7] = arrow2[0];
	}
	for (int i = 0; i < 7; i++)
	{
		delay(0);
		line(arrow2[i].x, arrow2[i].y, arrow2[i + 1].x, arrow2[i + 1].y);
	}
	scanLine(arrow2);
	return 400;
}
int arrow3()
{
	Point arrow3[10];
	{
		arrow3[0].x = 1300;
		arrow3[0].y = 540;

		arrow3[1].x = arrow3[0].x + 20;
		arrow3[1].y = arrow3[0].y - 20;

		arrow3[2].x = arrow3[0].x + 20;
		arrow3[2].y = arrow3[0].y - 10;

		arrow3[3].x = arrow3[0].x + 50;
		arrow3[3].y = arrow3[0].y - 10;

		arrow3[4].x = arrow3[0].x + 50;
		arrow3[4].y = arrow3[0].y + 10;

		arrow3[5].x = arrow3[0].x + 20;
		arrow3[5].y = arrow3[0].y + 10;

		arrow3[6].x = arrow3[0].x + 20;
		arrow3[6].y = arrow3[0].y + 20;

		arrow3[7] = arrow3[0];
	}
	for (int i = 0; i < 7; i++)
	{
		delay(0);
		line(arrow3[i].x, arrow3[i].y, arrow3[i + 1].x, arrow3[i + 1].y);
	}
	scanLine(arrow3);
	return 500;
}
//Delete arrow 1 2 3
void ClearnArow(int position1)
{
	if (position1 == 300)
	{
		settextstyle(0, HORIZ_DIR, 20);
		setcolor(7);
		arrow1();
		outtextxy(200, 300, "1.PLAY GAME");

		setcolor(0);
		arrow2();
		arrow3();

		settextstyle(0, HORIZ_DIR, 20);
		setcolor(15);
		outtextxy(200, 400, "2.INSTRUCTIONS");
		outtextxy(200, 500, "3.EXIT!");
		getch();

	}
	if (position1 == 400)
	{
		setcolor(10);
		arrow2();
		settextstyle(0, HORIZ_DIR, 20);
		outtextxy(200, 400, "2.INSTRUCTIONS");

		setcolor(0);
		arrow1();
		arrow3();
		settextstyle(0, HORIZ_DIR, 20);
		setcolor(15);
		outtextxy(200, 300, "1.PLAY GAME");
		outtextxy(200, 500, "3.EXIT!");
		getch();
	}
	if (position1 == 500)
	{
		setcolor(14);
		arrow3();
		settextstyle(0, HORIZ_DIR, 20);
		outtextxy(200, 500, "3.EXIT!");

		setcolor(0);
		arrow2();
		arrow1();
		settextstyle(0, HORIZ_DIR, 20);
		setcolor(15);
		outtextxy(200, 300, "1.PLAY GAME");
		outtextxy(200, 400, "2.INSTRUCTIONS");
		getch();
	}

}
//Score board
void Score(DWORD screenWidth, DWORD screenHeight)
{
	setcolor(15);
	line(screenWidth-400, 0, screenWidth-20, 0);// ---      
	line(screenWidth - 400, 0, screenWidth - 400, 150);// |
	line(screenWidth - 400, 150, screenWidth-20, 150); //2---
	line(screenWidth-20, 0, screenWidth-20, 150);// 2 |

	//screenWidth-400, 0       diem1
	//screenWidth - 400, 150   diem2
	//screenWidth-20, 150	   diem 3
	//screenWidth-20, 0		   diem 4
	settextstyle(6, 0, 50);
	outtextxy(screenWidth-320, 10, "SCORE");

	for (int j=1;;j++)
	{
		int left = 10;
		int right = 130;
		int bottom = 390;
		for (int i = 1; i <=10 ;i++)
		{
			
			setcolor(15);
			line(screenWidth - 390, left,		screenWidth - 390, left +10);//left
			line(screenWidth - 390, left+20,	screenWidth - 390, left + 30);//left
			line(screenWidth - 390, left+40,	screenWidth - 390, left + 50);//left

			line( screenWidth - bottom, 140,		screenWidth - (bottom- 20),140);//bottom
			line(screenWidth - (bottom-30), 140,	screenWidth -( bottom - 50), 140);//bottom
			line(screenWidth - (bottom-60), 140,	screenWidth - (bottom - 80), 140);//bottom
			line(screenWidth - (bottom - 90), 140,	screenWidth - (bottom - 110), 140);//bottom
			

			line(screenWidth - 30, right,		 screenWidth - 30, right - 10);//right
			line(screenWidth - 30, right-20,	 screenWidth - 30, right - 30);//right
			line(screenWidth - 30, right-40,	 screenWidth - 30, right - 50);//right
			

			delay(200);

			setcolor(LIGHTBLUE);
			line(screenWidth - 390, left,		screenWidth - 390, left + 10);//left
			line(screenWidth - 390, left + 20,	screenWidth - 390, left + 30);//left
			line(screenWidth - 390, left + 40,  screenWidth - 390, left + 50);//left

			line(screenWidth - bottom, 140,			 screenWidth - (bottom - 20), 140);//bottom
			line(screenWidth - (bottom - 30), 140,	 screenWidth - (bottom - 50), 140);//bottom
			line(screenWidth - (bottom - 60), 140,	 screenWidth - (bottom - 80), 140);//bottom
			line(screenWidth - (bottom - 90), 140,	 screenWidth - (bottom - 110), 140);//bottom


			line(screenWidth - 30, right,		screenWidth - 30, right - 10);//right
			line(screenWidth - 30, right - 20,	screenWidth - 30, right - 30);//right
			line(screenWidth - 30, right - 40,	screenWidth - 30, right - 50);//right

			left += 10;
			right -= 10;
			bottom -= 28;
		}
		//turn back
		int left2 = 130;
		int right2 = 10;
		int bottom2 = 20;

		for (int i = 1; i <= 10; i++)
		{

			setcolor(15);
			line(screenWidth - 390, left2,       screenWidth - 390, left2 - 10);//left
			line(screenWidth - 390, left2 - 20,  screenWidth - 390, left2 - 30);//left
			line(screenWidth - 390, left2 - 40,  screenWidth - 390, left2 - 50);//left

			line(screenWidth - bottom2, 140,			screenWidth - (bottom2 + 20), 140);//bottom
			line(screenWidth - (bottom2 + 30), 140,		screenWidth - (bottom2 + 50), 140);//bottom
			line(screenWidth - (bottom2 + 60), 140,		screenWidth - (bottom2 + 80), 140);//bottom
			line(screenWidth - (bottom2 + 90), 140,		screenWidth - (bottom2 + 110), 140);//bottom


			line(screenWidth - 30, right2,			screenWidth - 30, right2 + 10);//right
			line(screenWidth - 30, right2 + 20,		screenWidth - 30, right2 + 30);//right
			line(screenWidth - 30, right2 + 40,		screenWidth - 30, right2 + 50);//right


			delay(200);

			setcolor(LIGHTBLUE);
			line(screenWidth - 390, left2,			screenWidth - 390, left2 - 10);//left
			line(screenWidth - 390, left2 - 20,		screenWidth - 390, left2 - 30);//left
			line(screenWidth - 390, left2 - 40,		screenWidth - 390, left2 - 50);//left

			line(screenWidth - bottom2, 140,		screenWidth - (bottom2 + 20), 140);//bottom
			line(screenWidth - (bottom2 + 30), 140, screenWidth - (bottom2 + 50), 140);//bottom
			line(screenWidth - (bottom2 + 60), 140, screenWidth - (bottom2 + 80), 140);//bottom
			line(screenWidth - (bottom2 + 90), 140, screenWidth - (bottom2 + 110), 140);//bottom


			line(screenWidth - 30, right2,			 screenWidth - 30, right2 + 10);//right
			line(screenWidth - 30, right2 + 20,		 screenWidth - 30, right2 + 30);//right
			line(screenWidth - 30, right2 + 40,		 screenWidth - 30, right2 + 50);//right

			left2 -= 10;
			right2 += 10;
			bottom2 += 28;
		}

	}

	//float r = p[1].x - p[0].x; //khoảng cách từ x2 tới x1;

	//float gocRadian = M_PI*goc / 180;

	//float x3 = p[0].x + r*cos(gocRadian);
	//float y3 = p[0].y + r*sin(gocRadian);
	//line(p[0].x, p[0].y, x3, y3);
}
//Draw bricks
void bricks(int num, int x, int y, DWORD screenWidth, DWORD screenHeight)
{
	int size = 20;
	setfillstyle(1, 14);
	setcolor(6);
	for (int i = 1; i <= num; i++)
	{
		rectangle(x - size-1, y - size-1, x + size+1, y + size+1);
		bar(x - size, y - size, x + size, y + size);
		x += 40;
	}
}
//Draw pipe
void Pipe(DWORD screenWidth, DWORD screenHeight,int Tam, int Width,int Height)
{
	//Tam la toa do trung diem cua day' duong ong.
	//Width la do rong
	//Height la do cao cua ong

	setfillstyle(SOLID_FILL, 10);


	//Ong thang dung
	bar(Tam - Width/2, screenHeight - (screenHeight * 1 / 5)-Height, Tam + Width/2, screenHeight - (screenHeight * 1 / 5));
	rectangle(Tam - Width/2, screenHeight - (screenHeight * 1 / 5)-Height, Tam + Width/2, screenHeight - (screenHeight * 1 / 5));
	setcolor(0);
	//Ong nganng 
	bar(Tam - Width / 2 - 5, screenHeight - (screenHeight * 1 / 5) - Height + 20, Tam + Width / 2 + 5, screenHeight - (screenHeight * 1 / 5) - Height);
	rectangle(Tam - Width / 2 - 5, screenHeight - (screenHeight * 1 / 5) - Height + 20, Tam + Width / 2 + 5, screenHeight - (screenHeight * 1 / 5) - Height);
}
//sound 
//1:Mucsic,  2:Jump  , 3:Victory,  4:Gameover, 5:Wrong
void Sound(int  sound, bool accept)
{
	if (accept == true)
	{//Nhac nen
		if (sound == 1)
		{
			sndPlaySoundA("Music.wav", SND_ASYNC);
		}
		else //jump
			if (sound == 2)
			{
				sndPlaySoundA("Jump.wav", SND_ASYNC);
			}
			else
				if (sound == 3)
				{
					sndPlaySoundA("Victory.wav", SND_ASYNC);
				}
				else
					if (sound == 4)
					{
						sndPlaySoundA("GameOver.wav", SND_ASYNC);
					}
					else
						if (sound == 5)
						{
							sndPlaySoundA("Wrong.wav", SND_ASYNC);
						}
	}

	if (accept == false)
	{//Nhac nen
		if (sound == 1)
		{
			!sndPlaySoundA("Music.wav", SND_ASYNC);
		}
		else //jump
			if (sound == 2)
			{
				!sndPlaySoundA("Jump.wav", SND_ASYNC);
			}
			else
				if (sound == 3)
				{
					!sndPlaySoundA("Victory.wav", SND_ASYNC);
				}
				else
					if (sound == 4)
					{
						!sndPlaySoundA("GameOver.wav", SND_ASYNC);
					}
					else
						if (sound == 5)
						{
							!sndPlaySoundA("Wrong.wav", SND_ASYNC);
						}

	}
}
//the first level in game
void LvOne(DWORD screenWidth, DWORD screenHeight)
{
	Sound(1, true);
	setfillstyle(SOLID_FILL, LIGHTBLUE);//cloud
	bar(0, 0,screenWidth,screenHeight*1/5);

	setfillstyle(1, 1);
	setcolor(1);
	//1st cloud
	fillellipse(150, 70, 50, 50);
	fillellipse(220, 70, 50, 50);
	fillellipse(290, 70, 50, 50);
	fillellipse(150, 120, 50, 50);
	fillellipse(220, 120, 50, 50);
	fillellipse(290, 120, 50, 50);

	//2nd cloud
	fillellipse(500, 100, 30, 50);
	fillellipse(550, 100, 50, 70);
	fillellipse(600, 100, 50, 70);
	fillellipse(640, 100, 30, 50);

	//3th cloud
	fillellipse(950, 100, 50, 60);
	fillellipse(1020, 100, 70, 80);
	fillellipse(1090, 100, 70, 80);
	fillellipse(1160, 100, 50, 60);

	//ballons 2
	//red
		setfillstyle(1, 4);
		setcolor(4);
		fillellipse(1300, 50, 20, 20);
		setcolor(0);
		line(1300, 70, 1300, 100);

	//green
		setfillstyle(1, 3);
		setcolor(3);
		fillellipse(1350, 20, 20, 20);
		setcolor(0);
		line(1350, 40, 1350, 100);

	//lightblue
		setfillstyle(1, 8);
		setcolor(8);
		fillellipse(1400, 70, 20, 20);
		setcolor(0);
		line(1400, 90, 1400, 130);

	//ballons 1
	//purpose
		setfillstyle(1, 5);
		setcolor(5);
		fillellipse(310, 70, 30, 30);
		setcolor(0);
		line(310, 100, 350, 130);

	//green
		setfillstyle(1, 11);
		setcolor(11);
		fillellipse(350, 70, 20, 20);
		setcolor(0);
		line(350, 90, 350, 130);

	//green
		setfillstyle(1, 2);
		setcolor(2);
		fillellipse(400, 50, 20, 30);
		setcolor(0);
		line(400, 80, 350, 130);

	//yellow
		setfillstyle(1, 14);
		setcolor(14);
		fillellipse(450, 90, 20, 30);
		setcolor(0);
		line(430, 90, 350, 130);

	//birds
	setcolor(0);
	//1
	line(700, 100, 720, 110);
	line( 720,110,740,100);
	//2
	line(750, 100, 770, 110);
	line(770, 110, 790, 100);
	//3
	line(800, 100, 820, 110);
	line(820, 110, 840, 100);
	//4
	line(730, 130, 750, 140);
	line(750, 140, 770, 130);
	//5
	line(780, 130, 800, 140);
	line(800, 140, 820, 130);


	//ground
	setfillstyle(SOLID_FILL, 7);
	bar(0, screenHeight-( screenHeight * 1 / 5), screenWidth, screenHeight);

	//Eviroment
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, screenHeight * 1 / 5, screenWidth, screenHeight - (screenHeight * 1 / 5));
	Pipe(screenWidth, screenHeight, 400, 200, 300);

	bricks(1, 100, 700, screenWidth, screenHeight);

	Score(screenWidth, screenHeight);
	getch();
}
//First last in game
void LvTwo(DWORD screenWidth, DWORD screenHeight)
{
	cleardevice();
}




//Main Funtions 
//Man Hinh Load #1
void MainIntroduce(DWORD screenWidth, DWORD screenHeight)
{
	FullScreen(screenWidth, screenHeight);
	settextstyle(0, HORIZ_DIR,20);
	Sound(3, true);
	for (int i = 0; i < 2; i++)
	{
		setcolor(i+13);
		delay(100);
		outtextxy(400, 400, "S");
		delay(100);
		outtextxy(500, 400, "U");
		delay(100);
		outtextxy(600, 400, "P");
		delay(100);
		outtextxy(700, 400, "E");
		delay(100);
		outtextxy(800, 400, "R");
		delay(100);
		outtextxy(900, 400, " ");
		delay(100);
		outtextxy(1000, 400, "M");
		delay(100);
		outtextxy(1100, 400, "A");
		delay(100);
		outtextxy(1200, 400, "R");
		delay(100);
		outtextxy(1300, 400, "I");
		delay(100);
		outtextxy(1400, 400, "O");
		delay(100);
	}
	for (int i = 0; i < 3; i++)
	{
		setcolor(15);
		outtextxy(400, 700, "Loanding ...........");
		delay(100);
		setcolor(0);
		outtextxy(400, 700, "Loanding ...........");
		delay(100);
	}
	setcolor(15);
	outtextxy(400, 700, "Loanding ...........");
	delay(100);
	delay(500);
}//Man hinh load
//Menu chon Options #2
void MainMenu(DWORD screenWidth, DWORD screenHeight)
{
		cleardevice();
		bool choose = true;
		int position = 300;
		settextstyle(0, HORIZ_DIR, 20);
		setcolor(15);
		outtextxy(500, 200, "MENU GAME MARIO");
		outtextxy(200, 300, "1.PLAY GAME");
		outtextxy(200, 400, "2.INSTRUCTIONS");
		outtextxy(200, 500, "3.EXIT!");

		settextstyle(2, HORIZ_DIR, 50);
		setcolor(10);
		outtextxy(30, 700, "USE THE ARROW ON THE KEYBOARD TO MOVE ");
		outtextxy(30, 800, "AND PRESS ESCAPE TO CHOOSE:");

		while (choose)
		{
			if (position < 300 || position > 500)
			{
				if (GetAsyncKeyState(VK_DOWN))
				{
					Sound(5, true);
					getch();
				}
				else if (GetAsyncKeyState(VK_UP))
				{
					Sound(5, true);
					getch();
				}
			}

			if (position >= 300 || position <= 500)
			{
				if (GetAsyncKeyState(VK_DOWN))
				{
					Sound(2, true);
					if (position <= 500)//hai
					{
						position += 100;
						getch();
					}

				}
				else
				if (GetAsyncKeyState(VK_UP))
				{
					Sound(2, true);
					if (position >= 300)//hai
					{
						position -= 100;
						getch();
					}
				}
			}

			//FIRST CHOOSE
			if (position == 300)
			{//xoa mui ten 23
				ClearnArow(arrow1());
			}

			//SECOND CHOOSE
			else if (position == 400)
			{//xoa mui ten 13
				ClearnArow(arrow2());
			}
			//LAST CHOOSE
			else if (position == 500)
			{//xoa mui ten 12
				ClearnArow(arrow3());
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				if (position == 300)//Play Game
				{
					cleardevice();
					LvOne(screenWidth, screenHeight);
					choose = false;
				}
				else if (position == 400)//Instruction
				{
					Instruction(screenWidth, screenHeight);
					getch();
					choose = false;
				}
				else if (position == 500)
				{
					cleardevice();
					ExitGame(screenWidth, screenHeight);
					choose = false;
				}
			}
		}
}
//Option play #3
void PlayGame(DWORD screenWidth, DWORD screenHeight)
{
	cleardevice();
	LvOne( screenWidth,  screenHeight);
}
//Option Huong Dan #3

void Instruction(DWORD screenWidth, DWORD screenHeight)
{
	int k = 0;
		do {
			cleardevice();
			setcolor(14);
			settextstyle(1, 0, 3);
			outtextxy(0, 400, "SU DUNG  MUI TEN QUA TRAI QUA PHAI DE DI CHUYEN ");
			outtextxy(int(screenWidth) - 400, int(screenHeight) - 200, "Enter to Skip ->>");
			k = getch();
		} while (k != 13);

		do {
			cleardevice();
			setcolor(14);
			settextstyle(1, 0, 3);
			outtextxy(0, 400, "SU DUNG MUI TEN DI LEN DE NHAY LEN ");
			outtextxy(0, 500, "SU DUNG MUI TEN DI XUONG  DE NHAY XUONG ");
			outtextxy(int(screenWidth) - 300, int(screenHeight) - 200, "Enter to return to Menu ");
			k = getch();
		} while (k != 13);
			MainMenu(screenWidth, screenHeight);
}
//Exit #3
void ExitGame(DWORD screenWidth, DWORD screenHeight)
{
	cleardevice();
	for (int i = 1; i <= 8; i++)
	{
		setcolor(i + 1);
		settextstyle(1, 0, 9);

		outtextxy(500, 400, "GOOD BYE!!");
		delay(200);

		setcolor(0);
		settextstyle(1, 0, 9);
		outtextxy(500, 400, "GOOD BYE!!");
	}
	setcolor(9);
	settextstyle(1, 0, 9);
	outtextxy(200, 400, "SEE YOU NEXT TIME!!");
	delay(2000);
	closegraph();

}
//The End funtions
void GameOver(DWORD screenWidth, DWORD screenHeight)
{
	cleardevice();
	for (int i = 1; i <= 8; i++)
	{
		setcolor(i + 1);
		settextstyle(1, 0, i);
		outtextxy(300, 400, "GAME OVER");
		delay(200);

		setcolor(0);
		settextstyle(1, 0, i - 1);
		outtextxy(300, 400, "GAME OVER");
	}
	setcolor(9);
	settextstyle(1, 0, 9);
	outtextxy(300, 400, "GAME OVER");
	getch();
}

void Victory(DWORD screenWidth, DWORD screenHeight)
{
	//Ban Phao Hoa
	cleardevice();
	int doDaiPhaoHoa = 100;//chieu cao tia ban 
	int corner = 135;
	Point FireWok[5];
	Point FireWokcenter[5];



	/*int n = rand() % (b – a + 1) + a;*/
	
	for (;;) {
		// diem anh random
		Pointcolor ran[200]; 
		for (int i = 0; i < 200; i++)
		{
			ran[i].x = 0 + rand() % (screenWidth - 0 + 1);
			ran[i].y = 0 + rand() % (screenHeight - 0 + 1);
			ran[i].color = 0 + rand() % (15 - 0 + 1);
		}

		for (int i = 0; i < 100; i++)
		{
			putpixel(ran[i].x, ran[i].y, ran[i].color);
		}
		//

		for (int i = 1; i <= 8; i++)
		{
			setcolor(i + 1);
			settextstyle(1, 0, 10);
			outtextxy(400, 400, "VICTORY");
			delay(200);

			setcolor(0);
			settextstyle(1, 0, 10);
			outtextxy(400, 400, "VICTORY");
		}

		setcolor(9);
		settextstyle(1, 0, 10);
		outtextxy(300, 500, "VICTORY");

		for (int i = 1; i <= 5; i++)
		{//random FireWork
			FireWok[i].x = rand() % (int(screenWidth) - 200 + 1) + 200;
			FireWok[i].y = rand() % (int(screenHeight) - doDaiPhaoHoa + 1) + doDaiPhaoHoa;
			FireWokcenter[i].x = FireWok[i].x;
			FireWokcenter[i].y = FireWok[i].y - doDaiPhaoHoa;
		}

		//Draw FireWork
		for (int i = 1; i <= 5; i++)
		{
			int color = 1;
			lineDDA(FireWok[i].x, FireWok[i].y, FireWokcenter[i].x, FireWokcenter[i].y, 15);
			for (int j = 1; j <= 4; j++)// ve tia ban 2
			{
				RotatePoint(FireWok[i], FireWokcenter[i], corner, color);
				RotatePoint(FireWok[i], FireWokcenter[i], corner += 45, color += 1);
				corner += 45;
				color++;
			}
		}
		
		//Delete FireWork
		for (int i = 1; i <= 5; i++)
		{
			lineDDA(FireWok[i].x, FireWok[i].y, FireWokcenter[i].x, FireWokcenter[i].y, 15);

			for (int j = 1; j <= 4; j++)// ve tia ban 2
			{
				RotatePoint(FireWok[i], FireWokcenter[i], corner, 0);
				RotatePoint(FireWok[i], FireWokcenter[i], corner += 45, 0);
				corner += 45;
			}
		}
		setcolor(0);
		settextstyle(1, 0, 10);
		outtextxy(300, 500, "VICTORY");
	}
	
}

