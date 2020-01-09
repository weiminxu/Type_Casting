#include <iostream>

using namespace std;

struct S
{
	int i1;
	int i2;
	char c;
	bool b;
};

int main()
{
	S s;
	s.i1 = 10;
	s.i2 = 20;
	s.c = 'A';
	s.b = true;

	int* pS = reinterpret_cast<int*>(&s);
	cout << *pS <<endl;
	pS++;
	cout << *pS << endl;
	
	char* pSC = reinterpret_cast<char*>(pS);
	cout << pSC << endl;
	
	bool* pSB = reinterpret_cast<bool*>(pSC);
	cout << pSB << endl;

	return 0;
}

