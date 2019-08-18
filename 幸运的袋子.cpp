#include <iostream>
#include <algorithm>
using namespace std;

int Lucky(int x[], int n, int pos, int sum, int mul)
{
	int count = 0;
	//ѭ����������λ��i��ʼ���п��ܵ����
	for (int i = pos; i < n; ++i)
	{
		sum += x[i];
		mul *= x[i];
		if (sum > mul)
			//�ҵ�����Ҫ�����ϣ���1�������ۼӣ����Ƿ��з���Ҫ�󼯺�
			count += 1 + Lucky(x, n, i + 1, sum, mul);
		else if (x[i] == 1)
			//���������Ҫ���ҵ�ǰԪ��ֵΪ1��������������
			count += Lucky(x, n, i + 1, sum, mul);
		else
			break;
		//������һ��λ��ǰ���ָ�sum��mul
		sum -= x[i];
		mul /= x[i];
		//������ͬ����û������
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
		//�ӵ�һ��λ�ÿ�ʼ����
		cout << Lucky(x, n, 0, 0, 1) << endl;
	}
	return 0;
}