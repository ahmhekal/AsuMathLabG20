all: matrix

matrix: FORCE
	g++ main.cpp matrix.cpp -o matrix -Wall -Wextra -O3
matrix_test: FORCE
	g++ matrix_test.cpp matrix.cpp -o matrix_test -Wall -Wextra -O3 && ./matrix_test
functions_test: functions_test_generate_test_cases functions_test_compile_run
functions_test_generate_test_cases: FORCE
	octave -q generate-functions-test-cases.m 2>/dev/null
functions_test_compile_run: FORCE
	g++ functions_test.cpp matrix.cpp -o functions_test -Wall -Wextra -O3 && ./functions_test
clean:
	sh -c 'rm -f matrix *_test *-test.mat'

.PHONY: all test FORCE clean functions_test functions_test_generate_test_cases functions_test_compile_run
test: matrix_test functions_test
FORCE:

