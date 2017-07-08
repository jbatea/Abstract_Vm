#ifndef ABSTRACTVM_CLASS_HPP
#define ABSTRACTVM_CLASS_HPP

#include "Avm.hpp"

class AbstractVm {

public:

    AbstractVm( void ); // Default constructor
    AbstractVm( AbstractVm const & src ); // Copy constructor
    ~AbstractVm( void ); // Destructor
    AbstractVm & operator=( AbstractVm const & rhs );// Assignement

    void                            checkArg( int ac, char **av ); // Verif arg;
    std::deque<const IOperand *> &  getStackRef( void ); // Stack getter
    std::deque<const IOperand *>    getStack( void ) const; // Stack getter
    template <typename T>
    IOperand const *                callFactory(eOperandType type, std::string const & value) {
        Operand<T> const *operand = NULL; return(operand->createOperand(type, value)); };

private:

    void isFiles(char *av);
    void isLines(void);
    std::deque<const IOperand *> _stack;

};
#endif
