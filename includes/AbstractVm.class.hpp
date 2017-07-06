#ifndef ABSTRACTVM_CLASS_HPP
#define ABSTRACTVM_CLASS_HPP

#include "Avm.hpp"

class AbstractVm {

public:

    AbstractVm( void ); // Default constructor
    AbstractVm(AbstractVm const & src); // Copy constructor
    ~AbstractVm( void ); // Destructor
    AbstractVm & operator=( AbstractVm const & rhs);// Assignement

    void checkArg(int ac, char **av) ;

private:

    void isFiles(char *av);
    void isLines(void);
    std::deque<IOperand *> _stack;

};
#endif
