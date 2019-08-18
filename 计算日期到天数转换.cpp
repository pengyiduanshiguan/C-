#if 0
#include <iostream>
using namespace std;

bool Year(int n)
{
	if (n % 400 == 0 || (n % 4 == 0 && n % 100 != 0))
		return false;
	else
		return true;
}

int main()
{
	int year, month, day;
	cin >> year >> month >> day;
	int a1[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int a2[] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
	int num = 0;
	if (Year(year))
	{
		if (month < 1 || month>12)
		{
			cout << "-1" << endl;
			return 0;
		}
		else
		{
			for (int i = 0; i < month; ++i)
			{
				if (day > a1[month] || day < 1)
				{
					cout << "-1" << endl;
					return 0;
				}
				num = num + a1[i];
			}
			cout << num + day << endl;
		}
	}
	else
	{
		if (month < 1 || month>12)
		{
			cout << "-1" << endl;
			return 0;
		}
		else
		{
			for (int i = 0; i < month; ++i)
			{
				if (day > a2[month] || day < 1)
				{
					cout << "-1" << endl;
					return 0;
				}
				num = num + a2[i];
			}
			cout << num + day << endl;
		}
	}
	return 0;
}
#endif
#if 0
#include <iostream>
using namespace std;

int main()
{
	int array[12] = { 31,59,90,120,151,181,212,
	243,273,304,334,365 };
	int year, month, day;
	int sum = 0;
	while (cin >> year >> month >> day)
	{
		sum = 0;
		sum += array[month - 2];
		sum += day;
		if (month > 2)
		{
			if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
			{
				sum += 1;
			}
		}
		cout << sum << endl;
	}
	return 0;
}

#endif