#if 0
#include <iostream>
#include <algorithm>
using namespace std;

bool IsPrime(int num) {
	int tmp = sqrt(num);	
		//ֻ�����������������ܱ�������ߵ�����������һ�����ܱ������ұߵ������� 
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
		//���м��������� 
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
