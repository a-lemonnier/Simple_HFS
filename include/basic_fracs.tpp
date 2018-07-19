#include "basic_fracs.hpp"

// ***********
// Constructors
// ***********
/*********************************************************************/

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>::_frac(_T1 a, _T2 b) {
    if (b==0) {
        b=1;
        std::cerr << "/0!\n";
    }
    this->F[0]=a;
    this->F[1]=b;
    this->simplified=false;
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>::_frac() {
    this->F[0]=0;
    this->F[1]=1;
    this->simplified=false;
}
/***********/


// ***********
// Operateurs
// ***********
/*********************************************************************/

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator= ( const _frac<_T, _T1, _T2> & frac ) {
    if (&frac != this) {
        this->F[0]=frac.F[0];
        this->F[1]=frac.F[1];
        this->simplified=frac.simplified;
    }
    return *this;
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator+ ( const _frac<_T, _T1, _T2> & frac ) {
    _frac* res=new _frac();
    _T a=this->F[0];
    _T b=this->F[1];
    _T c=frac.F[0];
    _T d=frac.F[1];
    res->F[0]=a*d+b*c;    
    res->F[1]=b*d;
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator- ( const _frac& frac ) {
    _frac* res=new _frac();
    _T a=this->F[0];
    _T b=this->F[1];
    _T c=frac.F[0];
    _T d=frac.F[1];
    res->F[0]=a*d-b*c;    
    res->F[1]=b*d;
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator* ( const _frac& frac ) {
    _frac* res=new _frac();
    res->F[0]=this->F[0]*frac.F[0];    
    res->F[1]=this->F[1]*frac.F[1];
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator^ ( _T2 n ) {
    _frac* res=new _frac();
    res->F[0]=pow(this->F[0],n);    
    res->F[1]=pow(this->F[1],n);
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator/ ( const _frac<_T, _T1, _T2> &frac ) {
    _T2 s=frac.F[0];
    if (s==0) {
        s=1;
        std::cerr << "/0!\n";
    }
    _frac* res=new _frac();
    res->F[0]=this->F[0]*frac.F[1];    
    res->F[1]=this->F[1]*s;
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator+= ( const _frac& frac ) {
    _T2 d=this->F[1]+frac.F[1];
    if (d==0) {
        d=1;
        std::cerr << "/0!\n";
    }
    _frac* res= new _frac(this->F[0]*frac.F[0],d);
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator-= ( const _frac& frac ) {
    _T2 d=this->F[1]-frac.F[1];
    if (d==0) {
        d=1;
        std::cerr << "/0!\n";
    }
    _frac* res= new _frac(this->F[0]*frac.F[0],d);
    res->simplify();
    return *res;        
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator*= ( const _frac& frac ) {
    _T2 d=this->F[1]*frac.F[1];
    if (d==0) {
        d=1;
        std::cerr << "/0!\n";
    }
    _frac* res= new _frac(this->F[0]*frac.F[0],d);
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator++ ( int ) {
    this->F[0]+=F[1];
    this->simplify();
    return *this;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator-- ( int ) {
    this->F[0]-=F[1];
    this->simplify();
    return *this;    
}

template<class _T, class _T1, class _T2>
bool _frac<_T, _T1, _T2>::operator> ( const _frac& frac ) {
    return (this->F[0]/this->F[1]) > (frac.F[0]/frac.F[1]);    
}

template<class _T, class _T1, class _T2>
bool _frac<_T, _T1, _T2>::operator< ( const _frac& frac ) {
    return (this->F[0]/this->F[1]) < (frac.F[0]/frac.F[1]);    
}


template<class _T, class _T1, class _T2>
bool _frac<_T, _T1, _T2>::operator== ( const _frac& frac ) {
    return this->F[0]==frac.F[0] && this->F[1]==frac.F[0];    
}

template<class _T, class _T1, class _T2>
bool _frac<_T, _T1, _T2>::operator!= ( const _frac& frac ) {
    return this->F[0]!=frac.F[0] || this->F[1]!=frac.F[0];    
}

/***********/


// ***********
// Method
// ***********
/*********************************************************************/

template<class _T, class _T1, class _T2>
void _frac<_T, _T1, _T2>::show() {
    unsigned int prec=10;
    if (sizeof(_T)==sizeof(double long)) prec=308;
    if (sizeof(_T)==sizeof(long long)) prec=308;
    if (sizeof(_T)==sizeof(double)) prec=308;
    if (sizeof(_T)==sizeof(long)) prec=12;
    if (sizeof(_T)==sizeof(int)) prec=12;
    
    if  (this->F[1]!=1 &&  this->F[1]!=0) 
        std::cout << std::setprecision(prec) 
                    << static_cast<_T>(this->F[0]) 
                    << "/" << static_cast<_T>(this->F[1])
                    << "~" 
                    << static_cast<_T>(this->F[0]/this->F[1]) ;
    if  (this->F[1]==1 ) 
        std::cout << std::setprecision(prec) 
                    << static_cast<int>(this->F[0]);
    if  (this->F[1]==0) std::cerr << "/0!\n";
}

template<class _T, class _T1, class _T2>
void _frac<_T, _T1, _T2>::simplify() {
    _T d=gcd(this->F[0],this->F[1]);
    this->F[0]/=d;
    this->F[1]/=d;

    if (this->F[1]<0) {
	    this->F[0]=-this->F[0];
	    this->F[1]=-this->F[1];
    }

    this->simplified=true;
}

template<class _T, class _T1, class _T2>
_T _frac<_T, _T1, _T2>::gcd(_T1 a, _T2 b) {
    _T c = fmodl(a,b);
  while(c != 0) {
    a = b;
    b = c;
    c = fmodl(a,b);
  }
  return b;
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2> & _frac<_T, _T1, _T2>::abs() {
    this->F[0]=fabs(this->F[0]);
    this->F[1]=fabs(this->F[1]);
    return *this;
}

/***********/
