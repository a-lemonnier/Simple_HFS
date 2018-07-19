#include "io.hpp"

_io::_io(int argc, char** argv) {

// Default values
/*********************************************************************/
    mode=0;
    A=0; A_isempty=true;
    B=0; B_isempty=true;
    lambda=0; lambda_isempty=true;
    gf_hf=true;
/***********/

    
// convert char* into std::string via sI, sJ, sF ...;
/*********************************************************************/
    std::string sI, sJ, sF;
    std::string sJ0, sF0;
    std::string sJ1, sF1;
/***********/


// Parse command line
/*********************************************************************/
 	if (argc>1) {
		std::string help;
        std::string p_name(argv[0]);
		help="Usage: "+p_name+" [OPTIONS]\n \
	compute energy shift and log(gf_hfs) from quantum numbers and hfs constants if available \n\n \
OPTIONS:\n \
-h or --help     show this help\n\n \
\
-1 or --1        compute Energy or/and wavelength shift\n \
                 with these additional options:\n \
    --I int/int  momentum of electrons.\n \
                 Sets: integer or half integer (required)\n \
    --J int/int  momentum of the nucleus. \n \
                 Sets: integer or half integer (required)\n \
    --F int/int  total momentum: I+J. \n \
                 Sets: integer or half integer (required)\n \
    --A real     A-hfs constant\n \
    --B real     B-hfs constant\n \
    --l real     wavelength of the transition\n\n \
\
-2 or --2        compute hfs oscillator strength\n \
                 |I,J0,F0> --> |I,J1,F1>\n \
                 with these additional options:\n \
    --I  int/int nuclear momentum (required)\n \
    --J0 int/int (required)\n \
    --J1 int/int (required)\n \
    --F0 int/int (required)\n \
    --F1 int/int (required)\n \
    --gf real    hf oscillator strength log(gf_hf)\n\n";        


        help+="I=0 or J=0 or I=1/2 or J=1/2 will return a 'div by 0' while\n\
computing E2.\n\n";

        help+="Please note that nuclei far away from the double magicity (±3 nucleons)\n\
are no more spherical (Q<0 or Q>0) and hfs constant B might have to be taken into account.\n \
Pair-Pair nucleus has I=0.\n\n";

        help+="G. M. Wahlgren (1995) - DOI: 10.1086/175618\n\n";
        
        static struct option long_options[] = {
          {"1", no_argument, 0, '1'},
          {"2", no_argument, 0, '2'},            
          {"help", no_argument, 0, 'h'},
          {"I", required_argument, 0, 'I'},
          {"J", required_argument, 0, 'J'},
          {"F", required_argument, 0, 'F'},
          {"A", required_argument, 0, 'A'},
          {"B", required_argument, 0, 'B'},
          {"l", required_argument, 0, 'l'},
          {"J0", required_argument, 0, 'n'},
          {"F0", required_argument, 0, 'i'},
          {"J1", required_argument, 0, 'j'},
          {"F1", required_argument, 0, 'k'},
          {"gf", required_argument, 0, 'g'},
          {0, 0, 0, 0}
        };
        
        unsigned int test1=0;
        unsigned int test2=0;

		while(1) {
            int opt;
            int c = getopt_long (argc, argv, "12hI:J:F:A:B:l:g:",
                       long_options, &opt);
            if (c == -1) break;
            
            switch(c) {
                case '1':
                    mode=1;
                    test1++;
                    break;
                case '2':
                    mode=2;
                    test2++;
                    break;
                case 'I':
                    test1++;
                    test2++;
                    sI=std::string(optarg);
                    break;
                case 'J':
                    test1++;
                    sJ=std::string(optarg);
                    break;
                case 'F':
                    test1++;
                    sF=std::string(optarg);
                    break;
                case 'A':
                    A=std::stold(optarg);
                    A_isempty=false;
                    break;
                case 'B':
                    B=std::stold(optarg);
                    B_isempty=false;
                    break;
                case 'l':
                    lambda=std::stold(optarg);
                    lambda_isempty=false;
                    break;
                case 'n':
                    test2++;
                    sJ0=std::string(optarg);
                    break;
                case 'i':
                    test2++;
                    sF0=std::string(optarg);
                    break;
                case 'j':
                    test2++;
                    sJ1=std::string(optarg);
                    break;
                case 'k':
                    test2++;
                    sF1=std::string(optarg);
                    break;
                case 'g':
                    test2++;
                    gf_hf=std::stold(optarg);
                    gf_hf_isempty=false;
                    break;
                case 'h':
                    std::cout << help;
                    exit(EXIT_SUCCESS);
                    break;
                case '?':
                    std::cout << help;
                    exit(EXIT_SUCCESS);
                    break;
                default:
                    std::cout << "error in args! Try -h.\n";
                    exit(EXIT_FAILURE);
                    
            }                
        }
        if ((test1!=4 && mode==1) || (test2!=7 && mode==2)) {
            std::cerr << "not enough args. Type: " << test2 <<  argv[0] << " -h\n";
            exit(EXIT_FAILURE);
        }
	}
	else {
		std::cerr << "not enough args. Type: " << argv[0] << " -h\n";
		exit(EXIT_FAILURE);
	}
/***********/

	
// Convert std::string "n/m" into _frac<>(n,m)
/*********************************************************************/
	std::size_t pos;

    pos=sI.find('/');
 	if (pos!=std::string::npos)
        I=_frac<>(std::stold( sI.substr(0,pos) ),
                  std::stold( sI.substr( pos+1, sI.length()-1 )));
    else I=_frac<>(std::stold(sI),1);

    if (mode==1) {
        pos=sJ.find('/');
        if (pos!=std::string::npos)
            J=_frac<>(std::stold( sJ.substr(0,pos) ),
                      std::stold( sJ.substr( pos+1, sJ.length()-1 )));
            else J=_frac<>(std::stold(sJ),1);
            
            pos=sF.find('/');
        if (pos!=std::string::npos)
            F=_frac<>(std::stold( sF.substr(0,pos) ),
                      std::stold( sF.substr( pos+1, sF.length()-1 )));
            else F=_frac<>(std::stold(sF),1);
    }
    if (mode==2) {
        pos=sJ0.find('/');
        if (pos!=std::string::npos)
            J0=_frac<>(std::stold( sJ0.substr(0,pos) ),
                       std::stold( sJ0.substr( pos+1, sJ0.length()-1 )));
            else J0=_frac<>(std::stold(sJ0),1);
            
            pos=sF0.find('/');
        if (pos!=std::string::npos)
            F0=_frac<>(std::stold( sF0.substr(0,pos) ),
                       std::stold( sF0.substr( pos+1, sF0.length()-1 )));
            else F0=_frac<>(std::stold(sF0),1);
            
            pos=sJ1.find('/');
        if (pos!=std::string::npos)
            J1=_frac<>(std::stold( sJ1.substr(0,pos) ),
                       std::stold( sJ1.substr( pos+1, sJ1.length()-1 )));
            else J1=_frac<>(std::stold(sJ1),1);
            
            pos=sF1.find('/');
        if (pos!=std::string::npos)
            F1=_frac<>(std::stold( sF1.substr(0,pos) ),
                       std::stold( sF1.substr( pos+1, sF1.length()-1 )));
            else F1=_frac<>(std::stold(sF1),1);
    }
/***********/


// Show parameters
/*********************************************************************/
    if (mode==1) {
        std::cout << "Parameters:\n";
        std::cout << "I="; I.show();
        std::cout << " J="; J.show();
        std::cout << " F="; F.show();
        std::cout << "\n";
        if (!A_isempty) std::cout << std::setprecision(6) << "A=" << A << "\n";
        if (!B_isempty) std::cout << std::setprecision(6) << "B=" << B << "\n";
        if (!lambda_isempty) std::cout << std::setprecision(6) << "wavelength: " << lambda << "\n"; 
    }
    if (mode==2) {
        std::cout << "Parameters:\n";
        std::cout << "I="; I.show();
        std::cout << " J0="; J0.show();
        std::cout << " J1="; J1.show();
        std::cout << " F0="; F0.show();
        std::cout << " F1="; F0.show();
        std::cout << "\n";
        std::cout << std::setprecision(6) << "gf_hf=" << gf_hf << "\n"; 
    }

    std::cout << "\n";
/***********/
}

