#include <fstream>
#include "string"
#include "matrix.h"
#include <stdlib.h>  
using namespace asu;

std::string* vars; //variables names in string ====  std::string vars[10];
CMatrix* mvars; //matrices values of variables =========  CMatrix mvars[10];


std::string removeSpaces(std::string input)                   //remove spaces from the string before '[' or the whole line
{
  //int length = input.length();
  for (int i = 0; !( (input[i]=='[') || (input[i]=='\0') ); i++) {
     if(input[i] == ' ' )
      {  input.erase(i, 1);i--;}
  }
  return input;
}


CMatrix stringtomatrix (std::string s)  //return matrix value of a string name
{

for (int i =0 ; i<10; i++)
{
	if(vars[i]==s) return mvars[i];
}
return "";
}







int main(int argc, char** argv)
{
int stop=0;	std::string sMatrix;
int k=0;

vars=new std::string [100]; //variables names in string ====  std::string vars[10];
mvars=new CMatrix[100]; //matrices values of variables =========  CMatrix mvars[10];
	

	if (argc > 1) { // a filename is given
		for (int i = 1; i < argc; ++i) {
			std::ifstream mfile(argv[i]);
			if (!mfile.is_open()) {
				std::cerr << "Couldn't open "
				          << argv[i] << std::endl;
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
						{
				wantedvalue+=sMatrix[i];	
		}

vars[k]=matrixname; 
mvars[k].CopyMatrix(wantedvalue);
if ( sMatrix [sMatrix.find(']')+1]  !=';') std::cout<<mvars[k]<<std::endl;
}

else
{

if (sMatrix.find('-')!=std::string::npos)
{
std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('-')-endname-1); //to get the string name of the first variable
std::string secondvalue=sMatrix.substr(sMatrix.find('-')+1,1);
CMatrix firstmatrix=stringtomatrix(firstvalue);
CMatrix secondmatrix=stringtomatrix(secondvalue);

mvars[k].CopyMatrix(sub(firstmatrix,secondmatrix));
std::cout<<mvars[k]<<std::endl;
}


else if (sMatrix.find('+')!=std::string::npos)
{

std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('+')-endname-1); //to get the string name of the first variable
std::string secondvalue=sMatrix.substr(sMatrix.find('+')+1,1);
CMatrix firstmatrix=stringtomatrix(firstvalue);
CMatrix secondmatrix=stringtomatrix(secondvalue);

mvars[k].CopyMatrix(add(secondmatrix,firstmatrix));
std::cout<<mvars[k]<<std::endl;

}

else if (sMatrix.find('*')!=std::string::npos)
{
std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('*')-endname-1); //to get the string name of the first variable
std::string secondvalue=sMatrix.substr(sMatrix.find('*')+1,1);
CMatrix firstmatrix=stringtomatrix(firstvalue);
CMatrix secondmatrix=stringtomatrix(secondvalue);

mvars[k].CopyMatrix(mul(firstmatrix,secondmatrix));
std::cout<<mvars[k]<<std::endl;
}

else if (sMatrix.find('/')!=std::string::npos)
{
if(sMatrix[sMatrix.find('/')-1]=='.') //element wise
{
std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('.')-endname-1); //to get the string name of the first variable
std::string secondvalue=sMatrix.substr(sMatrix.find('/')+1,1);
double firstmatrix=atof(firstvalue.c_str());
CMatrix secondmatrix=stringtomatrix(secondvalue);

mvars[k].CopyMatrix(adiv(firstmatrix,secondmatrix));
std::cout<<mvars[k]<<std::endl;
}


else //normal division
{
std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('/')-endname-1); //to get the string name of the first variable
std::string secondvalue=sMatrix.substr(sMatrix.find('/')+1,1);
CMatrix firstmatrix=stringtomatrix(firstvalue);
CMatrix secondmatrix=stringtomatrix(secondvalue);

mvars[k].CopyMatrix(div(firstmatrix,secondmatrix));
std::cout<<mvars[k]<<std::endl;
}

}


