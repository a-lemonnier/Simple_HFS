#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip> // setprecision
#include <getopt.h> // GNU parser

#include "basic_fracs.hpp" // fraction class made to avoid boost::rational
#include "cte.hpp" // some constants
#include "cgwr.hpp" // Wigner 6j

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

    // return gf_hfs
    double long gf_hfs(void);

    bool A_isempty;
    bool B_isempty;
    bool lambda_isempty;
    bool gf_hf_isempty;
    int mode;

private:
    _frac<> I;
    _frac<> J0, F0; // |I J0 F0>
    _frac<> J1, F1; // |I J1 F1> 

    double long A, B;
    double long lambda;
    double long gf_hf;
};


#endif // IO_HPP
