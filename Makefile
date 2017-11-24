all: matrix

matrix: FORCE
	g++ main.cpp matrix.cpp readcmd.cpp -o matrix -Wall -Wextra -O3
matrix_test: FORCE
	g++ matrix_test.cpp matrix.cpp readcmd.cpp -o matrix_test -Wall -Wextra -O3 && ./matrix_test
readcmd_test: FORCE
	g++ readcmd_test.cpp matrix.cpp readcmd.cpp -o readcmd_test -Wall -Wextra -O3 && ./readcmd_test
clean:
	rm -f matrix matrix_test readcmd_test

.PHONY: all test FORCE clean
test: matrix_test readcmd_test
FORCE:

