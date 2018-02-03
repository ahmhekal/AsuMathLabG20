#include <iostream>
#include <string>
#include "math.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>
#include "matrix.h"
#include "functions.h"
using namespace std;
extern int numberofmatrixVariables;
extern std::string* matrixNames; 
extern asu::CMatrix* matrixVariables;
/**parns_are_incomplete function it takes string and return true if open brackets is more than closed brackets
and returns false otherwise */
bool parens_are_incomplete(std::string matrix_string)
{
  unsigned int open_counter = 0 , close_counter=0 ; 
   
  for (unsigned int i=0 ; i<matrix_string.length() ; i++)
     {
       if(matrix_string[i] == '[') 
          open_counter++;
       if(matrix_string[i] == ']')
          close_counter++;
     }
  
  if (open_counter > close_counter )
      return true ;
  else return false ;

}
std::string removeSpaces(std::string input)   //remove spaces from the beginning to '[' or the end of the line
{
  //int length = input.length();
	if (input == "\n" || input == "" ) return "";
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
		if(matrixNames[i]==s) return matrixVariables[i];
	}
	if(i<=0) throw std::invalid_argument("Impossible variable name");
	asu::CMatrix nomatrix; return nomatrix ;
}
std::string to_string(double operand){
char buffer_test[50];
sprintf(buffer_test,"%lf",operand);
return(std::string)buffer_test;
}
double to_double(std::string operand){
char * buffer=new char[operand.length()+1];
strcpy(buffer,operand.c_str());
double result=atof(buffer);
delete [] buffer;
return result;

}
/*this function is responsable for calcualating any expression containing any basic operations
like power,mul,div,add,sub,neg on numbers or matrices using piorities.
arguments:the expression that needs to be calculated and it is passed by reference to append in it 
return:void
*/

