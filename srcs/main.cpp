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
    abstractvm.create(INT8, "79");
    abstractvm.print();
    abstractvm.create(INT8, "12");
    abstractvm.dump();
    abstractvm.sub();
    abstractvm.exit("End of program");
    return 0;
}
