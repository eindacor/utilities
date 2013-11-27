#include <iostream>
#include <vector>
#include <math.h>

#define DEBUG

#define MAXDIGITS 100

#ifdef DEBUG
#define DECLARE(x) cout << "\n\t|  DECLARATION: " << #x << "= " << x
#define SHOW(x) x
#define SHOWLINE cout << endl << __LINE__ << endl
#else
#define DECLARE(x)
#define SHOW(x)
#define SHOWLINE
#endif

using std::cout;
using std::cin;
using std::endl;
using std::vector;


class bigNumber
{
	public:
		bigNumber(vector<int> n);
		bigNumber();
		bigNumber(int n);
		~bigNumber() {};

		int getDigit(int n) {return digits[n];}

		int getDigitCount();
		
		void printNumber();

		bool getNegative() {return negative;}
		
		int updateDigits();
		
		void setNegative() {negative = true;}
		void setPositive() {negative = false;}
		
		bool operator < (bigNumber &b);
		bool operator > (bigNumber &b);
		bool operator > (int n);
		bool operator < (int n);
		void operator += (bigNumber &b);
		void operator -= (bigNumber &b);
		void operator *= (bigNumber &b);
		void operator --();

		void decrement();

	private:
		int digits[MAXDIGITS];
		int digitCount;
		bool negative;
};

void bigNumber::operator --()
{
	bigNumber temp(1);
	*this -= temp;
}

bigNumber::bigNumber(int n)
{
	for (int i=0; i<MAXDIGITS; i++)
    {
        digits[i]=0;
    }
    
    negative = false;
    for (int i=0; i<20; i++)
    {
		int modifier = (pow((double) 10, i+1));
		int reduced = n % modifier;

		if (i==0)
			digits[i] = reduced;

		else digits[i] = reduced/(pow((double) 10, i));
    }
}

bool bigNumber::operator < (bigNumber &b)
{
    if (negative==true && b.getNegative()==false)
    {
        return true;
    }
    
    if (digitCount < b.getDigitCount())
    {
        return true;
    }
    
    if (digits[digitCount-1] < b.getDigit(digitCount-1))
    {
        return true;
    }

    return false;
}

bool bigNumber::operator < (int n)
{
	bigNumber b(n);

    if (negative==true && b.getNegative()==false)
    {
        return true;
    }
    
    if (digitCount < b.getDigitCount())
    {
        return true;
    }
    
    if (digits[digitCount-1] < b.getDigit(digitCount-1))
    {
        return true;
    }

    return false;
}

bool bigNumber::operator > (bigNumber &b)
{
    if (negative==false && b.getNegative()==true)
    {
        return true;
    }
    
    if (digitCount > b.getDigitCount())
    {
        return true;
    }
    
    if (digits[digitCount-1] > b.getDigit(digitCount-1))
    {
        return true;
    }
    
    return false;
}

bool bigNumber::operator > (int n)
{
	bigNumber b(n);

    if (negative==false && b.getNegative()==true)
    {
        return true;
    }
    
    if (digitCount > b.getDigitCount())
    {
        return true;
    }
    
    if (digits[digitCount-1] > b.getDigit(digitCount-1))
    {
        return true;
    }
    
    return false;
}

int bigNumber::updateDigits()
{
    for (int i=0; i<MAXDIGITS; i++)
    {
        if (digits[MAXDIGITS-1-i]>0)
        {
            digitCount = MAXDIGITS-i;
            return MAXDIGITS-i;
        }
    }
    return 0;
}

bigNumber::bigNumber()
{
    for (int i=0; i<MAXDIGITS; i++)
    {
        digits[i]=0;
    }
    
    negative = false;
}

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
		count++;
	}

	digitCount = count;
	
	negative = false;
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
    updateDigits();
    
	int comma = digitCount % 3;
	
	if (negative==true)
	    cout << "-";

	for (int i=0; i<digitCount; i++)
	{
		if (comma==0)
		{
		    if (i>0)
			    cout << ",";
			    
			comma = 3;
		}

		cout << digits[digitCount-i-1];

		comma--;
	}
}

