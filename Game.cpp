#include "Game.h"
#include"Star.h" 
#include"Investigator.h"

#pragma comment(lib,"winmm.lib")
#define SIZEX 1000
#define SIZEY 760
struct AttributeValue
{
	//��ְ���ܵ���:ְҵ�ǽ���x2 + ְҵȡ�������x2����Ȥ��ֵ��������x2���������õ�����ʼֵ
	double str = 0;
	double con = 0;
	double siz = 0;
	double dex = 0;
	double app = 0;
	double inte = 0;
	double  pow = 0;
	double edu = 0;
	double luck = 0;
	
	//��Ҫ���ԣ�����Ϸ����roll���жϾ�������
	double accouting = 5;
	double anthropology = 1;
	double appraise = 5;
	double archaeology = 1;
	//�Զ��弼���ȿ���
	double charm = 15;
	double climb = 20;
	//credit  rating and Cthulhu Nythos
	double disguise = 5;
	double dodge;//���ݵ�һ��
	double drive = 20;
	double eleRepair = 10;
	double talk = 5;
	double finghting = 25;
	//�Զ���񶷼���
	double firearms = 25;
	//�Զ������
	double firstAid = 30;
	double history = 5;
	double intimidate = 15;
	double jump = 20;
	double language = 0;//��ͬ�ڽ�����ֵ
	//���ְ����
	double law = 5;
	double libraryUse = 20;
	double listen = 20;
	double locksmith = 1;
	double mechRepair = 10;
	double medicine = 1;
	double naturalWorld = 10;//����ѧ
	double navigate = 10;
	double occult = 5; //����ѧ

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

//ȫ�ֱ�����

//����Ա��Ҳ���ǵ�һ�˳Ƶ�����
Investigator Inv;
Invest Inv2;


int pageNum = 1;//������ʹ��pageNum������ҳ��
int txtNum = 1;//txtNum���ı��ļ�������
int type = 1;//�����type��ҳ�������
int isView[10] = {};
int isViewAtt[18] = {};

//Ԥ�Ƶ���������investigator.h����ϸ�Ĳ�������

Gun pistol("�����������92F��ǹ", 8, 50);//�����������92F��ǹ  ���������ֱ������ơ��ӵ��������
Card random("��������",13);//������ƣ�����Խ���˺�Խ��

//��������ս�г���
Boss boss;

//ö������
enum pageType
{
	first = 1,
	game,
	attribute,
	weapon,
	end
};

//�������ֵĲ���
int Game::music()
{
	PlaySound(LPTSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);


	return 0;
}

//�����ַ���outtext��ʱ���������룬ԭ������txt�ı���ȡ��ʱ��Ҫ��UTF8ת��GB2312
//������ASCII�����GB2312���ܲ���������Ƕ�ȡ����UTF8ʱ���ͺ�����������룬
//��������ÿ�ζ�ȡʱ����ý���ȡ��������ת��GB2312��
string Game::UTF8ToGB(const char* str)
{
	std::string result;
	WCHAR* strSrc;
	LPSTR szRes;

	//�����ʱ�����Ĵ�С
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//�����ʱ�����Ĵ�С
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

//���ｫʣ���δ������������Գ�ʼ��
void Game::Attributeinit()
{
	Inv.attributeValue.language = Inv.attributeValue.edu;
	Inv.attributeValue.dodge = Inv.attributeValue.dex / 2;

}
//��string���͵�����ת����TCHAR����������outtext�����Ĳ�����Ҫ��
TCHAR* Game::string2TCHAR(string m_csFileName)
{
	TCHAR wc[MAX_PATH];
#ifdef UNICODE
	_stprintf_s(wc, MAX_PATH, _T("%S"), m_csFileName.c_str());//%S���ַ�
#else
	_stprintf_s(wc, MAX_PATH, _T("%s"), m_csFileName.c_str());//%s���ַ�
#endif
	return wc;


}

//�ڳ�����ʵ�ֶ��������Ե��޸�
void Game::ModifyAtt()
{
	/* �����ѡ�������㷨��
		��ô���ס3�����ԣ����͡�������������������3���ľ�����ʽ��2D6 + 6��
		�������Եľ�����ʽ����3D6�����������Ա�֤��������ڱ�Ҫ�������ϵ���������ڵ���*/

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
			// ��ȡ���ھ��
			HWND hnd = GetHWnd();
			//���ô��ڱ���
			SetWindowText(hnd, "TRPG");
			//�������ڣ���ʾ�û�����
			int is_ok = MessageBox(hnd, "�浵�ļ�δ�򿪻���δ����", "��ʾ", MB_OKCANCEL);
		}
		Invest inv(Inv.name, Inv.player, Inv.era, Inv.occupation, Inv.gender, Inv.recidence, Inv.hometown, Inv2.getStr(), Inv2.getCon(), Inv2.getSiz(), Inv2.getDex(),
			Inv2.getApp(), Inv2.getInte(), Inv2.getPow(), Inv2.getEdu(), Inv2.getLuck());
		fp.write((const char*)(&inv), sizeof(Invest));

		fp.close();
		ofstream fpage("page.txt", ios::out);
		if (!fpage)
		{
			// ��ȡ���ھ��
			HWND hnd = GetHWnd();
			//���ô��ڱ���
			SetWindowText(hnd, "TRPG");
			//�������ڣ���ʾ�û�����
			int is_ok = MessageBox(hnd, "�浵�ļ�δ�򿪻���δ����", "��ʾ", MB_OKCANCEL);
		}
		else {
			HWND hnd = GetHWnd();
			//���ô��ڱ���
			SetWindowText(hnd, "TRPG");
			//�������ڣ���ʾ�û�����
			int is_ok = MessageBox(hnd, "�浵�ɹ�", "��ʾ", MB_OKCANCEL);
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
	_stprintf_s(wc, MAX_PATH, _T("%S"), m_csFileName.c_str());//%S���ַ�
#else
	_stprintf_s(wc, MAX_PATH, _T("%s"), m_csFileName.c_str());//%s���ַ�
#endif

	//ͳһ��ť����ʽ
	setfillcolor(BLACK);
	settextcolor(WHITE);
	fillrectangle(left, top, right, bottom);
	RECT r = { left,top,right,bottom };	//��ȡ��ť�ľ�������
	settextcolor(WHITE);
	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT);
	drawtext(wc, &r, DT_CENTER | DT_NOPREFIX);//�������ֵ������ʽ�����У��Զ����У�ʹ��ϵͳ���壬ʹ��ϵͳ�����Զ����㣬�����������

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
	//���ļ����������ļ��������� 
//��ʧ��,�����������Ϣ,����ֹ�������� 
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

	infile.close();   //�ر��ļ������� 

	return str;


}
void Game::ReadIn()
{


	ifstream in("character.txt", ios::in | ios::binary);
	if (!in)
	{
		HWND hnd = GetHWnd();
		//���ô��ڱ���
		SetWindowText(hnd, "TRPG");
		//�������ڣ���ʾ�û�����
		int is_ok = MessageBox(hnd, "�޷��򿪴浵�ļ�", "��ʾ", MB_OKCANCEL);
	}
	in.read((char*)(&Inv2), sizeof(Invest));

	in.close();

	ifstream inpage("page.txt", ios::in);
	if (!inpage)
	{
		HWND hnd = GetHWnd();
		//���ô��ڱ���
		SetWindowText(hnd, "TRPG");
		//�������ڣ���ʾ�û�����
		int is_ok = MessageBox(hnd, "�޷��򿪴浵�ļ�", "��ʾ", MB_OKCANCEL);
	}
	else {
		HWND hnd = GetHWnd();
		//�������ڣ���ʾ�û�����
		int is_ok = MessageBox(hnd, "��ȡ�浵���", "��ʾ", MB_OKCANCEL);
	}


	inpage >> pageNum;
	for (int i = 0; i < 18; i++)
	{
		inpage >> isViewAtt[i];
	}
}
//��Ϸҳ��
void Game::FirstPage()
{
	cleardevice();
	for (int i = SIZEX; i != 0; i-=4)
	{
	
		IMAGE image;

		loadimage(&image, "PNG", MAKEINTRESOURCE(IDB_PNG14), SIZEX-i, SIZEY);//��ͷ����


		putimage(i, 0, &image);
		FlushBatchDraw();
		
	}
		setfillcolor(BLUE);
	
		//�����
		setbkmode(TRANSPARENT);

		settextstyle(60, 0, _T("����"));
		outtextxy(150, 100, _T("��˹�ء���֮��"));

		//����ѡ��ı���
		fillrectangle(230, 445, 560, 490);
		fillrectangle(230, 505, 560, 550);
		fillrectangle(230, 565, 560, 610);



		//����ѡ�������
		settextstyle(40, 0, _T("����"));

		//����ѡ��
		outtextxy(240, 450, _T("��ʼ��Ϸ"));
		outtextxy(240, 510, _T("��ȡ�浵"));
		outtextxy(240, 570, _T("�˳�"));
		MOUSEMSG m1;
		while (1)
		{
			m1 = GetMouseMsg();//��ȡ������
			if (m1.x >= 230 && m1.x <= 560 && m1.y >= 445 && m1.y <= 490)
			{
				setlinecolor(RED);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					type = 2;
					break;
				}
			}
			else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 505 && m1.y <= 550)//��ͨ�û�����
			{
				setlinecolor(RED);
				rectangle(230, 505, 560, 550);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					ReadIn();
				}
			}
			else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 565 && m1.y <= 610)//�˳�
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

			//��������

			if (pageNum >= 19)
			{

				setfillcolor(WHITE);
				setlinecolor(RED);
				fillroundrect(310, 600, 410, 700, 10, 10);

				std::string m_csFileName = random.getName() + "  " +"�˺�" +to_string((int)random.getDamage())
					+"  ���� " + to_string(random.getNumber2());
				RECT r = { 310,  600, 410, 700 };
				settextstyle(20, 0, "����");
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

				std::string m_csFileName = pistol.getName() + "�ӵ���: " + to_string(pistol.getBulletNum());
				RECT r = { 210,  600, 310, 700 };
				settextstyle(20, 0, "����");
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				drawtext(_T(m_csFileName.c_str()), &r, DT_INTERNAL | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
				m_csFileName = pistol.getBulletNum();

			}

			if (m5.x > 210 && m5.x < 300 && m5.y > 510 && m5.y < 560)
			{
				if (m5.uMsg == WM_LBUTTONDOWN)
				{
					//�����Ѿ�����Ĵ���
				

					if (temp[1] <= pistol.getBulletNum())
					{
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "��ǹ", "������ʾ", MB_OKCANCEL);
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
						int is_ok = MessageBox(hnd, "�ӵ���������", "������ʾ", MB_OKCANCEL);
					}



					continue;

				}
			}

			if (m5.x > 310 && m5.x < 400 && m5.y > 510 && m5.y < 560)
			{
				//�����ͣ�ڿ��Ƶ�����
				if (m5.uMsg == WM_LBUTTONDOWN)
				{

					
					if (temp[1] <= random.getNumber2())

					{
						random.setNumber2(random.getNumber2() - 1);
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "��������", "������ʾ", MB_OKCANCEL);
						setfillcolor(WHITE);
						boss.hp -= random.getDamage();
						if (boss.hp <= 0) {
							pageNum = 61;

						}
					}
					else {
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "������������", "������ʾ", MB_OKCANCEL);
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
						int is_ok = MessageBox(hnd, "�������ܣ���������", "������ʾ", MB_OKCANCEL);
						setfillcolor(WHITE);
						Card op1("����",13);

						boss.hp -= random.skillDamage(op1);
						if (boss.hp <= 0) {
							pageNum = 61;

						}
					}
					else {
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "������������", "������ʾ", MB_OKCANCEL);
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

			//��ʼ������ͼ������BeginBatchDraw�����еĻ�ͼ��������ʾ����Ļ�ϣ��������ڴ��н���
			/*��⣺��Ĭ���������ʾ�����ݾ���Ĭ�ϵ���ʾ�����������ݡ�
		     ��ʾ������˸����Ϊ�����������ݲ�������ʹ�ӡ������cleardevice()�������
			������������ô�ӡ�Ĺ��̲���ʾ������ֻ��ʾ��ӡ������ʾ�������Ϳ��Խ����˸���⡣ 
			��Ȼ����ӡ�Ĺ��̼�Ȼ����ʾ������������Ҳ�ܵ��ж����ÿ���̨����ʾ
			��ô���Ǿ���Ҫ����������������ӡһ����ͬʱ��ʾ��һ���������ظ�������̡�*/
			
			BeginBatchDraw();

		
			switch (type)
			{
			/*	����ʹ��switch�Ķ�ѡ��ṹ��Ҫ����Ϊ������ֵ�ҳ���в�ͬ�����࣬
				Ϊ�������ı��Ź���֮*/
			case first:

			{    FirstPage();
			break;
			
			
			}
			case game:
              
			{
		     //������
			 //���µı�������ÿ��������ʹ�ã���Ҫ���ڼ���ͼƬ�ͷ���ͼƬ
				IMAGE bk, image1, image2, bk2, image4, image3;

				//����1������������������
				if (pageNum < 5)
				{
					
					// ��������.jpg
					loadimage(&bk, "JPG", MAKEINTRESOURCE(IDR_JPG1), SIZEX, SIZEY);
					//��������İ׵ף���ʵ�ֿ�ͼ��Ч��
					loadimage(&image1, "PNG", MAKEINTRESOURCE(IDB_PNG8), 300, 400);
					//��������ĺڰ�ͼ
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
							//�����ڰ�ͼ,����������ȫ�ף����������������ǰ׵�
							putimage(
								800, 300, //��ʾ��λ��
								286, 500,//ͼƬ�Ĵ�С��Ҳ���������ô�С
								&image1, //ѡ����Ҫ����ͼ
								0, 0,	//�Ӹ�ͼƬ����ʼλ�ÿ�ʼ��ʾ
								SRCAND	//���Ƴ���������ɫ = ��Ļ��ɫ & ͼ����ɫ
							);
							//�����ʺ�ͼ
							putimage(
								800, 300, 286, 500, &image2, 0, 0,	//������ͬ
								SRCPAINT							//���Ƴ���������ɫ = ��Ļ��ɫ | ͼ����ɫ
							);
							FlushBatchDraw();
						}
					}
					
					cleardevice();
					
					putimage(0, 0, &bk);
					//�����ڰ�ͼ,����������ȫ�ף����������������ǰ׵�
					putimage(
						800, 300, //��ʾ��λ��
						286, 500,//ͼƬ�Ĵ�С��Ҳ���������ô�С
						&image1, //ѡ����Ҫ����ͼ
						0, 0,	//�Ӹ�ͼƬ����ʼλ�ÿ�ʼ��ʾ
						SRCAND	//���Ƴ���������ɫ = ��Ļ��ɫ & ͼ����ɫ
					);
					//�����ʺ�ͼ
					putimage(
						800, 300, 286, 500, &image2, 0, 0,	//������ͬ
						SRCPAINT							//���Ƴ���������ɫ = ��Ļ��ɫ | ͼ����ɫ
					);

					//��������ȥ
					putimage(0, 560, &image3);
				}

				//����2��������ɫ����
				else if (pageNum < 10) {
					//��һ��part��ʵ��ϸ������һ�εĲ��

					IMAGE image5, image6;
					cleardevice();
					//��������,������
					loadimage(&bk2, "JPG", MAKEINTRESOURCE(IDR_JPG12), 1000, 760);
					//��������
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
						//�����ڰ�ͼ
						putimage(
							800, 300, //��ʾ��λ��
							286, 500,//ͼƬ�Ĵ�С��Ҳ���������ô�С
							&image1, //ѡ����Ҫ����ͼ
							0, 0,	//�Ӹ�ͼƬ����ʼλ�ÿ�ʼ��ʾ
							SRCAND	//���Ƴ���������ɫ = ��Ļ��ɫ & ͼ����ɫ
						);
						//�����ʺ�ͼ��������ʵ�����Ǻڰ�ͼ����Ϊ���ﱾ��Ҳ�ǰ�ɫ��
						putimage(
							800, 300, 286, 500, &image5, 0, 0,	//������ͬ
							SRCPAINT							//���Ƴ���������ɫ = ��Ļ��ɫ | ͼ����ɫ
						);
						//��˳�����ͼƬ����ΪҪ�����������ǰ������ʾ����
						putimage(0, 560, &image6);
					}
					//���ñ���
					putimage(0, 0, &bk2);
					loadimage(&image5, "PNG", MAKEINTRESOURCE(IDB_PNG10));
					//�����ڰ�ͼ
					putimage(
						800, 300, //��ʾ��λ��
						286, 500,//ͼƬ�Ĵ�С��Ҳ���������ô�С
						&image1, //ѡ����Ҫ����ͼ
						0, 0,	//�Ӹ�ͼƬ����ʼλ�ÿ�ʼ��ʾ
						SRCAND	//���Ƴ���������ɫ = ��Ļ��ɫ & ͼ����ɫ
					);
					//�����ʺ�ͼ��������ʵ�����Ǻڰ�ͼ����Ϊ���ﱾ��Ҳ�ǰ�ɫ��
					putimage(
						800, 300, 286, 500, &image5, 0, 0,	//������ͬ
						SRCPAINT							//���Ƴ���������ɫ = ��Ļ��ɫ | ͼ����ɫ
					);
					//��˳�����ͼƬ����ΪҪ�����������ǰ������ʾ����
					Sleep(1000);
					putimage(0, 560, &image6);
					
					/*settextcolor(WHITE);
					settextstyle(30, 0, "����");
					outtextxy(700, 530, _T("������"));*/
					setlinecolor(WHITE);
					button(700, 530, 790, 560,"������");

				}

				//����3����ķ��䣬�������
				else if (pageNum < 15)
				{

					IMAGE image5, image6, image7;
				
					//��������
					loadimage(&bk2, "PNG", MAKEINTRESOURCE(IDB_PNG11), SIZEX, SIZEY);
					//�������Ի���
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
						//�����ڰ�ͼ
						putimage(
							700, 200, //��ʾ��λ��
							286, 500,//ͼƬ�Ĵ�С��Ҳ���������ô�С
							&image7, //ѡ����Ҫ����ͼ
							0, 0,	//�Ӹ�ͼƬ����ʼλ�ÿ�ʼ��ʾ
							SRCAND	//���Ƴ���������ɫ = ��Ļ��ɫ & ͼ����ɫ
						);
						//�����ʺ�ͼ
						putimage(
							700, 200, 286, 500, &image5, 0, 0,	//������ͬ
							SRCPAINT							//���Ƴ���������ɫ = ��Ļ��ɫ | ͼ����ɫ
						);
						putimage(0, 560, &image6);
					}
					putimage(0, 0, &bk2);
					loadimage(&image7, "PNG", MAKEINTRESOURCE(IDB_PNG12), 300, 400);//���
					loadimage(&image5, "PNG", MAKEINTRESOURCE(IDB_PNG13), 300, 400); //���
					//�����ڰ�ͼ,��2.png
					putimage(
						700, 200, //��ʾ��λ��
						286, 500,//ͼƬ�Ĵ�С��Ҳ���������ô�С
						&image7, //ѡ����Ҫ����ͼ
						0, 0,	//�Ӹ�ͼƬ����ʼλ�ÿ�ʼ��ʾ
						SRCAND	//���Ƴ���������ɫ = ��Ļ��ɫ & ͼ����ɫ
					);
					//�����ʺ�ͼ,��1.png
					putimage(
						700, 200, 286, 500, &image5, 0, 0,	//������ͬ
						SRCPAINT							//���Ƴ���������ɫ = ��Ļ��ɫ | ͼ����ɫ
					);
					putimage(0, 560, &image6);
				}

				//����4��ż����С��
				else if (pageNum < 20)
				{
					cleardevice();
					IMAGE image5, image6, image7, image8;

					loadimage(&image5, "JPG", MAKEINTRESOURCE(IDR_JPG3), SIZEX, SIZEY);//��С�㱳��
					putimage(0, 0, &image5);
					loadimage(&bk, "JPG", MAKEINTRESOURCE(IDR_JPG1), SIZEX, SIZEY);
					loadimage(&image8, "PNG", MAKEINTRESOURCE(IDB_PNG4), 100, 60);

					

					if (pageNum == 19)
					{
						for (int i = 0; i < 1000; i++)
						{
							FlushBatchDraw();

							putimage(0, 0, &image5);

							//Բ��
							setfillcolor(RGB(172, 23, 23));
							/*setlinestyle(PS_DOT, 6);*/
							setlinecolor(RGB(172, 23, 23));
							fillcircle(SIZEX / 2, SIZEY / 2, SIZEX / 5);
							setfillcolor(RGB(148, 114, 33));
							setlinestyle(PS_DOT, 6);
							setlinecolor(BLACK);
							fillcircle(SIZEX / 2, SIZEY / 2, SIZEX / 10);

							setlinestyle(PS_SOLID);

							//��֮��ʣ���ɲ���





							int x1 = 600, x2 = 700, y1 = 350, y2 = 410, r1 = (x1 + x2) / 2, r2 = (y1 + y2) / 2;

							
							setfillcolor(RGB(255, 255, 255));

							
							//��ת�����ߴ�֪ʶ
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

						//Բ��
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
								int is_ok = MessageBox(hnd, "���濨�������Ѿ����������װ��", "����֮ϲ", MB_OKCANCEL);
								break;
							}
							FlushBatchDraw();
						}
					}



				}

				// �¹��£���ֵĵ粨��
				else if (pageNum < 25)
				{
					IMAGE image5, image6;


					loadimage(&bk, "JPG", MAKEINTRESOURCE(IDR_JPG2), SIZEX, SIZEY); // �¹���.jpg
					loadimage(&image5, "PNG", MAKEINTRESOURCE(IDB_PNG8), 300 / (pageNum - 19), 400 / (pageNum - 19));
					loadimage(&image6, "PNG", MAKEINTRESOURCE(IDB_PNG2), 300 / (pageNum - 19), 400 / (pageNum - 19));






					putimage(0, 0, &bk);


					//�����ڰ�ͼ,��2.png
					putimage(
						500, 160, //��ʾ��λ��
						286 / (pageNum - 19), 500 / (pageNum - 19),//ͼƬ�Ĵ�С��Ҳ���������ô�С
						&image5, //ѡ����Ҫ����ͼ
						0, 0,	//�Ӹ�ͼƬ����ʼλ�ÿ�ʼ��ʾ
						SRCAND	//���Ƴ���������ɫ = ��Ļ��ɫ & ͼ����ɫ
					);
					//�����ʺ�ͼ,��1.png
					putimage(
						500, 160, 286 / (pageNum - 19), 500 / (pageNum - 19), &image6, 0, 0,	//������ͬ
						SRCPAINT							//���Ƴ���������ɫ = ��Ļ��ɫ | ͼ����ɫ
					);



					FlushBatchDraw();






				}

				
				//�������̨
				else if (pageNum == 26)
				{
				
					IMAGE image5, image6, image7, image8;
					
					loadimage(&image5, "JPG", MAKEINTRESOURCE(IDR_JPG4), SIZEX, SIZEY);//���򱳾�
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
					MessageBox(hnd, _T("��������̨��ʰ����һ����ǹ"), "����", MB_OKCANCEL);

				}

				//�������ĸ�����
				else
				{
					//�վ�֮ս
					IMAGE image5, image6, iamge7, image8;
					loadimage(&image5, "JPG", MAKEINTRESOURCE(IDR_JPG8), SIZEX, SIZEY);
					putimage(0, 0, &image5);





					settextstyle(30, 0, "����");
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
						int is_ok = MessageBox(hnd, "gun win", "������ʾ", MB_OKCANCEL);
						IMAGE image;
						loadimage(&image, "JPG", MAKEINTRESOURCE(IDR_JPG10), SIZEX, SIZEY);
						putimage(0, 0, &image);

					};

					if (pageNum == 60)
					{
						HWND hnd = GetHWnd();
						int is_ok = MessageBox(hnd, "card win", "������ʾ", MB_OKCANCEL);
						IMAGE image;
						loadimage(&image, "JPG", MAKEINTRESOURCE(IDR_JPG8), SIZEX, SIZEY);
						putimage(0, 0, &image);
					}



				}


				//ҳ���еı�Ҫ���
				string num = to_string(pageNum);
				char num1[10] = {};
				num.copy(num1, num.length());
				settextcolor(WHITE);
				settextstyle(30, 0, "����");
				outtextxy(0, 0, _T(num1));


				//��ť����
				string temp = "����";
				button(900, 730, 1000, 760, temp);
				string temp2 = "̽��";
				button(750, 730, 850, 760, temp2);
				string temp3 = "�浵";
				button(600, 730, 700, 760, temp3);
				string temp4 = "��������";
				button(450, 730, 550, 760, temp4);
				string temp5 = "װ��";
				button(300, 730, 400, 760, temp5);


				settextstyle(30, 0, "����");


				settextcolor(WHITE);
				if (pageNum > 55)
				{
					if (pageNum != 60)
					{
						if (pageNum != 61)
						{
							pageNum = 55;
							settextcolor(LIGHTBLUE);
							outtextxy(0, 30, _T("���ڿ�����װ����ѡ�������е�����������"));
							settextcolor(WHITE);
						}
					}


				}




				//�ĵ���ȡ
				std::string m_csFileName = readTxt(pageNum++);
				RECT r = { 0,560,1000,760 };
				setbkmode(TRANSPARENT);
				//c_str()������һ��const char* ָ�룬ָ���Կ��ַ���ֹ�����顣drawtext�����ĳ�Ա���͵�Ҫ��
				drawtext(_T(m_csFileName.c_str()), &r, DT_NOPREFIX | DT_WORDBREAK);//�������ֵ������ʽ�����У��Զ����У�ʹ��ϵͳ���壬ʹ��ϵͳ�����Զ����㣬����������� | DT_INTERNAL DT_CENTER |



		//���ֵ��������߼�
				MOUSEMSG m5;
				while (1)
				{

					m5 = GetMouseMsg();

					
					//������ת
					if (pageNum == 61 || pageNum == 62)
					{
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							//�����Ѿ�����Ӧ��ֵ����һҳ������ת��
							type = pageType::end;
							break;
						}
					}

					if (pageNum == 25)
					{
						continue;
				}

					//���԰�ť
					if (m5.x > 900 && m5.x < 1000 && m5.y < 760 && m5.y>730)
					{
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							//�ڵ㵽���԰�ťʱ����ת�����Խ���
							type = pageType::attribute;

							break;


						}
					}

					//�浵��ť
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

					//̽����ť
					else if (m5.x > 750 && m5.x < 850 && m5.y < 760 && m5.y>730)
					{
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							HWND hnd = GetHWnd();
							int is_ok = MessageBox(hnd, "������Ҫ̽����������Ӱ���������ƣ�", "������ʾ", MB_OKCANCEL);
							settextcolor(WHITE);
							outtextxy(500, 500, "����");
						}

					}

					//����װ������
					else if (m5.x > 300 && m5.x < 400 && m5.y < 760 && m5.y>730)
					{

						type = 4;
						break;


					}
					//���潻��
					else if (m5.x > 300 && m5.x < 700 && m5.y < 600 && m5.y>300 && pageNum < 5)
					{
						//���ﻹҪ��Ӵ���
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							int n = throw_1dx(100);
							HWND hnd = GetHWnd();
							SetWindowText(hnd, "TRPG");
							if (n < int(Inv2.getEdu()))
							{
								int is_ok = MessageBox(hnd, "���֪�˹�����������鱨������ѧ��֪ʶ������", "���", MB_OKCANCEL);
								Inv.attributeValue.occult += 5;
								isViewAtt[0] = 1;
							}
							else {
								int is_ok = MessageBox(hnd, "���е������ƺ��Ƚϻ�ɬ...", "���", MB_OKCANCEL);
							}

						}

						
					}

					else if (m5.x > 300 && m5.x < 700 && m5.y < 600 && m5.y>300 && pageNum < 10&&pageNum>5)
					{
						//���ﻹҪ��Ӵ���
						if (m5.uMsg == WM_LBUTTONDOWN)
						{
							int n = throw_1dx(100);
							HWND hnd = GetHWnd();
							SetWindowText(hnd, "TRPG");
							if (n < int(Inv2.getDex()))
							{
								int is_ok = MessageBox(hnd, "��ͨ��αװ�ƹ��˿�����", "���", MB_OKCANCEL);
								Inv.attributeValue.disguise += 5;
								isViewAtt[1] = 1;
							}
							else {
								int is_ok = MessageBox(hnd, "�㱻�����ߴ��˸�����", "���", MB_OKCANCEL);
							}

						}

					}

					else if (m5.x > 300 && m5.x < 700 && m5.y < 600 && m5.y>300 && pageNum < 15&&pageNum>=10)
					{
					//���ﻹҪ��Ӵ���
					if (m5.uMsg == WM_LBUTTONDOWN)
					{
						int n = throw_1dx(100);
						HWND hnd = GetHWnd();
						SetWindowText(hnd, "TRPG");
						if (n < int(Inv2.getDex()))
						{
							int is_ok = MessageBox(hnd, "�׿�����͸¶�������Ϣ", "���", MB_OKCANCEL);
							Inv.attributeValue.listen += 5;
							isViewAtt[2] = 1;
						}
						else {
							int is_ok = MessageBox(hnd, "�׿�һ�Բ��������޷���֪ʮ�����õ���Ϣ", "���", MB_OKCANCEL);
						}

					}

					}

					//���������������
					else if (m5.uMsg == WM_LBUTTONDOWN) {

						break;
					}

					/*ִ�к��κλ�ͼ����������ʱ���������ͼ�����ϣ�
					ֱ��ִ�� FlushBatchDraw �� EndBatchDraw �Ž�֮ǰ�Ļ�ͼ�����*/
					FlushBatchDraw();
					

				}

				break;
			}

			case attribute:
			{
				IMAGE image4;
				loadimage(&image4, "./����Ա����.png", 1000, 760);
				pageNum--;
	
				/* ����ѡ�������㷨��
	��ô���ס3�����ԣ����͡�������������������3���ľ�����ʽ��2D6 + 6��
	�������Եľ�����ʽ����3D6��Ҳ������3�ε���Ϊ1-6�����ӡ�
	���������Ա�֤��������ڱ�Ҫ�������ϵ���������ڵ���*/



				setbkmode(TRANSPARENT);

				double sum = Inv2.getApp() + Inv2.getCon() + Inv2.getDex() + Inv2.getEdu() + Inv2.getInte() + Inv2.getLuck() + Inv2.getPow() + Inv2.getSiz() + Inv2.getStr();
				settextstyle(70, 0, _T("����"));
				//����������ɫ
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
					settextstyle(30, 0, "����");
					outtextxy(SIZEX / 1.25 + 100, SIZEY / 2 - 30, _T("����ѧ"));
				}

				if (isViewAtt[0] == 2)
				{
					settextcolor(RED);
					settextstyle(30, 0, "����");
					outtextxy(SIZEX / 1.25 + 100, SIZEY / 2 + 60, _T("��ƽѧ"));
				}
				if (isViewAtt[1] == 1)
				{
					settextcolor(GREEN);
					settextstyle(30, 0, "����");
					outtextxy(SIZEX / 2.2 + 100, SIZEY / 5 - 30, _T("αװ"));
				}
				if (isViewAtt[2] == 1)
				{
					settextcolor(GREEN);
					settextstyle(30, 0, "����");
					outtextxy(SIZEX / 2.2 + 100, SIZEY / 5 - 30, _T("����"));
				}


				

				setfillcolor(BLACK);
				button(6 * SIZEX / 7, 0, SIZEX, SIZEY / 14, "��Ϸ����");


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
			//����ϵͳ�����Լ��϶��������Ľ���
              WeaponPage();

				break;
			}

			case pageType::end:
			{

				//����׼��
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
						settextstyle(i * 2, 0, "б��");
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
						settextstyle(i * 2, 0, "б��");
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
	settextstyle(15, 0, "����");
	drawtext(_T(txt.c_str()), &r, DT_NOPREFIX | DT_WORDBREAK | DT_NOCLIP);//�������ֵ������ʽ�����У��Զ����У�ʹ��ϵͳ���壬ʹ��ϵͳ�����Զ����㣬����������� | DT_
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
