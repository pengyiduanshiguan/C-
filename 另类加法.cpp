#if 0
#include <iostream>
using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;
	int n, m;
	//n是a与b相同的部分
	n = a & b;
	//m是a与b不同的部分
	m = a ^ b;
	if (n == 1)
		n = n << 1;
	cout << n + m << endl;
	return 0;
}

#endif

