#include "functions.h" // includes iostream, math, matrix
#include "readcmd.h"
#include <fstream>
using namespace asu;
#define M(m) ReadCmd::get(m)
#define TEST(cond) std::cout << ((cond)? "\e[1;32m1\e[m" : "\e[1;31m0\e[m") 
#define STR(a) #a
#define FILENAME(f) STR(f) "-functions-test.m"
#define FILENAME3(f1, f2, f3) STR(f1) "-" STR(f2) "-" STR(f3) "-functions-test.m"
int read_file(const char *filename)
{
	std::cout << filename << ": ";
	std::ifstream mfile(filename);
	if (!mfile.is_open()) {
		std::cerr << "Error openning file " << filename << "\n";
		return 0;
	}
	while (!mfile.eof())
		ReadCmd::readCmd(mfile);
	std::cout << '\t';
        return 1;
}
#define TEST_TRIG_FILE(f1, f2, f3) do {				\
	if (!read_file(FILENAME3(f1, f2, f3))) break;		\
	TEST(f1(M('a')) == M('A'));             		\
	TEST(f2(M('b')) == M('B'));				\
	TEST(f3(M('c')) == M('C'));				\
	std::cout << ' ';					\
	TEST(a##f1(M('d')) == M('D'));				\
	TEST(a##f2(M('e')) == M('E'));				\
	TEST(a##f3(M('f')) == M('F'));				\
	std::cout << std::endl;					\
} while(0)
int main()
{
	TEST_TRIG_FILE(sin,  cos,  tan);
	TEST_TRIG_FILE(sind, cosd, tand);
	TEST_TRIG_FILE(sinh, cosh, tanh);
	TEST_TRIG_FILE(csc,  sec,  cot);
	TEST_TRIG_FILE(cscd, secd, cotd);
	TEST_TRIG_FILE(csch, sech, coth);
	do {  // atan2
		if (!read_file(FILENAME(atan2))) break;
		TEST(atan2(M('a'), M('b')) == M('C'));
		TEST(atan2d(M('d'), M('e')) == M('F'));
		std::cout << std::endl;
	} while(0);
	do {  // hypot
		if (!read_file(FILENAME(hypot))) break;
		TEST(hypot(M('a'), M('b')) == M('C'));
		std::cout << std::endl;
	} while(0);
	do {  // rad, deg
		if (!read_file(FILENAME(rad-deg))) break;
		TEST(rad2deg(M('a')) == M('A'));
		TEST(deg2rad(M('b')) == M('B'));
		std::cout << std::endl;
	} while(0);
}
