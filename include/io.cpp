#include "io.hpp"

_io::_io(int argc, char** argv) {

    // Default values
    /***************************************/
    mode=-1;
    A0=0; A0_isempty=true;
    B0=0; B0_isempty=true;
    A1=0; A1_isempty=true;
    B1=0; B1_isempty=true;
    lambda=0; lambda_isempty=true;
    gf_hf=true;
    /***********/


    // convert char* into std::string via sI, sJ, sF ...;
    /***************************************/
    std::string sI="0";
    std::string sJ0="0", sF0="0";
    std::string sJ1="0", sF1="0";
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
-0 or --0        compute energy shift of the splitted levels (I\u2297J0)\n \
                 with these additional options:\n \
        --I int/int  nuclear momentum (required).\n \
        --J0 int/int electronic momentum (required). \n \
        --A0 real    A-HFS constant of the level\n \
        --B0 real    B-HFS constant of the level\n\n \
\
-1 or --1        compute energy or/and wavelength shift for one HFS transition\n \
                 |I,J0,F0> \u2192 |I,J1,F1> \n \
                 with these additional options:\n \
        --I int/int  (required).\n \
        --J0 int/int (required). \n \
        --F0 int/int total momentum: I\u2297J0 (required). \n \
        --J1 int/int (required)\n \
        --F1 int/int (required)\n \
        --A0 real    A-HFS constant of the lower/upper level (required)\n \
        --B0 real    B-HFS constant of the lower/upper level\n \
        --A1 real    A-HFS constant of the upper/lower level (required)\n \
        --B1 real    B-HFS constant of the upper/lower level\n \
        --l real     wavelength of the transition (\u00C5)\n\n \
\
-2 or --2        compute hfs oscillator strength for on HFS transition\n \
                 |I,J0,F0> \u2192 |I,J1,F1>\n \
                 with these additional options:\n \
        --I  int/int (required)\n \
        --J0 int/int (required)\n \
        --J1 int/int (required)\n \
        --F0 int/int (required)\n \
        --F1 int/int (required)\n \
        --gf real    HF oscillator strength log(gf_hf) (required)\n\n \
\
-3 or --3        compute energy shift of the level (J0 F0)\n \
                 with these additional options:\n \
        --I int/int  (required).\n \
        --J0 int/int (required). \n \
        --F0 int/int I\u2297J0 (required). \n \
        --A0 real    A-HFS constant of the level\n \
        --B0 real    B-HFS constant of the level\n\n";

        help+="The mandatory format int/int means p/q, \u2200(p,q) \u2208 N \u2A2F 2N.\n\n";

        help+="HFS shift is computed with the first order perturbation theory since coupling between \
magnetic field of electronic cloud and nucleus momentum is weak. \
Wigner 6j symbols are used to facilitate the manipulation of spherical harmonics in the matrix elements computation. \n\n";

        help+="A and B are independent from F: A=A(2S+1 L_J). They are expressed in MHz or mK. Thus one has to multiply the energy by 1e6*h or 1e-3*k_B.\n\n";

        help+="Note that nuclei far away from the double magicity (±3 nucleons) and heavy elements \
are no more spherical (Q<0 or Q>0) and HFS constant B might have to be taken into account.\n\n \
Examples: \n \
    Ca: A=40  Z=20 N=20  Q=0 b \n \
    Hg: A=201 Z=80 N=121 Q=0.65 b \n \
    U:  A=238 Z=92 N=146 Q=11 b \n\n\
Even-Even nucleus has I=0.\n\n";

        help+="Notations:\n \
<H> \u2250 <nIJF|H|nIJF>\n \
<\u0394H> \u2250 E(I,J',F') - E(I,J,F)\n\n";

        help+="Command examples:\n \
./shfs -0 -I 3/2 --J0 1\n \
./shfs -1 -I 7/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3\n \
./shfs -2 -I 7/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3 --gf 10\n \
./shfs -3 -I 3/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3\n\n";

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
            {"A0", required_argument, 0, 'A'},
            {"B0", required_argument, 0, 'B'},
            {"A1", required_argument, 0, 'C'},
            {"B1", required_argument, 0, 'D'},
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

        // Lambda function seems justified here:
        // exit if the given real is not a number
        /***************************************/
        auto is_real=[](char* arg) {
            std::string str(arg);
            if (!std::all_of(str.begin(), str.end(), [](char c){return std::isdigit(c) || c=='.' || c=='-' || c=='+';})){
                std::cerr << "\u26a0 non-real in the command line: "<< str <<"\n";
                exit(EXIT_FAILURE);
            }
        };
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
                    is_real(optarg);
                    test1++;
                    A0=std::stold(optarg);
                    A0_isempty=false;
                    break;
                case 'B':
                    is_real(optarg);
                    B0=std::stold(optarg);
                    B0_isempty=false;
                    break;
                case 'C':
                    is_real(optarg);
                    test1++;
                    A1=std::stold(optarg);
                    A1_isempty=false;
                    break;
                case 'D':
                    is_real(optarg);
                    B1=std::stold(optarg);
                    B1_isempty=false;
                    break;
                case 'l':
                    is_real(optarg);
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
                    is_real(optarg);
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
            (test1<7  && mode==1) ||
            (test2!=7 && mode==2) ||
            (test3!=4 && mode==3) ||
            (mode==-1)) {
                std::cerr << "\u26a0 not enough args. Type: " <<  argv[0] << " -h\n";
                exit(EXIT_FAILURE);
            }
    }
    else {
        std::cerr << "\u26a0 not enough args or bad mode. Type: " << argv[0] << " -h\n";
        exit(EXIT_FAILURE);
    }
    /***********/

    if (mode==1 && A0_isempty && A1_isempty) {
        std::cerr << "\u26a0 A-HFS constants are mandatory in this mode: A0 and A1\n";
        exit(EXIT_FAILURE);
    }


    // Check if args are numbers
    /***************************************/
    if (!_frac::is_number(sI) ||
        !_frac::is_number(sJ0)||
        (mode==0 && !_frac::is_number(sF0)) ||
        ((mode==0 || mode==3) && !_frac::is_number(sJ1)) ||
        ((mode==0 || mode==3) && !_frac::is_number(sF1)) ) {
        std::cerr << "\u26a0 bad quantum number in the command line\n";
        exit(EXIT_FAILURE);
    }
    /***********/


    // Convert std::string "n/m" into _frac<>(n,m)
    /***************************************/
    I=_frac::str_to_frac(sI);
    J0=_frac::str_to_frac(sJ0);
    if (mode!=0) {
        F0=_frac::str_to_frac(sF0);
        J1=_frac::str_to_frac(sJ1);
        F1=_frac::str_to_frac(sF1);
    }
    /***********/


    // Check if quantum numbers are half integer
    /***************************************/
    auto is_halfint=[](_frac<> f) {
        return std::floor(f.val()*2) == 2*f.val();
    };

    if (!is_halfint(I) ||
        !is_halfint(J0) ||
        !is_halfint(J1) ||
        !is_halfint(F0) ||
        !is_halfint(F1)) {
        std::cerr << "\u26a0 quantum numbers are not integer or half integer\n";
        exit(EXIT_FAILURE);
    }

    /***********/


    // Show parameters
    /***************************************/
    output << "Parameters:\n";
    output << "- I=" << I.show() << "\n";
    output << "- J0=" << J0.show() << "\n";
    if (mode!=0) {
        output << "- J1=" << J1.show() << "\n";
        output << "- F0=" << F0.show() << "\n";
        output << "- F1=" << F1.show() << "\n";
    }
    if (!A0_isempty)
        output << std::setprecision(6)
                   << "- A0=" << A0 << "\n";
    if (!B0_isempty)
        output << std::setprecision(6)
                   << "- B0=" << B0 << "\n";

    if (mode==1) {
        if (!B0_isempty &&
            !B1_isempty)
            output << std::setprecision(6)
            << "- A1=" << A1
            << " - B1=" << B1
            << "\n";
        else {
            output << std::setprecision(6)
            << "- A1=" << A1
            << "\n";
        }
        if (!lambda_isempty)
            output << std::setprecision(6)
            << "- wavelength: "
            << lambda << " \u00C5\n";
    }
    if (mode==2)
        output << std::setprecision(6)
        << "- gf_FS="
        << gf_hf
        << "\n";
    output << "\n";
    /***********/
}

