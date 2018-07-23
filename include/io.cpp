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
    std::string sI;
    std::string sJ0, sF0;
    std::string sJ1, sF1;
/***********/


// Parse command line
/*********************************************************************/
 	if (argc>1) {
		std::string help;
        std::string p_name(argv[0]);
		help="Usage: "+p_name+" [OPTIONS]\n \
	compute HFS energy shift and effective HFS oscillator strength from \
quantum numbers and hfs constants if available \n\n \
OPTIONS:\n \
-h or --help     show this help\n\n \
\
-1 or --1        compute Energy or/and wavelength shift\n \
                 |I,J0,F0> --> |I,J1,F1> \n \
                 with these additional options:\n \
    --I int/int  nuclear momentum.\n \
                 Sets: integer or half integer (required)\n \
    --J0 int/int electronic momentum. \n \
                 Sets: integer or half integer (required)\n \
    --F0 int/int total momentum: I+J0. \n \
                 Sets: integer or half integer (required)\n \
    --J1 int/int (required)\n \
    --F1 int/int (required)\n \
    --A real     A-hfs constant of the transition (Mhz)\n \
    --B real     B-hfs constant of the transition (Mhz)\n \
    --l real     wavelength of the transition (Angstrom)\n\n \
\
-2 or --2        compute hfs oscillator strength\n \
                 |I,J0,F0> --> |I,J1,F1>\n \
                 with these additional options:\n \
    --I  int/int (required)\n \
    --J0 int/int (required)\n \
    --J1 int/int (required)\n \
    --F0 int/int (required)\n \
    --F1 int/int (required)\n \
    --gf real    HF oscillator strength log(gf_hf) (required)\n\n";


        help+="I=0 or J=0 or I=1/2 or J=1/2 will return a 'div by 0' while\n\
computing E2.\n\n";

        help+="HFS shift is computed with the first order perturbation theory since coupling between \
electronic cloud magnetic field and nucleus momentum is weak.\n\n";

        help+="Please note that nuclei far away from the double magicity (±3 nucleons) and heavy elements \
are no more spherical (Q<0 or Q>0) and hfs constant B might have to be taken into account.\n\n \
Examples: \n \
Ca: A=40  Z=20 N=20  Q=0    (barn) \n \
Hg: A=201 Z=80 N=121 Q=0.65 (b) \n \
U:  A=238 Z=92 N=146 Q=11   (b) \n\n \
Pair-Pair nucleus has I=0.\n\n";


        help+=" ref: \n \
Jie Wang et al. (2014) - DOI: 10.1088/0957-0233/25/3/035501 \n \
R. D. Cowan, The Theory of Atomic Structure and Spectra (1981) \n \
G. M. Wahlgren (1995) - DOI: 10.1086/175618\n \
https://www-nds.iaea.org/nuclearmoments\n";

        static struct option long_options[] = {
          {"1", no_argument, 0, '1'},
          {"2", no_argument, 0, '2'},
          {"help", no_argument, 0, 'h'},
          {"I", required_argument, 0, 'I'},
          {"A", required_argument, 0, 'A'},
          {"B", required_argument, 0, 'B'},
          {"l", required_argument, 0, 'l'},
          {"J0", required_argument, 0, 'a'},
          {"F0", required_argument, 0, 'b'},
          {"J1", required_argument, 0, 'c'},
          {"F1", required_argument, 0, 'd'},
          {"gf", required_argument, 0, 'g'},
          {0, 0, 0, 0}
        };

        unsigned int test1=0;
        unsigned int test2=0;

		while(1) {
            int opt;
            int c = getopt_long (argc, argv, "12hI:A:B:l:g:",
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
                case 'a':
                    test1++;
                    test2++;
                    sJ0=std::string(optarg);
                    break;
                case 'b':
                    test1++;
                    test2++;
                    sF0=std::string(optarg);
                    break;
                case 'c':
                    test1++;
                    test2++;
                    sJ1=std::string(optarg);
                    break;
                case 'd':
                    test1++;
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

        if ((test1<5 && mode==1) || (test2!=7 && mode==2)) {
            std::cerr << "not enough args. Type: " <<  argv[0] << " -h\n";
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
    else I=_frac<>(std::stold(sI));

        pos=sJ0.find('/');
        if (pos!=std::string::npos)
            J0=_frac<>(std::stold( sJ0.substr(0,pos) ),
                       std::stold( sJ0.substr( pos+1, sJ0.length()-1 )));
            else J0=_frac<>(std::stold(sJ0));

            pos=sF0.find('/');
        if (pos!=std::string::npos)
            F0=_frac<>(std::stold( sF0.substr(0,pos) ),
                       std::stold( sF0.substr( pos+1, sF0.length()-1 )));
            else F0=_frac<>(std::stold(sF0));

            pos=sJ1.find('/');
        if (pos!=std::string::npos)
            J1=_frac<>(std::stold( sJ1.substr(0,pos) ),
                       std::stold( sJ1.substr( pos+1, sJ1.length()-1 )));
            else J1=_frac<>(std::stold(sJ1));

            pos=sF1.find('/');
        if (pos!=std::string::npos)
            F1=_frac<>(std::stold( sF1.substr(0,pos) ),
                       std::stold( sF1.substr( pos+1, sF1.length()-1 )));
            else F1=_frac<>(std::stold(sF1));
/***********/


// Show parameters
/*********************************************************************/
std::cout << "Parameters:\n";
std::cout << "- I="; I.show();
std::cout << "\n";
std::cout << "- J0="; J0.show();
std::cout << "\n";
std::cout << "- J1="; J1.show();
std::cout << "\n";
std::cout << "- F0="; F0.show();
std::cout << "\n";
std::cout << "- F1="; F1.show();
std::cout << "\n";

    if (mode==1) {
        if (!A_isempty) std::cout << std::setprecision(6) << "- A=" << A << "\n";
        if (!B_isempty) std::cout << std::setprecision(6) << "- B=" << B << "\n";
        if (!lambda_isempty) std::cout << std::setprecision(6) << "- wavelength: " << lambda << "\n";
    }
    if (mode==2)
        std::cout << std::setprecision(6) << "- gf_hf=" << gf_hf << "\n";

    std::cout << "\n";
/***********/
}

// useless
_io::~_io() { std::cout << "\nbye !\n"; }

_frac<> _io::E_M1_divA() {
    _frac<> A0(0);
    _frac<> A1(0);
    if (((F0-F1).abs()==_frac<>(1) || (F0-F1).F[0]==0) &&
        ((J0-J1).abs()==_frac<>(1) || (J0-J1).F[0]==0)) {
    A0=(F0*(F0+_frac<>(1))-J0*(J0+_frac<>(1))-I*(I+_frac<>(1)))/_frac<>(2);
    A1=(F1*(F1+_frac<>(1))-J1*(J1+_frac<>(1))-I*(I+_frac<>(1)))/_frac<>(2);
}
else {
    std::cout << " - forbidden transition: |F-F\'|=";
    (F0-F1).abs().show();
    std::cout << " |J-J'|=";
    (J0-J1).abs().show();
    std::cout << " - ";
    return 0;
}

     return A0-A1;
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
        _frac<> C0(1), P0(0), Q0(1);
        _frac<> C1(1), P1(0), Q1(1);

        if (((F0-F1).abs()==_frac<>(1) || (F0-F1).F[0]==0) &&
            ((J0-J1).abs()==_frac<>(1) || (J0-J1).F[0]==0)) {
// B*((3/4)*C(C+1)-I(I+1)*J(J+1))/2
/*********************************************************************/
        C0=F0*(F0+_frac<>(1))-J0*(J0+_frac<>(1))-I*(I+_frac<>(1));
        P0=_frac<>(3,4)*C0*(C0+_frac<>(1))-I*(I+_frac<>(1))*J0*(J0-_frac<>(1));
        Q0=_frac<>(2)*I*(_frac<>(2)*I-_frac<>(1))*J0*(_frac<>(2)*J0-_frac<>(1));

        C1=F1*(F1+_frac<>(1))-J1*(J1+_frac<>(1))-I*(I+_frac<>(1));
        P1=_frac<>(3,4)*C1*(C1-_frac<>(1))-I*(I+_frac<>(1))*J1*(J1-_frac<>(1));
        Q1=_frac<>(2)*I*(_frac<>(2)*I-_frac<>(1))*J1*(_frac<>(2)*J1-_frac<>(1));
/***********/

        if (Q0.F[0]==0 ||
            Q0.F[1]==0 ||
            Q1.F[0]==0 ||
            Q1.F[1]==0 ) {
            std::cerr << "/!\\ div by 0 /!\\\n";
            exit(EXIT_SUCCESS);
        }
    }
    else {
        std::cout << " - forbidden transition: |F-F\'|=";
        (F0-F1).abs().show();
        std::cout << " |J-J'|=";
        (J0-J1).abs().show();
        std::cout << " - ";
        return 0;
    }
        return P0/Q0-P1/P1;
}

double long _io::E_E2() {
    double long p=this->E_E2_divB().F[0];
    double long q=this->E_E2_divB().F[1];
    return B*p/q;
}

double long _io::lambda_shift() {
       return lambda-1.0/(E_M1()+E_E2())*1e-8; //1/(cm*10^8 A) ?
}


// Compute gf_hfs
/*********************************************************************/
double long _io::gf_hfs(void) {

// F'-F=0 or -1, or 1
/*********************************************************************/
if (((F0-F1).abs()==_frac<>(1) || (F0-F1).F[0]==0) &&
    ((J0-J1).abs()==_frac<>(1) || (J0-J1).F[0]==0)) {

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
    else {
        std::cout << " forbidden transition: |F-F\'|=";
        (F0-F1).abs().show();
        std::cout << " |J-J'|=";
        (J0-J1).abs().show();
        std::cout << "\n";
        return 0;
    }

/***********/
}
/***********/
