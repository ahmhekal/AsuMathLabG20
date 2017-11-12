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
	CMatrix(CMatrix& m);
	CMatrix(double d);
	CMatrix(std::string s);
	void CopyMatrix(const CMatrix& m);
	void CopyMatrix(double d);
	void CopyMatrix(const std::string s);
	void reset();
	std::string getString();
	CMatrix operator=(const CMatrix& m);
	CMatrix operator=(double d);
	CMatrix operator=(std::string s);
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
	CMatrix operator-();
	CMatrix operator+();
	friend std::istream& operator>>(std::istream& is, CMatrix& C);
	friend std::ostream& operator<<(std::ostream& os, CMatrix& C);
	void setSubMatrix(int iR, int iC, CMatrix& m);
	CMatrix getSubMatrix(int r, int c, int nr, int nc);
	CMatrix getCofactor(int r, int c);
	void addColumn(CMatrix& m);
	void addRow(CMatrix& m);
	double& operator[] (int i);
        double& operator() (int i);
	double operator() (int r, int c) const;
        double& operator() (int r, int c);
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
