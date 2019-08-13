
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s, cnt, cur;
	cin >> s;
	for (int i = 0; i < s.size(); ++i)
	{
		//找出数字串保存到cur中
		if (s[i] >= '0' && s[i] <= '9')
		{
			cur += s[i];
		}
		else
		{
			//找出最长数字串，保存到cnt中
			if (cnt.size() < cur.size())
			{
				cnt = cur;
			}
			cur.clear();
		}		
	}
	cout << cnt << endl;
	return 0;
}

