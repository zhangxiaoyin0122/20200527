#include <iostream>
using namespace std;

//int cnt = 0;  //��ȫ�Խϵͣ����״۸�
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
		//�Ǿ�̬��Ա�������Է��ʾ�̬��Ա����/����
		getCount();
		cout << cnt << endl;
	}

	
private:
	//C++11��ʼ����ʽ���൱�ڸ�һ��ȱʡֵ
	//���һ����ѡ
	int _year = 1;
	int _month = 1;
	int _day = 1;

public:
	static int cnt;

};
//��̬��Ա�����������ʼ��
int Date::cnt = 0;

//�����������Ϊ��֧��������ֵ
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


Date fun(Date d)  //��������
{
	cout << &d.cnt << endl;
	return d; //��������
}

void test()
{
	Date d;
	Date d2(2020, 5, 26);
}



void test2()
{
	Date d;  //����
	Date d2 = fun(d);  //��������  //fun: �����Ż���ֻ�����ο������죺���Σ� ����d2
	
	cout << d.getCount() << endl;
	cout << d2.getCount() << endl;
	cout << &d.cnt << endl;
	cout << &d2.cnt << endl;
	// 2. ���� + �������޶���
	cout << &Date::cnt << endl;
	cout << Date::cnt << endl;
	cout << Date::getCount() << endl;
	//��ͨ��Աֻ��ͨ��������ʣ�����ͨ����������
	d.Display();
	//Date::Display(); //��֧��
}

void test3()
{
	Date d(2020, 5, 26);
	Date d2(2020, 10, 26);
	//�����������
	cout << d << d2;
	operator<<(operator<<(cout, d), d2);
	//d << cout;
	//������������
	cin >> d >> d2;// �ȼ��� operator>>(operator>>(cin, d), d2);
	cout << d << d2;
}

class B
{
public:
	//disPlay, fun, fun1��ΪDate��ĵ���Ԫ����
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
			//����ͨ���ⲿ���������ⲿ���˽�г�Ա
			cout << c._color << endl;
			cout << c._c << endl;
			cout << c._sc << endl;
			cout << C::_sc << endl;
			//����ֱ�ӷ����ⲿ���static��Ա
			cout << _sc << endl;

		}
	private:
		int _d;
	};
private:
	int _c;
	static int _sc;
	Color _color;
	//�ڲ������������κεط�����
	class E
	{
	private:
		int _e;
	};
};

class Solution {
public:
	//�ڲ���
	class Sum
	{
	public:
		Sum()
		{
			//�ڲ���ֱ�ӷ����ⲿ���˽�г�Ա
			_sum += _num;
			++_num;
			cout << "Sum" << endl;
		}
	};
	int Sum_Solution() {
		//����
		_sum = 0;
		_num = 1;
		Sum sumArray[100];  //����n��Sum��Ĺ��캯��������Sum��������
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
