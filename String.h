#pragma  once 
#include <assert.h>
//说道string类的两个主要考点就是 
//深拷贝
//浅拷贝   写实拷贝 ()


//深拷贝
class String 
{
public:
	String(const  char  * str = "")
	{
		//要是传进来的字符串为 NULL
		if(str == NULL)
		{
			//我们需要创建一个内容为 /0的字符串
			_str  =new char [1];
			*_str  = '/0';
		}
		else
		{
			//否则，，，开辟一个长度为 str长度+1； 
			_str  = new char [strlen(str)+1];
			strcpy(_str,str);  
		}
	}

	//深拷贝的拷贝构造函数 
	//String(const  String &  str)
	//	:_str(new char[strlen(str._str)+1])
	//{
	//	//先为字符串开辟一个空间
	//	//将内部的数据拷贝
	//	strcpy(_str,str._str);
	//}

	//简介版 的拷贝构造函数 

	String (const String &  str)
		:_str(NULL)//现将当前的对象的字符串的指针赋为空 ，，，必须要写 
	{
		//使用的是 str内部的字符串的指针，，来构造一个新的对象 str1；
		String  str1(str._str);
		//将当前的对象的_str  与  重新生成的新对象的_str 交换
		swap(_str,str1._str);
	}
	
	//深拷贝的赋值运算符的重载
	//String & operator = (const  String  &  str)
	//{
	//	if(this!= &str)
	//	{
	//		//开辟一个空间 
	//		char *  tmp  =new char[strlen(str._str)+1];
	//		//将原来的空间释放
	//		delete[]_str;
	//		//将内容拷贝到所开辟的位置 
	//		strcpy(tmp,str._str);
	//		//将开辟的空间给当前的类
	//		_str = tmp;
	//	}
	//	return *this;
	//}

	//简介版 的赋值运算符的重载
	String &    operator =(const  String  &  str)
	{
		//防止自己给自己赋值
		if(this  != &  str)
		{
			String str1(str);//使用拷贝构造函数  ，，，来生成一个新的对象 
			//先将当前对象的_str释放 ，，，，并且赋值成 NULL
			delete[]  _str;
			_str = NULL;
			swap(_str,str1._str);
		}
		return  *this;
	}
	~String()
	{
		if(_str != NULL)
		{
			delete []  _str;
		}
		_str   =NULL;
	}


	//重载【】
	char & operator[](size_t n)
	{
		assert(n < strlen(_str) );
		return  *(_str+n);
	}
protected:
	char  *_str;
};



//引用计数的浅拷贝     写实拷贝
class StringS
{
public:
	StringS(const  char  * str = "")
	{
		//要是传进来的字符串为 NULL
		if(str == NULL)
		{
			//我们需要创建一个内容为 /0的字符串
			_str  =new char [1];
			*_str  = '/0';
		}
		else
		{
			//否则，，，开辟一个长度为 str长度+1； 
			_str  = new char [strlen(str)+1];
			strcpy(_str,str);  
		}
		_count = new int(1);
	}

	//拷贝构造函数 
	StringS(const  StringS &  str)
		:_str (str._str)
		,_count(str._count)
	{
		(*_count)++;
	}
	//带有引用计数的赋值运算符的重载 
	StringS &  operator=( const StringS  &  str)
	{
		if(_str !=  str._str)
		{
			if(*_count == 1)
			{
				delete[] _str;
				_str  =  str._str;
			}
			else
			{
				(*_count)--;
				_str  = str._str;
			}
			_count  = str._count;
			(*_count) ++;
		}
		return  *this;
	}
	~StringS()
	{
		if(*_count == 1)
		{
			delete[] _str;
			delete _count;
		}
		else
		{
			(*_count) --;
		}
		_str = NULL;
		_count =NULL;
	}


	//写实拷贝 
	//当某个对象要进行 写的话   ，，，就要对其 单独进行拷贝 
	char & operator[](size_t  n)
	{
		assert(n < strlen(_str) );
		if(*_count != 1)//如果这个数 多个 对象使用的话 
		{
			char  *  tmp  = new  char[strlen(_str)+1];
			strcpy(tmp,_str);
			_str  =  tmp;
			(*_count)--;
			_count  = new int(1);
		}
		return *(_str+n);
	}
protected:
	char *  _str;
	int  *  _count ;//表示的是 引用计数

};
void testString()
{
	String  st(NULL);
	String  st1;
	String  st2("we are happy");
	String  st3(st2);
	st1 = st3;
}
void testStringS()
{
	StringS  st(NULL);
	StringS  st1;
	StringS  st2("we are happy");
	StringS  st3(st2);
	st1 = st3;
	st2[2];
}