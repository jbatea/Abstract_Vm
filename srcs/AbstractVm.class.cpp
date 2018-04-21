#include "../includes/Avm.hpp"

// Default constructor
AbstractVm::AbstractVm( void ) {
    return;
}

 // Copy constructor
 AbstractVm::AbstractVm(AbstractVm const & src) {
     this->_lexer = src.getLexer();
     this->_parser = src.getParser();
     return;
 }

 AbstractVm::AbstractVm(int ac, char **av) {
    this->start(ac, av);
    return;
 }

 // Destructor
AbstractVm::~AbstractVm( void ) {
    return;
}

// Assignement
AbstractVm & AbstractVm::operator=( AbstractVm const & rhs) {
    if (this != &rhs) {
        this->_lexer =rhs.getLexer();
        this->_parser = rhs.getParser();
    }
    return *this;
}

Lexer const & AbstractVm::getLexer() const {
	return this->_lexer;
}

Parser const & AbstractVm::getParser() const {
	return this->_parser;
}

void    AbstractVm::start(int ac, char **av) {

	this->_lexer.getArg(ac, av);
	this->_parser.parseLexemes(this->_lexer);
	return;
}