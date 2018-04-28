#include "../includes/Avm.hpp"


// Default constructor
Lexer::Lexer( void ) {
    return;
}

 // Copy constructor
 Lexer::Lexer(Lexer const & src) {
     this->_lexemes = src.getLexemes();
     return;
 }

 // Destructor
Lexer::~Lexer( void ) {
	std::deque<const Lexeme *>::iterator it = this->_lexemes.begin();
    while (it != this->_lexemes.end()) delete(*it++);
    return;
}

// Assignement
Lexer & Lexer::operator=( Lexer const & rhs) {

    if (this != &rhs)
        this->_lexemes = rhs.getLexemes();
    return *this;
}

std::deque<const Lexeme *> const & Lexer::getLexemes(void) const {
	return this->_lexemes;
}

eCategory				Lexer::_getLexemeCategory(std::string const & _lexeme) {
	if (std::regex_match(_lexeme, std::regex("^(push|pop|dump|assert|add|sub|mul|div|mod|print|exit)$")))
		return INSTR;
	return VALUE;
}

void Lexer::_lexer(std::string const & line) noexcept(false) {
	std::istringstream 	stream;
	std::string 		_lexeme;
	std::string 		res;
	std::regex lex ("^((pop|dump|add|sub|mul|div|mod|print|exit)|((assert|push) (((int(8|16|32)\\(-?\\d+\\)))|((float|double)\\(-?\\d+[.]\\d+\\)))))?(\\s*;.*)?$");
	std::regex instr ("^\\w*( \\w*\\(-?\\d+(.\\d+)?\\)?)?(\\s*;.*)?$");

	if (!std::regex_match(line, instr)) throw AbstractVmException("Syntax error::  " + VAL + line + RESET);
	if (!std::regex_match(line, lex)) throw AbstractVmException("Lexical error:: " + VAL + line + RESET);
	std::regex_replace(std::back_inserter(res), line.begin(), line.end(), std::regex(".*;.*$"), "$`");
	stream.str(res);
	while (std::getline(stream, _lexeme, ' '))
		this->_lexemes.push_back(new Lexeme(_lexeme, this->_getLexemeCategory(_lexeme)));
	return;
}

void Lexer::_getLine(std::string line) noexcept(false) {
	try { this->_lexer(line); } catch (AbstractVmException e) { e.toString(); }
}

void Lexer::_getFile(int ac, char **av) noexcept(false) {
	std::string		line;
	std::ifstream	file;
	bool timeout = false;

	for (int i = 1; i < ac; i++) {

		try {
			file.open(av[i], std::ifstream::in);
			if (!file.is_open()) throw AbstractVmException("Failed to open file:: " + VAL + av[i] + RESET);
			std::thread([&]{
					std::this_thread::sleep_for(std::chrono::seconds(1));
                     timeout = true;
            }).detach();
			while (std::getline(file, line) && timeout == false) {
				this->_getLine(line);
				timeout = false;
			}
			if (timeout) throw AbstractVmException("Failed to read file :: " + VAL + av[i] + RESET);
			file.close();
			return;
		} catch (AbstractVmException e) { e.toString(); }
	}
	return;
}

void Lexer::_getInput(void) noexcept(false) {
	std::string		line;
	while (std::getline(std::cin, line) && line.compare(";;")) this->_getLine(line);
	return;
}

void Lexer::_checkArgs(int ac) const noexcept(false) {
	if (ac > 2) throw AbstractVmException("Usage::" + VAL + " ./avm Or ./avm ./sample.avm");
	return;
}

void Lexer::getArg(int ac, char **av) noexcept(false) {
	try { this->_checkArgs(ac); } catch (AbstractVmException e) { e.toString(); }
   	(ac > 1) ? this->_getFile(ac, av) : this->_getInput();
	return;
}


