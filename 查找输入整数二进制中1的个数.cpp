
#include <iostream>
using namespace std;
#if 0
int main()
{
	int n;
	cin >> n;
	int count = 0;
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		if (n % 2 == 1)
			++count;
		n = n / 2;
	}
	cout << count << endl;
	return 0;
}

#endif
