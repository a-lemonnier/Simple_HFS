#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <fstream> // write results
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip> // setprecision

#include <getopt.h> // GNU cmd line parser
#include <sys/stat.h> // file existence
#include <unistd.h>

#include "basic_fracs.hpp" // fraction class made to avoid boost::rational
#include "cte.hpp" // some constants
#include "cgwr.hpp" // Wigner 6j

class _io : public _frac<> {
public:

    _io(int argc, char** argv); // parse command line
    ~_io();
    
    // write results
    bool compute(void);
    void print(void);
    bool write(void);
    
private:
    
    // return DeltaE_M1/(A*hbar)
    _frac<> E_M1_divA(void);
    // return (E'_M1-E_M1)/hbar
    double long DE_M1(void);

    // return DeltaE_E2/(B*hbar)
    _frac<> E_E2_divB(void);
    // return E_E2/hbar
     double long DE_E2(void);

    // return Deltalambda_hfs
    double long lambda_shift(void);

    // return gf_hfs
    double long gf_hfs(void);

    bool A0_isempty;
    bool B0_isempty;
    bool A1_isempty;
    bool B1_isempty;
    bool lambda_isempty;
    bool gf_hf_isempty;

    int mode;
    double long A0, B0;
    double long A1, B1;
    double long lambda;
    double long gf_hf;
    
    _frac<> I;
    _frac<> J0, F0; // |I J0 F0>
    _frac<> J1, F1; // |I J1 F1> 
    
    std::ostringstream output;
};


#endif // IO_HPP
