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
    void                                    print( void );
    void                                    assert( std::string const & value );
    void                                    exit( std::string const & error );
    void                                    add( void );
    void                                    sub( void );
    void                                    mul( void );
    void                                    div( void );
    void                                    mod( void );

private:

    std::deque<const IOperand *>            _stack;
    void                                    isFiles(char *av);
    void                                    isLines(void);

};
#endif