// useless
_io::~_io() { std::cout << "\nbye !\n"; }

_frac<> _io::E_M1_divA() {
        return (F0*(F0+1)-J0*(J0+1)-I*(I+1))/2;
}

double long _io::DE_M1() {
    _frac<> C0(0);
    _frac<> C1(0);
    if (((F0-F1).abs().val()==1 || (F0-F1).val()==0) &&
        ((J0-J1).abs().val()==1 || (J0-J1).val()==0)) {
        C0=(F0*(F0+1)-J0*(J0+1)-I*(I+1));
        C1=(F1*(F1+1)-J1*(J1+1)-I*(I+1));
        }
        else {
            output << " - forbidden transition: |\u0394F|="
            << (F0-F1).abs().show()
            << " |\u0394J|="
            << (J0-J1).abs().show()
            << " - ";
            return 0;
        }
        return (A1*C1.val()-A0*C0.val())/2;
}

_frac<> _io::E_E2_divB() {
    _frac<> C0(1), P0(0), Q0(1);
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
    return P0/Q0;
}

double long _io::DE_E2() {
    _frac<> C0(1), P0(0), Q0(1);
    _frac<> C1(1), P1(0), Q1(1);

    if (I.val()==0 ||
        I.val()==0.5 ||
        J0.val()==0.5 ||
        J1.val()==0.5 )
        return 0;
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
            output << " - forbidden transition: |\u0394F|="
            << (F0-F1).abs().show()
            << " |\u0394J|="
            << (J0-J1).abs().show()
            << " - ";
            return 0;
        }
    }
    return B1*(P1/Q1).val()-B0*(P0/Q0).val();
}

