#include "readcmd.h"
#include <fstream>

int main(int argc, char** argv)
{
	if (argc > 1) { // a filename is given
		for (int i = 1; i < argc; ++i) {
			std::ifstream mfile(argv[i]);
			if (!mfile.is_open()) {
				std::cerr << "Couldn't open " << argv[i] << std::endl;
				continue;
			}
			while (!mfile.eof())
				ReadCmd::readCmd(mfile);
			mfile.close();
		}
	} else { // interactive prompt
		while (!std::cin.eof())
			ReadCmd::readCmd(std::cin);
	}
}

