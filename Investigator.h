#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;
double throw_1dx(int x);


//��������Ա
class Invest
{
public:

	Invest(string n="", string p = "", double e = 0.0, string o = "", string g = "", string r = "", string h = "", double st=0.0, double co=0.0, double si = 0.0, double de = 0.0,
		double ap = 0.0,double in = 0.0,double po = 0.0,double ed = 0.0,double lu = 0.0)
	{
		n.length() < 20 ? n.copy(name, n.length()) : n.copy(name, 19);
		p.length() < 20 ? p.copy(player, p.length()) : p.copy(player, 19);
		o.length() < 20 ? o.copy(occupation, o.length()) : o.copy(occupation, 19);
		g.length() < 20 ? g.copy(gender, g.length()) : g.copy(gender, 19);
		r.length() < 20 ? r.copy(recidence, p.length()) : r.copy(recidence, 19);
		h.length() < 20 ? h.copy(hometown, h.length()) : h.copy(hometown, 19);
	    //ʱ��
		era = e;
		//����
	    str = st;
		//����
		con = co;
		//����
		siz = si;
		//����
		dex = de;
		//��ò
		app = ap;
		//����
		inte = in;
		//��־
		pow = po;
		//����
		edu = ed;
		//����
		luck = lu;

		initSecondAtt();
	
		
	}
	double getFirearms()const
	{
		return firearms;
	}
	void initSecondAtt()
	{
		
			this->language = this->edu;
			this->dodge = this->dex / 2;

		
	}
	void strInit(double a)
	{
		str = a;
	}
	void conInit(double a)
	{
		con = a;
	}
	void sizInit(double a)
	{
		siz = a;
	}
	void dexInit(double a)
	{
		dex = a;
	}
	void appInit(double a)
	{
		app = a;
	}
	void inteInit(double a)
	{
		inte = a;
	}
	void powInit(double a)
	{
		pow = a;
	}
	void eduInit(double a) {
		edu = a;
	}
	void luckInit(double a)
	{
		luck = a;
	}

	double getStr()const
	{
		return str;
	}
	double getCon()const
	{
		return con;
	}
	double getSiz()const
	{
		return siz;
	}
	double getDex()const
	{
		return dex;
	}
	double getApp()const
	{
		return app;
	}
	double getInte()const
	{
		return inte;
	}
	double getPow()const
	{
		return pow;
	}
	double getEdu()const
	{
		return edu;
	}
	double getLuck()const
	{
		return luck;
	}
private:
	char name[20] = {};
	char player[20] = {};
	double era;
	char occupation[20];
	char gender[20] = {};
	char  recidence[20] = {};
	char hometown[20] = {};


	double str;
	double con;
	double siz;
	double dex;
	double app;
	double inte;
	double  pow;
	double edu;
	double luck;

	
	//��Ҫ���ԣ�����Ϸ����roll���жϾ�������
	double accouting = 5;     //���ѧ
	double anthropology = 1;  //����ѧ
	double appraise = 5;      //����
	double archaeology = 1;   //����ѧ
	//�Զ��弼���ȿ���
	double charm = 15;     //����
	double climb = 20;     //����
	//credit  rating and Cthulhu Nythos
	double disguise = 5;   //αװ
	double dodge;//���ݵ�һ��
	double drive = 20;  //��ʻ
	double eleRepair = 10;  //����ά��
	double talk = 5;   //̸��
	double finghting = 25;    //��
	//�Զ���񶷼���
	double firearms = 25;    //����
	//�Զ������
	double firstAid = 30;  //����
	double history = 5;    //��ʷѧ
	double intimidate = 15;   //����
	double jump = 20;   //��Ծ      
	double language;//ĸ�� ��ͬ�ڽ�����ֵ
	//���ְ����
	double law = 5;  //����
	double libraryUse = 20;  //ͼ���ʹ��
	double listen = 20;      //����
	double locksmith = 1;    //ǯ��
	double mechRepair = 10;   //��������
	double medicine = 1;     //ҽѧ
	double naturalWorld = 10;//����ѧ
	double navigate = 10;     //����
	double occult = 5; //����ѧ
};


class Weapon
{
public:
	Weapon() {};
	virtual ~Weapon() {};
	virtual void setName(string n) {  };
	virtual string getName()const { return ""; };
	
	virtual bool isAvailable(double distance)
	{
		return 0;
		
	}
	virtual bool isHit()
	{
		return 0;
	}
	virtual double getDamage()const
	{
		return 0;
	}
	virtual double setDamage()
	{
		return 0;
	}


};

class Card :virtual public Weapon
{
	//������ͨ��ϴ���㷨�������˺���ֵ,Ŀ����ģ����ʵ��ϴ��
public:
	Card()
	{
		
	}
	
	Card(string n,int s)
	{
		name = n;
		setNumbers(s);
		setDamage();
	}

	const Card operator+(const Card&); //+��Ҫ���ڿ����˺��ĵ���
	void Fisher_Yates_Shuffle(vector<int>& arr, vector<int>& res);
    void Inside_Out_Shuffle(const vector<int>& arr, vector<int>& res);
	double skillDamage(const Card& op1);

	virtual void setName(string n)override
	{
		name = n;
	}
	virtual string getName()const override
	{
		return name;
	}
	void setNumbers(int s)
	{

		vector<int> arr ;
		for (int i = 1; i <= s; i++)
		{
			arr.push_back(i);
		}
		vector<int>res, res2;
		Inside_Out_Shuffle(arr, res);//��Ԥ�ƺõ�arr����ϴ��res������
		number = res[0];
		Fisher_Yates_Shuffle(arr, res2);//�ڶ���ϴ�Ʒ�ʽ
		number2 = res[0];


	}
	virtual double setDamage()override
	{
		damage = (throw_1dx(5) + number) * 10;
		return damage;
	}
	int getNumber()const
	{
	
		return number;
	}
	int getNumber2()const
	{
		return number2;
	}
	double getDamage()const {
		return damage;
	}
    void setNumber(int s)
	{
		number = s;
	}
	void setNumber2(int s)
	{
		number2 = s;
	}
private:
	string name;
	int number = 0;  //�˺�
	int number2 = 0;  //������
	int damage = 0;
};

class Gun: virtual public Weapon
{//�������ӵ��Լ���̣����������Ӿ������˺���1d4+damagebunus+������
public:
	Gun(string n="", int bn=0, double r=0)
	{
		name = n;
		bulletNum = bn;
		range = r;
		setDamage();
	}
	
	virtual bool isHit()
	{
		if (bulletNum <= 0)
		{
			cout << "û���ӵ�";
			return 0;
		}

		else
		{
			bulletNum--;
			return 1;
			
		}
	}

	void setBulletNum(int n)
	{
		bulletNum = n;
	}
	int getBulletNum()const
	{
		return bulletNum;
	}
	void setRange(double r)
	{
		range = r;
	}
	double getRange()
	{
		return range;
	}
	virtual void setName(string n)override 
	{
		name = n;
	}
	virtual string getName()const override
	{
		return name;
	}
	virtual double setDamage()override
	{
		
		damage = throw_1dx(10) + 2;
		return damage;
	}
	virtual double getDamage()const override
	{
		return damage;
	}

	void skill()
	{
		//���ܿɷ���һ�Σ���������һ���˺������и���

	}
	private:
		string name;
		int bulletNum;
		double range;
		double damage;
};