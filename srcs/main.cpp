#include "../includes/Avm.hpp"


int     main(int ac, char **av)
{
    AbstractVm  abstractvm;

    abstractvm.checkArg(ac, av);
    abstractvm.push<double>(DOUBLE, "123.56");
    abstractvm.push<int8_t>(INT8, "65");
    abstractvm.dump();
    abstractvm.add();
    abstractvm.dump();
    abstractvm.push<int8_t>(INT8, "65");
    abstractvm.sub();
    abstractvm.dump();
    abstractvm.exit("End of program");
    return 0;
}
