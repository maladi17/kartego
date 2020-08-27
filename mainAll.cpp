
#include "parser.h"
#include <string>
extern "C" {
#include "pktheaders.h"
}

std::string getCmdOption(int argc, char* argv[], const std::string& option)
{
	std::string cmd="-" ;
	for (int i = 0; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (0 == arg.find(option))
		{

			int size = option.size();
			cmd = arg.substr(size);
		
			return cmd;
		}
	}
	return cmd;
}


void main(int argc, char* argv[]) {
	if (argc > 2) {
		std::cerr << "Usage: " << argv[0] << " -conf={file}" << std::endl;
		std::cerr << "Usage: " << argv[0] << std::endl;
		return;
	}
	std::string confF = getCmdOption(argc, argv, "-conf=");
	


	if (confF.compare("-") == 0 && argc == 1) {  //if there is no -conf and only the name of program.
		std::cout << std::endl;
		cmd_main();
	}
	else if (confF.compare("-") != 0) { //if we have -conf there.

		if (confF.compare("") == 0) { //if we have -conf= there.
			std::cerr << "Usage: " << argv[0] << " -conf={file}" << std::endl;
			std::cerr << "Usage: " << argv[0] << std::endl;
			return;
		}
		initC2R(confF);
	}
	else if (confF.compare("-") == 0 && argc == 2) { // if we dont have -conf and more than one val
		std::cerr << "Usage: " << argv[0] << " -conf={file}" << std::endl;
		std::cerr << "Usage: " << argv[0] << std::endl;
		return;
	}
	
	
	
	std::cout<<std::endl;
}