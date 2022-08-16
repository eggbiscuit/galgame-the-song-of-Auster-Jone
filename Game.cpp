#include "Game.h"
#include"Star.h" 
#include"Investigator.h"

#pragma comment(lib,"winmm.lib")
#define SIZEX 1000
#define SIZEY 760
struct AttributeValue
{
	//本职技能点数:职业是教育x2 + 职业取向的属性x2，兴趣点值就是智力x2。这里设置的是起始值
	double str = 0;
	double con = 0;
	double siz = 0;
	double dex = 0;
	double app = 0;
	double inte = 0;
	double  pow = 0;
	double edu = 0;
	double luck = 0;
	
	//次要属性，在游戏中作roll点判断剧情走势
	double accouting = 5;
	double anthropology = 1;
	double appraise = 5;
	double archaeology = 1;
	//自定义技艺先空着
	double charm = 15;
	double climb = 20;
	//credit  rating and Cthulhu Nythos
	double disguise = 5;
	double dodge;//敏捷的一半
	double drive = 20;
	double eleRepair = 10;
	double talk = 5;
	double finghting = 25;
	//自定义格斗技能
	double firearms = 25;
	//自定义火器
	double firstAid = 30;
	double history = 5;
	double intimidate = 15;
	double jump = 20;
	double language = 0;//等同于教育数值
	//三项本职技能
	double law = 5;
	double libraryUse = 20;
	double listen = 20;
	double locksmith = 1;
	double mechRepair = 10;
	double medicine = 1;
	double naturalWorld = 10;//博物学
	double navigate = 10;
	double occult = 5; //神秘学

};
struct Investigator
{
	char name[20] = {};
	char player[20] = {};
	double era = 0;
	char occupation[20] = {};
	char gender[20] = {};
	char  recidence[20] = {};
	char hometown[20] = {};
	AttributeValue attributeValue;

};
struct Boss
{
	double hp = 600.0;
};

//全局变量区

//调查员，也就是第一人称的主角
Investigator Inv;
Invest Inv2;


int pageNum = 1;//程序中使用pageNum来控制页面
int txtNum = 1;//txtNum是文本文件的行数
int type = 1;//这里的type是页面的类型
int isView[10] = {};
int isViewAtt[18] = {};

//预制的武器，在investigator.h有详细的参数描述

Gun pistol("意大利伯莱塔92F手枪", 8, 50);//意大利伯莱塔92F手枪  三个参数分别是名称、子弹数和射程
Card random("惊奇套牌",13);//随机卡牌，点数越大伤害越高

//在最后的挑战中出现
Boss boss;

//枚举类型
enum pageType
{
	first = 1,
	game,
	attribute,
	weapon,
	end
};

//背景音乐的播放
int Game::music()
{
	PlaySound(LPTSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);


	return 0;
}

