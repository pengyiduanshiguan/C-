//Ã«²¡2
#if 0
#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
	bool kuohao(string& s)
	{
		int size = s.size();
		int left = 0, right = 0;
		for (int i = 0; i < size; ++i)
		{
			if (s[0] != '(')
				return false;
			if (s[i] != '(' || s[i] != ')')
				return false;
			if (s[i] == '(')
				++left;
			if (s[i] == ')')
				++right;
			if (left < right)
				return false;
		}
		if (left == right)
			return true;
		else
			return false;
	}

	string s;
};


//class Parenthesis 
//{
//public:
//	bool chkParenthesis(string A, int n)
//	{
//		stack<char> sc;
//		for (auto ele : A)
//		{
//			switch (ele)
//			{
//				case'(';
//					sc.push(ele);
//					break:
//				case')':
//					if (sc.empty() || sc.top() != '(')
//						return false;
//					else
//						sc.pop();				
//					break;
//				default:
//					return false;
//			}
//		}
//		return true;
//	}
//};

#endif