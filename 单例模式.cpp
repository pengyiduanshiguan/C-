#if 0
//�����һ���࣬����ֻ���ڶ��ϴ����ռ�
//���캯��˽�л�
//   1.����Ĺ��캯��˽�У��������캯��˽�С���ֹ���˵��ÿ���������ջ�����ɶ���
//   2.�ṩһ����̬�ĳ�Ա�������ڸþ�̬��Ա��������ɶѶ���Ĵ���

//      �ѣ�����������һ���г���Ա�����ͷţ�������Ա���ͷţ��������ʱ��OS
//          ���գ����䷽ʽ����������(malloc  new)
class HeapOnly
{
public:
	static HeapOnly* CreateObject()
	{
		return new HeapOnly();
	}
	HeapOnly(const HeapOnly&) = delete;

private:
	HeapOnly() {}
	
};



//�����һ���࣬����ֻ����ջ�ϴ�������
//    ջ������������ջ�ڴ�������������ڴ�������ָ��֣�Ч�ʺܸߣ����Ƿ��������
//        ���ޡ�ջ����Ҫ������к���������ľֲ������������������������ݣ����ز�����


class StackOnly
{
public:
	static StackOnly CreateObject()
	{
		return StackOnly();
	}
private:
	StackOnly() {}
};

//ֻ����ջ�ϴ������󣬼Ȳ����ڶ��ϴ����������ֻҪ��new�Ĺ������ε�����
//�����ε�operator new �Ͷ�λnew���ʽ   ע�⣺���ε�operator new ʵ��Ҳ���ε���
// ��λnew
class StackOnly
{
public:
	StackOnly() {}
private:
	void* operator new(size_t size);
	void operator delete(void* p);
};

//ʵ��һ�����ܱ��̳е���
class NoInherit
{
public:
	static NoInherit GetInstance()
	{
		return NoInherit();
	}
private:
	NoInherit() {}
};

//C++�����µĹؼ���  final 
class NoInherit final
{
	//����
};

//����ģʽ:
//һ����ֻ�ܴ���һ�����󣬼�����ģʽ����ģʽ���Ա�֤ϵͳ�и���ֻ��һ��ʵ��
//���ṩһ����������ȫ�ַ��ʵ㣬��ʵ�������г���ģ�鹲��

//����ģʽ������ʵ�ַ�ʽ��
//1����ģʽ������˵���ܽ������ò��ã���������ʱ�ʹ���һ��Ψһ��ʵ������
//      �ŵ�;��
//      ȱ�㣺���ܻᵼ�½�����������������ж�����������ʵ������˳��ȷ��
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		return &m_instance;
	}
private:
	//���캯��˽��
	Singleton() {};

	//C++98������
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	//C++11
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton m_instance;
};
Singleton Singleton::m_instance;     //�ڳ������֮ǰ����ɵ�������ĳ�ʼ��


#endif

//���������������ڶ��̸߲߳���������Ƶ��ʹ�ã�����Ҫ��ϸ�
//��ôʹ�ö���ģʽ��������Դ�����������Ӧ�ٶȸ���

//����ģʽ��
//   �������ģʽ�������ʮ�ֺ�ʱ����ռ����Դ��������ز������ʼ�������
//   ���п��ܸö���������в����õ�����ô�ڳ���һ��ʼ�ͽ��г�ʼ�����ͻᵼ�³���
//   ���л������������ʹ������ģʽ����
//    �ŵ㣺��һ��ʹ��ʵ������ʱ���������󡣽��������޸���
//    ȱ�㣺����
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Singleton 
{
public:
	static Singleton* GetInstance()
	{
		//������һ��Ҫʹ��double-check�ķ�ʽ���������ܱ�֤Ч�ʺ��̰߳�ȫ
		if (m_pInstance == nullptr)
		{
			m_mutex.lock();
			if (m_pInstance == nullptr)
				m_pInstance = new Singleton();
			m_mutex.unlock();
		}
		return m_pInstance;
	}
	//ʵ��һ����Ƕ����������
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if (Singleton::m_pInstance)
				delete Singleton::m_pInstance;
		}
	};
	//����һ����̬��Ա�������������ʱ��ϵͳ���Զ��������������������Ӷ��ͷŵ�������
	static CGarbo Garbo;
private:
	//���캯��˽��
	Singleton()
	{}
	//������
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* m_pInstance;   //��������ָ��
	static mutex m_mutex;            //������
};

Singleton* Singleton::m_pInstance;
Singleton::CGarbo Garbo;
mutex Singleton::m_mutex;

void func(int n)
{
	cout << Singleton::GetInstance() << endl;
}

//���߳�ģʽ����ʾ��������Ͳ�����������
int main()
{
	thread t1(func, 10);
	thread t2(func, 10);
	t1.join;
	t2.join;
	cout << Singleton::GetInstance() << endl;
	cout << Singleton::GetInstance() << endl;
}