#pragma once
#include<stdio.h>
//auto_ptrʵ�ֵ�����ָ�� ���е�  ���漰����� ����������ȱ�� 
template<class T>
class  auto_ptr
{
public:
	//�������ʽ�Ĺ��캯�������� �÷�ֹ���͵���ʽת��
	explicit  auto_ptr(T* ptr  = NULL)
		:_ptr(ptr)
	{}
	~auto_ptr()
	{
		if(_ptr)
		{
			delete _ptr;
		}
		_ptr = NULL;
	}
	T& operator*(){};
	T* operator->(){};
protected:
	T* _ptr;
};


//�����auto_ptr��˵�Ļ� ��������������  һ����������ʾָ��ĺϷ��� 
//һ������ָ�����������ֻ��һ�� ���������Ǿ������¶��壬�������߸�ֵ���Ǹ� ���� 
//���ǻ��Ǵ��ڵ���    ��ǳ����������
template<class T>
class unique_ptr
{
public:
	explicit  unique_ptr(T* ptr =NULL)
		:_ptr(ptr)
		,_owner(true)
	{}
	unique_ptr(unique_ptr<T> & ap)
		:_ptr(ap._ptr)
		,_owner(true)//�����¿�������Ķ���    ����Ϊ  true
	{
		if(ap._owner == true)
		{
			ap._owner = false;//�ɵĶ���    ����Ϊ false
		}
		else
		{
			_ptr = NULL;
			_owner = false;
		}
		
	}

	unique_ptr<T> & operator=(const  unique_ptr<T> & ap)
	{
		if(ap._owner == true&&_ptr != ap._ptr)
		{
			if(_ptr && _owner == true)
			{
				delete _ptr;
			}
			_ptr  = ap._ptr;
			_owner = true;//�µ����ó�  true
			ap._owner  =false;
		}
		return *this;
	}


	~unique_ptr()
	{
		if(_ptr && _owner == true)
		{
			delete _ptr;
		}
		_ptr  =NULL;
		_owner  =false;
	}

protected:
	T*  _ptr;
	bool _owner;//��¼��ǰָ��ĺϷ�
};



//�������������ָ����������� �������������ڵ��� ��������   ��ֵ��������ǳ�������� 
//���µ��� ���������ǵ�ָ���ͷŵ����� ����������
//���Ծ��ֲ�����   һ���µ�ָ�룬�����Ǿ��� scoped_ptr
//����     ��ֹ������ ��ֵ


template<class T>
class scoped_ptr
{
public:
	explicit scoped_ptr(const  T* ptr = NULL)
		:_ptr(ptr)
	{}
	~scoped_ptr()
	{
		if(_ptr)
		{
			delete _ptr;
		}
		_ptr =NULL;
	}
protected:
	//�������븳ֵ�����˽�еģ��������ܷ�ֹ����
	scoped_ptr(const  scoped_ptr<T> &  ap);
	scoped_ptr<T>&  operator=(const  scoped_ptr<T> & ap);
protected:
	 T* _ptr;
};



//���������ָ��ֻ������  ��ʾ���� ����   �����ָ��
//�������Ǿ��� ��ʾ���� һ������������ʾ����ָ���    ����ָ��


template<class T>
class scoped_array
{
public:
	explicit scoped_array(const  T*  array =NULL)
		:_array(array)
	{}
	~scoped_array()
	{
		delete[] _array;
	}
protected:
	scoped_array(const scoped_array<T> &  ay);
	scoped_array&  operator=(const scoped_array<T> &  ay);
protected:
	T*  _array;
};


//Ϊ�˽������������ǳ����    �ͷ�ʱ������ �������ǿ���   ʹ�����ü�����
//����������
//����ɾ����   ����  ������Ҫ����ֻ�ں���������    һ���ļ�ָ��
template<class T,class D = void*>
class shared_ptrDel
{
public:
	explicit shared_ptrDel(T* ptr,D del)
		:_ptr(ptr)
		,_count(NULL)
		,_del(del)
	{
		if(_ptr)
			_count = new  int(1);
	}
	shared_ptrDel(const shared_ptrDel<T,D>& sp)
		:_ptr(sp._ptr)
		,_count(sp._count)
		,_del(sp._del)
	{
		if(_ptr)
		{
			(*_count)++;
		}
	}

	shared_ptrDel<T,D> & operator=(const shared_ptrDel<T,D>& sp )
	{
		if(_ptr!= sp._ptr)
		{
			if(*_count == 1)
			{
				del(_ptr);
				delete _count;
			}
			_ptr = sp._ptr;
			_count = sp._count;
			_del = sp._del;
			if(_ptr)
			{
				*(_count)++;	
			}	 
		}
		return *this;
	}
	~shared_ptrDel()
	{
		if(_ptr)
		{
			if(*_count == 1)
			{
				_del(_ptr);			
				delete _count;
			}
			else
			{
				(*_count )--;
			}
		}
		
		_ptr =NULL;
		_count  =NULL;	
	}

protected:
	T* _ptr;
	int *  _count;
	D  _del;
};


template<class T>
class shared_ptr
{
public:
	explicit shared_ptr(T* ptr =NULL)
		:_ptr(ptr)
		,_count(NULL)
		
	{
		if(_ptr)
			_count = new  int(1);
	}
	
	shared_ptr(const shared_ptr<T>& sp)
		:_ptr(sp._ptr)
		,_count(sp._count)
	{
		if(_ptr)
		{
			(*_count)++;
		}
	}

	shared_ptr<T>& operator=(const shared_ptr<T>& sp )
	{
		if(_ptr!= sp._ptr)
		{
			if(*_count == 1)
			{
				delete _ptr;
				delete _count;
			}
			_ptr = sp._ptr;
			_count = sp._count;
			if(_ptr)
			{
				(*_count)++;	
			}	 
		}
		return *this;
	}
	~shared_ptr()
	{	
		if(_ptr)
		{
			if(*_count == 1)
			{
				delete _ptr;
				delete _count;
			}
			else
			{
				(*_count )--;
			}
		}
		
		_ptr =NULL;
		_count  =NULL;	
	}

protected:
	T* _ptr;
	int *  _count;
	
};
void test()
{
	auto_ptr<int> ptr(new int(1));
	unique_ptr<int> ptr1(new int(2));
	unique_ptr<int> ptr2(ptr1);
	unique_ptr<int> ptr3 = ptr2;



	FILE * fp  = fopen("123.txt","w");
	shared_ptr<int>  ptr4(new int(3));
	shared_ptr<int>  ptr5(ptr4);
	shared_ptr<int>  ptr6(new int(5));
	ptr6 = ptr5;
	struct Fclose
	{
		void operator()(FILE* ptr)
		{
			fclose(ptr);
		}
	};
	shared_ptrDel<FILE,Fclose> ptr7(fp,Fclose());
}