// double long _io::lambda_shift() {
//     return lambda-1.0/(E_M1()+E_E2())*1e-8; //1/(cm*10^8 A) ?
// }


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
            output << " - forbidden transition: |\u0394F|="
            << (F0-F1).abs().show()
            << " |\u0394J|="
            << (J0-J1).abs().show()
            << " - ";
            return 0;
        }

        /***********/
}
/***********/


// Compute, print to term or write
/***************************************/

bool _io::compute(void) {
        if (mode==0) {
        output << "\u25cf HFS Energy shift:\n";
        output << "\u2192 Magnetic dipole M1\n";

	// |I-J0| <= F <= I+J0
	/***************************************/
	for(F0=(I-J0).abs(); F0< I+J0+_frac<>(1); F0++) {
	  output << "F="<< F0.show();
	  output  << std::setw(10) << "\t<H>_M1/A="+E_M1_divA().show();

	  if (!A0_isempty)
	    output  << std::setw(10)  << "\t<H>_M1\u2243" <<  E_M1_divA().val()*A0;
	  output << std::endl;
	}

	output << "\n";
	output << "\u2192 Electric quadrupole E2 \n";

	for(F0=(I-J0).abs(); F0< I+J0+_frac<>(1); F0++) {
	  output << "F="<< F0.show();
	  output  << std::setw(10) << "\t<H>_E2/B="+E_E2_divB().show();
	  if (!B0_isempty)
	    output  << std::setw(10)  << "\t<H>_E2\u2243" <<  E_E2_divB().val()*B0;
	  output << std::endl;
	}
	/***********/

    }
    if (mode==1) {
        output << "\u2776 HFS Energy shift:\n";
        output << "\u2192 Magnetic dipole M1\n";
        output << std::setprecision(20)
        << "<\u0394H>_M1="
        << DE_M1()
        << "\n";

	if (!B0_isempty && !B1_isempty) {
	  output << "\n\u2192 Electric quadrupole E2 \n";
	  output << std::setprecision(20)
	  << "<\u0394H>_E2="
	  << DE_E2()
	  << "\n";
	}

//         if (!lambda_isempty && !A_isempty)
//             output << std::setprecision(20)
//             << "\nshifted wavelength: "
//             << lambda_shift()
//             << " \u00C5\n";
    }

    if (mode==2) {
        output << "\u2777 HFS oscillator strength:\n";
        output  << std::setprecision(15)
        << "\u2192 gf_HFS="
        << gf_hfs()
        << "\n";

        if (gf_hfs()!=0)
            output  << std::setprecision(5)
            << "\u2192 log(gf_HFS)="
            << log(gf_hfs())
            << "\n";

        output  << std::setprecision(15)
        << "\u2192 effective ngf_HFS="
        << gf_hfs()/(2*I.val()+1)
        << "\n";

        if (gf_hfs()!=0)
            output << std::setprecision(5)
            << "\u2192 effective log(ngf_HFS)="
            << log(gf_hfs()/(2*I.val()+1))
            << "\n";

    }
    if (mode==3) {
        output << "\u2778 HFS Energy shift:\n";
        output << "\u2192 Magnetic dipole M1\n";

        output << "<\u0394H>_M1/A="
        << E_M1_divA().show();
         if (!A0_isempty)
                output << std::setw(10)  << "\t<H>_M1\u2243"
                << E_M1_divA().val()*A0;
        output << "\n";

        output << "\n\u2192 Electric quadrupole E2 \n";
        output << "<\u0394H>_E2/B="
        << E_E2_divB().show();
        if (!B0_isempty)
                output << std::setw(10)  << "\t<H>_E2\u2243"
                << E_E2_divB().val()*B0;
        output << "\n";
    }
    return mode>-1 && mode<4;
}


void _io::print(void) {
    std::cout << output.str() << "\n";
}

bool _io::write(void) {
    bool OK=false;
    std::string ext=".txt";

    // If file exists, add a number to the filename
	/***************************************/
    auto file_exists=[](const std::string &str, const std::string &ext){
        struct stat buf;
        return (stat ((str+ext).c_str(), &buf) == 0);};

    std::string pattern="out_m"+std::to_string(mode);
    std::string filename=pattern+"_0";
    unsigned int i=0;
    while(file_exists(filename,ext))
        filename=pattern+"_"+std::to_string(i++);

    // Write results
	/***************************************/
    std::ofstream flux(filename+ext, std::ios::out|std::ios::trunc);

    if (flux.is_open()) {
        flux << output.str();
        flux.close();
        OK=true;
    }
    else {
        std::cerr << "\u26a0 error while opening: output_mode" << mode << ".txt\n";
    }

    return OK;
}

/***********/
