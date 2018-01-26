#include <fstream>
#include "string"
#include "matrix.h"
#include <stdlib.h>  
#include "functions.h"
#include "math.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace asu;


std::string* vars; //matrices names in string ====  std::string vars[100];
CMatrix* mvars;   //matrices values  ====  CMatrix mvars[100];
int k=0; //matrix index (global variable)

std::string removeSpaces(std::string input)   //remove spaces from the beginning to '[' or the end of the line
{
  //int length = input.length();
  for (int i = 0; !( (input[i]=='[') || (input[i]=='\0') ); i++) 
  {
     if(input[i] == ' ' )
      {input.erase(i, 1);i--;}
  }
  return input;
}


asu::CMatrix stringtomatrix (std::string s, int k)  //return matrix value of a string name
{
	int i;
	for (i =k+1 ; i>=0; i--)
	{
		if(vars[i]==s) return mvars[i];
	}
	if(i<=0) throw std::invalid_argument("Impossible variable name");
	asu::CMatrix nomatrix; return nomatrix ;
}
std::string to_string(double operand){
char buffer_test[50];
sprintf(buffer_test,"%g",operand);
return(std::string)buffer_test;
}
double to_double(std::string operand){
char * buffer=new char[operand.length()+1];
strcpy(buffer,operand.c_str());
double result=atof(buffer);
delete [] buffer;
return result;

}

