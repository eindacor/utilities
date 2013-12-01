#include <iostream>
#include <vector>
#include <math.h>

#define MAXDIGITS 1000
#define PRECISION 10

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
		void setDigit(int n, int s) {digits[n] = s;}
		int getDigitCount();
		int getDecimalCount();
		void printNumber();
		bool getNegative() {return negative;}
		void updateDigits();
		void adjustPrecision(int n);
		void query (int n);

		void timesTen (int n);
		void divideByTen (int n);
		
		void setNegative() {negative = true;}
		void setPositive() {negative = false;}
		
		bool operator < (bigNumber b); 
		bool operator <= (bigNumber b); 
		bool operator < (int n);
		bool operator <= (int n);

		bool operator > (bigNumber b);
		bool operator >= (bigNumber b);
		bool operator > (int n);
		bool operator >= (int n);

		bool operator == (bigNumber b); 
		bool operator == (int n);   
		bool operator != (bigNumber b);
		bool operator != (int n); 

		void operator += (bigNumber b);    
		void operator -= (bigNumber b);
		void operator *= (bigNumber b);
		void operator -- (int);
		void operator = (bigNumber b);

		bigNumber operator * (bigNumber b);
		bigNumber operator * (int n);
		bigNumber operator + (bigNumber b);
		bigNumber operator + (int n);
		bigNumber operator - (bigNumber b);
		bigNumber operator - (int n);
		bigNumber absolute();

		void decrement();

	private:
		int digits[MAXDIGITS];
		int digitCount;
		int decimalCount;
		bool negative;
};

void bigNumber::operator = (bigNumber b)
{
	int highestDigits=0;
	int decimal=0;

	if (digitCount < b.getDigitCount())
        highestDigits = b.getDigitCount();
        
	else highestDigits = digitCount;

	if (decimalCount < b.getDecimalCount())
		decimal = b.getDecimalCount();

	else decimal = decimalCount;
    
	for (int i=(PRECISION-decimal); i<highestDigits; i++)
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
		{
			digits[i+PRECISION] = reduced;
		}

		else 
		{
			digits[i+PRECISION] = reduced/(pow((double) 10, i));
		}

	}
	
	decimalCount = 0;
	updateDigits();
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

bool bigNumber::operator != (bigNumber b)
{
	return !(*this==b);
}

bool bigNumber::operator != (int n)
{
	bigNumber b(n);
	return (*this!=b);
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
        return ( absolute() > b.absolute() );
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
        
        if (digits[i] > b.getDigit(i))
        {
            return false;
        }
    }
    
    return false;
}

bool bigNumber::operator <= (bigNumber b)
{
    updateDigits();
    b.updateDigits();
    
    if (*this == b)
    {
        return true;
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
        return ( absolute() > b.absolute() );
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
        
        if (digits[i] > b.getDigit(i))
        {
            return false;
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

bool bigNumber::operator <= (int n)
{
	bigNumber b(n);
	updateDigits(); 
	return (*this <= b);
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
        return ( absolute() < b.absolute() );
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
        
        if (digits[i] < b.getDigit(i))
        {
            return false;
        }
    }
    
    return false;
}

bool bigNumber::operator >= (bigNumber b)
{
    updateDigits();
    b.updateDigits();
    
    if (*this == b)
    {
        return true;
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
        return ( absolute() < b.absolute() );
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
        
        if (digits[i] < b.getDigit(i))
        {
            return false;
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

bool bigNumber::operator >= (int n)
{
	bigNumber b(n);
    updateDigits(); 
    return (*this >= b);
}

void bigNumber::updateDigits()
{
	for (int i=MAXDIGITS-1; i>0; i--)
   {
   	if (digits[i]>0)
      {
      	digitCount = (i+1);
			break;
      }	
	}

	decimalCount = 0;

	for (int i=0; i<PRECISION; i++)
	{
		if (digits[PRECISION-1-i]>0)
		{
			decimalCount = i+1;
			break;
		}
	}

	if (decimalCount==0 && digitCount==(PRECISION+1) && digits[PRECISION]==0)
		setPositive();
}

bigNumber::bigNumber()
{
    for (int i=0; i<MAXDIGITS; i++)
    {
        digits[i]=0;
    }
    
	decimalCount=0;
	updateDigits();
}

/*
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

	updateDigits();
	negative = false;
}
*/

int bigNumber::getDigitCount()
{
	updateDigits();
	return digitCount;
}

int bigNumber::getDecimalCount()
{
	updateDigits();
	return decimalCount;
}

void bigNumber::printNumber()
{
   updateDigits();

	int comma = (digitCount-PRECISION) % 3;

	if (negative==true)
	{
		 cout << "-";
	}

	for (int i=0; i<(digitCount-(PRECISION-decimalCount)); i++)
	{
		if (comma==0 && (digitCount-i) >= PRECISION)
		{
			if (i>0)
			{
				COMMA;
			}
				 
			comma = 3;
		}

		if (digitCount-i-1 == (PRECISION-1))
		{
			cout << ".";
		}

		cout << digits[digitCount-i-1];

		comma--;
	}
}

bigNumber addNumbers(bigNumber &bn1, bigNumber &bn2)
{
	bigNumber sum;

    if (bn1.absolute() == bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp(0);
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            bigNumber temp(0);
            return temp;
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            bigNumber temp = bn1.absolute() + bn2.absolute();
            temp.setNegative();
				temp.updateDigits();
            return temp;
        }
    }
    
    if (bn1.absolute() > bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bn1.absolute() - bn2.absolute();
            temp.setNegative();
				temp.updateDigits();
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            return bn1.absolute() - bn2.absolute();
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            bigNumber temp = bn1.absolute() + bn2.absolute();
            temp.setNegative();
				temp.updateDigits();
            return temp;
        }
    }
    
    if (bn1.absolute() < bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bn1.absolute() - bn2.absolute();
            temp.setNegative();
				temp.updateDigits();
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            return bn1.absolute() - bn2.absolute();
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            bigNumber temp = bn1.absolute() + bn2.absolute();
            temp.setNegative();
				temp.updateDigits();
            return temp;
        }
    }
    
	vector<int> temp;
	int carry=0;
	int digits=0;
	int decimal=0;

	if (bn1.getDecimalCount() > bn2.getDecimalCount())
		decimal = bn1.getDecimalCount();

	else decimal = bn2.getDecimalCount();

	if (bn1.getDigitCount() > bn2.getDigitCount())
		digits = bn1.getDigitCount()+1;

	else digits = bn2.getDigitCount()+1;

	for (int i=(PRECISION-decimal); i<digits+1; i++)
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

		sum.setDigit(i, tempNumber);
	}
    
	sum.updateDigits();
	return sum;
}

bigNumber subtractNumbers(bigNumber &bn1, bigNumber &bn2)
{
	bigNumber sum;

    if (bn1.absolute() == bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bn1.absolute() + bn2.absolute();
            temp.setNegative();
				temp.updateDigits();
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
				temp.updateDigits();
            return temp;
        }
    }
    
    if (bn1.absolute() > bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bn1.absolute() + bn2.absolute();
            temp.setNegative();
				temp.updateDigits();
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
				temp.updateDigits();
            return temp;
        }
    }
    
    if (bn1.absolute() < bn2.absolute())
    {
        if (bn1.getNegative()==false && bn2.getNegative()==false)
        {
            bigNumber temp = bn2.absolute() - bn1.absolute();
            temp.setNegative();
				temp.updateDigits();
            return temp;
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bn1.absolute() + bn2.absolute();
            temp.setNegative();
				temp.updateDigits();
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
	int digits=0;
	int decimal=0;

	if (bn1.getDecimalCount() > bn2.getDecimalCount())
		decimal = bn1.getDecimalCount();

	else decimal = bn2.getDecimalCount();

	if (bn1.getDigitCount() > bn2.getDigitCount())
		digits = bn1.getDigitCount()+1;

	else digits = bn2.getDigitCount()+1;

	for (int i=(PRECISION-decimal); i<digits+1; i++)
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

		sum.setDigit(i, tempNumber);
	}

   sum.updateDigits();
	return sum;
}

