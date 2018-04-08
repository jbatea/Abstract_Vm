#include "../includes/Avm.hpp"

// Default constructor
Lexeme::Lexeme( void ) {
    return;
}

Lexeme::Lexeme( std::string const & value, eCategory category) {
    this->_value = value;
    this->_category = category;
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
	std::map<std::string, eInstruction> instructions {{"push", PUSH}, {"pop", POP}, {"dump", DUMP}, {"assert", ASSERT}, {"add", ADD}, {"sub", SUB}, {"mul", MUL}, {"div", DIV}, {"mod", MOD}, {"print", PRINT}, {"exit", EXIT}};
    std::map<std::string, eInstruction>::iterator it = instructions.find(this->_value);
    return it->second;
}

eCategory Lexeme::getCategory() const {
    return this->_category;
}

std::string const & Lexeme::getValue() const {
	return this->_value;
}
