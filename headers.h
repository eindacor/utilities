#ifndef HEADERS_H //1
#define HEADERS_H

#include <iostream>
#include <vector>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

#define MAXDIGITS 1000
#define PRECISION 10

#ifdef NOCOMMAS //2
#define COMMA 
#else 
#define COMMA cout << ","
#endif //2

#ifdef DEBUG //3
#define DECLARE(x) cout << "\n\t|  DECLARATION: " << #x << "= " << x
#define SHOW(x) x
#define SHOWLINE cout << endl << endl << __LINE__ << endl
#else
#define DECLARE(x)
#define SHOW(x)
#define SHOWLINE
#endif //3

#endif //1