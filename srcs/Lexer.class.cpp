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

	if (!std::regex_match(line, instr) && !std::regex_match(line, instr)) throw AbstractVmException("Syntactic && Lexical error:: ", line);
	if (!std::regex_match(line, instr)) throw AbstractVmException("Syntactic error::  ", line);
	if (!std::regex_match(line, lex)) throw AbstractVmException("Lexical error:: ", line);
	std::regex_replace(std::back_inserter(res), line.begin(), line.end(), std::regex(".*;.*$"), "$`");
	stream.str(res);
	while (std::getline(stream, _lexeme, ' '))
		this->_lexemes.push_back(new Lexeme(_lexeme, this->_getLexemeCategory(_lexeme)));
	return;
}

void Lexer::_timeoutHandler(bool *timeout) {
	std::this_thread::sleep_for(std::chrono::seconds(2));
    *timeout = true;
    return;
}

void Lexer::_getLines(std::vector<std::string> lines) noexcept(false) {
   	bool exit = false;
	std::vector<std::string>::iterator it = lines.begin();

    while (it != lines.end()) {
         if (!(*it).compare("exit")) exit = true;
         try { this->_lexer(*it++); } catch (AbstractVmException e) { e.toString(); }
    }
    if (!exit) throw AbstractVmException("Error::", " Program doesn't have exit instruction");
	return;
}

void Lexer::_getFile(char *av) noexcept(false) {
	std::string		line;
	std::ifstream	file;
	bool timeout = false;
	std::vector<std::string> lines;

	try {
			file.open(av, std::ifstream::in);
			if (!file.is_open()) throw AbstractVmException("Failed to open file:: ", av);
			std::thread(&Lexer::_timeoutHandler, this, &timeout).detach();
			while (std::getline(file, line) && timeout == false) lines.push_back(line);
			if (timeout) throw AbstractVmException("Timeout on reading file:: ", av);
			this->_getLines(lines);
			file.close();
		} catch (AbstractVmException e) { e.toString(); }
	return;
}

void Lexer::_getInput(void) {
	std::string		line;
	std::vector<std::string> lines;
	while (std::getline(std::cin, line) && line.compare(";;")) lines.push_back(line);
	this->_getLines(lines);
	return;
}

void Lexer::_checkArgs(int ac) const noexcept(false) {
	if (ac > 2) throw AbstractVmException("Usage::", " ./avm Or ./avm ./sample.avm");
	return;
}

void Lexer::getArg(int ac, char **av) noexcept(false) {
	try { this->_checkArgs(ac); } catch (AbstractVmException e) { e.toString(); }
   	try { (ac > 1) ? this->_getFile(av[1]) : this->_getInput(); } catch (AbstractVmException e) { e.toString(); }
	return;
}


