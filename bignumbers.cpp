#include <iostream>
#include <vector>
#include <math.h>

#define MAXDIGITS 100

#ifdef NOCOMMAS
#define COMMA 
#else 
#define COMMA cout << ","
#endif

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
		
		bool operator < (bigNumber b);     //updated
		bool operator > (bigNumber b);     //updated
		bool operator > (int n);            //updated
		bool operator < (int n);            //updated
		bool operator == (bigNumber b); 
		bool operator == (int n);   
		void operator += (bigNumber b);    
		void operator -= (bigNumber b);
		void operator *= (bigNumber b);
		void operator -- (int);
		void operator = (bigNumber b);
		bigNumber operator * (bigNumber b); //updated
		bigNumber operator * (int n);       //updated
		bigNumber operator + (bigNumber b); //updated
		bigNumber operator + (int n);       //updated
		bigNumber operator - (bigNumber b); //updated
		bigNumber operator - (int n);       //updated
		bigNumber absolute();

		void decrement();

	private:
		int digits[MAXDIGITS];
		int digitCount;
		bool negative;
};

void bigNumber::operator = (bigNumber b)
{
    int highestDigits=0;
    if (digitCount < b.getDigitCount())
        highestDigits = b.getDigitCount();
        
    else highestDigits = b.getDigitCount()+1;
    
    for (int i=0; i<highestDigits; i++)
    {
        digits[i] = b.getDigit(i);
    }
    
    updateDigits();
}

void bigNumber::operator -- (int)
{
	bigNumber temp(1);
	*this -= temp;
}

bigNumber::bigNumber(int n)
{
    negative = (n<0);
    if(n<0)
    {
      n *= -1;
    }
    
	for (int i=0; i<MAXDIGITS; i++)
    {
        digits[i]=0;
    }
    
    for (int i=0; i<20; i++)
    {
		int modifier = (pow((double) 10, i+1));
		int reduced = n % modifier;

		if (i==0)
			digits[i] = reduced;

		else digits[i] = reduced/(pow((double) 10, i));
    }
}

bool bigNumber::operator == (bigNumber b)
{
    if (negative != b.getNegative())
    {
        return false;
    }
    
    if (digitCount != b.getDigitCount())
    {
        return false;
    }
    
    for (int i=digitCount-1; i>=0; i--)
    {
        if (digits[i] != b.getDigit(i))
        {
            return false;
        }
    }
    
    return true;
}

bool bigNumber::operator == (int n)
{
    bigNumber b(n);
    return (*this == b);
}

bool bigNumber::operator < (bigNumber b)
{
    updateDigits();
    b.updateDigits();
    
    if (*this == b)
    {
        return false;
    }
    
    if (negative==true && b.getNegative()==false)
    {
        return true;
    }
    
    if (negative==false && b.getNegative()==true)
    {
        return false;
    }
    
    if (negative==true && b.getNegative()==true)
    {
        return !( absolute() < b.absolute() );
    }
    
    if (digitCount < b.getDigitCount())
    {
        return true;
    }
    
    if (digitCount > b.getDigitCount())
    {
        return false;
    }

    
    for (int i=digitCount-1; i>=0; i--)
    {
        if (digits[i] < b.getDigit(i))
        {
            return true;
        }
    }
    
    return false;
}

bool bigNumber::operator < (int n)
{
	bigNumber b(n);
    updateDigits(); 
    return (*this < b);
}

bool bigNumber::operator > (bigNumber b)
{
    updateDigits();
    b.updateDigits();
    
    if (*this == b)
    {
        return false;
    }
    
    if (negative==false && b.getNegative()==true)
    {
        return true;
    }
    
    if (negative==true && b.getNegative()==false)
    {
        return false;
    }
    
    if (negative==true && b.getNegative()==true)
    {
        return !( absolute() > b.absolute() );
    }
    
    if (digitCount > b.getDigitCount())
    {
        return true;
    }
    
    if (digitCount < b.getDigitCount())
    {
        return false;
    }
    
    for (int i=digitCount-1; i>=0; i--)
    {
        if (digits[i] > b.getDigit(i))
        {
            return true;
        }
    }
    
    return false;
}

bool bigNumber::operator > (int n)
{
	bigNumber b(n);
    updateDigits(); 
    return (*this > b);
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
    
    digitCount=0;
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
    
    if (digitCount==0)
        cout << 0;
    
	int comma = digitCount % 3;
	
	if (negative==true)
	    cout << "-";

	for (int i=0; i<digitCount; i++)
	{
		if (comma==0)
		{
		    if (i>0)
		    {
			    COMMA;
		    }
			    
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
    if (bn1.absolute() == bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bn1.absolute() + bn2.absolute();
            temp.setNegative();
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            return bn1.absolute() + bn2.absolute();
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            bigNumber temp = bn1.absolute() - bn2.absolute();
            temp.setNegative();
            return temp;
        }
    }
    
    if (bn1.absolute() > bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bn1.absolute() + bn2.absolute();
            temp.setNegative();
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            return bn1.absolute() + bn2.absolute();
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            bigNumber temp = bn1.absolute() - bn2.absolute();
            temp.setNegative();
            return temp;
        }
    }
    
    if (bn1.absolute() < bn2.absolute())
    {
        if (bn1.getNegative()==false && bn2.getNegative()==false)
        {
            bigNumber temp = bn2.absolute() - bn1.absolute();
            temp.setNegative();
            return temp;
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bn1.absolute() + bn2.absolute();
            temp.setNegative();
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            return bn1.absolute() + bn2.absolute();
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            return bn2.absolute() - bn1.absolute();
        }
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

void bigNumber::operator += (bigNumber b)
{
    bigNumber temp(addNumbers(*this, b));
    
    for (int i=0; i<MAXDIGITS-1; i++)
    {
        digits[i] = temp.getDigit(i);
    }
}

void bigNumber::operator -= (bigNumber b)
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
        bigNumber zero;
        return zero;
    }
    
    bigNumber temp(bn1);
    
    if (bn1.getNegative() == n<0)
    {
        temp.setPositive();
    }
    
    for (int i=0; i<(n-1); i++)
    {
        temp += bn1;
    }
    
    return temp;
}

