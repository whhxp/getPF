#ifndef POWERFACTOR_H
#define POWERFACTOR_H

#include <math.h>
#include <string>
#include "fftw3.h"
#include <complex>
#include <valarray>
#define PI 3.1415926535897932384626433832

#define DEBUG 0
#define ANGLE 1
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;


class powerFactor
{
public:
    powerFactor(int argc, std::string FileName1, std::string FileName2);
    powerFactor(int argc,std::string FileName1);

    float getPF() const;
    void setPF();

    void calc();

    int getMax() const;

    std::string getFileName() const;
    void setFileName(const std::string &value);

    std::string getFile1() const;
    void setFile1(const std::string &value);

    std::string getFile2() const;
    void setFile2(const std::string &value);

    void readCSV(std::string PFfile);
    void readCSV();
    void printArray(std::string name, CArray &n);
    void printArray(std::string name, Complex* complexArray);

    CArray fft(CArray a);
private:
    int argC;
    std::string file1;
    std::string file2;
    Complex voltageC[10000];
    Complex currentC[10000];
    double PF;
    int Max;
    const int size = 1000;
    int lineCount;
    Complex voltage[1000];
    Complex current[1000];
};

#endif // POWERFACTOR_H
