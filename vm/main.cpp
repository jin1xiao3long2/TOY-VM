#include"core.hpp"

int main(int argc, char **argv)
{
    freopen("./csvm.log","w",stderr);
	if (argc != 2)
	{
		std::cerr << "no input." << std::endl;
		return -1;
	}
	try {
		csvm::vm_t *vm_impl = new csvm::vm_t();
        vm_impl->load_functions(argv[1]);
		int exit_code = vm_impl->start();
		delete vm_impl;
        fclose(stdout);
		return exit_code;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
        return 0;
	}
}