void basicOperationCalculation(std::string& expression){
int count=0;//number of temporary matrix variables 
//searching for any operation contains power operator.
while(expression.find('^')!=std::string::npos){

unsigned int operatorPosition=0;//position of operator 
//determining the position of the operator 
for(unsigned int i=0;i<expression.length();i++){
if(expression[i]=='^'){
operatorPosition=i;
break;

}
}
//if the operator at the end of the expression ,it throws expection 
if(operatorPosition==expression.length()-1){
throw std::invalid_argument
		    ("Syntax Error");

}

int startPosition=0;//the position of the first char in the operation 
int endPosition=expression.length()-1;//the position of the last char in the operation 
//determining the position of the first char in the operation 
for(int i=operatorPosition-1;i>=0;i--){
if(!((expression[i]>='.'&&expression[i]<='9')&&expression[i]!='/')&&(!(expression[i]>='a'&&expression[i]<='z'))&&(!(expression[i]>='A'&&expression[i]<='Z')))
 {
startPosition=i+1;
break;

}
}
//determining the position of the last char in the operation 
for(unsigned int j=operatorPosition+1;j<expression.length();j++){
if(!((expression[j]>='.'&&expression[j]<='9')&&expression[j]!='/')&&(!(expression[j]>='a'&&expression[j]<='z'))&&(!(expression[j]>='A'&&expression[j]<='Z'))&&(expression[operatorPosition+1]!='-'||j!=operatorPosition+1)){


endPosition=j-1;
//

break;

}

}

std::string operand1;//the first operand in the operation 
std::string operand2;//the second operand in the operation 

if(expression[operatorPosition-1]=='.'){
	//extract the first operand in case of elementwise operation
 operand1=expression.substr(startPosition,operatorPosition-startPosition-1);
}
else{
	//extract the first operand
 operand1=expression.substr(startPosition,operatorPosition-startPosition);
}


 operand2=expression.substr(operatorPosition+1,endPosition-operatorPosition);//extract the second operand
 //incase of the operands are matrices 
if((!isdigit(operand1[0])||!isdigit(operand2[0]))&&operand1[0]!='-'&&operand2[0]!='-'){
double powerValue=to_double(operand2);
asu::CMatrix resultMatrix ;
if(expression[operatorPosition-1]=='.'){
	//elementwise operation
  resultMatrix =power_modified_elementwise(stringtomatrix(operand1,numberofmatrixVariables),powerValue);
}
else{//normal operation
 resultMatrix =power_modified(stringtomatrix(operand1,numberofmatrixVariables),powerValue);}


count++;
numberofmatrixVariables++;
matrixVariables[numberofmatrixVariables]=resultMatrix;//saving the result in the array of matrices 
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);//saving the name of resulting matrices 
expression.replace(startPosition,endPosition-startPosition+1,matrixNames[numberofmatrixVariables]);//appending the expression with the result


}
else{
double operand_double=to_double(expression.substr(startPosition,operatorPosition-startPosition));
double power=to_double(expression.substr(operatorPosition+1,endPosition-operatorPosition));


double result=pow(operand_double,power);

std::string replacement=to_string(result);
expression.replace(startPosition,endPosition-startPosition+1,replacement);


}
 }
 while(expression.find('*')!=std::string::npos||expression.find('/')!=std::string::npos){
unsigned int operatorPosition=0;
for(unsigned int i=0;i<expression.length();i++){
if(expression[i]=='*'||expression[i]=='/'){
operatorPosition=i;
break;
}
}
if(operatorPosition==expression.length()-1){
throw std::invalid_argument
		    ("Syntax Error");

}

int startPosition=0;
int endPosition=expression.length()-1;
//&&expression[0]!='-'
for(int i=operatorPosition-1;i>=0;i--){
if(!((expression[i]>='.'&&expression[i]<='9')&&expression[i]!='/')&&(!(expression[i]>='a'&&expression[i]<='z'))&&(!(expression[i]>='A'&&expression[i]<='Z')))
 {
startPosition=i+1;
break;

}
}
if(startPosition==1&&expression[0]=='-')
{
startPosition=0;
}
for(unsigned int j=operatorPosition+1;j<expression.length();j++){
if(!((expression[j]>='.'&&expression[j]<='9')&&expression[j]!='/')&&(!(expression[j]>='a'&&expression[j]<='z'))&&(!(expression[j]>='A'&&expression[j]<='Z'))&&(expression[operatorPosition+1]!='-'||j!=operatorPosition+1)){


endPosition=j-1;
//

break;

}

}
std::string operand1;
std::string operand2;
if(expression[operatorPosition-1]=='.'){
 operand1=expression.substr(startPosition,operatorPosition-startPosition-1);
}
else{ operand1=expression.substr(startPosition,operatorPosition-startPosition);}
if(expression[endPosition]=='.'){
endPosition-=1;
}


 operand2=expression.substr(operatorPosition+1,endPosition-operatorPosition);
 if(operand1[0]=='-'&&(!isdigit(operand1[1]))){
double negative=-1;
numberofmatrixVariables++;
matrixVariables[numberofmatrixVariables].CopyMatrix(amul(stringtomatrix(operand1.substr(1,operand1.length()-1),numberofmatrixVariables),negative));
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
operand1=matrixNames[numberofmatrixVariables];

}
if(operand2[0]=='-'&&(!isdigit(operand2[1]))){
double negative=-1;
numberofmatrixVariables++;
matrixVariables[numberofmatrixVariables].CopyMatrix(amul(stringtomatrix(operand2.substr(1,operand2.length()-1),numberofmatrixVariables),negative));
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
operand2=matrixNames[numberofmatrixVariables];

}
 if(operand2=="0"&&expression[operatorPosition]=='/')
    throw std::invalid_argument
		    ("Division by Zero");

if((!isdigit(operand1[0])||!isdigit(operand2[0]))&&operand1[0]!='-'&&operand2[0]!='-'){
asu::CMatrix firstmatrix;
asu::CMatrix secondmatrix;
double operand_double;
if(!isdigit(operand1[0])&&!isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,numberofmatrixVariables);
secondmatrix=stringtomatrix(operand2,numberofmatrixVariables);
if(expression[operatorPosition-1]=='.'){
numberofmatrixVariables++;
switch(expression[operatorPosition]){
case '*': matrixVariables[numberofmatrixVariables].CopyMatrix(amul(firstmatrix,secondmatrix)); break;
case '/': matrixVariables[numberofmatrixVariables].CopyMatrix(adiv(firstmatrix,secondmatrix)); break;

}
}
else{
numberofmatrixVariables++;
switch(expression[operatorPosition]){
case '*': matrixVariables[numberofmatrixVariables].CopyMatrix(mul(firstmatrix,secondmatrix)); break;
case '/': matrixVariables[numberofmatrixVariables].CopyMatrix(div(firstmatrix,secondmatrix)); break;


}
}
}
if(!isdigit(operand1[0])&&isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,numberofmatrixVariables);
operand_double=to_double(operand2);
if(expression[operatorPosition-1]=='.'){
numberofmatrixVariables++;
switch(expression[operatorPosition]){
case '*': matrixVariables[numberofmatrixVariables].CopyMatrix(amul(firstmatrix,operand_double)); break;
case '/': matrixVariables[numberofmatrixVariables].CopyMatrix(adiv(firstmatrix,operand_double)); break;

}

}
else{
secondmatrix=operand_double;
numberofmatrixVariables++;
switch(expression[operatorPosition]){
case '*': matrixVariables[numberofmatrixVariables].CopyMatrix(mul(firstmatrix,secondmatrix)); break;
case '/': matrixVariables[numberofmatrixVariables].CopyMatrix(div(firstmatrix,secondmatrix)); break;


}
}


}

