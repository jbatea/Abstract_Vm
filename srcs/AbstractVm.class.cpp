#include "../includes/AbstractVm.class.hpp"

// Default constructor
AbstractVm::AbstractVm( void ) {
    return;
}

 // Copy constructor
 AbstractVm::AbstractVm(AbstractVm const & src) {
     *this = src;
     return;
 }

 // Destructor
AbstractVm::~AbstractVm( void ) {
    return;
}

// Assignement
AbstractVm & AbstractVm::operator=( AbstractVm const & rhs) {

    if (this != &rhs)
        *this = rhs;
    return *this;
}

std::deque<const IOperand *> & AbstractVm::getStackRef( void ) {

    return this->_stack;
}

std::deque<const IOperand *>  AbstractVm::getStack( void ) const {

    return this->_stack;
}

void AbstractVm::checkArg( int ac, char **av) {

    if (ac == 2)
        this->isFiles(av[1]);
    else if (ac == 1)
        this->isLines();
    else
        std::cout << "Too much arguments, Usage: ./avm Or ./avm ./sample.avm" << std::endl;
    return;
}

void AbstractVm::isFiles(char *av) {

    (void)av;
    return;
}

void AbstractVm::isLines() {
        return;
}

void  AbstractVm::pop( void ) {
    this->getStackRef().pop_front();
    return;
}

void  AbstractVm::dump( void ) {
    std::deque<const IOperand *>::iterator it = this->getStackRef().begin();

    while (it != this->getStackRef().end())
        std::cout << (*it++)->toString() << std::endl;return;
}

void AbstractVm::exit(void) {
    std::exit(0);
}
