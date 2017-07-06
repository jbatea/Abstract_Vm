
#include "../includes/Avm.hpp"

int     main(int ac, char **av)
{
    AbstractVm abstractvm;

    abstractvm.checkArg(ac, av);
    return 0;
}
