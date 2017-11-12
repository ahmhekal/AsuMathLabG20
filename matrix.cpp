#include "matrix.h"
#include <cstdlib>	// atof, rand
#include <ctime>	// time, for seeding rand
#include <cstring>	// strtok_r
#include <stdexcept>	// invalid_argument and other exceptions
#include <cstdarg>	// va_list, etc
#include <string.h>	// strcpy, strtok_r
#include <math.h>	// NAN, isnan

CMatrix CMatrix::operator-()
{
	CMatrix result = *this;
	for (int i = 0; i < nRows; ++i)
		for (int j = 0; j < nColumns; ++j)
			result.values[i][j] = -values[i][j];
	return result;
}

CMatrix CMatrix::operator+()
{
	return *this;
}

void CMatrix::reset()
{
	if (values) {
		for (int i = 0; i < nRows; ++i)
			delete[] values[i];
		delete[] values;
	}
	nRows = nColumns = 0;
	values = NULL;
}

std::string CMatrix::getString() // wtf
{
	std::string s;
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nColumns; ++j) {
			//char buffer[50];
			//sprintf_s(buffer,50,"%g\t",values[i][j]);
			if (values[i][j] == 0
			    || fabs(values[i][j]) < 1e-15)
				std::cout << "0" << " ";
			else
				std::cout << values[i][j] << " ";
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

void CMatrix::add(CMatrix& m)
{
	if (nRows != m.nRows || nColumns != m.nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimension in CMatrix::add()");
	for (int i = 0; i < nRows; ++i)
		for (int j = 0; j < nColumns; ++j)
			values[i][j] += m.values[i][j];
}

void CMatrix::operator+=(CMatrix& m)
{
	add(m);
}

void CMatrix::operator+=(double d)
{
	CMatrix addend(nRows, nColumns, MI_VALUE, d);
	add(addend);
}

CMatrix CMatrix::operator+(CMatrix& m)
{
	CMatrix r = *this;
	r += m;
	return r;
}

CMatrix CMatrix::operator+(double d)
{
	CMatrix r = *this;
	r += d;
	return r;
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

CMatrix::CMatrix(int nRows, int nColumns, int initialization,
		 double initializationValue)
{
	this->nRows = nRows;
	this->nColumns = nColumns;
	if ((nRows * nColumns) == 0) {
		values = NULL;
		return;
	}

	values = new double*[nRows];
	for (int i = 0; i < nRows; ++i) {
		values[i] = new double[nColumns];
		for (int j = 0; j < nColumns; ++j) {
			switch (initialization) {
			case MI_ZEROS:
				values[i][j] = 0;
				break;
			case MI_ONES:
				values[i][j] = 1;
				break;
			case MI_EYE:
				values[i][j] = (i == j) ? 1 : 0;
				break;
			case MI_RAND:
				values[i][j] =
				    (rand() % 1000000) / 1000000.0;
				break;
			case MI_VALUE:
				values[i][j] = initializationValue;
				break;
			}
		}

	}
}

CMatrix::CMatrix(int nRows, int nColumns, double first, ...)
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
	for (int i = 0; i < nRows; ++i) {
		values[i] = new double[nColumns];
		for (int j = 0; j < nColumns; ++j) {
			values[i][j] = (i == 0 && j == 0)
			               ? first
				       : va_arg(va, double);
		}
	}
	va_end(va);
}

CMatrix::CMatrix(CMatrix& m)
{
	nRows = nColumns = 0;
	values = NULL;
	CopyMatrix(m);
}

void CMatrix::addColumn(CMatrix& m)
{
	CMatrix n(std::max(nRows, m.nRows), nColumns + m.nColumns);
	n.setSubMatrix(0, 0, *this);
	n.setSubMatrix(0, nColumns, m);
	*this = n;
}

void CMatrix::addRow(CMatrix& m)
{
	CMatrix n(nRows + m.nRows, std::max(nColumns, m.nColumns));
	n.setSubMatrix(0, 0, *this);
	n.setSubMatrix(nRows, 0, m);
	*this = n;
}

void CMatrix::getInverse(CMatrix& t)
{
	double det = getDeterminant();
	if (det == 0 || fabs(det) < 1e-15)
		throw std::invalid_argument
		    ("Inverting a noninvertible martix in CMatrix::getInverse()");
	det = 1.0 / det;
	CMatrix r(nRows, nRows);
	for (int i = 0; i < nRows; ++i)
		for (int j = 0; j < nRows; ++j) {
			double minor = getCofactor(i,j).getDeterminant();
			int sign = (((i + j) % 2 == 0) ? 1 : -1);
			r.values[j][i] = minor * sign;
		}
	r *= det;
	t = r;
}

CMatrix CMatrix::div(CMatrix& m)
{
	CMatrix d(m);
	CMatrix This = *this;
	m.getInverse(d);
	This.mul(d);
	return This;
}

CMatrix CMatrix::operator/(CMatrix& m)
{
	CMatrix d(m);
	CMatrix This = *this;
	m.getInverse(d);
	This.mul(d);
	return This;
}

CMatrix CMatrix::operator/(double d)
{
	if (d == 0 || fabs(d) < 1e-15)
		throw std::invalid_argument("Division by zero");
	CMatrix result = *this;
	for (int i = 0; i < nRows; ++i)
		for (int j = 0; j < nColumns; ++j)
			result.values[i][j] /= d;
	return result;
}

void CMatrix::setSubMatrix(int r, int c, CMatrix& m)
{
	if ((r + m.nRows) > nRows || (c + m.nColumns) > nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimension in CMatrix::setSubMatrix()");
	for (int i = 0; i < m.nRows; ++i)
		for (int j = 0; j < m.nColumns; ++j)
			values[r + i][c + j] = m.values[i][j];
}

CMatrix CMatrix::getSubMatrix(int r, int c, int nr, int nc)
{
	if ((r + nr) > nRows || (c + nc) > nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimension in CMatrix::getSubMatrix()");
	CMatrix m(nr, nc);
	for (int i = 0; i < m.nRows; ++i)
		for (int j = 0; j < m.nColumns; ++j)
			m.values[i][j] = values[r + i][c + j];
	return m;
}

CMatrix CMatrix::getCofactor(int r, int c)
{
	if (nRows <= 1 && nColumns <= 1)
		throw std::invalid_argument
		    ("Invalid matrix dimension in CMatrix::getCofactor()");
	CMatrix m(nRows - 1, nColumns - 1);
	for (int i = 0; i < m.nRows; ++i)
		for (int j = 0; j < m.nColumns; ++j) {
			int sR = (i < r) ? i : i + 1;
			int sC = (j < c) ? j : j + 1;
			m.values[i][j] = values[sR][sC];
		}
	return m;
}

double CMatrix::getDeterminant()
{
	if (nRows != nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimension in CMatrix::getDeterminant()");
	if (nRows == 1 && nColumns == 1)
		return values[0][0];
	double value = 0.0, m = 1.0;
	for (int i = 0; i < nRows; ++i) {
		double minor = getCofactor(0, i).getDeterminant();
		value += m * values[0][i] * minor;
		m *= -1.0;
	}
	return value;
}

void CMatrix::getTranspose(CMatrix& r)
{
	r = CMatrix(nColumns, nRows);
	for (int i = 0; i < nRows; ++i)
		for (int j = 0; j < nColumns; ++j)
			r.values[j][i] = values[i][j];
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


std::ostream& operator<<(std::ostream& os, CMatrix& m)
{
	os << m.getString();
	return os;
}

int CMatrix::getnColumns() const
{
	return this->nColumns;
}

int CMatrix::getnRows() const
{
	return this->nRows;
}

int CMatrix::getn() const
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
	for (int i = 0; i < nRows; ++i) {
		values[i] = new double[nColumns];
		for (int j = 0; j < nColumns; ++j) {
			values[i][j] = m.values[i][j];
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
	values[0][0] = d;
}


void CMatrix::mul(CMatrix& m)
{
	if (nColumns != m.nRows)
		throw std::invalid_argument
		    ("Invalid matrix dimension in CMatrix::mul()");
	CMatrix r(nRows, m.nColumns);
	for (int i = 0; i < r.nRows; ++i)
		for (int j = 0; j < r.nColumns; ++j) {
			r.values[i][j] = 0.0;
			for (int k = 0; k < nColumns; k++)
				r.values[i][j] +=
				    values[i][k] * m.values[k][j];
		}
	CopyMatrix(r);
}

void CMatrix::operator*=(CMatrix& m)
{
	mul(m);
}

void CMatrix::operator*=(double d)
{
	for (int i = 0; i < nRows; ++i)
		for (int j = 0; j < nColumns; ++j)
			values[i][j] *= d;
}

CMatrix CMatrix::operator*(CMatrix& m)
{
	CMatrix r = *this;
	r *= m;
	return r;
}

CMatrix CMatrix::operator*(double d)
{
	CMatrix r = *this;
	r *= d;
	return r;
}

void CMatrix::sub(CMatrix& m)
{
	if (nRows != m.nRows || nColumns != m.nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimension in CMatrix::sub()");
	for (int i = 0; i < nRows; ++i)
		for (int j = 0; j < nColumns; ++j)
			values[i][j] -= m.values[i][j];
}

void CMatrix::operator-=(CMatrix& m)
{
	sub(m);
}

void CMatrix::operator-=(double d)
{
	CMatrix subtrahend(nRows, nColumns, MI_VALUE, d);
	sub(subtrahend);
}

CMatrix CMatrix::operator-(CMatrix& m)
{
	CMatrix r = *this;
	r -= m;
	return r;
}

CMatrix CMatrix::operator-(double d)
{
	CMatrix r = *this;
	r -= d;
	return r;
}

CMatrix operator+(double d, CMatrix& m)
{
	CMatrix result(m);
	result += d;
	return result;
}

CMatrix operator-(double d, CMatrix& m)
{
	CMatrix result(m);
	result *= -1;
	result += d;
	return result;
}

CMatrix operator*(double d, CMatrix& m)
{
	CMatrix result(m);
	result *= d;
	return result;
}

CMatrix operator/(double d, CMatrix& m)
{
	CMatrix result;
	m.getInverse(result);
	result *= d;
	return result;
}

// element-wise disivison, './'
CMatrix adiv(const CMatrix& a, const CMatrix& b)
{
	if (a.getnRows() != b.getnRows()
	    || a.getnColumns() != b.getnColumns())
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::adiv()");
	CMatrix r(a.getnRows(), a.getnColumns());
	for (int i = 0; i < a.getnRows(); ++i)
		for (int j = 0; j < a.getnColumns(); ++j)
			r(i, j) = a(i, j) / b(i, j);
	return r;
}


double& CMatrix::operator[](int i)
{
	return values[i / nColumns][i % nColumns];
}
double& CMatrix::operator()(int i)
{
	return values[i / nColumns][i % nColumns];
}
double CMatrix::operator()(int r, int c) const
{
	return values[r][c];
}
double& CMatrix::operator()(int r, int c)
{
	return values[r][c];
}