//中文字符在outtext的时候会出现乱码，原因是在txt文本读取的时候要将UTF8转成GB2312
//编码是ASCII码或者GB2312可能不会出错，但是读取的是UTF8时，就很容易造成乱码，
//所以我们每次读取时都最好将读取到的内容转成GB2312。
string Game::UTF8ToGB(const char* str)
{
	std::string result;
	WCHAR* strSrc;
	LPSTR szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

//这里将剩余的未分配点数的属性初始化
void Game::Attributeinit()
{
	Inv.attributeValue.language = Inv.attributeValue.edu;
	Inv.attributeValue.dodge = Inv.attributeValue.dex / 2;

}
//将string类型的文字转换成TCHAR类型以满足outtext函数的参数的要求
TCHAR* Game::string2TCHAR(string m_csFileName)
{
	TCHAR wc[MAX_PATH];
#ifdef UNICODE
	_stprintf_s(wc, MAX_PATH, _T("%S"), m_csFileName.c_str());//%S宽字符
#else
	_stprintf_s(wc, MAX_PATH, _T("%s"), m_csFileName.c_str());//%s单字符
#endif
	return wc;


}

//在程序中实现对人物属性的修改
void Game::ModifyAtt()
{
	/* 如果你选择了骰点法，
		那么请记住3个属性：体型、智力、教育。除了这3个的决定方式是2D6 + 6，
		其他属性的决定方式都是3D6。这个规则可以保证你的人物在必要的属性上点数不会过于低下*/

	Inv2.appInit((throw_1dx(6) + throw_1dx(6) + throw_1dx(6)) * 5.0);
	Inv2.conInit((throw_1dx(6) + throw_1dx(6) + throw_1dx(6)) * 5);
	Inv2.dexInit((throw_1dx(6) + throw_1dx(6) + throw_1dx(6)) * 5);
	Inv2.eduInit((throw_1dx(6) + throw_1dx(6) + 6) * 5);
	Inv2.inteInit((throw_1dx(6) + throw_1dx(6) + 6) * 5);
	Inv2.luckInit((throw_1dx(6) + throw_1dx(6) + throw_1dx(6)) * 5);
	Inv2.powInit((throw_1dx(6) + throw_1dx(6) + throw_1dx(6)) * 5);
	Inv2.sizInit((throw_1dx(6) + throw_1dx(6) + 6) * 5);
	Inv2.strInit((throw_1dx(6) + throw_1dx(6) + throw_1dx(6)) * 5);



	Attributeinit();




}
void Game::SaveIn()
{
	if (sizeof(Inv.name) != 0)
	{
		ofstream fp("character.txt", ios::out | ios::binary);
		if (!fp)
		{
			// 获取窗口句柄
			HWND hnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hnd, "TRPG");
			//弹出窗口，提示用户操作
			int is_ok = MessageBox(hnd, "存档文件未打开或尚未创建", "提示", MB_OKCANCEL);
		}
		Invest inv(Inv.name, Inv.player, Inv.era, Inv.occupation, Inv.gender, Inv.recidence, Inv.hometown, Inv2.getStr(), Inv2.getCon(), Inv2.getSiz(), Inv2.getDex(),
			Inv2.getApp(), Inv2.getInte(), Inv2.getPow(), Inv2.getEdu(), Inv2.getLuck());
		fp.write((const char*)(&inv), sizeof(Invest));

		fp.close();
		ofstream fpage("page.txt", ios::out);
		if (!fpage)
		{
			// 获取窗口句柄
			HWND hnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hnd, "TRPG");
			//弹出窗口，提示用户操作
			int is_ok = MessageBox(hnd, "存档文件未打开或尚未创建", "提示", MB_OKCANCEL);
		}
		else {
			HWND hnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hnd, "TRPG");
			//弹出窗口，提示用户操作
			int is_ok = MessageBox(hnd, "存档成功", "提示", MB_OKCANCEL);
		}

		fpage << pageNum;
		for (int i = 0; i < 18; i++)
		{
			fpage << " ";
			fpage << isViewAtt[i];
		}
		
		fpage.close();
	}
}
void Game::button(int left, int top, int right, int bottom, string m_csFileName)
{
	TCHAR wc[MAX_PATH];

#ifdef UNICODE
	_stprintf_s(wc, MAX_PATH, _T("%S"), m_csFileName.c_str());//%S宽字符
#else
	_stprintf_s(wc, MAX_PATH, _T("%s"), m_csFileName.c_str());//%s单字符
#endif

	//统一按钮的样式
	setfillcolor(BLACK);
	settextcolor(WHITE);
	fillrectangle(left, top, right, bottom);
	RECT r = { left,top,right,bottom };	//获取按钮的矩形区域
	settextcolor(WHITE);
	settextstyle(30, 0, "楷体");
	setbkmode(TRANSPARENT);
	drawtext(wc, &r, DT_CENTER | DT_NOPREFIX);//设置文字的输出格式：居中，自动换行，使用系统字体，使用系统字体自动计算，并且输出文字

}
char* Game::calculateAtt(int n)
{
	string p = to_string(n);

	char c1[100] = {};
	p.copy(c1, p.length());
	return c1;
}
string Game::readTxt(int n)
{
	fstream infile("./script.txt", ios::in);
	string str;
	if (!infile)
	{
		cerr << "not open";
	}
	//将文件流对象与文件连接起来 
//若失败,则输出错误消息,并终止程序运行 
	int temp = 1;
	string s;
	while (getline(infile, s))
	{
		str = UTF8ToGB(s.c_str()).c_str();
		if (temp == n)
			break;
		else {
			temp++;
		}

	};

	infile.close();   //关闭文件输入流 

	return str;


}
void Game::ReadIn()
{


	ifstream in("character.txt", ios::in | ios::binary);
	if (!in)
	{
		HWND hnd = GetHWnd();
		//设置窗口标题
		SetWindowText(hnd, "TRPG");
		//弹出窗口，提示用户操作
		int is_ok = MessageBox(hnd, "无法打开存档文件", "提示", MB_OKCANCEL);
	}
	in.read((char*)(&Inv2), sizeof(Invest));

	in.close();

	ifstream inpage("page.txt", ios::in);
	if (!inpage)
	{
		HWND hnd = GetHWnd();
		//设置窗口标题
		SetWindowText(hnd, "TRPG");
		//弹出窗口，提示用户操作
		int is_ok = MessageBox(hnd, "无法打开存档文件", "提示", MB_OKCANCEL);
	}
	else {
		HWND hnd = GetHWnd();
		//弹出窗口，提示用户操作
		int is_ok = MessageBox(hnd, "读取存档完成", "提示", MB_OKCANCEL);
	}


	inpage >> pageNum;
	for (int i = 0; i < 18; i++)
	{
		inpage >> isViewAtt[i];
	}
}
//游戏页面
void Game::FirstPage()
{
	cleardevice();
	for (int i = SIZEX; i != 0; i-=4)
	{
	
		IMAGE image;

		loadimage(&image, "PNG", MAKEINTRESOURCE(IDB_PNG14), SIZEX-i, SIZEY);//开头背景


		putimage(i, 0, &image);
		FlushBatchDraw();
		
	}
		setfillcolor(BLUE);
	
		//大标题
		setbkmode(TRANSPARENT);

		settextstyle(60, 0, _T("黑体"));
		outtextxy(150, 100, _T("奥斯特·琼之曲"));

		//三个选项的背景
		fillrectangle(230, 445, 560, 490);
		fillrectangle(230, 505, 560, 550);
		fillrectangle(230, 565, 560, 610);



		//三个选项的文字
		settextstyle(40, 0, _T("黑体"));

		//三个选项
		outtextxy(240, 450, _T("开始游戏"));
		outtextxy(240, 510, _T("读取存档"));
		outtextxy(240, 570, _T("退出"));
		MOUSEMSG m1;
		while (1)
		{
			m1 = GetMouseMsg();//获取鼠标操作
			if (m1.x >= 230 && m1.x <= 560 && m1.y >= 445 && m1.y <= 490)
			{
				setlinecolor(RED);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					type = 2;
					break;
				}
			}
			else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 505 && m1.y <= 550)//普通用户界面
			{
				setlinecolor(RED);
				rectangle(230, 505, 560, 550);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					ReadIn();
				}
			}
			else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 565 && m1.y <= 610)//退出
			{
				setlinecolor(RED);
				rectangle(230, 565, 560, 610);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{

					exit(0);
				}
			}
			else
			{
				setlinecolor(WHITE);
				rectangle(230, 445, 560, 490);
				rectangle(230, 505, 560, 550);
				rectangle(230, 565, 560, 610);

			}
			FlushBatchDraw();
		}
	
}
void Game::WeaponPage()
{
	FlushBatchDraw();


	setfillcolor(WHITE);
	fillroundrect(200, 500, 500, 700, 10, 10);

	IMAGE gun, card;

	if (pageNum >= 19)
	{
		loadimage(&card, "PNG", MAKEINTRESOURCE(IDB_PNG4), 90, 50);
		putimage(310, 510, &card);



	}
	if (pageNum >= 26)
	{
		loadimage(&gun, "JPEG", MAKEINTRESOURCE(IDR_JPEG1), 90, 50);
		putimage(210, 510, &gun);

	}
	MOUSEMSG m5;
	int temp[3] = {};
	static int isSkilled = 0;
	while (1)
	{
		m5 = GetMouseMsg();
		FlushBatchDraw();


		if (m5.x > 200 && m5.x < 500 && m5.y < 760 && m5.y>500) {

			//武器介绍

			if (pageNum >= 19)
			{

				setfillcolor(WHITE);
				setlinecolor(RED);
				fillroundrect(310, 600, 410, 700, 10, 10);

				std::string m_csFileName = random.getName() + "  " +"伤害" +to_string((int)random.getDamage())
					+"  牌数 " + to_string(random.getNumber2());
				RECT r = { 310,  600, 410, 700 };
				settextstyle(20, 0, "楷体");
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				drawtext(_T(m_csFileName.c_str()), &r, DT_INTERNAL | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
				m_csFileName = pistol.getBulletNum();

			}
			
			if (pageNum >= 26)
			{

				setfillcolor(WHITE);
				fillroundrect(210, 600, 310, 700, 10, 10);
				setlinecolor(RED);

				std::string m_csFileName = pistol.getName() + "子弹数: " + to_string(pistol.getBulletNum());
				RECT r = { 210,  600, 310, 700 };
				settextstyle(20, 0, "楷体");
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				drawtext(_T(m_csFileName.c_str()), &r, DT_INTERNAL | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
				m_csFileName = pistol.getBulletNum();

			}

			if (m5.x > 210 && m5.x < 300 && m5.y > 510 && m5.y < 560)
			{
				if (m5.uMsg == WM_LBUTTONDOWN)
				{
					//计算已经发射的次数
				

					if (temp[1] <= pistol.getBulletNum())
					{
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "开枪", "操作提示", MB_OKCANCEL);
						setfillcolor(WHITE);
						pistol.setBulletNum(pistol.getBulletNum() - 1);
						boss.hp -= pistol.getDamage() * 30;
						if (boss.hp <= 0)
						{
							pageNum = 62;
						}
					}
					else {
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "子弹数量不足", "操作提示", MB_OKCANCEL);
					}



					continue;

				}
			}

			if (m5.x > 310 && m5.x < 400 && m5.y > 510 && m5.y < 560)
			{
				//鼠标悬停在卡牌的区域
				if (m5.uMsg == WM_LBUTTONDOWN)
				{

					
					if (temp[1] <= random.getNumber2())

					{
						random.setNumber2(random.getNumber2() - 1);
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "掷出卡牌", "操作提示", MB_OKCANCEL);
						setfillcolor(WHITE);
						boss.hp -= random.getDamage();
						if (boss.hp <= 0) {
							pageNum = 61;

						}
					}
					else {
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "卡牌数量不足", "操作提示", MB_OKCANCEL);
					}
					continue;
				}
				else if (m5.uMsg == WM_RBUTTONDOWN && isSkilled == 0)
				{
					isSkilled++;
					temp[1]++;
					if (temp[1] <= random.getNumber2())

					{
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "发动技能，增益打击！", "操作提示", MB_OKCANCEL);
						setfillcolor(WHITE);
						Card op1("技能",13);

						boss.hp -= random.skillDamage(op1);
						if (boss.hp <= 0) {
							pageNum = 61;

						}
					}
					else {
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "卡牌数量不足", "操作提示", MB_OKCANCEL);
					}
					continue;
				}
			}
		}
			else {

				type = 2;
				pageNum--;
				break;
			}
			



			

		
		
	}
}
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{

	Sleep(1000);
	while (1)
	{
		
		if (pageNum == 25)
		{
			MoveStarTest();
			pageNum = 26;
		}
	}
	return 0L;

}
void Game::GamePage()
{
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc1, NULL, 0, NULL);
   
	music();
	
		initgraph(SIZEX, SIZEY);
		while (1)
		{

			//开始批量绘图，运行BeginBatchDraw后，所有的绘图都不再显示在屏幕上，而是在内存中进行
			/*理解：在默认情况下显示的内容就是默认的显示缓冲区的内容。
		     显示出现闪烁是因为缓冲区的内容不断清除和打印，正如cleardevice()这个过程
			那如果我们能让打印的过程不显示出来，只显示打印完后的显示缓冲区就可以解决闪烁问题。 
			当然，打印的过程既然不显示缓冲区的内容也总得有东西让控制台来显示
			那么我们就需要有两个缓冲区，打印一个的同时显示另一个，不断重复这个过程。*/
			
			BeginBatchDraw();

		
			switch (type)
			{
			/*	这里使用switch的多选择结构主要是因为我想呈现的页面有不同的种类，
				为方便代码的编排故用之*/
			case first:

			{    FirstPage();
			break;
			
			
			}
			case game:
              
			{
		     //背景区
			 //以下的变量会在每个条件中使用，主要用于加载图片和放置图片
				IMAGE bk, image1, image2, bk2, image4, image3;

				//场景1，在主角卧室中醒来
				if (pageNum < 5)
				{
					
					// 男主房间.jpg
					loadimage(&bk, "JPG", MAKEINTRESOURCE(IDR_JPG1), SIZEX, SIZEY);
					//载入人物的白底，以实现抠图的效果
					loadimage(&image1, "PNG", MAKEINTRESOURCE(IDB_PNG8), 300, 400);
					//载入人物的黑白图
					loadimage(&image2, "PNG", MAKEINTRESOURCE(IDB_PNG7));
					//box_horror_red
					loadimage(&image3,"PNG", MAKEINTRESOURCE(IDB_PNG6), 1000, 200);

					if (pageNum == 1&&isView[0]==0)
					{
						isView[0] = 1;
						for (int i = SIZEX; i != 0; i--){
	
		                    putimage(i, 0, &bk);
		                    FlushBatchDraw();
		
	                       }
						Sleep(1000);

						for (int i = SIZEX; i != 0; i--) {
							//先贴黑白图,由于人物是全白，所以整个背景都是白底
							putimage(
								800, 300, //显示的位置
								286, 500,//图片的大小，也可自行设置大小
								&image1, //选择需要贴的图
								0, 0,	//从该图片的起始位置开始显示
								SRCAND	//绘制出的像素颜色 = 屏幕颜色 & 图像颜色
							);
							//再贴彩黑图
							putimage(
								800, 300, 286, 500, &image2, 0, 0,	//与上相同
								SRCPAINT							//绘制出的像素颜色 = 屏幕颜色 | 图像颜色
							);
							FlushBatchDraw();
						}
					}
					
					cleardevice();
					
					putimage(0, 0, &bk);
					//先贴黑白图,由于人物是全白，所以整个背景都是白底
					putimage(
						800, 300, //显示的位置
						286, 500,//图片的大小，也可自行设置大小
						&image1, //选择需要贴的图
						0, 0,	//从该图片的起始位置开始显示
						SRCAND	//绘制出的像素颜色 = 屏幕颜色 & 图像颜色
					);
					//再贴彩黑图
					putimage(
						800, 300, 286, 500, &image2, 0, 0,	//与上相同
						SRCPAINT							//绘制出的像素颜色 = 屏幕颜色 | 图像颜色
					);

					//将红框放上去
					putimage(0, 560, &image3);
				}

				//场景2，经过黑色大桥
				else if (pageNum < 10) {
					//这一个part的实现细节与上一次的差不多

					IMAGE image5, image6;
					cleardevice();
					//背景载入,巷子里
					loadimage(&bk2, "JPG", MAKEINTRESOURCE(IDR_JPG12), 1000, 760);
					//载入蓝框
					loadimage(&image6, "PNG", MAKEINTRESOURCE(IDB_PNG9), 1000, 200);

					
					if (pageNum == 5&&isView[1] == 0)
					{
						isView[1] = 1;
						for (double i = 0, j = 0; i <= SIZEX || j <= SIZEY; i += 1, j += 0.76)
						{
							loadimage(&bk2, "JPG", MAKEINTRESOURCE(IDR_JPG12), i, j);
							putimage(SIZEX / 2 - i / 2, SIZEY / 2 - j/2, &bk2);
							FlushBatchDraw();
						}
						Sleep(1000);
						
						loadimage(&image5, "PNG", MAKEINTRESOURCE(IDB_PNG10));
						//先贴黑白图
						putimage(
							800, 300, //显示的位置
							286, 500,//图片的大小，也可自行设置大小
							&image1, //选择需要贴的图
							0, 0,	//从该图片的起始位置开始显示
							SRCAND	//绘制出的像素颜色 = 屏幕颜色 & 图像颜色
						);
						//再贴彩黑图，在这里实际上是黑白图，因为人物本身也是白色的
						putimage(
							800, 300, 286, 500, &image5, 0, 0,	//与上相同
							SRCPAINT							//绘制出的像素颜色 = 屏幕颜色 | 图像颜色
						);
						//按顺序放置图片，因为要将框放在人物前面以显示文字
						putimage(0, 560, &image6);
					}
					//放置背景
					putimage(0, 0, &bk2);
					loadimage(&image5, "PNG", MAKEINTRESOURCE(IDB_PNG10));
					//先贴黑白图
					putimage(
						800, 300, //显示的位置
						286, 500,//图片的大小，也可自行设置大小
						&image1, //选择需要贴的图
						0, 0,	//从该图片的起始位置开始显示
						SRCAND	//绘制出的像素颜色 = 屏幕颜色 & 图像颜色
					);
					//再贴彩黑图，在这里实际上是黑白图，因为人物本身也是白色的
					putimage(
						800, 300, 286, 500, &image5, 0, 0,	//与上相同
						SRCPAINT							//绘制出的像素颜色 = 屏幕颜色 | 图像颜色
					);
					//按顺序放置图片，因为要将框放在人物前面以显示文字
					Sleep(1000);
					putimage(0, 560, &image6);
					
					/*settextcolor(WHITE);
					settextstyle(30, 0, "楷体");
					outtextxy(700, 530, _T("看守者"));*/
					setlinecolor(WHITE);
					button(700, 530, 790, 560,"看守者");

				}

				//场景3，琼的房间，与琼会面
				else if (pageNum < 15)
				{

					IMAGE image5, image6, image7;
				
					//背景载入
					loadimage(&bk2, "PNG", MAKEINTRESOURCE(IDB_PNG11), SIZEX, SIZEY);
					//载入蓝对话框
					loadimage(&image6, "PNG", MAKEINTRESOURCE(IDB_PNG9), SIZEX, 200);
					
					if (pageNum == 10 && isView[2] == 0)
					{
						isView[2] == 1;
						for (double i = SIZEX, j = SIZEY; i >= 0; i -= 8, j -= 6)
						{
							cleardevice();
							loadimage(&bk2, "PNG", MAKEINTRESOURCE(IDB_PNG11), SIZEX-i, SIZEY-j);
							putimage(i, j, &bk2);
							FlushBatchDraw();
						}
						Sleep(1000);
						//先贴黑白图
						putimage(
							700, 200, //显示的位置
							286, 500,//图片的大小，也可自行设置大小
							&image7, //选择需要贴的图
							0, 0,	//从该图片的起始位置开始显示
							SRCAND	//绘制出的像素颜色 = 屏幕颜色 & 图像颜色
						);
						//再贴彩黑图
						putimage(
							700, 200, 286, 500, &image5, 0, 0,	//与上相同
							SRCPAINT							//绘制出的像素颜色 = 屏幕颜色 | 图像颜色
						);
						putimage(0, 560, &image6);
					}
					putimage(0, 0, &bk2);
					loadimage(&image7, "PNG", MAKEINTRESOURCE(IDB_PNG12), 300, 400);//琼黑
					loadimage(&image5, "PNG", MAKEINTRESOURCE(IDB_PNG13), 300, 400); //琼彩
					//先贴黑白图,即2.png
					putimage(
						700, 200, //显示的位置
						286, 500,//图片的大小，也可自行设置大小
						&image7, //选择需要贴的图
						0, 0,	//从该图片的起始位置开始显示
						SRCAND	//绘制出的像素颜色 = 屏幕颜色 & 图像颜色
					);
					//再贴彩黑图,即1.png
					putimage(
						700, 200, 286, 500, &image5, 0, 0,	//与上相同
						SRCPAINT							//绘制出的像素颜色 = 屏幕颜色 | 图像颜色
					);
					putimage(0, 560, &image6);
				}

				//场景4，偶遇大小姐
				else if (pageNum < 20)
				{
					cleardevice();
					IMAGE image5, image6, image7, image8;

					loadimage(&image5, "JPG", MAKEINTRESOURCE(IDR_JPG3), SIZEX, SIZEY);//大小姐背景
					putimage(0, 0, &image5);
					loadimage(&bk, "JPG", MAKEINTRESOURCE(IDR_JPG1), SIZEX, SIZEY);
					loadimage(&image8, "PNG", MAKEINTRESOURCE(IDB_PNG4), 100, 60);

					

					if (pageNum == 19)
					{
						for (int i = 0; i < 1000; i++)
						{
							FlushBatchDraw();

							putimage(0, 0, &image5);

							//圆形
							setfillcolor(RGB(172, 23, 23));
							/*setlinestyle(PS_DOT, 6);*/
							setlinecolor(RGB(172, 23, 23));
							fillcircle(SIZEX / 2, SIZEY / 2, SIZEX / 5);
							setfillcolor(RGB(148, 114, 33));
							setlinestyle(PS_DOT, 6);
							setlinecolor(BLACK);
							fillcircle(SIZEX / 2, SIZEY / 2, SIZEX / 10);

							setlinestyle(PS_SOLID);

							//君之妙笔，令鄙不及





							int x1 = 600, x2 = 700, y1 = 350, y2 = 410, r1 = (x1 + x2) / 2, r2 = (y1 + y2) / 2;

							
							setfillcolor(RGB(255, 255, 255));

							
							//旋转矩阵！线代知识
							POINT pts1[] = { {500 + 100 * cos(i) - sin(i) * 30,    cos(i) * 30 + 380 + 100 * sin(i)},{500 + 100 * cos(i) - (-30) * sin(i) , cos(i) * (-30) + 380 + 100 * sin(i)},
							 {500 + 200 * cos(i) - sin(i) * (-30),  380 + cos(i) * (-30) + 200 * sin(i)}, {500 + 200 * cos(i) - sin(i) * 30,    cos(i) * 30 + 380 + sin(i) * 200} };
							solidpolygon(pts1, 4);



							POINT pts2[] = { {500 - 100 * cos(i) - sin(i) * 30,    cos(i) * 30 + 380 - 100 * sin(i)},{500 - 100 * cos(i) - (-30) * sin(i) , cos(i) * (-30) + 380 - 100 * sin(i)},
						 {500 - 200 * cos(i) - sin(i) * (-30),  380 + cos(i) * (-30) - 200 * sin(i)}, {500 - 200 * cos(i) - sin(i) * 30,    cos(i) * 30 + 380 - sin(i) * 200} };
							solidpolygon(pts2, 4);



							line(SIZEX / 2, SIZEY / 2, SIZEX / 2 + SIZEX / 10 * cos(i + 3.14159265358579), SIZEY / 2 + SIZEY / 10 * sin(i + 3.14159265358579));
							line(SIZEX / 2, SIZEY / 2, SIZEX / 2 + SIZEX / 10 * cos(i + 3.14159265358579), SIZEY / 2 + SIZEY / 10 * sin(i + 3.14159265358579));
							line(SIZEX / 2, SIZEY / 2, SIZEX / 2 + SIZEX / 10 * cos(i), SIZEY / 2 + SIZEY / 10 * sin(i));
							line(SIZEX / 2, SIZEY / 2, SIZEX / 2 + SIZEX / 10 * cos(i), SIZEY / 2 + SIZEY / 10 * sin(i));





						}
						FlushBatchDraw();

						putimage(0, 0, &image5);

						//圆形
						setfillcolor(RGB(172, 23, 23));
						setlinecolor(RGB(172, 23, 23));
						fillcircle(SIZEX / 2, SIZEY / 2, SIZEX / 5);
						setfillcolor(RGB(148, 114, 33));
						setlinestyle(PS_DOT, 6);
						setlinecolor(BLACK);
						fillcircle(SIZEX / 2, SIZEY / 2, SIZEX / 10);


						setlinestyle(PS_SOLID);
						putimage(600, 350, &image8);
						putimage(300, 350, &image8);

						MOUSEMSG m;
						while (1)
						{
							m = GetMouseMsg();

							if (m.uMsg == WM_LBUTTONDOWN)
							{
								HWND hnd = GetHWnd();
								int is_ok = MessageBox(hnd, "惊奇卡牌现在已经加入了你的装备", "意外之喜", MB_OKCANCEL);
								break;
							}
							FlushBatchDraw();
						}
					}



				}

				// 月光下，奇怪的电波人
				else if (pageNum < 25)
				{
					IMAGE image5, image6;


					loadimage(&bk, "JPG", MAKEINTRESOURCE(IDR_JPG2), SIZEX, SIZEY); // 月光下.jpg
					loadimage(&image5, "PNG", MAKEINTRESOURCE(IDB_PNG8), 300 / (pageNum - 19), 400 / (pageNum - 19));
					loadimage(&image6, "PNG", MAKEINTRESOURCE(IDB_PNG2), 300 / (pageNum - 19), 400 / (pageNum - 19));






					putimage(0, 0, &bk);


					//先贴黑白图,即2.png
					putimage(
						500, 160, //显示的位置
						286 / (pageNum - 19), 500 / (pageNum - 19),//图片的大小，也可自行设置大小
						&image5, //选择需要贴的图
						0, 0,	//从该图片的起始位置开始显示
						SRCAND	//绘制出的像素颜色 = 屏幕颜色 & 图像颜色
					);
					//再贴彩黑图,即1.png
					putimage(
						500, 160, 286 / (pageNum - 19), 500 / (pageNum - 19), &image6, 0, 0,	//与上相同
						SRCPAINT							//绘制出的像素颜色 = 屏幕颜色 | 图像颜色
					);



					FlushBatchDraw();






				}

				
				//琼的蜡烛台
				else if (pageNum == 26)
				{
				
					IMAGE image5, image6, image7, image8;
					
					loadimage(&image5, "JPG", MAKEINTRESOURCE(IDR_JPG4), SIZEX, SIZEY);//蜡烛背景
					loadimage(&image6, "JPG", MAKEINTRESOURCE(IDR_JPG5), SIZEX, SIZEY);
					loadimage(&image8, "JPG", MAKEINTRESOURCE(IDR_JPG6), SIZEX, SIZEY);
					loadimage(&image7, "JPG", MAKEINTRESOURCE(IDR_JPG7), SIZEX, SIZEY);

					putimage(0, 0, &image5);
					Sleep(1000);
					FlushBatchDraw();
					putimage(0, 0, &image6);
					Sleep(1000);
					FlushBatchDraw();
					putimage(0, 0, &image7);
					Sleep(1000);
					FlushBatchDraw();
					putimage(0, 0, &image8);
					
					HWND hnd = GetHWnd();
					MessageBox(hnd, _T("你在蜡烛台上拾到了一把手枪"), "意外", MB_OKCANCEL);

				}

				//最后在琼的钢琴旁
				else
				{
					//终局之战
					IMAGE image5, image6, iamge7, image8;
					loadimage(&image5, "JPG", MAKEINTRESOURCE(IDR_JPG8), SIZEX, SIZEY);
					putimage(0, 0, &image5);





					settextstyle(30, 0, "黑体");
					settextcolor(LIGHTBLUE);


					static int hpsize[4] = { 0,0,boss.hp,30 };
					setfillcolor(BLACK);
					fillrectangle(hpsize[0], hpsize[1], hpsize[2], hpsize[3]);
					int bossHp[4] = { 0,0,boss.hp,30 };
					setfillcolor(WHITE);
					fillrectangle(bossHp[0], bossHp[1], bossHp[2], bossHp[3]);

					if (pageNum == 61)
					{
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "gun win", "操作提示", MB_OKCANCEL);
						IMAGE image;
						loadimage(&image, "JPG", MAKEINTRESOURCE(IDR_JPG10), SIZEX, SIZEY);
						putimage(0, 0, &image);

					};

					if (pageNum == 60)
					{
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "card win", "操作提示", MB_OKCANCEL);
						IMAGE image;
						loadimage(&image, "JPG", MAKEINTRESOURCE(IDR_JPG8), SIZEX, SIZEY);
						putimage(0, 0, &image);
					}



				}


				//页面中的必要组件
				string num = to_string(pageNum);
				char num1[10] = {};
				num.copy(num1, num.length());
				settextcolor(WHITE);
				settextstyle(30, 0, "黑体");
				outtextxy(0, 0, _T(num1));


				//按钮设置
				string temp = "属性";
				button(900, 730, 1000, 760, temp);
				string temp2 = "探索";
				button(750, 730, 850, 760, temp2);
				string temp3 = "存档";
				button(600, 730, 700, 760, temp3);
				string temp4 = "文字履历";
				button(450, 730, 550, 760, temp4);
				string temp5 = "装备";
				button(300, 730, 400, 760, temp5);


				settextstyle(30, 0, "楷体");


				settextcolor(WHITE);
				if (pageNum > 55)
				{
					if (pageNum != 60)
					{
						if (pageNum != 61)
						{
							pageNum = 55;
							settextcolor(LIGHTBLUE);
							outtextxy(0, 30, _T("现在可以在装备中选择你现有的武器攻击了"));
							settextcolor(WHITE);
						}
					}


				}




				//文档读取
				std::string m_csFileName = readTxt(pageNum++);
				RECT r = { 0,560,1000,760 };
				setbkmode(TRANSPARENT);
				//c_str()：生成一个const char* 指针，指向以空字符终止的数组。drawtext函数的成员类型的要求
				drawtext(_T(m_csFileName.c_str()), &r, DT_NOPREFIX | DT_WORDBREAK);//设置文字的输出格式：居中，自动换行，使用系统字体，使用系统字体自动计算，并且输出文字 | DT_INTERNAL DT_CENTER |



		//各种的鼠标操作逻辑
				MOUSEMSG m5;
				while (1)
				{

					m5 = GetMouseMsg();

					
					//结束跳转
					if (pageNum == 61 || pageNum == 62)
					{
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							//假如已经到对应结局的最后一页，则跳转到
							type = pageType::end;
							break;
						}
					}

					if (pageNum == 25)
					{
						continue;
				}

					//属性按钮
					if (m5.x > 900 && m5.x < 1000 && m5.y < 760 && m5.y>730)
					{
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							//在点到属性按钮时，跳转至属性界面
							type = pageType::attribute;

							break;


						}
					}

					//存档按钮
					else if (m5.x > 600 && m5.x < 700 && m5.y < 760 && m5.y>730)
					{
						if (m5.uMsg == WM_LBUTTONDOWN)
						{

							SaveIn();
						}

					}

					else if (m5.x > 450 && m5.x < 550 && m5.y < 760 && m5.y>730)
					{
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							TxtRecord(1, pageNum);

						}
					}

					//探索按钮
					else if (m5.x > 750 && m5.x < 850 && m5.y < 760 && m5.y>730)
					{
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							HWND hnd = GetHWnd();
							int is_ok = MessageBox(hnd, "请点击想要探索的事物，这会影响剧情的走势！", "操作提示", MB_OKCANCEL);
							settextcolor(WHITE);
							outtextxy(500, 500, "查阅");
						}

					}

					//进入装备界面
					else if (m5.x > 300 && m5.x < 400 && m5.y < 760 && m5.y>730)
					{

						type = 4;
						break;


					}
					//界面交互
					else if (m5.x > 300 && m5.x < 700 && m5.y < 600 && m5.y>300 && pageNum < 5)
					{
						//这里还要添加次数
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							int n = throw_1dx(100);
							HWND hnd = GetHWnd();
							SetWindowText(hnd, "TRPG");
							if (n < int(Inv2.getEdu()))
							{
								int is_ok = MessageBox(hnd, "你获知了关于兹曼巷的情报，神秘学的知识增加了", "结果", MB_OKCANCEL);
								Inv.attributeValue.occult += 5;
								isViewAtt[0] = 1;
							}
							else {
								int is_ok = MessageBox(hnd, "书中的内容似乎比较晦涩...", "结果", MB_OKCANCEL);
							}

						}

						
					}

					else if (m5.x > 300 && m5.x < 700 && m5.y < 600 && m5.y>300 && pageNum < 10&&pageNum>5)
					{
						//这里还要添加次数
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							int n = throw_1dx(100);
							HWND hnd = GetHWnd();
							SetWindowText(hnd, "TRPG");
							if (n < int(Inv2.getDex()))
							{
								int is_ok = MessageBox(hnd, "你通过伪装绕过了看守者", "结果", MB_OKCANCEL);
								Inv.attributeValue.disguise += 5;
								isViewAtt[1] = 1;
							}
							else {
								int is_ok = MessageBox(hnd, "你被看守者逮了个正着", "结果", MB_OKCANCEL);
							}

						}

					}

					else if (m5.x > 300 && m5.x < 700 && m5.y < 600 && m5.y>300 && pageNum < 15&&pageNum>=10)
					{
					//这里还要添加次数
					if (m5.uMsg == WM_LBUTTONDOWN)
					{
						int n = throw_1dx(100);
						HWND hnd = GetHWnd();
						SetWindowText(hnd, "TRPG");
						if (n < int(Inv2.getDex()))
						{
							int is_ok = MessageBox(hnd, "雷克向你透露了琼的消息", "结果", MB_OKCANCEL);
							Inv.attributeValue.listen += 5;
							isViewAtt[2] = 1;
						}
						else {
							int is_ok = MessageBox(hnd, "雷克一言不发，你无法获知十分有用的消息", "结果", MB_OKCANCEL);
						}

					}

					}

					//按其他任意键继续
					else if (m5.uMsg == WM_LBUTTONDOWN) {

						break;
					}

					/*执行后，任何绘图操作都将暂时不输出到绘图窗口上，
					直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出。*/
					FlushBatchDraw();
					

				}

				break;
			}

			case attribute:
			{
				IMAGE image4;
				loadimage(&image4, "./调查员属性.png", 1000, 760);
				pageNum--;
	
				/* 这里选择了骰点法，
	那么请记住3个属性：体型、智力、教育。除了这3个的决定方式是2D6 + 6，
	其他属性的决定方式都是3D6（也就是掷3次点数为1-6的骰子。
	这个规则可以保证你的人物在必要的属性上点数不会过于低下*/



				setbkmode(TRANSPARENT);

				double sum = Inv2.getApp() + Inv2.getCon() + Inv2.getDex() + Inv2.getEdu() + Inv2.getInte() + Inv2.getLuck() + Inv2.getPow() + Inv2.getSiz() + Inv2.getStr();
				settextstyle(70, 0, _T("楷体"));
				//设置字体颜色
				settextcolor(BLACK);
				FlushBatchDraw();

				cleardevice();
				putimage(0, 0, &image4);
				double a = Inv2.getStr();
				outtextxy(SIZEX / 9, SIZEY / 22, _T(to_string(int(sum)).c_str()));
				outtextxy(SIZEX / 7, SIZEY / 5, _T(to_string(int(Inv2.getStr())).c_str()));
				outtextxy(SIZEX / 7, SIZEY / 2, _T(to_string(int(Inv2.getCon())).c_str()));
				outtextxy(SIZEX / 7, SIZEY * 4 / 5, _T(to_string(int(Inv2.getSiz())).c_str()));
				outtextxy(SIZEX / 2.2, SIZEY / 5, _T(to_string(int(Inv2.getDex())).c_str()));
				outtextxy(SIZEX / 2.2, SIZEY / 2, _T(to_string(int(Inv2.getApp())).c_str()));
				outtextxy(SIZEX / 2.2, SIZEY * 4 / 5, _T(to_string(int(Inv2.getInte())).c_str()));
				outtextxy(SIZEX / 1.25, SIZEY / 5, _T(to_string(int(Inv2.getPow())).c_str()));
				outtextxy(SIZEX / 1.25, SIZEY / 2, _T(to_string(int(Inv2.getEdu())).c_str()));
				outtextxy(SIZEX / 1.25, SIZEY * 4 / 5, _T(to_string(int(Inv2.getLuck())).c_str()));

				if (isViewAtt[0] == 1)
				{
					settextcolor(GREEN);
					settextstyle(30, 0, "楷体");
					outtextxy(SIZEX / 1.25 + 100, SIZEY / 2 - 30, _T("神秘学"));
				}

				if (isViewAtt[0] == 2)
				{
					settextcolor(RED);
					settextstyle(30, 0, "楷体");
					outtextxy(SIZEX / 1.25 + 100, SIZEY / 2 + 60, _T("躺平学"));
				}
				if (isViewAtt[1] == 1)
				{
					settextcolor(GREEN);
					settextstyle(30, 0, "楷体");
					outtextxy(SIZEX / 2.2 + 100, SIZEY / 5 - 30, _T("伪装"));
				}
				if (isViewAtt[2] == 1)
				{
					settextcolor(GREEN);
					settextstyle(30, 0, "楷体");
					outtextxy(SIZEX / 2.2 + 100, SIZEY / 5 - 30, _T("聆听"));
				}


				

				setfillcolor(BLACK);
				button(6 * SIZEX / 7, 0, SIZEX, SIZEY / 14, "游戏界面");


				settextcolor(WHITE);
				MOUSEMSG m1;
				while (1)
				{
					m1 = GetMouseMsg();
					if (m1.x < SIZEX && m1.y>0 && m1.x > 6 * SIZEX / 7 && m1.y < SIZEY / 14)
					{
						if (m1.uMsg == WM_LBUTTONDOWN)
						{
							type = 2;
							break;
						}
					}
					FlushBatchDraw();
				}
				break;
			}

			case weapon:
			{
			//武器系统还可以加上对于武器的介绍
              WeaponPage();

				break;
			}

			case pageType::end:
			{

				//结束准备
				if (pageNum == 61)
				{
					FlushBatchDraw();
					IMAGE bk;
					loadimage(&bk, "JPG", MAKEINTRESOURCE(IDB_PNG5), SIZEX, SIZEY);//
					putimage(0, 0, &bk);



					FlushBatchDraw();
					cleardevice();
					for (int i = 0; i <= 255; i++)
					{
						FlushBatchDraw();
						cleardevice();
						settextstyle(i * 2, 0, "斜体");
						settextcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
						Sleep(400);
						RECT r = { 0,0,SIZEX,SIZEY };
						setbkmode(TRANSPARENT);
						drawtext(_T("THE END"), &r, DT_NOPREFIX | DT_WORDBREAK | DT_CENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);

					}



					exit(0);
				}

				else if (pageNum == 62)
				{
					IMAGE bk;
					FlushBatchDraw();

					loadimage(&bk, "JPG", MAKEINTRESOURCE(IDR_JPG10), SIZEX, SIZEY);
					putimage(0, 0, &bk);


					cleardevice();
					for (int i = 0; i <= 255; i++)
					{
						FlushBatchDraw();
						cleardevice();
						settextstyle(i * 2, 0, "斜体");
						settextcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
						Sleep(400);
						RECT r = { 0,0,SIZEX,SIZEY };
						setbkmode(TRANSPARENT);
						drawtext(_T("THE END"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}



					exit(0);
				}
				break;
			}

			}
		}
}
void Game::TxtRecord(int current, int TxtNum)
{
	RECT r = { 0,0,SIZEX,SIZEY };
	setbkmode(TRANSPARENT);
	string txt = "";
	for (int i = current; i < TxtNum; i++)
	{
		txt += readTxt(i);

	}
	settextstyle(15, 0, "黑体");
	drawtext(_T(txt.c_str()), &r, DT_NOPREFIX | DT_WORDBREAK | DT_NOCLIP);//设置文字的输出格式：居中，自动换行，使用系统字体，使用系统字体自动计算，并且输出文字 | DT_
	MOUSEMSG a;
	while (1)
	{
		a = GetMouseMsg();
		if (a.wheel)
		{
			cleardevice();
		}
		else
		{
			break;
		}
	}
}
