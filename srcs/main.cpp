#include "../includes/Avm.hpp"

int     main(int ac, char **av)
{
    AbstractVm  abstractvm;
    Operand<int8_t>*operand = NULL;

    abstractvm.checkArg(ac, av);
    abstractvm.getStackRef().push_front(operand->createOperand(INT8, "127" ));
    abstractvm.getStackRef().push_front(operand->createOperand(INT16, "32767"));
    abstractvm.getStackRef().push_front(operand->createOperand(INT32, "2147483647"));
    abstractvm.getStackRef().push_front(operand->createOperand(FLOAT, "3.4028"));
    abstractvm.getStackRef().push_front(operand->createOperand(DOUBLE, "3.4028"));
    std::deque<const IOperand *>::iterator it = abstractvm.getStackRef().begin();

  while (it != abstractvm.getStackRef().end())
    std::cout << (*it++)->toString() << std::endl;
    return 0;
}
