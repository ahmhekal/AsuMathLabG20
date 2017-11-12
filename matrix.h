#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cstdarg>
#include <string.h>
#include <istream>
#include <ostream>
#include <math.h>
using namespace std;

#pragma once

class CMatrix
{

int nRows, nColumns;
double** values;
public:
CMatrix();
~CMatrix();
enum MI{MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE};
CMatrix(int nRows, int nColumns, int initialization = MI_ZEROS, double
initializationValue = 0.0);
CMatrix(int nRows, int nColumns, double first, ...);
CMatrix(CMatrix& m);
CMatrix(double d);
CMatrix(string s);
void CopyMatrix(const CMatrix& m);
void CopyMatrix(double d);
void CopyMatrix(const string s);
void reset();
string getString();
CMatrix operator=(const CMatrix& m);
CMatrix operator=(double d);
CMatrix operator=(string s);
void add(CMatrix& m);
void operator+=(CMatrix& m);
void operator+=(double d);
CMatrix operator+(CMatrix& m);
CMatrix operator+(double d);
void sub(CMatrix& m);
void operator-=(CMatrix& m);
void operator-=(double d);
CMatrix operator-(CMatrix& m);
CMatrix operator-(double d);
void mul(CMatrix& m);
void operator*=(CMatrix& m);
void operator*=(double d);
CMatrix operator*(CMatrix& m);
CMatrix operator*(double d);
CMatrix div(CMatrix& m);
void operator/=(CMatrix& m);
void operator/=(double d);
CMatrix operator/(CMatrix& m);
CMatrix operator/(double d);
CMatrix operator++(); //Pre Increment
CMatrix operator++(int); //Post Increment, int is not used
CMatrix operator--(); //Pre Increment
CMatrix operator--(int); //Post Increment, int is not used
CMatrix operator-();
CMatrix operator+();
friend istream& operator >> (istream &is, CMatrix& C); //Stream
friend ostream& operator << (ostream &os, CMatrix& C); //Stream
void setSubMatrix(int iR, int iC, CMatrix& m);
CMatrix getSubMatrix(int r, int c, int nr, int nc);
CMatrix getCofactor(int r, int c);
void addColumn(CMatrix& m);
void addRow(CMatrix& m);
double& operator[](int i){return values[i/nColumns][i%nColumns];}
double& operator()(int i){return values[i/nColumns][i%nColumns];}
double operator()(int r, int c) const {return values[r][c];}
double& operator()(int r, int c){return values[r][c];}
int getn() const;
int getnRows() const;
int getnColumns() const;
double getDeterminant();
void getTranspose(CMatrix& r);
void getInverse(CMatrix& t);
};

CMatrix operator+(double d, CMatrix& m);
CMatrix operator-(double d, CMatrix& m);
CMatrix operator*(double d, CMatrix& m);
CMatrix operator/(double d, CMatrix& m);

// element-wise disivison, './'
CMatrix adiv(const CMatrix& a, const CMatrix& b);
// the following functions are identical to operator/()
//CMatrix adiv(const CMatrix& a, double d); 
//CMatrix adiv(double d, const CMatrix& b);
//CMatrix adiv(double d, double e);
