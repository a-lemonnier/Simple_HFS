#include <iostream>
#include <iomanip> //precision
#include <cmath>

#include "include/basic_fracs.hpp"
#include "include/io.hpp"
#include "include/cgwr.hpp"



int main(int argc, char** argv) {
    
    _io io(argc, argv);
    
    if (io.mode==0) {
        std::cout << "\u25cf HFS Energy shift:\n";
        std::cout << "\u2192 Magnetic dipole M1\n";
        
        // |I-J0| <= F <= I+J0
        /***************************************/       
        for(io.F0=(io.I-io.J0).abs(); io.F0< io.I+io.J0+_frac<>(1); io.F0++) {
            std::cout << "F="<< io.F0.show();
            std::cout << _io::centerstr("<H>_M1/A="+io.E_M1_divA().show());
            
            if (!io.A0_isempty)
                std::cout << _io::rightstr("<H>_M1\u2243"+std::to_string(io.E_M1_divA().val()*io.A0));
            std::cout << "\n";
        }
        
        std::cout << "\n";
        std::cout << "\u2192 Electric quadrupole E2 \n";
        
        for(io.F0=(io.I-io.J0).abs(); io.F0< io.I+io.J0+_frac<>(1); io.F0++) {
            std::cout << "F=" 
            << io.F0.show() 
            << ": <H>_E2/B=" 
            << io.E_E2_divB().show();
            if (!io.B0_isempty)
                std::cout << " - <H>_E2\u2243"
                << io.E_E2_divB().val()*io.B0;
            std::cout << "\n";
        }
        /***********/
        
    }
    if (io.mode==1) {
        std::cout << "\u2776 HFS Energy shift:\n";
        std::cout << "\u2192 Magnetic dipole M1\n";

        std::cout << std::setprecision(20) 
        << "<\u0394H>_M1=" 
        << io.DE_M1() 
        << "\n";
        
        std::cout << "\n\u2192 Electric quadrupole E2 \n";
        
        std::cout << "<\u0394H>_E2/B=" 
        << io.E_E2_divB().show() 
        << "\n";
        
        if (!io.B0_isempty && !io.B1_isempty)
            std::cout << std::setprecision(20) 
            << "<\u0394H>__E2=" 
            << io.DE_E2() 
            << "\n";
        
//         if (!io.lambda_isempty && !io.A_isempty)
//             std::cout << std::setprecision(20) 
//             << "\nshifted wavelength: " 
//             << io.lambda_shift() 
//             << " \u00C5\n";
    }
    
    if (io.mode==2) {
        std::cout << "\u2777 HFS oscillator strength:\n";
        std::cout  << std::setprecision(20) 
        << "\u2192 HFS gf=" 
        << io.gf_hfs() 
        << "\n";
        
        if (io.gf_hfs()!=0)
            std::cout  << std::setprecision(5) 
            << "\u2192 log(gf)=" 
            << log(io.gf_hfs()) 
            << "\n";
        
        std::cout  << std::setprecision(20) 
        << "\u2192 effective ngf=" 
        << io.gf_hfs()/(2*io.I.val()+1) 
        << "\n";
        
        if (io.gf_hfs()!=0)
            std::cout << std::setprecision(5) 
            << "\u2192 effective log(ngf)="
            << log(io.gf_hfs()/(2*io.I.val()+1)) 
            << "\n";
        
    }
    if (io.mode==3) {
        std::cout << "\u2778 HFS Energy shift:\n";
        std::cout << "\u2192 Magnetic dipole M1\n";
        
        std::cout << "<\u0394H>_M1/A=" 
        << io.E_M1_divA().show(); 
         if (!io.A0_isempty)
                std::cout << " - <H>_M1\u2243"
                << io.E_M1_divA().val()*io.A0;
        std::cout << "\n";
        
        std::cout << "\n\u2192 Electric quadrupole E2 \n";
        std::cout << "<\u0394H>_E2/B=" 
        << io.E_E2_divB().show();
        if (!io.B0_isempty)
                std::cout << " - <H>_E2\u2243"
                << io.E_E2_divB().val()*io.B0;
        std::cout << "\n";        
    }
    
    return EXIT_SUCCESS;
}
