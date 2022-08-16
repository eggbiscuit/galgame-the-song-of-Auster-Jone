#pragma once
#include<iostream>
using namespace std;
#define MAXSTAR 200
#define WIDTH 1000
#define HEIGHT 760
struct star
{
	int x;
	int y;
	double step;
	int color;//烟色 


};

//初始化星星数组
void InitStar(int i);
void MoveStar(int i);
void MoveStarTest();