void math_piority_calc(std::string& test){
int count=0;

while(test.find('^')!=std::string::npos){
//int a=test.find('*');
int a=0;
for(unsigned int i=0;i<test.length();i++){
if(test[i]=='^'){
a=i;
break;
}
}

int x=0;
int y=test.length()-1;
for(int i=a-1;i>=0;i--){
if(!((test[i]>='.'&&test[i]<='9')&&test[i]!='/')&&(!(test[i]>='a'&&test[i]<='z'))&&(!(test[i]>='A'&&test[i]<='Z')))
 {
x=i+1;
break;

}
}
for(unsigned int j=a+1;j<test.length();j++){
if(!((test[j]>='.'&&test[j]<='9')&&test[j]!='/')&&(!(test[j]>='a'&&test[j]<='z'))&&(!(test[j]>='A'&&test[j]<='Z'))&&test[a+1]!='-'){


y=j-1;
//
//cout<<y;
break;

}

}
//cout<<test.substr(x,a-x)<<endl;
//cout<<test.substr(a+1,y-a+1);
//cout<<stringtomatrix(test.substr(x,a-x),k);
std::string operand1;
std::string operand2;
if(test[a-1]=='.'){
 operand1=test.substr(x,a-x-1);
}
else{ operand1=test.substr(x,a-x);}


 operand2=test.substr(a+1,y-a);
if(!isdigit(operand1[0])||!isdigit(operand2[0])){
double m=to_double(operand2);
asu::CMatrix r ;
if(test[a-1]=='.'){
  r =power_modified_elementwise(stringtomatrix(operand1,k),m);
}
else{ r =power_modified(stringtomatrix(operand1,k),m);}

//cout<<r;
count++;
k++;
mvars[k]=r;
std::string s="result";
vars[k]=s+to_string(k);
test.replace(x,y-x+1,vars[k]);
//std::cout<<test<<std::endl;


}
else{
double z=to_double(test.substr(x,a-x));
double k=to_double(test.substr(a+1,y-a));


double result=pow(z,k);

std::string replacement=to_string(result);
test.replace(x,y-x+1,replacement);
//std::cout<<test<<std::endl;

}
 }
 while(test.find('*')!=std::string::npos||test.find('/')!=std::string::npos){
//int a=test.find('*');
int a=0;
for(unsigned int i=0;i<test.length();i++){
if(test[i]=='*'||test[i]=='/'){
a=i;
break;
}
}

int x=0;
int y=test.length()-1;
//&&test[0]!='-'
for(int i=a-1;i>=0;i--){
if(!((test[i]>='.'&&test[i]<='9')&&test[i]!='/')&&(!(test[i]>='a'&&test[i]<='z'))&&(!(test[i]>='A'&&test[i]<='Z'))&&test[0]!='-')
 {
x=i+1;
break;

}
}
for(unsigned int j=a+1;j<test.length();j++){
if(!((test[j]>='.'&&test[j]<='9')&&test[j]!='/')&&(!(test[j]>='a'&&test[j]<='z'))&&(!(test[j]>='A'&&test[j]<='Z'))){


y=j-1;
//
//cout<<y;
break;

}

}
std::string operand1;
std::string operand2;
if(test[a-1]=='.'){
 operand1=test.substr(x,a-x-1);
}
else{ operand1=test.substr(x,a-x);}
if(test[y]=='.'){
y-=1;
}


 operand2=test.substr(a+1,y-a);
//std::cout<<operand1<<std::endl;

//std::cout<<operand2<<std::endl;
if((!isdigit(operand1[0])||!isdigit(operand2[0]))&&operand1[0]!='-'){
asu::CMatrix firstmatrix;
asu::CMatrix secondmatrix;
double operand_double;
if(!isdigit(operand1[0])&&!isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,k);
secondmatrix=stringtomatrix(operand2,k);
if(test[a-1]=='.'){
k++;
switch(test[a]){
case '*': mvars[k].CopyMatrix(amul(firstmatrix,secondmatrix)); break;
case '/': mvars[k].CopyMatrix(adiv(firstmatrix,secondmatrix)); break;

}
}
else{
k++;
switch(test[a]){
case '*': mvars[k].CopyMatrix(mul(firstmatrix,secondmatrix)); break;
case '/': mvars[k].CopyMatrix(div(firstmatrix,secondmatrix)); break;


}
}
}
if(!isdigit(operand1[0])&&isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,k);
operand_double=to_double(operand2);
if(test[a-1]=='.'){
k++;
switch(test[a]){
case '*': mvars[k].CopyMatrix(amul(firstmatrix,operand_double)); break;
case '/': mvars[k].CopyMatrix(adiv(firstmatrix,operand_double)); break;

}

}
else{
secondmatrix=operand_double;
k++;
switch(test[a]){
case '*': mvars[k].CopyMatrix(mul(firstmatrix,secondmatrix)); break;
case '/': mvars[k].CopyMatrix(div(firstmatrix,secondmatrix)); break;


}
}


}

///
if(isdigit(operand1[0])&&!isdigit(operand2[0])){
operand_double=to_double(operand1);
secondmatrix=stringtomatrix(operand2,k);

if(test[a-1]=='.'){
k++;
switch(test[a]){
case '*': mvars[k].CopyMatrix(amul(operand_double,secondmatrix)); break;
case '/': mvars[k].CopyMatrix(adiv(operand_double,secondmatrix)); break;

}

}
else{
firstmatrix=operand_double;
k++;
switch(test[a]){
case '*': mvars[k].CopyMatrix(mul(firstmatrix,secondmatrix)); break;
case '/': mvars[k].CopyMatrix(div(firstmatrix,secondmatrix)); break;


}
}


}
std::string s="result";
vars[k]=s+to_string(k);
test.replace(x,y-x+1,vars[k]);
//std::cout<<test<<std::endl;



}
else{
double z=to_double(test.substr(x,a-x));
double k=to_double(test.substr(a+1,y-a));
double result;
switch(test[a]){
case '*': result=z*k; break;
case '/': result=z/k; break;

}
std::string replacement=to_string(result);
test.replace(x,y-x+1,replacement);
//std::cout<<test<<std::endl;
}
}
while((test.find('+')!=std::string::npos||test.find('-',1)!=std::string::npos)/*&&(test[0]!='-'||test.length()>10)*/){
int a=0;
for(unsigned int i=0;i<test.length();i++){
if((test[i]=='+'||test[i]=='-')&&i!=0){
a=i;
break;
}
}
int x=0;
int y=test.length()-1;
for(int i=a-1;i>=0;i--){
if(!((test[i]>='.'&&test[i]<='9')&&test[i]!='/')&&(!(test[i]>='a'&&test[i]<='z'))&&(!(test[i]>='A'&&test[i]<='Z'))&&test[0]!='-')
 {
x=i+1;
break;

}
}
for(unsigned int j=a+1;j<test.length();j++){
if(!((test[j]>='.'&&test[j]<='9')&&test[j]!='/')&&(!(test[j]>='a'&&test[j]<='z'))&&(!(test[j]>='A'&&test[j]<='Z'))){


y=j-1;
//
//cout<<y;
break;

}

}
std::string operand1;
std::string operand2;
if(test[a-1]=='.'){
 operand1=test.substr(x,a-x-1);
}
else{ operand1=test.substr(x,a-x);}
if(test[y]=='.'){
y-=1;
}


 operand2=test.substr(a+1,y-a);
//std::cout<<operand1<<std::endl;

//std::cout<<operand2<<std::endl;
if((!isdigit(operand1[0])||!isdigit(operand2[0]))&&operand1[0]!='-'){
asu::CMatrix firstmatrix;
asu::CMatrix secondmatrix;
double operand_double;
if(!isdigit(operand1[0])&&!isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,k);
secondmatrix=stringtomatrix(operand2,k);
k++;
//cout<<secondmatrix<<endl;
switch(test[a]){
case '+': mvars[k].CopyMatrix(add(firstmatrix,secondmatrix)); break;
case '-': mvars[k].CopyMatrix(sub(firstmatrix,secondmatrix)); break;

}
}
if(!isdigit(operand1[0])&&isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,k);
operand_double=to_double(operand2);
if(test[a-1]=='.'){
k++;
switch(test[a]){
case '+': mvars[k].CopyMatrix(add(firstmatrix,operand_double)); break;
case '-': mvars[k].CopyMatrix(sub(firstmatrix,operand_double)); break;

}

}
else{
secondmatrix=operand_double;
k++;
switch(test[a]){
case '+': mvars[k].CopyMatrix(add(firstmatrix,secondmatrix)); break;
case '-': mvars[k].CopyMatrix(sub(firstmatrix,secondmatrix)); break;


}
}


}

