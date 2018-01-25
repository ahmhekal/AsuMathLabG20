#include <fstream>
#include "string"
#include "matrix.h"
#include <stdlib.h>  
#include "parser2.h"
using namespace asu;

std::string* vars; //matrices names in string ====  std::string vars[100];
CMatrix* mvars;   //matrices values  ====  CMatrix mvars[100];

void allocate_sub_matrix(string &in,CMatrix *temp);
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
void allocate_sub_matrix(string &in,CMatrix *temp);
		
		std::string svalue="";
	svalue=sMatrix.substr(2,3);

			if (svalue=="zer")
			{

				int index= sMatrix.find('s');

				std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
				std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

				vars[k]=matrixname;
 			       CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_ZEROS);	
			   
                                 mvars[k]=cc;

			
			}

			else if (svalue=="one")
			{

				int index= sMatrix.find('s');

				std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
				std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

				vars[k]=matrixname;
 			       CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_ONES);	
			       
                                mvars[k]=cc;

			
			}

			else if (svalue=="eye")
			{

				int index= sMatrix.find('e');
				index+=2;

				std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
				std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

				vars[k]=matrixname;
 			       CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_EYE);	
			       
                                 mvars[k]=cc;

			
			}

			else if (svalue=="ran")
			{

				int index= sMatrix.find('d');

				std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
				std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);
	                   	 		
				vars[k]=matrixname;
 			       CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_RAND);	
			        std::cout<<cc<<std::endl;
                                 mvars[k]=cc;
			
			}



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

void allocate_sub_matrix(string &in,CMatrix *temp)
{
	string t =in;
	int x1 =in.find('[');
	int x2 =in.find('[',x1+1);
	if( x1!=std::string::npos && x2!=std::string::npos )
	{	
		int x22 =in.find('[',x2+1);
		int x3  =in.find(']',x2);
		int count=1;
		int offsetPos=0;
		int inlength=in.length();
		for(int i=x2+1;i<inlength;i++)
		{
			if(in[i]=='[')
 			count++;
		}
		temp =new CMatrix[count];
		for (int i=0;i<count; i++)
		{
			if( x3!=std::string::npos )
			{	
				if( x3<x22 )
				{
					string s=in.substr(x2,x3-x2+1);
					char text[10];
					sprintf(text,"temp%d",i);
					string ss=string(text);
					t=t.replace(x2-offsetPos,x3-x2+1,ss);
					temp[i].CopyMatrix(s);
					std::cout<<s<<"  "<<ss<<"  "<<std::endl;
					std::cout<<x2<<"  "<<x3<<"  "<<x22<<"  "<<offsetPos<<"  "<<std::endl;
					x2 =x22;
					x22 =in.find('[',x22+1);
					if(x22==std::string::npos)x22=inlength;
					x3 =in.find(']',x2);
					offsetPos+=s.length()-ss.length();
				}
				else 
				{

					
				}
			}
			else
			{
				throw std::invalid_argument("expected ']'");
			}
		}
		in=t;	
	}
	std::cout<< in<<std::endl;
}
//a=[[1;0] [[5;3;4] [7;8;9]]]


