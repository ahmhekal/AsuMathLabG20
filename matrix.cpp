#include "matrix.h"
#include <cstdlib>	// atof, rand
#include <ctime>	// time, for seeding rand
#include <cstring>	// strtok_r
#include <stdexcept>	// invalid_argument and other exceptions
#include <cstdarg>	// va_list, etc
#include <string.h>	// strcpy, strtok_r
#include <math.h>	// NAN, isnan

void CMatrix::reset()
{
	if (values) {
		for (size_t i = 0; i < nRows; ++i)
			delete[] values[i];
		delete[] values;
	}
	nRows = nColumns = 0;
	values = NULL;
}

std::string CMatrix::getString() const // wtf
{
	std::string s;
	for (size_t i = 0; i < nRows; ++i) {
		for (size_t j = 0; j < nColumns; ++j) {
			//char buffer[50];
			//sprintf_s(buffer,50,"%g\t",(*this)(i, j));
			if ((*this)(i, j) == 0
			    || fabs((*this)(i, j) < 1e-15)
				std::cout << "0" << " ";
			else
				std::cout << (*this)(i, j) << " ";
		}
		//s+="\n";
		std::cout << "\n";
	}
	return s;
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

CMatrix CMatrix::operator=(const std::string s)
{
	CopyMatrix(s);
	return *this;
}

CMatrix::CMatrix()
{
	nRows = nColumns = 0;
	values = NULL;
}

CMatrix::~CMatrix()
{
	reset();
}

CMatrix::CMatrix(size_t nRows, size_t nColumns, int initialization,
		 double initializationValue)
{
	this->nRows = nRows;
	this->nColumns = nColumns;
	if ((nRows * nColumns) == 0) {
		values = NULL;
		return;
	}

	values = new double*[nRows];
	for (size_t i = 0; i < nRows; ++i) {
		values[i] = new double[nColumns];
		for (size_t j = 0; j < nColumns; ++j) {
			switch (initialization) {
			case MI_ZEROS:
				(*this)(i, j) = 0;
				break;
			case MI_ONES:
				(*this)(i, j) = 1;
				break;
			case MI_EYE:
				(*this)(i, j) = (i == j) ? 1 : 0;
				break;
			case MI_RAND:
				(*this)(i, j) =
				    (rand() % 1000000) / 1000000.0;
				break;
			case MI_VALUE:
				(*this)(i, j) = initializationValue;
				break;
			}
		}

	}
}

CMatrix::CMatrix(size_t nRows, size_t nColumns, double first, ...)
{
	this->nRows = nRows;
	this->nColumns = nColumns;
	if ((nRows * nColumns) == 0) {
		values = NULL;
		return;
	}

	values = new double*[nRows];
	va_list va;
	va_start(va, first);
	for (size_t i = 0; i < nRows; ++i) {
		values[i] = new double[nColumns];
		for (size_t j = 0; j < nColumns; ++j) {
			(*this)(i, j) = (i == 0 && j == 0)
			               ? first
				       : va_arg(va, double);
		}
	}
	va_end(va);
}

CMatrix::CMatrix(const CMatrix& m)
{
	nRows = nColumns = 0;
	values = NULL;
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
	if (det == 0 || fabs(det) < 1e-15)
		throw std::invalid_argument
		    ("Inverting a noninvertible martix in CMatrix::getInverse()");
	det = 1.0 / det;
	CMatrix r(nRows, nRows);
	for (size_t i = 0; i < nRows; ++i)
		for (size_t j = 0; j < nRows; ++j) {
			int sign = (((i + j) % 2 == 0) ? 1 : -1);
			r(j,i) = sign * getCofactor(i,j).getDeterminant();
		}
	r *= det;
	return r;
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
			m(*this)(i, j) = (*this)(r + i, c + j);
	return m;
}

CMatrix CMatrix::getCofactor(size_t r, size_t c) const
{
	if (nRows <= 1 && nColumns <= 1)
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::getCofactor()");
	CMatrix m(nRows - 1, nColumns - 1);
	for (size_t i = 0; i < m.nRows; ++i)
		for (size_t j = 0; j < m.nColumns; ++j) {
			size_t sR = (i < r) ? i : i + 1;
			size_t sC = (j < c) ? j : j + 1;
			m(*this)(i, j) = (*this)(sR, sC);
		}
	return m;
}

double CMatrix::getDeterminant() const
{
	if (nRows != nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::getDeterminant()");
	if (nRows == 1 && nColumns == 1)
		return (*this)(0, 0);
	double value = 0.0, m = 1.0;
	for (size_t i = 0; i < nRows; ++i) {
		double minor = getCofactor(0, i).getDeterminant();
		value += m * (*this)(0, i) * minor;
		m *= -1.0;
	}
	return value;
}

void CMatrix::getTranspose(CMatrix& r) const
{
	r = CMatrix(nColumns, nRows);
	for (size_t i = 0; i < nRows; ++i)
		for (size_t j = 0; j < nColumns; ++j)
			r(j, i) = (*this)(i, j);
}

std::istream& operator>>(std::istream& is, CMatrix& m)   //need to be edited
{
	std::string s;
	std::getline(is, s, ']');
	s += "]";
	CMatrix readMatrix(s);
	m = readMatrix;
	return is;
}


std::ostream& operator<<(std::ostream& os, const CMatrix& m)
{
	//os << m.getString();
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

size_t CMatrix::getnColumns() const
{
	return this->nColumns;
}

size_t CMatrix::getnRows() const
{
	return this->nRows;
}

size_t CMatrix::getn() const
{
	return (this->nColumns) * (this->nRows);
}

CMatrix::CMatrix(std::string s)   //need to be edited
{
	nRows = nColumns = 0;
	values = NULL;
	CopyMatrix(s);
}

CMatrix::CMatrix(double d)
{
	nRows = nColumns = 0;
	values = NULL;
	CopyMatrix(d);
}

void CMatrix::CopyMatrix(const CMatrix& m)
{
	reset();
	this->nRows = m.nRows;
	this->nColumns = m.nColumns;
	if ((nRows * nColumns) == 0) {
		values = NULL;
		return;
	}
	values = new double*[nRows];
	for (size_t i = 0; i < nRows; ++i) {
		values[i] = new double[nColumns];
		for (size_t j = 0; j < nColumns; ++j) {
			(*this)(i, j) = m(i, j);
		}
	}
}


void CMatrix::CopyMatrix(std::string s)   //need to be edited
{
	reset();

	char* buffer = new char[s.length() + 1];
	strcpy(buffer, s.c_str());
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
			token = strtok_r(NULL, separators, &context);
		}
		if (row.nColumns > 0
		    && (row.nColumns == nColumns || nRows == 0))
			addRow(row);
		line = strtok_r(NULL, lineSeparators, &lineContext);
	}
	delete[] buffer;
}

void CMatrix::CopyMatrix(double d)
{
	reset();
	this->nRows = 1;
	this->nColumns = 1;
	values = new double*[1];
	values[0] = new double[1];
	(*this)(0,0) = d;
}

// accessing and boolean operators: [], (), ==, !=
double& CMatrix::operator[](size_t i)
{
	return (*this)(i / nColumns, i % nColumns);
}

double CMatrix::operator[](size_t i) const
{
	return (*this)(i / nColumns, i % nColumns);
}

double CMatrix::operator()(size_t i) const
{
	return (*this)(i / nColumns, i % nColumns);
}

double& CMatrix::operator()(size_t i)
{
	return (*this)(i / nColumns, i % nColumns);
}

double CMatrix::operator()(size_t r, size_t c) const
{
	return (*this)(r, c);
}

double& CMatrix::operator()(size_t r, size_t c)
{
	return (*this)(r, c);
}

bool operator==(const CMatrix& a, const CMatrix& b)
{
	if (a.getnRows() != b.getnRows())
		return false;
	if (a.getnColumns() != b.getnColumns())
		return false;
	for (size_t i = 0; i < a.getnRows() * a.getnColumns(); ++i)
		if (a[i] != b[i])
			return false;
	return true;
}

bool operator!=(const CMatrix& a, const CMatrix& b)
{
	return !(a == b);
}

// arithmatic functions and operators:
// first, the unique functions: mul, div
CMatrix& CMatrix::mul(const CMatrix& m)
{
	if (nColumns != m.nRows)
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::mul()");
	CMatrix r(nRows, m.nColumns);
	for (size_t i = 0; i < r.nRows; ++i)
		for (size_t j = 0; j < r.nColumns; ++j) {
			r(i, j) = 0.0;
			for (size_t k = 0; k < nColumns; k++)
				r(i, j) += (*this)(i, k) * m(k, j);
		}
	CopyMatrix(r);
	return *this;
}

CMatrix& CMatrix::div(const CMatrix& m)
{
	CMatrix denom(m.getInverse());
	mul(denom);
	return *this;
}

// second, the element-wise functions: add, sub, amul, adiv
#define elementwise_fn(name, op)                         \
CMatrix& CMatrix::name(const CMatrix& m)                 \
{                                                        \
	if (nRows != m.nRows || nColumns != m.nColumns)  \
		throw std::invalid_argument              \
		    ("Invalid matrix dimensions"         \
		     " in CMatrix::" #name "()");        \
	for (size_t i = 0; i < nRows * nColumns; ++i)    \
		(*this)[i] op m[i];                      \
	return *this;                                    \
}
elementwise_fn(add,  +=);
elementwise_fn(sub,  -=);
elementwise_fn(amul, *=);
elementwise_fn(adiv, /=);
#undef elementwise_fn

// third, the operators +=, -=, *=, /=
// with (CMatrix, CMatrix) and with (CMatrix, double)
#define def_op_eq(op, fn)                                \
CMatrix CMatrix::operator op(const CMatrix& m)           \
{                                                        \
	return fn(m);                                    \
}                                                        \
CMatrix CMatrix::operator op(double d)                   \
{                                                        \
	for (size_t i = 0; i < nRows * nColumns; ++i)    \
		(*this)[i] op d;                         \
	return *this;                                    \
}
def_op_eq(+=, add);
def_op_eq(-=, sub);
def_op_eq(*=, mul);
def_op_eq(/=, div);
#undef def_op_eq

// fourth, defining all the remaining operators (+,-,*,/)
// with (CMatrix,CMatrix), (CMatrix,double), (double,CMatrix)
#define defop(op, A, B, c, statements)                    \
CMatrix operator op(A,B)                                  \
{                                                         \
	CMatrix r(c);  statements;  return r;             \
}
defop(+, const CMatrix& a, const CMatrix& b, a,              r += b);
defop(+, const CMatrix& a, double b,         a,              r += b);
defop(+, double a,         const CMatrix& b, b,              r += a);

defop(-, const CMatrix& a, const CMatrix& b, a,              r -= b);
defop(-, const CMatrix& a, double b,         a,              r -= b);
defop(-, double a,         const CMatrix& b, b,              r -= a; r *= -1);

defop(*, const CMatrix& a, const CMatrix& b, a,              r *= b);
defop(*, const CMatrix& a, double b,         a,              r *= b);
defop(*, double a,         const CMatrix& b, b,              r *= a);

defop(/, const CMatrix& a, const CMatrix& b, a,              r /= b);
defop(/, const CMatrix& a, double b,         a,              r /= b);
defop(/, double a,         const CMatrix& b, b.getInverse(), r *= a);
#undef defop

// finally, the unary sign operators
CMatrix CMatrix::operator-() const
{
	CMatrix result = *this;
	for (size_t i = 0; i < nRows; ++i)
		for (size_t j = 0; j < nColumns; ++j)
			result(i, j) = -(*this)(i, j);
	return result;
}

CMatrix CMatrix::operator+() const
{
	return *this;
}
