#include <iostream>
using namespace std;

int PathNum(int n, int m)
{
	if (n > 1 && m > 1)
		//b������ݹ�
		return PathNum(n - 1, m) + PathNum(n, m - 1);
	else if (((n > 1) && (m == 1) || ((n == 1) && (m >= 1))))
		//a�������ֹ����
		return n + m;
	else
		//����Ϊ0ʱ��·��Ϊ0
		return 0;
}

int main()
{
	int n, m;
	cin >> n >> m;
	cout << PathNum(n, m) << endl;
	return 0;
}