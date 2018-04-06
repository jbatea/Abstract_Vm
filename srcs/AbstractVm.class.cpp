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

void  AbstractVm::pop( unsigned long erase ) noexcept(false) {
	if (erase == 1) this->getLexer().setInstruction(POP);
    if (this->_getStackRef().size() < erase) throw AbstractVmException("Empty Stack");
    this->_getStackRef().erase(this->_getStackRef().begin(), this->_getStackRef().begin()+erase);
    return;
}

void  AbstractVm::dump( void ) {
    std::deque<const IOperand *>::iterator it = this->_getStackRef().begin();

	this->getLexer().setInstruction(DUMP);
    std::cout << "Avm:: Dump: " << std::endl;
    while (it != this->_getStackRef().end())
        std::cout << (*it++)->toString() << std::endl;
    return;
}

void AbstractVm::exit(std::string const & error) {
    std::cout << this->getLexer().getInstruction() << "::" << error << std::endl;
    this->~AbstractVm();
    std::exit(0);
}

void AbstractVm::assert( eOperandType type, std::string const & value ) noexcept(false) {

	this->getLexer().setInstruction(ASSERT);
    if (this->_getStackRef().empty()) throw AbstractVmException("Empty Stack");
    if (this->_getStackRef()[0]->toString().compare(value))
    	throw AbstractVmException("Expected Value -> " + value + " Front Stack Value -> " + this->_getStackRef()[0]->toString());
    if (this->_getStackRef()[0]->getType() != type)
		throw AbstractVmException(this->_getStackRef()[0]->getType(), "Type");
    std::cout << "Assert::Success:: Value -> " << value << std::endl;
    return;
}

void AbstractVm::print( void ) noexcept(false) {

	this->getLexer().setInstruction(PRINT);
    if (this->_getStackRef().empty()) throw AbstractVmException("Empty Stack");
    if (this->_getStackRef()[0]->getType() != INT8) throw AbstractVmException("Not a 8bit integer");
    std::cout << "Print: " <<  static_cast<char>(stoi(this->_getStackRef()[0]->toString())) << std::endl;
    return;
}

void				AbstractVm::doOp(eInstruction op) noexcept(false) {
 	const IOperand         *v1;
    const IOperand         *v2;
    const IOperand         *result;

	this->getLexer().setInstruction(op);
 	if (this->_getStackRef().size() < 2)
 		throw AbstractVmException("Missing operands");
 	if ((op == DIV || op == MOD) && !this->_getStackRef()[0]->toString().compare("0"))
 		throw AbstractVmException("Right Operand is 0");
    v1 = this->_getStackRef()[0];
    v2 = this->_getStackRef()[1];
    this->pop(2);
    switch (op) {
    	case ADD: result = *v2 + *v1; break;
    	case SUB: result = *v2 - *v1; break;
    	case MUL: result = *v2 * *v1; break;
    	case DIV: result = *v2 / *v1; break;
    	case MOD: result = *v2 % *v1; break;
    	default: break;
    }
    this->_push(result);
    return;
}


void  AbstractVm::create( eOperandType type, std::string const & value ) noexcept(false) {
	this->getLexer().setInstruction(PUSH);
    this->_push(Factory::getFactory()->createOperand(type, value));
    return;
};

void  AbstractVm::_push( const IOperand *operand ) {
//    std::cout << "Avm:: Push: " << std::endl;
    this->_getStackRef().push_front(operand);
    return;
};

void AbstractVm::printLexemes() {
    std::deque<const Lexeme *>::iterator it = this->getLexer().getLexemes().begin();
    while (it != this->getLexer().getLexemes().end()) {
		if ((*it)->getCategory() == "SEP") std::cout << std::endl;
        else std::cout << "{cat:" << (*it)->getCategory() << ",val:" << (*it)->getValue() << "}";
         this->_parse(*it);
        *it++;
    }
    return;
}

void	AbstractVm::_parse(const Lexeme * lexeme) {
	typedef void (AbstractVm::*op)(void);
		op a[] = {
//			&AbstractVm::pop,
			&AbstractVm::print,
			&AbstractVm::dump,
//			&AbstractVm::exit
		 };
		 (void)lexeme;
		 (this->*a[0])();
}

Lexer & AbstractVm::getLexer(){
	return this->_lexer;
}
