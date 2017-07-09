#include "../includes/Avm.hpp"


int     main(int ac, char **av)

{
    AbstractVm  abstractvm;

    abstractvm.checkArg(ac, av);
    abstractvm.push<int8_t>(INT8, "123");
    abstractvm.push<double>(DOUBLE, "123.56");
    abstractvm.dump();
    abstractvm.pop();
    abstractvm.dump();
    abstractvm.exit();
    return 0;
}
