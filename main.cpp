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
void concat_analysis(std::string& test2);
CMatrix concat(std::string s );

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
if(a==test.length()-1){
throw std::invalid_argument
		    ("syntax error");

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

break;

}

}

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


count++;
k++;
mvars[k]=r;
std::string s="result";
vars[k]=s+to_string(k);
test.replace(x,y-x+1,vars[k]);


}
else{
double z=to_double(test.substr(x,a-x));
double k=to_double(test.substr(a+1,y-a));


double result=pow(z,k);

std::string replacement=to_string(result);
test.replace(x,y-x+1,replacement);


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
if(a==test.length()-1){
throw std::invalid_argument
		    ("syntax error");

}

int x=0;
int y=test.length()-1;
//&&test[0]!='-'
for(int i=a-1;i>=0;i--){
if(!((test[i]>='.'&&test[i]<='9')&&test[i]!='/')&&(!(test[i]>='a'&&test[i]<='z'))&&(!(test[i]>='A'&&test[i]<='Z')))
 {
x=i+1;
break;

}
}
if(x==1&&test[0]=='-')
{
x=0;
}
for(unsigned int j=a+1;j<test.length();j++){
if(!((test[j]>='.'&&test[j]<='9')&&test[j]!='/')&&(!(test[j]>='a'&&test[j]<='z'))&&(!(test[j]>='A'&&test[j]<='Z'))){


y=j-1;
//

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
 if(operand2=="0"&&test[a]=='/')
    throw std::invalid_argument
		    ("division by zero");

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

}
}
int flag=0;
while((test.find('+')!=std::string::npos||test.find('-',flag+1)!=std::string::npos)/*&&(test[0]!='-'||test.length()>10)*/){
int a=0;
for(unsigned int i=flag;i<test.length();i++){
if((test[i]=='+'||test[i]=='-')&&i!=0){
a=i;
break;
}
}

if(a==test.length()-1){
throw std::invalid_argument
		    ("syntax error");

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
if(x==1&&test[0]=='-')
{
x=0;
}
for(unsigned int j=a+1;j<test.length();j++){
if(!((test[j]>='.'&&test[j]<='9')&&test[j]!='/')&&(!(test[j]>='a'&&test[j]<='z'))&&(!(test[j]>='A'&&test[j]<='Z'))){


y=j-1;
//

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
if(test[a-1]==' '||test[a-1]==';'){
flag=a+1;
continue;
}


 operand2=test.substr(a+1,y-a);

if((!isdigit(operand1[0])||!isdigit(operand2[0]))&&operand1[0]!='-'){
asu::CMatrix firstmatrix;
asu::CMatrix secondmatrix;
double operand_double;
if(!isdigit(operand1[0])&&!isdigit(operand2[0])){
firstmatrix=stringtomatrix(operand1,k);
secondmatrix=stringtomatrix(operand2,k);
k++;

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

}

}
}

void parthen_analysis(std::string& test2){
while(test2.find('(')!=std::string::npos)
{
	unsigned int open_counter = 0 , close_counter=0 ;

  for (unsigned int i=0 ; i<test2.length() ; i++)
     {
       if(test2[i] == '(')
          open_counter++;
       if(test2[i] == ')')
          close_counter++;
     }

  if (open_counter > close_counter )
  throw std::invalid_argument
		    ("syntax error");
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
	        	
	        mathematical_calc(stringvalue);
	        parthen_analysis(stringvalue);
	        math_piority_calc(stringvalue);

	                if (sMatrix.find('[')!=std::string::npos) //if '[' found
	                {   
	                    if ( sMatrix.find ( '[', (sMatrix.find('[')+1)  ) !=std::string::npos) 
	                    {   //if found another '[' (concatination is found)
	                        std::cout<<std::endl;
	                        concat_analysis(stringvalue);
	                        mvars[k]=concat(stringvalue);
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
	            if (print==1) std::cout<<matrixname<<" =\n"<<mvars[k]<<std::endl;   
	            vars[k]=matrixname; 
	            k++;
	        }

	}


catch(const std::invalid_argument& ia){
                std::cout<<"Error found:"<<std::endl<<ia.what()<<std::endl;}


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
				
						int startcalc= sMatrix.find('[');
							for(int i=startcalc; sMatrix[i]!='\0';i++) wantedvalue+=sMatrix[i];	
								//std::cout<<wantedvalue<<std::endl;
							mvars[k].CopyMatrix(wantedvalue);
					
				}

				else
				{
				mathematical_calc(stringvalue);
				parthen_analysis(stringvalue);
				math_piority_calc(stringvalue);



				if (sMatrix.find('[')!=std::string::npos) //if '[' found
				{	
					if ( sMatrix.find ( '[', (sMatrix.find('[')+1)  ) !=std::string::npos) 
					{	//if found another '[' (concatination is found)
						std::cout<<std::endl;
						concat_analysis(stringvalue);
						mvars[k]=concat(stringvalue);
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
			if (print==1) std::cout<<matrixname<<" =\n"<<mvars[k]<<std::endl;
			vars[k]=matrixname; 
			k++;
		}
		}

		catch(const std::invalid_argument& ia){
                std::cout<<"Error found:"<<std::endl<<ia.what()<<std::endl;

}
		
	}
}

	delete[]mvars;
	delete[]vars;

	return 0;
}












asu::CMatrix concat(std::string s ){
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
void concat_analysis(std::string& test2){
while(test2.find('[',1)!=std::string::npos)
{
unsigned int x=0;
int y=test2.length()-1;
for(unsigned int i=0;i<test2.length();i++){
if(test2[i]=='[')
x=i;

}
for(unsigned int i=0;i<test2.length()-1;i++){
if(test2[i]==']'&&i>x){
y=i;
break;
}
}

std::string expression=test2.substr(x+1,y-x-1);
//std::cout<<expression<<std::endl;
k++;
mvars[k]=concat(expression);
std::string s="result";
vars[k]=s+to_string(k);
test2.replace(x,y-x+1,vars[k]);
//std::cout<<test2<<std::endl;

}
}
