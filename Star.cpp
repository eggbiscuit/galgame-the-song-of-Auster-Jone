#include "Star.h"
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<iostream>
#include<stdlib.h>
#include<string>
#include<ctype.h>
#include<comdef.h>
#include<fstream>
#include<stdio.h>
#include<Windows.h>
#include"resource.h"
#include<mmsystem.h>
#include<cmath>
#pragma comment(lib,"winmm.lib")
star s[MAXSTAR];
void InitStar(int i)
{
	s[i].x = 0;
	s[i].y = rand() % HEIGHT;
	s[i].step = (rand() % 5000 / 1000.0 + 1);
	/*s[i].color = (int)(s[i].step * 255 / 6.0 + 0.5);*/
	s[i].color = RGB(255,255,255);//������ɫ
}
void MoveStar(int i)
{
	putpixel(s[i].x, s[i].y, 0);
	s[i].x += s[i].step;
	if (s[i].x > WIDTH)
	{
		InitStar(i);
	}
	//putpixel(s[i].x,s[i].y, s[i].color);//�滭�µ�����

	setfillcolor(WHITE);
	setlinecolor(WHITE);
	fillcircle(s[i].x, s[i].y, 1);
}

void MoveStarTest()
{
	srand(time(NULL));//���ˢ��

	for (int i = 0; i < MAXSTAR; i++)
	{
		
		FlushBatchDraw();
		InitStar(i);
		s[i].x = rand() % WIDTH;
	}

	// �����ǿգ���������˳�
	MOUSEMSG m1;
	while (!_kbhit()) {
		FlushBatchDraw();
		IMAGE imagebk;
		loadimage(&imagebk, "JPG", MAKEINTRESOURCE(IDR_JPG2), 1000, 760); // �¹���.jpg

		
		putimage(0, 0, &imagebk);

		settextstyle(20, 0, "����");
		outtextxy(0, 720, _T("�Ͽճ����˳�Ⱥ��ө��棬������ָ����ǰ���ұߵķ���"));
		outtextxy(0, 740, _T("���������������������"));
		for (int i = 0; i < MAXSTAR; i++) {
		
			MoveStar(i);
		}
		

	}
	
	}
