#pragma once
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>          //�û�ͨ�������̲����Ķ�Ӧ����������getch()����
#include<iostream>
#include<stdlib.h>
#include<string>
#include<ctype.h>

#include<fstream>
#include<stdio.h>
#include<Windows.h>
#include"resource.h"
#include<mmsystem.h>
#include<cmath>


using namespace std;
class Game
{
public:
	void FirstPage();
	void WeaponPage();
	void SaveIn();
	void ReadIn();
	void GamePage();
	void Attributeinit();
	void TxtRecord(int current, int txtNum);
	string readTxt(int n);
	string UTF8ToGB(const char* str);
	TCHAR* string2TCHAR(string m_csFileName);
	int music();
	void ModifyAtt();

	
	void button(int left, int top, int right, int bottom, string m_csFileName);
	char* calculateAtt(int n);
	

	


};


