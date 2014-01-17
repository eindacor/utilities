#include "headers.h"
#include "bignum_decs.h"
#include <string>

#define MAXENTERED 256
#define RETURN_ERROR return solution(bigNumber(), __LINE__)

#ifdef DEBUG
#define RETURN_OK(x) cout << "\t\t|" << __LINE__ << "|"; return solution(x, 0)

#else
#define RETURN_OK(x) return solution(x, 0)
#endif


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
    
    if (i>=0 && i<=9)
	{
        return i;
	}
        
    else
    {
        i = 10 + (c - 'A');
        return i;
    }
}

bool checkSpace(char const &c)
{
    return (c == ' ');
}

bool isNumber(char const &c, settings &user)
{
	return (checkNumber(c) >= 0 && checkNumber(c) <= (user.getBase()-1) );
}

bool isSymbol(char &c)
{
	return (checkSymbol(c) != ERROR);
}

void displayNumber(bigNumber &bn, settings &user, bool exact, bool stats)
{
	if (exact)
		bn.printNumber();

	else
	{
		int actualDigits = bn.getDigitCount() - (PRECISION-bn.getDecimalCount());
		
		if (user.getPercent())
		{
			bn.printPercent(user.getRound());
		}
					
		else 
		{
		    bn.printNumber(user.getRound());
		}

		if (user.getShowDigits() && stats==true)
		{
			cout << endl;
			cout << "Digits: ";
			if (bn<1 && bn > -1 && bn != 0)
				cout << actualDigits - 1;

			else cout << actualDigits;

			cout << "\nDecimal places: " << bn.getDecimalCount();
			cout << "\nBase: " << bn.getBase();
		}
	}
}

bigNumber numberFromVector(vector<int> &vec, bool neg, int dec, settings &user)
{
	bigNumber temp;
	temp.setBase(user.getBase());

	for (int i=0; i<vec.size(); i++)
	{
		int numberToUse = vec.at(vec.size()-i-1);
		int locationToSet = PRECISION + i;
		temp.setDigit(locationToSet, numberToUse);
	}
	
	if (neg)
		temp.setNegative();

	temp.divideByTen(dec);

	return temp;
}

