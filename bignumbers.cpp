#include <iostream>
#include <vector>

#define MAXDIGITS 100

#define DEBUG

#ifdef DEBUG
#define DECLARE(x) cout << "\t|  DECLARATION: " << x << endl;
#else
#define DECLARE(x)
#endif

using std::cout;
using std::cin;
using std::endl;
using std::vector;


class bigNumber
{
	public:
		bigNumber(vector<int> n);
		~bigNumber() {};

		int getDigit(int n) {return digits[n];}

		int getDigitCount();
		
		void printNumber();

		bool getNegative() {return negative;}

	private:
		int digits[MAXDIGITS];
		int digitCount;
		bool negative;
};

bigNumber::bigNumber(vector<int> n)
{
	for (int i=0; i<MAXDIGITS; i++)
	{
		digits[i] = 0;
	}

	int count=0;

	for (vector<int>::iterator i=n.begin(); i!=n.end(); i++)
	{
		digits[count] = (*i);
		cout << "adding " << *i << endl;
		count++;
	}

	digitCount = count;
}

int bigNumber::getDigitCount()
{
	for (int i=MAXDIGITS-1; i>=0; i--)
	{
		if (getDigit(i)>0)
		{
			return i+1;
		}
	}

	return 0;
}

void bigNumber::printNumber()
{
	int comma = digitCount % 3;

	for (int i=0; i<digitCount; i++)
	{
		if (i>0 && comma==0)
		{
			cout << ",";
			comma = 3;
		}

		cout << digits[digitCount-i-1];

		comma--;
	}
}

bigNumber addNumbers(bigNumber bn1, bigNumber bn2)
{
	vector<int> temp;
	int carry=0;

	for (int i=0; i<MAXDIGITS; i++)
	{
		int tempNumber = bn1.getDigit(i) + bn1.getDigit(i);
		
		tempNumber += carry;

		if (tempNumber>9)
		{
			tempNumber-=10;
			carry = 1;
		}

		else 
		{
			carry = 0;
		}

		temp.push_back(tempNumber);
	}

	return bigNumber(temp);
}

bigNumber subtractNumbers(bigNumber bn1, bigNumber bn2)
{
	vector<int> temp;
	int carry=0;

	for (int i=0; i<MAXDIGITS; i++)
	{
		int tempNumber = bn1.getDigit(i) - bn1.getDigit(i);
		
		tempNumber -= carry;

		if (tempNumber<0)
		{
			tempNumber+=10;
			carry = 1;
		}

		else 
		{
			carry = 0;
		}

		temp.push_back(tempNumber);
	}

	return bigNumber(temp);
}

int main()
{
	vector<int>firstVector;

	firstVector.push_back(1);
	firstVector.push_back(2);
	firstVector.push_back(3);
	firstVector.push_back(4);
	firstVector.push_back(5);
	firstVector.push_back(6);
	
	for (int i=0; i<6; i++)
	{
		cout << "firstVector.at(" << i << "): " << firstVector.at(i) << endl;
	}

	vector<int>secondVector;

	secondVector.push_back(9);
	secondVector.push_back(8);
	secondVector.push_back(7);
	secondVector.push_back(6);
	secondVector.push_back(5);
	secondVector.push_back(4);

	for (int i=0; i<6; i++)
	{
		cout << "secondVector.at(" << i << "): " << secondVector.at(i) << endl;
	}

	bigNumber first(firstVector);
	bigNumber second(secondVector);

	cout << "first: ";
	first.printNumber();
	cout << endl << "second: ";
	second.printNumber();

	bigNumber third(addNumbers(first, second));

	cout << endl << "first + second = ";
	third.printNumber();
	
	return 0;
}












