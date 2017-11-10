#include "readcmd.h"
#include <sstream>

namespace ReadCmd
{

/*
 * get() returns a ref a var matrix
 *
 * currently, we can have up to 26 variables
 *   to be used in the command prompt/files.
 * they are A..Z case-insensitive.
 **/
static CMatrix& get(char name)
{
	static CMatrix vars[52];
	if (name < 'A' || name > 'z' || (name < 'a' && name > 'Z'))
		throw std::runtime_error("Impossible variable name");
	// convert A..Z to 0..25, and a..z to 26..51
	size_t ord = name >= 'a' ? name - 'a' + 26 : name - 'A';
	return vars[ord];
}

static void readoperand(istream& is, double& operand_double, char& operand_char)
{
	is >> operand_double;
	if (!is) { // if failed; it's a char
		is.clear(); // clear the failure state
		is >> operand_char;
		operand_double = NAN; // make the number invalid
	}
}

/*
 * readexpr() reads an expression from an istream and evaluates it,
 *   and returns the result as a CMatrix.
 **/
#define RESULT_OF(op) do {                                                  \
    if (isnan(firstoperand_double))                                         \
        if (isnan(secondoperand_double))                                    \
            result = get(firstoperand_matrix) op get(secondoperand_matrix); \
        else                                                                \
            result = get(firstoperand_matrix) op secondoperand_double;      \
    else                                                                    \
        if (isnan(secondoperand_double))                                    \
            result = firstoperand_double op get(secondoperand_matrix);      \
        else                                                                \
            result = firstoperand_double op secondoperand_double;           \
} while(0)

static CMatrix readexpr(istream& is, double firstoperand_double = NAN, char firstoperand_matrix = '0')
{
	CMatrix result;
	char operation; is >> operation;
	if (operation == '\'') {
		get(firstoperand_matrix).getTranspose(result);
	} else {
		double secondoperand_double; char secondoperand_matrix;
		readoperand(is, secondoperand_double, secondoperand_matrix);
		if (secondoperand_matrix == '/') // op is './', the element-wise division
			readoperand(is, secondoperand_double, secondoperand_matrix); // for real this time
		if (!isnan(firstoperand_double) && !isnan(secondoperand_double))
			result = CMatrix(1, 1); // we are working with scalers
		switch (operation) {
		case '+': RESULT_OF(+); break;
		case '-': RESULT_OF(-); break;
		case '*': RESULT_OF(*); break;
		case '.': if (isnan(firstoperand_double) && isnan(secondoperand_double)) {
                                result = adiv(get(firstoperand_matrix), get(secondoperand_matrix));
                                break;
                          }  // else? operator/() will take care of the rest.
		case '/': RESULT_OF(/); break;
		}
	}
	return result;
}
#undef RESULT_OF

/* 
 * readCmd() reads a cmd from a given istream and executes it.
 *
 * - istream can be cin or an ifstream.
 * - currently the supported cmd formats are:
 *   1. A = [...;...]
 *   2. A = B * C
 *   3. A = B'
 *   the first form is a MATLAB-style matrix definition.
 *   the second form is a matrix binary operation.
 *   the third form is a matrix unary opertion using a postfix
 *     operator.
 **/
void readCmd(istream& orig_is)
{
	std::string input; std::getline(orig_is, input, '\n');
	std::istringstream is(input);
	char leftvar; is >> leftvar;
	char eqsign; is >> eqsign;
	if (eqsign != '=')
		throw std::runtime_error("Equals sign expected");
	double whatnext_d; is >> whatnext_d;
	if (is) { // if it was a number
		get(leftvar) = readexpr(is, whatnext_d);
	} else {
		is.clear();
		char whatnext_c; is >> whatnext_c;
		if (whatnext_c == '[') { // the first form, matrix def
			is >> get(leftvar);
		} else {
			get(leftvar) = readexpr(is, NAN, whatnext_c);
		}
	}

	// if the last char is not no semicolon, print the value
	if (input[input.size()-1] != ';')
		cout << get(leftvar);
}

}; // namespace ReadCmd
