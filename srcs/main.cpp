#include "../includes/Avm.hpp"


int     main(int ac, char **av)

{
    AbstractVm  abstractvm;

    abstractvm.checkArg(ac, av);
    abstractvm.getStackRef().push_front(abstractvm.callFactory<int8_t>(INT8, "123"));
    std::deque<const IOperand *>::iterator it = abstractvm.getStackRef().begin();

  while (it != abstractvm.getStackRef().end())
    std::cout << (*it++)->toString() << std::endl;
    return 0;
}
