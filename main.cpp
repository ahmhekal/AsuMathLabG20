#include <fstream>
#include "string"
#include "matrix.h"
#include <stdlib.h>  
#include "functions.h"
#include "math.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <streambuf>
using namespace asu;

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

 


std::string* vars; //matrices names in string ====  std::string vars[100];
CMatrix* mvars;   //matrices values  ====  CMatrix mvars[100];
int k=0; //matrix index (global variable)
void concatinationAnalysis(std::string& test2);
CMatrix concatinationCalculation(std::string s );

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
		if(vars[i]==s) return mvars[i];
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
  resultMatrix =power_modified_elementwise(stringtomatrix(operand1,k),powerValue);
}
else{//normal operation
 resultMatrix =power_modified(stringtomatrix(operand1,k),powerValue);}


count++;
k++;
mvars[k]=resultMatrix;//saving the result in the array of matrices 
std::string s="result";
vars[k]=s+to_string(k);//saving the name of resulting matrices 
expression.replace(startPosition,endPosition-startPosition+1,vars[k]);//appending the expression with the result


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
k++;
mvars[k].CopyMatrix(amul(stringtomatrix(operand1.substr(1,operand1.length()-1),k),negative));
std::string s="result";
vars[k]=s+to_string(k);
operand1=vars[k];

}
if(operand2[0]=='-'&&(!isdigit(operand2[1]))){
double negative=-1;
k++;
mvars[k].CopyMatrix(amul(stringtomatrix(operand2.substr(1,operand2.length()-1),k),negative));
std::string s="result";
vars[k]=s+to_string(k);
operand2=vars[k];

}
 if(operand2=="0"&&expression[operatorPosition]=='/')
    throw std::invalid_argument
		    ("Division by Zero");

if((!isdigit(operand1[0])||!isdigit(operand2[0]))&&operand1[0]!='-'&&operand2[0]!='-'){
asu::CMatrix firstmatrix;
asu::CMatrix secondmatrix;
double operand_double;
if(!isdigit(operand1[0])&&!isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,k);
secondmatrix=stringtomatrix(operand2,k);
if(expression[operatorPosition-1]=='.'){
k++;
switch(expression[operatorPosition]){
case '*': mvars[k].CopyMatrix(amul(firstmatrix,secondmatrix)); break;
case '/': mvars[k].CopyMatrix(adiv(firstmatrix,secondmatrix)); break;

}
}
else{
k++;
switch(expression[operatorPosition]){
case '*': mvars[k].CopyMatrix(mul(firstmatrix,secondmatrix)); break;
case '/': mvars[k].CopyMatrix(div(firstmatrix,secondmatrix)); break;


}
}
}
if(!isdigit(operand1[0])&&isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,k);
operand_double=to_double(operand2);
if(expression[operatorPosition-1]=='.'){
k++;
switch(expression[operatorPosition]){
case '*': mvars[k].CopyMatrix(amul(firstmatrix,operand_double)); break;
case '/': mvars[k].CopyMatrix(adiv(firstmatrix,operand_double)); break;

}

}
else{
secondmatrix=operand_double;
k++;
switch(expression[operatorPosition]){
case '*': mvars[k].CopyMatrix(mul(firstmatrix,secondmatrix)); break;
case '/': mvars[k].CopyMatrix(div(firstmatrix,secondmatrix)); break;


}
}


}

