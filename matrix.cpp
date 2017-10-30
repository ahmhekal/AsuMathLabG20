#include "matrix.h"
#include <cstdlib>	// atof, rand
#include <ctime>	// time, for seeding rand
#include <cstring>	// strtok_r

//**************************************Branch [ahmhekal]**************************************//

CMatrix CMatrix::operator++()
{
	CMatrix addend(nR, nC, MI_VALUE, 1.0);
	add(addend);
	return *this;
}

CMatrix CMatrix::operator++(int)
{
	CMatrix C = *this;
	CMatrix addend(nR, nC, MI_VALUE, 1.0);
	add(addend);
	return C;
}

CMatrix CMatrix::operator--()
{
	CMatrix addend(nR, nC, MI_VALUE, -1.0);
	add(addend);
	return *this;
}

CMatrix CMatrix::operator--(int)
{
	CMatrix r = *this;
	CMatrix addend(nR, nC, MI_VALUE, -1.0);
	add(addend);
	return r;
}

CMatrix CMatrix::operator-()
{
	CMatrix result = *this;
	for (int iR = 0; iR < nR; iR++)
		for (int iC = 0; iC < nC; iC++)
			result.values[iR][iC] = -values[iR][iC];
	return result;
}

CMatrix CMatrix::operator+()
{
	return *this;
}



//**************************************Branch [abdozizo111]**************************************//

void CMatrix::reset()
{
	if (values)
	{
		for(int i=0;i<nR;i++)
			delete[] values[i];
		delete[] values;
	}
	nR=nC=0;
	values=NULL;
}
string CMatrix::getString()
{
	string s;
	for(int iR=0;iR<nR;iR++)
	{
		for(int iC=0;iC<nC;iC++)
		{
			//char buffer[50];
			//sprintf_s(buffer,50,"%g\t",values[iR][iC]);
			if(values[iR][iC]==0 || fabs(values[iR][iC])<1e-15)cout<<"0"<<" ";
			else {cout<<values[iR][iC]<<" ";}
		}
		//s+="\n";
		cout<<endl;
	}
	return s;
}
CMatrix CMatrix::operator =(const CMatrix& m)
{
	CopyMatrix(m);
	return *this;
}
CMatrix CMatrix::operator=(double d)
{
	CopyMatrix(d);
	return *this;
}

CMatrix CMatrix::operator=(const string s)
{
	CopyMatrix(s);
	return *this;
}

//************************************** ABDO0000 **************************************//
void CMatrix::add(CMatrix& m)
{
	if(nR!=m.nR||nC!=m.nC)
		throw("Invalid matrix dimension");
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC] += m.values[iR][iC];
}
void CMatrix::operator+=(CMatrix& m)
{
	add(m);
}
void CMatrix::operator+=(double d)
{
	CMatrix addend(nR, nC, MI_VALUE, d);
	add(addend);
}
CMatrix CMatrix::operator+(CMatrix& m)
{
	CMatrix r = *this;
	r+=m;
	return r;
}
CMatrix CMatrix::operator+(double d)
{
	CMatrix r = *this;
	r+=d;
	return r;
}

//**************************************Branch [Abduu13]**************************************//
CMatrix::CMatrix()
{
	nR = nC = 0;
	values = NULL;
}

CMatrix::~CMatrix()
{
	reset();
}

CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue)
{
	this->nR = nR;
	this->nC = nC;
	if((nR*nC)==0){values = NULL; return;}

	values = new double*[nR];
	for(int iR = 0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC = 0;iC<nC;iC++)
		{
			switch(initialization)
			{
			case MI_ZEROS:values[iR][iC] = 0;break;
			case MI_ONES :values[iR][iC] = 1;break;
			case MI_EYE  :values[iR][iC] = (iR==iC)?1:0; break;
			case MI_RAND :values[iR][iC] = (rand()%1000000)/1000000.0; break;
			case MI_VALUE: values[iR][iC] = initializationValue; break;
			}
		}

	}
}

CMatrix::CMatrix(int nR, int nC, double first, ...)
{
	this->nR= nR;
	this->nC= nC;
	if((nR*nC)==0){values = NULL; return;}

	values = new double*[nR];
	va_list va;
	va_start(va, first);
	for(int iR=0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC=0;iC<nC;iC++)
		{
			values[iR][iC] = (iR==0&&iC==0)?first:va_arg(va, double);
		}
	}
	va_end(va);
}

