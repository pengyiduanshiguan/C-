#include <iostream>
using namespace std;

int PathNum(int n, int m)
{
	if (n > 1 && m > 1)
		//b情况，递归
		return PathNum(n - 1, m) + PathNum(n, m - 1);
	else if (((n > 1) && (m == 1) || ((n == 1) && (m >= 1))))
		//a情况，终止条件
		return n + m;
	else
		//格子为0时，路径为0
		return 0;
}

int main()
{
	int n, m;
	cin >> n >> m;
	cout << PathNum(n, m) << endl;
	return 0;
}