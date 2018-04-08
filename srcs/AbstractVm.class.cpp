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

void  AbstractVm::pop( void ) noexcept(false) {
    if (this->_getStackRef().empty()) throw AbstractVmException("Empty Stack");
    this->_getStackRef().pop_front();
    return;
}

void  AbstractVm::dump( void ) {
    std::deque<const IOperand *>::iterator it = this->_getStackRef().begin();

    while (it != this->_getStackRef().end())
        std::cout << (*it++)->toString() << std::endl;
    return;
}

void AbstractVm::exit(std::string const & error) {
    std::cout << "Exit::"<< error << std::endl;
    this->~AbstractVm();
    std::exit(0);
}

void AbstractVm::assert(eOperandType type, std::string const & value) noexcept(false) {

    if (this->_getStackRef().empty()) throw AbstractVmException("Empty Stack");
    if (this->_getStackRef()[0]->toString().compare(value))
    	throw AbstractVmException("Expected Value -> " + value + " Front Stack Value -> " + this->_getStackRef()[0]->toString());
    if (this->_getStackRef()[0]->getType() != type)
		throw AbstractVmException(this->_getStackRef()[0]->getType(), "Wrong Type:: Front Stack Type -> ");
    std::cout << "Assert::Success:: Value -> " << value << std::endl;
    return;
}

void AbstractVm::print( void ) noexcept(false) {

    if (this->_getStackRef().empty()) throw AbstractVmException("Empty Stack");
    if (this->_getStackRef()[0]->getType() != INT8) throw AbstractVmException("Not a 8bit integer");
    std::cout << "Print: " <<  static_cast<char>(stoi(this->_getStackRef()[0]->toString())) << std::endl;
    return;
}

void				AbstractVm::_doOp(eInstruction op) noexcept(false) {
 	const IOperand         *v1;
    const IOperand         *v2;
    const IOperand         *result;

 	if (this->_getStackRef().size() < 2) throw AbstractVmException("Missing operands");
 	if ((op == DIV || op == MOD) && !this->_getStackRef()[0]->toString().compare("0"))
 		throw AbstractVmException("Right Operand is 0");
    v1 = this->_getStackRef()[0];
    v2 = this->_getStackRef()[1];
    this->_getStackRef().erase(this->_getStackRef().begin(), this->_getStackRef().begin()+2);
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

void            AbstractVm::_doInstr(eInstruction instr, std::string value) {
	switch (instr) {
		case ADD: case SUB: case MUL: case DIV: case MOD: this->_doOp(instr); break;
		case EXIT: this->exit("End Of Program"); break;
		case PRINT: this->print(); break;
		case ASSERT: this->assert(this->_parseType(value), this->_parseValue(value)); break;
		case PUSH: this->create(this->_parseType(value), this->_parseValue(value)); break;
		case POP: this->pop(); break;
		case DUMP: this->dump(); break;
		default: break;
	}
	return;
}

void  AbstractVm::create(eOperandType type, std::string const & value ) noexcept(false) {
    this->_push(Factory::getFactory()->createOperand(type, value));
    return;
};

std::string AbstractVm::_parseValue(std::string const & value) {
	std::smatch match;
	std::regex_search(value, match, std::regex("\\(-?\\d*(.\\d*)?\\)"));
	return match.str().substr(1, match.length() - 2);
}

eOperandType AbstractVm::_parseType(std::string const & value) {
	std::map<std::string, eOperandType> types {{"int8", INT8}, {"int16", INT16}, {"int32", INT32}, {"float", FLOAT}, {"double", DOUBLE}};
	std::smatch match;
	std::regex_search(value, match, std::regex("(int8|int16|int32|float|double)"));
	std::map<std::string, eOperandType>::iterator it = types.find(match.str());
	return it->second;
}

void  AbstractVm::_push( const IOperand *operand ) {
    this->_getStackRef().push_front(operand);
    return;
};

void AbstractVm::parseLexemes() {
    std::deque<const Lexeme *>::iterator it = this->getLexer().getLexemes().begin();

    while (it != this->getLexer().getLexemes().end()) {
        if ((*it)->getCategory() == INSTR) {
        	std::regex_match((*it)->getValue(), std::regex("(push|assert)")) ?
            this->_doInstr((*it)->getInstruction(), (*(it + 1))->getValue()) :
            this->_doInstr((*it)->getInstruction(), "");
        }
        *it++;
    }
    return;
}

Lexer & AbstractVm::getLexer(){
	return this->_lexer;
}