///
if(isdigit(operand1[0])&&!isdigit(operand2[0])){
operand_double=to_double(operand1);
secondmatrix=stringtomatrix(operand2,k);

if(expression[operatorPosition-1]=='.'){
k++;
switch(expression[operatorPosition]){
case '*': mvars[k].CopyMatrix(amul(operand_double,secondmatrix)); break;
case '/': mvars[k].CopyMatrix(adiv(operand_double,secondmatrix)); break;

}

}
else{
firstmatrix=operand_double;
k++;
switch(expression[operatorPosition]){
case '*': mvars[k].CopyMatrix(mul(firstmatrix,secondmatrix)); break;
case '/': mvars[k].CopyMatrix(div(firstmatrix,secondmatrix)); break;


}
}


}
std::string s="result";
vars[k]=s+to_string(k);
expression.replace(startPosition,endPosition-startPosition+1,vars[k]);




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
k++;
mvars[k].CopyMatrix(amul(stringtomatrix(operand1.substr(1,operand1.length()-1),k),negative));
std::string s="result";
vars[k]=s+to_string(k);
operand1=vars[k];

}
if(operand2[0]=='-'&&(!isdigit(operand2[1]))){
double negative=-1;
k++;
mvars[k].CopyMatrix(amul(stringtomatrix(operand2.substr(1,operand2.length()-1),k),negative));
std::string s="result";
vars[k]=s+to_string(k);
operand2=vars[k];

}
if((!isdigit(operand1[0])||!isdigit(operand2[0]))&&operand1[0]!='-'&&operand2[0]!='-'){
asu::CMatrix firstmatrix;
asu::CMatrix secondmatrix;
double operand_double;
if(!isdigit(operand1[0])&&!isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,k);
secondmatrix=stringtomatrix(operand2,k);
k++;

switch(expression[operatorPosition]){
case '+': mvars[k].CopyMatrix(add(firstmatrix,secondmatrix)); break;
case '-': mvars[k].CopyMatrix(sub(firstmatrix,secondmatrix)); break;

}
}
if((!isdigit(operand1[0]))&&((isdigit(operand2[0]))||(isdigit(operand2[1])&&operand2[0]=='-'))){
	 
firstmatrix=stringtomatrix(operand1,k);
operand_double=to_double(operand2);
if(expression[operatorPosition-1]=='.'){
k++;
switch(expression[operatorPosition]){
case '+': mvars[k].CopyMatrix(add(firstmatrix,operand_double)); break;
case '-': mvars[k].CopyMatrix(sub(firstmatrix,operand_double)); break;

}

}
else{
secondmatrix=operand_double;
k++;
switch(expression[operatorPosition]){
case '+': mvars[k].CopyMatrix(add(firstmatrix,secondmatrix)); break;
case '-': mvars[k].CopyMatrix(sub(firstmatrix,secondmatrix)); break;


}
}


}

///
if((isdigit(operand1[0])||(isdigit(operand1[1])&&operand1[0]=='-'))&&!isdigit(operand2[0])){

operand_double=to_double(operand1);
secondmatrix=stringtomatrix(operand2,k);

if(expression[operatorPosition-1]=='.'){
k++;
switch(expression[operatorPosition]){
case '+': mvars[k].CopyMatrix(add(operand_double,secondmatrix)); break;
case '-': mvars[k].CopyMatrix(sub(operand_double,secondmatrix)); break;

}

}
else{
firstmatrix=operand_double;
k++;
switch(expression[operatorPosition]){
case '+': mvars[k].CopyMatrix(add(firstmatrix,secondmatrix)); break;
case '-': mvars[k].CopyMatrix(sub(firstmatrix,secondmatrix)); break;


}
}


}
std::string s="result";
vars[k]=s+to_string(k);
expression.replace(startPosition,endPosition-startPosition+1,vars[k]);



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
k++;
mvars[k].CopyMatrix(amul(stringtomatrix(expression.substr(1,expression.length()-1),k),negative));
std::string s="result";
vars[k]=s+to_string(k);
expression=vars[k];

}


}
 
/*
this function is responsable for determining the parthensis and calculating the expressions inside it 
it takes care of piorities 
arguments:the expression and it is passed by reference to append in it 
*/

void parthen_analysis(std::string& expression){
while(expression.find('(')!=std::string::npos)
{
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
unsigned int openingBracket=0;
int closingBracket=expression.length()-1;
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

std::string insideBrackets=expression.substr(openingBracket+1,closingBracket-openingBracket-1);

basicOperationCalculation(insideBrackets);
expression.replace(openingBracket,closingBracket-openingBracket+1,insideBrackets);


}

}/*
this function is resposable for searching for trignometric and sqrt expression and calculating it and append the result in the expression 
arguments:the expression and it is passed by reference to append in it 

*/