///
if(isdigit(operand1[0])&&!isdigit(operand2[0])){
operand_double=to_double(operand1);
secondmatrix=stringtomatrix(operand2,numberofmatrixVariables);

if(expression[operatorPosition-1]=='.'){
numberofmatrixVariables++;
switch(expression[operatorPosition]){
case '*': matrixVariables[numberofmatrixVariables].CopyMatrix(amul(operand_double,secondmatrix)); break;
case '/': matrixVariables[numberofmatrixVariables].CopyMatrix(adiv(operand_double,secondmatrix)); break;

}

}
else{
firstmatrix=operand_double;
numberofmatrixVariables++;
switch(expression[operatorPosition]){
case '*': matrixVariables[numberofmatrixVariables].CopyMatrix(mul(firstmatrix,secondmatrix)); break;
case '/': matrixVariables[numberofmatrixVariables].CopyMatrix(div(firstmatrix,secondmatrix)); break;


}
}


}
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
expression.replace(startPosition,endPosition-startPosition+1,matrixNames[numberofmatrixVariables]);




}
else{
double operand1_double=to_double(expression.substr(startPosition,operatorPosition-startPosition));
double operand2_double=to_double(expression.substr(operatorPosition+1,endPosition-operatorPosition));
double result;
switch(expression[operatorPosition]){
case '*': result=operand1_double*operand2_double; break;
case '/': result=operand1_double/operand2_double; break;

}
std::string replacement=to_string(result);
expression.replace(startPosition,endPosition-startPosition+1,replacement);

}
}
int flag=0;
while((expression.find('+')!=std::string::npos||expression.find('-',flag+1)!=std::string::npos)/*&&(expression[0]!='-'||expression.length()>10)*/){
unsigned int operatorPosition=0;
for(unsigned int i=flag;i<expression.length();i++){
if((expression[i]=='+'||expression[i]=='-')&&i!=0){
operatorPosition=i;
break;
}
}

if(operatorPosition==expression.length()-1){
throw std::invalid_argument
		    ("Syntax Error");

}

int startPosition=0;
int endPosition=expression.length()-1;
for(int i=operatorPosition-1;i>=0;i--){
if(!((expression[i]>='.'&&expression[i]<='9')&&expression[i]!='/')&&(!(expression[i]>='a'&&expression[i]<='z'))&&(!(expression[i]>='A'&&expression[i]<='Z')))
 {
startPosition=i+1;
break;

}
}
if(startPosition==1&&expression[0]=='-')
{
startPosition=0;
}
for(unsigned int j=operatorPosition+1;j<expression.length();j++){
if(!((expression[j]>='.'&&expression[j]<='9')&&expression[j]!='/')&&(!(expression[j]>='a'&&expression[j]<='z'))&&(!(expression[j]>='A'&&expression[j]<='Z'))&&(expression[operatorPosition+1]!='-'||j!=operatorPosition+1)){


endPosition=j-1;
//

break;

}

}
std::string operand1;
std::string operand2;
if(expression[operatorPosition-1]=='.'){
 operand1=expression.substr(startPosition,operatorPosition-startPosition-1);
}
else{ operand1=expression.substr(startPosition,operatorPosition-startPosition);}
if(expression[endPosition]=='.'){
endPosition-=1;
}
if(expression[operatorPosition-1]==' '||expression[operatorPosition-1]==';'||expression[operatorPosition-1]=='['){
int index;
for(int i=operatorPosition;i<expression.length();i++){
if(expression[i]==' '||expression[i]==']' ||expression[i]==';'){index=i-1; break;}
}
std::string matrixElement=expression.substr(operatorPosition,index-operatorPosition+1);
basicOperationCalculation(matrixElement);
expression.replace(operatorPosition,expression.substr(operatorPosition,index-operatorPosition+1).length(),matrixElement);
flag=operatorPosition+1;
continue;
}





 operand2=expression.substr(operatorPosition+1,endPosition-operatorPosition);
if(operand1[0]=='-'&&(!isdigit(operand1[1]))){
double negative=-1;
numberofmatrixVariables++;
matrixVariables[numberofmatrixVariables].CopyMatrix(amul(stringtomatrix(operand1.substr(1,operand1.length()-1),numberofmatrixVariables),negative));
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
operand1=matrixNames[numberofmatrixVariables];

}
if(operand2[0]=='-'&&(!isdigit(operand2[1]))){
double negative=-1;
numberofmatrixVariables++;
matrixVariables[numberofmatrixVariables].CopyMatrix(amul(stringtomatrix(operand2.substr(1,operand2.length()-1),numberofmatrixVariables),negative));
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
operand2=matrixNames[numberofmatrixVariables];

}
if((!isdigit(operand1[0])||!isdigit(operand2[0]))&&operand1[0]!='-'&&operand2[0]!='-'){
asu::CMatrix firstmatrix;
asu::CMatrix secondmatrix;
double operand_double;
if(!isdigit(operand1[0])&&!isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,numberofmatrixVariables);
secondmatrix=stringtomatrix(operand2,numberofmatrixVariables);
numberofmatrixVariables++;

switch(expression[operatorPosition]){
case '+': matrixVariables[numberofmatrixVariables].CopyMatrix(add(firstmatrix,secondmatrix)); break;
case '-': matrixVariables[numberofmatrixVariables].CopyMatrix(sub(firstmatrix,secondmatrix)); break;

}
}
if((!isdigit(operand1[0]))&&((isdigit(operand2[0]))||(isdigit(operand2[1])&&operand2[0]=='-'))){
	 
firstmatrix=stringtomatrix(operand1,numberofmatrixVariables);
operand_double=to_double(operand2);
if(expression[operatorPosition-1]=='.'){
numberofmatrixVariables++;
switch(expression[operatorPosition]){
case '+': matrixVariables[numberofmatrixVariables].CopyMatrix(add(firstmatrix,operand_double)); break;
case '-': matrixVariables[numberofmatrixVariables].CopyMatrix(sub(firstmatrix,operand_double)); break;

}

}
else{
secondmatrix=operand_double;
numberofmatrixVariables++;
switch(expression[operatorPosition]){
case '+': matrixVariables[numberofmatrixVariables].CopyMatrix(add(firstmatrix,secondmatrix)); break;
case '-': matrixVariables[numberofmatrixVariables].CopyMatrix(sub(firstmatrix,secondmatrix)); break;


}
}


}

///
if((isdigit(operand1[0])||(isdigit(operand1[1])&&operand1[0]=='-'))&&!isdigit(operand2[0])){

operand_double=to_double(operand1);
secondmatrix=stringtomatrix(operand2,numberofmatrixVariables);

if(expression[operatorPosition-1]=='.'){
numberofmatrixVariables++;
switch(expression[operatorPosition]){
case '+': matrixVariables[numberofmatrixVariables].CopyMatrix(add(operand_double,secondmatrix)); break;
case '-': matrixVariables[numberofmatrixVariables].CopyMatrix(sub(operand_double,secondmatrix)); break;

}

}
else{
firstmatrix=operand_double;
numberofmatrixVariables++;
switch(expression[operatorPosition]){
case '+': matrixVariables[numberofmatrixVariables].CopyMatrix(add(firstmatrix,secondmatrix)); break;
case '-': matrixVariables[numberofmatrixVariables].CopyMatrix(sub(firstmatrix,secondmatrix)); break;


}
}


}
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
expression.replace(startPosition,endPosition-startPosition+1,matrixNames[numberofmatrixVariables]);



}
else{
double operand1_double=to_double(expression.substr(startPosition,operatorPosition-startPosition));
double operand2_double=to_double(expression.substr(operatorPosition+1,endPosition-operatorPosition));
double result;
switch(expression[operatorPosition]){
case '+': result=operand1_double+operand2_double; break;
case '-': result=operand1_double-operand2_double; break;

}
std::string replacement=to_string(result);
expression.replace(startPosition,endPosition-startPosition+1,replacement);

}

}
if(expression[0]=='-'&&(!isdigit(expression[1]))){
double negative=-1;
numberofmatrixVariables++;
matrixVariables[numberofmatrixVariables].CopyMatrix(amul(stringtomatrix(expression.substr(1,expression.length()-1),numberofmatrixVariables),negative));
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
expression=matrixNames[numberofmatrixVariables];

}


}
 
