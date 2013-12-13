#include "headers.h"
#include "bignum_decs.h"
#include <string>

#define MAXENTERED 256

//change checkSymbol() etc. to getSymbol()
//change checkNumber() to getNumber()


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

int checkNumber(char const &c)
{
    int i = c - '0';
    
    return i;
}

bool checkSpace(char const &c)
{
    return (c == ' ');
}

bool isNumber(char const &c)
{
	return (checkNumber(c) >= 0 && checkNumber(c) <= 9);
}

bool isSymbol(char &c)
{
	return (checkSymbol(c) != ERROR);
}

solution solve(string &c, bigNumber previous)
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
			if (checkSpace(c[i])==false && isNumber(c[i])==false && isSymbol(c[i])==false && c[i] != '@')
			{
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
				SHOWLINE;
				SHOWNUMBER(temp);
            return solution(temp, 1);
        }
        
        //if it's a number
        else if (checkNumber(c[i]) >= 0 && checkNumber(c[i]) <= 9)
        {
            
            //if number was complete, return error
            if (done==true)
				{
					SHOWLINE;
					SHOWNUMBER(temp);	
               return solution(temp, 1);
				}
                
            //otherwise add number to target vector, add decimal count if needed
            else 
            {
					DECLARE(c[i]);
                (*targetVec).push_back(checkNumber(c[i]));
                numbers++;
                
                if (decimal==true)
					 {
                    (*targetDec)++;
							DECLARE(*targetDec);
					 }
            }
        }
        
        //if it's a minus symbol
        else if (checkSymbol(c[i]) == SUBTRACT)
        {
            //if no numbers have been added
            if (numbers==0)
            {
                //if negative hasn't been set, the target is a negative number
                if (negative==false)
                {
                    (*targetBN).setNegative();
                    negative = true;
                }
                
                //if negative has been set, and this is the first number, the intention is to subtract a negative number from previous
                else if (targetBN == &bn1)
                {
                    pType = SUBTRACT;
                    targetBN = &bn2;
                    numbers=0;
                    bn2.setNegative();
                    negative=true; //sets 2nd number to negative
                    done=false;
                    targetDec = &decimalCount2;
                    targetVec = &second;
                    decimal=false;
                }
                
                else 
					 {
						SHOWLINE;
						SHOWNUMBER(temp);
						return solution(temp, 1);
					 }
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
                decimal=false;
            }
            
            //if numbers have been added, and the target is the second number, return error
            else 
				{
					SHOWLINE;
					SHOWNUMBER(temp);
					return solution(temp, 1);
				}
        }
        
        //if it's a symbol other than minus
        else if (checkSymbol(c[i]) != ERROR && checkSymbol(c[i]) != SUBTRACT)
        {
            //if the type is already established, return error
            if (pType != ERROR)
				{
					SHOWLINE;
					DECLARE(c[i]);
					SHOWNUMBER(temp);
                return solution(temp, 1);
				}
                
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
                decimal=false;
            }
        }
        
         //if it's a decimal point
        else if (c[i]=='.')
        {
            //if there's already been a decimal point, return error
            if (decimal==true)
				{
					SHOWLINE;
					SHOWNUMBER(temp);
                return solution(temp, 1);
				}
                
            else decimal = true;
        }
        
        //if it's an endline character
        else if (c[i] == '@')
        {
            //if negative was declared, the first number is empty, the second number is not, and the problem type is subtract, subtract second from previous
            if (negative==true && first.size()==0 && second.size()>0 && pType == SUBTRACT)
            {
                for (int n=0; n<second.size(); n++)
                {
                    int numberToUse = second.at(second.size()-n-1);
                    int locationToSet = PRECISION + n;
                    bn2.setDigit(locationToSet, numberToUse);
							SHOWLINE;
							SHOWNUMBER(bn2);
                    bn2.divideByTen(decimalCount2);
							SHOWNUMBER(bn2);
                }
                
                temp = previous - bn2;
                SHOWLINE;
					 SHOWNUMBER(temp);
						cout << "Entered: "; previous.printNumber(); cout << " - "; bn2.printNumber();
                return solution(temp, 0);
            }
            
            //if first number is empty, set first number to previous
            if (first.size()==0)
                bn1 = previous;
                
            //otherwise take ints from vector and use to set bigNumber1
            else 
            {
                for (int n=0; n<first.size(); n++)
                {
                    int numberToUse = first.at(first.size()-n-1);
							DECLARE(numberToUse);
                    int locationToSet = PRECISION + n;
							DECLARE(locationToSet);
                    bn1.setDigit(locationToSet, numberToUse);
							SHOWLINE;
							SHOWNUMBER(bn1);
                }
					SHOWLINE;
					SHOWNUMBER(bn1);
					bn1.divideByTen(decimalCount1);
					SHOWNUMBER(bn1);
            }
            
            //if second number is empty
            if (second.size()==0)
            {
                //if problem type is factorial, return factorial of first number
                if (pType == FACTORIAL)
                {
                    if (bn1<0)
                    {
								SHOWLINE;
								SHOWNUMBER(temp);
								bn1.printNumber(); cout << "!";
                        return solution(temp, 1);
                    }
                    
                    else if (bn1==0)
                    {
								SHOWLINE;
								SHOWNUMBER(temp);
								bn1.printNumber(); cout << "!";
                        return solution(bigNumber(1), 0);
                    }
                    
                    temp = bigNumber::factorial(bn1);
							SHOWLINE;
							SHOWNUMBER(temp);
							bn1.printNumber(); cout << "!";
                    return solution(temp, 0);
                }
                
                //if negative was declared, subtract number from previous
                else if (negative==true && first.size()>0 && second.size()==0)
                {
                    for (int n=0; n<first.size(); n++)
                    {
                        int numberToUse = first.at(first.size()-n-1);
                        int locationToSet = PRECISION + n;
                        bn1.setDigit(locationToSet, numberToUse);
                    }

							SHOWLINE;
							SHOWNUMBER(bn1);
							bn1.divideByTen(decimalCount1);
							SHOWNUMBER(bn1);
                    
                    temp = previous - bn1.absolute();
							SHOWLINE;
							SHOWNUMBER(temp);
							cout << "Entered: "; previous.printNumber(); cout << " - "; bn1.absolute().printNumber();
                    return solution(temp, 0);
                }
                
                //if negative wasn't declared and a number is entered, return that number
                else if (pType == ERROR)
                {
                    if (first.size()==0)
                    {
								SHOWLINE;
								SHOWNUMBER(previous);
								cout << "Entered: "; bn1.printNumber(); cout << " + "; bn2.printNumber();
                        return solution(previous, 0);
                    }
                    
                    else
                    {
                        for (int n=0; n<first.size(); n++)
                        {
                            int numberToUse = first.at(first.size()-n-1);
                            int locationToSet = PRECISION + n;
                            bn1.setDigit(locationToSet, numberToUse);
                        }

								SHOWLINE;
								SHOWNUMBER(bn1);
								bn1.divideByTen(decimalCount1);
								SHOWNUMBER(bn1);
                    }
                    
							SHOWLINE;
							SHOWNUMBER(bn1);
							cout << "Entered: "; bn1.printNumber();
                    return solution(bn1, 0);
                }
                
                else 
					 {
							SHOWLINE;
							SHOWNUMBER(temp);
							return solution(temp, 1);
					 }
            }
                
            //otherwise take ints from vector and use to set bigNumber2
            else 
            {
                for (int n=0; n<second.size(); n++)
                {  
                    int numberToUse = second.at(second.size()-n-1);
                    int locationToSet = PRECISION + n;
                    bn2.setDigit(locationToSet, numberToUse);
                }

					SHOWLINE;
					SHOWNUMBER(bn2);
					bn2.divideByTen(decimalCount2);
					SHOWNUMBER(bn2);
            }
            

            //use problem type to calculate solution, return with no errors if valid
            switch(pType)
            {
                case ERROR: return solution(temp, 1);
                
                case ADD: cout << "Entered: "; bn1.printNumber(); cout << " + "; bn2.printNumber();
								temp = bn1 + bn2;
                        return solution(temp, 0);
                
                case SUBTRACT: cout << "Entered: "; bn1.printNumber(); cout << " - "; bn2.printNumber();
								temp = bn1 - bn2;
                        return solution(temp, 0);
                        
                case MULTIPLY: cout << "Entered: "; bn1.printNumber(); cout << " * "; bn2.printNumber();
								temp = bn1 * bn2;
                        return solution(temp, 0);      
                        
                case DIVIDE: cout << "Entered: "; bn1.printNumber(); cout << " / "; bn2.printNumber();
                        if (bn2==0)
                        {
                            return solution(temp,1);
                        }
                        temp = bn1 / bn2;
                        return solution(temp, 0);        
                        
                case FACTORIAL: return solution(temp, 1);    
                   
                case EXPONENT: cout << "Entered: "; bn1.printNumber(); cout << "^"; bn2.printNumber();
								temp = bigNumber::exponent(bn1, bn2);
                        return solution(temp, 0);
                
                case ITERATION: cout << "Entered: "; bn1.printNumber(); cout << "c"; bn2.printNumber();
								temp = bigNumber::iterations(bn1, bn2);
                        return solution(temp, 0);
                
                default: return solution(temp, 1);
            }
        }
    }
}

int main(int argc, char** argv)
{
	bool commline=false;

	if (argc>1)
		commline=true;

	 string entered;
    PTYPE problemType = ERROR;
    bool exit = false;
    bigNumber previous;
    
    while (exit == false)
    {      		
		if (commline==false)
		{
			entered.clear();

			previous.printNumber();
			cout << "\n";

			std::getline(cin, entered);
			cout << "-----------------------" << endl;
		}

		else 
		{
			entered.clear();
			for (int i=1; i<argc; i++)
			{
				entered += argv[i];
			}
			commline=false;
		}

        
        if (entered != "exit" && entered != "EXIT" && entered != "Exit")
        {
            solution answer(solve(entered, previous));
        
            if (answer.getError()>0)
            {
                cout << "Invalid Input";
            }
            
            else 
            {
                previous = answer.getSolved();
            }
        }
        
        else exit = true;
        
        cout << endl;
    }
}
