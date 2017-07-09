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

    std::cout << "Dump: " << std::endl;
    while (it != this->getStackRef().end())
        std::cout << (*it++)->toString() << std::endl;return;
}

void AbstractVm::exit(std::string const & error) {
    std::cout << error << std::endl;
    std::exit(0);
}

void AbstractVm::assert( std::string const & value ) {

    if (std::strcmp(this->getStackRef().front()->toString().c_str(), value.c_str()))
        this->exit("Assert Failed"); return;
}

void AbstractVm::print( void ) {

    if (this->getStackRef().front()->getType() != INT8)
        this->exit("Print Failed");
    std::cout << static_cast<char>(atoi(this->getStackRef().front()->toString().c_str())) << std::endl;
    return;
}

void AbstractVm::add( void ) {

    int                 result;

    result = atoi(this->getStackRef().front()->toString().c_str());
    this->pop();
    result = result + atoi(this->getStackRef().front()->toString().c_str());
    this->pop();
    this->push<int8_t>(INT8, std::to_string(result));
    return;
}

void AbstractVm::sub( void ) {

    int                 result;

    result = atoi(this->getStackRef().front()->toString().c_str());
    this->pop();
    result = result - atoi(this->getStackRef().front()->toString().c_str());
    this->pop();
    this->push<int8_t>(INT8, std::to_string(result));
    return;
}

void AbstractVm::mul( void ) {

    int                 result;

    result = atoi(this->getStackRef().front()->toString().c_str());
    this->pop();
    result = result * atoi(this->getStackRef().front()->toString().c_str());
    this->pop();
    this->push<int8_t>(INT8, std::to_string(result));
    return;
}

void AbstractVm::div( void ) {

    int                 result;

    result = atoi(this->getStackRef().front()->toString().c_str());
    this->pop();
    result = result / atoi(this->getStackRef().front()->toString().c_str());
    this->pop();
    this->push<int8_t>(INT8, std::to_string(result));
    return;
}

void AbstractVm::mod( void ) {

    int                 result;

    result = atoi(this->getStackRef().front()->toString().c_str());
    this->pop();
    result = result % atoi(this->getStackRef().front()->toString().c_str());
    this->pop();
    this->push<int8_t>(INT8, std::to_string(result));
    return;
}
