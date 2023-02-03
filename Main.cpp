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
			m_data = 0 ;// nullptr лучше использовать
		}
	}
	Intvec(const Intvec& other) : m_size(other.m_size),
		m_data(new int[m_size]) {
		log("copy constructor");
		for (size_t i = 0; i < m_size; i++) {
			m_data[i] = other.m_data[i];
		}
	}
	Intvec& operator=(Intvec&& other) noexcept {//&& - ссылка на Rvalue(universal reference)//значительно сокращает расходы 1 раз вызываются все методы позволяет не создавть дополнительный обьект копирования
		//оператор присваивания пермещением
		log("move assigment operation");
		std::swap(m_size, other.m_size);
		std::swap(m_size, other.m_size);
		return*this;
	}
	//c1 = c2
	Intvec& operator=(const Intvec& other) 
	{//оператор присваиванивая копированием
		log("copy assigment operator");
		Intvec tmp(other);
		std::swap(m_size, tmp.m_size);//swap позволит при непрохождении замены вернуть значеие к исходному состоянию, то есть безопасный обмен данными
		std::swap(m_size, tmp.m_size);
		return *this;
	}
private:
	void log(const char* msg) {
		std::cout << "[" << this << "]" << msg//не разименованный this выведет адрес обьекта
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
A Func() { return A(); } // А() - вызов конструктра // возвращает this ->foo()
const A c_aFunc() { return A(); }// возвращает const this -> foo() const

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
	return globalvalue;//результат работы - адрес перменной ,
	//возвращает тип ссылка на int(ссылка на тип возвращаемого значения - int&)
};
///////////////////////////////////////////////
int main() 
{
	setlocale(LC_ALL, "russian");
//lvalue - это обьект который занимает идентифицируемое место в памяти, например имеет адрес
//rvalue - это обьект который  не занимает идентифицируемое место в памяти, например имеет адрес

	int x = 5;
	//foo1() = 2;
	bar() = 10;
//////////////////////////////////////////////////
	std::string s = "abc";
	s = "a";

std::map<int, float> mymap;
	mymap[10] = 5.6f;//оператор[] внутри мапы вернулл ссылку на обьект который можно изменть
	
	const int a = 11;

	int  t = 1;
	int  tt = 2;
	int res = t + tt;// operator + ожидает rvalue, поэтому lvalue не явно преобразуется в rvalue // обратного перобразовнаия !!не явно быть!! не может 
	//a = 10;

	int arr[] = { 1,2 };
	int* p = &arr[0];
	*(p + 1) = 10;//явное преобразование rvalue (p + 1) в  lvalue с помощью *
	//*(p + 1) - lvalue;

	//lvalue in rvalue с помощью амперсанта &
	int var = 10;
	//int* bad_addr = &(var + 1);//error: для унарного оператора & требуется  lvalue


	int* addr = &var;//ok
	//&var = 40;// error . need lvalue from left side

	//lvalue на тип т( далее по тексту любой тип данных) не являющимся 
	// функциональным(функцией) или массивом, 
	// может быть преобразован в rvalue.<...>
	//если т не класс , типом rvalue является - cv(свойства обьекта быть или\и константным, волотильным) - не специфицированная версия типа т. 
	//иначе типом rvalue является t

	// t lvalue -> t rvalue
	//const volatile t lvalue -> t rvalue
	//если т это класс то rvalue может сохранить  cv специфицированность

	//cv: c -const, v -volatile(переменные которые явно или не явно могут изменены в любой момент)
//////////////////////////////////////////////////
	std::vector<int> qwe = {1,2,3,4};
	for (size_t i = 0; i < qwe.size(); i++) {/*......*/};//если обьявлеяем volotile тогда метод сайз 
	//не будет подставлять константные значения для нахождения конца размера массива(например 4)
	//а будет работать как задуманно
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
	v3 = std::move(v1);//Превращает ссылку Lvalue в Rvalue(возвращает ссылку на Rvalue)//теперь v3 владеет данными v1 
	//v3.operator = (std::move(v1))//Intvec& operator = (Intvec&& v1) {....}
	return 0;
}
	
	
	
