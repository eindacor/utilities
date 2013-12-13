#ifndef BIGNUM_DECS_H
#define BIGNUM_DECS_H

enum PTYPE {ERROR, ADD, SUBTRACT, MULTIPLY, DIVIDE, EXPONENT, LESSTHAN, LESSTHANEQUALS, GREATERTHAN, GREATERTHANEQUALS, EQUALS, FACTORIAL, ITERATION};

class bigNumber
{
	public:
		bigNumber(vector<int> n);
		bigNumber();
		bigNumber(int n);
		~bigNumber() {};    

		int getDigit(int n) {return digits[n];}
		void setDigit(int n, int s) {digits[n] = s; updateDigits();}
		int getDigitCount();
		int getDecimalCount();
		int printNumber();
		int printNumber(int n);
		void printPercent();
		void printPercent(int n);
		void printStats();
		bool getNegative() {return negative;}
		void updateDigits();
		void adjustPrecision(int n);
		void query (int n);

		void timesTen (int n);
		void divideByTen (int n);
		
		void setNegative() {negative = true;}
		void setPositive() {negative = false;}
		
		bool operator < (bigNumber b); 
		bool operator <= (bigNumber b); 
		bool operator < (int n);
		bool operator <= (int n);

		bool operator > (bigNumber b);
		bool operator >= (bigNumber b);
		bool operator > (int n);
		bool operator >= (int n);

		bool operator == (bigNumber b); 
		bool operator == (int n);   
		bool operator != (bigNumber b);
		bool operator != (int n); 

		void operator += (bigNumber b);    
		void operator -= (bigNumber b);
		void operator *= (bigNumber b);
		void operator /= (bigNumber b);
		void operator -- (int);
		void operator ++ (int);
		void operator = (bigNumber b);

		bigNumber operator * (bigNumber b);
		bigNumber operator * (int n);
		bigNumber operator / (bigNumber b);
		bigNumber operator / (int n);
		bigNumber operator + (bigNumber b);
		bigNumber operator + (int n);
		bigNumber operator - (bigNumber b);
		bigNumber operator - (int n);
		bigNumber absolute();
		bigNumber noDecimal();
		
		static bigNumber addNumbers(bigNumber &bn1, bigNumber &bn2);
        static bigNumber subtractNumbers(bigNumber &bn1, bigNumber &bn2);
        static bigNumber multiplyNumbersSimple(bigNumber bn1, int n);
        static bigNumber multiplyNumbers(bigNumber &bn1, bigNumber &bn2);
        static int divideNumbersSimple (bigNumber bn1, bigNumber bn2, bool &r);
        static bigNumber divideNumbers(bigNumber bn1, bigNumber bn2);
        static bigNumber factorial(bigNumber bn);
        static bigNumber iterations(bigNumber bn1, bigNumber bn2);
        static bigNumber exponent(bigNumber bn1, bigNumber bn2);
        static bigNumber fibonacci(bigNumber bn1);
        static bigNumber fibonacci(int n);

		void decrement();

	private:
		int digits[MAXDIGITS];
		int digitCount;
		int decimalCount;
		bool negative;
};

class solution
{
    public:
        solution(bigNumber bn, int n): solved(bn), error(n) {};
        ~solution(){};
        
        bigNumber getSolved() {return solved;}
        int getError() {return error;}
    
    private:
        bigNumber solved;
        int error;
};

class settings
{
    public:
        settings() {round = 10; percent = false;}
        settings(int n, bool b) {round = n; percent = b;}
        ~settings(){};
        
        void setRound(int n);
        void percentOff() {percent=false;}
        void percentOn() {percent=true;}
        
        int getRound() {return round;}
        bool getPercent() {return percent;}
    
    private:
        int round;
        bool percent;
};

#endif
