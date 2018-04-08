#include "../includes/Avm.hpp"

// Default constructor
Lexer::Lexer( void ) {
    return;
}

 // Copy constructor
 Lexer::Lexer(Lexer const & src) {
     *this = src;
     return;
 }

 // Destructor
Lexer::~Lexer( void ) {
    return;
}

// Assignement
Lexer & Lexer::operator=( Lexer const & rhs) {

    if (this != &rhs)
        *this = rhs;
    return *this;
}

std::deque<const Lexeme *> & Lexer::getLexemes(void) {
	return this->_lines;
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
	std::regex e ("^((pop|dump|add|sub|mul|div|mod|print|exit)|((assert|push) (((int(8|16|32)\\(-?\\d+\\)))|((float|double)\\(-?\\d+[.]\\d+\\)))))?(\\s*;.*)?$");

	if (!std::regex_match(line, e)) throw AbstractVmException("Lexer:: Invalid line format -> " + line);
	std::regex_replace(std::back_inserter(res), line.begin(), line.end(), std::regex(".*;.*$"), "$`");
	stream.str(res);
	while (std::getline(stream, _lexeme, ' '))
		this->getLexemes().push_back(new Lexeme(_lexeme, this->_getLexemeCategory(_lexeme)));
	return;
}

void Lexer::_getFile(char *av) noexcept(false) {
	std::string		line;
	std::ifstream	file;

	file.open(av, std::ifstream::in);
	if (!file.is_open()) throw AbstractVmException("Failed to open file");
	while (std::getline(file, line)) this->_lexer(line);
	file.close();
	return;
}

void Lexer::_getInput(void) noexcept(false) {
	std::string		line;
	while (std::getline(std::cin, line) && line.compare(";;")) this->_lexer(line);
	return;
}

void Lexer::getArg(int ac, char **av) noexcept(false) {
   	std::deque<const Lexeme *>::iterator it;

	if (ac > 2) throw AbstractVmException("Lexer:: Too much arguments, Usage: ./avm Or ./avm ./sample.avm");
   	(ac == 2) ? this->_getFile(av[1]) : this->_getInput();
    it = this->getLexemes().begin();
    while (it != this->getLexemes().end()) {
        if (!(*it)->getValue().compare("exit")) return;
        *it++;
    }
    throw AbstractVmException("Lexer:: Program doesn't have exit instruction");
}
