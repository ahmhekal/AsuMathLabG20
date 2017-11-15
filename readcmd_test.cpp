#include "readcmd.h" // indirectly includes iostream
#include <sstream>
int main()
{
    // sin is the input stream for readCmd, not me.
    // sout is the output stream for readCmd, not me.
    // for me, they are revesed.
    std::stringstream sin;
    std::stringstream sout;
    std::string s;

#define TEST(line) ({ std::getline(sout,s);  \
        if (s == line) std::cout << "\e[1;32m1\e[m"; \
        else           std::cout << "\e[1;31m0\e[m"; })
#define READ ReadCmd::readCmd(sin, sout)
#define NL std::cout << std::endl

    {
        sin << "A = [8.9 7.3 4.8 2.4;"
                    "2.3 6.5 8.9 1.2;"
                    "4.9 3.8 7.2 7.5;"
                    "9.8 3.4 7.5 8.9]\n";
        READ;
        TEST("8.9\t7.3\t4.8\t2.4");
        TEST("2.3\t6.5\t8.9\t1.2");
        TEST("4.9\t3.8\t7.2\t7.5");
        TEST("9.8\t3.4\t7.5\t8.9"); NL;

        sin << "B = [1.2 5.7 4.2 1.4;"
                    "6.3 2.5 8.1 3.1;"
                    "6.4 2.8 7.1 8.1;"
                    "3.2 5.1 7.2 6.2]\n";
        READ;
        TEST("1.2\t5.7\t4.2\t1.4");
        TEST("6.3\t2.5\t8.1\t3.1");
        TEST("6.4\t2.8\t7.1\t8.1");
        TEST("3.2\t5.1\t7.2\t6.2"); NL;

        /*sin << "\n"; READ;
        TEST(""); NL;*/
        // doesn't work in the test if supplied alone;
        // but it works in the real application anyway

        sin << "\nC = A + B\n"; READ;
        TEST("10.1\t13\t9\t3.8");
        TEST("8.6\t9\t17\t4.3");
        TEST("11.3\t6.6\t14.3\t15.6");
        TEST("13\t8.5\t14.7\t15.1"); NL;

        sin << "D = A - B\n"; READ;
        TEST("7.7\t1.6\t0.6\t1");
        TEST("-4\t4\t0.8\t-1.9");
        TEST("-1.5\t1\t0.1\t-0.6");
        TEST("6.6\t-1.7\t0.3\t2.7"); NL;

        sin << "E = A * B\n"; READ;
        TEST("95.07\t94.66\t147.87\t88.85");
        TEST("104.51\t60.4\t134.14\t102.9");
        TEST("99.9\t95.84\t156.48\t123.46");
        TEST("109.66\t130.75\t186.03\t140.19"); NL;

        sin << "F = A / B\n"; READ;  // BE AWARE OF THE PRECISION
        TEST("3.68433\t-0.142503\t2.96126\t-4.24234");
        TEST("0.154969\t0.935297\t-1.25678\t1.33283");
        TEST("-0.0723849\t-0.0232315\t0.528432\t0.547267");
        TEST("1.07013\t-0.0756962\t2.27603\t-1.74184"); NL;

        sin <<"G = 1 ./ A\n"; READ;
        TEST("0.11236\t0.136986\t0.208333\t0.416667");
        TEST("0.434783\t0.153846\t0.11236\t0.833333");
        TEST("0.204082\t0.263158\t0.138889\t0.133333");
        TEST("0.102041\t0.294118\t0.133333\t0.11236"); NL;

        sin <<"H = C'\n"; READ;
        TEST("10.1\t8.6\t11.3\t13");
        TEST("13\t9\t6.6\t8.5");
        TEST("9\t17\t14.3\t14.7");
        TEST("3.8\t4.3\t15.6\t15.1"); NL;
    }{
        /*sin << "A =[1.4\t2.2\t3.2;"
                   "4.4\t5.4\t6.4;"
                   "3.3\t4.2\t2.2];\n";*/ // throws
        sin << "A = [1.4 2.2 3.2;"
                    "4.4 5.4 6.4;"
                    "3.3 4.2 2.2];\n";
        READ;
        // silent; don't TEST()

        /*sin << "B= [1.5\t4.1\t5.4;"
                   "3.1\t4.2\t1.2;"
                   "3.2\t4.3\t2.2];\n";*/  // throws
        sin << "B = [1.5 4.1 5.4;"
                    "3.1 4.2 1.2;"
                    "3.2 4.3 2.2];\n";
        READ;
        // silent; don't TEST()

        sin << "C = A + B\n"; READ;
        TEST("2.9\t6.3\t8.6");
        TEST("7.5\t9.6\t7.6");
        TEST("6.5\t8.5\t4.4"); NL;

        sin << "D = A - B\n"; READ;
        TEST("-0.1\t-1.9\t-2.2");
        TEST("1.3\t1.2\t5.2");
        TEST("0.1\t-0.1\t0"); NL;

        sin << "E = A * B\n"; READ;
        TEST("19.16\t28.74\t17.24");
        TEST("43.82\t68.24\t44.32");
        TEST("25.01\t40.63\t27.7"); NL;
        
        sin << "F = A / B\n"; READ;
        TEST("0.178721\t-1.56426\t1.8691");
        TEST("-0.172744\t-4.43455\t5.75194");
        TEST("-0.105499\t-0.4211\t1.48864"); NL;

        sin << "G = A'\n"; READ;
        TEST("1.4\t4.4\t3.3");
        TEST("2.2\t5.4\t4.2");
        TEST("3.2\t6.4\t2.2"); NL;
    }
}
