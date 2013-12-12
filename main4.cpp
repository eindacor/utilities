#include "headers.h"
#include "bignum_decs.h"
#include <string>

#define MAXENTERED 256

/*
extracted numberFromRange(int n1, int n2, const char* &c)
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

solution solve(const char* &c)
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
        
        case EXPONENT:
            temp = ex1.getStored() ^ ex2.getStored();
            return solution(temp, 0);
        
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
*/

PTYPE checkSymbol(char &c)
{
    if (c == '+')
    {
        return ADD;
    }
        
    if (c == '-')
    {
        return SUBTRACT;
    }
        
    if (c == '*' || c == 'x' || c == 'X')
    {
        return MULTIPLY;
    }
        
    if (c == '/')
    {
        return DIVIDE;
    }
        
    if (c == '^')
    {
        return EXPONENT;
    }
        
    if (c == '!')
    {
        return FACTORIAL;
    }
        
    if (c == 'c' || c == 'C')
    {
        return ITERATION;
    }
    
    return ERROR;
}

int checkNumber(char &c)
{
    int i = c - '0';
    
    return i;
}

bool checkSpace(char &c)
{
    return (c == ' ');
}

solution solve(string &c)
{
    c += '@';
    PTYPE pType=ERROR;
    
    vector<int> first;
    vector<int> second;
    bigNumber bn1;
    bigNumber bn2;
    bigNumber temp;
    
    bool decimal=false;
    int decimalCount1=0;
    int decimalCount2=0;
    int numbers=0;
    bool negative=false;
    bool done=false;
    bigNumber* targetBN = &bn1;
    vector<int>* targetVec = &first;
    int* targetDec = &decimalCount1;
    
    for (int i=0; i<c.size(); i++)
    {
        SHOWLINE;
        DECLARE(c[i]);
        DECLARE(checkNumber(c[i]));
        //first space can't be a symbol
        if (i==0)
        {
            SHOWLINE;
            if (checkSymbol(c[i]) != ERROR && checkSymbol(c[i]) != SUBTRACT)
                return solution(temp, 1);
        }
    
        //if it's a space, and is preceeded by a number, number is complete
        if (checkSpace(c[i])==true && checkNumber(c[i-1]) >= 0 && checkNumber(c[i-1]) <= 9)
        {
            done = true;
        }
        
        //if it's a space, negative is set, and it is preceeded by a minus symbol, return error
        if (checkSpace(c[i])==true && checkSymbol(c[i-1]) == SUBTRACT && negative == true)
        {
            return solution(temp, 1);
        }
        
        //if it's a number
        else if (checkNumber(c[i]) >= 0 && checkNumber(c[i]) <= 9)
        {
            
            //if number was complete, return error
            if (done==true)
                return solution(temp, 1);
                
            //otherwise add number to target vector, add decimal count if needed
            else 
            {
                (*targetVec).push_back(checkNumber(c[i]));
                numbers++;
                
                if (decimal==true)
                    (*targetDec)++;
            }
        }
        
        //if it's a minus symbol
        else if (checkSymbol(c[i]) == SUBTRACT)
        {
            //if no numbers have been added, target number is negative
            if (numbers==0)
            {
                SHOWLINE;
                if (negative==false)
                {
                    (*targetBN).setNegative();
                    negative = true;
                }
                
                else return solution(temp, 1);
            }
            
            //if numbers have been added, and the target is the first number, the problem type is subtraction
            else if (targetBN == &bn1)
            {
                pType = SUBTRACT;
                targetBN = &bn2;
                numbers=0;
                negative=false;
                done=false;
                targetDec = &decimalCount2;
                targetVec = &second;
            }
            
            //if numbers have been added, and the target is the second number, return error
            else return solution(temp, 1);
        }
        
        //if it's a symbol other than minus
        else  if (checkSymbol(c[i]) != ERROR && checkSymbol(c[i]) != SUBTRACT)
        {
            SHOWLINE;
            //if the type is already established, return error
            if (pType != ERROR)
                return solution(temp, 1);
                
            //otherwise, set problem type based on symbol and reset figures
            else 
            {
                pType = checkSymbol(c[i]);
                targetBN = &bn2;
                numbers=0;
                negative=false;
                done=false;
                targetDec = &decimalCount2;
                targetVec = &second;
            }
        }
        
         //if it's a decimal point
        else if (c[i]=='.')
        {
            SHOWLINE;
            //if there's already been a decimal point, return error
            if (decimal==true)
                return solution(temp, 1);
                
            else decimal = true;
        }
        
        //if it's an endline character
        else if (c[i] == '@')
        {
            SHOWLINE;
            //if first number is empty, return error
            if (first.size()==0)
                return solution(temp, 1);
                
            //otherwise take ints from vector and use to set bigNumber1
            else 
            {
                for (int n=0; n<first.size(); n++)
                {
                    int numberToUse = first.at(first.size()-n-1);
                    int locationToSet = PRECISION + n;
                    bn1.setDigit(locationToSet, numberToUse);
                    bn1.divideByTen(decimalCount1);
                }
            }
            
            //if second number is empty
            if (second.size()==0)
            {
                SHOWLINE;
                //if problem type is factorial, return factorial of first number
                if (pType == FACTORIAL)
                {
                    if (bn1<0)
                    {
                        return solution(temp, 1);
                    }
                    
                    else if (bn1==0)
                    {
                        return solution(bigNumber(1), 0);
                    }
                    
                    temp = bigNumber::factorial(bn1);
                    return solution(temp, 0);
                }
                
                else return solution(temp, 1);
            }
                
            //otherwise take ints from vector and use to set bigNumber2
            else 
            {
                for (int n=0; n<second.size(); n++)
                {  
                    int numberToUse = second.at(second.size()-n-1);
                    int locationToSet = PRECISION + n;
                    bn2.setDigit(locationToSet, numberToUse);
                    bn2.divideByTen(decimalCount2);
                }
            }
            
            //use problem type to calculate solution, return with no errors if valid
            switch(pType)
            {
                case ERROR: SHOWLINE;
                        return solution(temp, 1);
                
                case ADD: SHOWLINE;
                        temp = bn1 + bn2;
                        return solution(temp, 0);
                
                case SUBTRACT: SHOWLINE;
                        temp = bn1 - bn2;
                        return solution(temp, 0);
                        
                case MULTIPLY: SHOWLINE;
                        temp = bn1 * bn2;
                        return solution(temp, 0);      
                        
                case DIVIDE: SHOWLINE;
                        if (bn2==0)
                        {
                            return solution(temp,1);
                        }
                        temp = bn1 / bn2;
                        return solution(temp, 0);        
                        
                case FACTORIAL: SHOWLINE;
                        return solution(temp, 1);    
                   
                /*        
                case EXPONENT: temp = bn1 ^ bn2;
                        return solution(temp, 0);
                */
                
                case ITERATION: SHOWLINE;
                        temp = bigNumber::iterations(bn1, bn2);
                        return solution(temp, 0);
                
                default: SHOWLINE;
                        return solution(temp, 1);
            }
        }
    }
}

int main()
{
    string entered;
    PTYPE problemType = ERROR;
    bool exit = false;
    
    while (exit == false)
    {
        entered.clear();

        cout << "Enter an equation: ";
        
        std::getline(cin, entered);
        
        if (entered != "exit" && entered != "EXIT" && entered != "Exit")
        {
            solution answer(solve(entered));
        
            if (answer.getError()>0)
            {
                cout << "There has been an error";
            }
            
            else 
            {
                answer.getSolved().printNumber();
            }
        }
        
        else exit = true;
        
        cout << endl;
    }
}