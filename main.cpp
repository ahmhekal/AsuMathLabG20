#include <fstream>
#include "string"
#include "matrix.h"
#include <stdlib.h>  
#include "parser2.h"
#include "math.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <streambuf>
using namespace asu;

 
 


std::string* matrixNames; //matrices names in string ====  std::string matrixNames[100];
CMatrix* matrixVariables;   //matrices values  ====  CMatrix matrixVariables[100];
int numberofmatrixVariables=0; //matrix index (global variable)
void concatinationAnalysis(std::string& test2);
CMatrix concatinationCalculation(std::string s );



int main(int argc, char** argv)
{
int stop=0; int donothing=0;
std::string sMatrix; //input line as string


matrixNames=new std::string [100]; //matrices names in string ====  std::string matrixNames[100];
matrixVariables=new CMatrix[100]; //matrices values  ====  CMatrix matrixVariables[100];
	

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

	            matrixNames[numberofmatrixVariables]=matrixname;
	            CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_ZEROS);  
	            matrixVariables[numberofmatrixVariables]=cc;
	    
	        }

	        else if (svalue=="one")
	        {

	            int index= sMatrix.rfind('s');

	            std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2));    
	            std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

	            matrixNames[numberofmatrixVariables]=matrixname;
	            CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_ONES);   
	            matrixVariables[numberofmatrixVariables]=cc;
	         
	        
	        }

	        else if (svalue=="eye")
	        {

	            int index= sMatrix.rfind('e');
	            index+=2;

	            std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2));    
	            std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

	            matrixNames[numberofmatrixVariables]=matrixname;
	            CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_EYE);    
	            matrixVariables[numberofmatrixVariables]=cc;
	        
	        }

	        else if (svalue=="ran")
	        {

	            int index= sMatrix.rfind('d');

	            std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2));    
	            std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);
	                            
	            matrixNames[numberofmatrixVariables]=matrixname;
	            CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_RAND);   
	            matrixVariables[numberofmatrixVariables]=cc;
	                 
	        }
	        else if (sMatrix.find("'")!=std::string::npos)
			{

				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find("'")-endname-1); //to get the string name of the first variable
				CMatrix firstmatrix=stringtomatrix(firstvalue,numberofmatrixVariables);
				matrixVariables[numberofmatrixVariables]=firstmatrix.getTranspose();

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
	                        matrixVariables[numberofmatrixVariables]=concatinationCalculation(stringvalue);
	                    }

	                    else
	                    {
	                            int startcalc= sMatrix.find('[');
	                            for(int i=startcalc; sMatrix[i]!='\0';i++) wantedvalue+=sMatrix[i]; 
	                                //std::cout<<wantedvalue<<std::endl;
	                            matrixVariables[numberofmatrixVariables].CopyMatrix(wantedvalue);
	                
	                    }
	                }

	                else if((stringvalue[0]>='0' && stringvalue[0]<('9'+1)) ||(stringvalue[0]=='-') )
	                {
	                    matrixVariables[numberofmatrixVariables]=CMatrix( 1,1, to_double(stringvalue));
	                }


	                else if (sMatrix=="") { donothing=1;}

	                else if ((stringvalue.find('\n'))==std::string::npos)
	                {   
	                    matrixVariables[numberofmatrixVariables]=stringtomatrix(stringvalue,numberofmatrixVariables);
	                }
	              

	                else { donothing=1;} 

	        }
	        
	        if (donothing==0)
	        {
	            if (print==1) std::cout<<printedmatrixname<<" =\n"<<matrixVariables[numberofmatrixVariables]<<std::endl;   

	            matrixNames[numberofmatrixVariables]=matrixname; 
	            numberofmatrixVariables++;
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

			matrixNames[numberofmatrixVariables]=matrixname;
			CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_ZEROS);	
            matrixVariables[numberofmatrixVariables]=cc;
	
		}

		else if (svalue=="one")
		{

			int index= sMatrix.rfind('s');

			std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
			std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

			matrixNames[numberofmatrixVariables]=matrixname;
			CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_ONES);	
		    matrixVariables[numberofmatrixVariables]=cc;
         
		
		}

		else if (svalue=="eye")
		{

			int index= sMatrix.rfind('e');
			index+=2;

			std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
			std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);

			matrixNames[numberofmatrixVariables]=matrixname;
			CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_EYE);	
		    matrixVariables[numberofmatrixVariables]=cc;
		
		}

		else if (svalue=="ran")
		{

			int index= sMatrix.rfind('d');

			std::string the_row=sMatrix.substr(index+2,sMatrix.find(',')-(index+2)); 	
			std::string the_column=sMatrix.substr(sMatrix.find(',')+1,sMatrix.find(')')-sMatrix.find(',')+1-2);
                   	 		
			matrixNames[numberofmatrixVariables]=matrixname;
			CMatrix cc((int)to_double(the_row),(int)to_double(the_column),asu::CMatrix::MI_RAND);	
			matrixVariables[numberofmatrixVariables]=cc;
                 
		}

		else 
		{

				//normal operations phase 1

			    if (sMatrix.find("'")!=std::string::npos)
				{

				std::string firstvalue=sMatrix.substr(endname+1,sMatrix.find("'")-endname-1); //to get the string name of the first variable
				CMatrix firstmatrix=stringtomatrix(firstvalue,numberofmatrixVariables);
				matrixVariables[numberofmatrixVariables]=firstmatrix.getTranspose();

				}


				else if ( (sMatrix.find('[')!=std::string::npos)  
							&& ( sMatrix.find ( '[', (sMatrix.find('[')+1)  ) ==std::string::npos) )
					//if '[' found but no concatination
				{	
					functionsCalculation(stringvalue);
					parthen_analysis(stringvalue);
					basicOperationCalculation(stringvalue);
					concatinationAnalysis(stringvalue);
					matrixVariables[numberofmatrixVariables]=concatinationCalculation(stringvalue);
					
						//int startcalc= stringvalue.find('[');
						//	for(int i=startcalc; stringvalue[i]!='\0';i++) wantedvalue+=stringvalue[i];	
								//std::cout<<wantedvalue<<std::endl;
						//	matrixVariables[numberofmatrixVariables].CopyMatrix(wantedvalue);
					
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
					
						matrixVariables[numberofmatrixVariables]=concatinationCalculation(stringvalue);

						
					}
				}

				else if((stringvalue[0]>='0' && stringvalue[0]<('9'+1)) ||(stringvalue[0]=='-') )
				{
					matrixVariables[numberofmatrixVariables]=CMatrix( 1,1, to_double(stringvalue));
				}


				else if (sMatrix=="") { donothing=1;}

				else if ((stringvalue.find('\n'))==std::string::npos)
				{	
					matrixVariables[numberofmatrixVariables]=stringtomatrix(stringvalue,numberofmatrixVariables);
				}


			

				else { donothing=1;} 

		}}
		
		if (donothing==0)
		{

			if (print==1) std::cout<<printedmatrixname<<" =\n"<<matrixVariables[numberofmatrixVariables]<<std::endl;

			matrixNames[numberofmatrixVariables]=matrixname; 
			numberofmatrixVariables++;
		}
		}

		catch(const std::invalid_argument& ia){
                std::cout<<"Error found:"<<ia.what()<<std::endl;

}
		
	}
}

	delete[]matrixVariables;
	delete[]matrixNames;

	return 0;
}











