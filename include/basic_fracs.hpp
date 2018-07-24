#ifndef BASIC_FRACS_HPP
#define BASIC_FRACS_HPP

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>

template<class _T, class _T1, class _T2> class _frac;


// ***********
// Symmetry of operators
// ***********
/***************************************/
template<typename _TT, typename _TT1, typename _TT2, typename _TT3>
_frac<_TT,_TT1,_TT2> operator+(_TT3 x, const _frac<_TT,_TT1,_TT2> &frac);
template<typename _TT, typename _TT1, typename _TT2, typename _TT3>
_frac<_TT,_TT1,_TT2> operator-(_TT3 x, const _frac<_TT,_TT1,_TT2> &frac);
template<typename _TT, typename _TT1, typename _TT2, typename _TT3>
_frac<_TT,_TT1,_TT2>& operator*(_TT3 x, const _frac<_TT,_TT1,_TT2> &frac);
/***********/


template<class _T=double long, class _T1=double long, class _T2=double long>
class _frac {
public:
    
    _T F[2];
    
    _frac(_T1 a, _T2 b); // a/b
    _frac(_T1 a);   // a/1
    _frac(void); // 0/1
    
    // print frac<>
    std::string show(void);
    // print approx
    _T val(void); 
    
    // convert string "p/q" to _frac<>(p,q)
    static _frac<_T, _T1, _T2>& str_to_frac(const std::string &str);
    
    _frac& abs(void);
    
    _frac& operator= ( const _frac &frac );
    
    _frac& operator+ ( const _frac &frac );
    _frac& operator+ ( _T1 x );
    template<typename _TT, typename _TT1, typename _TT2, typename _TT3>
    friend _frac<_TT,_TT1,_TT2> operator+(_TT3 x, const _frac<_TT,_TT1,_TT2> &frac);
    
    _frac& operator- ( const _frac &frac );
    _frac& operator- ( _T1 x );
    template<typename _TT, typename _TT1, typename _TT2, typename _TT3>
    friend _frac<_TT,_TT1,_TT2> operator-(_TT3 x, const _frac<_TT,_TT1,_TT2> &frac);
    
    _frac& operator* ( const _frac &frac );
    _frac& operator* ( _T1 x );
    template<typename _TT, typename _TT1, typename _TT2, typename _TT3>
    friend _frac<_TT,_TT1,_TT2>& operator*(_TT3 x, const _frac<_TT,_TT1,_TT2> &frac);
    
    _frac& operator^ ( _T2 n );
    _frac& operator/ ( const _frac &frac );
    _frac& operator/ ( _T1 x );
    
    _frac& operator++ ( int );
    _frac& operator-- ( int );
    
    _frac& operator+= ( const _frac &frac );
    _frac& operator+= ( _T1 );
    _frac& operator-= ( const _frac &frac );
    _frac& operator-= ( _T1 );
    _frac& operator*= ( const _frac &frac );
    _frac& operator*= ( _T1 );
    _frac& operator/= ( _T1 );
    
    bool operator< ( const _frac &frac );
    bool operator< ( _T2 );
    bool operator> ( const _frac &frac );
    bool operator> ( _T2 );
    
    bool operator== ( const _frac &frac );
    bool operator== ( _T2 );
    bool operator!= ( const _frac &frac );
    bool operator!= ( _T2 );
    
protected:
    bool simplified;
    
private:
    void simplify(void);
    _T gcd(_T1, _T2);
    
};

#include "basic_fracs.tpp"

#endif // BASIC_FRACS_HPP
