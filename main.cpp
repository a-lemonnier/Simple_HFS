#include <iostream>
#include <iomanip> //precision of cout

#include "include/basic_fracs.hpp"
#include "include/io.hpp"
#include "include/cgwr.hpp"

int main(int argc, char** argv) {
    
    _io io(argc, argv);
    
    std::cout << "HFS Energy shift:\n";
    std::cout << "-> Magnetic dipole\n";
    
    std::cout << "E_M1/A=";
    io.E_M1_divA().show();
    std::cout << "\n";
    
    
    if (!io.A_isempty) 
        std::cout << std::setprecision(6) << "E_M1=" << io.E_M1() << "\n";
    
    std::cout << "\n-> Electric quadrupole\n";
    
    std::cout << "E_E2/B=";
    io.E_E2_divB().show();
    std::cout << "\n";
    
    if (!io.B_isempty) 
        std::cout << std::setprecision(6) << "E_E2=" << io.E_E2() << "\n";
    
    if (!io.lambda_isempty && !io.A_isempty) 
        std::cout << std::setprecision(6) << "\nwavelength shift: " << io.lambda_shift() << "\n";
    
}
