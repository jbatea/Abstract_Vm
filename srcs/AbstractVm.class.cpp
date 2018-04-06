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

void AbstractVm::assert(std::string const & value ) noexcept(false) {
	std::smatch match;
	std::regex_search(value, match, std::regex("\\(\\d*(.\\d*)?\\)"));

	this->getLexer().setInstruction(ASSERT);
    if (this->_getStackRef().empty()) throw AbstractVmException("Empty Stack");
    if (this->_getStackRef()[0]->toString().compare(match.str().substr(1, match.size())))
    	throw AbstractVmException("Expected Value -> " + value + " Front Stack Value -> " + this->_getStackRef()[0]->toString());
    if (this->_getStackRef()[0]->getType() != INT8)
		throw AbstractVmException(this->_getStackRef()[0]->getType(), "Type");
    std::cout << "Assert::Success:: Value -> " << match.str().substr(1, match.size()) << std::endl;
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

void            AbstractVm::_doInstr(eInstruction instr, std::string value) {
	switch (instr) {
		case ADD:
		case SUB:
		case MUL:
		case DIV:
		case MOD:
			this->doOp(instr); break;
		case EXIT: this->exit("Instr exit was called"); break;
		case PRINT: this->print(); break;
		case ASSERT: this->assert(value); break;
		case PUSH: this->create(value); break;
		case POP: this->pop(1); break;
		case DUMP: this->dump(); break;
		default: break;
	}
	return;
}

void  AbstractVm::create(std::string const & value ) noexcept(false) {
//	eOperandType type;
	std::smatch match;
	std::map<std::string, eOperandType> types {{"int8", INT8}, {"int16", INT16}, {"int32", INT32}, {"float", FLOAT}, {"double", DOUBLE}};


	std::regex_search(value, match, std::regex("\\(\\d*(.\\d*)?\\)"));
	this->getLexer().setInstruction(PUSH);
    this->_push(Factory::getFactory()->createOperand(INT8, match.str().substr(1, match.size())));
      std::cout << "PUSH -> " << match.str().substr(1, match.size()) << std::endl;
    return;
};

void  AbstractVm::_push( const IOperand *operand ) {
//    std::cout << "Avm:: Push: " << std::endl;
    this->_getStackRef().push_front(operand);
    return;
};

void AbstractVm::parseLexemes() {
    std::deque<const Lexeme *>::iterator it = this->getLexer().getLexemes().begin();
    eInstruction instr;

    while (it != this->getLexer().getLexemes().end()) {
        if ((*it)->getCategory() == "INSTR" && std::regex_match((*it)->getValue(), std::regex("(push|assert)"))) {
            instr = (*it)->getInstruction();
            *it++;
            this->_doInstr(instr, (*it)->getValue());
        }
        else this->_doInstr((*it)->getInstruction(), NULL);
        if (it != this->getLexer().getLexemes().end()) *it++;
    }
    return;
}

Lexer & AbstractVm::getLexer(){
	return this->_lexer;
}