else if (sMatrix.find("'")!=std::string::npos)
{

std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find("'")-endname-1); //to get the string name of the first variable
CMatrix firstmatrix=stringtomatrix(firstvalue);
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








 else { // interactive prompt

	

while(stop==0)


{

	
std::getline (std::cin,sMatrix);		
		sMatrix=removeSpaces(sMatrix);
std::string matrixname="",wantedvalue="";
		

int endname = sMatrix.find('=');
matrixname=sMatrix.substr(0,endname);
		
if (sMatrix.find('[')!=std::string::npos)
{
int startcalc= sMatrix.find('[');

for(int i=startcalc; sMatrix[i]!='\0';i++)
		{
		wantedvalue+=sMatrix[i];	
		}

vars[k]=matrixname; 
mvars[k].CopyMatrix(wantedvalue);
if ( sMatrix [sMatrix.find(']')+1]  !=';') std::cout<<mvars[k]<<std::endl;
}

else
{

if (sMatrix.find('-')!=std::string::npos)
{
std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('-')-endname-1); //to get the string name of the first variable
std::string secondvalue=sMatrix.substr(sMatrix.find('-')+1,1);
CMatrix firstmatrix=stringtomatrix(firstvalue);
CMatrix secondmatrix=stringtomatrix(secondvalue);

mvars[k].CopyMatrix(sub(firstmatrix,secondmatrix));
std::cout<<mvars[k]<<std::endl;
}


 if (sMatrix.find('+')!=std::string::npos)
{

std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('+')-endname-1); //to get the string name of the first variable
std::string secondvalue=sMatrix.substr(sMatrix.find('+')+1,1);
CMatrix firstmatrix=stringtomatrix(firstvalue);
CMatrix secondmatrix=stringtomatrix(secondvalue);

mvars[k].CopyMatrix(add(secondmatrix,firstmatrix));
std::cout<<mvars[k]<<std::endl;

}

if (sMatrix.find('*')!=std::string::npos)
{
std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('*')-endname-1); //to get the string name of the first variable
std::string secondvalue=sMatrix.substr(sMatrix.find('*')+1,1);
CMatrix firstmatrix=stringtomatrix(firstvalue);
CMatrix secondmatrix=stringtomatrix(secondvalue);

mvars[k].CopyMatrix(mul(firstmatrix,secondmatrix));
std::cout<<mvars[k]<<std::endl;
}

if (sMatrix.find('/')!=std::string::npos)
{
if(sMatrix[sMatrix.find('/')-1]=='.') //element wise
{
std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('.')-endname-1); //to get the string name of the first variable
std::string secondvalue=sMatrix.substr(sMatrix.find('/')+1,1);
double firstmatrix=atof(firstvalue.c_str());
CMatrix secondmatrix=stringtomatrix(secondvalue);

mvars[k].CopyMatrix(adiv(firstmatrix,secondmatrix));
std::cout<<mvars[k]<<std::endl;
}


else //normal division
{
std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find('/')-endname-1); //to get the string name of the first variable
std::string secondvalue=sMatrix.substr(sMatrix.find('/')+1,1);
CMatrix firstmatrix=stringtomatrix(firstvalue);
CMatrix secondmatrix=stringtomatrix(secondvalue);

mvars[k].CopyMatrix(div(firstmatrix,secondmatrix));
std::cout<<mvars[k]<<std::endl;
}
}

if (sMatrix.find("'")!=std::string::npos)
{
std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find("'")-endname-1); //to get the string name of the first variable
CMatrix firstmatrix=stringtomatrix(firstvalue);
mvars[k]=firstmatrix.getTranspose();
std::cout<<mvars[k]<<std::endl;

}

}


		
vars[k]=matrixname; 

k++;


	}}


delete[]mvars;
delete[]vars;

return 0;
}

