
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s, cnt, cur;
	cin >> s;
	for (int i = 0; i < s.size(); ++i)
	{
		//�ҳ����ִ����浽cur��
		if (s[i] >= '0' && s[i] <= '9')
		{
			cur += s[i];
		}
		else
		{
			//�ҳ�����ִ������浽cnt��
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

