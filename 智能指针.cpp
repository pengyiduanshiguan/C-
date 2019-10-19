#if 0
//auto_ptr的实现原理:管理权转移的思想
//模拟实现一份简答的AutoPtr,了解原理
template <class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr=NULL)
		:_ptr(ptr)
	{}
	~AutoPtr()
	{
		if (_ptr)
			delete _ptr;
	}
	//一旦发生拷贝，就将ap中的资源转移到当前对象中，然后ap与其所管理资源断开联系
	//这样就解决了一块空间被多个对象使用而造成程序崩溃问题
	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}
	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		//检查是否为自己给自己赋值
		if (this != &ap)
		{
			//释放当前资源
			if (_ptr)
				delete _ptr;
			//转移zp中资源到当前对象中
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

int main()
{
	AutoPtr<Date> ap(new Date);
	//现在再从实现原理层分析会发现，这里拷贝后把ap对象的指针赋空了
	//通过ap对象访问资源时就会出现问题
	AutoPtr<Date> copy(ap);
	ap->_year = 2108;
	return 0;
}

#endif

#if 0
//设计思路：防拷贝，就是不让拷贝和赋值
//模拟实现
template<class T>
class UniquePtr
{
public:
	UniquePtr(T* ptr = nullptr)
		:_ptr(ptr)
	{}
	~UniquePtr()
	{
		if (_ptr)
			delete _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T& operator->()
	{
		return _ptr;
	}
private:
	//C++98防拷贝方式：只声明+不实现+声明成私有
	UniquePtr(UniquePtr<T> const&);
	UniquePtr& operator=(UniquePtr<T> const&);

	//C++11防拷贝的方式：delete   禁止默认成员的产生
	UniquePtr(UniquePtr<T> const&) = delete;
	UniquePtr& operator=(UniquePtr<T> const&) = delete;
private:
	T* _ptr;
};

//缺陷：对象之间不能共享资源

#endif

#if 0
//模拟实现一份简单的shard_ptr，了解原理
#include <thread>
#include <mutex>

template <class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = nullptr)
		:_ptr(ptr)
		,_pRefCount(new int(1))
		,_pMutex(new mutex)
	{}
	~SharedPtr()
	{
		Release();
	}
	SharedPtr(const SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		, _pRefCount(sp._pRefCount)
		, _pMutex(sp._pMutex)
	{
		AddRefCount();
	}
	//sp1=sp2
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		//if(this!=&sp)
		if (_ptr != sp._ptr)
		{
			//释放管理的旧资源
			Release();

			//共享管理新对象的资源，并增加引用计数
			_ptr = sp._pMutex;
			_pRefCount = sp._pRefCount;
			_pMutex = sp._pMutex;

			AddRefCount();
		}
		return *this;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	int UseCount()
	{
		*_pRefCount;
	}
	T* Get()
	{
		return _ptr;
	}
     
	void AddRefCount()
	{
		//加锁或者使用加1的原子操作
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}

private:
	void Release()
	{
		bool deleteflag = false;
		//引用计数减1，如果减至0，则释放资源
		_pMutex.lock();
		if (--(*_pRefCount) == 0)
		{
			delete _ptr;
			delete _pRefCount;
			deleteflag = true;
		}
		_pMutex.unlock();
		if (deleteflag == true)
			delete _pMutex;
	}

private:
	//关于引用计数的类型：
	//   如果为普通类型比如int count  sp2(sp1)当对sp2中的count--时，sp1中的count不会发生变化
	//   如果设置为static int count    shared_ptr <int> sp3 count为所有类对象所共享，
	//           那么count会变为1，sp1,sp2中的count也会改变为1，那么就会受影响  
	//计数应该与资源挂钩，所以采用指针的方式，直接指向资源的空间
	int* _pRefCount;   //引用计数
	T* _ptr;    //指向管理资源的指针
	mutex* _pMutex;    //互斥锁
};

// shared_ptr用来处理delete malloc  FILE  至于delete[]可以直接用vector处理
//资源的类型：new的堆空间  delete的堆空间   文件指针   套接字

//shared_ptr:定制删除     让shared_pt释放资源的方式：采用仿函数
//   具体资源，让用户根据资源的类型选择合适的方式进行释放

//线程安全问题：
//       
 
//采用双向链表---循环引用
#endif 

#include <memory>
#include <iostream>
using namespace std;

struct ListNode
{
	ListNode(int data)
		/*:next(nullptr)
		,prev(nullptr)
		,_data(data)*/
		:_data(data)
	{
		cout << "ListNode(int):" << this << endl;
	}
	~ListNode()
	{
		cout << "~ListNode():" << this << endl;
	}
	//存在循环引用
	/*shared_ptr<ListNode> next;
	shared_ptr<ListNode> prev;*/
	weak_ptr<ListNode> next;
	weak_ptr<ListNode> prev;
	int _data;
};

void TestSharedPtr()
{
	shared_ptr<ListNode> sp1(new ListNode(10));
	shared_ptr<ListNode> sp2(new ListNode(20));

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;

	sp1->next = sp2;
	sp2->prev = sp1;

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
}

//shared_ptr会造成循环引用，导致内存泄漏
//C++11引入weak_ptr作用：专门解决shared_ptr中存在的循环引用
//   weak_ptr不能单独管理资源--->配合shared_ptr一起使用
//      weak_ptr没有提供可以接受资源的构造函数
//        weak_ptr，在连接期间，没有增加引用计数--->use_count:1   ?