CMatrix::CMatrix(CMatrix& m)
{
	nR = nC = 0;
	values = NULL;
	CopyMatrix(m);
}

//**************************************Branch [AbdallahReda]**************************************//
void CMatrix::addColumn(CMatrix& m)
{
	CMatrix n(max(nR, m.nR), nC+m.nC);
	n.setSubMatrix(0, 0, *this);
	n.setSubMatrix(0, nC, m);
	*this = n;
}
void CMatrix::addRow(CMatrix& m)
{
	CMatrix n(nR+m.nR, max(nC, m.nC));
	n.setSubMatrix(0, 0, *this);
	n.setSubMatrix(nR, 0, m);
	*this = n;
}

void CMatrix::getInverse(CMatrix& t)
{
	double det = getDeterminant();
	if (det == 0 || fabs(det) < 1e-15)
		throw std::runtime_error("Inverting a noninvertible martix");
	det = 1.0 / det; 
	CMatrix r(nR, nR);
	for (int i = 0; i < nR; ++i)
		for (int j = 0; j < nR; ++j)
			r.values[j][i] = getCofactor(i,j).getDeterminant() * (((i+j)%2==0)?1:-1);
	r *= det;
	t = r;
}

CMatrix CMatrix::div(CMatrix& m)
{
    CMatrix d(m);
    CMatrix This= *this;
    m.getInverse(d);
    //CMatrix rd.getnR(),d.getnC(),CMatrix::MI_ZEROS);
   // r.CopyMatrix(*this*d);
    This.mul(d);
	return This;
}
CMatrix CMatrix::operator/(CMatrix& m)
{
    CMatrix d(m);
    CMatrix This= *this;
    m.getInverse(d);
    //CMatrix rd.getnR(),d.getnC(),CMatrix::MI_ZEROS);
   // r.CopyMatrix(*this*d);
    This.mul(d);
	return This;

    }

CMatrix CMatrix::operator/(double d)
{
	if (d == 0 || fabs(d) < 1e-15)
	    throw std::runtime_error("Division by zero");
	CMatrix result = *this;
	for (int i = 0; i < nR; ++i)
		for (int j = 0; j < nC; ++j)
			result.values[i][j] /= d;
	return result;
}

//**************************************Branch [diaa]**************************************//

void CMatrix::setSubMatrix(int r, int c, CMatrix& m)
{
	if((r+m.nR)>nR || (c+m.nC)>nC)throw("Invalid matrix dimension");
	for(int iR=0;iR<m.nR;iR++)
		for(int iC=0;iC<m.nC;iC++)
			values[r+iR][c+iC] = m.values[iR][iC];
}
CMatrix CMatrix::getSubMatrix(int r, int c, int nr, int nc)
{
	if((r+nr)>nR || (c+nc)>nC)throw("Invalid matrix dimension");
	CMatrix m(nr, nc);
	for(int iR=0;iR<m.nR;iR++)
		for(int iC=0;iC<m.nC;iC++)
			m.values[iR][iC] = values[r+iR][c+iC];
	return m;
}
CMatrix CMatrix::getCofactor(int r, int c)
{
	if (nR <= 1 && nC <= 1)throw("Invalid matrix dimension");
	CMatrix m(nR - 1, nC - 1);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
		{
			int sR = (iR<r) ? iR : iR + 1;
			int sC = (iC<c) ? iC : iC + 1;
			m.values[iR][iC] = values[sR][sC];
		}
	return m;
}
double CMatrix::getDeterminant()
{
	if (nR != nC)throw("Invalid matrix dimension");
	if (nR == 1 && nC == 1)return values[0][0];
	double value = 0.0, m = 1.0;
	for (int iR = 0; iR<nR; iR++)
	{
		value += m * values[0][iR] * getCofactor(0, iR).getDeterminant();
		m *= -1.0;
	}
	return value;
}

void CMatrix::getTranspose(CMatrix& r)
{
    r = CMatrix(nC, nR);
	for (int i = 0; i < nR; ++i)
		for (int j = 0; j < nC; ++j)
			r.values[j][i] = values[i][j];
}

//**************************************Branch [Aladdin95]**************************************//

