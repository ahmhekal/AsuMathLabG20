#include "matrix.h"
#include <cstdlib>	// atof, rand
#include <string>	// string
#include <stdexcept>	// invalid_argument and other exceptions
#include <cstdarg>	// va_list, etc
#include <string.h>	// strcpy, strtok_r
#include <math.h>	// NAN, isnan

namespace asu {

void CMatrix::reset()
{
	if (values)
		delete[] values;
	nRows = nColumns = 0;
	values = 0;
}

CMatrix CMatrix::operator=(const CMatrix& m)
{
	CopyMatrix(m);
	return *this;
}

CMatrix CMatrix::operator=(double d)
{
	CopyMatrix(d);
	return *this;
}

CMatrix CMatrix::operator=(const char* s)
{
	CopyMatrix(s);
	return *this;
}

CMatrix::CMatrix()
{
	nRows = nColumns = 0;
	values = 0;
}

CMatrix::~CMatrix() { reset(); }

CMatrix::CMatrix(size_t nRows, size_t nColumns, int initialization,
		 double initializationValue)
{
	this->nRows = nRows;
	this->nColumns = nColumns;
	if ((nRows * nColumns) == 0) {
		values = 0;
		return;
	}

	values = new double[nRows * nColumns];
	for (size_t i = 0; i < nRows * nColumns; ++i) {
		switch (initialization) {
		case MI_ZEROS:
			(*this)(i) = 0;
			break;
		case MI_VALUE:
			(*this)(i) = initializationValue;
			break;
		case MI_ONES:
			(*this)(i) = 1;
			break;
		case MI_EYE:
			(*this)(i) = (i/nColumns == i%nColumns)? 1 : 0;
			break;
		case MI_RAND:
			(*this)(i) = (rand() % 1000000) / 1000000.0;
			break;
		}
	}
}

CMatrix::CMatrix(size_t nRows, size_t nColumns, double first, ...)
{
	this->nRows = nRows;
	this->nColumns = nColumns;
	if ((nRows * nColumns) == 0) {
		values = 0;
		return;
	}

	values = new double[nRows * nColumns];
	va_list va;
	va_start(va, first);
	for (size_t i = 0; i < nRows * nColumns; ++i) {
		(*this)(i) = (i == 0)
			     ? first
			     : va_arg(va, double);
	}
	va_end(va);
}

CMatrix::CMatrix(const CMatrix& m)
{
	nRows = nColumns = 0;
	values = 0;
	CopyMatrix(m);
}

void CMatrix::addColumn(const CMatrix& m)
{
	CMatrix n(std::max(nRows, m.nRows), nColumns + m.nColumns);
	n.setSubMatrix(0, 0, *this);
	n.setSubMatrix(0, nColumns, m);
	*this = n;
}

void CMatrix::addRow(const CMatrix& m)
{
	CMatrix n(nRows + m.nRows, std::max(nColumns, m.nColumns));
	n.setSubMatrix(0, 0, *this);
	n.setSubMatrix(nRows, 0, m);
	*this = n;
}

CMatrix CMatrix::getInverse() const
{
	double det = getDeterminant();
	if (det == 0 || fabs(det) < 1e-5)
		throw std::invalid_argument
		    ("Inverting a noninvertible martix in CMatrix::getInverse()");
	det = 1.0 / det;
	CMatrix r(nRows, nRows);
	for (size_t i = 0; i < nRows; ++i)
		for (size_t j = 0; j < nRows; ++j) {
			int sign = (((i + j) % 2 == 0) ? 1 : -1);
			r(j,i) = sign * getCofactor(i,j).getDeterminant();
		}
	return mul(r, det);
}

void CMatrix::setSubMatrix(size_t r, size_t c, const CMatrix& m)
{
	if ((r + m.nRows) > nRows || (c + m.nColumns) > nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::setSubMatrix()");
	for (size_t i = 0; i < m.nRows; ++i)
		for (size_t j = 0; j < m.nColumns; ++j)
			(*this)(r + i, c + j) = m(i, j);

}

CMatrix CMatrix::getSubMatrix(size_t r, size_t c, size_t nr, size_t nc) const
{
	if ((r + nr) > nRows || (c + nc) > nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::getSubMatrix()");
	CMatrix m(nr, nc);
	for (size_t i = 0; i < m.nRows; ++i)
		for (size_t j = 0; j < m.nColumns; ++j)
			m(i, j) = (*this)(r + i, c + j);
	return m;
}

CMatrix CMatrix::getCofactor(size_t r, size_t c) const
{
	if (nRows <= 1 && nColumns <= 1)  // wat?! shouldn't be `||`?
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::getCofactor()");
	CMatrix m(nRows - 1, nColumns - 1);
	for (size_t i = 0; i < m.nRows; ++i)
		for (size_t j = 0; j < m.nColumns; ++j) {
			size_t sR = (i < r) ? i : i + 1;
			size_t sC = (j < c) ? j : j + 1;
			m(i, j) = (*this)(sR, sC);
		}
	return m;
}

static CMatrix LUPFactorize(const CMatrix& m, bool& negdet)
{
	if (m.getnRows() != m.getnColumns())
		throw std::invalid_argument
		    ("Non-square matrix won't be factorized");
	size_t n = m.getnRows();
	// pivoting
	CMatrix pa = m;
	negdet = false;
	for (size_t k = 0; k < n; ++k) {
		double maxvalue = 0;
		size_t maxindex = 0;
		// determine the maxvalue in the col, and its row index
		for (size_t i = k; i < n; ++i)
			if (fabs(pa(i, k) > maxvalue)) {
				maxvalue = pa(i, k);
				maxindex = i;
			}
		if (maxvalue == 0) return CMatrix();  // non-invertible
		if (maxindex != k) {  // if we need swapping rows
			negdet = !negdet;
			for (size_t j = 0; j < n; ++j) {
				// swap pa(k, j) with pa(maxindex, j)
				double tmp = pa(k, j);
				pa(k, j) = pa(maxindex, j);
				pa(maxindex, j) = tmp;
			}
		}
	}
	// factorizing: decompose pa as lu
	for (size_t k = 0; k < n - 1; ++k)
		for (size_t i = k + 1; i < n; ++i) {
			double m = pa(i, k)/pa(k, k);
			pa(i, k) = m;
			for (size_t j = 0; j < n; ++j)
				pa(i, j) -= m * pa(k, j);
		}
	return pa;
}

double CMatrix::getDeterminant() const
{
	if (nRows != nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::getDeterminant()");
	if (nRows == 1 && nColumns == 1)
		return (*this)(0, 0);
	bool negdet;
	double det = 1;
	CMatrix lu = LUPFactorize(*this, negdet);
	if (lu == CMatrix())
		return 0;
	for (size_t k = 0; k < nRows; ++k)
		det *= lu(k, k);
	if (negdet)
		det = -det;
	return det;
}

CMatrix CMatrix::getTranspose() const
{
	CMatrix r(nColumns, nRows);
	for (size_t i = 0; i < nRows; ++i)
		for (size_t j = 0; j < nColumns; ++j)
			r(j, i) = (*this)(i, j);
	return r;
}

std::istream& operator>>(std::istream& is, CMatrix& m)   //need to be edited
{
	std::string s;
	std::getline(is, s, ']');
	s += "]";
	CMatrix readMatrix(s.c_str());
	m = readMatrix;
	return is;
}


std::ostream& operator<<(std::ostream& os, const CMatrix& m)
{
	for (size_t i = 0; i < m.getnRows(); ++i) {
		for (size_t j = 0; j < m.getnColumns(); ++j) {
			os << m(i,j);
			if (j != m.getnColumns() - 1)
				os << "\t";
		}
		os << "\n";
	}
	return os;
}

size_t CMatrix::getnColumns() const { return nColumns; }

size_t CMatrix::getnRows() const { return nRows; }

size_t CMatrix::getn() const { return nColumns * nRows; }

CMatrix::CMatrix(const char* s)   //need to be edited
{
	nRows = nColumns = 0;
	values = 0;
	CopyMatrix(s);
}

CMatrix::CMatrix(double d)
{
	nRows = nColumns = 0;
	values = 0;
	CopyMatrix(d);
}

void CMatrix::CopyMatrix(const CMatrix& m)
{
	reset();
	this->nRows = m.nRows;
	this->nColumns = m.nColumns;
	if ((nRows * nColumns) == 0) {
		values = 0;
		return;
	}
	values = new double[nRows * nColumns];
	for (size_t i = 0; i < nRows * nColumns; ++i)
		(*this)(i) = m(i);
}


void CMatrix::CopyMatrix(const char* s)   //need to be edited
{
	reset();
	char* buffer = strdup(s);
	char* lineContext;
	const char* lineSeparators = ";\r\n";
	char* line = strtok_r(buffer, lineSeparators, &lineContext);
	while (line) {
		CMatrix row;
		char* context;
		const char* separators = " []";
		char* token = strtok_r(line, separators, &context);
		while (token) {
			CMatrix item(atof(token));
			row.addColumn(item);
			token = strtok_r(0, separators, &context);
		}
		if (row.nColumns > 0
		    && (row.nColumns == nColumns || nRows == 0))
			addRow(row);
		line = strtok_r(0, lineSeparators, &lineContext);
	}
	delete[] buffer;
}

void CMatrix::CopyMatrix(double d)
{
	reset();
	this->nRows = 1;
	this->nColumns = 1;
	values = new double[1];
	(*this)(0) = d;
}

double& CMatrix::operator[](size_t i)
{ return values[i]; }

double CMatrix::operator[](size_t i) const
{ return values[i]; }

double CMatrix::operator()(size_t i) const
{ return values[i]; }

double& CMatrix::operator()(size_t i)
{ return values[i]; }

double CMatrix::operator()(size_t i, size_t j) const
{ return values[j + i * nColumns]; }

double& CMatrix::operator()(size_t i, size_t j)
{ return values[j + i * nColumns]; }

bool operator==(const CMatrix& a, const CMatrix& b)
{
	if (a.getnRows() != b.getnRows())
		return false;
	if (a.getnColumns() != b.getnColumns())
		return false;
	for (size_t i = 0; i < a.getnRows() * a.getnColumns(); ++i)
		if (fabs(a[i] - b[i]) > 1e-5)
			return false;
	return true;
}

bool operator!=(const CMatrix& a, const CMatrix& b)
{ return !(a == b); }

// arithmatic functions and operators:
// first, the unique functions: mul, div
CMatrix mul(const CMatrix& a, const CMatrix& b)
{
	if (a.getnColumns() != b.getnRows())
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::mul()");
	CMatrix r(a.getnRows(), b.getnColumns(), CMatrix::MI_ZEROS);
	for (size_t i = 0; i < r.getnRows(); ++i)
		for (size_t j = 0; j < r.getnColumns(); ++j)
			for (size_t k = 0; k < a.getnColumns(); k++)
				r(i, j) += a(i, k) * b(k, j);
	return r;
}

CMatrix mul(const CMatrix& a, double b) { return amul(a, b); }
CMatrix mul(double a, const CMatrix& b) { return amul(a, b); }
CMatrix mul(double a, double b)         { return amul(a, b); }

CMatrix div(const CMatrix& a, const CMatrix& b)
{ return mul(a, b.getInverse()); }

CMatrix div(double a, const CMatrix& b)
{ return mul(a, b.getInverse()); }

CMatrix div(const CMatrix& a, double b) { return adiv(a, b); }
CMatrix div(double a, double b)         { return adiv(a, b); }

#define elementwise_fn(name, op)			\
CMatrix name(const CMatrix& a, const CMatrix& b)	\
{							\
	if (a.getnRows() != b.getnRows()		\
	    || a.getnColumns() != b.getnColumns())	\
		throw std::invalid_argument		\
		    ("Invalid matrix dimensions"	\
		     " in " #name "()");		\
	CMatrix r(a.getnRows(), a.getnColumns());	\
	for (size_t i = 0; i < a.getn(); i++)		\
		r(i) = a(i) op b(i);			\
	return r;					\
}							\
CMatrix name(const CMatrix& a, double b)		\
{							\
	CMatrix r(a.getnRows(), a.getnColumns());	\
	for (size_t i = 0; i < a.getn(); i++)		\
		r(i) = a(i) op b;			\
	return r;					\
}							\
CMatrix name(double a, const CMatrix& b)		\
{							\
	CMatrix r(b.getnRows(), b.getnColumns());	\
	for (size_t i = 0; i < b.getn(); i++)		\
		r(i) = a op b(i);			\
	return r;					\
}                                                       \
CMatrix name(double a, double b)                        \
{                                                       \
    CMatrix r(1,1);                                     \
    r(0) = a op b;                                      \
    return r;                                           \
}

elementwise_fn(add,  +);
elementwise_fn(sub,  -);
elementwise_fn(amul, *);
elementwise_fn(adiv, /);

#undef elementwise_fn

}; // namespace asu
