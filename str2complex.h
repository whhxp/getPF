#ifndef STR2COMPLEX_H
#define STR2COMPLEX_H
#include <complex>
#include <iostream>
#include <regex>
class Str2complex
{
public:
    Str2complex(std::string str);
    std::complex<float> str2complex(std::string str);
};

#endif // STR2COMPLEX_H
