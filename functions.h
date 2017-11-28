#include "matrix.h"
#include "math.h"

// generate the sec, csc, cot, asec, acsc, acot
#define EXTRA_TRIG_FN(name, fn)					\
double name(double n) { return 1/fn(n); }			\
double a##name(double n) { return a##fn(1/n); }			\
double name##h(double n) { return 1/fn##h(n); }			\
double a##name##h(double n) { return a##fn##h(1/n); }

EXTRA_TRIG_FN(sec, cos)  // sec, asec, sech, asech
EXTRA_TRIG_FN(csc, sin)
EXTRA_TRIG_FN(cot, tan)

// generate elementwise functions with one argument:
// like sin, cos, tan, atan, etc
#define ELEMENTWISE_FN(name)					\
asu::CMatrix name(const asu::CMatrix& m)			\
{								\
	asu::CMatrix r(m.getnRows(), m.getnColumns());		\
	for (size_t i = 0; i < m.getn(); i++)			\
		r(i) = name(m(i));				\
	return r;						\
}

// generate the decimal trigonometric counterpart functions
#define TRIG_DECIMAL_GEN(name)					\
double name##d(double n) { return name(n * M_PI / 180); }	\
double a##name##d(double n) { return a##name(n) * 180 / M_PI; }


TRIG_DECIMAL_GEN(sin)  // sind, asind (for double)
TRIG_DECIMAL_GEN(cos)  // ...
TRIG_DECIMAL_GEN(tan)
TRIG_DECIMAL_GEN(cot)
TRIG_DECIMAL_GEN(sec)
TRIG_DECIMAL_GEN(csc)

// generate all the trigonometric functions: sin, asin, cosh, etc
#define TRIG_GENERATE(name)					\
ELEMENTWISE_FN(name)						\
ELEMENTWISE_FN(a##name)						\
ELEMENTWISE_FN(name##d)						\
ELEMENTWISE_FN(a##name##d)					\
ELEMENTWISE_FN(name##h)						\
ELEMENTWISE_FN(a##name##h)

TRIG_GENERATE(sin)  // sin, sind, asin, asind, sinh, asinh (for CMatrix)
TRIG_GENERATE(cos)
TRIG_GENERATE(tan)
TRIG_GENERATE(cot)
TRIG_GENERATE(sec)
TRIG_GENERATE(csc)

// generate elementwise functions with two arguments:
// like atan2, hypot
#define ELEMENTWISE_FN2(name)					\
asu::CMatrix name(const asu::CMatrix& a, const asu::CMatrix& b)	\
{								\
	if (a.getnRows() != b.getnRows()			\
	    || a.getnColumns() != b.getnColumns())		\
		throw std::invalid_argument			\
		    ("Invalid matrix dimensions"		\
		     " in " #name "()");			\
	asu::CMatrix r(a.getnRows(), a.getnColumns());		\
	for (size_t i = 0; i < a.getn(); i++)			\
		r(i) = name(a(i), b(i));			\
	return r;						\
}								\

double atan2d(double x, double y) { return atan2(x, y) * 180 / M_PI; }
double hypot(double a, double b) { return sqrt(a * a + b * b); }

ELEMENTWISE_FN2(atan2)
ELEMENTWISE_FN2(atan2d)
ELEMENTWISE_FN2(hypot)

// rad-deg conversions
double rad2deg(double r) { return r * 180 / M_PI; }
double deg2rad(double d) { return d * M_PI / 180; }

ELEMENTWISE_FN(rad2deg)
ELEMENTWISE_FN(deg2rad)

// exp, log, etc
ELEMENTWISE_FN(exp)
ELEMENTWISE_FN(log)
ELEMENTWISE_FN(log10)
ELEMENTWISE_FN(log2)
ELEMENTWISE_FN(log1p)
ELEMENTWISE_FN(sqrt)
ELEMENTWISE_FN2(pow)
double power(double n, double m) { return pow(n, m); }
asu::CMatrix power(const asu::CMatrix& n, const asu::CMatrix& m)
{ return pow(n, m); }
