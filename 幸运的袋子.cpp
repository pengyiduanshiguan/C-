#include <iostream>
#include <algorithm>
using namespace std;

int Lucky(int x[], int n, int pos, int sum, int mul)
{
	int count = 0;
	//循环，搜索以位置i开始所有可能的组合
	for (int i = pos; i < n; ++i)
	{
		sum += x[i];
		mul *= x[i];
		if (sum > mul)
			//找到符合要求的组合，加1，继续累加，看是否有符合要求集合
			count += 1 + Lucky(x, n, i + 1, sum, mul);
		else if (x[i] == 1)
			//如果不符合要求，且当前元素值为1，则继续向后搜索
			count += Lucky(x, n, i + 1, sum, mul);
		else
			break;
		//搜索下一个位置前，恢复sum和mul
		sum -= x[i];
		mul /= x[i];
		//数字相同的球，没有区别
		while (i < n - 1 && x[i] == x[i - 1])
			++i;
	}
	return count;
}

int main()
{
	int n;
	while (cin >> n)
	{
		int x[n];
		for (int i = 0; i < n; ++i)
			cin >> x[i];
		sort(x, x + n);
		//从第一个位置开始搜索
		cout << Lucky(x, n, 0, 0, 1) << endl;
	}
	return 0;
}