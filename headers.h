#ifndef HEADERS_H //1
#define HEADERS_H

#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

#ifndef MAXDIGITS
#define MAXDIGITS 1000
#endif


#ifdef P20
	#define PRECISION 20
	#define PI "314159265358979323846"
	#define THETA "161803398874989484820"

#else
	#ifdef P30
		#define PRECISION 30
		#define PI "3141592653589793238462643383279"
		#define THETA "1618033988749894848204586834365"

	#else
		#ifdef P40
			#define PRECISION 40
			#define PI "31415926535897932384626433832795028841971"
			#define THETA "16180339887498948482045868343656381177203"

		#else
			#ifdef P50
				#define PRECISION 50
				#define PI "314159265358979323846264338327950288419716939937510"
				#define THETA "161803398874989484820458683436563811772030917980576"


			#else 
			#define PRECISION 100
			#define PI "31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
			#define THETA "16180339887498948482045868343656381177203091798057628621354486227052604628189024497072072041893911374"

			#endif
		#endif
	#endif
#endif

#ifdef NOCOMMAS
#define COMMA 
#else 
#define COMMA cout << ","
#endif

#ifdef DEBUG
#define SHOWNUMBER(x) cout << endl << __FILE__ << " (line " << __LINE__ << ") :\t" << #x << "= " ; x.printNumber(); cout << endl
#define QUERYNUMBER(x) cout << endl << __FILE__ << " (line " << __LINE__ << "), " << #x << ":\n" ; x.query(); cout << endl
#define DECLARE(x) cout << endl << __FILE__ << " (line " << __LINE__ << ") :\t" << #x << "= " << x
#define SHOW(x) cout << endl << __FILE__ << " (line " << __LINE__ << ") :\t" << #x << "= " << x
#define SHOWLINE cout << endl << endl << __FILE__ << ": " << __LINE__ << endl
#else
#define SHOWNUMBER(x)
#define QUERYNUMBER(x)
#define DECLARE(x)
#define SHOW(x)
#define SHOWLINE
#endif

#endif