solution solve(string &c, bigNumber previous, settings &user)
{
    c += '$';
    PTYPE pType=ERROR;
    
    vector<int> first;
    vector<int> second;
    bigNumber bn1;
    bigNumber bn2;
    bigNumber temp;
    
    bn1.setBase(user.getBase());
    bn2.setBase(user.getBase());
    temp.setBase(user.getBase());

    int decimalCount1=0;
    int decimalCount2=0;
    int numbers=0;

    bool decimal=false;
	bool negative1=false;
	bool negative2=false;
    bool done=false;
	bool printExact=false;
	bool printStats=false;

    bigNumber* targetBN = &bn1;
    vector<int>* targetVec = &first;
    int* targetDec = &decimalCount1;
	bool* targetNegative = &negative1;
    
    for (int i=0; i<c.size(); i++)
    {
		//if it isn't a space, number, symbol, end marker, or decimal point, return error
		if (checkSpace(c[i])==false && isNumber(c[i], user)==false && isSymbol(c[i])==false && c[i] != '$' && c[i] != '.')
		{
			RETURN_ERROR;
		}
			
		//if it's a space
		else if (checkSpace(c[i])==true)
		{
			//if it's preceeded by a number, number is complete
			if (isNumber(c[i-1], user))
		    {
		        done = true;
		    }
		    
		    //if negative is set, and it is preceeded by a minus symbol, return error
		    else if (checkSymbol(c[i-1]) == SUBTRACT && *targetNegative == true)
		    {
		        RETURN_ERROR;
		    }
		}

        //if it's a number
        else if (isNumber(c[i], user))
        {        
            //if number was complete, return error
            if (done==true)
			{
                RETURN_ERROR;
			}
                
            //otherwise add number to target vector, add decimal count if needed
            else 
            {
                (*targetVec).push_back(checkNumber(c[i]));
                numbers++;
                
                if (decimal==true)
				{
                    (*targetDec)++;
				}
            }
        }
        
        //if it's a minus symbol
        else if (checkSymbol(c[i]) == SUBTRACT)
        {
            //if no numbers have been added
            if (numbers==0)
            {
                //if target isn't negative, make target negative
                if ((*targetNegative)==false)
                {
                    (*targetNegative) = true;
                    (*targetBN).setNegative();
                }
                
                //if target is negative, no numbers have been added, and the target is the first number: 
				//there are two minus symbols, which means the intent is to 
				//subtract a negative number from previous
                else if (targetBN == &bn1)
                {
                    pType = SUBTRACT;
                    targetBN = &bn2;
                    numbers=0;
                    bn2.setNegative(); //sets 2nd number to negative
					negative2=true; //sets 2nd number to negative
                    targetNegative= &negative2;
                    done=false;
                    targetDec = &decimalCount2;
                    targetVec = &second;
                    decimal=false;
                }
                
                else 
				{
					RETURN_ERROR;
				}
            }
            
            //if numbers have been added, and the target is the first number, the problem type is subtraction
            else if (targetBN == &bn1)
            {
                pType = SUBTRACT;
                numbers=0;
                done=false;
                targetBN = &bn2;
				targetNegative= &negative2;
                targetDec = &decimalCount2;
                targetVec = &second;
                decimal=false;
            }
            
            //if numbers have been added, and the target is the second number, return error
            else 
			{
				RETURN_ERROR;
			}
        }
        
        //if it's a symbol other than minus
        else if (checkSymbol(c[i]) != ERROR && checkSymbol(c[i]) != SUBTRACT)
        {
            //if the type is already established, return error
            if (pType != ERROR)
			{
            	RETURN_ERROR;
			}
                
            //otherwise, set problem type based on symbol and reset figures
            else 
            {
                pType = checkSymbol(c[i]);
                targetBN = &bn2;
                numbers=0;
                done=false;
				targetNegative = &negative2;
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
                RETURN_ERROR;
			}
                
            else decimal = true;
        }
        
        //if it's an endline character
        else if (c[i] == '$')
        {
			SHOWNUMBER(bn1);
			SHOWNUMBER(bn2);

			//if both numbers are empty
			if (first.size()==0 && second.size()==0)
			{
				if (pType==FACTORIAL)
				{
					bn1 = previous;
					SHOWNUMBER(bn1);
				}

				else RETURN_ERROR;
			}

			//if first number is empty, set bn1 to previous
			if (first.size()==0)
				{
					bn1 = previous;
					SHOWNUMBER(bn1);
				}

			//otherwise create bn1 from entered and print it as is
            else
            {   
				bn1 = numberFromVector(first, negative1, decimalCount1, user);
				SHOWNUMBER(bn1);
				printExact=true;
            }
            
            //if second number is empty
            if (second.size()==0)
            {               
                //if first number is negative and pType is undefined, subtract number from previous
                if (negative1==true && pType == ERROR)
                {
					bn1.setPositive();
					SHOWNUMBER(previous);
					SHOWNUMBER(bn1);
                    temp = previous - bn1;
					SHOWNUMBER(temp);

					cout << "Entered: "; 
					displayNumber(previous, user, false, false);
					cout << " - "; 
					displayNumber(bn1, user, true, false);

					RETURN_OK(temp);
					//return solution(temp, 0);
                }
                
                //if first number isn't negative and no problem type has been declared, return that number
                else if (pType == ERROR)
                {
					cout << "Entered: "; 
					displayNumber(bn1, user, true, false);
					RETURN_OK(bn1);
                    //return solution(bn1, 0);
                }
               
                else if (pType != FACTORIAL)
                {
                    RETURN_ERROR;
                }
            }
                
            //otherwise take ints from second vector and use to set bigNumber2
            else 
            {
                bn2 = numberFromVector(second, negative2, decimalCount2, user);
				SHOWNUMBER(bn2);
            }

			cout << "Entered: ";
			displayNumber(bn1, user, printExact, printStats);

			SHOWNUMBER(bn1);
			SHOWNUMBER(bn2);

            //use problem type to calculate solution, return with no errors if valid
            switch(pType)
            {
                case ERROR: RETURN_ERROR;
                
                case ADD: cout << " + "; bn2.printNumber();
                    temp = bn1 + bn2;
					SHOWNUMBER(temp);
					RETURN_OK(temp);
                
                case SUBTRACT: cout << " - "; bn2.printNumber();
					temp = bn1 - bn2;
					SHOWNUMBER(temp);
					RETURN_OK(temp);
                        
                case MULTIPLY: cout << " * "; bn2.printNumber();
					temp = bn1 * bn2;
					SHOWNUMBER(temp);
					RETURN_OK(temp);
                        
                case DIVIDE: cout << " / "; bn2.printNumber();
                    if (bn2==0)
                    {
                        RETURN_ERROR;
                    }
                    temp = bn1 / bn2;
					SHOWNUMBER(temp);
					RETURN_OK(temp);
                        
                case FACTORIAL: 
					if (bn1<0 || bn1.getDecimalCount() > 0)
                    {
						RETURN_ERROR;
                    }
                    
                    else if (bn1==0)
                    {
						cout << "!";
						bigNumber fact(1);
						fact.setBase(user.getBase());
						RETURN_OK(fact);
                    }
                    
                    temp = bigNumber::factorial(bn1);
					cout << "!";
					SHOWNUMBER(temp);
					RETURN_OK(temp);    
                   
                case EXPONENT: cout << "^"; bn2.printNumber();
					temp = bigNumber::exponent(bn1, bn2);
					SHOWNUMBER(temp);
					RETURN_OK(temp);
                    //return solution(temp, 0);
                
                case ITERATION: cout << "c"; bn2.printNumber();
					temp = bigNumber::iterations(bn1, bn2);
					SHOWNUMBER(temp);
					RETURN_OK(temp);
                    //return solution(temp, 0);
                
                default: RETURN_ERROR;
            }
        }
    }
}

