#include "basic_fracs.hpp"


// ***********
// Constructors
// ***********
/***************************************/

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>::_frac(_T1 a, _T2 b) {
    if (b==0) {
        b=1;
        std::cerr << "./0!.";
    }
    this->F[0]=a;
    this->F[1]=b;
    this->simplified=false;
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>::_frac(_T1 a) {
    this->F[0]=a;
    this->F[1]=1;
    this->simplified=true;
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
/***************************************/

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
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator+ ( _T1 x ) {
    _frac* res=new _frac();
    res->F[0]=this->F[0]+this->F[1]*x; 
    res->F[1]=this->F[1];
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
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator- ( _T1 x ) {
    _frac* res=new _frac();
    res->F[0]=this->F[0]-this->F[1]*x;
    res->F[1]=this->F[1];    
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
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator* ( _T1 x ) {
    _frac* res=new _frac();
    res->F[0]=this->F[0]*x;
    res->F[1]=this->F[1];    
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
    _T2 q=frac.F[0];
    if (q==0) {
        q=1;
        std::cerr << "./0!.";
    }
    _frac* res=new _frac();
    res->F[0]=this->F[0]*frac.F[1];    
    res->F[1]=this->F[1]*q;
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator/ ( _T1 x ) {
    _frac* res=new _frac();
    res=this;
    if (x!=0)
        res->F[1]=this->F[1]*x;
    else {
        std::cerr << "./0!.";
    }
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator+= ( const _frac& frac ) {
    _T2 d=this->F[1]+frac.F[1];
    if (d==0) {
        d=1;
        std::cerr << "./0!.";
    }
    _frac* res= new _frac(this->F[0]*frac.F[0],d);
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator+= ( _T1 x) {
    return *(this+x);    
}


template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator-= ( const _frac& frac ) {
    _T2 d=this->F[1]-frac.F[1];
    if (d==0) {
        d=1;
        std::cerr << "./0!.";
    }
    _frac* res= new _frac(this->F[0]*frac.F[0],d);
    res->simplify();
    return *res;        
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator-= ( _T1 x) {
    return *(this-x);    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator*= ( const _frac& frac ) {
    _T2 d=this->F[1]*frac.F[1];
    if (d==0) {
        d=1;
        std::cerr << "./0!.";
    }
    _frac* res= new _frac(this->F[0]*frac.F[0],d);
    res->simplify();
    return *res;    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator*= ( _T1 x ) {
    return *(this*x);    
}

template<class _T, class _T1, class _T2>
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::operator/= ( _T1 x ) {
    _frac* res= new _frac(this->F[0],this->F[1]*x);
    this->simplify();
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
bool _frac<_T, _T1, _T2>::operator> (_T2 x) {
    return (this->F[0]/this->F[1]) > x;    
}

template<class _T, class _T1, class _T2>
bool _frac<_T, _T1, _T2>::operator< ( const _frac& frac ) {
    return (this->F[0]/this->F[1]) < (frac.F[0]/frac.F[1]);    
}

template<class _T, class _T1, class _T2>
bool _frac<_T, _T1, _T2>::operator< ( _T2 x ) {
    return (this->F[0]/this->F[1]) < x;    
}

template<class _T, class _T1, class _T2>
bool _frac<_T, _T1, _T2>::operator== ( const _frac& frac ) {
    return this->F[0]==frac.F[0] && this->F[1]==frac.F[1];    
}

template<class _T, class _T1, class _T2>
bool _frac<_T, _T1, _T2>::operator== ( _T2 x ) {
    return this->val()==x;    
}

template<class _T, class _T1, class _T2>
bool _frac<_T, _T1, _T2>::operator!= ( const _frac& frac ) {
    return this->F[0]!=frac.F[0] || this->F[1]!=frac.F[0];    
}

template<class _T, class _T1, class _T2>
bool _frac<_T, _T1, _T2>::operator!= ( _T2 x ) {
    return this->val()!=x;    
}


/***********/


// ***********
// Method
// ***********
/***************************************/

template<class _T, class _T1, class _T2>
std::string _frac<_T, _T1, _T2>::show() {
    std::string str;
    std::ostringstream buf;
    unsigned int prec=15;
    if  (this->F[1]!=1 &&  this->F[1]!=0) 
        buf << std::setprecision(prec) 
                    << static_cast<_T>(this->F[0]) 
                    << "/" << static_cast<_T>(this->F[1])
                    << "\u2243" 
                    << static_cast<_T>(this->F[0]/this->F[1]) ;
    if  (this->F[1]==1 && (std::floor(this->F[0]) ==  this->F[0]))
        buf << std::setprecision(prec) 
                    << static_cast<int>(this->F[0]);
    if  (this->F[1]==1 && (std::floor(this->F[0]) !=  this->F[0]))
        buf << std::setprecision(prec) 
                    << static_cast<_T>(this->F[0]);
    if  (this->F[1]==0) buf << "./0!.";
    return buf.str();
}

template<class _T, class _T1, class _T2>
void _frac<_T, _T1, _T2>::simplify() {
    if (std::floor( this->F[0]) ==  this->F[0] && 
	std::floor( this->F[1]) ==  this->F[1] )  {
    _T d=gcd(this->F[0],this->F[1]);
      this->F[0]/=d;
      this->F[1]/=d;
      if (this->F[1]<0) {
	      this->F[0]=-this->F[0];
	      this->F[1]=-this->F[1];
      }
    }
    this->simplified=true;
}

template<class _T, class _T1, class _T2>
_T _frac<_T, _T1, _T2>::val() {
    return this->F[0]/this->F[1];
}


template<class _T, class _T1, class _T2> 
_frac<_T, _T1, _T2>& _frac<_T, _T1, _T2>::str_to_frac(const std::string &str) {
    _frac* res= new _frac();
     std::size_t pos=str.find('/');
     if (pos!=std::string::npos)
                *res=_frac<>(std::stold( str.substr(0,pos) ),
                           std::stold( str.substr( pos+1, str.length()-1 )));
                else *res=_frac<>(std::stold(str));
    return *res;
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


// ***********
// Symmetry of operators
// ***********
/***************************************/

template<typename _TT, typename _TT1, typename _TT2, typename _TT3>
_frac<_TT,_TT1,_TT2> operator+(_TT3 x, const _frac<_TT,_TT1,_TT2> &frac) {
    _frac<_TT,_TT1,_TT2>* res=new _frac<_TT,_TT1,_TT2>();
    res->F[0]=frac.F[0]+frac.F[1]*x;
    res->F[1]=frac.F[1];
    res->simplify();    
    return *res;
}

template<typename _TT, typename _TT1, typename _TT2, typename _TT3>
_frac<_TT,_TT1,_TT2> operator-(_TT3 x, const _frac<_TT,_TT1,_TT2> &frac) {
    _frac<_TT,_TT1,_TT2>* res=new _frac<_TT,_TT1,_TT2>();
    res->F[0]=frac.F[0]-frac.F[1]*x;
    res->F[1]=frac.F[1];
    res->simplify();    
    return *res;
}

template<typename _TT, typename _TT1, typename _TT2, typename _TT3>
_frac<_TT,_TT1,_TT2>& operator*(_TT3 x, const _frac<_TT,_TT1,_TT2> &frac) {
    _frac<_TT,_TT1,_TT2>* res=new _frac<_TT,_TT1,_TT2>();
    res->F[0]=frac.F[0]*x;
    res->F[1]=frac.F[1];
    res->simplify();    
    return *res;
}
/***********/
