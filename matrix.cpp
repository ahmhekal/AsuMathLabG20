#include "matrix.h"

//**************************************Branch [ahmhekal]**************************************//


CMatrix CMatrix: :operator++()
{
add(CMatrix(nR, nC, MI_VALUE, 1.0) );
return *this;
}

CMatrix CMatrix: :operator++(int)
{
CMatrix C = *this;
add(CMatrix(nR, nC, MI_VALUE, 1.0) );
return C;
}

CMatrix CMatrix: :operator--( )
{
add (CMatrix(nR, nC, MI_VALUE, -1.0) );
return *this;
}

CMatrix CMatrix: :operator--(int)
{
CMatrix r = *this;
add(CMatrix(nR,nC, MI_VALUE, -1.0) );
return r;
}

CMatrix CMatrix: :operator-( )
{
for(int iR=0;iR<n R;i R++)
 
for(int iC=0;iC<n C;iC++)
values[iR] [iC] = -values[iR] [iC];

return *this;
}



CMatrix CMatrix: :operator+()
{
return *this;
}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//



//**************************************Branch [diaaahmed850]**************************************//

 //---------------------------------write your code here---------------------------//


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//






//**************************************Branch [abdozizo111]**************************************//



void CMatrix::reset
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
string CMatrix::getstring()
{
string s;
for(int iR=0;iR<nR;iR++)
{
for(int iC=0;iC<nC;iC++)
{
char buffer[50];
sprintf_s(buffer,50,"%g\t",values[iR][iC]);
}
s+="\n";
}
return s;
}
CMatrix CMatrix::operator=(CMatrix& m)
{
copy(m);
return *this;
}
CMatrix CMatrix::operator=(double d)
{
copy(d);
return *this;
}

CMatrix CMatrix::operator=(string s)
{
copy(s);
return *this;
}


//************************************** ABDO0000 **************************************//

 //---------------------------------write your code here---------------------------//
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
  add(CMatrix(nR, nC, MI_VALUE, d));
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



//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//


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
    for(int iC;iC<nC;iC++)
    {
     values[iR][iC] = (iR==0&&iC==0)first:va_arg(va, double);
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


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//



//**************************************Branch [AbdallahReda]**************************************//

 //---------------------------------write your code here---------------------------//


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//



//**************************************Branch [Aladdin95]**************************************//

istream& operator >> (istream &is, CMatrix& m)
{
 string s;
 getline(is, s, ']');
 s+="]";
 m = CMatrix(s);
 return is;
}


ostream& operator << (ostream &os, CMatrix& m)
{
 os<<m.getString();
 return os;
}

int GetnC()
{
return this->nC;
}

int GetnR()
{
return this->nR;
}

int Getn()
{
return (this->nC)*(this->nR);
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//


//**************************************Branch [omarashraf10]**************************************//

 CMatrix::CMatrix(string s)
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

void CMatrix::CopyMatrix(CMatrix& m)
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

void CMatrix::CopyMatrix(string s)
{
reset();

char* buffer = new char[s.length()+1];
strcpy(buffer, s.c_str());
char* lineContext;
char* lineSeparators = ";\r\n";
char* line = strtok_s(buffer, lineSeparators, &lineContext);
while(line)
{
CMatrix row;
char* context;
char* separators = " []";
char* token = strtok_s(line, separators, &context);
while(token)
{
CMatrix item = atof(token);
row.addColumn(item);
token = strtok_s(NULL, separators, &context);
}
if(row.nC>0 && (row.nC==nC || nR==0))
addRow(row);
line = strtok_s(NULL, lineSeparators, &lineContext);
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


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//


//**************************************Branch [noureddin]**************************************//

void CMatrix::mul(CMatrix& m) { copy(operator*(m)); }

void CMatrix::operator*=(CMatrix& m) { copy(operator*(m)); }

void CMatrix::operator*=(double d) { copy(operator*(d)); }
    
CMatrix CMatrix::operator*(CMatrix& m) {
    if (nC != m.nR) throw("Matrix dimension error");
    CMatrix result = CMatrix(nR, m.nC, MI_ZERO);
    for (size_t i = 0; i < nR; ++i)
        for (size_t j = 0; j < m.nC; ++j)
            for (size_t k = 0; k < nC; ++k)
                result.values[i][j] += values[i][k] * m.values[k][j];
    return result;
}

CMatrix CMatrix::operator*(double d) {
    CMatrix result = CMatrix(nR, nC);
    for (size_t i = 0; i < nR; ++i)
        for (size_t j = 0; j < nC; ++j)
            result.values[i][j] = values[i][j] * d;
    return result;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//


//**************************************Branch [mafouadm]**************************************//

void CMatrix::sub(CMatrix& m) { copy(operator-(m)); }

void CMatrix::operator-=(CMatrix& m) { copy(operator-(m)); }

void CMatrix::operator-=(double d) { copy(operator-(d)); }
    
CMatrix CMatrix::operator-(CMatrix& m) {
    if (nR != m.nR || nC != m.nC) throw("Matrix dimension error");
    CMatrix result = CMatrix(nR, nC);
    for (size_t i = 0; i < nR; ++i)
        for (size_t j = 0; j < nC; ++j)
            result.values[i][j] = values[i][j] - m.values[i][j];
    return result;
}

CMatrix CMatrix::operator-(double d) {
    CMatrix result = CMatrix(nR, nC);
    for (size_t i = 0; i < nR; ++i)
        for (size_t j = 0; j < nC; ++j)
            result.values[i][j] = values[i][j] - d;
    return result;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//


