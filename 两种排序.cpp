#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	vector<string> v;
	int n;
	cin >> n;
	v.resize(n);
	for (auto& e : v)
		cin >> e;
	bool lenSym = true, lexSym = true;
	//ע���i=1��ʼ������ǰ��Ƚϣ��Ƚϳ���
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i - 1].size() >= v[i].size)
		{
			lenSym = false;
			break;
		}
	}
	//�Ƚ�ASCII
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i - 1] >= v[i])
		{
			lexSym = false;
			break;
		}
	}
	if (lenSym && lexSym)
		cout << "both" << endl;
	else if (!lenSym && lexSym)
		cout << "lexicographically" << endl;
	else if (lenSym && !lexSym)
		cout << "lengths" << endl;
	else if (!lenSym && !lexSym)
		cout << "none" << endl;
	return 0;
}
#endif