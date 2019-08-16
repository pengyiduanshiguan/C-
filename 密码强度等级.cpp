#if 0
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	cin >> s;
	int grade = 0;
	int num = 0, A = 0, a = 0, sign = 0;
	//ÃÜÂë³¤¶È
	if (s.size() <= 4)
		grade += 5;
	if (s.size() >= 5 && s.size() <= 7)
		grade += 10;
	if (s.size() >= 8)
		grade += 25;
	//×ÖÄ¸,Êı×Ö£¬·ûºÅ
	for (int i = 0; i < s.size(); ++i)
	{
		//Êı×Ö   num
		if (s[i] >= '0' && s[i] <= '9')
			++num;
		//×ÖÄ¸
		else if (s[i] >= 'a' && s[i] <= 'z')
			++a;
		else if (s[i] >= 'A' && s[i] <= 'Z')
			++A;
		//·ûºÅ
		else
			++sign;
	}
	if (num == 1)
		grade += 10;
	if (num > 1)
		grade += 20;
	if ((A == 0 && a != 0) || (A != 0 && a == 0))
		grade += 10;
	if (a > 0 && A > 0)
		grade += 20;
	if (sign == 1)
		grade += 10;
	if (sign > 1)
		grade += 25;
	if (num && (A + a))
		grade += 2;
	if (num && (A + a) && sign)
		grade += 3;
	if (num && a && A && sign)
		grade += 5;
	if (grade >= 90)
		cout << "VERY_SECURE" << endl;
	else if (grade >= 80)
		cout << "SECURE" << endl;
	else if (grade >= 70)
		cout << "VERY_STRONG" << endl;
	else if (grade >= 60)
		cout << "STRONG" << endl;
	else if (grade >= 50)
		cout << "AVERAGE" << endl;
	else if (grade >= 25)
		cout << "WEAK" << endl;
	else
		cout << "VERY_WEAK" << endl;
	return 0;
}

#endif

