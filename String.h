#pragma  once 
#include <assert.h>
//˵��string���������Ҫ������� 
//���
//ǳ����   дʵ���� ()


//���
class String 
{
public:
	String(const  char  * str = "")
	{
		//Ҫ�Ǵ��������ַ���Ϊ NULL
		if(str == NULL)
		{
			//������Ҫ����һ������Ϊ /0���ַ���
			_str  =new char [1];
			*_str  = '/0';
		}
		else
		{
			//���򣬣�������һ������Ϊ str����+1�� 
			_str  = new char [strlen(str)+1];
			strcpy(_str,str);  
		}
	}

	//����Ŀ������캯�� 
	//String(const  String &  str)
	//	:_str(new char[strlen(str._str)+1])
	//{
	//	//��Ϊ�ַ�������һ���ռ�
	//	//���ڲ������ݿ���
	//	strcpy(_str,str._str);
	//}

	//���� �Ŀ������캯�� 

	String (const String &  str)
		:_str(NULL)//�ֽ���ǰ�Ķ�����ַ�����ָ�븳Ϊ�� ����������Ҫд 
	{
		//ʹ�õ��� str�ڲ����ַ�����ָ�룬��������һ���µĶ��� str1��
		String  str1(str._str);
		//����ǰ�Ķ����_str  ��  �������ɵ��¶����_str ����
		swap(_str,str1._str);
	}
	
	//����ĸ�ֵ�����������
	//String & operator = (const  String  &  str)
	//{
	//	if(this!= &str)
	//	{
	//		//����һ���ռ� 
	//		char *  tmp  =new char[strlen(str._str)+1];
	//		//��ԭ���Ŀռ��ͷ�
	//		delete[]_str;
	//		//�����ݿ����������ٵ�λ�� 
	//		strcpy(tmp,str._str);
	//		//�����ٵĿռ����ǰ����
	//		_str = tmp;
	//	}
	//	return *this;
	//}

	//���� �ĸ�ֵ�����������
	String &    operator =(const  String  &  str)
	{
		//��ֹ�Լ����Լ���ֵ
		if(this  != &  str)
		{
			String str1(str);//ʹ�ÿ������캯��  ������������һ���µĶ��� 
			//�Ƚ���ǰ�����_str�ͷ� �����������Ҹ�ֵ�� NULL
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


	//���ء���
	char & operator[](size_t n)
	{
		assert(n < strlen(_str) );
		return  *(_str+n);
	}
protected:
	char  *_str;
};



//���ü�����ǳ����     дʵ����
class StringS
{
public:
	StringS(const  char  * str = "")
	{
		//Ҫ�Ǵ��������ַ���Ϊ NULL
		if(str == NULL)
		{
			//������Ҫ����һ������Ϊ /0���ַ���
			_str  =new char [1];
			*_str  = '/0';
		}
		else
		{
			//���򣬣�������һ������Ϊ str����+1�� 
			_str  = new char [strlen(str)+1];
			strcpy(_str,str);  
		}
		_count = new int(1);
	}

	//�������캯�� 
	StringS(const  StringS &  str)
		:_str (str._str)
		,_count(str._count)
	{
		(*_count)++;
	}
	//�������ü����ĸ�ֵ����������� 
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


	//дʵ���� 
	//��ĳ������Ҫ���� д�Ļ�   ��������Ҫ���� �������п��� 
	char & operator[](size_t  n)
	{
		assert(n < strlen(_str) );
		if(*_count != 1)//�������� ��� ����ʹ�õĻ� 
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
	int  *  _count ;//��ʾ���� ���ü���

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