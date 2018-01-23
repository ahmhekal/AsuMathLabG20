#include <fstream>
#include "string"
#include "matrix.h"
#include <stdlib.h>  
#include "parser2.h"
using namespace asu;

std::string* vars; //matrices names in string ====  std::string vars[100];
CMatrix* mvars;   //matrices values  ====  CMatrix mvars[100];

void allocate_sub_matrix(string &in);
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


CMatrix stringtomatrix (std::string s, int k)  //return matrix value of a string name
{
	int i; k++;
	for (i =k ; i>=0; i--)
	{
		if(vars[i]==s) return mvars[i];
	}
	if(i>99) throw std::invalid_argument("Impossible variable name");
	CMatrix nomatrix; return nomatrix ;
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
		parthen_analysis(stringvalue);
		mathematical_calc(stringvalue);
		math_piority_calc(stringvalue);
		//std::cout<<stringvalue;
		allocate_sub_matrix(stringvalue);


		if (sMatrix.find('[')!=std::string::npos)
		{
			int startcalc= sMatrix.find('[');

			for(int i=startcalc; sMatrix[i]!='\0';i++) wantedvalue+=sMatrix[i];	
					
			vars[k]=matrixname; 
			mvars[k].CopyMatrix(wantedvalue);
			if ( sMatrix [sMatrix.find(']')+1]  !=';') std::cout<<mvars[k]<<std::endl;
		}

		else if(atof(stringvalue.c_str())!=0)//stringvalue[0]>='0' && stringvalue[0]<('9'+1))
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


void allocate_sub_matrix(string &in)
{
	std::cout<< in<<std::endl;
	int x1 =in.find('[');
	string t =in;
	if(x1!=std::string::npos)
	{
int count=-1;

		for(int i=0;i<in.length();i++)
			{
				if(in[i]=='[')

 				count++;
			}
		
		
		int x2 =in.find('[',x1+1);
		int x22 =in.find('[',x2+1);
		int x3 =in.find(']',x2);
		std::cout<<x1<<"  "<<x2<<"  "<<x22<<"   "<<x3<<"    "<<std::endl;
		CMatrix *temp =new CMatrix[count];
		for (int i=0;i<count; i++)
		{
			
		if(x2!=std::string::npos
			&&x22!=std::string::npos
			&&x3!=std::string::npos
			&&(x3<x22)
			||(x22==std::string::npos && (x3>x22)))
		{
			std::cout<<"in"<<std::endl;
			string s=in.substr(x2,in.find(']')-x2+1);
			char text[10];
			sprintf(text,"tt[%d]",i);
			string ss=string(text);
			in=in.replace(x2,x3-x2+1,ss);
			temp[i].CopyMatrix(s);
			x2 =x22;
			x22 =t.find('[',x22+1);
			x3 =t.find(']',x2);
			std::cout<<x1<<"  "<<x2<<"  "<<x22<<"   "<<x3<<"    "<<std::endl;
	
		}

		}



//a=[[5;3] [7;8]]


	}

	std::cout<< in<<std::endl;

}




