
#include "parser.h"

extern "C" {
#include "pktheaders.h"
}
void main() {

	confParser test("conf.json");
	std::cout << test.getIsPcap();
	cmd_main();
	std::cout<<std::endl;
}