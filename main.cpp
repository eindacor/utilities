#include "headers.h"
#include "bignum_decs.h"

int main()
{
	bigNumber test1(1);
	bigNumber test2(32);
	bigNumber test7(2);

	int n=78;
	int r=5;

	bigNumber test5(n);
	bigNumber test6(r);
	bigNumber itTest = iterations(test5, test6);
	cout << n << "c" << r << " = ";
	itTest.printNumber();
	cout << endl;
	
	bigNumber quotient = test1 / test2;
	test1.printNumber();
	cout << " / ";
	test2.printNumber();
	cout << " = ";
	quotient.printNumber();
	cout << endl;

	bigNumber quotient2 = quotient / test7;
	quotient.printNumber();
	cout << " / ";
	test7.printNumber();
	cout << " = ";
	quotient2.printNumber();
	cout << endl;

	bigNumber test3 = test1 * test2;
	bigNumber test4 = test3 * 85;
	test3.printNumber();
	cout << " * 85 = ";
	test4.printNumber();

	cout << endl;
	bigNumber quotient3 = test4 / test1;
	test4.printNumber();
	cout << " / ";
	test1.printNumber();
	cout << " = ";
	quotient3.printNumber();
	cout << endl;

	cout << endl;
	bigNumber newNumber = quotient * 12;
	quotient.printNumber();
	cout << " * 12 = ";
	newNumber.printNumber();

	cout << endl;
	return 0;
}












