********
* Build:
********

TODO:
- effective ngf_hfs
- Selection rules W6j
- _frac<> W6j
- fix hbar² and energy


Dependencies:
- cmake or make: a makefile is in Simple_HFS/make
- gcc / g++ : c++11


```
$ ls -R
.:
include  main.cpp  make  Makefile  README.md

./include:
basic_fracs.hpp  cgwr.cpp  CMakeLists.txt  cte.hpp  io.hpp
basic_fracs.tpp  cgwr.hpp  cte.cpp         io.cpp

./make:
CMakeLists.txt  Makefile
```

With cmake:

```
$ cmake .
-- The C compiler identification is GNU 7.3.0
-- The CXX compiler identification is GNU 7.3.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/gentoo/Prog/Simple_HFS

$ make
Scanning dependencies of target shfs
[ 20%] Building CXX object CMakeFiles/shfs.dir/main.cpp.o
[ 40%] Building CXX object CMakeFiles/shfs.dir/include/io.cpp.o
[ 60%] Building CXX object CMakeFiles/shfs.dir/include/cte.cpp.o
[ 80%] Building CXX object CMakeFiles/shfs.dir/include/cgwr.cpp.o
[100%] Linking CXX executable shfs
[100%] Built target shfs
```

With make:

```
$ make
g++ -std=c++11 -O3	 -Wall -pedantic -Iinclude   -c -o main.o main.cpp
g++ -std=c++11 -O3	 -Wall -pedantic -Iinclude -c -o include/cte.o  include/cte.cpp
g++ -std=c++11 -O3	 -Wall -pedantic -Iinclude -c -o include/io.o  include/io.cpp
g++ -std=c++11 -O3	 -Wall -pedantic -Iinclude -c -o include/cgwr.o  include/cgwr.cpp
g++ main.o include/cte.o include/io.o include/cgwr.o include/cte.hpp include/io.hpp include/basic_fracs.hpp include/cgwr.hpp -std=c++11 -Iinclude  -o shfs
rm -dfr main.o include/cte.o include/io.o include/cgwr.o
```


********
* Run help:
********

```
$ ./shfs -h
Usage: ./shfs [OPTIONS]
        compute HFS energy shift and effective HFS oscillator strength from quantum numbers and hfs constants if available 

 OPTIONS:
 -h or --help     show this help

 -1 or --1        compute Energy or/and wavelength shift
                  |I,J0,F0> --> |I,J1,F1> 
                  with these additional options:
     --I int/int  nuclear momentum.
                  Sets: integer or half integer (required)
     --J0 int/int electronic momentum. 
                  Sets: integer or half integer (required)
     --F0 int/int total momentum: I+J0. 
                  Sets: integer or half integer (required)
     --J1 int/int (required)
     --F1 int/int (required)
     --A real     A-hfs constant of the transition (Mhz)
     --B real     B-hfs constant of the transition (Mhz)
     --l real     wavelength of the transition (Angstrom)

 -2 or --2        compute hfs oscillator strength
                  |I,J0,F0> --> |I,J1,F1>
                  with these additional options:
     --I  int/int (required)
     --J0 int/int (required)
     --J1 int/int (required)
     --F0 int/int (required)
     --F1 int/int (required)
     --gf real    HF oscillator strength log(gf_hf) (required)

I=0 or J=0 or I=1/2 or J=1/2 will return a 'div by 0' while
computing E2.

HFS shift is computed with the first order perturbation theory since coupling between electronic cloud magnetic field and nucleus momentum is weak.

Please note that nuclei far away from the double magicity (±3 nucleons) and heavy elements are no more spherical (Q<0 or Q>0) and hfs constant B might have to be taken into account.

 Examples: 
 Ca: A=40  Z=20 N=20  Q=0    (barn) 
 Hg: A=201 Z=80 N=121 Q=0.65 (b) 
 U:  A=238 Z=92 N=146 Q=11   (b) 

 Pair-Pair nucleus has I=0.

 ref: 
 Jie Wang et al. (2014) - DOI: 10.1088/0957-0233/25/3/035501 
 R. D. Cowan, The Theory of Atomic Structure and Spectra (1981) 
 G. M. Wahlgren (1995) - DOI: 10.1086/175618
 https://www-nds.iaea.org/nuclearmoments
```
>
> Dummy examples:
>

Caesium 8S1/2: A=219 MHz
```
$ ./shfs -1 -I 2 --J0 1/2 --F0 4 --J1 1/2 --F1 3
Parameters:
- I=2
- J0=1/2~0.5
- J1=1/2~0.5
- F0=4
- F1=3

HFS Energy shift:
-> Magnetic dipole
E_M1/A=4

-> Electric quadrupole
E_E2/B=0

bye !

$ ./shfs -2 -1 -I 2 --J0 1/2 --F0 4 --J1 1/2 --F1 3 --gf 0.1
Parameters:
- I=2
- J0=1/2~0.5
- J1=1/2~0.5
- F0=4
- F1=3
- gf_hf=0.1

-> HFS gf=0
-> HFS log(gf)=-inf

bye !

```
