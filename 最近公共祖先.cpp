#include <algorithm>
#include <iostream>
using namespace std;

class LCA {
public:
	int getLCA(int a, int b) {
		// write code here
		if (a == 1 || b == 1)
			return 1;
		int num = max(a, b);
		int sum = min(a, b);
		while (1)
		{
			if (num == sum)
				return sum;
			else if (num > sum)
				num /= 2;
			else
				sum /= 2;
		}		
	}
};