#include <string>
#include <iostream>

#include "Polinom.h"

using std::string;
using std::cout;
using std::endl;

int main()
{
	string s2 = "2 + xyz+x2yz";
	string s1 = "x^1*y1z+xy2z";


	Polinom a(s1);
	Polinom b(s2);
	cout << endl << a << endl;
	cout << endl << b << endl;
	cout << endl << a + b << endl;
	cout << endl << a * b << endl;


	return 0;
}