void functionsCalculation(std::string& expression){
	if(expression=="sin"||expression=="cos"||expression=="tan"||expression=="sqrt")
throw std::invalid_argument("error using " + expression + "\n not enough input arguments");
	

while(expression.find("sin")!=std::string::npos){

int first_pos=expression.find("sin");
int end_pos=expression.find(')',first_pos);
std::string function=expression.substr(first_pos,end_pos-first_pos+1);
std::string expressionInsideFunction=function.substr(4,expression.length()-4-1);
if(expressionInsideFunction.find(')')!=std::string::npos){
expressionInsideFunction.erase(expressionInsideFunction.find(')'),1);
}
basicOperationCalculation(expressionInsideFunction);
if(!isdigit(expressionInsideFunction[0])){
asu::CMatrix firstmatrix=stringtomatrix(expressionInsideFunction,k);
k++;
mvars[k]=sin(firstmatrix);
std::string s="result";
vars[k]=s+to_string(k);
expression.replace(first_pos,end_pos-first_pos+1,vars[k]);



}
else{
char * buffer=new char[expressionInsideFunction.length()+1];
strcpy(buffer,expressionInsideFunction.c_str());
double operand=atof(buffer);
double result;
result=sin(operand);
char buffer_test[50];
sprintf(buffer_test,"%g",result);
expression.replace(first_pos,end_pos-first_pos+1,(std::string)buffer_test);

delete [] buffer;

}
}
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
asu::CMatrix firstmatrix=stringtomatrix(expressionInsideFunction,k);
k++;
mvars[k]=cos(firstmatrix);
std::string s="result";
vars[k]=s+to_string(k);
expression.replace(first_pos,end_pos-first_pos+1,vars[k]);



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
asu::CMatrix firstmatrix=stringtomatrix(expressionInsideFunction,k);
k++;
mvars[k]=tan(firstmatrix);
std::string s="result";
vars[k]=s+to_string(k);
expression.replace(first_pos,end_pos-first_pos+1,vars[k]);
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
asu::CMatrix firstmatrix=stringtomatrix(expressionInsideFunction,k);
k++;
mvars[k]=sqrt(firstmatrix);
std::string s="result";
vars[k]=s+to_string(k);
expression.replace(first_pos,end_pos-first_pos+1,vars[k]);



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
 


bool getlinefile(std::string& stream, std::string& str)
{
	int i=0;stream=""; if(str[0]) ; else return 0; 
  while((str[i]=='\n' && str[i+1]==' ' && str[i+2]==' ' && str[i+3]==' ' && str[i+4]==' ')
  		|| (str[i]!='\n'))
  		{
  			stream+=str[i];
  			i++;
  		}
 
  		str=str.substr(i+1,str.size()-i-1);

  return 1;
}



int main(int argc, char** argv)
{
int stop=0; int donothing=0;
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


	

		while (std::getline(mfile,sMatrix))
			
		{

		try{
			sMatrix = sMatrix.substr(0, sMatrix.size()-1);
			while (parens_are_incomplete(sMatrix)) {

	        std::string nextline=sMatrix;
	        std::getline(mfile,sMatrix);
	        sMatrix = sMatrix.substr(0, sMatrix.size()-1);
	        nextline+="\n";
	        nextline += sMatrix;
	        sMatrix=nextline;
	        }


			donothing=0;
		
			sMatrix=removeSpaces(sMatrix);
				 
			

			bool print;
	        if (sMatrix[sMatrix.size()-1]==';'){ 
	            print=0; sMatrix = sMatrix.substr(0, sMatrix.size()-1); }
	            else print =1;

	        std::string matrixname="",wantedvalue="";   
	        int endname = sMatrix.find('=');
	        matrixname=sMatrix.substr(0,endname);
	        
	        std::string printedmatrixname=matrixname;
	        if (
	    		(sMatrix.find('=') == std::string::npos)
	    		&& ( sMatrix.find('+')!= std::string::npos || sMatrix.find('-')!= std::string::npos 
	    			|| sMatrix.find('*')!= std::string::npos || sMatrix.find('/')!= std::string::npos 
	    			||sMatrix.find("sqrt")!= std::string::npos || sMatrix.find("sin")!= std::string::npos
	    			|| sMatrix.find("cos")!= std::string::npos || sMatrix.find("tan")!= std::string::npos 
	    			|| sMatrix.find('^')!= std::string::npos  ) 
	    	
	    		)
	    		printedmatrixname = "ans";
	    	


	        std::string stringvalue=sMatrix.substr(endname+1, sMatrix.length()-endname-1);
	     

	        std::string svalue="";
	        svalue=sMatrix.substr( endname+1,3);

	       

	        if (svalue=="zer")
	        {

	            int index= sMatrix.rfind('s');

	            std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2));    
	            std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

	            vars[k]=matrixname;
	            CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_ZEROS);  
	            mvars[k]=cc;
	    
	        }

	        else if (svalue=="one")
	        {

	            int index= sMatrix.rfind('s');

	            std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2));    
	            std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

	            vars[k]=matrixname;
	            CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_ONES);   
	            mvars[k]=cc;
	         
	        
	        }

	        else if (svalue=="eye")
	        {

	            int index= sMatrix.rfind('e');
	            index+=2;

	            std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2));    
	            std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

	            vars[k]=matrixname;
	            CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_EYE);    
	            mvars[k]=cc;
	        
	        }

	        else if (svalue=="ran")
	        {

	            int index= sMatrix.rfind('d');

	            std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2));    
	            std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);
	                            
	            vars[k]=matrixname;
	            CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_RAND);   
	            mvars[k]=cc;
	                 
	        }
	        else if (sMatrix.find("'")!=std::string::npos)
			{

				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find("'")-endname-1); //to get the string name of the first variable
				CMatrix firstmatrix=stringtomatrix(firstvalue,k);
				mvars[k]=firstmatrix.getTranspose();

			}	

	        else 
	        {
	        	
	        functionsCalculation(stringvalue);

	        parthen_analysis(stringvalue);
	        basicOperationCalculation(stringvalue);

	                if (sMatrix.find('[')!=std::string::npos) //if '[' found
	                {   
	                    if ( sMatrix.find ( '[', (sMatrix.find('[')+1)  ) !=std::string::npos) 
	                    {   //if found another '[' (concatination is found)
	                        std::cout<<std::endl;
	                        concatinationAnalysis(stringvalue);
	                        mvars[k]=concatinationCalculation(stringvalue);
	                    }

	                    else
	                    {
	                            int startcalc= sMatrix.find('[');
	                            for(int i=startcalc; sMatrix[i]!='\0';i++) wantedvalue+=sMatrix[i]; 
	                                //std::cout<<wantedvalue<<std::endl;
	                            mvars[k].CopyMatrix(wantedvalue);
	                
	                    }
	                }

	                else if((stringvalue[0]>='0' && stringvalue[0]<('9'+1)) ||(stringvalue[0]=='-') )
	                {
	                    mvars[k]=CMatrix( 1,1, to_double(stringvalue));
	                }


	                else if (sMatrix=="") { donothing=1;}

	                else if ((stringvalue.find('\n'))==std::string::npos)
	                {   
	                    mvars[k]=stringtomatrix(stringvalue,k);
	                }
	              

	                else { donothing=1;} 

	        }
	        
	        if (donothing==0)
	        {
	            if (print==1) std::cout<<printedmatrixname<<" =\n"<<mvars[k]<<std::endl;   

	            vars[k]=matrixname; 
	            k++;
	        }

	}


