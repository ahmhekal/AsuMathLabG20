ASU Math Lab Software Project
=============================

Intro
-----

This project is made by a group of 3rd year Computer and systems depatrtment
students at Faculty of Engineering Ain Shams University.

This is a complete rewrite in C++. The aim of the software is to
simulating a program dealing with matrices and it's operations similar
to Matlab, Octave and similar tools.

ASU Math Lab Software will go through the following Phases:

- Core operations 
- Advanced Operations and Tuning 
- Advanced system operations


Phases 1: Core Operations
-------------------------

- Implement C++ class for matrix.
- Support dynamic creation and destruction of matrices of any size.
- Support addition, subtraction, multiplication, transpose and division.
- Process input user commands and show results directly.
- Process input file, show each step result then exit.

Phases 2: Advanced Operations and Tuning 
----------------------------------------

- Support mathematical functions(Trigonometric, Logarithmic, Roots, Power).
- Support mathematical expressions(Either with (dot) or not).
- Support flexible matrix parser(Accept matrix in matrix, expressions and variables).
- Support error handling(Do not crash for invalid input).

Phases 3: Advanced system operations 
------------------------------------
- Soon

Input Format
------------

- User can write directly in the CommandLine or type in a .m file

- The inputs should be similar to the following formats(MATLAB Format)

- Example For supported formats in Phase1 :
::
                              
> A = [1.4 2.2 3.2; 4.4 5.4 6.4; 3.3 4.2 2.2]; //Defining the first matrix A
> B = [1.5 4.1 5.4; 3.1 4.2 1.2; 3.2 4.3 2.2]; //Defining the second matrix B
> C = A + B //Adding two matrices and put result in a matrix C
> D = A - B //Subtracting two matrices and put result in a matrix D
> E = A * B //Mul two matrices and put result in a matrix E
> F = A / B //Div two matrices and put result in a matrix F
> G = A’    //Trasnpose matrix A and put result in a matrix H

- Example For supported formats in Phase2 :
::  
                         
> A = 5.5 + 12 * sin(0.4) + 2.2^4; //Support Trigonometric functions like sin,cos,...
> B = [1.2 2.3 A;[1.3 2.4;4.6 1.3],[3.2;7.8]]; //Accept matrix in matrix ,expressions and variables
> C = [[B [3.4; 2.1; 3.5+9.1]]1.2^3 3+1.2 15/(2.1+10*sin(0.12)) 1.2]
> D = rand(4,4) //Create random matrix with size 4x4
> E = eye(4, 4) //Create eye matrix with size 4x4
> F = zeros(2, 3) //Create zero matrix with size 2x3
> G = ones(3, 6) //Create ones matrix with size 3x6
> L = (1.2 + 3.4 - 5.6)/(2.1*3.2 + 4.6) - 12.1*3.1 + (1.2 + 5.2)^(4/(3.2+5.6)) //Support Support mathematical functions
> X = ((C*D .+ 4)./2.1 + sqrt(D))./C.^2
> Y = C^3 * sin(1./D) 

How to Run the Project
----------------------
1.Get the repository on your device by downloading or cloning it using terminal
2.Open the terminal in the directory of the project
3.Type "make" in the terminal and enter it
4.User can type the input manually or using a ready .m file 
  >>in case of typing inputs manually ,user should type "./matrix" in the terminal then type the matrices he wants.
  >>in case of using a ready .m file  ,user should type "./matrix <filename.m>" in the terminal then waits for results.
