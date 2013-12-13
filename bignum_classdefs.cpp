#include "headers.h"
#include "bignum_decs.h"

bigNumber bigNumber::addNumbers(bigNumber &bn1, bigNumber &bn2)
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

bigNumber bigNumber::subtractNumbers(bigNumber &bn1, bigNumber &bn2)
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

bigNumber bigNumber::multiplyNumbersSimple(bigNumber bn1, int n)
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

bigNumber bigNumber::multiplyNumbers(bigNumber &bn1, bigNumber &bn2)
{
   bigNumber temp(0);

	if (bn1==temp || bn2==temp)
	{
		return temp;
	}
	
	int counter = (bn2.getDigitCount()-(PRECISION-bn2.getDecimalCount()));
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

int bigNumber::divideNumbersSimple (bigNumber bn1, bigNumber bn2, bool &r)
{
	int temp=0;
	
	while (bn1 >= bn2)
	{
		bn1-=bn2;
		temp++;
	}

	if (bn1 > 0)
	{
		r = true;
	}

	return temp;
}

bigNumber bigNumber::divideNumbers(bigNumber bn1, bigNumber bn2)
{
	bigNumber temp;

	if (bn1.getNegative() != bn2.getNegative())
	{
        temp.setNegative();
	}

	bn1.setPositive();
	bn2.setPositive();

	bool remainder=false;
	bool end=false;
	int counter=bn1.getDigitCount()-1;
	bigNumber numberToCompare(bn1.getDigit(counter));
	int nextNumber = divideNumbersSimple(numberToCompare, bn2.noDecimal(), remainder);
	bigNumber numberToSubtract;

	while (end != true)
	{
		if (remainder==false && counter < bn1.getDigitCount() - (PRECISION-bn1.getDecimalCount()) )
		{
			end = true;
		}

		temp.setDigit(counter, nextNumber);
		counter--;
	
		numberToSubtract = bn2.noDecimal() * nextNumber;
		numberToSubtract.updateDigits();

		numberToCompare -= numberToSubtract;

		numberToCompare.timesTen(1);

		if (counter>=0)
		{
			numberToCompare += bn1.getDigit(counter);
		}

		nextNumber = divideNumbersSimple(numberToCompare, bn2.noDecimal(), remainder);

		if (counter<0)
		{
			end = true;
		}

	}

	temp.timesTen(bn2.getDecimalCount());
	return temp;
}

bigNumber bigNumber::factorial(bigNumber bn)
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

bigNumber bigNumber::iterations(bigNumber bn1, bigNumber bn2)
{
	bigNumber first = factorial(bn1);
	bigNumber second = bn1-bn2;
	bigNumber third = factorial(second);
	bigNumber fourth = factorial(bn2);
	bigNumber fifth = third * fourth;

	bigNumber temp = divideNumbers(first, fifth);

	return temp;
}

bigNumber bigNumber::exponent(bigNumber bn1, bigNumber bn2)
{
    bigNumber counter = bn2.absolute();
    bigNumber temp = bn1;
    
    if (bn2 == 0)
    {
        return bigNumber(1);
    }
    
    while (counter > 1)
    {
        temp *= bn1;
        counter--;
    }
    
    if (bn2.getNegative())
    {
        temp = bigNumber(1) / temp;
    }
    
    return temp;
}

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
    
    negative = b.getNegative();
    
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

void bigNumber::printPercent()
{
    bigNumber temp = *this;
    temp.timesTen(2);
    temp.printNumber();
    cout << "%";
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

	for (int i=n; i>0; i--)
	{
		if (digits[0]>4)
			digits[0] = digits[1] + 1;

		for (int c=1; c<digitCount; c++)
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