/*
this function is responsable for determining the parthensis and calculating the expressions inside it 
it takes care of piorities 
arguments:the expression and it is passed by reference to append in it 
*/

void parthen_analysis(std::string& expression){
	//searching for opening bracket until it finds no brackets
while(expression.find('(')!=std::string::npos)
{
	//checking that there is no syntax errors by comparing the number of opening brackets and closing brackets
	unsigned int openBracket_counter = 0 , closeBracket_counter=0 ;

  for (unsigned int i=0 ; i<expression.length() ; i++)
     {
       if(expression[i] == '(')
         openBracket_counter ++;
       if(expression[i] == ')')
         closeBracket_counter++;
     }

  if (openBracket_counter  > closeBracket_counter )
  throw std::invalid_argument
		    ("Syntax Error");
unsigned int openingBracket=0;//position of first bracket
int closingBracket=expression.length()-1;//position of closing bracket
//finding the positions of opening and closing brackets
for(unsigned int i=0;i<expression.length();i++){
if(expression[i]=='(')
openingBracket=i;

}
for(unsigned int i=0;i<expression.length();i++){
if(expression[i]==')'&&i>openingBracket){
closingBracket=i;
break;
}
}

std::string insideBrackets=expression.substr(openingBracket+1,closingBracket-openingBracket-1);//expression inside brackets

basicOperationCalculation(insideBrackets);//calculation the expression inside brackets
expression.replace(openingBracket,closingBracket-openingBracket+1,insideBrackets);//replacing the result of the expression in the original expression


}

}/*
this function is resposable for searching for trignometric and sqrt expression and calculating it and append the result in the expression 
arguments:the expression and it is passed by reference to append in it 

*/

