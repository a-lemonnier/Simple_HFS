#include "io.hpp"

_io::_io(int argc, char** argv) {
    
    // Default values
    /***************************************/
    mode=-1;
    A=0; A_isempty=true;
    B=0; B_isempty=true;
    lambda=0; lambda_isempty=true;
    gf_hf=true;
    /***********/
    
    
    // convert char* into std::string via sI, sJ, sF ...;
    /***************************************/
    std::string sI;
    std::string sJ0, sF0;
    std::string sJ1, sF1;
    /***********/
    
    
    // Parse command line
    /***************************************/
    if (argc>1) {
        std::string help;
        std::string p_name(argv[0]);
        help="Usage: "+p_name+" [OPTIONS]\n \
compute HFS energy shift and effective HFS oscillator strength from \
quantum numbers and HFS constants if available \n\n \
OPTIONS:\n \
-h or --help     show this help\n\n \
-0 or --0        compute energy shift of the level for I\u2297J0\n \
                 with these additional options:\n \
        --I int/int  nuclear momentum (required).\n \
        --J0 int/int electronic momentum (required). \n\n \
\
-1 or --1        compute energy or/and wavelength shift\n \
                 |I,J0,F0> \u2192 |I,J1,F1> \n \
                 with these additional options:\n \
        --I int/int  (required).\n \
        --J0 int/int (required). \n \
        --F0 int/int total momentum: I\u2297J0 (required). \n \
        --J1 int/int (required)\n \
        --F1 int/int (required)\n \
        --A real     A-hfs constant of the transition (Mhz)\n \
        --B real     B-hfs constant of the transition (Mhz)\n \
        --l real     wavelength of the transition (\u00C5)\n\n \
\
-2 or --2        compute hfs oscillator strength\n \
                 |I,J0,F0> \u2192 |I,J1,F1>\n \
                 with these additional options:\n \
        --I  int/int (required)\n \
        --J0 int/int (required)\n \
        --J1 int/int (required)\n \
        --F0 int/int (required)\n \
        --F1 int/int (required)\n \
        --gf real    HF oscillator strength log(gf_hf) (required)\n\n \
\
-3 or --3        compute energy shift of the level (J F)\n \
                 with these additional options:\n \
        --I int/int  (required).\n \
        --J0 int/int (required). \n \
        --F0 int/int I\u2297J0 (required). \n\n";
        
        help+="The non-mandatory format int/int means p/q, \u2200(p,q) \u2208 N \u2A2F \u00BDN.\n\n";
        
        help+="HFS shift is computed with the first order perturbation theory since coupling between \
magnetic field of electronic cloud and nucleus momentum is weak. \
Wigner 6j symbols are used to facilitate the manipulation of spherical harmonics in the matrix elements computation. \n\n";
        
        help+="Please note that nuclei far away from the double magicity (±3 nucleons) and heavy elements \
are no more spherical (Q<0 or Q>0) and HFS constant B might have to be taken into account.\n\n \
Examples: \n \
    Ca: A=40  Z=20 N=20  Q=0 b \n \
    Hg: A=201 Z=80 N=121 Q=0.65 b \n \
    U:  A=238 Z=92 N=146 Q=11 b \n\n \
Even-Even nucleus has I=0.\n\n";
        
        help+="Command examples:\n \
./shfs -0 -I 3/2 --J0 1\n \
./shfs -1 -I 7/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3\n \
./shfs -2 -I 7/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3 --gf 10\n \
./shfs -3 -I 1.5 --J0 0.5 --F0 4 --J1 0.5 --F1 3\n\n";
        
        help+=" ref: \n \
R. D. Cowan, The Theory of Atomic Structure and Spectra (1981) \n \
Jie Wang et al. (2014) - DOI: 10.1088/0957-0233/25/3/035501 \n \
G. M. Wahlgren (1995) - DOI: 10.1086/175618\n \
https://www-nds.iaea.org/nuclearmoments\n";
        
        static struct option long_options[] = {
            {"0", no_argument, 0, '0'},
            {"1", no_argument, 0, '1'},
            {"2", no_argument, 0, '2'},
            {"3", no_argument, 0, '3'},
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
        
        
        // Count the number of args as function of the selected mode
        /***************************************/
        unsigned int test0=0;
        unsigned int test1=0;
        unsigned int test2=0;
        unsigned int test3=0;
        /***********/
        
        while(1) {
            int opt;
            int c = getopt_long (argc, argv, "0123hI:A:B:l:g:",
                                 long_options, &opt);
            if (c == -1) break;
            
            switch(c) {
                case '0':
                    mode=0;
                    test0++;
                    break;  
                case '1':
                    mode=1;
                    test1++;
                    break;
                case '2':
                    mode=2;
                    test2++;
                    break;
                case '3':
                    mode=3;
                    test3++;
                    break;
                case 'I':
                    test0++;
                    test1++;
                    test2++;
                    test3++;
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
                    test0++;
                    test1++;
                    test2++;
                    test3++;
                    sJ0=std::string(optarg);
                    break;
                case 'b':
                    test1++;
                    test2++;
                    test3++;
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
                    std::cout << "\u26a0 error in args! Try -h.\n";
                    exit(EXIT_FAILURE);
            }
        }        
        if ((test0!=3 && mode==0) ||
            (test1<5 && mode==1) || 
            (test2!=7 && mode==2) || 
            (test3!=4 && mode==3)) {
                std::cerr << "\u26a0 not enough args. Type: " <<  argv[0] << " -h\n";
                exit(EXIT_FAILURE);
            }
    }
    else {
        std::cerr << "\u26a0 not enough args. Type: " << argv[0] << " -h\n";
        exit(EXIT_FAILURE);
    }
    /***********/
    
    
    // Convert std::string "n/m" into _frac<>(n,m)
    /***************************************/
    I=_frac::str_to_frac(sI);
    J0=_frac::str_to_frac(sJ0);
    if (mode!=0)
        F0=_frac::str_to_frac(sF0);
    if (mode!=0 && mode!=3) {
        J1=_frac::str_to_frac(sJ1);
        F1=_frac::str_to_frac(sF1);
    }
    /***********/
    
    
    // Show parameters
    /***************************************/
    std::cout << "Parameters:\n";
    std::cout << "- I=" << I.show() << "\n";
    std::cout << "- J0=" << J0.show() << "\n";
    if (mode!=0 && mode!=3) 
        std::cout << "- J1=" << J1.show() << "\n";
    if (mode!=0) 
        std::cout << "- F0=" << F0.show() << "\n";
    if (mode!=0 && mode!=3) 
        std::cout << "- F1=" << F1.show() << "\n";
    
    if (mode==1) {
        if (!A_isempty) std::cout << std::setprecision(6) << "- A=" << A << "\n";
        if (!B_isempty) std::cout << std::setprecision(6) << "- B=" << B << "\n";
        if (!lambda_isempty) std::cout << std::setprecision(6) << "- wavelength: " << lambda << " \u00C5\n";
    }
    if (mode==2)
        std::cout << std::setprecision(6) << "- gf_hf=" << gf_hf << "\n";
    
    std::cout << "\n";
    /***********/
}

// useless
_io::~_io() { std::cout << "\nbye !\n"; }

_frac<> _io::E_M1_divA() {
    _frac<> C0(0);
    _frac<> C1(0);
    if (mode!=0 && mode!=3) {
        if (((F0-F1).abs().val()==1 || (F0-F1).val()==0) &&
            ((J0-J1).abs().val()==1 || (J0-J1).val()==0)) {
            C0=(F0*(F0+1)-J0*(J0+1)-I*(I+1)); 
            C1=(F1*(F1+1)-J1*(J1+1)-I*(I+1));
            }
            else {
                std::cout << " - forbidden transition: |\u0394F|=" 
                << (F0-F1).abs().show() 
                << " |\u0394J|=" 
                << (J0-J1).abs().show() 
                << " - ";
                return _frac<>();
            }
            return (C0-C1)/2;
    }
    else {
        return (F0*(F0+1)-J0*(J0+1)-I*(I+1))/2;
    }
}

// G. M. Wahlgren (1995)

double long _io::E_M1() {
    return A*E_M1_divA().val();
}

_frac<> _io::E_E2_divB() {
    _frac<> C0(1), P0(0), Q0(1);
    _frac<> C1(1), P1(0), Q1(1);
    
    if (mode!=0 && mode!=3) {
        
        if (I.val()==0 || 
            I.val()==0.5 ||
            J0.val()==0.5 || 
            J1.val()==0.5 ) 
            return _frac<>();
        else {
            if (((F0-F1).abs().val()==1 || (F0-F1).val()==0) &&
                ((J0-J1).abs().val()==1 || (J0-J1).val()==0) ) {
                
                // B*((3/4)*C(C+1)-I(I+1)*J(J+1))/2
               /***************************************/
                C0=F0*(F0+1)-J0*(J0+1)-I*(I+1);
                P0=_frac<>(3,4)*C0*(C0+1)-I*(I+1)*J0*(J0+1);
                Q0=2*I*(2*I-1)*J0*(2*J0-1);
            
                C1=F1*(F1+1)-J1*(J1+1)-I*(I+1);
                P1=_frac<>(3,4)*C1*(C1-1)-I*(I+1)*J1*(J1+1);
                Q1=2*I*(2*I-1)*J1*(2*J1-1);
                /***********/
                }
                else {
                    std::cout << " - forbidden transition: |\u0394F|=" 
                    << (F0-F1).abs().show() 
                    << " |\u0394J|=" 
                    << (J0-J1).abs().show() 
                    << " - ";
                    return _frac<>();
                }
        }
        return (P0/Q0)-(P1/Q1);
    }
    else {
        if (I.val()==0 ||
            I.val()==0.5 ||
            J0.val()==0.5 ) 
            return _frac<>();
        else {
            // B*((3/4)*C(C+1)-I(I+1)*J(J+1))/2
            /***************************************/
            C0=F0*(F0+1)-J0*(J0+1)-I*(I+1);
            P0=_frac<>(3,2)*C0*(C0+1)-2*I*(I+1)*J0*(J0+1);
            Q0=4*I*(2*I-1)*J0*(2*J0-1);
            /***********/
        }
    }
    return P0/Q0;
}

double long _io::E_E2() {
    return B*this->E_E2_divB().val();
}

double long _io::lambda_shift() {
    return lambda-1.0/(E_M1()+E_E2())*1e-8; //1/(cm*10^8 A) ?
}


// Compute gf_hfs
/***************************************/
double long _io::gf_hfs(void) {
    
    // F'-F=0 or -1, or 1
    /***************************************/
    if (((F0-F1).abs().val()==1 || (F0-F1).val()==0) &&
        ((J0-J1).abs().val()==1 || (J0-J1).val()==0)) {
        
        // { I  J  F  } * (2F+1)(2F'+1) * gf_hf
        // { F' 1  J' }
        /***************************************/
        double long  QN[]={ // Quantum Numbers
            J0.val(),
            I.val(),
            F0.val(),
            F1.val(),
            1,
            J1.val() };
            
            // Compute Wigner 6j
            _CGWR W6j(QN, _CGWR::C_W6j);
            
            return (2*F0.val()+1)*(2*F1.val()+1)*pow(W6j.W6j(),2)*gf_hf;
            /***********/
        }
        else {
            std::cout << " - forbidden transition: |\u0394F|=" 
            << (F0-F1).abs().show() 
            << " |\u0394J|=" 
            << (J0-J1).abs().show() 
            << " - ";
            return 0;
        }
        
        /***********/
}
/***********/
