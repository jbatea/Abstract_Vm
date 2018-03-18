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

std::string const Lexeme::getCategory() const {
	const std::string lexemeList[] = {"INSTR", "VALUE", "SEP", "COM"};
    return lexemeList[this->_category];
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
