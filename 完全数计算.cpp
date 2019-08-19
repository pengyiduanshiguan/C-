
#include <iostream>
#include <algorithm>
using namespace std;

int  main()
{
	int n;
	cin >> n;
	int num = 0, count = 0;
	for (int i = 3; i <= n; ++i)
	{
		for (int j = 2; j <= sqrt(i); ++j)
		{
				if (i % j == 0)
					num += j + i / j;
		}
		if (num == i)
			++count;
		num = 0;
	}
	if (count > 0)
		cout << count << endl;
	else
		cout << "-1" << endl;
	return 0;
}


