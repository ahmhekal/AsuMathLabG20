all: matrix

matrix: FORCE
	g++ main.cpp matrix.cpp -o matrix -Wall -Wextra -O3
functions_test_compile_run: FORCE
	g++ functions_test.cpp matrix.cpp -o functions_test -Wall -Wextra -O3 && ./functions_test
clean:
	rm -f matrix matrix_test

