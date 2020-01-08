#include <iostream>

using namespace std;

//conversion provided through conversion operator or conversion constructor
class A
{
private:
	int x;

public:
	A(int i) :x(i)
	{
		cout << "conversion ctr" << endl;
	}
	operator string()
	{
		cout << "conversion operator" << endl;
		return to_string(x);
	}


};


int main()
{
	/*
		Type Promotion:
		bool->char->short int->int->unsigned int->long->unsigned->long long->float->double->long double

		1)C-Stple cast
		2)Using casting operator:
		  (1)static_cast<>
		  (2)dynamic_cast<>
		  (3)const_cast<>
		  (4)reinterpret_cast<>
	*/

	float a = 2.0;
	int b = 2;
	int c = 3;

	int d1 = a + b;
	float e1 = c / b;

	cout << "d1 = " << d1 << endl;
	cout << "e1 = " << e1 << endl;

	//C Style Casting (data_type) Expression
	float d2 = a + (float)b;
	float e2 = (float)(c / b);

	cout << "d2 = " << d2 << endl;
	cout << "e2 = " << e2 << endl;

	//static_cast<type>(expression), implicit conversions between types
	float f = 10.5;
	int i1;
	int i2;

	i1 = f;
	i2 = static_cast<int>(f);
	cout << "i1 = " << i1 << endl;
	cout << "i2 = " << i2 << endl;

	//prevent dangerous casts -- more restrictive
	char c;
	int* p1 = (int*)(&c);
	*p1 = 3; //pass at compile time, fall at run-time
	int* p2 = static_cast<int*>(&c); //compile-time error

	//converting to void* or from void*
	int i = 10;
	void* v = static_cast<void*>(&i);
	int* p = static_cast<int*>(v);

	//conversins invlving inheritance: is-a
	/*
		class A{}
		class B:private A{}
	*/
	B b;
	A* aptr1 = (A*)(&b); //allowed
	A* aptr2 = static_cast<A*>(&b);//error: 'A' is an inaccessible base of 'B'

	//private inheritance: not is-a but has-a
	/*
		class person{}
		class student:private person{}

		void eat(const person& p){} // anyone can eat
		void study(const student& s){} //only students study
	*/
	person p;//p is a person
	student s; //s is a student
	eat(p); //fine, p is a person
	eat(s); //error, s is not a person

	//conversions involving inheritance: is-a
	/*
		class A{}
		class B:private A{}
	*/
	B b;
	A* aptr = (A*)(&b); //allowed
	A* aptr1 = static_cast<A*>(&b); //error, 'A' is an inaccessible base of 'B'

	/*****************************RTTI********************************************************/
	//run time type identification
	//provide a standard way for a program to determine the type of object during runtime
	//RTTI is provided through two operators:
	//1)typeid operator, returns the actual type of object referred to by pointer (or reference)
	//2)dynamic_cast operator, safely converts from pointer (or reference) to base type to pointer
	//  (or reference) to a derived type


	/******************************Dynamic_cast************************************************/
	//dynamic_cast<new_type>(expression)
	//involves a run-time type check
	//base class has to be polymorphic
	//on success returns a value of new_type
	//on failure:
	//1)if new_type is pointer->null pointer
	//2)if new_type is reference->bad_cast exception
	/*
	class Base{}
	class Base{virtual void f(){}}
	class Derived:public Base{}
	*/
	Base b;
	Derived d;
	Base* ph = dynamic_cast<Base*>(&d);
	Derived* pd = dynamic_cast<Derived*>(&b);// Quiz:will it compile?

	Base* pBD = new Derived;
	Base* pBB = new Base;
	Derived* pd;
	pd = dynamic_cast<Derived*>(pBD);
	pd = dynamic_cast<Derived*>(pBB);

	Derived d2;
	Base b2;
	try
	{
		Base& rb = dynamic_cast<Base&>(d2);
		Derived& rd = dynamic_cast<Derived&>(b2); //exception bad_cast
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}

	/*****************************const_cast*******************************************************/
	//const_cast<new_type>(expression)
	//used to cast away the constness of variables
	//passing const data to a function that does not recerive const
	/*
		int fun(int* ptr)
		{
			return (*ptr)
		}
	*/
	const int val = 5;
	const int* ptr = &val;
	int* ptr1 = const_cast<int*>(ptr);
	cout << fun(ptr1);

	//change non-const class members inside a const member function
	/*
	class A
	{
	private:
		int x;
	public:
		void f(int) const
		{
			//this->x=i; //error
			const_cast<A*>(this)->x = i;	
		}
	}
	*/

	//undefined behaviour to modify a value initially declared as const
	//except that any class member declared mutable can be modified, any
	//attempt to modify
	const int a1 = 10;
	const int* p1 = &a1;
	int* p2 = const_cast<int*>(p1);
	*p2 = 20;

	cout << *p2 << endl;
	cout << a1 << endl;

	//can not cast to a type different from original object
	int a = 40;
	const int* b = &a;
	char* c = const_cast<char*>(b); //compiler error


	/****************************reinterpret_cast***********************************************/
	//reinterpret_cast<new_type>(expression)
	1)allows any pointer to be coverted into any other pointer type
	2)allows any integral type to be converted into any pointer typeand vice versa.
	int a1 = 70;
	int* p1 = &a1;
	char* pc = reinterpret_cast<char*>(p1);
	cout << *pc << endl;

	int* p2 = reinterpret_cast<int*>(a);
	cout << p2 << endl;
	cout << reinterpret_cast<long>(p2) << endl;
	//cout << reinterpret_cast<int>(p2) << endl;//error:cast from pointer to smaller type 'int' loses information
	//cout << sizeof(int*) << "  " << sizeof(int) << sizeof(long) << endl;


	//inheretly unsafe conversions

	//the reinterpret_cast operator can be used for conversions, such as:1)char* to int* 2)one_class* to unrelated_class*
	//which are inherently unsafe

	//the result of a reinterpret_cast can not safely be used for anything other than being cast back to its original
	//type, other uses are, at best, nonportable.
	/*
	class A
	{
	private:
		int x1;
		int x2;
	public:
		A():x1(10), x2(20){}
		void printA()
		{
			cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
		}
	}
	
	class B
	{
	private:
		char c;
	public:
		B():c('A'){}
		void printB()
		{
			cout << "c= " << c << endl;
		}
	}
	*/
	A a;
	B b;
	A* pA = reinterpret_cast<A*>(&b);
	B* pB = reinterpret_cast<B*>(&a);
	pA->printA();
	pB->printB();
	A* pA1 = reinterpret_cast<A*>(pB);
	B* pB1 = reinterpret_cast<B*>(pA);
	pA1->printA();
	pB1->printB();

	//can not away the const, volatile, or _unaligned attributes
	int a;
	const int* ap = &a;
	char* pc = reinterpret_cast<char*>(ap);
	const char* pc = reinterpret_cast<const char*>(ap);

	//working with bits
	/*
	struct S
	{
		int i1;
		int i2;
		char c;
		bool b;
	}
	*/
	S s;
	s.i1 = 10;
	s.i2 = 20;
	s.c = 'A';
	s.b = true;

	int* pS = reinterpret_cast<int*>(&s);
	cout << *pS << endl;
	pS++;
	cout << *pS << endl;
	char* pSC = reinterpret_cast<int*>(pS);
	cout << *pSC << endl;
	pSC++;
	//char* pSB = reinterpret_cast<bool*>(pSC);//error: can not initialize a variable of type 'char*' with an rvalue of type
	bool* pSB = reinterpret_cast<bool*>(pSC);
	cout << *pSB << endl;






	return 0;
}