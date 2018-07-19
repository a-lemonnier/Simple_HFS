********
* Build:
********

Dependencies:
- cmake
- gcc / g++ : c++11

```
$ ls
- CMakeLists.txt  include  main.cpp  README

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
[ 25%] Building CXX object CMakeFiles/shfs.dir/main.cpp.o
[ 50%] Building CXX object CMakeFiles/shfs.dir/include/io.cpp.o
[ 75%] Building CXX object CMakeFiles/shfs.dir/include/cte.cpp.o
[100%] Linking CXX executable shfs
[100%] Built target shfs
```

********
* Run:
********
```
$ ./shfs -h
Usage: ./shfs [OPTIONS]
 	compute energy shift from quantum numbers and hfs constants if available 

 OPTIONS:
 -h              show this help
 -I int/int      momentum of electrons. Sets: integer or half integer (required)
 -J int/int      momentum of the nucleus. Sets: integer or half integer (required)
 -F int/int      total momentum: I+J. Sets: integer or half integer (required)
 -A real         A-hfs constant
 -B real         B-hfs constant
 -l real         wavelength of the transition

I=0 or J=0 or I=1/2 or J=1/2 will return a 'div by 0' while
computing E2 shift.

Please note that nuclei far away from the double magicity (±3 nucleons)
are no more spherical (Q<0 or Q>0) and hfs constant B might have to be taken into account.

G. M. Wahlgren (1995) - DOI: 10.1086/175618

$ echo "example"
$ ./shfs -I 3/2 -J 1 -F 1 -A 0.1  -l 1625.25
Parameters:
I=3/2~1.5 J=1 F=1
A=0.1
wavelength: 1625.25

HFS Energy shift:
-> Magnetic dipole
E_M1/A=-15/8~-1.875

E_M1=-0.1875
-> Electric quadrupole
E_E2/B=0

wavelength shift: 1625.25

bye !
```
