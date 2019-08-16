#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n;
	cin >> n;
	string s;
	int num=0, sum=0;
	while (n > 0)
	{
		s += n % 2;
		n /= 2;
	}
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == 1)
			++num;
		else
			num = 0;
		if (num > sum)
			sum = num;
	}
	cout << sum << endl;
	return 0;
}