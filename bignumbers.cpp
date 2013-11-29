#include <iostream>
#include <vector>
#include <math.h>

#define MAXDIGITS 1000

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

		void timesTen (int n);
		
		void setNegative() {negative = true;}
		void setPositive() {negative = false;}
		
		bool operator < (bigNumber b);     //updated
		bool operator > (bigNumber b);     //updated
		bool operator > (int n);            //updated
		bool operator < (int n);            //updated
		bool operator == (bigNumber b); 
		bool operator == (int n);   
		bool operator != (bigNumber b);
		bool operator != (int n); 
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
		{
			digits[i] = reduced;
		}

		else 
		{
			digits[i] = reduced/(pow((double) 10, i));
		}
	}
	
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
        SHOWLINE;
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

bool bigNumber::operator > (int n)
{
	bigNumber b(n);
    updateDigits(); 
    return (*this > b);
}

int bigNumber::updateDigits()
{
	for (int i=MAXDIGITS-1; i>0; i--)
   {
   	if (digits[i]>0)
      {
      	digitCount = (i+1);
         return digitCount;
      }	
	}

	digitCount = 1;
	if (digits[0] == 0)
		setPositive();	

   return 1;
}

bigNumber::bigNumber()
{
    for (int i=0; i<MAXDIGITS; i++)
    {
        digits[i]=0;
    }
    
    updateDigits();
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

	updateDigits();
	negative = false;
}

int bigNumber::getDigitCount()
{
	updateDigits();
	return digitCount;
}

void bigNumber::printNumber()
{
   updateDigits();

	if (digitCount==0)
	{
       cout << 0;
	}

	else
	{
    
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
}

bigNumber addNumbers(bigNumber &bn1, bigNumber &bn2)
{
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
	int digits;

	if (bn1.getDigitCount() > bn2.getDigitCount())
		digits = bn1.getDigitCount()+1;

	else digits = bn2.getDigitCount()+1;

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
    
	sum.updateDigits();
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
	int digits;

	if (bn1.getDigitCount() > bn2.getDigitCount())
		digits = bn1.getDigitCount()+1;

	else digits = bn2.getDigitCount()+1;

	for (int i=0; i<digits; i++)
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
   sum.updateDigits();
	return sum;
}

void bigNumber::operator += (bigNumber b)
{
    bigNumber temp(addNumbers(*this, b));
    
    for (int i=0; i<MAXDIGITS-1; i++)
    {
        digits[i] = temp.getDigit(i);
    }

	updateDigits();
}

void bigNumber::operator -= (bigNumber b)
{
    bigNumber temp(subtractNumbers(*this, b));
    
    for (int i=0; i<MAXDIGITS-1; i++)
    {
        digits[i] = temp.getDigit(i);
    }

	updateDigits();
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
			zero.updateDigits();
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
	
	int counter = bn2.getDigitCount();
	for (int i=0; i<counter; i++)
	{
		int multiplier = pow((double) 10, (int) i);
		bigNumber toAdd = multiplyNumbersSimple(bn1.absolute(), bn2.getDigit(i));
		toAdd.timesTen(i);
		temp += toAdd;
	}
 
	if (bn1.getNegative() != bn2.getNegative())
	{
        temp.setNegative();
	}

	temp.updateDigits();
	return temp;   
}

void bigNumber::timesTen(int n)
{
	for (int i=0; i<n; i++)
	{
		for (int c=0; c<digitCount; c++)
		{
			digits[digitCount-c] = digits[digitCount-1-c];
		}

		digits[0] = 0;
		updateDigits();
	}
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

void testMultiply(bigNumber bn1, bigNumber bn2)
{
	bigNumber temp = bn1 * bn2;
	bn1.printNumber();
	cout << " * ";
	bn2.printNumber();
	cout << " = ";
	temp.printNumber();
	cout << endl;
}

int main()
{
	bigNumber fact = factorial(bigNumber(365));

	fact.printNumber();
	cout << endl << fact.getDigitCount();

	cout << endl << endl;

	bigNumber multiplied = bigNumber(123456789) * bigNumber(987654321);
	multiplied.printNumber();
	cout << endl << multiplied.getDigitCount();

	cout << endl;
	return 0;
}












