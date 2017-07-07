
#include "../includes/Avm.hpp"

int     main(int ac, char **av)
{
    AbstractVm  abstractvm;
    Operand<int8_t> *_int8 = NULL;

    abstractvm.checkArg(ac, av);
    abstractvm.getStackRef().push_front(_int8->createOperand(INT8, "2"));
    abstractvm.getStackRef().push_front(_int8->createOperand(INT8, "4"));
    std::deque<const IOperand *>::iterator it = abstractvm.getStackRef().begin();

  while (it != abstractvm.getStackRef().end())
    std::cout << (*it++)->toString() << std::endl;
    return 0;
}
