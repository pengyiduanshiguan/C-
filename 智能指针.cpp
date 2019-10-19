#if 0
//auto_ptr��ʵ��ԭ��:����Ȩת�Ƶ�˼��
//ģ��ʵ��һ�ݼ���AutoPtr,�˽�ԭ��
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
	//һ�������������ͽ�ap�е���Դת�Ƶ���ǰ�����У�Ȼ��ap������������Դ�Ͽ���ϵ
	//�����ͽ����һ��ռ䱻�������ʹ�ö���ɳ����������
	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}
	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		//����Ƿ�Ϊ�Լ����Լ���ֵ
		if (this != &ap)
		{
			//�ͷŵ�ǰ��Դ
			if (_ptr)
				delete _ptr;
			//ת��zp����Դ����ǰ������
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
	//�����ٴ�ʵ��ԭ�������ᷢ�֣����������ap�����ָ�븳����
	//ͨ��ap���������Դʱ�ͻ��������
	AutoPtr<Date> copy(ap);
	ap->_year = 2108;
	return 0;
}

#endif

#if 0
//���˼·�������������ǲ��ÿ����͸�ֵ
//ģ��ʵ��
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
	//C++98��������ʽ��ֻ����+��ʵ��+������˽��
	UniquePtr(UniquePtr<T> const&);
	UniquePtr& operator=(UniquePtr<T> const&);

	//C++11�������ķ�ʽ��delete   ��ֹĬ�ϳ�Ա�Ĳ���
	UniquePtr(UniquePtr<T> const&) = delete;
	UniquePtr& operator=(UniquePtr<T> const&) = delete;
private:
	T* _ptr;
};

//ȱ�ݣ�����֮�䲻�ܹ�����Դ

#endif

#if 0
//ģ��ʵ��һ�ݼ򵥵�shard_ptr���˽�ԭ��
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
			//�ͷŹ���ľ���Դ
			Release();

			//��������¶������Դ�����������ü���
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
		//��������ʹ�ü�1��ԭ�Ӳ���
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}

private:
	void Release()
	{
		bool deleteflag = false;
		//���ü�����1���������0�����ͷ���Դ
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
	//�������ü��������ͣ�
	//   ���Ϊ��ͨ���ͱ���int count  sp2(sp1)����sp2�е�count--ʱ��sp1�е�count���ᷢ���仯
	//   �������Ϊstatic int count    shared_ptr <int> sp3 countΪ���������������
	//           ��ôcount���Ϊ1��sp1,sp2�е�countҲ��ı�Ϊ1����ô�ͻ���Ӱ��  
	//����Ӧ������Դ�ҹ������Բ���ָ��ķ�ʽ��ֱ��ָ����Դ�Ŀռ�
	int* _pRefCount;   //���ü���
	T* _ptr;    //ָ�������Դ��ָ��
	mutex* _pMutex;    //������
};

// shared_ptr��������delete malloc  FILE  ����delete[]����ֱ����vector����
//��Դ�����ͣ�new�Ķѿռ�  delete�Ķѿռ�   �ļ�ָ��   �׽���

//shared_ptr:����ɾ��     ��shared_pt�ͷ���Դ�ķ�ʽ�����÷º���
//   ������Դ�����û�������Դ������ѡ����ʵķ�ʽ�����ͷ�

//�̰߳�ȫ���⣺
//       
 
//����˫������---ѭ������
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
	//����ѭ������
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

//shared_ptr�����ѭ�����ã������ڴ�й©
//C++11����weak_ptr���ã�ר�Ž��shared_ptr�д��ڵ�ѭ������
//   weak_ptr���ܵ���������Դ--->���shared_ptrһ��ʹ��
//      weak_ptrû���ṩ���Խ�����Դ�Ĺ��캯��
//        weak_ptr���������ڼ䣬û���������ü���--->use_count:1   ?

