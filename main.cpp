#include <fstream>
#include "string"
#include "matrix.h"
#include <stdlib.h>  
#include "parser2.h"
using namespace asu;

std::string* vars; //matrices names in string ====  std::string vars[100];
CMatrix* mvars;   //matrices values  ====  CMatrix mvars[100];


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
	int i; //k++;
	for (i =k ; i>=0; i--)
	{
		if(vars[i]==s) return mvars[i];
	}
	if(i>99) throw std::invalid_argument("Impossible variable name");
	asu::CMatrix nomatrix; return nomatrix ;
}
string to_string(double operand){
char buffer_test[50];
sprintf(buffer_test,"%g",operand);
return(string)buffer_test;
}
double to_double(string operand){
char * buffer=new char[operand.length()+1];
strcpy(buffer,operand.c_str());
double result=atof(buffer);
delete [] buffer;
return result;

}
void math_piority_calc(string& test){
int count=0;

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
if(!((test[i]>='.'&&test[i]<='9')&&test[i]!='/')&&(!(test[i]>='a'&&test[i]<='z')))
 {
x=i+1;
break;

}
}
for(int j=a+1;j<test.length();j++){
if(!((test[j]>='.'&&test[j]<='9')&&test[j]!='/')&&(!(test[j]>='a'&&test[j]<='z'))&&test[a+1]!='-'){


y=j-1;
//
//cout<<y;
break;

}

}
//cout<<test.substr(x,a-x)<<endl;
//cout<<test.substr(a+1,y-a+1);
//cout<<stringtomatrix(test.substr(x,a-x),k);
string operand1;
string operand2;
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
string s="result";
vars[k]=s+to_string(k);
test.replace(x,y-x+1,vars[k]);
cout<<test<<endl;


}
else{
double z=to_double(test.substr(x,a-x));
double k=to_double(test.substr(a+1,y-a));


double result=pow(z,k);

string replacement=to_string(result);
test.replace(x,y-x+1,replacement);
cout<<test<<endl;

}
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
//&&test[0]!='-'
for(int i=a-1;i>=0;i--){
if(!((test[i]>='.'&&test[i]<='9')&&test[i]!='/')&&(!(test[i]>='a'&&test[i]<='z'))&&test[0]!='-')
 {
x=i+1;
break;

}
}
for(int j=a+1;j<test.length();j++){
if(!((test[j]>='.'&&test[j]<='9')&&test[j]!='/')&&(!(test[j]>='a'&&test[j]<='z'))){


y=j-1;
//
//cout<<y;
break;

}

}
string operand1;
string operand2;
if(test[a-1]=='.'){
 operand1=test.substr(x,a-x-1);
}
else{ operand1=test.substr(x,a-x);}
if(test[y]=='.'){
y-=1;
}


 operand2=test.substr(a+1,y-a);
cout<<operand1<<endl;

cout<<operand2<<endl;
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
string s="result";
vars[k]=s+to_string(k);
test.replace(x,y-x+1,vars[k]);
cout<<test<<endl;



}
else{
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
if(!((test[i]>='.'&&test[i]<='9')&&test[i]!='/')&&(!(test[i]>='a'&&test[i]<='z'))&&test[0]!='-')
 {
x=i+1;
break;

}
}
for(int j=a+1;j<test.length();j++){
if(!((test[j]>='.'&&test[j]<='9')&&test[j]!='/')&&(!(test[j]>='a'&&test[j]<='z'))){


y=j-1;
//
//cout<<y;
break;

}

}
string operand1;
string operand2;
if(test[a-1]=='.'){
 operand1=test.substr(x,a-x-1);
}
else{ operand1=test.substr(x,a-x);}
if(test[y]=='.'){
y-=1;
}


 operand2=test.substr(a+1,y-a);
cout<<operand1<<endl;

cout<<operand2<<endl;
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
string s="result";
vars[k]=s+to_string(k);
test.replace(x,y-x+1,vars[k]);
cout<<test<<endl;



}
else{
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
}

