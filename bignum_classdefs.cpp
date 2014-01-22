#include "headers.h"
#include "bignum_decs.h"

//FUNCTION FOR ADDING NUMBERS OF DIFFERENT BASES
bigNumber bigNumber::addNumbers(bigNumber bn1, bigNumber bn2)
{
    int base = bn1.getBase();
    
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
            bigNumber temp = bigNumber::addNumbers(bn1.absolute(), bn2.absolute());
            temp.setNegative();
			temp.updateDigits();
            return temp;
        }
    }
    
    if (bn1.absolute() > bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bigNumber::subtractNumbers(bn1.absolute(), bn2.absolute());
            temp.setNegative();
				temp.updateDigits();
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            return bigNumber::subtractNumbers(bn1.absolute(), bn2.absolute());
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            bigNumber temp = bigNumber::addNumbers(bn1.absolute(), bn2.absolute());
            temp.setNegative();
				temp.updateDigits();
            return temp;
        }
    }
    
    if (bn1.absolute() < bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bigNumber::subtractNumbers(bn2.absolute(), bn1.absolute());
			temp.updateDigits();
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            return bigNumber::subtractNumbers(bn1.absolute(), bn2.absolute());
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            bigNumber temp = bigNumber::addNumbers(bn1.absolute(), bn2.absolute());
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

		if (tempNumber>(base-1))
		{
			tempNumber-=base;
			carry = 1;
		}

		else 
		{
			carry = 0;
		}

		sum.setDigit(i, tempNumber);
	}
    
	sum.updateDigits();
	sum.setBase(base);
	return sum;
}

//FUNCTION FOR SUBTRACTING NUMBERS OF DIFFERENT BASES
bigNumber bigNumber::subtractNumbers(bigNumber bn1, bigNumber bn2)
{
    int base = bn1.getBase();
    bigNumber difference;
	difference.setBase(base);

    if (bn1.absolute() == bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bigNumber::addNumbers(bn1.absolute(), bn2.absolute());
            temp.setNegative();
			temp.updateDigits();
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            return bigNumber::addNumbers(bn1.absolute(), bn2.absolute());
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            bigNumber temp = bigNumber::subtractNumbers(bn1.absolute(), bn2.absolute());
            temp.setNegative();
			temp.updateDigits();
            return temp;
        }
    }
    
    if (bn1.absolute() > bn2.absolute())
    {
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bigNumber::addNumbers(bn1.absolute(), bn2.absolute());
            temp.setNegative();
			temp.updateDigits();
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            return bigNumber::addNumbers(bn1.absolute(), bn2.absolute());
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            bigNumber temp = bigNumber::subtractNumbers(bn1.absolute(), bn2.absolute());
            temp.setNegative();
			temp.updateDigits();
            return temp;
        }
    }
    
    if (bn1.absolute() < bn2.absolute())
    {
        if (bn1.getNegative()==false && bn2.getNegative()==false)
        {
            bigNumber temp = bigNumber::subtractNumbers(bn2.absolute(), bn1.absolute());
            temp.setNegative();
			temp.updateDigits();
            return temp;
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==false)
        {
            bigNumber temp = bigNumber::addNumbers(bn1.absolute(), bn2.absolute());
            temp.setNegative();
			temp.updateDigits();
            return temp;
        }
        
        if (bn1.getNegative()==false && bn2.getNegative()==true)
        {
            return bigNumber::addNumbers(bn1.absolute(), bn2.absolute());
        }
        
        if (bn1.getNegative()==true && bn2.getNegative()==true)
        {
            return bigNumber::subtractNumbers(bn2.absolute(), bn1.absolute());
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
			tempNumber+=base;
			carry = 1;
		}

		else 
		{
			carry = 0;
		}

		difference.setDigit(i, tempNumber);
	}

    difference.updateDigits();
    difference.setBase(base);
	return difference;
}

