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

bool checkWord(string &c, int start, string compare)
{
    for (int i=0; i<compare.size(); i++)
    {
        if (c[start+i] != compare[i])
            return false;
    }
    
    return true;
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
    int commaNumbers=0;
    int numbers=0;

    bool decimal=false;
	bool comma=false;
	bool negative1=false;
	bool negative2=false;
    bool done=false;
	bool printExact=false;
	bool printStats=false;

    bigNumber* targetBN = &bn1;
    vector<int>* targetVec = &first;
    int* targetDec = &decimalCount1;
	bool* targetNegative = &negative1;
    
    int counter = c.size();
    
    for (int i=0; i<counter; i++)
    {
        if (checkWord(c, i, "pi"))
        {
            if (numbers>0 || comma==true || decimal==true)
            {
                RETURN_ERROR;
            }
            
            else
            {
                bigNumber piNumber = bigNumber::pi();
                piNumber.convertBase(user.getBase());
                if (*targetNegative==true)
                    piNumber.setNegative();
                    
                *targetBN = piNumber;
                
                done=true;
                first.push_back(0);
                
                numbers += (PRECISION+1);
                counter += 2;
                i += 2;
                
                SHOWNUMBER(piNumber);
                QUERYNUMBER(piNumber);
            }
        }
        
        if (checkWord(c, i, "theta"))
        {
            
        }
        
		//if it isn't a space, number, symbol, end marker, or decimal point, return error
		if (checkSpace(c[i])==false && 
			isNumber(c[i], user)==false && 
			isSymbol(c[i])==false && 
			c[i] != '$' && 
			c[i] != ',' && 
			c[i] != '.')
		{
			RETURN_ERROR;
		}

		if (c[i]==',')
		{
			if (comma==false)
			{
				if (decimal==true || numbers==0 || numbers > 3 || done==true)
					RETURN_ERROR;

				else comma = true;
			}

			else if (commaNumbers != 3)
			    RETURN_ERROR;
			    
			commaNumbers=0;    
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
			
		    if (comma==true)
		        commaNumbers++;
                
            //otherwise add number to target vector, add decimal count if needed
            (*targetVec).push_back(checkNumber(c[i]));
                numbers++;
                
            if (decimal==true)
			{
                (*targetDec)++;
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
					commaNumbers=0;
					comma=false;
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
                if (comma==true && decimal==false && commaNumbers != 3)
                    RETURN_ERROR;
                
                pType = SUBTRACT;
                numbers=0;
				commaNumbers=0;
				comma=false;
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
                if (comma==true && decimal==false && commaNumbers != 3)
                    RETURN_ERROR;
                
                pType = checkSymbol(c[i]);
                targetBN = &bn2;
                numbers=0;
				commaNumbers=0;
				comma=false;
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
            
            if (comma==true && commaNumbers != 3)
                RETURN_ERROR;
        }
        
        //if it's an endline character
        else if (c[i] == '$')
        {
            if (comma==true && decimal==false && commaNumbers != 3)
                    RETURN_ERROR;
                    
			//if both numbers are empty
			if (first.size()==0 && second.size()==0)
			{
				if (pType==FACTORIAL)
				{
					bn1 = previous;
				}

				else RETURN_ERROR;
			}

			//if first number is empty, set bn1 to previous
			if (first.size()==0)
				{
					bn1 = previous;
				}

			//otherwise create bn1 from entered and print it as is
            else
            {   
				bn1 = numberFromVector(first, negative1, decimalCount1, user);
				printExact=true;
            }
            
            //if second number is empty
            if (second.size()==0)
            {               
                //if first number is negative and pType is undefined, subtract number from previous
                if (negative1==true && pType == ERROR)
                {
					bn1.setPositive();
                    temp = previous - bn1;

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
            }

			cout << "Entered: ";
			displayNumber(bn1, user, printExact, printStats);
			
			break;
        }
    }
    
    //use problem type to calculate solution, return with no errors if valid
    switch(pType)
    {
        case ERROR: RETURN_ERROR;
        
        case ADD: cout << " + "; bn2.printNumber();
            temp = bn1 + bn2;
			RETURN_OK(temp);
        
        case SUBTRACT: cout << " - "; bn2.printNumber();
			temp = bn1 - bn2;
			RETURN_OK(temp);
                
        case MULTIPLY: cout << " * "; bn2.printNumber();
			temp = bn1 * bn2;
			RETURN_OK(temp);
                
        case DIVIDE: cout << " / "; bn2.printNumber();
            if (bn2==0)
            {
                RETURN_ERROR;
            }
            temp = bn1 / bn2;
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
			RETURN_OK(temp);    
           
        case EXPONENT: cout << "^"; bn2.printNumber();
			temp = bigNumber::exponent(bn1, bn2);
			RETURN_OK(temp);
        
        case ITERATION: cout << "c"; bn2.printNumber();
			temp = bigNumber::iterations(bn1, bn2);
			RETURN_OK(temp);
        
        default: RETURN_ERROR;
    }

}

void printHelp()
{
	cout << "This calculator accepts problems in the following formats:\n\n";
	cout << "\tAddition\n\t	12345.6789 + 98765.4321\n\n";
	cout << "\tSubtraction\n\t	12345.6789 - 98765.4321\n\n";
	cout << "\tMultiplication\n\t	12345.6789 * 98765.4321\n\n";
	cout << "\tDivision\n\t	12345.6789 / 98765.4321\n\n";
	cout << "\tExponent\n\t	12345.6789 ^ 98765.4321\n\n";
	cout << "\tFactorial\n\t	123!\n\n";
	cout << "- To use the previous value, enter the rest of the calculation like so: \"+ 12345\"\n\n";
	cout << "- To change bases, enter \"base 12\" or \"binary\", \"decimal\", etc.\n\n";
	cout << "- To show/hide statistics, enter \"show stats\" or \"hide stats\".\n\n";
	cout << "- To reset the calculator, enter \"clear\" or \"reset\".\n\n";
	cout << "- Problems can also be entered in the command line without spaces.\n\n";
	cout << "- To end your session, type \"exit\".\n\n";
	cout << "NOTE: Factorials and base conversions of large decimals can be very time\n";
	cout << "consuming. To exit out of the program mid-calculation, press ctrl+C.\n\n";
	
	//      "01234567890123456789012345678901234567890123456789012345678901234567890123456789"
}

bool changeBase(string &c, settings &user)
{
	if (c == "base 2" || c == "base2" || c == "binary")
	{
		user.setBase(2);
		return true;
	}
	
	if (c == "base 3" || c == "base3" || c == "ternary")
	{
		user.setBase(3);
		return true;
	}

	if (c == "base 4" || c == "base4" || c == "quaternary")
	{
		user.setBase(4);
		return true;
	}

	if (c == "base 5" || c == "base5" || c == "quinary")
	{
		user.setBase(5);
		return true;
	}

	if (c == "base 6" || c == "base6" || c == "senary")
	{
		user.setBase(6);
		return true;
	}

	if (c == "base 7" || c == "base7" || c == "septenary")
	{
		user.setBase(7);
		return true;
	}

	if (c == "base 8" || c == "base8" || c == "octonary")
	{
		user.setBase(8);
		return true;
	}

	if (c == "base 9" || c == "base9" || c == "nonary")
	{
		user.setBase(9);
		return true;
	}

	if (c == "base 10" || c == "base10" || c == "decimal")
	{
		user.setBase(10);
		return true;
	}

	if (c == "base 11" || c == "base11" || c == "undenary")
	{
		user.setBase(11);
		return true;
	}

	if (c == "base 12" || c == "base12" || c == "dozenal" || c == "duodecimal")
	{
		user.setBase(12);
		return true;
	}

	if (c == "base 13" || c == "base13" || c == "tridecimal")
	{
		user.setBase(13);
		return true;
	}

	if (c == "base 14" || c == "base14" || c == "quattuordecimal")
	{
		user.setBase(14);
		return true;
	}

	if (c == "base 15" || c == "base15" || c == "quindecimal")
	{
		user.setBase(15);
		return true;
	}

	if (c == "base 16" || c == "base16" || c == "sexadecimal" || c == "hexadecimal")
	{
		user.setBase(16);
		return true;
	}

	if (c == "base 17" || c == "base17" || c == "septendecimal")
	{
		user.setBase(17);
		return true;
	}

	if (c == "base 18" || c == "base18" || c == "octodecimal")
	{
		user.setBase(18);
		return true;
	}

	if (c == "base 19" || c == "base19" || c == "nonadecimal")
	{
		user.setBase(19);
		return true;
	}

	if (c == "base 20" || c == "base20" || c == "vigesimal")
	{
		user.setBase(20);
		return true;
	}

	if (c == "base 21" || c == "base21")
	{
		user.setBase(21);
		return true;
	}

	if (c == "base 22" || c == "base22")
	{
		user.setBase(22);
		return true;
	}

	if (c == "base 23" || c == "base23")
	{
		user.setBase(23);
		return true;
	}

	if (c == "base 24" || c == "base24")
	{
		user.setBase(24);
		return true;
	}

	if (c == "base 25" || c == "base25")
	{
		user.setBase(25);
		return true;
	}

	if (c == "base 26" || c == "base26")
	{
		user.setBase(26);
		return true;
	}

	if (c == "base 27" || c == "base27")
	{
		user.setBase(27);
		return true;
	}

	if (c == "base 28" || c == "base28")
	{
		user.setBase(28);
		return true;
	}

	if (c == "base 29" || c == "base29")
	{
		user.setBase(29);
		return true;
	}

	if (c == "base 30" || c == "base30")
	{
		user.setBase(30);
		return true;
	}

	if (c == "base 31" || c == "base31")
	{
		user.setBase(31);
		return true;
	}

	if (c == "base 32" || c == "base32")
	{
		user.setBase(32);
		return true;
	}

	if (c == "base 33" || c == "base33")
	{
		user.setBase(33);
		return true;
	}

	if (c == "base 34" || c == "base34")
	{
		user.setBase(34);
		return true;
	}

	if (c == "base 35" || c == "base35")
	{
		user.setBase(35);
		return true;
	}

	if (c == "base 36" || c == "base36")
	{
		user.setBase(36);
		return true;
	}

	return false;
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
	cout << endl << "Welcome to BigNum! Enter \"help\" for assistance." << endl << endl;

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

			if (changeBase(entered, user))
			{
				continue;
			}
			
			if (entered == "clear" || entered == "reset")
			{
			    bigNumber reset(0);
			    reset.setBase(user.getBase());
			    previous = reset;
				continue;
			}

			if (entered == "settings" || entered == "options" || entered == "preferences")
            {
                modifySettings(user);
                continue;
            }
			
			if (entered == "show stats")
			{
			    cout << "\nNumber stats are visible\n\n";
			    user.showDigitsOn();
				continue;
			}
			
			if (entered == "hide stats")
			{
			    cout << "\nNumber stats are hidden\n\n";
			    user.showDigitsOff();
				continue;
			}

			if (entered == "help")
			{
				printHelp();
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