void parthen_analysis(string& test2){
while(test2.find('(')!=string::npos)
{
int x=0;
int y=test2.length()-1;
for(int i=0;i<test2.length();i++){
if(test2[i]=='(')
x=i;

}
for(int i=0;i<test2.length();i++){
if(test2[i]==')'&&i>x){
y=i;
break;
}
}

string expression=test2.substr(x+1,y-x-1);

math_piority_calc(expression);
test2.replace(x,y-x+1,expression);
cout<<test2<<endl;

}

}
void parthen_analysis(string& test2){
while(test2.find('(')!=string::npos)
{
int x=0;
int y=test2.length()-1;
for(int i=0;i<test2.length();i++){
if(test2[i]=='(')
x=i;

}
for(int i=0;i<test2.length();i++){
if(test2[i]==')'&&i>x){
y=i;
break;
}
}

string expression=test2.substr(x+1,y-x-1);

math_piority_calc(expression);
test2.replace(x,y-x+1,expression);
cout<<test2<<endl;

}


}
void func(string& test){
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







int main(int argc, char** argv)
{
int stop=0; 
std::string sMatrix; //input line as string
int k=0; //matrix index

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

			sMatrix=removeSpaces(sMatrix);
			std::string matrixname="",wantedvalue="";
	
			int endname = sMatrix.find('=');
			matrixname=sMatrix.substr(0,endname);
	
			if (sMatrix.find('[')!=std::string::npos)
			{
				int startcalc= sMatrix.find('[');

				for(int i=startcalc; sMatrix[i]!='\0';i++)		
				wantedvalue+=sMatrix[i];	
		
				vars[k]=matrixname; 
				mvars[k].CopyMatrix(wantedvalue);
				if ( sMatrix [sMatrix.find(']')+1]  !=';') std::cout<<mvars[k]<<std::endl;
			}

			else if(sMatrix[endname+1]>='0' && sMatrix[endname+1]<('9'+1))
			{
				string stringvalue=sMatrix.substr(endname+1, sMatrix.length()-endname-1);
				mathematical_calc(stringvalue);
				math_piority_calc(stringvalue);
				mvars[k]=CMatrix( 1,1, to_double(stringvalue));
				std::cout<<"da5al hna";
				if ( sMatrix.find(';')==std::string::npos) std::cout<<mvars[k]<<std::endl;
			}

			else
			{

				if (sMatrix.find('-')!=std::string::npos)
				{
				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('-')-endname-1); //to get the string name of the first variable
				std::string secondvalue=sMatrix.substr(sMatrix.find('-')+1,(sMatrix.length()-sMatrix.find('-')-1));
				CMatrix firstmatrix=stringtomatrix(firstvalue,k);
				CMatrix secondmatrix=stringtomatrix(secondvalue,k);

				mvars[k].CopyMatrix(sub(firstmatrix,secondmatrix));
				std::cout<<mvars[k]<<std::endl;
				}


			else if (sMatrix.find('+')!=std::string::npos)
			{
				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('+')-endname-1); //to get the string name of the first variable
				std::string secondvalue=sMatrix.substr(sMatrix.find('+')+1,(sMatrix.length()-sMatrix.find('+')-1));
				CMatrix firstmatrix=stringtomatrix(firstvalue,k);
				CMatrix secondmatrix=stringtomatrix(secondvalue,k);

				mvars[k].CopyMatrix(add(secondmatrix,firstmatrix));
				std::cout<<mvars[k]<<std::endl;
			}

			else if (sMatrix.find('*')!=std::string::npos)
			{
				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('*')-endname-1); //to get the string name of the first variable
				std::string secondvalue=sMatrix.substr(sMatrix.find('*')+1,(sMatrix.length()-sMatrix.find('*')-1));
				CMatrix firstmatrix=stringtomatrix(firstvalue,k);
				CMatrix secondmatrix=stringtomatrix(secondvalue,k);

				mvars[k].CopyMatrix(mul(firstmatrix,secondmatrix));
				std::cout<<mvars[k]<<std::endl;
			}

			else if (sMatrix.find('/')!=std::string::npos)
			{
				if(sMatrix[sMatrix.find('/')-1]=='.') //element wise
				{
					std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('.')-endname-1); //to get the string name of the first variable
					std::string secondvalue=sMatrix.substr(sMatrix.find('/')+1,(sMatrix.length()-sMatrix.find('/')-1));
					double firstmatrix=atof(firstvalue.c_str());
					CMatrix secondmatrix=stringtomatrix(secondvalue,k);

					mvars[k].CopyMatrix(adiv(firstmatrix,secondmatrix));
					std::cout<<mvars[k]<<std::endl;
				}


				else //normal division
				{
					std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('/')-endname-1); //to get the string name of the first variable
					std::string secondvalue=sMatrix.substr(sMatrix.find('/')+1,(sMatrix.length()-sMatrix.find('/')-1));
					CMatrix firstmatrix=stringtomatrix(firstvalue,k);
					CMatrix secondmatrix=stringtomatrix(secondvalue,k);

					mvars[k].CopyMatrix(div(firstmatrix,secondmatrix));
					std::cout<<mvars[k]<<std::endl;
				}

			}


			else if (sMatrix.find("'")!=std::string::npos)
			{

				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find("'")-endname-1); //to get the string name of the first variable
				CMatrix firstmatrix=stringtomatrix(firstvalue,k);
				mvars[k]=firstmatrix.getTranspose();

				std::cout<<mvars[k]<<std::endl;

			}

		}


	vars[k]=matrixname; 
	k++;


		}
			mfile.close();
	}
	
}


