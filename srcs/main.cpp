#include "../includes/Avm.hpp"

Factory *Factory::_factory = NULL;

void checkArg( int ac, char **av) {

	(void)ac;
	(void)av;
    /*if (ac == 2)
        isFiles(av[1]);
    else if (ac == 1)
       	isLines();
    else
        std::cout << "Too much arguments, Usage: ./avm Or ./avm ./sample.avm" << std::endl;*/
    return;
}

int     main(int ac, char **av)
{
    AbstractVm  abstractvm;

   	checkArg(ac, av);
   	try {
     	abstractvm.create(INT8, "2");
     	abstractvm.create(INT8, "0");
     	abstractvm.doOp(MOD);
     	abstractvm.dump();
     	abstractvm.exit("End of program");
   	} catch (AbstractVmException e) {
   		abstractvm.exit(e.what());
   	}
    return 0;
}