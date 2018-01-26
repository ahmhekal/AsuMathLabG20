#include "Complex.h"


void Complex :: SetComplex(float r , float i){R=r; I=i;}
float Complex :: GetReal(){ return R;}
float Complex :: GetImaj(){ return I;}
void Complex :: SetReal(float r){ R=r;}
void Complex :: SetImaj(float i){ I=i;}
Complex Complex :: Add(Complex x){ Complex c; c.R= R + x.R; c.I= I + x.I;  return c; }
Complex Complex :: Subtract(Complex x){ Complex c; c.R= R - x.R; c.I= I - x.I;  return c; }
Complex Complex :: Multiply(Complex x){ Complex c;  c.R=(R*x.R)-(I*x.I);  c.I=(R*x.I)+(I*x.R);  return c; }

Complex Complex :: Divide(Complex x){ 
	int div=(x.R*x.R) + (x.I*x.I);
	Complex tmp; 
	tmp.R=(R*x.R)+(I*x.I); tmp.R/=div; tmp.I=(I*x.R)-(R*x.I); tmp.I/=div; 
	return tmp; }

ostream&  operator << ( ostream& o , Complex c)
{
	if(c.GetReal()>0 && c.GetImaj()>0){o<<c.GetReal()<<" + "<<c.GetImaj()<<"i"<<"\n";return o;}
	if(c.GetReal()>0 && c.GetImaj()<0){o<<c.GetReal()<<" - "<<-c.GetImaj()<<"i"<<"\n";return o;}
	if(c.GetReal()>0 && c.GetImaj()==0){o<<c.GetReal()<<"\n"; return o;}
	if(c.GetReal()==0 && c.GetImaj()>0){o<<c.GetImaj()<<"i"<<"\n"; return o;}
	if(c.GetReal()==0 && c.GetImaj()<0){o<<" - "<<-c.GetImaj()<<"i"<<"\n";return o;}
	if(c.GetReal()==0 && c.GetImaj()==0){o<<c.GetReal()<<"\n"; return o;}
	if(c.GetReal()<0 && c.GetImaj()<0){o<<c.GetReal()<<" - "<<-c.GetImaj()<<"i"<<"\n";return o;} // look at "-c.GetImaj()"
	if(c.GetReal()<0 && c.GetImaj()>0){o<<c.GetReal()<<" + "<<c.GetImaj()<<"i"<<"\n";return o;}
	if(c.GetReal()<0 && c.GetImaj()==0){o<<c.GetReal()<<"\n";return o;}
}
Complex Complex:: operator = (Complex x ) {R=x.GetReal(); I=x.GetImaj(); return x;}
Complex Complex:: operator + (Complex x ) {return Add(x);}
Complex Complex:: operator - (Complex x ) {return Subtract(x);}
Complex Complex:: operator * (Complex x ) {return Multiply(x);}
Complex Complex:: operator / (Complex x ) {return Divide(x);}
Complex Complex:: operator *=(Complex x ) {Complex temp; temp.SetComplex(1,1);return Multiply(x);}
Complex Complex:: Conjugate() {Complex tmp;tmp.R=this->R;tmp.I=this->I*(-1); return tmp;}
Complex Complex:: operator^(int n){
	Complex ONE=Complex(1,0);
	if (n<=0) return ONE;
	return ((*this)*((*this)^(n-1)));
}