void bigNumber::operator += (bigNumber b)
{
	*this = *this + b;
}

void bigNumber::operator -= (bigNumber b)
{
	*this = *this - b;
}

void bigNumber::decrement()
{
	bigNumber temp(1);

	*this -= temp;

	updateDigits();
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
    
	 temp.updateDigits();
    return temp;
}

bigNumber multiplyNumbers(bigNumber &bn1, bigNumber &bn2)
{
   bigNumber temp(0);
	
	int counter = (bn2.getDigitCount()-(PRECISION-bn2.getDecimalCount()));
	DECLARE(counter);
	for (int i=0; i<counter; i++)
	{
		int toMultiply = (PRECISION-bn2.getDecimalCount()) + i;
		bigNumber toAdd = multiplyNumbersSimple(bn1.absolute(), bn2.getDigit(toMultiply) );
		toAdd.timesTen(i);
		temp += toAdd;
	}
 
	if (bn1.getNegative() != bn2.getNegative())
	{
        temp.setNegative();
	}

	temp.divideByTen(bn2.getDecimalCount());

	temp.updateDigits();
	return temp;   
}

void bigNumber::timesTen(int n)
{
	for (int i=0; i<n; i++)
	{
		for (int c=0; c<digitCount-(PRECISION-decimalCount); c++)
		{
			digits[digitCount-c] = digits[digitCount-1-c];
		}

		digits[PRECISION-decimalCount] = 0;
		updateDigits();
	}
}

void bigNumber::divideByTen(int n)
{
	int start=0;

	if (decimalCount!=PRECISION)
		start = PRECISION-decimalCount-1;
			
	for (int i=0; i<n; i++)
	{
		for (int c=start; c<digitCount; c++)
		{
			digits[c] = digits[c+1];
		}
	}

	updateDigits();
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
	*this = *this * b;
}

bigNumber factorial(bigNumber bn)
{
    bigNumber temp(bn);

    for (bigNumber counter(bn); counter > (int) 1 ; counter--)
    {

        if (bn > counter)
        {
            temp *= counter;
        }
    }

	temp.updateDigits();
	return temp;
}

bigNumber bigNumber::absolute()
{
    bigNumber temp = *this;
	 temp.updateDigits();
    temp.setPositive();
    return temp;
}

int divideNumbersSimple (bigNumber bn1, bigNumber bn2)
{
	int temp=0;
	
	while (bn1 >= bn2)
	{
		bn1-=bn2;
		temp++;
	}

	return temp;
}

void bigNumber::query (int n)
{
	for (int i=0; i<n; i++)
	{
		if ((n-i-1)==(PRECISION-1))
			cout << ".";

		cout << digits[n-i-1];
	}
	
	cout << endl;
}

int main()
{
	bigNumber test1(987654321);
	bigNumber test2(123456789);

	cout << endl;
	test1.printNumber();
	cout << " * ";
	test2.printNumber();
	cout << " = ";
	(test1*test2).printNumber();

	cout << endl;
	test1.printNumber();
	cout << " + ";
	test2.printNumber();
	cout << " = ";
	(test1+test2).printNumber();

	cout << endl;
	test1.printNumber();
	cout << " - ";
	test2.printNumber();
	cout << " = ";
	(test1-test2).printNumber();

	cout << endl;
	test1 -= test2;
	test1.printNumber();

	cout << endl;
	return 0;
}












