#include <iostream>
using namespace std;

//int cnt = 0;  //安全性较低，容易篡改
class Date
{
public:
	
	friend ostream& operator<<(ostream& outputS, Date& d);
	friend istream& operator >> (istream& inputS, Date& d);

	friend class B;

	Date(int year = 2020, int month = 12, int day = 25)
		:_year(year)
		, _month(month)
		, _day(day)

	{
		++cnt;
		cout << "Date(int,int,int)" << endl;
	}

	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._month)
	{
		++cnt;
		cout << "Date(const Date&)" << endl;
	}
	static int getCount()
	{
		return cnt;
	}

	void Display()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
		//非静态成员函数可以访问静态成员函数/变量
		getCount();
		cout << cnt << endl;
	}

	
private:
	//C++11初始化方式：相当于给一个缺省值
	//最后一个候选
	int _year = 1;
	int _month = 1;
	int _day = 1;

public:
	static int cnt;

};
//静态成员必须在类外初始化
int Date::cnt = 0;

//返回输出流是为了支持连续赋值
ostream& operator<<(ostream& outputS, Date& d)
{
	outputS << d._year << "-" << d._month << "-" << d._day << endl;
	return outputS;
}

istream& operator >> (istream& inputS, Date& d)
{
	inputS >> d._year >> d._month >> d._day;
	return inputS;
}


Date fun(Date d)  //拷贝构造
{
	cout << &d.cnt << endl;
	return d; //拷贝构造
}

void test()
{
	Date d;
	Date d2(2020, 5, 26);
}



void test2()
{
	Date d;  //构造
	Date d2 = fun(d);  //拷贝构造  //fun: 进过优化，只有两次拷贝构造：传参， 创建d2
	
	cout << d.getCount() << endl;
	cout << d2.getCount() << endl;
	cout << &d.cnt << endl;
	cout << &d2.cnt << endl;
	// 2. 类名 + 作用域限定符
	cout << &Date::cnt << endl;
	cout << Date::cnt << endl;
	cout << Date::getCount() << endl;
	//普通成员只能通过对象访问，不能通过类名访问
	d.Display();
	//Date::Display(); //不支持
}

void test3()
{
	Date d(2020, 5, 26);
	Date d2(2020, 10, 26);
	//从左向右输出
	cout << d << d2;
	operator<<(operator<<(cout, d), d2);
	//d << cout;
	//从左向右输入
	cin >> d >> d2;// 等价于 operator>>(operator>>(cin, d), d2);
	cout << d << d2;
}

class B
{
public:
	//disPlay, fun, fun1都为Date类的的友元函数
	void disPlay(const Date& d)
	{
		cout << d._year << d._month << d._day << endl;
	}

	void fun(const Date& d)
	{
		cout << d._year << d._month << d._day << endl;
	}

	void fun1(const Date& d)
	{
		cout << d._year << d._month << d._day << endl;
	}
};

void test4()
{
	B b;
	Date d(2020, 5, 26);
	b.disPlay(d);
}

enum Color
{
	BLACK,
	WHITE
};

class C
{
public:
	
	class D
	{
	public:
		void fun(const C& c)
		{
			//可以通过外部类对象访问外部类的私有成员
			cout << c._color << endl;
			cout << c._c << endl;
			cout << c._sc << endl;
			cout << C::_sc << endl;
			//可以直接访问外部类的static成员
			cout << _sc << endl;

		}
	private:
		int _d;
	};
private:
	int _c;
	static int _sc;
	Color _color;
	//内部类可以在类的任何地方定义
	class E
	{
	private:
		int _e;
	};
};

class Solution {
public:
	//内部类
	class Sum
	{
	public:
		Sum()
		{
			//内部类直接访问外部类的私有成员
			_sum += _num;
			++_num;
			cout << "Sum" << endl;
		}
	};
	int Sum_Solution() {
		//重置
		_sum = 0;
		_num = 1;
		Sum sumArray[100];  //调用n次Sum类的构造函数，创建Sum对象数组
		return _sum;
	}
	//private:
	static int _sum;
	static int _num;
};

int Solution::_sum = 0;
int Solution::_num = 1;

void test5()
{
	Solution s;
	int sum = s.Sum_Solution();
	cout << Solution::_num << endl;
	cout << sum << endl;
}
