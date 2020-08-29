
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
	if (argc !=3 && argc != 1) {
		std::cerr << "Usage: " << argv[0] << " -conf={file} -t={1 or 0}" << std::endl;
		std::cerr << "Usage: " << argv[0] << std::endl;
		return;
	}
	std::string confF = getCmdOption(argc, argv, "-conf=");
	std::string threads = getCmdOption(argc, argv, "-t=");
	


	if (argc == 1) {  //if there is no -conf and only the name of program.
		std::cout << std::endl;
		cmd_main();
	}
	else if (confF.compare("-") != 0 && threads.compare("-") != 0) { //if we have -conf there and t parameter

		if (confF.compare("") == 0 || threads.compare("") == 0) { //if we have -conf= there.
			std::cerr << "Usage: " << argv[0] << " -conf={file} -t={1 or 0}" << std::endl;
			std::cerr << "Usage: " << argv[0] << std::endl;
			return;
		}
		else if(threads.compare("0") == 0)
			initC2RWithpointers(confF);
		else if (threads.compare("1") == 0)
			initC2RWiththreads(confF);
		else {
			std::cerr << "Usage: " << argv[0] << " -conf={file} -t={1 or 0}" << std::endl;
			std::cerr << "Usage: " << argv[0] << std::endl;
			return;
		}
	}

	else { // if we dont have 
		std::cerr << "Usage: " << argv[0] << " -conf={file} -t={1 or 0}" << std::endl;
		std::cerr << "Usage: " << argv[0] << std::endl;
		return;
	}
	
	
	
	std::cout<<std::endl;
}