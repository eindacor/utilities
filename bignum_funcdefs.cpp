#include "headers.h"
#include "bignum_decs.h"

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

int divideNumbersSimple (bigNumber bn1, bigNumber bn2, bool &r)
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

bigNumber divideNumbers(bigNumber bn1, bigNumber bn2)
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

bigNumber iterations(bigNumber bn1, bigNumber bn2)
{
	bigNumber first = factorial(bn1);
	bigNumber second = bn1-bn2;
	bigNumber third = factorial(second);
	bigNumber fourth = factorial(bn2);
	bigNumber fifth = third * fourth;

	bigNumber temp = divideNumbers(first, fifth);

	return temp;
}