catch(const std::invalid_argument& ia){
                std::cout<<"Error found:"<<ia.what()<<std::endl;}


		}
			mfile.close();
	}
	
}


else // interactive prompt
{ 

	while(stop==0)

	{
	try{

		std::getline(std::cin, sMatrix);
		while (parens_are_incomplete(sMatrix)) {
		std::string nextline;
		std::getline(std::cin, nextline);
		sMatrix+="\n";
		sMatrix += nextline;
		}

		//std::getline (std::cin,sMatrix);
		donothing=0;		
		sMatrix=removeSpaces(sMatrix);
		bool print;
		if (sMatrix[sMatrix.size()-1]==';'){ 
			print=0; sMatrix = sMatrix.substr(0, sMatrix.size()-1); }
			else print =1;

		std::string matrixname="",wantedvalue="";	
		int endname = sMatrix.find('=');
		matrixname=sMatrix.substr(0,endname);
		
 			std::string printedmatrixname=matrixname;
	        if (
	    		(sMatrix.find('=') == std::string::npos)
	    		&& ( sMatrix.find('+')!= std::string::npos || sMatrix.find('-')!= std::string::npos 
	    			|| sMatrix.find('*')!= std::string::npos || sMatrix.find('/')!= std::string::npos 
	    			||sMatrix.find("sqrt")!= std::string::npos || sMatrix.find("sin")!= std::string::npos
	    			|| sMatrix.find("cos")!= std::string::npos || sMatrix.find("tan")!= std::string::npos 
	    			|| sMatrix.find('^')!= std::string::npos  ) 
	    	
	    		)
	    		printedmatrixname = "ans";

		std::string stringvalue=sMatrix.substr(endname+1, sMatrix.length()-endname-1);
	
		std::string svalue="";
		svalue=sMatrix.substr( endname+1,3);

		if (svalue=="zer")
		{

			int index= sMatrix.rfind('s');

			std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
			std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

			vars[k]=matrixname;
			CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_ZEROS);	
            mvars[k]=cc;
	
		}

		else if (svalue=="one")
		{

			int index= sMatrix.rfind('s');

			std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
			std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

			vars[k]=matrixname;
			CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_ONES);	
		    mvars[k]=cc;
         
		
		}

		else if (svalue=="eye")
		{

			int index= sMatrix.rfind('e');
			index+=2;

			std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
			std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

			vars[k]=matrixname;
			CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_EYE);	
		    mvars[k]=cc;
		
		}

		else if (svalue=="ran")
		{

			int index= sMatrix.rfind('d');

			std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
			std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);
                   	 		
			vars[k]=matrixname;
			CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_RAND);	
			mvars[k]=cc;
                 
		}

		else 
		{

				//normal operations phase 1

			    if (sMatrix.find("'")!=std::string::npos)
				{

				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find("'")-endname-1); //to get the string name of the first variable
				CMatrix firstmatrix=stringtomatrix(firstvalue,k);
				mvars[k]=firstmatrix.getTranspose();

				}


				else if ( (sMatrix.find('[')!=std::string::npos)  
							&& ( sMatrix.find ( '[', (sMatrix.find('[')+1)  ) ==std::string::npos) )
					//if '[' found but no concatination
				{	
					functionsCalculation(stringvalue);
					parthen_analysis(stringvalue);
					basicOperationCalculation(stringvalue);
					concatinationAnalysis(stringvalue);
					mvars[k]=concatinationCalculation(stringvalue);
					
						//int startcalc= stringvalue.find('[');
						//	for(int i=startcalc; stringvalue[i]!='\0';i++) wantedvalue+=stringvalue[i];	
								//std::cout<<wantedvalue<<std::endl;
						//	mvars[k].CopyMatrix(wantedvalue);
					
				}

				else
				{

				
				functionsCalculation(stringvalue);	
				parthen_analysis(stringvalue);
				basicOperationCalculation(stringvalue);

				std::cout<<std::endl;

				if (sMatrix.find('[')!=std::string::npos) //if '[' found
				{	
					if ( sMatrix.find ( '[', (sMatrix.find('[')+1)  ) !=std::string::npos) 
					{	//if found another '[' (concatinationCalculationination is found)
						
						
						concatinationAnalysis(stringvalue);
					
						mvars[k]=concatinationCalculation(stringvalue);

						
					}
				}

				else if((stringvalue[0]>='0' && stringvalue[0]<('9'+1)) ||(stringvalue[0]=='-') )
				{
					mvars[k]=CMatrix( 1,1, to_double(stringvalue));
				}


				else if (sMatrix=="") { donothing=1;}

				else if ((stringvalue.find('\n'))==std::string::npos)
				{	
					mvars[k]=stringtomatrix(stringvalue,k);
				}


			

				else { donothing=1;} 

		}}
		
		if (donothing==0)
		{

			if (print==1) std::cout<<printedmatrixname<<" =\n"<<mvars[k]<<std::endl;

			vars[k]=matrixname; 
			k++;
		}
		}

		catch(const std::invalid_argument& ia){
                std::cout<<"Error found:"<<ia.what()<<std::endl;

}
		
	}
}

	delete[]mvars;
	delete[]vars;

	return 0;
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
row.addColumn(stringtomatrix(token,k));
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
while(expression.find('[',1)!=std::string::npos)
{
unsigned int startPosition=0;
int endPosition=expression.length()-1;
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

std::string insideBrackets=expression.substr(startPosition+1,endPosition-startPosition-1);
//std::cout<<expression<<std::endl;
k++;
mvars[k]=concatinationCalculation(insideBrackets);
std::string s="result";
vars[k]=s+to_string(k);
expression.replace(startPosition,endPosition-startPosition+1,vars[k]);
//std::cout<<test2<<std::endl;

}
}
