all: matrix

matrix: FORCE
	g++ main.cpp matrix.cpp -o matrix -Wall -Wextra -O3
matrix_test: FORCE
	g++ matrix_test.cpp matrix.cpp -o matrix_test -Wall -Wextra -O3 && ./matrix_test
clean:
	rm -f matrix matrix_test

.PHONY: all test FORCE clean
test: matrix_test
FORCE:
