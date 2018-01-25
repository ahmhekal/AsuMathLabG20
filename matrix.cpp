#include "matrix.h"
#include <cstdlib>	// atof, rand
#include <string>	// string
#include <vector>	// vector
#include <algorithm>	// max_element
#include <iomanip>	// setw
#include <cstdio>	// snprintf
#include <stdexcept>	// invalid_argument and other exceptions
#include <cstdarg>	// va_list, etc
#include <string.h>	// strcpy, strtok_r
#include <math.h>	// NAN, isnan
#include <sys/ioctl.h>	// for ioctl to get the terminal width

namespace asu {

#define EPSILON 1e-5  // the precision of the floating numbers comparison

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
			get(i) = 0;
			break;
		case MI_VALUE:
			get(i) = initializationValue;
			break;
		case MI_ONES:
			get(i) = 1;
			break;
		case MI_EYE:
			// TODO: maybe you should loop directly
			// instead of using if inside for.
			get(i) = (i/nColumns == i%nColumns)? 1 : 0;
			break;
		case MI_RAND:
			get(i) = (rand() % 1000000) / 1000000.0;
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
		get(i) = (i == 0)
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
	if (nRows == 1 && nColumns ==1)
		return 1/get(0); // 1 over the 1st element
	double det = getDeterminant();
	if (det == 0 || fabs(det) < EPSILON)
            return CMatrix(nRows, nColumns, MI_VALUE, NAN);
	// MATLAB doesn't throw; it returns NaNs with a warning
		//throw std::invalid_argument
		    //("Inverting a noninvertible martix in CMatrix::getInverse()");
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
			get(r + i, c + j) = m(i, j);

}

CMatrix CMatrix::getSubMatrix(size_t r, size_t c, size_t nr, size_t nc) const
{
	if ((r + nr) > nRows || (c + nc) > nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::getSubMatrix()");
	CMatrix m(nr, nc);
	for (size_t i = 0; i < m.nRows; ++i)
		for (size_t j = 0; j < m.nColumns; ++j)
			m(i, j) = get(r + i, c + j);
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

			m(i, j) = get(sR, sC);
		}
	return m;
}


double CMatrix::getDeterminant() const
{
	if (nRows != nColumns)
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::getDeterminant()");
        if (*this == CMatrix())
            return 0;
	if (nRows == 1 && nColumns == 1)

		return (*this)(0, 0);

    size_t a=0; size_t b=0; double flag=1.0;
    size_t m=getnRows();
    size_t n=getnColumns();
    CMatrix r(m,n);
    r=*this;
    double det=1.0;
	while(a<m && b<n)
	{
		r.fix(a,b,flag);//basicall puts blank rows on the bottom
		r.sweep(a,b);//sweeps the column b taking a as pivot
		//advancing after sweeping
		det*=r(a,b);
		a++;
		b++;
	}
	//for(int k=0;k<m;k++) det*=r(k,k);
	return det*flag;
}

void CMatrix::sweep(size_t a,size_t b)
{

	if ((*this)(a,b) == 0)	//Checking whether the element is a valid pivot
		return;

	double factor=0.0;//number to multiply pivot with and subtract from corresponding rows
	for(size_t i=a+1;i<getnRows();i++)
	{
		if(i!=a)
		{
			factor=(*this)(i,b)/(*this)(a,b);//number to multiply pivot with and subtract from corresponding rows to sweep

			for(size_t j=0;j<getnRows();j++)
			{

				(*this)(i,j)-=factor*(*this)(a,j);//actual subtraction of each element of row i
                		if(fabs((*this)(i,j))<EPSILON)(*this)(i,j)=0.0;
			}
		}
	}

}

void CMatrix::swaprow(size_t a,size_t b)
{
	/*swaps row a and row b*/
	double temp=0;
	for(size_t j=0;j<getnRows();j++)
	{

		temp=(*this)(a,j);
		(*this)(a,j)=(*this)(b,j);
		(*this)(b,j)=temp;
	}
}

void CMatrix::fix(size_t a,size_t b,double &flag)
{
	//Simply swaps the first non zero row it finds incase element we are trying to use as pivot is 0
	while((*this)(a,b)==0 && a<getnRows() && b<getnRows())
	{
		for(size_t i=a;i<getnRows();i++)
		{
			if((*this)(i,b)!=0)
			{
				swaprow(a,i);
				flag*=-1.0;
				return;
			}
		}
		b++;
	}
}
CMatrix CMatrix::getTranspose() const
{
	CMatrix r(nColumns, nRows);
	for (size_t i = 0; i < nRows; ++i)
		for (size_t j = 0; j < nColumns; ++j)
			r(j, i) = get(i, j);
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

static unsigned short get_window_width()
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	return w.ws_col;
}

static void print_page(
		std::ostream& os,
		size_t full_column_width,
		const std::vector<std::string>& matrix_string,
		size_t m_nrows,
		size_t m_ncols,
		size_t start_col,
		size_t ncols_in_page
	)
{
	size_t end_col = start_col + ncols_in_page;
	if (ncols_in_page != 0) { // a multipage matrix; print a header
		if (ncols_in_page == 1)
			os << " Column " << start_col + 1 << ":\n\n";
		else
			os << " Columns " << start_col + 1
			   << " through " << end_col << ":\n\n";
	} else {
		end_col = start_col + m_ncols;
	}
	for (size_t i = 0; i < m_nrows; ++i, os << '\n')
		for (size_t j = start_col; j < end_col; ++j)
			os << std::setw(full_column_width)
			   << matrix_string[i*m_ncols + j];
}

