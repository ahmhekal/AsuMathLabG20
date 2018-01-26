#include "matrix.h"
#include "math.h"

/*
 * Part 0: Introduction
 * ====================
 *
 * We need to write functions for `sin`, `cos`, `sqrt`, etc that take a matrix
 * and return a matrix, whose elements are the result of applying the function
 * on the each element in the input matrix.
 * eg, `sqrt([1 4; 9 16])` = `[1 2; 3 4]`.
 *
 * We implement all Trigonometry functions and most of Exponents and Logarithms
 * functions: https://www.mathworks.com/help/matlab/functionlist.html
 *
 * All these functions are element-wise, so we need to have these functions
 * take double and return double, first, then overload them to accept matrices.
 *
 * But, not all the required functions are available in C++ standard library,
 * So we need to make those first.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Part 1: Trigonometry functions
 * ==============================
 *
 * Section 0: Introduction
 * -----------------------
 *
 * We need to implement 41 functions:
 *   sin      cos      tan      csc      sec      cot
 *   sind     cosd     tand     cscd     secd     cotd
 *   sinh     cosh     tanh     csch     sech     coth
 *   asin     acos     atan     acsc     asec     acot
 *   asind    acosd    atand    acscd    asecd    acotd
 *   asinh    acosh    atanh    acsch    asech    acoth
 *   deg2rad  rad2deg
 *   atan2    atan2d   hypot
 *
 * We assume that we have all these implemented on numbers (`double`), but
 * because this is not the case, we need to fill in the gaps first.
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * Section 1: Defining the reciprocals
 * -----------------------------------
 *
 * We already have `sin`, `sinh`, `asin`, and `asinh`. But we don't have their
 * reciprocals: `csc`, `csch`, `acsc`, and `acsch`. Similarly, we don't have
 * any `sec` or `cot` functions; we need to define those first, for `double`s.
 *
 */

// generate sec, csc, asec, etc
#define EXTRA_TRIG_FN(name, fn)                                     \
    double name(double n) { return 1/fn(n); }                       \
    double a##name(double n) { return a##fn(1/n); }                 \
    double name##h(double n) { return 1/fn##h(n); }                 \
    double a##name##h(double n) { return a##fn##h(1/n); }

EXTRA_TRIG_FN(sec, cos)  // sec, asec, sech, asech
EXTRA_TRIG_FN(csc, sin)
EXTRA_TRIG_FN(cot, tan)

/*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * Section 2: Defining the degrees functions
 * -----------------------------------------
 *
 * In MATLAB, `sin` takes radians. Great! That's exactly how C++ `sin` works.
 * Also, MATLAB presents `sind`, which take degrees. That means: for every trig
 * function, you need another function that takes or returns degrees instead of
 * radians.
 *
 */

// generate the decimal trigonometric counterpart functions
#define TRIG_DECIMAL_GEN(name)                                      \
    double name##d(double n) { return name(n * M_PI / 180); }       \
    double a##name##d(double n) { return a##name(n) * 180 / M_PI; }

TRIG_DECIMAL_GEN(sin)  // sind, asind (for double)
TRIG_DECIMAL_GEN(cos)  // ...
TRIG_DECIMAL_GEN(tan)
TRIG_DECIMAL_GEN(cot)
TRIG_DECIMAL_GEN(sec)
TRIG_DECIMAL_GEN(csc)

/*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * Section 3: All one-argument trig functions
 * ------------------------------------------
 *
 * Now, it is the time! We can now generate the 36 trig functions easily.
 * We will write a C macro, that overloads a given function to accept a matrix
 * and return a matrix whose elements are the element-wise application of the
 * given function on the input matrix.
 *
 * We will use this macro again and again later.
 *
 */

// generate element-wise functions with one argument:
// like sin, cos, tan, atan, etc
#define ELEMENTWISE_FN(name)                                        \
    asu::CMatrix name(const asu::CMatrix& m)                        \
    {                                                               \
            asu::CMatrix r(m.getnRows(), m.getnColumns());          \
            for (size_t i = 0; i < m.getn(); i++)                   \
                    r(i) = name(m(i));                              \
            return r;                                               \
    }

