#include "../includes/Avm.hpp"

// Default constructor
Lexeme::Lexeme( void ) {
    return;
}

Lexeme::Lexeme( std::string const & value, eCategory category) {
	this->_value = value;
	this->_category = category;
	this->_setInstruction();
    return;
}

 // Copy constructor
 Lexeme::Lexeme(Lexeme const & src) {
     *this = src;
     return;
 }

 // Destructor
Lexeme::~Lexeme( void ) {
    return;
}

// Assignement
Lexeme & Lexeme::operator=( Lexeme const & rhs) {

    if (this != &rhs)
        *this = rhs;
    return *this;
}

eInstruction Lexeme::getInstruction() const {
	return this->_instruction;
}

std::string const Lexeme::getCategory() const {
	const std::string lexemeList[] = {"INSTR", "VALUE", "SEP", "COM"};
    return lexemeList[this->_category];
}

void Lexeme::_setInstruction(void) {
	std::map<std::string, eInstruction> instructions {{"push", PUSH}, {"pop", POP}, {"dump", DUMP}, {"assert", ASSERT}, {"add", ADD}, {"sub", SUB}, {"mul", MUL}, {"div", DIV}, {"mod", MOD}, {"print", PRINT}, {"exit", EXIT}};

	if (this->getCategory() != "INSTR") return;
	std::map<std::string, eInstruction>::iterator it = instructions.find(this->_value);
	this->_instruction = it->second;
	return;
}

void Lexeme::setCategory(eCategory category) {
	this->_category = category;
	return;
}

void Lexeme::setValue(std::string const & value) {
	this->_value = value;
	return;
}

std::string const & Lexeme::getValue() const {
	return this->_value;
}