istream& operator >> (istream &is, CMatrix& m)   //need to be edited
{
	string s;
	getline(is, s, ']');
	s+="]";
	CMatrix readMatrix(s);
	m = readMatrix;
	return is;
}


ostream& operator << (ostream &os, CMatrix& m)
{
	os<<m.getString();
	return os;
}

int CMatrix::getnC() const
{
	return this->nC;
}

int CMatrix::getnR() const
{
	return this->nR;
}

int CMatrix::getn() const
{
	return (this->nC)*(this->nR);
}

//**************************************Branch [omarashraf10]**************************************//


CMatrix::CMatrix(string s)   //need to be edited
{
	nR = nC = 0;
	values = NULL;
	CopyMatrix(s);
}

CMatrix::CMatrix(double d)
{
	nR = nC = 0;
	values = NULL;
	CopyMatrix(d);
}

void CMatrix::CopyMatrix(const CMatrix& m)
{
	reset();
	this->nR = m.nR;
	this->nC = m.nC;
	if((nR*nC)==0){values=NULL; return;}
	values = new double*[nR];
	for(int iR=0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC=0;iC<nC;iC++)
		{
			values[iR][iC] = m.values[iR][iC];
		}
	}
}


void CMatrix::CopyMatrix(string s)   //need to be edited
{
	reset();

	char* buffer = new char[s.length()+1];
	strcpy(buffer, s.c_str());
	char* lineContext;
	const char* lineSeparators = ";\r\n";
	char* line = strtok_r(buffer, lineSeparators, &lineContext);
	while(line)
	{
		CMatrix row;
		char* context;
		const char* separators = " []";
		char* token = strtok_r(line, separators, &context);
		while(token)
		{
			CMatrix item(atof(token));
			row.addColumn(item);
			token = strtok_r(NULL, separators, &context);
		}
		if(row.nC>0 && (row.nC==nC || nR==0))
			addRow(row);
		line = strtok_r(NULL, lineSeparators, &lineContext);
	}
	delete[] buffer;
}

void CMatrix::CopyMatrix(double d)
{
	reset();
	this->nR = 1;
	this->nC = 1;
	values = new double*[1];
	values[0] = new double[1];
	values[0][0] = d;
}


//**************************************Branch [noureddin]**************************************//

void CMatrix::mul(CMatrix& m)
{
	if(nC != m.nR)
		throw("Invalid matrix dimension");
	CMatrix r(nR, m.nC);
	for(int iR=0;iR<r.nR;iR++)
		for(int iC=0;iC<r.nC;iC++)
		{
			r.values[iR][iC] = 0.0;
			for(int k=0;k<nC;k++)
				r.values[iR][iC] += values[iR][k]*m.values[k][iC];
		}
        CopyMatrix(r);
}
void CMatrix::operator*=(CMatrix& m)
{
	mul(m);
}
void CMatrix::operator*=(double d)
{
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC] *= d;
}
CMatrix CMatrix::operator*(CMatrix& m)
{
	CMatrix r = *this;
	r*=m;
	return r;
}
CMatrix CMatrix::operator*(double d)
{
	CMatrix r = *this;
	r*=d;
	return r;
}
//**************************************Branch [mafouadm]**************************************//


void CMatrix::sub(CMatrix& m)
{
	if(nR!=m.nR||nC!=m.nC)
		throw("Invalid matrix dimension");
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC] -= m.values[iR][iC];
}
void CMatrix::operator-=(CMatrix& m)
{
	sub(m);
}
void CMatrix::operator-=(double d)
{
	CMatrix subtrahend(nR, nC, MI_VALUE, d);
	sub(subtrahend);
}
CMatrix CMatrix::operator-(CMatrix& m)
{
	CMatrix r = *this;
	r-=m;
	return r;
}
CMatrix CMatrix::operator-(double d)
{
	CMatrix r = *this;
	r-=d;
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
	if (a.getnR() != b.getnR() || a.getnC() != b.getnC())
	    throw std::runtime_error("Invalid matrix dimensions");
	CMatrix r(a.getnR(), a.getnC());
	for (int i = 0; i < a.getnR(); ++i)
		for (int j = 0; j < a.getnC(); ++j)
			r(i,j) = a(i,j) / b(i,j);
	return r;
}