// generate all the 36 trigonometric functions: sin, asin, cosh, etc
#define TRIG_GENERATE(name)                                         \
    ELEMENTWISE_FN(name)                                            \
    ELEMENTWISE_FN(a##name)                                         \
    ELEMENTWISE_FN(name##d)                                         \
    ELEMENTWISE_FN(a##name##d)                                      \
    ELEMENTWISE_FN(name##h)                                         \
    ELEMENTWISE_FN(a##name##h)

TRIG_GENERATE(sin)  // sin, sind, asin, asind, sinh, asinh (for CMatrix)
TRIG_GENERATE(cos)
TRIG_GENERATE(tan)
TRIG_GENERATE(cot)
TRIG_GENERATE(sec)
TRIG_GENERATE(csc)

/*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * Section 4: Radians-degrees Converters
 * -------------------------------------
 *
 * MATLAB defines two functions to convert between radians and degrees.
 * We first define the `double` functions, then generate the overloaded matrix
 * version using our earlier macro.
 *
 */

// rad-deg conversions
double rad2deg(double r) { return r * 180 / M_PI; }
double deg2rad(double d) { return d * M_PI / 180; }

ELEMENTWISE_FN(rad2deg)
ELEMENTWISE_FN(deg2rad)

/*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * Section 5: The two-argument functions
 * -------------------------------------
 *
 * `atan2`, `atan2d`, and `hypot` take two arguments. We write an element-wise
 * function generator like the earlier, but make the generated functions accept
 * two arguments.
 *
 * As we don't have `atan2d` defined on `double`s yet, we need to define it
 * before we generate the corresponding element-wise function.
 *
 */

// generate element-wise functions with two arguments:
// like atan2, hypot
#define ELEMENTWISE_FN2(name)                                       \
    asu::CMatrix name(const asu::CMatrix& a, const asu::CMatrix& b) \
    {                                                               \
            if (a.getnRows() != b.getnRows()                        \
                || a.getnColumns() != b.getnColumns())              \
                    throw std::invalid_argument                     \
                        ("Invalid matrix dimensions"                \
                         " in " #name "()");                        \
            asu::CMatrix r(a.getnRows(), a.getnColumns());          \
            for (size_t i = 0; i < a.getn(); i++)                   \
                    r(i) = name(a(i), b(i));                        \
            return r;                                               \
    }                                                               \

double atan2d(double x, double y) { return atan2(x, y) * 180 / M_PI; }

ELEMENTWISE_FN2(atan2)
ELEMENTWISE_FN2(atan2d)
ELEMENTWISE_FN2(hypot)

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Part 2: Exponents and Logarithms functions
 * ==========================================
 *
 * Section 0: Introduction
 * -----------------------
 *
 * We'll implement the following functions:
 *   exp     log     log10   log2    log1p   sqrt    power
 *
 * Interestingly, all of them are available in C++ standard library, except
 * `power`, which is called `pow`.
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * Section 1: Implementation
 * -------------------------
 *
 * For more symmetric code, we implement the element-wise `pow` first, then
 * write two `power` functions that returns the result of `pow`.
 * An optimizing complier should inline these `power` functions, among others,
 * so it should not cause a performance issue.
 *
 */

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

asu::CMatrix power_modified_elementwise(const asu::CMatrix& n,double m){
 asu::CMatrix r(n.getnRows(), n.getnColumns());
 for(unsigned int i=0;i<n.getnRows();i++)
 {
 for(unsigned int j=0;j<n.getnColumns();j++){
 r(i,j)=pow(n(i,j),m);
 }
 }
 return r;


}
asu::CMatrix power_modified(const asu::CMatrix& n,double m)
{
asu::CMatrix r=n;
for(int i=0;i<m-1;i++){
r.CopyMatrix(mul(r,n));
}
return r;
}

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Part 3: Cleaning
 * ================
 *
 * Section 0: Introduction
 * -----------------------
 *
 * `#include`ing a file, literally copies its contents and pastes them in the
 * place of the `#include` statement. Thus, macros should be `#undef`ined after
 * their use, not to cause any unindented replacement, causing bugs and pain.
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * Section 1: Undefing macros
 * --------------------------
 *
 * We `#undef` the macros used in this header file, not to clutter the global
 * namespace. This also may prevent some bugs and a lot of pain.
 *
 */

#undef EXTRA_TRIG_FN
#undef TRIG_DECIMAL_GEN
#undef ELEMENTWISE_FN
#undef TRIG_GENERATE
#undef ELEMENTWISE_FN2

/*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * Thank you for reading so far! We really appreciate that you take the time
 * to read this all.
 *
 * If you're interested in this commenting style, it's just an attempt at
 * Literate Programming: https://en.wikipedia.org/wiki/Literate_programming.
 *
 */

