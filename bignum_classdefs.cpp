#include "headers.h"
#include "bignum_decs.h"

void bigNumber::printStats()
{
	cout << endl << "digitCount=" << digitCount << " ; decimalCount=" << decimalCount << " ; ";

	if (negative)
		cout << "is negative";
	
	else cout << "is positive";
}

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
		int reduced = (n % modifier);

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
	digitCount=0;
	decimalCount=0;

	for (int i=MAXDIGITS-1; i>0; i--)
   {
		if (i==PRECISION)
		{
			digitCount = PRECISION + 1;
			break;
		}

   	if (digits[i]>0)
      {
      	digitCount = (i+1);
			break;
      }	
	}

	for (int i=0; i<PRECISION; i++)
	{
		if (digits[i]>0)
		{
			decimalCount = PRECISION-i;
			break;
		}
	}

	if (decimalCount==0 && digitCount==(PRECISION+1) && digits[PRECISION]==0)
	{
		setPositive();
	}
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

int bigNumber::printNumber()
{
	bigNumber temp;
	if (*this==temp)
	{
		cout << 0;
		return 0;
	}

   updateDigits();

	int comma = (digitCount-PRECISION) % 3;

	if (negative==true)
	{
		 cout << "-";
	}

	for (int i=0; i<(digitCount-(PRECISION-decimalCount)); i++)
	{
		if (digitCount-i-1 == (PRECISION-1))
		{
			cout << ".";
		}

		else if (comma==0 && (digitCount-i) >= PRECISION)
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

	return 1;
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
	updateDigits();
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

bigNumber bigNumber::operator / (bigNumber b)
{
	return divideNumbers (*this, b);
}

bigNumber bigNumber::operator / (int n)
{
   bigNumber b(n);
   return divideNumbers (*this, b);
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

void bigNumber::operator /= (bigNumber b)
{
	*this = *this / b;
}

bigNumber bigNumber::absolute()
{
    bigNumber temp = *this;
	 temp.updateDigits();
    temp.setPositive();
    return temp;
}

bigNumber bigNumber::noDecimal()
{
	bigNumber temp(*this);
	temp.timesTen(getDecimalCount());
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