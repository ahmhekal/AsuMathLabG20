matrix:
	g++ main.cpp matrix.cpp readcmd.cpp -o matrix -Wall -Wextra -O3
matrix_test: FORCE
	g++ matrix_test.cpp matrix.cpp readcmd.cpp -o matrix_test -Wall -Wextra -O3 && ./matrix_test
readcmd_test: FORCE
	g++ readcmd_test.cpp matrix.cpp readcmd.cpp -o readcmd_test -Wall -Wextra -O3 && ./readcmd_test
.PHONY: test FORCE
test: matrix_test readcmd_test
FORCE:

