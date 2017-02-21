/*!
 * \file main.cpp
 * \date 2017/02/20 20:10
 *
 * \author henry
 * Contact: henrytien@hotmail.com
 *
 * \brief
 *
 * TODO: long description
 *
 * \note
*/
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::endl;
using std::cout;

class String
{
public:
	String()
		:_Pstr(new char[1]) {
		cout << "String ()" << endl;
	}

	String & operator=(const String &rhs) {

		if (this == &rhs) {  // 自复制
			delete[] _Pstr; // 释放原对象
			_Pstr = new char[strlen(rhs._Pstr) + 1];  // 再去复制
			strcpy(_Pstr, rhs._Pstr);
		}
		return (*this);
	}

	String(const char *Pstr)
		:_Pstr(new char[strlen(Pstr) + 1]) {
		strcpy(_Pstr, Pstr);
		cout << "String(const char *Pstr)" << endl;
	}


	~String() {
		delete[] _Pstr;
		cout << "~String()" << endl;
	}
#if 0
	String(const String &rhs)
		:_Pstr(rhs._Pstr) { // 浅拷贝


	}

#endif
	void print() {

		cout << _Pstr << endl;
	}
private:

	char * _Pstr;
};


int main() {


	String s1 = "hello";
	String s2 = "how ";
	s1 = s1;
	s1 = s2;

	printf("%p\n", s1);
	printf("%s\n", s2);
	system("pause");
	return 0;
}