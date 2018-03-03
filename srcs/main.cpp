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
    abstractvm.create(DOUBLE, "121.3");
    abstractvm.create(INT8, "2");
    abstractvm.create(FLOAT, "12.45");
    abstractvm.create(FLOAT, "120.52");
    abstractvm.create(INT16, "9");
    abstractvm.create(INT32, "11");
    abstractvm.dump();
    abstractvm.sub();
    abstractvm.dump();
    abstractvm.mul();
    abstractvm.dump();
    abstractvm.add();
    abstractvm.dump();
    abstractvm.div();
    abstractvm.dump();
    abstractvm.mod();
    abstractvm.dump();
    abstractvm.exit("End of program");
    return 0;
}