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
void math_piority_calc(string& test){
while(test.find('^')!=string::npos){
//int a=test.find('*');
int a;
for(int i=0;i<test.length();i++){
if(test[i]=='^'){
a=i;
break;
}
}

int x=0;
int y=test.length()-1;
for(int i=a-1;i>=0;i--){
if(!(((test[i]>='.'&&test[i]<='9')&&test[i]!='/')/*||test[0]=='-'*/)){
x=i+1;
break;

}
}
for(int j=a+1;j<test.length();j++){
if(!((test[j]>='.'&&test[j]<='9')&&test[j]!='/')){


y=j-1;
break;

}

}
double z=to_double(test.substr(x,a-x));
double k=to_double(test.substr(a+1,y-a));


double result=pow(z,k);

string replacement=to_string(result);
test.replace(x,y-x+1,replacement);
cout<<test<<endl;
}
while(test.find('*')!=string::npos||test.find('/')!=string::npos){
//int a=test.find('*');
int a;
for(int i=0;i<test.length();i++){
if(test[i]=='*'||test[i]=='/'){
a=i;
break;
}
}

int x=0;
int y=test.length()-1;
for(int i=a-1;i>=0;i--){
if(!(((test[i]>='.'&&test[i]<='9')&&test[i]!='/')/*||test[0]=='-'*/)){
x=i+1;
break;

}
}
for(int j=a+1;j<test.length();j++){
if(!((test[j]>='.'&&test[j]<='9')&&test[j]!='/')){


y=j-1;
break;

}

}
double z=to_double(test.substr(x,a-x));
double k=to_double(test.substr(a+1,y-a));
double result;
switch(test[a]){
case '*': result=z*k; break;
case '/': result=z/k; break;

}
string replacement=to_string(result);
test.replace(x,y-x+1,replacement);
cout<<test<<endl;
}
while((test.find('+')!=string::npos||test.find('-',1)!=string::npos)/*&&(test[0]!='-'||test.length()>10)*/){
int a;
for(int i=0;i<test.length();i++){
if((test[i]=='+'||test[i]=='-')&&i!=0){
a=i;
break;
}
}
int x=0;
int y=test.length()-1;
for(int i=a-1;i>=0;i--){
if(!((test[i]>='.'&&test[i]<='9')||test[0]=='-')){
x=i+1;
break;

}
}
for(int j=a+1;j<test.length();j++){
if(!(test[j]>='.'&&test[j]<='9')){


y=j-1;
break;

}

}
double z=to_double(test.substr(x,a-x));
double k=to_double(test.substr(a+1,y-a));
double result;
switch(test[a]){
case '+': result=z+k; break;
case '-': result=z-k; break;

}
string replacement=to_string(result);
test.replace(x,y-x+1,replacement);
cout<<test<<endl;
}
}

int main(){
//testing first issue in parser2 that replace sin,cos,sqrt... with thier result
string test="sin(0.4)*5.5/2+12*tan(0.4)+sqrt(25)+5^3-1";
mathematical_calc(test);
math_piority_calc(test);

cout<<test<<endl;
string test1="-1/11.32-12.1*3.1+6.4^0.454545";
math_piority_calc(test1);

cout<<test1<<endl;
/////////////////////////////////////

}
