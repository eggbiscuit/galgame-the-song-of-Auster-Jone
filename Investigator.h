#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;
double throw_1dx(int x);


//创建调查员
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
	    //时代
		era = e;
		//力量
	    str = st;
		//体质
		con = co;
		//体型
		siz = si;
		//敏捷
		dex = de;
		//外貌
		app = ap;
		//智力
		inte = in;
		//意志
		pow = po;
		//教育
		edu = ed;
		//幸运
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

	
	//次要属性，在游戏中作roll点判断剧情走势
	double accouting = 5;     //会计学
	double anthropology = 1;  //人类学
	double appraise = 5;      //估价
	double archaeology = 1;   //考古学
	//自定义技艺先空着
	double charm = 15;     //魅力
	double climb = 20;     //攀爬
	//credit  rating and Cthulhu Nythos
	double disguise = 5;   //伪装
	double dodge;//敏捷的一半
	double drive = 20;  //驾驶
	double eleRepair = 10;  //电子维修
	double talk = 5;   //谈吐
	double finghting = 25;    //打斗
	//自定义格斗技能
	double firearms = 25;    //火器
	//自定义火器
	double firstAid = 30;  //急救
	double history = 5;    //历史学
	double intimidate = 15;   //恫吓
	double jump = 20;   //跳跃      
	double language;//母语 等同于教育数值
	//三项本职技能
	double law = 5;  //法律
	double libraryUse = 20;  //图书馆使用
	double listen = 20;      //聆听
	double locksmith = 1;    //钳工
	double mechRepair = 10;   //机器修理
	double medicine = 1;     //医学
	double naturalWorld = 10;//博物学
	double navigate = 10;     //导航
	double occult = 5; //神秘学
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
	//参数：通过洗牌算法来决定伤害数值,目的是模拟真实的洗牌
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

	const Card operator+(const Card&); //+主要用于卡牌伤害的叠加
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
		Inside_Out_Shuffle(arr, res);//将预制好的arr的牌洗至res容器中
		number = res[0];
		Fisher_Yates_Shuffle(arr, res2);//第二种洗牌方式
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
	int number = 0;  //伤害
	int number2 = 0;  //卡牌数
	int damage = 0;
};

class Gun: virtual public Weapon
{//参数：子弹以及射程，命中由骰子决定，伤害由1d4+damagebunus+体格决定
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
			cout << "没有子弹";
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
		//技能可发动一次，用于增加一次伤害或命中概率

	}
	private:
		string name;
		int bulletNum;
		double range;
		double damage;
};