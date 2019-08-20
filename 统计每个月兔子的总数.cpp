#if 0
#include <iostream>
using namespace std;

int Fib(int n)
{
	if (n < 3)
		return 1;
	else
		return Fib(n - 1) + Fib(n - 2);
}

int main()
{
	int month;
	cin >> month;
	cout << Fib(month) << endl;
	return 0;
}
#endif
#if 0

#include <iostream>
using namespace std;

int main()
{
	int month;
	cin >> month;
	int num=0, left=1, right=1;

	for (int i = 3; i <= month; ++i)
	{
		num = left + right;
		left = right;
		right = num;
	}
	cout << num << endl;
	return 0;
}
#endif