bigNumber multiplyNumbers(bigNumber bn1, bigNumber bn2)
{
    bigNumber temp(0);
    
    if (bn1.getNegative() != bn2.getNegative())
        temp.setNegative();
    
    bn1.updateDigits();
    bn2.updateDigits();
    
    for (int i=0; i<bn2.getDigitCount(); i++)
    {
        bigNumber toAdd( multiplyNumbersSimple ( multiplyNumbersSimple (bn1.absolute(), bn2.getDigit(i)) , pow((double)10, (int)i)) );
        SHOW(cout << endl << "toAdd: "; toAdd.printNumber(); << cout << endl);
        temp += toAdd;
    }
 
    return temp;   
}

bigNumber bigNumber::operator * (bigNumber b)
{
    return multiplyNumbers (*this, b);
}

bigNumber bigNumber::operator * (int n)
{
    bigNumber b(n);
    return multiplyNumbers (*this, b);
}

bigNumber bigNumber:: operator + (bigNumber b)
{
    return addNumbers(*this, b);
}

bigNumber bigNumber:: operator + (int n)
{
    bigNumber b(n);
    return addNumbers(*this, b);
}

bigNumber bigNumber:: operator - (bigNumber b)
{
    return subtractNumbers(*this, b);
}

bigNumber bigNumber:: operator - (int n)
{
    bigNumber b(n);
    return subtractNumbers(*this, b);
}

void bigNumber::operator *= (bigNumber b)
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

    for (bigNumber counter(bn); counter > (int) 1 ; counter--)
    {
        if (bn > counter)
        {
            temp *= counter;
            SHOW(cout << endl << "temp: "; temp.printNumber());
            SHOW(cout << endl << "counter: "; counter.printNumber());
        }
    }

	return temp;
}

bigNumber bigNumber::absolute()
{
    bigNumber temp = *this;
    temp.setPositive();
    return temp;
}

void testGreaterThan(bigNumber bn1, bigNumber bn2)
{
    bn1.printNumber();
    cout << " > ";
    bn2.printNumber();
    cout << " is ";
    if (bn1 > bn2)
    {
        cout << "true";
    }
    
    else cout << "false";
    cout << endl;
}

void testLessThan(bigNumber bn1, bigNumber bn2)
{
    bn1.printNumber();
    cout << " < ";
    bn2.printNumber();
    cout << " is ";
    if (bn1 < bn2)
    {
        cout << "true";
    }
    
    else cout << "false";
    cout << endl;
}

void testEquals(bigNumber bn1, bigNumber bn2)
{
    bn1.printNumber();
    cout << " == ";
    bn2.printNumber();
    cout << " is ";
    if (bn1 == bn2)
    {
        cout << "true";
    }
    
    else cout << "false";
    cout << endl;
}

int main()
{
	bigNumber positive1(968723);
	bigNumber negative1(-732863);
	bigNumber positive2(647382);
	bigNumber negative2(-846243);
	
	testGreaterThan(positive1, positive1);
	testGreaterThan(positive1, negative1);
	testGreaterThan(positive1, positive2);
	testGreaterThan(positive1, negative2);
	cout << endl;
	testGreaterThan(negative1, positive1);
	testGreaterThan(negative1, negative1);
	testGreaterThan(negative1, positive2);
	testGreaterThan(negative1, negative2);  //incorrect
	cout << endl;
	testGreaterThan(positive2, positive1);  //incorrect
	testGreaterThan(positive2, negative1);
	testGreaterThan(positive2, positive2);
	testGreaterThan(positive2, negative2);
	cout << endl;
	testGreaterThan(negative2, positive1);
	testGreaterThan(negative2, negative1);
	testGreaterThan(negative2, positive2);
	testGreaterThan(negative2, negative2);
	cout << endl;
	testLessThan(positive1, positive1);
	testLessThan(positive1, negative1);
	testLessThan(positive1, positive2);  //incorrect   
	testLessThan(positive1, negative2);
	cout << endl;
	testLessThan(negative1, positive1);
	testLessThan(negative1, negative1);
	testLessThan(negative1, positive2);
	testLessThan(negative1, negative2);    
	cout << endl;
	testLessThan(positive2, positive1);
	testLessThan(positive2, negative1);
	testLessThan(positive2, positive2);
	testLessThan(positive2, negative2);
	cout << endl;
	testLessThan(negative2, positive1);
	testLessThan(negative2, negative1);  //incorrect
	testLessThan(negative2, positive2);
	testLessThan(negative2, negative2);
	cout << endl;
	testEquals(positive1, positive1);
	testEquals(positive1, negative1);
	testEquals(positive1, positive2);     
	testEquals(positive1, negative2);
	cout << endl;
	testEquals(negative1, positive1);
	testEquals(negative1, negative1);
	testEquals(negative1, positive2);
	testEquals(negative1, negative2);     
	cout << endl;
	testEquals(positive2, positive1);
	testEquals(positive2, negative1);
	testEquals(positive2, positive2);
	testEquals(positive2, negative2);
	cout << endl;
	testEquals(negative2, positive1);
	testEquals(negative2, negative1);
	testEquals(negative2, positive2);
	testEquals(negative2, negative2);

	
	cout << endl;
	return 0;
}