bigNumber addNumbers(bigNumber &bn1, bigNumber &bn2)
{
    int digits=0;
    if (bn1.getDigitCount() < bn2.getDigitCount())
        digits = bn2.getDigitCount()+1;
        
    else digits = bn1.getDigitCount()+1;
    
	vector<int> temp;
	int carry=0;

	for (int i=0; i<digits; i++)
	{
		int tempNumber = bn1.getDigit(i) + bn2.getDigit(i);
		
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

    bigNumber sum(temp);
    
	return sum;
}

bigNumber subtractNumbers(bigNumber &bn1, bigNumber &bn2)
{
    if (bn1.getNegative()==true && bn2.getNegative()==true)
    {
        bigNumber negativeSum(addNumbers(bn1, bn2));
        negativeSum.setNegative();
        return negativeSum;
        
    }
    
    if (bn1<bn2 && bn1.getNegative()==false && bn2.getNegative()==false)
    {
        bigNumber negativeNumber(subtractNumbers(bn2, bn1));
        negativeNumber.setNegative();
        return negativeNumber;
    }
    
    vector<int> temp;
	int carry=0;

	for (int i=0; i<MAXDIGITS; i++)
	{
		int tempNumber = bn1.getDigit(i) - bn2.getDigit(i);
		
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

    bigNumber sum(temp);
    
	return sum;
}

void bigNumber::operator += (bigNumber &b)
{
    bigNumber temp(addNumbers(*this, b));
    
    for (int i=0; i<MAXDIGITS-1; i++)
    {
        digits[i] = temp.getDigit(i);
    }
}

void bigNumber::operator -= (bigNumber &b)
{
    bigNumber temp(subtractNumbers(*this, b));
    
    for (int i=0; i<MAXDIGITS-1; i++)
    {
        digits[i] = temp.getDigit(i);
    }
}

void bigNumber::decrement()
{
	bigNumber temp(1);

	*this -= temp;
}

bigNumber multiplyNumbersSimple(bigNumber bn1, int n)
{
    if (n==0)
    {
        vector<int> one;
        one.push_back(1);
        return bigNumber(one);
    }
    
    bigNumber temp(bn1);
    
    for (int i=0; i<(n-1); i++)
    {
        temp += bn1;
    }
    
    return temp;
}

bigNumber multiplyNumbers(bigNumber bn1, bigNumber bn2)
{
    bigNumber temp;
    
    if (bn1.getNegative() != bn2.getNegative())
        temp.setNegative();
    
    bn1.setPositive();
    bn1.updateDigits();
    bn2.setPositive();
    bn2.updateDigits();
    
    for (int i=0; i<bn2.getDigitCount(); i++)
    {
        bigNumber toAdd( multiplyNumbersSimple( multiplyNumbersSimple(bn1, bn2.getDigit(i)) , pow((double)10, (int)i)) );
        temp += toAdd;
    }
 
    return temp;   
}

void bigNumber::operator *= (bigNumber &b)
{
    bigNumber temp(multiplyNumbers(*this, b));
    
    for (int i=0; i<MAXDIGITS-1; i++)
    {
        digits[i] = temp.getDigit(i);
    }
}

bigNumber factorial(bigNumber bn)
{
    bigNumber temp(bn);
	bigNumber counter(temp);

	temp *= counter;
	temp *= counter;
	temp *= counter;
	temp *= counter;
	temp *= counter;
	temp *= counter;

	if (counter < temp)
		SHOWLINE;

	return temp;
}


int main()
{
	vector<int>firstVector;

	firstVector.push_back(1);
	firstVector.push_back(3);
	firstVector.push_back(8);
	firstVector.push_back(5);
	firstVector.push_back(2);
	firstVector.push_back(5);
	firstVector.push_back(8);
	firstVector.push_back(3);
	firstVector.push_back(7);
	firstVector.push_back(5);
	firstVector.push_back(6);

	vector<int>secondVector;

	secondVector.push_back(9);
	secondVector.push_back(8);
	secondVector.push_back(1);
	secondVector.push_back(3);
	secondVector.push_back(5);
	secondVector.push_back(8);
	secondVector.push_back(3);
	secondVector.push_back(4);
	secondVector.push_back(4);

	bigNumber first(firstVector);
	bigNumber second(secondVector);

	cout << "first: ";
	first.printNumber();
	cout << endl << "second: ";
	second.printNumber();

	bigNumber third(addNumbers(first, second));
	cout << endl;
	first.printNumber();
	cout << " + ";
	second.printNumber();
	cout << " = ";
	third.printNumber();
	
	cout << endl;
	first.printNumber();
	cout << " < ";
	second.printNumber();
	cout << " is ";
	if (first < second == true)
	{
	    cout << "true";
	}
	else cout << "false";
	
	bigNumber fourth(subtractNumbers(first, second));
	cout << endl;
	first.printNumber();
	cout << " - ";
	second.printNumber();
	cout << " = ";
	fourth.printNumber();
	
	cout << endl;
	second.printNumber();
	cout << " < ";
	first.printNumber();
	cout << " is ";
	if (second < first == true)
	{
	    cout << "true";
	}
	else cout << "false";
	
	cout << endl;
	second.printNumber();
	cout << " > ";
	first.printNumber();
	cout << " is ";
	if (second > first == true)
	{
	    cout << "true";
	}
	else cout << "false";
	
	cout << endl;
	first.printNumber();
	cout << " += ";
	second.printNumber();
	first += second;
	cout << endl << "first: ";
	first.printNumber();

	cout << endl << "multiplyNumbersSimple(first, 5) = ";
	bigNumber fifth(multiplyNumbersSimple(first, 5));
	fifth.printNumber();
	
	cout << endl;
	second.printNumber();
	cout << " - ";
	first.printNumber();
	cout << " = ";
	bigNumber sixth(subtractNumbers(second, first));
	sixth.printNumber();
	
	cout << endl;
	
	vector<int>thirdVector;
	thirdVector.push_back(1);
	thirdVector.push_back(3);
	thirdVector.push_back(8);
	thirdVector.push_back(5);
	bigNumber seventh(thirdVector);
	
	vector<int>fourthVector;
	fourthVector.push_back(2);
	fourthVector.push_back(2);
	fourthVector.push_back(4);
	bigNumber eighth(fourthVector);
	
	cout << endl;
	cout << "seventh: ";
	seventh.printNumber();
	cout << endl << "eighth: ";
	eighth.printNumber();
	
	bigNumber ninth(multiplyNumbers(seventh, eighth));
	
	cout << endl;
	seventh.printNumber();
	cout << " * ";
	eighth.printNumber();
	cout << " = ";
	ninth.printNumber();

	bigNumber eleventh(28777932);
	cout << endl;
	cout << "eleventh: ";
	eleventh.printNumber();

	bigNumber thirteenth(4);
	thirteenth *= bigNumber(7);
	cout << endl;
	cout << "thirteenth: ";
	thirteenth.printNumber();

	bigNumber joe(1);
	cout << endl;
	cout << "joe: ";
	joe.printNumber();

	bigNumber fourteenth(factorial(bigNumber(4)));
	cout << endl;
	cout << "fourteenth: ";
	fourteenth.printNumber();


	/*
	bigNumber tenth(multiplyNumbers(first, second));
	cout << endl;
	first.printNumber();
	cout << " * ";
	second.printNumber();
	cout << " = ";
	tenth.printNumber();
	*/
	
	cout << endl;
	char response;
	cin >> response;
	return 0;
}












