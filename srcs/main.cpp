#include "../includes/Avm.hpp"

Factory *Factory::_factory = NULL;


int     main(int ac, char **av)
{
    AbstractVm  abstractvm(ac, av);
    return 0;
}