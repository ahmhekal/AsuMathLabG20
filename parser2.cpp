#include <iostream>
#include<string>
#include "math.h"
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<fstream>
#include"matrix.h"
//first issue:replacing mathimatical operations eith thier result
void mathematical_calc(string& a){
if(a.find("sin")!=string::npos){

int first_pos=a.find("sin");
int end_pos=a.find(')',first_pos);
string expression=a.substr(first_pos,end_pos-first_pos+1);
string operand_str=expression.substr(4,a.length()-4-1);
char * buffer=new char[operand_str.length()+1];
strcpy(buffer,operand_str.c_str());
double operand=atof(buffer);
double result;
result=sin(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
a.replace(first_pos,end_pos-first_pos+1,(string)buffer_test);

delete [] buffer;


}
if(a.find("cos")!=string::npos){
int first_pos=a.find("cos");
int end_pos=a.find(')',first_pos);
string expression=a.substr(first_pos,end_pos-first_pos+1);
string operand_str=expression.substr(4,a.length()-4-1);
char * buffer=new char[operand_str.length()+1];
strcpy(buffer,operand_str.c_str());
double operand=atof(buffer);
double result=cos(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
a.replace(first_pos,end_pos-first_pos+1,(string)buffer_test);

delete [] buffer;



}
 if(a.find("tan")!=string::npos){
int first_pos=a.find("tan");
int end_pos=a.find(')',first_pos);
string expression=a.substr(first_pos,end_pos-first_pos+1);
string operand_str=expression.substr(4,a.length()-4-1);
char * buffer=new char[operand_str.length()+1];
strcpy(buffer,operand_str.c_str());
double operand=atof(buffer);
double result=tan(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
a.replace(first_pos,end_pos-first_pos+1,(string)buffer_test);

delete [] buffer;

}
if(a.find("sqrt")!=string::npos){
int first_pos=a.find("sqrt");
int end_pos=a.find(')',first_pos);
string expression=a.substr(first_pos,end_pos-first_pos+1);
string operand_str=expression.substr(5,a.length()-5-1);
char * buffer=new char[operand_str.length()+1];
strcpy(buffer,operand_str.c_str());
double operand=atof(buffer);
double result=sqrt(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
a.replace(first_pos,end_pos-first_pos+1,(string)buffer_test);

delete [] buffer;



}

}

//////////////////////////////////////////////////////////////////
double to_double(string operand){
char * buffer=new char[operand.length()+1];
strcpy(buffer,operand.c_str());
double result=atof(buffer);
delete [] buffer;
return result;

}
string to_string(double operand){
char buffer_test[50];
sprintf(buffer_test,"%g",operand);
return(string)buffer_test;
}

int main(){
//testing first issue in parser2 that replace sin,cos,sqrt... with thier result
string test="sin(0.4)*5.5/2+12*tan(0.4)+sqrt(25)+5^3-1";
mathematical_calc(test1);
cout<<test1<<endl;
/////////////////////////////////////

}
