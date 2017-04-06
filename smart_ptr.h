#pragma once
#include<stdio.h>
//auto_ptr实现的智能指针 其中的  不涉及的深拷贝 ，，，，有缺陷 
template<class T>
class  auto_ptr
{
public:
	//定义成显式的构造函数，，， 用防止类型的隐式转换
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


//相对于auto_ptr来说的话 ，，，，增加了  一个变量来表示指针的合法性 
//一个智能指针真正代表的只有一个 ，，，，那就是最新定义，，，或者赋值的那个 对象 
//但是还是存在的是    深浅拷贝的问题
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
		,_owner(true)//将最新拷贝定义的对象    设置为  true
	{
		if(ap._owner == true)
		{
			ap._owner = false;//旧的对象    设置为 false
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
			_owner = true;//新的设置成  true
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
	bool _owner;//记录当前指针的合法
};



//对于上面的智能指针产生的问题 ，，，都是由于的是 拷贝还有   赋值引发的深浅拷贝问题 
//导致的是 对象析构是的指针释放的问题 。。。。。
//所以就又产生了   一个新的指针，，，那就是 scoped_ptr
//用来     防止拷贝与 赋值


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
	//将拷贝与赋值定义成私有的，，，就能防止拷贝
	scoped_ptr(const  scoped_ptr<T> &  ap);
	scoped_ptr<T>&  operator=(const  scoped_ptr<T> & ap);
protected:
	 T* _ptr;
};



//上面的智能指针只能用来  表示的是 单个   对象的指针
//下面我们就来 表示的是 一个可以用来表示数组指针的    智能指针


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


//为了解决的上述的深浅拷贝    释放时的问题 ，，我们可以   使用引用计数来
//解决这个问题
//定制删除器   比如  我们需要智能只在乎你管理的是    一个文件指针
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