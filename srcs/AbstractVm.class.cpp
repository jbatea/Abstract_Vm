#include "../includes/Avm.hpp"

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
    std::deque<const IOperand *>::iterator it = this->getStackRef().begin();
      while (it != this->getStackRef().end())
            (*it++)->~IOperand();
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

void  AbstractVm::pop( void ) {
    if (!this->getStackRef().front())
        this->exit("Pop:: Empty Stack");
    this->getStackRef().pop_front();
    return;
}

void  AbstractVm::dump( void ) {
    std::deque<const IOperand *>::iterator it = this->getStackRef().begin();

    std::cout << "Avm:: Dump: " << std::endl;
    while (it != this->getStackRef().end())
        std::cout << (*it++)->toString() << std::endl;
    return;
}

void AbstractVm::exit(std::string const & error) {
    std::cout << error << std::endl;
    this->~AbstractVm();
    std::exit(0);
}

void AbstractVm::assert( std::string const & value ) {

    if (this->getStackRef().front()->toString().compare(value))
        this->exit("Assert:: Failed");
    return;
}

void AbstractVm::print( void ) {

    if (this->getStackRef().front()->getType() != INT8)
        this->exit("Print:: Not a 8bit integer");
    std::cout << "Avm:: Print: " <<  static_cast<char>(stoi(this->getStackRef().front()->toString())) << std::endl;
    return;
}

void AbstractVm::add( void ) {

    const IOperand         *result;

    if (this->getStackRef().size() < 2)
        this->exit("Add:: Missing operands");
  	result = this->getStackRef().front();
  	this->pop();
  	result = *result + *(this->getStackRef().front());
  	this->pop();
  	this->push(result);
    return;
}

void AbstractVm::sub( void ) {

const IOperand         *result;

  	result = this->getStackRef().front();
  	this->pop();
  	result = *(this->getStackRef().front()) - *result;
  	this->pop();
  	this->push(result);
    return;
}

void AbstractVm::mul( void ) {
const IOperand         *result;

  	result = this->getStackRef().front();
  	this->pop();
  	result = *(this->getStackRef().front()) * *result;
  	this->pop();
  	this->push(result);
    return;
}

void AbstractVm::div( void ) {
const IOperand         *result;

  	result = this->getStackRef().front();
  	this->pop();
  	result = *(this->getStackRef().front()) / *result;
  	this->pop();
  	this->push(result);
    return;
}

void AbstractVm::mod( void ) {
    const IOperand         *result;

      	result = this->getStackRef().front();
      	this->pop();
      	result = *(this->getStackRef().front()) % *result;
      	this->pop();
      	this->push(result);
    return;
}

void  AbstractVm::create( eOperandType type, std::string const & value ) {
    std::cout << "Avm:: Create: " << std::endl;
    this->push(Factory::getFactory()->createOperand(type, value));
    return;
  };

void  AbstractVm::push( const IOperand *operand ) {
    std::cout << "Avm:: Push: " << std::endl;
    this->getStackRef().push_front(operand);
    return;
  };