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
    std::deque<const IOperand *>::iterator it = this->_getStackRef().begin();
      while (it != this->_getStackRef().end())
            (*it++)->~IOperand();
    return;
}

// Assignement
AbstractVm & AbstractVm::operator=( AbstractVm const & rhs) {

    if (this != &rhs)
        *this = rhs;
    return *this;
}

std::deque<const IOperand *> & AbstractVm::_getStackRef( void ) {
    return this->_stack;
}


const std::string  AbstractVm::_getTypeAsString(eOperandType type) const {
	const std::string typeList[] = {"INT8", "INT16", "INT32", "FLOAT", "DOUBLE"};
	return typeList[type];
}

const std::string  AbstractVm::_getOpAsString(eOperator op) const {
	const std::string opList[] = {"ADD", "SUB", "MUL", "DIV", "MOD"};
	return opList[op];
}

void  AbstractVm::pop( unsigned long erase ) noexcept(false) {
    if (this->_getStackRef().size() < erase) throw AbstractVmException("Pop:: Empty Stack");
    this->_getStackRef().erase(this->_getStackRef().begin(), this->_getStackRef().begin()+erase);
    return;
}

void  AbstractVm::dump( void ) {
    std::deque<const IOperand *>::iterator it = this->_getStackRef().begin();

    std::cout << "Avm:: Dump: " << std::endl;
    while (it != this->_getStackRef().end())
        std::cout << (*it++)->toString() << std::endl;
    return;
}

void AbstractVm::exit(std::string const & error) {
    std::cout << error << std::endl;
    this->~AbstractVm();
    std::exit(0);
}

void AbstractVm::assert( eOperandType type, std::string const & value ) noexcept(false) {

    if (this->_getStackRef().empty()) throw AbstractVmException("Assert:: Empty Stack");
    if (this->_getStackRef()[0]->toString().compare(value))
    	throw AbstractVmException("Assert:: Expected Value -> " + value + " Front Stack Value -> " + this->_getStackRef()[0]->toString());
    if (this->_getStackRef()[0]->getType() != type)
		throw AbstractVmException("Assert:: Expected Type -> "  + this->_getTypeAsString(type) +
			" Front Stack Type -> " + this->_getTypeAsString(this->_getStackRef()[0]->getType()));
    std::cout << "Assert::Success:: Type -> " << this->_getTypeAsString(type) << " Value -> " << value << std::endl;
    return;
}

void AbstractVm::print( void ) noexcept(false) {

    if (this->_getStackRef().empty()) throw AbstractVmException("Print:: Empty Stack");
    if (this->_getStackRef()[0]->getType() != INT8) throw AbstractVmException("Print:: Not a 8bit integer");
    std::cout << "Avm:: Print: " <<  static_cast<char>(stoi(this->_getStackRef()[0]->toString())) << std::endl;
    return;
}

void				AbstractVm::doOp(eOperator op) noexcept(false) {
 	const IOperand         *v1;
    const IOperand         *v2;
    const IOperand         *result;

 	if (this->_getStackRef().size() < 2)
 		throw AbstractVmException(this->_getOpAsString(op) + ":: Missing operands");
 	if ((op == DIV || op == MOD) && !this->_getStackRef()[0]->toString().compare("0"))
 		throw AbstractVmException(this->_getOpAsString(op) + ":: Right Operand is 0");
    v1 = this->_getStackRef()[0];
    v2 = this->_getStackRef()[1];
    this->pop(2);
    switch (op) {
    	case ADD: result = *v2 + *v1; break;
    	case SUB: result = *v2 - *v1; break;
    	case MUL: result = *v2 * *v1; break;
    	case DIV: result = *v2 / *v1; break;
    	case MOD: result = *v2 % *v1; break;
    }
    this->_push(result);
    return;
}


void  AbstractVm::create( eOperandType type, std::string const & value ) noexcept(false) {
    this->_push(Factory::getFactory()->createOperand(type, value));
    return;
};

void  AbstractVm::_push( const IOperand *operand ) {
//    std::cout << "Avm:: Push: " << std::endl;
    this->_getStackRef().push_front(operand);
    return;
};