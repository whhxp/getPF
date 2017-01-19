#include "powerfactor.h"
#include "csv.h"

#include "str2complex.h"
#include "fftw3.h"

powerFactor::powerFactor(int argc, std::string FileName1, std::string FileName2)
{
    setFile1(FileName1);
    setFile2(FileName2);
}

powerFactor::powerFactor(int argc, std::__cxx11::string FileName1)
{
    setFile1(FileName1);
}

float powerFactor::getPF() const
{
    return PF;
}

void powerFactor::setPF()
{
    std::string data1;
    double time;
    io::CSVReader<2> voltageCSV(file1);
    voltageCSV.next_line();
    for (lineCount = 0; voltageCSV.read_row(time, data1); lineCount++)
    {
        Str2complex conv("voltage");
        voltage[lineCount] = conv.str2complex(data1);
    }
//    std::cout<<lineCount<<std::endl;
    io::CSVReader<2> currentCSV(file2);
    currentCSV.next_line();
    for (lineCount = 0; currentCSV.read_row(time, data1); lineCount++)
    {
        Str2complex conv("current");
        current[lineCount] = conv.str2complex(data1);
    }
    printArray("Voltage", voltage);
    printArray("Current", current);
    CArray voltageArray(voltage, lineCount);
    CArray currentArray(current, lineCount);
    CArray magVoltage(lineCount);
    CArray magCurrent(lineCount);
    magVoltage = std::abs(voltageArray);
    magCurrent = std::abs(currentArray);
    printArray("MagVoltage", magVoltage);
    printArray("MagCurrent", magCurrent);
    int volFlag = 0;
    int curFlag = 0;
    float max = 0;
    for (unsigned int i = 0; i < magVoltage.size(); i++)
    {
        if (magVoltage[i].real() > max)
        {
            max = magVoltage[i].real();
            volFlag = i;
        }
    }
    float phaVol = std::arg(voltageArray[volFlag]);
    std::cout << "Max number in voltage array " << volFlag << ", value is " <<
        voltageArray[volFlag] << " angle = " <<
        phaVol / PI * 180 <<
        std::endl;

    max = 0;
    for (unsigned int i = 0; i < magCurrent.size(); i++)
    {
        if (magCurrent[i].real() > max)
        {
            max = magCurrent[i].real();
            curFlag = i;
        }
    }
    float phaCur = std::arg(currentArray[curFlag]);
    std::cout << "Max number in current array " << curFlag << ", value is " <<
        currentArray[curFlag] << " angle = " <<
        phaCur / PI * 180 <<
        std::endl;
    PF = cos(phaVol - phaCur);
}

void powerFactor::calc()
{
    CArray volArray(voltageC, lineCount);
    CArray curArray(currentC, lineCount);

    volArray = fft(volArray);
    curArray = fft(curArray);
    CArray magVoltage(lineCount);
    CArray magCurrent(lineCount);
    magVoltage = std::abs(volArray);
    magCurrent = std::abs(curArray);
    printArray("Voltage", magVoltage);
    printArray("Current", magCurrent);
    int volFlag = 0;
    int curFlag = 0;
    float max = round(magVoltage[0].real() * 1e6) / 1e6;
    volFlag = 0;
    for (unsigned int i = 0; i < magVoltage.size(); i++)
    {
        float tmp = round(magVoltage[i].real() * 1e6) / 1e6;
        if (tmp > max)
        {
            max = tmp;
            volFlag = i;
        }
    }
    double phaVol = std::arg(volArray[volFlag]);
#if ANGLE
    std::cout << "Max number in voltage array " << volFlag << ", value is " <<
        volArray[volFlag] << " angle = " <<
        phaVol / PI * 180 <<
        std::endl;
#endif
    float maxC = round(magCurrent[0].real() * 1e6) / 1e6;
    curFlag = 0;
    for (unsigned int i = 0; i < magCurrent.size(); i++)
    {
        float tmp = round(magCurrent[i].real() * 1e6) / 1e6;
        if (tmp > maxC)
        {
            maxC = tmp;
            curFlag = i;
        }
    }
    double phaCur = std::arg(curArray[curFlag]);
#if ANGLE
    std::cout << "Max number in current array " << curFlag << ", value is " <<
        curArray[curFlag] << " angle = " <<
        phaCur / PI * 180 <<
        std::endl;
#endif
    PF = cos(phaVol - phaCur);
}

int powerFactor::getMax() const
{
    return Max;
}



std::string powerFactor::getFile1() const
{
    return file1;
}

void powerFactor::setFile1(const std::string &value)
{
    file1 = value;
}

std::string powerFactor::getFile2() const
{
    return file2;
}

void powerFactor::setFile2(const std::string &value)
{
    file2 = value;
}

void powerFactor::readCSV(std::__cxx11::string PFfile)
{
    try
    {
        io::CSVReader<3> voltageCSV(PFfile);
        voltageCSV.next_line();
        double time;
        double data1;
        double data2;
        for (lineCount = 0; voltageCSV.read_row(time, data1, data2); lineCount++)
        {
            voltageC[lineCount] = data1;
            currentC[lineCount] = data2;
        }
    }
    catch (...)
    {
        std::cout<<"ReadCSV() error"<<std::endl;
        exit(-2);
    }
}

void powerFactor::readCSV()
{
    io::CSVReader<2> voltageCSV(file1);
    voltageCSV.next_line();
    double time;
    double data1;

    for (lineCount = 0; voltageCSV.read_row(time, data1); lineCount++)
    {
        voltageC[lineCount] = data1;
    }
    io::CSVReader<2> currentCSV(file2);
    currentCSV.next_line();
    for (lineCount = 0; currentCSV.read_row(time, data1); lineCount++)
    {
        currentC[lineCount] = data1;
    }
}

void powerFactor::printArray(std::string name, CArray &n)
{
#if DEBUG
    std::cout << name << " = " << std::endl;
    for (Complex n1 : n)
    {
        std::cout << std::fixed << n1 << ' ';
    }
    std::cout << std::endl;
#endif
}

void powerFactor::printArray(std::__cxx11::string name, Complex *complexArray)
{
#if DEBUG
    std::cout << name << " = " << std::endl;
    for (int i = 0; i < sizeof(complexArray) / sizeof(Complex); i++)
    {
        std::cout << std::fixed << complexArray[i] << ' ';
    }
    std::cout << std::endl;
#endif
}

CArray powerFactor::fft(CArray a)
{
    int N = lineCount;
    fftw_complex *in, *out;
    fftw_plan p;

    //add code;
    in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    //add code;
    for (int i = 0; i < N; i++)
    {
        in[i][0] = a[i].real();
        in[i][1] = a[i].imag();
    }
    fftw_execute(p); /* repeat as needed */
    //add code;
    CArray result(lineCount);
    for (int i = 0; i < N; i++)
    {
        //qDebug()<<out[i][0]<<","<<out[i][1];
        result[i].real(out[i][0]);
        result[i].imag(out[i][1]);
    }
    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
    return result;
}
