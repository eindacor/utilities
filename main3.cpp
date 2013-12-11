#include "headers.h"
#include "bignum_decs.h"
#include <string>

#define MAXENTERED 256

extracted numberFromRange(int n1, int n2, char* c)
{
    bigNumber temp;
    int numbers=0;
    int negative=0;
    bool decimal=false;
    int decimalCount=0;
    vector<int> vec;
    
    for (int i=n1; i<n2; i++)
    {
        int numeral = c[i] - '0';
        
        if (c[i] == '-')
        {
            if (negative>0 || numbers>0)
            {
                return extracted(temp,  1);
            }
            
            temp.setNegative();
            negative++;
        }
        
        else if (c[i] == '.')
        {
            if (decimal>0)
            {
                return extracted(temp,  1);
            }
            
            decimal = true;
        }
        
        else if (c[i] == ' ')
        {
            if (negative>0 || numbers>0)
            {
                if (c[i+1] != ' ' && (i+1) != n2)
                    return extracted(temp,  1);
            }
        }
        
        else if (numeral >= 0 && numeral <= 9)
        {
            vec.push_back(numeral);
            numbers++;
            
            if (decimal==true)
                decimalCount++;
        }
        
        else return extracted(temp,  1);
    }
    
    for (int i=0; i<vec.size(); i++)
    {
        int numberToUse = vec.at(vec.size()-i);
        int locationToSet = PRECISION + i;
        temp.setDigit(locationToSet, numberToUse);
        temp.divideByTen(decimalCount);
    }
    
    return extracted(temp, 0);
}

solution solve(char* c)
{
    bigNumber temp;
    PTYPE p=ERROR;
    int symbol=0;
    int negative=0;
    
    for (int i=0; i<MAXENTERED; i++)
    {
        if (c[i] == '+')
        {
            symbol = i;
            p = ADD;
            break;
        }
            
        if (c[i] == '-')
        {
            if (negative > 0)
            {
                symbol = i;
                p = SUBTRACT;
                break;
            }
            
            else negative++;
        }
            
        if (c[i] == '*' || c[i] == 'x' || c[i] == 'X')
        {
            symbol = i;
            p = MULTIPLY;
            break;
        }
            
        if (c[i] == '/')
        {
            symbol = i;
            p = DIVIDE;
        }
            
        if (c[i] == '^')
        {
            symbol = i;
            p = EXPONENT;
        }
           
        /* 
        if (c[i] == '<' && c[i+1] != '=')
        {
            symbol = i;
            p = LESSTHAN;
        }
            
        if (c[i] == '<' && c[i+1] == '=')
        {
            symbol = i;
            p = LESSTHANEQUALS;
        }
            
        if (c[i] == '>' && c[i+1] != '=')
        {
            symbol = i;
            p = GREATERTHAN;
        }
            
        if (c[i] == '>' && c[i+1] == '=')
        {
            symbol = i;
            p = GREATERTHANEQUALS;
        }
            
        if (c[i] == '=')
        {
            symbol = i;
            p = EQUALS;
        }
        */
            
        if (c[i] == '!')
        {
            symbol = i;
            p = FACTORIAL;
        }
            
        if (c[i] == 'c' || c[i] == 'C')
        {
            symbol = i;
            p = ITERATION;
        }
    }
    
    extracted ex1(numberFromRange(0, symbol, c));
    extracted ex2(numberFromRange((symbol+1), MAXENTERED, c));
    
    if (ex1.getError()>0 || ex2.getError()>0)
        return solution(temp, 1);
        
    switch(p)
    {
        case ERROR:
            return solution(temp, 1);
        
        case ADD:
            temp = ex1.getStored() + ex2.getStored();
            return solution(temp, 0);
        
        case SUBTRACT:
            temp = ex1.getStored() - ex2.getStored();
            return solution(temp, 0);
        
        case MULTIPLY:
            temp = ex1.getStored() * ex2.getStored();
            return solution(temp, 0);
        
        case DIVIDE:
            temp = ex1.getStored() / ex2.getStored();
            return solution(temp, 0);
        
        /*
        case EXPONENT:
            temp = ex1.getStored() ^ ex2.getStored();
            return solution(temp, 0);
        */
        
        case FACTORIAL:
            temp = bigNumber::factorial(ex1.getStored());
            return solution(temp, 0);
        
        case ITERATION:
            temp = bigNumber::iterations(ex1.getStored(), ex2.getStored());
            return solution(temp, 0);
        
        default:
            return solution(temp, 1);
    }
}

int main()
{
    char entered[MAXENTERED];
    PTYPE problemType = ERROR;
    
    cout << "Enter an equation: ";
    
    cin.get(entered, MAXENTERED, "\n");
    
    solution solved(solved(entered));
    
    if (solved.getError()>0)
    {
        cout << "There has been an error";
    }
    
    else 
    {
        solved.getSolved().printNumber();
    }
    
    cout << endl;
}