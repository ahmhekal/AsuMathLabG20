#pragma once
#include <string>	// string
#include <iostream>	// istream, ostream

class CMatrix {
private:
	int nRows, nColumns;
	double** values;
public:
	CMatrix();
	~CMatrix();
	enum MI { MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE };
	CMatrix(int nRows, int nColumns,
	        int initialization = MI_ZEROS,
	        double initializationValue = 0.0);
	CMatrix(int nRows, int nColumns, double first, ...);
	CMatrix(const CMatrix& m);
	CMatrix(double d);
	CMatrix(std::string s);
	void CopyMatrix(const CMatrix& m);
	void CopyMatrix(double d);
	void CopyMatrix(const std::string s);
	void reset();
	std::string getString() const;
	CMatrix operator=(const CMatrix& m);
	CMatrix operator=(double d);
	CMatrix operator=(std::string s);
	void add(const CMatrix& m);
	void operator+=(const CMatrix& m);
	void operator+=(double d);
	CMatrix operator+(const CMatrix& m) const;
	CMatrix operator+(double d) const;
	void sub(const CMatrix& m);
	void operator-=(const CMatrix& m);
	void operator-=(double d);
	CMatrix operator-(const CMatrix& m) const;
	CMatrix operator-(double d) const;
	void mul(const CMatrix& m);
	void operator*=(const CMatrix& m);
	void operator*=(double d);
	CMatrix operator*(const CMatrix& m) const;
	CMatrix operator*(double d) const;
	CMatrix div(const CMatrix& m);
	void operator/=(const CMatrix& m);
	void operator/=(double d);
	CMatrix operator/(const CMatrix& m) const;
	CMatrix operator/(double d) const;
	CMatrix operator-() const;
	CMatrix operator+() const;
	void setSubMatrix(int iR, int iC, const CMatrix& m);
	CMatrix getSubMatrix(int r, int c, int nr, int nc) const;
	CMatrix getCofactor(int r, int c) const;
	void addColumn(const CMatrix& m);
	void addRow(const CMatrix& m);
	double& operator[] (int i);
	double operator[](int i) const;
        double& operator() (int i);
	double operator() (int r, int c) const;
        double& operator() (int r, int c);
	int getn() const;
	int getnRows() const;
	int getnColumns() const;
	double getDeterminant() const;
	void getTranspose(CMatrix& r) const;
	void getInverse(CMatrix& t) const;
};

CMatrix operator+(double d, const CMatrix& m);
CMatrix operator-(double d, const CMatrix& m);
CMatrix operator*(double d, const CMatrix& m);
CMatrix operator/(double d, const CMatrix& m);
bool operator==(const CMatrix& a, const CMatrix& b);
std::istream& operator>>(std::istream& is, CMatrix& C);
std::ostream& operator<<(std::ostream& os, const CMatrix& C);
// element-wise disivison, './'
CMatrix adiv(const CMatrix& a, const CMatrix& b);
// the following functions are identical to operator/()
//CMatrix adiv(const CMatrix& a, double d); 
//CMatrix adiv(double d, const CMatrix& b);
//CMatrix adiv(double d, double e);
