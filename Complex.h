#include <math.h>
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

class Complex{
	double R; double I;
public:
	Complex() {R=0; I=0;}
	Complex(double r, double i){R=r;I=i;}

	void SetComplex(double r , double i);

	double GetR();
	double GetIm();

	void SetR(double r);
	void SetIm(double i);

	void Add(Complex& x);
	void Subtract(Complex& x);
	void Multiply(Complex& x);
	void Divide(Complex& x);

	Complex Conjugate();
	Complex Power(Complex& x, int y);
	double modulus();

	Complex AddComplex(Complex& x,Complex& y);
	Complex SubtractComplex(Complex& x,Complex& y);
	Complex MultiplyComplex(Complex& x);
	Complex DivideComplex(Complex& x);

	Complex operator =(Complex& x);
	Complex operator +(Complex& x);
	Complex operator -(Complex& x);
	Complex operator *(Complex& x);
	Complex operator /(Complex& x);


	void operator +=(Complex& x);
	void operator -=(Complex& x);
	void operator *=(Complex& x);
	void operator /=(Complex& x);

	Complex operator^(int n);

	friend ostream&  operator << ( ostream& o ,Complex& c);

};
