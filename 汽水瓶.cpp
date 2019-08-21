#if 0
#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int num = 0;
	while (n > 2)
	{
		num += n / 3;
		n = n / 3 + n % 3;
	}
	if (n == 2)
		cout << ++num << endl;
	else
		cout << num << endl;
	return 0;
}

#endif