else // interactive prompt
{ 

	while(stop==0)

	{
		std::getline (std::cin,sMatrix);		
		sMatrix=removeSpaces(sMatrix);
		std::string matrixname="",wantedvalue="";	
		int endname = sMatrix.find('=');
		matrixname=sMatrix.substr(0,endname);

		string stringvalue=sMatrix.substr(endname+1, sMatrix.length()-endname-1);
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

			if (sMatrix.find('-')!=std::string::npos)
			{
				std::string secondvalue;
				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('-')-endname-1); //to get the string name of the first variable
				if ( sMatrix.find(';')==std::string::npos)
				secondvalue=sMatrix.substr(sMatrix.find('-')+1,(sMatrix.length()-sMatrix.find('-')-1));
				else 
				secondvalue=sMatrix.substr(sMatrix.find('-')+1,(sMatrix.length()-sMatrix.find('-')-2));
				CMatrix firstmatrix=stringtomatrix(firstvalue,k);
				CMatrix secondmatrix=stringtomatrix(secondvalue,k);

				mvars[k].CopyMatrix(sub(firstmatrix,secondmatrix));
				if ( sMatrix.find(';')==std::string::npos) std::cout<<mvars[k]<<std::endl;
			}


			 if (sMatrix.find('+')!=std::string::npos)
			{
				std::string secondvalue;
				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('+')-endname-1); //to get the string name of the first variable
				if ( sMatrix.find(';')==std::string::npos)
				secondvalue=sMatrix.substr(sMatrix.find('+')+1,(sMatrix.length()-sMatrix.find('+')-1));
				else 
				secondvalue=sMatrix.substr(sMatrix.find('+')+1,(sMatrix.length()-sMatrix.find('+')-2));
				CMatrix firstmatrix=stringtomatrix(firstvalue,k);
				CMatrix secondmatrix=stringtomatrix(secondvalue,k);

				mvars[k].CopyMatrix(add(secondmatrix,firstmatrix));
				if ( sMatrix.find(';')==std::string::npos) std::cout<<mvars[k]<<std::endl;
			}

			if (sMatrix.find('*')!=std::string::npos)
			{std::string secondvalue;
				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('*')-endname-1); //to get the string name of the first variable
				if ( sMatrix.find(';')==std::string::npos)
				secondvalue=sMatrix.substr(sMatrix.find('*')+1,(sMatrix.length()-sMatrix.find('*')-1));
				else 
				secondvalue=sMatrix.substr(sMatrix.find('*')+1,(sMatrix.length()-sMatrix.find('*')-2));
				CMatrix firstmatrix=stringtomatrix(firstvalue,k);
				CMatrix secondmatrix=stringtomatrix(secondvalue,k);

				mvars[k].CopyMatrix(mul(firstmatrix,secondmatrix));
				if ( sMatrix.find(';')==std::string::npos) std::cout<<mvars[k]<<std::endl;
			}

			if (sMatrix.find('/')!=std::string::npos)
			{
				if(sMatrix[sMatrix.find('/')-1]=='.') //element wise
				{
					std::string secondvalue;
				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('/')-endname-1); //to get the string name of the first variable
				if ( sMatrix.find(';')==std::string::npos)
				secondvalue=sMatrix.substr(sMatrix.find('/')+1,(sMatrix.length()-sMatrix.find('/')-1));
				else 
				secondvalue=sMatrix.substr(sMatrix.find('/')+1,(sMatrix.length()-sMatrix.find('/')-2));
					double firstmatrix=atof(firstvalue.c_str());
					CMatrix secondmatrix=stringtomatrix(secondvalue,k);

					mvars[k].CopyMatrix(adiv(firstmatrix,secondmatrix));
					if ( sMatrix.find(';')==std::string::npos) std::cout<<mvars[k]<<std::endl;
				}

				else //normal division
				{
					std::string secondvalue;
				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('/')-endname-1); //to get the string name of the first variable
				if ( sMatrix.find(';')==std::string::npos)
				secondvalue=sMatrix.substr(sMatrix.find('/')+1,(sMatrix.length()-sMatrix.find('/')-1));
				else 
				secondvalue=sMatrix.substr(sMatrix.find('/')+1,(sMatrix.length()-sMatrix.find('/')-2));
					CMatrix firstmatrix=stringtomatrix(firstvalue,k);
					CMatrix secondmatrix=stringtomatrix(secondvalue,k);

					mvars[k].CopyMatrix(div(firstmatrix,secondmatrix));
					if ( sMatrix.find(';')==std::string::npos) std::cout<<mvars[k]<<std::endl;
				}
			}

			if (sMatrix.find("'")!=std::string::npos)
			{
				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find("'")-endname-1); //to get the string name of the first variable
				CMatrix firstmatrix=stringtomatrix(firstvalue,k);
				mvars[k]=firstmatrix.getTranspose();
				if ( sMatrix.find(';')==std::string::npos) std::cout<<mvars[k]<<std::endl;
			}

			if(sMatrix.find("=")==std::string::npos)
			{

				std::cout<<stringtomatrix(sMatrix,k)<<std::endl;
			}

		}


				
		vars[k]=matrixname; 
		k++;
	}
}


	delete[]mvars;
	delete[]vars;

	return 0;
}

