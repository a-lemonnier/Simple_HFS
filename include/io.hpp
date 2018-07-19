#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip> // setprecision
#include <getopt.h> // GNU parser

#include "basic_fracs.hpp" // fraction class made to avoid boost::rational
#include "cte.hpp" // some constants

class _io : public _frac<> {
public:

    _io(int argc, char** argv); // parse command line
    ~_io();

    // return DeltaE_M1/(A*hbar)
    _frac<> E_M1_divA(void);
    // return E_M1/hbar
    double long E_M1(void);

    // return DeltaE_E2/(B*hbar)
    _frac<> E_E2_divB(void);
    // return E_E2/hbar
    double long E_E2(void);

    // return Deltalambda_hfs
    double long lambda_shift(void);

    bool A_isempty;
    bool B_isempty;
    bool lambda_isempty;

private:
    _frac<> I, J, F;

    double long A, B;
    double long lambda;
};



#endif // IO_HPP
