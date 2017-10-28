#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
    CMatrix a(3,3,1.0,2.0,3.0,4.0,8.0,6.0,7.0,9.0,9.0);
    CMatrix b(3,3,2.0,2.0,3.0,4.0,8.0,6.0,7.0,8.0,9.0);
    CMatrix y(3,3);
    double h=a.getDeterminant();

    cout<<endl<<h<<endl;
    b.getInverse(y);
    CMatrix o(3,3);
    o=a*y;
    //y=u/t;
    cout<<endl<<y.getString()<<endl; cout<<endl<<o.getString()<<endl;
    double x=0;
    cout<<endl<<x*(-1.0/12.0);
    return 0;
}

