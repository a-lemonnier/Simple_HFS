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
 	compute energy shift and log(gf_hfs) from quantum numbers and hfs constants if available 

 OPTIONS:
 -h or --help     show this help

 -1 or --1        compute Energy or/and wavelength shift
 with these additionnal options:
     --I int/int  momentum of electrons.
                  Sets: integer or half integer (required)
     --J int/int  momentum of the nucleus. 
                  Sets: integer or half integer (required)
     --F int/int  total momentum: I+J. 
                  Sets: integer or half integer (required)
     --A real     A-hfs constant
     --B real     B-hfs constant
     --l real     wavelength of the transition

 -2 or --2        compute hfs oscillator strength
                  |I,J0,F0> --> |I,J1,F1>
 with these additionnal options:
     --I  int/int nuclear momentum (required)
     --J0 int/int (required)
     --J1 int/int (required)
     --F0 int/int (required)
     --F1 int/int (required)
     --gf real    hf oscillator strength log(gf_hf)

I=0 or J=0 or I=1/2 or J=1/2 will return a 'div by 0' while
computing E2.

Please note that nuclei far away from the double magicity (±3 nucleons)
are no more spherical (Q<0 or Q>0) and hfs constant B might have to be taken into account.
 Pair-Pair nucleus has I=0.

G. M. Wahlgren (1995) - DOI: 10.1086/175618
```
>
> Dummy examples:
>

```
$ ./shfs -1 -I 1/2 -J 1/2 -F 1 -A 0.1
Parameters:
- I=1/2~0.5
- J=1/2~0.5
- F=1
A=0.1

HFS Energy shift:
-> Magnetic dipole
E_M1/A=7/8~0.875
E_M1=0.087499999999999999999

-> Electric quadrupole
E_E2/B=0

bye !

$ ./shfs -2 -I 1 --J0 1/2 --F0 1/2 --J1 1/2 --F1 3/2 --gf 0.1
Parameters:
- I=1
- J0=1/2~0.5
- J1=1/2~0.5
- F0=1/2~0.5
- F1=1/2~0.5
- gf_hf=0.1

HFS gf=0.06666666666666666297

bye !

```