///
if(isdigit(operand1[0])&&!isdigit(operand2[0])){
operand_double=to_double(operand1);
secondmatrix=stringtomatrix(operand2,k);

if(test[a-1]=='.'){
k++;
switch(test[a]){
case '+': mvars[k].CopyMatrix(add(operand_double,secondmatrix)); break;
case '-': mvars[k].CopyMatrix(sub(operand_double,secondmatrix)); break;

}

}
else{
firstmatrix=operand_double;
k++;
switch(test[a]){
case '+': mvars[k].CopyMatrix(add(firstmatrix,secondmatrix)); break;
case '-': mvars[k].CopyMatrix(sub(firstmatrix,secondmatrix)); break;


}
}


}
std::string s="result";
vars[k]=s+to_string(k);
test.replace(x,y-x+1,vars[k]);
//std::cout<<test<<std::endl;



}
else{
double z=to_double(test.substr(x,a-x));
double k=to_double(test.substr(a+1,y-a));
double result;
switch(test[a]){
case '+': result=z+k; break;
case '-': result=z-k; break;

}
std::string replacement=to_string(result);
test.replace(x,y-x+1,replacement);
//std::cout<<test<<std::endl;
}

}
}

void parthen_analysis(std::string& test2){
while(test2.find('(')!=std::string::npos)
{
unsigned int x=0;
int y=test2.length()-1;
for(unsigned int i=0;i<test2.length();i++){
if(test2[i]=='(')
x=i;

}
for(unsigned int i=0;i<test2.length();i++){
if(test2[i]==')'&&i>x){
y=i;
break;
}
}

std::string expression=test2.substr(x+1,y-x-1);

math_piority_calc(expression);
test2.replace(x,y-x+1,expression);
//std::cout<<test2<<std::endl;

}

}

