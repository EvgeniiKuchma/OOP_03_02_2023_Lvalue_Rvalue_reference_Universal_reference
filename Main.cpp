#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
//lvaue and rVALUE reference and universal refference
class Intvec {
public:
	explicit Intvec(size_t num = 0) : m_size(num), m_data(new int[m_size]) {
		log("constructor");
	}
	~Intvec() {
		log("desftructor\n");
		if (m_data) {
			delete[] m_data;
			m_data = 0 ;// nullptr ����� ������������
		}
	}
	Intvec(const Intvec& other) : m_size(other.m_size),
		m_data(new int[m_size]) {
		log("copy constructor");
		for (size_t i = 0; i < m_size; i++) {
			m_data[i] = other.m_data[i];
		}
	}
	Intvec& operator=(Intvec&& other) noexcept {//&& - ������ �� Rvalue(universal reference)//����������� ��������� ������� 1 ��� ���������� ��� ������ ��������� �� �������� �������������� ������ �����������
		//�������� ������������ �����������
		log("move assigment operation");
		std::swap(m_size, other.m_size);
		std::swap(m_size, other.m_size);
		return*this;
	}
	//c1 = c2
	Intvec& operator=(const Intvec& other) 
	{//�������� �������������� ������������
		log("copy assigment operator");
		Intvec tmp(other);
		std::swap(m_size, tmp.m_size);//swap �������� ��� ������������� ������ ������� ������� � ��������� ���������, �� ���� ���������� ����� �������
		std::swap(m_size, tmp.m_size);
		return *this;
	}
private:
	void log(const char* msg) {
		std::cout << "[" << this << "]" << msg//�� �������������� this ������� ����� �������
			<< "\n";
	}
	size_t m_size;
	int* m_data;
};

///////////////////////////////////////////////
class A {
public : 
	void foo() const {
		std::cout << "A::foo() const\n";
	}
	void foo() {
		std::cout << "A::foo()\n";
	}
};
///////////////////////////////////////////////
A Func() { return A(); } // �() - ����� ����������� // ���������� this ->foo()
const A c_aFunc() { return A(); }// ���������� const this -> foo() const

 /*int main() {								
	func().foo();
	c_afunc().foo();
	return 0;
 }*/
///////////////////////////////////////////////
//int& foo1() {
//	
//	return 25;
//}
///////////////////////////////////////////////
int globalvalue = 20;
int& bar() {
	return globalvalue;//��������� ������ - ����� ��������� ,
	//���������� ��� ������ �� int(������ �� ��� ������������� �������� - int&)
};
///////////////////////////////////////////////
int main() 
{
	setlocale(LC_ALL, "russian");
//lvalue - ��� ������ ������� �������� ���������������� ����� � ������, �������� ����� �����
//rvalue - ��� ������ �������  �� �������� ���������������� ����� � ������, �������� ����� �����

	int x = 5;
	//foo1() = 2;
	bar() = 10;
//////////////////////////////////////////////////
	std::string s = "abc";
	s = "a";

std::map<int, float> mymap;
	mymap[10] = 5.6f;//��������[] ������ ���� ������� ������ �� ������ ������� ����� �������
	
	const int a = 11;

	int  t = 1;
	int  tt = 2;
	int res = t + tt;// operator + ������� rvalue, ������� lvalue �� ���� ������������� � rvalue // ��������� �������������� !!�� ���� ����!! �� ����� 
	//a = 10;

	int arr[] = { 1,2 };
	int* p = &arr[0];
	*(p + 1) = 10;//����� �������������� rvalue (p + 1) �  lvalue � ������� *
	//*(p + 1) - lvalue;

	//lvalue in rvalue � ������� ���������� &
	int var = 10;
	//int* bad_addr = &(var + 1);//error: ��� �������� ��������� & ���������  lvalue


	int* addr = &var;//ok
	//&var = 40;// error . need lvalue from left side

	//lvalue �� ��� �( ����� �� ������ ����� ��� ������) �� ���������� 
	// ��������������(��������) ��� ��������, 
	// ����� ���� ������������ � rvalue.<...>
	//���� � �� ����� , ����� rvalue �������� - cv(�������� ������� ���� ���\� �����������, �����������) - �� ����������������� ������ ���� �. 
	//����� ����� rvalue �������� t

	// t lvalue -> t rvalue
	//const volatile t lvalue -> t rvalue
	//���� � ��� ����� �� rvalue ����� ���������  cv �������������������

	//cv: c -const, v -volatile(���������� ������� ���� ��� �� ���� ����� �������� � ����� ������)
//////////////////////////////////////////////////
	std::vector<int> qwe = {1,2,3,4};
	for (size_t i = 0; i < qwe.size(); i++) {/*......*/};//���� ���������� volotile ����� ����� ���� 
	//�� ����� ����������� ����������� �������� ��� ���������� ����� ������� �������(�������� 4)
	//� ����� �������� ��� ���������
//////////////////////////////////////////////////
	Intvec v1(20);
	Intvec v2;
	Intvec v3;

	std::cout << "assigning Lvalue...\n";
	v2 = v1;
	std::cout << "ended assigning Lvalue...\n";
	std::cout << "=========================\n";
	std::cout << "assigning Rvalue...\n";
	v3 = Intvec(33);
	std::cout << "ended assigning Rvalue...\n";
	std::cout << "=========================\n";
	v3 = std::move(v1);//���������� ������ Lvalue � Rvalue(���������� ������ �� Rvalue)//������ v3 ������� ������� v1 
	//v3.operator = (std::move(v1))//Intvec& operator = (Intvec&& v1) {....}
	return 0;
}
	
	
	
