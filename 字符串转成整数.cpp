#include <iostream>
#include <string>
using namespace std;

bool IntergerOfString(string& s)
{
	if (s[0] != '+' && s[0] != '-' && s[0]<'0' && s[0]>'9')
		return false;
	for (int i = 1; i < s.size(); ++i)
	{
		if (s[0]<'0' || s[0]>'9')
			return false;
	}
	return true;
}

int main()
{
	string s;
	cin >> s;
	if (IntergerOfString(s))
		cout << s << endl;
	else
		cout << "0" << endl;
	return 0;
}