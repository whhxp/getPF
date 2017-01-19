QT += core
TEMPLATE = app
CONFIG += console c++11

SOURCES += main.cpp \
    powerfactor.cpp \
    str2complex.cpp

HEADERS += \
    powerfactor.h \
    csv.h \
    str2complex.h \
    fftw3.h

win32: LIBS += C:/svn/fftw-3.3.5-dll32/libfftw3-3.dll

INCLUDEPATH += $$PWD/C:/svn/fftw-3.3.5-dll32
DEPENDPATH += $$PWD/C:/svn/fftw-3.3.5-dll32
