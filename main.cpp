#include <iostream>
#include <iomanip> //precision of cout
#include <cmath>

#include "include/basic_fracs.hpp"
#include "include/io.hpp"
#include "include/cgwr.hpp"

int main(int argc, char** argv) {

    _io io(argc, argv);

    if (io.mode==0) {
        std::cout << "HFS Energy shift for an energy level:\n";
        std::cout << "-> Magnetic dipole M1\n";
	
 // |I-J0| <= F <= I+J0
/*********************************************************************/       
	for(io.F0=(io.I-io.J0).abs(); io.F0< io.I+io.J0+_frac<>(1); io.F0++) {
	  std::cout << "F=";
	  io.F0.show();
	  std::cout << ": \u0394E_M1/A=";
	  io.E_M1_divA().show();
	  std::cout << "\n";
	}
	
	std::cout << "\n";
	std::cout << "\n-> Electric quadrupole E2 \n";

	for(io.F0=(io.I-io.J0).abs(); io.F0< io.I+io.J0+_frac<>(1); io.F0++) {
	  std::cout << "F=";
	  io.F0.show();
	  std::cout << ": \u0394E_E2/B=";
	  io.E_E2_divB().show();
	  std::cout << "\n";
	}
/***********/

    }
    if (io.mode==1) {
        std::cout << "HFS Energy shift for a transition:\n";
        std::cout << "-> Magnetic dipole M1\n";

        std::cout << "\u0394E_M1/A=";
        io.E_M1_divA().show();
        std::cout << "\n";

        if (!io.A_isempty)
            std::cout << std::setprecision(20) << "\u0394E_M1=" << io.E_M1() << "\n";

        std::cout << "\n-> Electric quadrupole E2 \n";

        std::cout << "\u0394E_E2/B=";
        io.E_E2_divB().show();
        std::cout << "\n";

        if (!io.B_isempty)
            std::cout << std::setprecision(20) << "\u0394E_E2=" << io.E_E2() << "\n";

        if (!io.lambda_isempty && !io.A_isempty)
            std::cout << std::setprecision(20) << "\nshifted wavelength: " << io.lambda_shift() << "\n";
    }

    if (io.mode==2) {
        std::cout  << std::setprecision(20) << "-> HFS gf=" << io.gf_hfs() << "\n";
        if (io.gf_hfs()!=0)
        std::cout  << std::setprecision(5) << "-> HFS log(gf)=" << log(io.gf_hfs()) << "\n";
    }
    if (io.mode==3) {
        std::cout << "HFS Energy shift for an energy level:\n";
        std::cout << "-> Magnetic dipole M1\n";
        std::cout << "\u0394E_M1/A=";
        io.E_M1_divA().show();
        std::cout << "\n";
	std::cout << "\n-> Electric quadrupole E2 \n";
        std::cout << "\u0394E_E2/B=";
        io.E_E2_divB().show();
        std::cout << "\n";
    }

    return EXIT_SUCCESS;
}