// useless
_io::~_io() { std::cout << "\nbye !\n"; }

_frac<> _io::E_M1_divA() {
     return F*(F+_frac<>(1,1))-J*(J+_frac<>(1,1))-I*(I+_frac<>(1,1))/_frac<>(2,1);
}

//
// G. M. Wahlgren (1995)
//

double long _io::E_M1() {
    double long p=this->E_M1_divA().F[0];
    double long q=this->E_M1_divA().F[1];
    return A*p/q;
}

_frac<> _io::E_E2_divB() {
    if (!B_isempty) {
        _frac<> C=F*(F+_frac<>(1,1))-J*(J+_frac<>(1,1))-I*(I+_frac<>(1,1));
        _frac<> P=_frac<>(3,4)*C*(C-_frac<>(1,1))-I*(I+_frac<>(1,1))*J*(J-_frac<>(1,1));
        _frac<> Q=_frac<>(2,1)*I*(_frac<>(2,1)*I-_frac<>(1,1))*J*(_frac<>(2,1)*J-_frac<>(1,1));
        if (Q.F[0]==0 || Q.F[1]==0) {
            std::cerr << "/!\\ div by 0 /!\\\n";
            exit(EXIT_SUCCESS);
        }
        return C*P/Q;
    }
    else return _frac<>(0,1);
}

double long _io::E_E2() {
    double long p=this->E_E2_divB().F[0];
    double long q=this->E_E2_divB().F[1];
    return B*p/q;
}

double long _io::lambda_shift() {
       return lambda-2*PI*hbar*v_light/(E_M1()+E_E2());
}


// Compute gf_hfs
/*********************************************************************/
double long _io::gf_hfs(void) {

// { I  J  F  } * (2F+1)(2F'+1) * gf_hf
// { F' 1  J' }
/*********************************************************************/
    double long  QN[]={
        J0.F[0]/J0.F[1],
        I.F[0]/I.F[1],
        F0.F[0]/F0.F[1],
        F1.F[0]/F1.F[1],
        1,
        J1.F[0]/J1.F[1] };
        
    _CGWR W6j(QN, _CGWR::C_W6j);
    
    return (2*F0.F[0]/F0.F[1]+1)*(2*F1.F[0]/F1.F[1])*pow(W6j.W6j(),2)*gf_hf;
/***********/
}
/***********/
