#if 0
#include <iostream>
#include <algorithm>
using namespace std;

bool IsPrime(int num) {
	int tmp = sqrt(num);	
		//只遍历到开方出，不能被开方左边的数整除，则一定不能被开方右边的数整除 
		for (int i = 2; i <= tmp; i++) 
		{
			if (num %i == 0) 
				return false;
		}
		return true; 
}

int main() {
	int num; int half; int i; while (cin >> num) {
		half = num / 2;
		//从中间向两边找 
		for (i = half; i > 0; i--)
		{
			if (IsPrime(i) && IsPrime(num - i))
				break;
		}
		cout << i << endl << num - i << endl;
	}
	return 0;
}
//int main()
//{
//	int n;
//	cin >> n;
//	int num1 = n / 2 , num2 = n / 2 ;
//	while (num1 > 1)
//	{
//		if (IsPrime(num1) && IsPrime(num2))
//		{
//			cout << num1 << " " << num2;
//			break;
//		}
//		--num1;
//		++num2;
//	}
//	return 0;
//}

#endif
