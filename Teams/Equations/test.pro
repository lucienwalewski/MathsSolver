TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG+=debug

QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG += -O0

HEADERS += \
    polynomial.hpp \
    numbers.hpp

SOURCES += \
        polynomial.cpp\
        numbers.cpp\
        test_polynomial.cpp
