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

void  AbstractVm::pop( void ) noexcept(false) {
    if (!this->getStackRef().size()) throw AbstractVmException("Pop:: Empty Stack");
    this->getStackRef().pop_front();
    return;
}

const std::string  AbstractVm::_getTypeAsString(eOperandType type) const {
	const std::string typeList[] = {"INT8", "INT16", "INT32", "FLOAT", "DOUBLE"};
	return typeList[type];
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

void AbstractVm::assert( eOperandType type, std::string const & value ) noexcept(false) {

    if (!this->getStackRef().size()) throw AbstractVmException("Assert:: Empty Stack");
    if (this->getStackRef().front()->toString().compare(value))
    	throw AbstractVmException("Assert:: Expected Value -> " + value + " Front Stack Value -> " + this->getStackRef().front()->toString());
    if (this->getStackRef().front()->getType() != type)
		throw AbstractVmException("Assert:: Expected Type -> "  + this->_getTypeAsString(type) +
			" Front Stack Type -> " + this->_getTypeAsString(this->getStackRef().front()->getType()));
    std::cout << "Assert::Success:: Type -> " << this->_getTypeAsString(type) << " Value -> " << value << std::endl;
    return;
}

void AbstractVm::print( void ) noexcept(false) {

    if (!this->getStackRef().size()) throw AbstractVmException("Print:: Empty Stack");
    if (this->getStackRef().front()->getType() != INT8) throw AbstractVmException("Print:: Not a 8bit integer");
    std::cout << "Avm:: Print: " <<  static_cast<char>(stoi(this->getStackRef().front()->toString())) << std::endl;
    return;
}

void AbstractVm::add( void ) noexcept(false) {

    const IOperand         *result;
    std::cout << "Avm:: Add: " << std::endl;

    if (this->getStackRef().size() < 2) throw AbstractVmException("Add:: Missing operands");
  	result = this->getStackRef().front();
  	this->pop();
  	result = *result + *(this->getStackRef().front());
  	this->pop();
  	this->_push(result);
    return;
}

void AbstractVm::sub( void ) noexcept(false) {

const IOperand         *result;
    std::cout << "Avm:: Sub: " << std::endl;

    if (this->getStackRef().size() < 2) throw AbstractVmException("Sub:: Missing operands");
  	result = this->getStackRef().front();
  	this->pop();
  	result = *(this->getStackRef().front()) - *result;
  	this->pop();
  	this->_push(result);
    return;
}

void AbstractVm::mul( void ) noexcept(false) {

	const IOperand         *result;

    std::cout << "Avm:: Mul: " << std::endl;
    if (this->getStackRef().size() < 2) throw AbstractVmException("Mul:: Missing operands");
  	result = this->getStackRef().front();
  	this->pop();
  	result = *(this->getStackRef().front()) * *result;
  	this->pop();
  	this->_push(result);
    return;
}

void AbstractVm::div( void ) noexcept(false) {

	const IOperand         *result;
    std::cout << "Avm:: Div: " << std::endl;
    if (this->getStackRef().size() < 2) throw AbstractVmException("Div:: Missing operands");
    if (!this->getStackRef().front()->toString().compare("0")) throw AbstractVmException("Div:: Right Operand is 0");
  	result = this->getStackRef().front();
  	this->pop();
  	result = *(this->getStackRef().front()) / *result;
  	this->pop();
  	this->_push(result);
    return;
}

void AbstractVm::mod( void ) noexcept(false) {
    const IOperand         *result;
    std::cout << "Avm:: Mod: " << std::endl;

   		if (this->getStackRef().size() < 2) throw AbstractVmException("Mod:: Missing operands");
      	if (!this->getStackRef().front()->toString().compare("0")) throw AbstractVmException("Div:: Right Operand is 0");
      	result = this->getStackRef().front();
      	this->pop();
      	result = *(this->getStackRef().front()) % *result;
      	this->pop();
      	this->_push(result);
    return;
}

void  AbstractVm::create( eOperandType type, std::string const & value ) noexcept(false) {
    this->_push(Factory::getFactory()->createOperand(type, value));
    return;
};

void  AbstractVm::_push( const IOperand *operand ) {
//    std::cout << "Avm:: Push: " << std::endl;
    this->getStackRef().push_front(operand);
    return;
};