static void create_string_representation(
		const CMatrix& m,
		std::vector<std::string>& matrix_string,
		size_t& column_width
	)
{
	std::vector<size_t> elements_length;
	size_t n = m.getn();
	matrix_string.resize(n);
	elements_length.resize(n);
	for (size_t i = 0; i < n; ++i) {
		enum { max_chars_per_elem = 16 };
		char element[max_chars_per_elem];
		std::snprintf(element, max_chars_per_elem, "%.5g", m(i));
		matrix_string[i] = element;
		elements_length[i] = matrix_string[i].length();
	}
	column_width =
		*std::max_element(elements_length.begin(), elements_length.end());
}

std::ostream& operator<<(std::ostream& os, const CMatrix& m)
{
	// we want to print the matrix in columns whose width is constant, and
	// wrap the rows around the entire matrix if they are too long.
	// every non-complex number is printed using the format "%.5g".
	// columns are left-padded with spaces when necessary.
	//
	// the number of columns in the window
	unsigned short window_width = get_window_width();
	// the number of spaces before or between columns
	const size_t space_width = 3;
	// the matrix' elements formatted for printing
	std::vector<std::string> matrix_string;
	// the max num of chars per column
	size_t column_width;
	// determine column_width and matrix_string
	create_string_representation(m, matrix_string, column_width);
	const size_t full_column_width = space_width + column_width;
	// if the matrix' rows are not too long for a single screen/page
	if (m.getnColumns() * full_column_width <= window_width) {
		os << '\n';
		print_page(
			os,
			full_column_width,
			matrix_string,
			m.getnRows(),
			m.getnColumns(),
			0,
			0
		);
	// if we need to print the matrix on multiple screens/pages
	} else {
		// determine the number of cols to print in a row per "page"
		const size_t ncols = window_width / full_column_width;
		// determine how many "pages" we need to print
		const size_t npages = ceil(m.getnColumns() * 1.0 / ncols);
		for (size_t page = 0; page < npages; ++page) {
			size_t start_col = page * ncols;
			size_t ncols_in_page =
				std::min(ncols, m.getnColumns() - start_col);
			os << '\n';
			print_page(
				os,
				full_column_width,
				matrix_string,
				m.getnRows(),
				m.getnColumns(),
				start_col,
				ncols_in_page
			);
		}
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
		get(i) = m(i);
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


void CMatrix::CopyMatrix(std::string s)
{
reset();
char* buffer = new char[s.length()+1];
strcpy(buffer, s.c_str());
char* lineContext;
char lineSeparators[3];
lineSeparators[0] = ';';
lineSeparators[1] = '\r';
lineSeparators[2] = '\n';


char* line = strtok_r(buffer, lineSeparators, &lineContext);
while(line)
{
CMatrix row;
char* context;
char separators[3];
separators[0] = ' ';
separators[1] = '[';
separators[2] = ']';

char* token = strtok_r(line, separators, &context);
while(token)
{
CMatrix item = atof(token);
row.addColumn(item);
token = strtok_r(NULL, separators, &context);
}
if(row.nColumns>0 && (row.nColumns==nColumns || nRows==0))
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
	values = new double[1];
	get(0) = d;
}

double CMatrix::get(size_t i) const
{ return values[i]; }
        
double& CMatrix::get(size_t i)
{ return values[i]; }

double CMatrix::get(size_t i, size_t j) const
{ return values[j + i * nColumns]; }
        
double& CMatrix::get(size_t i, size_t j)
{ return values[j + i * nColumns]; }

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
		if (fabs(a[i] - b[i]) > EPSILON)
			return false;
	return true;
}

bool operator!=(const CMatrix& a, const CMatrix& b)
{ return !(a == b); }

// arithmetic functions and operators:
// first, the unique functions: mul, div
CMatrix mul(const CMatrix& a, const CMatrix& b)
{
	if (a.getnColumns() != b.getnRows())
		throw std::invalid_argument
		    ("Invalid matrix dimensions in CMatrix::mul()");
	CMatrix r(a.getnRows(), b.getnColumns(), CMatrix::MI_ZEROS);
	// looping over j inside k makes fewer cache misses
	for (size_t i = 0; i < r.getnRows(); ++i)
		for (size_t k = 0; k < a.getnColumns(); k++)
			for (size_t j = 0; j < r.getnColumns(); ++j)
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

// We need to construct 4 overloaded versions of 4 element-wise functions:
// add, sub, amul (element-wise multiplication), adiv (element-wise division).
// Copy&pasting is never a good coding strategy. Instead, we will write a
// template, and generate them all from it. I won't go for C++ templates.
// This C macro takes the name (add, sub, etc) and the operator (+, -, etc)
// and generates all the 4 overloaded functions for us.
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

// Thanks for reading this far! I really appreciate it. ^_^

}; // namespace asu

