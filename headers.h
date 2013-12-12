#ifndef HEADERS_H //1
#define HEADERS_H

#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

#ifndef MAXDIGITS //2
#define MAXDIGITS 1000
#endif //2

#ifndef PRECISION //3
#define PRECISION 10
#endif //3

#ifdef NOCOMMAS //4
#define COMMA 
#else 
#define COMMA cout << ","
#endif //4

#ifdef DEBUG //5
#define DECLARE(x) cout << "\n\t|  DECLARATION: " << #x << "= " << x
#define SHOW(x) x
#define SHOWLINE cout << endl << endl << __LINE__ << endl
#else
#define DECLARE(x)
#define SHOW(x)
#define SHOWLINE
#endif //5

#endif //1