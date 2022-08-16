#include "Investigator.h"
using namespace std;
double throw_1dx(int x)
{
	double t = rand() % x;
	double n = t + 1.0;
	return n;
}

void Card::Fisher_Yates_Shuffle(vector<int>& arr, vector<int>& res)
{//时间复杂度n2,空间复杂度n
	srand((unsigned int)time(0));
	int k = 0;
	for (int i = arr.size() - 1; i > 0; i--)
	{
		k = rand() % (arr.size() - 1);//抽牌
		res.push_back(arr[k]);
		arr.erase(arr.begin() + k);
	}
}
double Card::skillDamage(const Card& op1)
{
	Card temp;
	temp = *this + op1;
	temp.setDamage();
	return temp.getDamage();
}


const Card Card::operator+(const Card& op1)
{
	Card temp;
	temp.setNumber(this->number + op1.number);
	
	return temp;
}
void Card::Inside_Out_Shuffle(const vector<int>& arr, vector<int>& res)
{//第i个元素在前i次实验中确保不被选中
	res.assign(arr.size(), 0);
	copy(arr.begin(), arr.end(), res.begin());
	int k;
	for (int i = 0; i < arr.size(); ++i)
	{
		k = rand() % (i + 1);
		res[i] = res[k];
		res[k] = arr[i];
	}
}
