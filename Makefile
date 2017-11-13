all:
	g++ main.cpp matrix.cpp readcmd.cpp -o matrix -Wall -Wextra -O3
test:
	g++ test.cpp matrix.cpp readcmd.cpp -o test -Wall -Wextra -O3 && ./test && rm -f test