void modifySettings(settings &user)
{
    cout << endl;
    string setI;
    string setS;
    bool invalid=false;
    int intSet=0;
    
    do
    {
		intSet=0;
        invalid=false;
        setI.clear();
        
        cout << "Enter desired precision: ";
        std::getline(cin, setI);
        
        for (int i=0; i<setI.size(); i++)
        {
			int target = setI.size()-i-1;
			
            if (checkNumber(setI[target]) < 0 || checkNumber(setI[target]) > 9)
            {
                cout << "Invalid entry" << endl << endl;
                invalid=true;
                break;
            }
            
            else intSet += (checkNumber(setI[target]) * pow(10, i));
        }
        
        if (invalid==false)
        {
            if (intSet>PRECISION)
            {
                cout << "Invalid entry (precision must be between 0 and " << PRECISION << ")" << endl << endl;
                invalid=true;
            }
            
            else 
            {
                user.setRound(intSet);
            }
        }
    } while (invalid==true);
    
    do
    {
		intSet=0;
        invalid=false;
        setI.clear();
        
        cout << "Enter desired base: ";
        std::getline(cin, setI);
        
        for (int i=0; i<setI.size(); i++)
        {
			int target = setI.size()-i-1;
			
            if (checkNumber(setI[target]) < 0 || checkNumber(setI[target]) > 9 )
            {
                cout << "Invalid entry" << endl << endl;
                invalid=true;
                break;
            }
            
            else intSet += (checkNumber(setI[target]) * pow(10, i));
        }
    
        
        if (invalid==false)
        {
            if (intSet < 2 || intSet > 36)
            {
                cout << "Invalid entry (base must be between 2 and 36)" << endl << endl;
                invalid=true;
            }
            
            else 
            {
                user.setBase(intSet);
            }
        }
        
    } while (invalid==true);
    
    for (;;)
    {
      
        if (user.getPercent())
        {
            setS.clear();
            cout << "Turn off percentages? ";
            std::getline(cin, setS);
            
            if (setS=="yes" || setS=="y")
            {
                user.percentOff();
                break;
            }
            
            else if (setS=="no" || setS=="n")
            {
                break;
            }
            
            else
            {
                cout << "Invalid entry" << endl << endl;
                continue;
            }
        }
        
        else
        {
            setS.clear();
            cout << "Turn on percentages? ";
            std::getline(cin, setS);
            
            if (setS=="yes" || setS=="y")
            {
                user.percentOn();
                break;
            }
            
            else if (setS=="no" || setS=="n")
            {
                break;
            }
            
            else
            {
                cout << "Invalid entry" << endl << endl;
                continue;
            }
        }
    }

	for (;;)
    {
        setS.clear();
      
        if (user.getShowDigits())
        {
            cout << "Hide number stats? ";
            std::getline(cin, setS);
            
            if (setS=="yes" || setS=="y")
            {
                user.showDigitsOff();
                break;
            }
            
            else if (setS=="no" || setS=="n")
            {
                break;
            }
            
            else
            {
                cout << "Invalid entry" << endl << endl;
                continue;
            }
        }
        
        else
        {
            cout << "Show number stats? ";
            std::getline(cin, setS);
            
            if (setS=="yes" || setS=="y")
            {
                user.showDigitsOn();
                break;
            }
            
            else if (setS=="no" || setS=="n")
            {
                break;
            }
            
            else
            {
                cout << "Invalid entry" << endl << endl;
                continue;
            }
        }
    }
    
    cout << endl << endl;
}

int main(int argc, char** argv)
{
    settings user(10, false, false);
	bool commline=false;

	if (argc>1)
		commline=true;

	string entered;
    PTYPE problemType = ERROR;
    bool exit = false;
    bigNumber previous;
    previous.updateDigits();
    
    while (exit == false)
    {     
    	if (commline==false)
		{
			entered.clear();

            if (previous.getBase() != user.getBase())
                previous.convertBase(user.getBase());

			cout << "\n";
            displayNumber(previous, user, false, true);
			cout << "\n\n";

			std::getline(cin, entered);
            
			cout << "-----------------------" << endl;

			if (entered == "settings" || entered == "options" || entered == "preferences")
            {
                modifySettings(user);
                continue;
            }

			if (entered == "STATS" || entered == "stats" || entered == "Stats")
			{
				displayNumber(previous, user, false, true);
				continue;
			}
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
            solution answer(solve(entered, previous, user));
      
            if (answer.getError()>0)
            {
                cout << endl << "Invalid Input (Error " << answer.getError() << ")";
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