bigNumber bigNumber::multiplyNumbersSimple(bigNumber bn1, int n)
{  
    if (n==0)
    {
    	bigNumber zero;
    	zero.setBase(bn1.getBase());
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
    temp.setBase(bn1.getBase());

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

bigNumber bigNumber::divideNumbersSimple (bigNumber bn1, bigNumber bn2, bool &r)
{
    SHOWNUMBER(bn1);
    SHOWNUMBER(bn2);
	bigNumber temp;
	temp.setBase(bn1.getBase());
	
	while (bn1 >= bn2)
	{
		bn1-=bn2;
		temp++;
	}

	if (temp * bn2 == bn1)
	{
		r = false;
	}

	else r = true;

    SHOWNUMBER(temp);
	return temp;
}

bigNumber bigNumber::divideNumbers(bigNumber bn1, bigNumber bn2)
{
	QUERYNUMBER(bn1);
	QUERYNUMBER(bn2);
    
    int baseSet=bn1.getBase();
	bigNumber temp;
	temp.setBase(baseSet);

	if (bn1.getNegative() != bn2.getNegative())
	{
        temp.setNegative();
	}

	bn1.setPositive();
	bn2.setPositive();

	bool remainder=false;
	bool end=false;
	int marker=bn1.getDigitCount()-1;
	bigNumber numberToCompare(bn1.getDigit(marker));
	numberToCompare.setBase(baseSet);
	bigNumber nextNumber = divideNumbersSimple(numberToCompare, bn2.noDecimal(), remainder);
	bigNumber numberToSubtract;
	numberToSubtract.setBase(baseSet);

	while (end != true)
	{	
		SHOW(remainder);
		SHOW(marker);

		if (remainder==false && marker < PRECISION-bn1.getDecimalCount() )
		{
			end = true;
		}

		temp.setDigit(marker, nextNumber.getDigit(PRECISION));
		marker--;
	
		numberToSubtract = bn2.noDecimal() * nextNumber;
		numberToSubtract.updateDigits();

		numberToCompare -= numberToSubtract;

		numberToCompare.timesTen(1);

		if (marker>=0)
		{
			numberToCompare += bn1.getDigit(marker);
		}

		nextNumber = divideNumbersSimple(numberToCompare, bn2.noDecimal(), remainder);

		if (marker<0)
		{
			end = true;
		}

	}

	temp.timesTen(bn2.getDecimalCount());
	QUERYNUMBER(temp);
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
        temp = (bigNumber(1) / temp);
    }
    
    return temp;
}

void bigNumber::convertBaseSimple(int n)
{
    if (*this==0)
	{
		base = n;
	}

	else
    {
        bigNumber counter = (*this).absolute();
        
        bigNumber converted;
        converted.setBase(n);
        
        while (counter > 0)
        {
            converted++;
            counter--;
        }
 
        *this = converted;
    } 
}

void bigNumber::convertBase(int n)
{
	bigNumber temp;
	temp.setBase(n);

	if (*this==0)
	{
		base = n;
	}

	else if (base != n)
	{
		if (decimalCount > 0)
		{
			bigNumber temp1 = *this;
			temp1.timesTen(decimalCount);
			bigNumber temp2(pow((int) 10, decimalCount));
			temp2.setBase(base);

			temp1.convertBase(n);
			temp2.convertBase(n);

			temp = temp1/temp2;

			*this = temp;
		}

		else 
		{
			bigNumber baseConvert(base);
			baseConvert.convertBaseSimple(n);

			int counter = digitCount-PRECISION;

			for (int i=counter; i>0; i--)
			{
				int marker = PRECISION + (i - 1);

				bigNumber digitExponent = (marker - PRECISION);
				bigNumber digitValue = digits[marker];

				digitExponent.convertBaseSimple(n);
				digitValue.convertBaseSimple(n);

				bigNumber exp = exponent(baseConvert, digitExponent);
			
				bigNumber numberToAdd = digitValue * exp;
				temp += numberToAdd;
			}			
			
			if (getNegative())
			    temp.setNegative();
			    
			*this = temp;
		}
	}
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
    base = b.getBase();
    
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

void bigNumber::operator ++ (int)
{
	bigNumber temp(1);
	*this += temp;
}

bigNumber bigNumber::pi()
{
    string piString(PI);
    bigNumber piNumber(0);
    
    for (int i=PRECISION; i>=0; i--)
    {
        char c = '0';
        int n = piString[PRECISION-i] - c;
        
        piNumber.setDigit(i, n);
    }
    
    return piNumber;
}

bigNumber bigNumber::theta()
{
    string thetaString(THETA);
    bigNumber thetaNumber(0);
    
    for (int i=PRECISION; i>=0; i--)
    {
        char c = '0';
        int n = thetaString[PRECISION-i] + c;
        
        thetaNumber.setDigit(i, n);
    }
    
    return thetaNumber;
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
	base = 10;
	updateDigits();
}

bool bigNumber::operator == (bigNumber b)
{
    bigNumber temp = b;
    
    if (negative != b.getNegative())
    {
        return false;
    }
    
    if (digitCount != temp.getDigitCount())
    {
        return false;
    }

    for (int i=digitCount; i>0; i--)
    {
        if (digits[i-1] != temp.getDigit(i-1))
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
    bigNumber temp = b;
    
    updateDigits();
    temp.updateDigits();
    
    if (*this == temp)
    {
        return false;
    }
    
    if (negative==true && temp.getNegative()==false)
    {
        return true;
    }
    
    if (negative==false && temp.getNegative()==true)
    {
        return false;
    }
    
    if (negative==true && temp.getNegative()==true)
    {
        return ( absolute() > temp.absolute() );
    }
    
    if (digitCount < temp.getDigitCount())
    {
        return true;
    }
    
    if (digitCount > temp.getDigitCount())
    {
        return false;
    }

    
    for (int i=digitCount-1; i>=0; i--)
    {
        if (digits[i] < temp.getDigit(i))
        {
            return true;
        }
        
        if (digits[i] > temp.getDigit(i))
        {
            return false;
        }
    }
    
    return false;
}

bool bigNumber::operator <= (bigNumber b)
{
    bigNumber temp = b;
    
    updateDigits();
    temp.updateDigits();
    
    if (*this == temp)
    {
        return true;
    }
    
    if (negative==true && temp.getNegative()==false)
    {
        return true;
    }
    
    if (negative==false && temp.getNegative()==true)
    {
        return false;
    }
    
    if (negative==true && temp.getNegative()==true)
    {
        return ( absolute() > temp.absolute() );
    }
    
    if (digitCount < temp.getDigitCount())
    {
        return true;
    }
    
    if (digitCount > temp.getDigitCount())
    {
        return false;
    }

    for (int i=digitCount-1; i>=0; i--)
    {
        if (digits[i] < temp.getDigit(i))
        {
            return true;
        }
        
        if (digits[i] > temp.getDigit(i))
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
    bigNumber temp = b;
    
    updateDigits();
    temp.updateDigits();
    
    if (*this == temp)
    {
        return false;
    }
    
    if (negative==false && temp.getNegative()==true)
    {
        return true;
    }
    
    if (negative==true && temp.getNegative()==false)
    {
        return false;
    }
    
    if (negative==true && temp.getNegative()==true)
    {
        return ( absolute() < temp.absolute() );
    }
    
    if (digitCount > temp.getDigitCount())
    {
        return true;
    }
    
    if (digitCount < temp.getDigitCount())
    {
        return false;
    }
    
    for (int i=digitCount-1; i>=0; i--)
    {
        if (digits[i] > temp.getDigit(i))
        {
            return true;
        }
        
        if (digits[i] < temp.getDigit(i))
        {
            return false;
        }
    }
    
    return false;
}

bool bigNumber::operator >= (bigNumber b)
{
    bigNumber temp = b;
    
    updateDigits();
    temp.updateDigits();
    
    if (*this == temp)
    {
        return true;
    }
    
    if (negative==false && temp.getNegative()==true)
    {
        return true;
    }
    
    if (negative==true && temp.getNegative()==false)
    {
        return false;
    }
    
    if (negative==true && temp.getNegative()==true)
    {
        return ( absolute() < temp.absolute() );
    }
    
    if (digitCount > temp.getDigitCount())
    {
        return true;
    }
    
    if (digitCount < temp.getDigitCount())
    {
        return false;
    }
    
    for (int i=digitCount-1; i>=0; i--)
    {
        if (digits[i] > temp.getDigit(i))
        {
            return true;
        }
        
        if (digits[i] < temp.getDigit(i))
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
	base = 10;
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
	base = 10;
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

void bigNumber::printDigit(int n)
{
    if (n<10)
        cout << n;
        
    else 
    {
        char toPrint='A';
        toPrint += (n-10);
        cout << toPrint;
    }
}

int bigNumber::printNumber()
{
	bigNumber temp;
	temp.updateDigits();
	if ((*this)==temp)
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
	    int target = digitCount-i-1;
	    
		if (target == (PRECISION-1))
		{
			cout << ".";
		}

		else if (comma==0 && (digitCount-i) >= PRECISION && base != 2)
		{
			if (i>0)
			{
				COMMA;
			}
				 
			comma = 3;
		}

        printDigit(digits[target]);

		comma--;
	}

	return 1;
}

int bigNumber::printNumber(int n)
{
    if (n>PRECISION)
    {
        cout << "Requested accuracy is too precise";
        return 0;
    }
    
	bigNumber temp;
	temp.updateDigits();

	if ((*this)==temp)
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

    int toUse=n;
    if (decimalCount<n)
        toUse = decimalCount;
        
    int toPrint = digitCount-(PRECISION-toUse);
	for (int i=0; i<toPrint; i++)
	{
	    int target = digitCount-i-1;
	    
		if (target == (PRECISION-1))
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

        if (i == toPrint-1 && target > 0 && digits[target-1] > 4)
        {
            printDigit(digits[target]+1);
        }
            
        else
        {
            printDigit(digits[target]);
        }

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

void bigNumber::printPercent(int n)
{
    bigNumber temp = *this;
    temp.timesTen(2);
    temp.printNumber(n);
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

bigNumber bigNumber::golden(bigNumber b)
{
    bigNumber temp1 = bigNumber(fibonacci(b));
    bigNumber temp2 = bigNumber(fibonacci(b-1));
    
    return temp1/temp2;
}

bigNumber bigNumber::golden(int n)
{
    bigNumber temp(n);
    return golden(temp);   
}

bigNumber bigNumber::fibonacci(bigNumber b)
{
    bigNumber counter;
    bigNumber high(1);
    bigNumber low(1);
    
    while (counter < (b-2))
    {
        bigNumber temp = high;
        high += low;
        low = temp;
        counter++;
    }
    return high;
}

bigNumber bigNumber::fibonacci(int n)
{
    bigNumber temp(n);
    return fibonacci(temp);
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

void bigNumber::query()
{
	int count = digitCount - (PRECISION - decimalCount);

	cout << "|";
	for (int i=0; i<count; i++)
	{
		int marker = (digitCount - i) - 1;
		if (marker == PRECISION-1)
			cout << ".|";

		cout << digits[marker] << "|";
	}
	
	cout << endl;
}

void settings::setRound(int n)
{
    if (n>PRECISION)
    {
        cout << "Cannot satisfy request" << endl;
    }
    
    else round = n;
}
