#if 0
//请设计一个类，该类只能在堆上创建空间
//构造函数私有化
//   1.将类的构造函数私有，拷贝构造函数私有。防止别人调用拷贝构造在栈上生成对象。
//   2.提供一个静态的成员函数，在该静态成员函数中完成堆对象的创建

//      堆：向上增长，一般有程序员分配释放，若程序员不释放，程序结束时由OS
//          回收，分配方式类似于链表(malloc  new)
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



//请设计一个类，该类只能在栈上创建对象
//    栈：向下增长。栈内存分配运算内置于处理器的指令集种，效率很高，但是分配的容量
//        有限。栈区主要存放运行函数二分配的局部变量，函数参数，返回数据，返回参数等


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

//只能在栈上创建对象，既不能在堆上创建对象，因此只要将new的功能屏蔽掉即可
//即屏蔽掉operator new 和定位new表达式   注意：屏蔽掉operator new 实际也屏蔽掉了
// 定位new
class StackOnly
{
public:
	StackOnly() {}
private:
	void* operator new(size_t size);
	void operator delete(void* p);
};

//实现一个不能被继承的类
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

//C++给出新的关键字  final 
class NoInherit final
{
	//……
};

//单例模式:
//一个类只能创建一个对象，即单例模式，该模式可以保证系统中该类只有一个实例
//并提供一个访问他的全局访问点，该实例被所有程序模块共享

//单例模式有两种实现方式：
//1饿汉模式：就是说不管将来你用不用，程序启动时就创建一个唯一的实例对象
//      优点;简单
//      缺点：可能会导致进程启动慢，但如果有多个单例类对象实例启动顺序不确定
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		return &m_instance;
	}
private:
	//构造函数私有
	Singleton() {};

	//C++98防拷贝
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	//C++11
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton m_instance;
};
Singleton Singleton::m_instance;     //在程序入口之前就完成单例对象的初始化


#endif

//如果这个单例对象在多线程高并发环境下频繁使用，性能要求较高
//那么使用饿汉模式来避免资源竞争，提高响应速度更好

//饿汉模式：
//   如果单例模式构造对象十分耗时或者占用资源，比如加载插件，初始化网络等
//   而有可能该对象程序运行不会用到，那么在程序一开始就进行初始化，就会导致程序
//   运行缓慢，这种情况使用懒汉模式更好
//    优点：第一次使用实例对象时，创建对象。进程启动无负载
//    缺点：复杂
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Singleton 
{
public:
	static Singleton* GetInstance()
	{
		//这里以一定要使用double-check的方式加锁，才能保证效率和线程安全
		if (m_pInstance == nullptr)
		{
			m_mutex.lock();
			if (m_pInstance == nullptr)
				m_pInstance = new Singleton();
			m_mutex.unlock();
		}
		return m_pInstance;
	}
	//实现一个内嵌垃圾回收类
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if (Singleton::m_pInstance)
				delete Singleton::m_pInstance;
		}
	};
	//定义一个静态成员变量，程序结束时，系统会自动调用他的析构函数，从而释放单例对象
	static CGarbo Garbo;
private:
	//构造函数私有
	Singleton()
	{}
	//防拷贝
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* m_pInstance;   //单例对象指针
	static mutex m_mutex;            //互斥锁
};

Singleton* Singleton::m_pInstance;
Singleton::CGarbo Garbo;
mutex Singleton::m_mutex;

void func(int n)
{
	cout << Singleton::GetInstance() << endl;
}

//多线程模式下演示上面加锁和不加锁的区别
int main()
{
	thread t1(func, 10);
	thread t2(func, 10);
	t1.join;
	t2.join;
	cout << Singleton::GetInstance() << endl;
	cout << Singleton::GetInstance() << endl;
}