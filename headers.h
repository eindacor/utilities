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

#ifndef MAXDIGITS //2
#define MAXDIGITS 3000
#endif //2

#ifndef PRECISION //3
#define PRECISION 100
#endif //3

#ifdef NOCOMMAS //4
#define COMMA 
#else 
#define COMMA cout << ","
#endif //4

#ifdef DEBUG //5
#define SHOWNUMBER(x) cout << endl << #x << "= " ; x.printNumber(); cout << endl
#define DECLARE(x) cout << "\n\t|  DECLARATION: " << #x << "= " << x
#define SHOW(x) x
#define SHOWLINE cout << endl << endl << __FILE__ << ": " << __LINE__ << endl
#else
#define SHOWNUMBER(x)
#define DECLARE(x)
#define SHOW(x)
#define SHOWLINE
#endif //5

#endif //1
