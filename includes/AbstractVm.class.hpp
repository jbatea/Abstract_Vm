#ifndef ABSTRACTVM_CLASS_HPP
#define ABSTRACTVM_CLASS_HPP

#include "Avm.hpp"

class AbstractVm {

public:

    AbstractVm( void ); // Default constructor
    AbstractVm( AbstractVm const & src ); // Copy constructor
    ~AbstractVm( void ); // Destructor
    AbstractVm & operator=( AbstractVm const & rhs );// Assignement

    void                                    checkArg( int ac, char **av ); // Verif arg;
    std::deque<const IOperand *> &          getStackRef( void ); // Stack getter
    std::deque<const IOperand *>            getStack( void ) const; // Stack getter
    template <typename T> IOperand const *  callFactory(eOperandType type, std::string const & value) { Operand<T> const *operand = NULL; return(operand->createOperand(type, value)); };
    template <typename T> void              push( eOperandType type, std::string const & value ) { this->getStackRef().push_front(this->callFactory<T>(type, value)); return; };
    void                                    pop( void );
    void                                    dump( void );
    void                                    exit( void );

private:

    template <typename T> void  assert( eOperandType type, std::string const & value ) { this->getStackRef().push_front(this->callFactory<T>(type, value)); return; };
    template <typename T> void  add( eOperandType type, std::string const & value ) { this->getStackRef().push_front(this->callFactory<T>(type, value)); return; };
    template <typename T> void  sub( eOperandType type, std::string const & value ) { this->getStackRef().push_front(this->callFactory<T>(type, value)); return; };
    template <typename T> void  mul( eOperandType type, std::string const & value ) { this->getStackRef().push_front(this->callFactory<T>(type, value)); return; };
    template <typename T> void  div( eOperandType type, std::string const & value ) { this->getStackRef().push_front(this->callFactory<T>(type, value)); return; };
    template <typename T> void  mod( eOperandType type, std::string const & value ) { this->getStackRef().push_front(this->callFactory<T>(type, value)); return; };
    template <typename T> void  print( eOperandType type, std::string const & value ) { this->getStackRef().push_front(this->callFactory<T>(type, value)); return; };
    std::deque<const IOperand *>            _stack;
    void                                    isFiles(char *av);
    void                                    isLines(void);

};
#endif
