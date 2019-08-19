#if 0
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	string s1, s2;
	getline(cin, s);
	for (int i = 0; i < s.size(); ++i)
	{
		int cur;
		if (s[i] == '-')
			cur = i;
		s1 = s.substr(0, i-1);
		s2 = s.substr(i + 1, s.size() - 1);
		if (s1 == "joker JOKER" || s2 == "joker JOKER")
		{
			cout << "joker JOKER" << endl;
			break;
		}
		if (s1.size() != s2.size())
		{
			cout << "ERROR" << endl;
			break;
		}
		else
		{
			if (s[0] == '2')
			{
				cout << s1 << endl;
				break;
			}
			else if (s[cur + 1] == '2')
			{
				cout << s2 << endl;
				break;
			}
			else
			{
				if (s[0] > s[cur + 1])
				{
					cout << s1 << endl;
					break;
				}
				else
				{
					cout << s2 << endl;
					break;
				}
			}
		}
	}
	return 0;
}

#endif


