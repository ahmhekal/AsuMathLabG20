#include <math.h>
#include <iostream>
using namespace std;

class Complex{
	float R; float I;
public:
	Complex() {R=0; I=0;}
	Complex(float r, float i){R=r;I=i;}
	void SetComplex(float r , float i);
	float GetReal();
	float GetImaj();
	void SetReal(float r);
	void SetImaj(float i);
	Complex Add(Complex x);
	Complex Subtract(Complex x);
	Complex Multiply(Complex x);
	Complex Divide(Complex x);
	Complex Conjugate();
	Complex Power(Complex x, int y);
	Complex operator =(Complex x);
	Complex operator +(Complex x);
	Complex operator -(Complex x);
	Complex operator *(Complex x);
	Complex operator /(Complex x);
	Complex operator *=(Complex x); 
	Complex operator^(int n);
	friend ostream&  operator << ( ostream& o , Complex c);

};