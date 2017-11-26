#include "matrix.h"

namespace ReadCmd {
	asu::CMatrix& get(char name);
	void readCmd(std::istream& is, std::ostream& os = std::cout);
};
