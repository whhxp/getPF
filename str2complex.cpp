#include "str2complex.h"

Str2complex::Str2complex(std::__cxx11::string str)
{
}

std::complex<float> Str2complex::str2complex(std::__cxx11::string str)
{
    std::smatch m;
    std::regex e("(-?\\d+.?\\d*)\\s([+|-])\\s(\\d+.?\\d*)i");  // matches words beginning by "sub"
//    std::cout << "Target sequence: " << str << std::endl;
    std::complex<float> result;
    std::string real, img, opt;
//    std::cout << "Regular expression: (-?\\d+.?\\d*)\\s*(+|-?\\d+.?\\d*)i" << std::endl;
//    std::cout << "The following matches and submatches were found:" << std::endl;

    while (std::regex_search(str, m, e))
    {
//        for (auto x = m.begin(); x != m.end(); x++)
//        {
//            std::cout << x->str() << " ";
//        }
//        std::cout << "--> ([^ ]*) match " << m.format("$2") << std::endl;
//
        real = m.format("$1");
        opt = m.format("$2");
        img = m.format("$3");
//        std::cout<<"real="<<real<<" opt="<<opt<<" img="<<img<<std::endl<<"--------"<<std::endl;
        str = m.suffix().str();
    }

    result.real(stof(real));
    if (opt[0] == '-')
        img.insert(0,"-");
    result.imag(stof(img));

    return result;
}
