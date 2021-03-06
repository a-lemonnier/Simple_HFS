# Simple_HFS [![Build Status](https://cloud.drone.io/api/badges/a-lemonnier/Simple_HFS/status.svg)](https://cloud.drone.io/a-lemonnier/Simple_HFS)

TODO:
- _frac<> W6j
- wavelength shift
- cm^-1 to eV


Dependencies:
- cmake or make: a makefile is located in Simple_HFS/make/
- gcc / g++ : c++11

********
* Build:
********

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
$ make -j3
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
 compute HFS energy shift and effective HFS oscillator strength from quantum numbers and HFS constants if available 

 OPTIONS:
 -h or --help     show this help

 -0 or --0        compute energy shift of the splitted levels (I⊗J0)
                  with these additional options:
         --I int/int  nuclear momentum (required).
         --J0 int/int electronic momentum (required). 
         --A0 real    A-HFS constant of the level
         --B0 real    B-HFS constant of the level

 -1 or --1        compute energy or/and wavelength shift for one HFS transition
                  |I,J0,F0> → |I,J1,F1> 
                  with these additional options:
         --I int/int  (required).
         --J0 int/int (required). 
         --F0 int/int total momentum: I⊗J0 (required). 
         --J1 int/int (required)
         --F1 int/int (required)
         --A0 real    A-HFS constant of the lower/upper level (required)
         --B0 real    B-HFS constant of the lower/upper level
         --A1 real    A-HFS constant of the upper/lower level (required)
         --B1 real    B-HFS constant of the upper/lower level
         --l real     wavelength of the transition (Å)

 -2 or --2        compute hfs oscillator strength for on HFS transition
                  |I,J0,F0> → |I,J1,F1>
                  with these additional options:
         --I  int/int (required)
         --J0 int/int (required)
         --J1 int/int (required)
         --F0 int/int (required)
         --F1 int/int (required)
         --gf real    HF oscillator strength log(gf_hf) (required)

 -3 or --3        compute energy shift of the level (J0 F0)
                  with these additional options:
         --I int/int  (required).
         --J0 int/int (required). 
         --F0 int/int I⊗J0 (required). 
         --A0 real    A-HFS constant of the level
         --B0 real    B-HFS constant of the level

The mandatory format int/int means p/q, ∀(p,q) ∈ N ⨯ 2N.

HFS shift is computed with the first order perturbation theory since coupling between magnetic field of electronic cloud and nucleus momentum is weak. Wigner 6j symbols are used to facilitate the manipulation of spherical harmonics in the matrix elements computation. 

A and B are independent from F: A=A(2S+1 L_J). They are expressed in MHz or mK. Thus one has to multiply the energy by 1e6*h or 1e-3*k_B.

Note that nuclei far away from the double magicity (±3 nucleons) and heavy elements are no more spherical (Q<0 or Q>0) and HFS constant B might have to be taken into account.

 Examples: 
     Ca: A=40  Z=20 N=20  Q=0 b 
     Hg: A=201 Z=80 N=121 Q=0.65 b 
     U:  A=238 Z=92 N=146 Q=11 b 

Even-Even nucleus has I=0.

Notations:
 <H> ≐ <nIJF|H|nIJF>
 <ΔH> ≐ E(I,J',F') - E(I,J,F)

Command examples:
 ./shfs -0 -I 3/2 --J0 1
 ./shfs -1 -I 7/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3
 ./shfs -2 -I 7/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3 --gf 10
 ./shfs -3 -I 3/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3

 ref: 
 R. D. Cowan, The Theory of Atomic Structure and Spectra (1981) 
 Jie Wang et al. (2014) - DOI: 10.1088/0957-0233/25/3/035501 
 G. M. Wahlgren (1995) - DOI: 10.1086/175618
 https://www-nds.iaea.org/nuclearmoments
```
>
> Dummy examples:
>

Caesium 8S1/2: A=219 MHz
```
$ ./shfs -0 -I 3/2 --J0 1 -A 219
Parameters:
- I=3/2
- J0=1
- A0=219

● HFS Energy shift:
→ Magnetic dipole M1
F=1/2   <H>_M1/A=-5/2   <H>_M1≃-547.5
F=3/2   <H>_M1/A=-1     <H>_M1≃-219
F=5/2   <H>_M1/A=3/2    <H>_M1≃328.5

→ Electric quadrupole E2 
F=1/2   <H>_E2/B=5/4
F=3/2   <H>_E2/B=-1
F=5/2   <H>_E2/B=1/4


bye !

$ ./shfs -1 -I 7/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3 --A0 12 --A1 -5
Parameters:
- I=7/2
- J0=1/2
- J1=1/2
- F0=4
- F1=3
- A0=12
- A1=-5

❶ HFS Energy shift:
→ Magnetic dipole M1
<ΔH>_M1=-9.75


bye !

$ ./shfs -2 -I 7/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3 --gf 10
Parameters:
- I=7/2
- J0=1/2
- J1=1/2
- F0=4
- F1=3
- gf_FS=10

❷ HFS oscillator strength:
→ gf_HFS=26.25
→ log(gf_HFS)=3.2677
→ effective ngf_HFS=3.28125
→ effective log(ngf_HFS)=1.1882


bye !

$ ./shfs -3 -I 3/2 --J0 1/2 --F0 4 --J1 1/2 --F1 3
Parameters:
- I=3/2
- J0=1/2
- J1=1/2
- F0=4
- F1=3

❸ HFS Energy shift:
→ Magnetic dipole M1
<ΔH>_M1/A=31/4

→ Electric quadrupole E2 
<ΔH>_E2/B=0


bye !

```
