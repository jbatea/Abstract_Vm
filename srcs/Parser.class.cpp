#include "../includes/Avm.hpp"


// Default constructor
Parser::Parser( void ) {
    return;
}

 // Copy constructor
 Parser::Parser(Parser const & src) {
    this->_stack = src.getStack();
    return;
 }

 // Destructor
Parser::~Parser( void ) {
    std::deque<const IOperand *>::iterator it = this->_getStackRef().begin();
    while (it != this->_getStackRef().end()) delete(*it++);
    return;
}

// Assignement
Parser & Parser::operator=( Parser const & rhs) {
    if (this != &rhs)
        this->_stack = rhs.getStack();
    return *this;
}

std::string Parser::_parseValue(std::string const & value) {
	std::smatch match;
	std::regex_search(value, match, std::regex("\\(-?\\d*(.\\d*)?\\)"));
	return match.str().substr(1, match.length() - 2);
}

eOperandType Parser::_parseType(std::string const & value) {
	std::map<std::string, eOperandType> types {{"int8", INT8}, {"int16", INT16}, {"int32", INT32}, {"float", FLOAT}, {"double", DOUBLE}};
	std::smatch match;
	std::regex_search(value, match, std::regex("(int8|int16|int32|float|double)"));
	std::map<std::string, eOperandType>::iterator it = types.find(match.str());
	return it->second;
}

void Parser::parseLexemes(Lexer const & lexer) noexcept(false) {
    std::deque<const Lexeme *>::const_iterator it = lexer.getLexemes().begin();
    bool exit = false;

    while (it != lexer.getLexemes().cend() && !exit) {
        if ((*it)->getCategory() == INSTR) {
            try {
        	    std::regex_match((*it)->getValue(), std::regex("(push|assert)")) ?
                this->_doInstr((*it)->getInstruction(), (*(it + 1))->getValue()) :
                this->_doInstr((*it)->getInstruction(), "");
            } catch (AbstractVmException e) { e.toString(); }
            exit = !(*it)->getValue().compare("exit");
        }
        *it++;
    }
    return;
}

std::deque<const IOperand *> & Parser::_getStackRef( void ) {
    return this->_stack;
}

std::deque<const IOperand *> const &  Parser::getStack( void ) const  {
    return this->_stack;
}

void  Parser::pop( void ) noexcept(false) {
    if (this->_getStackRef().empty()) throw AbstractVmException("Pop:: " + VAL +  "Empty Stack" + RESET);
    delete(this->_getStackRef()[0]);
    this->_getStackRef().pop_front();
    return;
}

void  Parser::dump( void ) {
    std::deque<const IOperand *>::iterator it = this->_getStackRef().begin();

	std::cout << SUCCESS << "Dump::" << RESET << std::endl;
    while (it != this->_getStackRef().end())
            std::cout << VAL << (*it++)->toString() << RESET << std::endl;
    return;
}

void Parser::assert(eOperandType type, std::string const & value) noexcept(false) {

    if (this->_getStackRef().empty()) throw AbstractVmException("Assert:: " + VAL + "Empty Stack" + RESET);
    if (stold(this->_getStackRef()[0]->toString()) != stold(value))
    	throw AbstractVmException("Assert:: " + VAL + value + RESET);
    if (this->_getStackRef()[0]->getType() != type)
		throw AbstractVmException(this->_getStackRef()[0]->getType(),"Assert:: " + VAL +  "Wrong Type ::" + RESET);
    std::cout << SUCCESS << "Assert:: " << VAL << value << RESET << std::endl;
    return;
}

void Parser::print( void ) noexcept(false) {

    if (this->_getStackRef().empty()) throw AbstractVmException("Print:: " + VAL + "Empty Stack" + RESET);
    if (this->_getStackRef()[0]->getType() != INT8) throw AbstractVmException("Print:: " + VAL + "Not a 8bit integer" + RESET);
    std::cout << SUCCESS << "Print:: " << VAL << static_cast<char>(stoi(this->_getStackRef()[0]->toString())) << RESET << std::endl;
    return;
}

void				Parser::_doOp(eInstruction op) noexcept(false) {
 	const IOperand         *v1;
    const IOperand         *v2;
    const IOperand         *result;

 	if (this->_getStackRef().size() < 2) throw AbstractVmException(this->_getInstr(op) + ":: " + VAL + "Missing operands" + RESET);
 	if ((op == DIV || op == MOD) && stold(this->_getStackRef()[0]->toString()) == 0)
 		throw AbstractVmException(this->_getInstr(op) + ":: " + VAL + "Right Operand is 0" + RESET);
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
    delete(v1);
    delete(v2);
    this->_push(result);
    return;
}

std::string Parser::_getInstr(eInstruction instr) const {
	const std::string instrList[] = {"Push", "Pop", "Dump", "Assert", "Add", "Sub", "Mul", "Div", "Mod", "Print", "Exit"};
	return instrList[instr];
}

void            Parser::_doInstr(eInstruction instr, std::string value) {
	switch (instr) {
		case ADD: case SUB: case MUL: case DIV: case MOD: this->_doOp(instr); break;
		case EXIT: std::cout << SUCCESS + "Exit:: " + VAL + "Instruction exit was called" + RESET << std::endl; break;
		case PRINT: this->print(); break;
		case ASSERT: this->assert(this->_parseType(value), this->_parseValue(value)); break;
		case PUSH: this->create(this->_parseType(value), this->_parseValue(value)); break;
		case POP: this->pop(); break;
		case DUMP: this->dump(); break;
		default: break;
	}
	return;
}

void  Parser::create(eOperandType type, std::string const & value ) noexcept(false) {
    this->_push(Factory::getFactory()->createOperand(type, value));
    return;
};

void  Parser::_push( const IOperand *operand ) {
    this->_getStackRef().push_front(operand);
    return;
};