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
#define MAXDIGITS 3000
#endif


#ifdef P20
	#define PRECISION 20

#else
	#ifdef P30
		#define PRECISION 30

	#else
		#ifdef P40
			#define PRECISION 40

		#else
			#ifdef P50
				#define PRECISION 50

			#else 
			#define PRECISION 100
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
