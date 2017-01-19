
#include "fftw3.h"
#include "powerfactor.h"
#include "csv.h"
#include <QtCore>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{

//    QString a = "inf";
//    std::cout<<a.toDouble()<<std::endl;
    if (argc > 3 || argc < 2 )
    {
        std::cout<<"Usage:"<<std::endl
                <<"getPF [file1] [file2]"<<std::endl;
        exit(-1);
    }
//Get fft data directly
//    powerFactor pf(argv[1], argv[2]);
//    pf.setPF();
//    std::cout<<"__PowerFactor="<<pf.getPF()<<std::endl;
    powerFactor *pf1;
    switch (argc) {
    case 2:
        pf1 = new powerFactor(argc, argv[1]);
        pf1->readCSV(argv[1]);
        break;
    case 3:
        pf1 = new powerFactor(argc, argv[1],argv[2]);
        pf1->readCSV();
        break;
    default:
        break;
    }
    pf1->calc();
    std::cout<<"__PowerFactor="<<pf1->getPF()<<std::endl;

    delete pf1;
    return 0;
}
