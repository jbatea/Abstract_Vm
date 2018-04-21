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

	if (!std::regex_match(line, instr)) throw AbstractVmException("Syntax error::\n" + VAL + line);
	if (!std::regex_match(line, lex)) throw AbstractVmException("Lexical error::\n" + VAL + line);
	std::regex_replace(std::back_inserter(res), line.begin(), line.end(), std::regex(".*;.*$"), "$`");
	stream.str(res);
	while (std::getline(stream, _lexeme, ' '))
		this->_lexemes.push_back(new Lexeme(_lexeme, this->_getLexemeCategory(_lexeme)));
	return;
}

void Lexer::_getFile(char **av) noexcept(false) {
	std::string		line;
	std::ifstream	file;

	av++;
	while (av) {
		try {
			file.open(*av, std::ifstream::in);
			if (!file.is_open()) throw AbstractVmException("Lexer::Failed to open file");
			else {
				while (std::getline(file, line)) {
					try { this->_lexer(line); } catch (AbstractVmException e) {
						std::cout << EXCEPTION << "Lexer::" << e.what() << RESET << std::endl; }
				}
				file.close();
				return;
			}
		} catch (AbstractVmException e) { std::cout << EXCEPTION << e.what() << RESET << std::endl; }
		av++;
	}
	return;
}



void Lexer::_getInput(void) noexcept(false) {
	std::string		line;
	while (std::getline(std::cin, line) && line.compare(";;")) {
		try { this->_lexer(line); } catch (AbstractVmException e) { std::cout << EXCEPTION << "Lexer::\n" << e.what() << RESET << std::endl; }
	}
	return;
}

void Lexer::_checkExitInstr(void) noexcept(false) {
   	std::deque<const Lexeme *>::iterator it;
    it = this->_lexemes.begin();
    while (it != this->_lexemes.end()) {
        if (!(*it)->getValue().compare("exit")) return;
        *it++;
    }
    throw AbstractVmException("Lexer::\nProgram doesn't have exit instruction");
    return;
}

void Lexer::_checkArgs(int ac) const noexcept(false) {
	if (ac > 2) throw AbstractVmException("Lexer::Too much arguments" + VAL + "\nUsage:: ./avm Or ./avm ./sample.avm");
	return;
}

void Lexer::getArg(int ac, char **av) noexcept(false) {
	try { this->_checkArgs(ac); } catch (AbstractVmException e) { std::cout << EXCEPTION << e.what() << RESET << std::endl; }
   	(ac > 1) ? this->_getFile(av) : this->_getInput();
   	try { this->_checkExitInstr(); } catch (AbstractVmException e) { std::cout << EXCEPTION << e.what() << RESET << std::endl; }
	return;
}


