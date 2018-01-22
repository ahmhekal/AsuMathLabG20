#include <iostream>
#include <string>
#include "math.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>
#include "matrix.h"
using namespace std;

void mathematical_calc (string& a);

//////////////////////////////////////////////////////////////////
double to_double(string operand);
string to_string(double operand);
void math_piority_calc(string& test);
/*
int main(){
//testing first issue in parser2 that replace sin,cos,sqrt... with thier result
string test="sin(0.4)*5.5/2+12*tan(0.4)+sqrt(25)+5^3-1";
mathematical_calc(test1);
cout<<test1<<endl;
/////////////////////////////////////

}*/

