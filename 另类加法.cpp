#if 0
#include <iostream>
using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;
	int n, m;
	//n��a��b��ͬ�Ĳ���
	n = a & b;
	//m��a��b��ͬ�Ĳ���
	m = a ^ b;
	if (n == 1)
		n = n << 1;
	cout << n + m << endl;
	return 0;
}

#endif

