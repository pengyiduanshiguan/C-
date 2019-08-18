#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//����Լ���������1�ͱ����Լ��
void divisorNum(int n, vector<int>& divNum)
{
	for (int i = 0; i <= sqrt(n); ++i)
	{
		if (n % i == 0)
		{
			divNum.push_back(i);
			//��ƽ�����ǻ�����һ����ҲҪ����
			if (n / i != i)
				divNum.push_back(n / i);

		}
	}
}

int Jump(int N,int M)
{
	//����ĵ����stepNum��Ĳ�������ʶNΪ1������N��Nλ1��
	vector<int> stepNum(M + 1, 0);
	stepNum[N] = 1;
	for (int i = 0; i < M; ++i)
	{
		//N������Լ������Ϊ�ӱ�������㿪ʼ���ߵ�����
		vector<int>divNum;
		//0��������㲻�ܵ�
		if (stepNum[i] == 0)
			continue;
		//����������ߵò����洢��divNum��������
		divisorNum(i, divNum);

		for (int j = 0; j < divNum.size(); ++i)
		{
			//��λ��i�����ܵ���ĵ�ΪstepNum[divNum[j]+i]
			if ((divNum[j]) + i <= M && stepNum[divNum[j] + i] != 0)
				stepNum[divNum[j] + i] = min(stepNum[divNum[j] + i], stepNum[i] + 1);
			else if ((divNum[j] + i) <= M)
				stepNum[divNum[j] + i] = stepNum[i] + 1;
		}
	}
	if (stepNum[M] == 0)
		return -1;
	else
		//��ʼ��ʱ���һ��������Ҫ-1
		return stepNum[M] - 1;
}

int main()
{
	int n, m;
	cin >> n >> m;
	cout << Jump(n, m) << endl;
	return 0;
}
#endif
