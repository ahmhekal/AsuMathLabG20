#include "Complex.h"


void Complex :: SetComplex(double r , double i){R=r; I=i;}

double Complex :: GetR(){ return R;}
double Complex :: GetIm(){ return I;}

void Complex :: SetR(double r){ R=r;}
void Complex :: SetIm(double i){ I=i;}


void Complex :: Add(Complex& x){R += x.R; I += x.I; }

void Complex :: Subtract(Complex& x){R -= x.R; I -= x.I;}

void Complex :: Multiply(Complex& x){double Real=R; double Imaj=I;  R=(Real*x.R)-(Imaj*x.I); I=(Real*x.I)+(Imaj*x.R);}

void Complex :: Divide(Complex& x){ 
	double Real=R; double Imaj=I;
	R=((Real*x.R)+(Imaj*x.I))/((x.R*x.R) + (x.I*x.I)); I=((Imaj*x.R)-(Real*x.I))/((x.R*x.R) + (x.I*x.I));
}


Complex Complex ::AddComplex(Complex& x,Complex& y){Complex C;C.R = x.R + y.R; C.I = x.I + y.I; return C;}

Complex Complex ::SubtractComplex(Complex& x,Complex& y){Complex C;C.R = x.R - y.R; C.I = x.I - y.I; return C;}

Complex Complex ::MultiplyComplex(Complex& x){Complex c;  c.R=(R*x.R)-(I*x.I);  c.I=(R*x.I)+(I*x.R);  return c;}

Complex Complex ::DivideComplex(Complex& x){
	double div=(x.R*x.R) + (x.I*x.I);
	Complex tmp; 
	tmp.R=(R*x.R)+(I*x.I); tmp.R/=div; tmp.I=(I*x.R)-(R*x.I); tmp.I/=div; 
	return tmp;
}

Complex Complex::Power(Complex& input, int power)
{
	Complex ONE=Complex(1,0);
    if (power>= 0) {for (int i = 0; i < power; ++i) ONE = ONE * input; }
    else		   {for (int i = 0; i > power; --i) ONE = ONE / input; }
    return ONE;
}

double Complex :: modulus() {double absolute = sqrt((R*R)+(I*I)); return absolute; }

Complex Complex:: Conjugate() {Complex tmp;tmp.R=this->R;tmp.I=this->I*(-1); return tmp;}


Complex Complex:: operator = ( Complex& x ) {R=x.GetR(); I=x.GetIm(); return x;}
Complex Complex:: operator + ( Complex& x ) {return AddComplex(*this,x);}
Complex Complex:: operator - ( Complex& x ) {return SubtractComplex(*this,x);}
Complex Complex:: operator * ( Complex& x ) {return MultiplyComplex(x);}
Complex Complex:: operator / ( Complex& x ) {return DivideComplex(x);}

void Complex:: operator +=(Complex& x ) { Add(x);}
void Complex:: operator -=(Complex& x ) { Subtract(x);}
void Complex:: operator *=(Complex& x ) { Multiply(x);}
void Complex:: operator /=(Complex& x ) { Divide(x);}


Complex Complex:: operator +(double& x){return AddComplex(*this, Complex(x, 0));}
Complex Complex:: operator -(double& x){return SubtractComplex(*this, Complex(x, 0));}
Complex Complex:: operator *(double& x){return Complex(R*x,I*x);}
Complex Complex:: operator /(double& x){return Complex(R/x,I/x);}

void Complex:: operator +=(double& x){R+=x;}
void Complex:: operator -=(double& x){R-=x;}

void Complex:: operator *=(double& x){R*=x; I*=x;}		//operation on Both Real & Imaj
void Complex:: operator /=(double& x){R/=x; I/=x;}		//operation on Both Real & Imaj

Complex Complex::operator++(){R++; return *this;}
Complex Complex::operator++(int){Complex C = *this; R+=1; return C;}
Complex Complex::operator--(){R--; return *this;}
Complex Complex::operator--(int){Complex C = *this; R-=1; return C;}

Complex Complex::operator-(){return Complex(-R, -I);}

Complex Complex:: operator^(int n){return Power(*this,n);}



ostream&  operator << ( ostream& o , Complex& c)
{
	if(c.GetR()>0 && c.GetIm()>0){o<<c.GetR()<<" + "<<c.GetIm()<<"i"<<"\n";return o;}
	else if(c.GetR()>0 && c.GetIm()<0){o<<c.GetR()<<" - "<<-c.GetIm()<<"i"<<"\n";return o;}
	else if(c.GetR()>0 && c.GetIm()==0){o<<c.GetR()<<"\n"; return o;}
	else if(c.GetR()==0 && c.GetIm()>0){o<<c.GetIm()<<"i"<<"\n"; return o;}
	else if(c.GetR()==0 && c.GetIm()<0){o<<" - "<<-c.GetIm()<<"i"<<"\n";return o;}
	else if(c.GetR()==0 && c.GetIm()==0){o<<c.GetR()<<"\n"; return o;}
	else if(c.GetR()<0 && c.GetIm()<0){o<<c.GetR()<<" - "<<-c.GetIm()<<"i"<<"\n";return o;} // look at "-c.GetIm()"
	else if(c.GetR()<0 && c.GetIm()>0){o<<c.GetR()<<" + "<<c.GetIm()<<"i"<<"\n";return o;}
	//else if(c.GetR()<0 && c.GetIm()==0){o<<c.GetR()<<"\n";return o;}
	else {o<<c.GetR()<<"\n";return o;}
}
