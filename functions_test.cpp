#include "functions.h" // includes iostream, math, matrix
#include <fstream>
using namespace asu;

#define TEST(cond) std::cout << ((cond)? "\e[1;32m1\e[m" : "\e[1;31m0\e[m") 

#define PRINT_TEST_FUNCTION(fnname, result, expected) do {                  \
        if (!readmatfile(fnname "-test.mat")) break;                        \
        std::cout << fnname ": ";                                           \
        TEST(result == expected);                                           \
        std::cout << std::endl;                                             \
} while (0)

#define TEST_ONE_ARG_FN(fn)                                                 \
        PRINT_TEST_FUNCTION(#fn, fn(_('a')), _('A'))
#define TEST_TWO_ARG_FN(fn)                                                 \
        PRINT_TEST_FUNCTION(#fn, fn(_('a'), _('b')), _('C'))

#define TEST_TRIG_FUNCTIONS(f1, f2, f3) do {                                \
        std::cout << #f1 "-" #f2 "-" #f3 ": ";                              \
        if (!readmatfile(#f1 "-" #f2 "-" #f3 "-test.mat")) break;           \
        TEST(f1(_('a')) == _('A'));                                         \
        TEST(f2(_('b')) == _('B'));                                         \
        TEST(f3(_('c')) == _('C'));                                         \
        std::cout << ' ';                                                   \
        TEST(a##f1(_('d')) == _('D'));                                      \
        TEST(a##f2(_('e')) == _('E'));                                      \
        TEST(a##f3(_('f')) == _('F'));                                      \
        _('a').reset();  _('A').reset();                                    \
        _('b').reset();  _('B').reset();                                    \
        _('c').reset();  _('C').reset();                                    \
        _('d').reset();  _('D').reset();                                    \
        _('e').reset();  _('E').reset();                                    \
        _('f').reset();  _('F').reset();                                    \
        std::cout << std::endl;                                             \
} while (0)

CMatrix& _(char name)
{
        static CMatrix vars[52];
        if (name < 'A' || name > 'z' || (name < 'a' && name > 'Z'))
                throw std::invalid_argument("Impossible variable name");
        // convert A..Z to 0..25, and a..z to 26..51
        size_t ord = name >= 'a' ? name - 'a' + 26 : name - 'A';
        return vars[ord];
}

int readmatfile(const char *filename)
{
        std::ifstream matfile(filename);
        if (!matfile.is_open()) {
                std::cerr << "Couldn't open " << filename << std::endl;
                return 0;
        }

        std::string ignored;
        getline(matfile, ignored); // the first line is irrelevant

        /* every matrix in the mat file is of the form:
                # name: a
                # type: matrix
                # rows: 50
                # columns: 50
        then followed by ${rows} lines, each of which is
        ${columns} decimal numbers separated with spaces.
        **/
        while (!matfile.eof()) {
                // reading the metadata: the lines staring with #
                #define READ_METADATA(var) \
                matfile >> ignored >> ignored >> var; \
                getline(matfile, ignored);
                // ignore `# fieldname:` then read the var
                // and ignore the rest of the line, usually the \n only.

                char name; READ_METADATA(name);
                getline(matfile, ignored); // ignore `# type: matrix'

                size_t rows; READ_METADATA(rows);
                size_t columns; READ_METADATA(columns);
                #undef READ_METADATA

                // reading the matrix
                _(name).reset();
                _(name) = CMatrix(rows, columns);
                size_t n = rows * columns;
                for (size_t i = 0; i < n; ++i)
                        matfile >> _(name)(i);

                // ignoring the two empty lines that follow a matrix definition
                getline(matfile, ignored);
                getline(matfile, ignored);
        }
        return 1;
}

int main()
{
        TEST_TRIG_FUNCTIONS(sin,  cos,  tan);
        // FIXME: there is a problem in the following tests; they go infinite!
        //TEST_TRIG_FUNCTIONS(sind, cosd, tand);
        //TEST_TRIG_FUNCTIONS(sinh, cosh, tanh);
        //TEST_TRIG_FUNCTIONS(csc,  sec,  cot);
        //TEST_TRIG_FUNCTIONS(cscd, secd, cotd);
        //TEST_TRIG_FUNCTIONS(csch, sech, coth);

        TEST_TWO_ARG_FN(atan2);
        TEST_TWO_ARG_FN(atan2d);
        TEST_TWO_ARG_FN(hypot);
        TEST_TWO_ARG_FN(power);

        TEST_ONE_ARG_FN(rad2deg);
        TEST_ONE_ARG_FN(deg2rad);

        TEST_ONE_ARG_FN(exp);
        TEST_ONE_ARG_FN(log);
        TEST_ONE_ARG_FN(log10);
        TEST_ONE_ARG_FN(log2);
        TEST_ONE_ARG_FN(log1p);
        TEST_ONE_ARG_FN(sqrt);
}