void mathematical_calc(std::string& a){
if(a.find("sin")!=std::string::npos){

int first_pos=a.find("sin");
int end_pos=a.find(')',first_pos);
std::string expression=a.substr(first_pos,end_pos-first_pos+1);
std::string operand_str=expression.substr(4,a.length()-4-1);
if(operand_str.find(')')!=std::string::npos){
operand_str.erase(operand_str.find(')'),1);
}
math_piority_calc(operand_str);
if(!isdigit(operand_str[0])){
asu::CMatrix firstmatrix=stringtomatrix(operand_str,k);
k++;
mvars[k]=sin(firstmatrix);
std::string s="result";
vars[k]=s+to_string(k);
a.replace(first_pos,end_pos-first_pos+1,vars[k]);



}
else{
char * buffer=new char[operand_str.length()+1];
strcpy(buffer,operand_str.c_str());
double operand=atof(buffer);
double result;
result=sin(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
a.replace(first_pos,end_pos-first_pos+1,(std::string)buffer_test);

delete [] buffer;

}
}
 if(a.find("cos")!=std::string::npos){
int first_pos=a.find("cos");
int end_pos=a.find(')',first_pos);
std::string expression=a.substr(first_pos,end_pos-first_pos+1);
std::string operand_str=expression.substr(4,a.length()-4-1);
if(operand_str.find(')')!=std::string::npos){
operand_str.erase(operand_str.find(')'),1);
}
math_piority_calc(operand_str);
if(!isdigit(operand_str[0])){
asu::CMatrix firstmatrix=stringtomatrix(operand_str,k);
k++;
mvars[k]=cos(firstmatrix);
std::string s="result";
vars[k]=s+to_string(k);
a.replace(first_pos,end_pos-first_pos+1,vars[k]);



}
else{
char * buffer=new char[operand_str.length()+1];
strcpy(buffer,operand_str.c_str());
double operand=atof(buffer);
double result=cos(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
a.replace(first_pos,end_pos-first_pos+1,(std::string)buffer_test);

delete [] buffer;
}



}
 if(a.find("tan")!=std::string::npos){
int first_pos=a.find("tan");
int end_pos=a.find(')',first_pos);
std::string expression=a.substr(first_pos,end_pos-first_pos+1);
std::string operand_str=expression.substr(4,a.length()-4-1);
if(operand_str.find(')')!=std::string::npos){
operand_str.erase(operand_str.find(')'),1);
}
math_piority_calc(operand_str);
if(!isdigit(operand_str[0])){
asu::CMatrix firstmatrix=stringtomatrix(operand_str,k);
k++;
mvars[k]=tan(firstmatrix);
std::string s="result";
vars[k]=s+to_string(k);
a.replace(first_pos,end_pos-first_pos+1,vars[k]);
}

else{
char * buffer=new char[operand_str.length()+1];
strcpy(buffer,operand_str.c_str());
double operand=atof(buffer);
double result=tan(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
a.replace(first_pos,end_pos-first_pos+1,(std::string)buffer_test);

delete [] buffer;
}

}
if(a.find("sqrt")!=std::string::npos){
int first_pos=a.find("sqrt");
int end_pos=a.find(')',first_pos);
std::string expression=a.substr(first_pos,end_pos-first_pos+1);
std::string operand_str=expression.substr(5,a.length()-5-1);
if(operand_str.find(')')!=std::string::npos){
operand_str.erase(operand_str.find(')'),1);
}
math_piority_calc(operand_str);
std::cout<<operand_str<<std::endl;
if(!isdigit(operand_str[0])){
asu::CMatrix firstmatrix=stringtomatrix(operand_str,k);
k++;
mvars[k]=sqrt(firstmatrix);
std::string s="result";
vars[k]=s+to_string(k);
a.replace(first_pos,end_pos-first_pos+1,vars[k]);



}
else{
char * buffer=new char[operand_str.length()+1];
strcpy(buffer,operand_str.c_str());
double operand=atof(buffer);
double result=sqrt(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
a.replace(first_pos,end_pos-first_pos+1,(std::string)buffer_test);

delete [] buffer;
}



}



}
 





int main(int argc, char** argv)
{

std::string sMatrix; //input line as string
vars=new std::string [100]; //matrices names in string ====  std::string vars[100];
mvars=new CMatrix[100]; //matrices values  ====  CMatrix mvars[100];
	

if (argc > 1) 	//if a filename is given
{ 
	for (int i = 1; i < argc; ++i) 
	{
		std::ifstream mfile(argv[i]);
		if (!mfile.is_open()) 
		{
			std::cerr << "Couldn't open " << argv[i] << std::endl;
			continue;
		}
		while (std::getline(mfile, sMatrix))
			
		{

			std::getline (std::cin,sMatrix);		
			sMatrix=removeSpaces(sMatrix);
			std::string matrixname="",wantedvalue="";	
			int endname = sMatrix.find('=');
			matrixname=sMatrix.substr(0,endname);

			std::string stringvalue=sMatrix.substr(endname+1, sMatrix.length()-endname-1);
			mathematical_calc(stringvalue);
			parthen_analysis(stringvalue);
			math_piority_calc(stringvalue);



			if (sMatrix.find('[')!=std::string::npos)
			{
				int startcalc= sMatrix.find('[');

				for(int i=startcalc; sMatrix[i]!='\0';i++) wantedvalue+=sMatrix[i];	
						
				vars[k]=matrixname; 
				mvars[k].CopyMatrix(wantedvalue);
				if ( sMatrix [sMatrix.find(']')+1]  !=';') std::cout<<mvars[k]<<std::endl;
			}

			else if(stringvalue[0]>='0' && stringvalue[0]<('9'+1))
			{
			
				mvars[k]=CMatrix( 1,1, to_double(stringvalue));
				if ( sMatrix.find(';')==std::string::npos) std::cout<<mvars[k]<<std::endl;
			}


			else
			{	
				mvars[k]=stringtomatrix(stringvalue,k);
				
				std::cout<<mvars[k]<<std::endl;

			}


				
			vars[k]=matrixname; 
			k++;


		}
			mfile.close();
	}
	
}


else // interactive prompt
{ 


	std::getline (std::cin,sMatrix);		
	sMatrix=removeSpaces(sMatrix);
	std::string matrixname="",wantedvalue="";	
	int endname = sMatrix.find('=');
	matrixname=sMatrix.substr(0,endname);

	std::string stringvalue=sMatrix.substr(endname+1, sMatrix.length()-endname-1);
	mathematical_calc(stringvalue);
	parthen_analysis(stringvalue);
	math_piority_calc(stringvalue);



	if (sMatrix.find('[')!=std::string::npos)
	{
		int startcalc= sMatrix.find('[');

		for(int i=startcalc; sMatrix[i]!='\0';i++) wantedvalue+=sMatrix[i];	
				
		vars[k]=matrixname; 
		mvars[k].CopyMatrix(wantedvalue);
		if ( sMatrix [sMatrix.find(']')+1]  !=';') std::cout<<mvars[k]<<std::endl;
	}

	else if(stringvalue[0]>='0' && stringvalue[0]<('9'+1))
	{
	
		mvars[k]=CMatrix( 1,1, to_double(stringvalue));
		if ( sMatrix.find(';')==std::string::npos) std::cout<<mvars[k]<<std::endl;
	}


	else
	{	
		mvars[k]=stringtomatrix(stringvalue,k);
		
		std::cout<<mvars[k]<<std::endl;

	}


			
	vars[k]=matrixname; 
	k++;
	
}


	delete[]mvars;
	delete[]vars;

	return 0;
}

