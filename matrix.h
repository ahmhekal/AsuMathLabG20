#pragma once
#include <string>	// string
#include <iostream>	// istream, ostream

class CMatrix {
private:
	size_t nRows, nColumns;
	double** values;
public:
	CMatrix();
	~CMatrix();
	enum MI { MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE };
	CMatrix(size_t nRows, size_t nColumns,
	        int initialization = MI_ZEROS,
	        double initializationValue = 0.0);
	CMatrix(size_t nRows, size_t nColumns, double first, ...);
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
	CMatrix& add(const CMatrix& m);
	CMatrix operator+=(const CMatrix& m);
	CMatrix operator+=(double d);
	CMatrix& sub(const CMatrix& m);
	CMatrix operator-=(const CMatrix& m);
	CMatrix operator-=(double d);
	CMatrix& mul(const CMatrix& m);
	CMatrix operator*=(const CMatrix& m);
	CMatrix operator*=(double d);
	CMatrix& div(const CMatrix& m);
	CMatrix operator/=(const CMatrix& m);
	CMatrix operator/=(double d);
	CMatrix& adiv(const CMatrix& b);
	CMatrix& amul(const CMatrix& b);
	CMatrix operator-() const;
	CMatrix operator+() const;
	void setSubMatrix(size_t iR, size_t iC, const CMatrix& m);
	CMatrix getSubMatrix(size_t r, size_t c, size_t nr, size_t nc) const;
	CMatrix getCofactor(size_t r, size_t c) const;
	void addColumn(const CMatrix& m);
	void addRow(const CMatrix& m);
	double& operator[](size_t i);
	double operator[](size_t i) const;
	double operator()(size_t i) const;
	double& operator()(size_t i);
	double operator()(size_t r, size_t c) const;
	double& operator()(size_t r, size_t c);
	size_t getn() const;
	size_t getnRows() const;
	size_t getnColumns() const;
	double getDeterminant() const;
	void getTranspose(CMatrix& r) const;
	CMatrix getInverse() const;
};

CMatrix operator+(const CMatrix& a, const CMatrix& b);
CMatrix operator+(const CMatrix& m, double d);
CMatrix operator+(double d,         const CMatrix& m);
CMatrix operator-(const CMatrix& a, const CMatrix& b);
CMatrix operator-(const CMatrix& m, double d);
CMatrix operator-(double d,         const CMatrix& m);
CMatrix operator*(const CMatrix& a, const CMatrix& b);
CMatrix operator*(const CMatrix& m, double d);
CMatrix operator*(double d,         const CMatrix& m);
CMatrix operator/(const CMatrix& a, const CMatrix& b);
CMatrix operator/(const CMatrix& m, double d);
CMatrix operator/(double d,         const CMatrix& m);

bool operator==(const CMatrix& a, const CMatrix& b);
std::istream& operator>>(std::istream& is, CMatrix& C);
std::ostream& operator<<(std::ostream& os, const CMatrix& C);
// element-wise disivison, './'
// the following functions are identical to operator/()
//CMatrix adiv(const CMatrix& a, double d); 
//CMatrix adiv(double d, const CMatrix& b);
//CMatrix adiv(double d, double e);
