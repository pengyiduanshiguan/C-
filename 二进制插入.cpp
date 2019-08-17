#if 0
#include <iostream>
#include <string>
using namespace std;

class BinInsert {
public:
	int binInsert(int n, int m, int j, int i) {
		// write code here
		m <<= j;
		return m | n;
	}
};
#endif
