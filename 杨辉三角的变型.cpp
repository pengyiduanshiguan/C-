#if 0
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	int n, m;
	cin >> n;
	m = 2 * n - 1;
	vector<vector<int>> v(n, vector<int>(m, 0));
	v[0][0] = 1;
	for (int i = 1; i < n; ++i)
	{
		//��һ�к����һ�ж�Ϊ1
		v[i][0] = v[i][2 * i] = 1;
		for (int j = 1; j < 2 * i; ++j)
		{
			if (j == 1)
				//����ǵڶ��У���ֻ������Ԫ�صĺ�
				v[i][j] = v[i - 1][j - 1] + v[i - 1][j];
			else
				v[i][j] = v[i - 1][j - 1] + v[i - 1][j] + v[i - 1][j + 1];

		}

	}
	int k;
	for (k = 0; k < m; ++k)
	{
		if (v[n - 1][k] % 2 == 0 && v[n - 1][k] != 0)
		{
			cout << k + 1 << endl;
			break;
		}
	}
	if (k == m)
		cout << -1 << endl;
	return 0;
}

#endif