void functionsCalculation(std::string& expression){
	//if the expression is sin or cos,... only it throws exception
	if(expression=="sin"||expression=="cos"||expression=="tan"||expression=="sqrt")
throw std::invalid_argument("error using " + expression + "\n not enough input arguments");
	
//searching for sin in the expression
while(expression.find("sin")!=std::string::npos){

int first_pos=expression.find("sin");//position of first occurence of sin in the string
int end_pos=expression.find(')',first_pos);//position of the end of sin expression
std::string function=expression.substr(first_pos,end_pos-first_pos+1);//extraction the function that needed to be calculated
std::string expressionInsideFunction=function.substr(4,expression.length()-4-1);//extracting the expression inside the function
//erasing any brackets found in the expression
if(expressionInsideFunction.find(')')!=std::string::npos){
expressionInsideFunction.erase(expressionInsideFunction.find(')'),1);
}
basicOperationCalculation(expressionInsideFunction);//calculating the expression inside the function
//if the expression was a matrix expression
if(!isdigit(expressionInsideFunction[0])){
asu::CMatrix firstmatrix=stringtomatrix(expressionInsideFunction,numberofmatrixVariables);//getting the matrix variable inside the function
numberofmatrixVariables++;//increasing the number of matrix varibales to save the result
matrixVariables[numberofmatrixVariables]=sin(firstmatrix);
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
expression.replace(first_pos,end_pos-first_pos+1,matrixNames[numberofmatrixVariables]);//replacing the name of resulting matrix in the original matrix



}
//if the expression was a number
else{
char * buffer=new char[expressionInsideFunction.length()+1];//creating a char array to have the number
strcpy(buffer,expressionInsideFunction.c_str());//copying the number to the char array
double operand=atof(buffer);//getting the operand by converting it into double to be able to calculate the required function
double result;//result of the required function
result=sin(operand);
char buffer_test[50];//char array to save the result 
sprintf(buffer_test,"%g",result);
expression.replace(first_pos,end_pos-first_pos+1,(std::string)buffer_test);//replacing the function with the result

delete [] buffer;

}
}
/////////////////////////the same steps was explainded prevouisly in the part of finding sin //////////////////////////////////////
 while(expression.find("cos")!=std::string::npos){
int first_pos=expression.find("cos");
int end_pos=expression.find(')',first_pos);
std::string function=expression.substr(first_pos,end_pos-first_pos+1);
std::string expressionInsideFunction=function.substr(4,expression.length()-4-1);
if(expressionInsideFunction.find(')')!=std::string::npos){
expressionInsideFunction.erase(expressionInsideFunction.find(')'),1);
}
basicOperationCalculation(expressionInsideFunction);
if(!isdigit(expressionInsideFunction[0])){
asu::CMatrix firstmatrix=stringtomatrix(expressionInsideFunction,numberofmatrixVariables);
numberofmatrixVariables++;
matrixVariables[numberofmatrixVariables]=cos(firstmatrix);
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
expression.replace(first_pos,end_pos-first_pos+1,matrixNames[numberofmatrixVariables]);



}
else{
char * buffer=new char[expressionInsideFunction.length()+1];
strcpy(buffer,expressionInsideFunction.c_str());
double operand=atof(buffer);
double result=cos(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
expression.replace(first_pos,end_pos-first_pos+1,(std::string)buffer_test);

delete [] buffer;
}



}
 while(expression.find("tan")!=std::string::npos){
int first_pos=expression.find("tan");
int end_pos=expression.find(')',first_pos);
std::string function=expression.substr(first_pos,end_pos-first_pos+1);
std::string expressionInsideFunction=function.substr(4,expression.length()-4-1);
if(expressionInsideFunction.find(')')!=std::string::npos){
expressionInsideFunction.erase(expressionInsideFunction.find(')'),1);
}
basicOperationCalculation(expressionInsideFunction);
if(!isdigit(expressionInsideFunction[0])){
asu::CMatrix firstmatrix=stringtomatrix(expressionInsideFunction,numberofmatrixVariables);
numberofmatrixVariables++;
matrixVariables[numberofmatrixVariables]=tan(firstmatrix);
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
expression.replace(first_pos,end_pos-first_pos+1,matrixNames[numberofmatrixVariables]);
}

else{
char * buffer=new char[expressionInsideFunction.length()+1];
strcpy(buffer,expressionInsideFunction.c_str());
double operand=atof(buffer);
double result=tan(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
expression.replace(first_pos,end_pos-first_pos+1,(std::string)buffer_test);

delete [] buffer;
}

}
while(expression.find("sqrt")!=std::string::npos){
int first_pos=expression.find("sqrt");
int end_pos=expression.find(')',first_pos);
std::string function=expression.substr(first_pos,end_pos-first_pos+1);
std::string expressionInsideFunction=function.substr(5,expression.length()-5-1);
if(expressionInsideFunction.find(')')!=std::string::npos){
expressionInsideFunction.erase(expressionInsideFunction.find(')'),1);
}
basicOperationCalculation(expressionInsideFunction);

if(!isdigit(expressionInsideFunction[0])){
asu::CMatrix firstmatrix=stringtomatrix(expressionInsideFunction,numberofmatrixVariables);
numberofmatrixVariables++;
matrixVariables[numberofmatrixVariables]=sqrt(firstmatrix);
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
expression.replace(first_pos,end_pos-first_pos+1,matrixNames[numberofmatrixVariables]);



}
else{
char * buffer=new char[expressionInsideFunction.length()+1];
strcpy(buffer,expressionInsideFunction.c_str());
double operand=atof(buffer);
double result=sqrt(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
expression.replace(first_pos,end_pos-first_pos+1,(std::string)buffer_test);

delete [] buffer;
}



}


}

/*this function is resposable for stroring a matrix line in a CMatrix variable 
arguments:matrix line with concatination brackets
return type:CMatrix varibale 
*/
asu::CMatrix concatinationCalculation(std::string s ){
asu::CMatrix r;
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
asu::CMatrix row;
char* context;
char separators[4];
separators[0] = ' ';
separators[1] = '[';
separators[2] = ']';
separators[3] = ',';
char* token = strtok_r(line, separators, &context);
while(token)
{
if(!isdigit(token[0])&&token[0]!='-'){
row.addColumn(stringtomatrix(token,numberofmatrixVariables));
}
else{
asu::CMatrix item = atof(token);
row.addColumn(item);}
token = strtok_r(NULL, separators, &context);
}

if (row.getnColumns() > 0 && (row.getnColumns() == r.getnColumns() || r.getnRows() == 0)){
r.addRow(row);

}
else{
throw std::invalid_argument
		    ("Invalid matrix dimensions");
}




line = strtok_r(NULL, lineSeparators, &lineContext);
}
delete[] buffer;
return r;

}
/*
this function responsable for handling concatination process and replacing any matrix brackets with 
a n
*/
void concatinationAnalysis(std::string& expression){
	//checking that there is no syntax errors by comparing the number of opening brackets and closing concatination brackets
while(expression.find('[',1)!=std::string::npos)
{
unsigned int startPosition=0;//postion of opening bracket
int endPosition=expression.length()-1;//postion of closing bracket
//searching for opening and closing brackets 
for(unsigned int i=0;i<expression.length();i++){
if(expression[i]=='[')
startPosition=i;

}
for(unsigned int i=0;i<expression.length()-1;i++){
if(expression[i]==']'&&i>startPosition){
endPosition=i;
break;
}
}

std::string insideBrackets=expression.substr(startPosition+1,endPosition-startPosition-1);//expression inside brackets
numberofmatrixVariables++;
matrixVariables[numberofmatrixVariables]=concatinationCalculation(insideBrackets);//getting a matrix variable of the expression inside brackets
std::string s="result";
matrixNames[numberofmatrixVariables]=s+to_string(numberofmatrixVariables);
expression.replace(startPosition,endPosition-startPosition+1,matrixNames[numberofmatrixVariables]);//replacing these brackets by a name refered to the resulting matrix 

}
}
