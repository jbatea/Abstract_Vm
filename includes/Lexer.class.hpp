#ifndef LEXER_CLASS_HPP
#define LEXER_CLASS_HPP

class Lexer {

	public:

 	Lexer( void ); // Default constructor
 	Lexer( Lexer const & src ); // Copy constructor
 	~Lexer( void ); // Destructor
 	Lexer & operator=( Lexer const & rhs );// Assignement
   	void 									getArg( int ac, char **av ) noexcept(false);
	void									setInstruction(eInstruction instruction);
	eInstruction							getInstruction();
	std::deque<const Lexeme *> & 			getLexemes( void );

	private:

	void 									_lexer( std::string const & line ) noexcept(false);
	eCategory								_getLexemeCategory(std::string const & _lexeme);
	void 									_addLexeme(std::string const & lexeme, eCategory category);
    void 									_getFile( char *av ) noexcept(false);
    void 									_getInput( void ) noexcept(false);

	std::deque<const Lexeme *>				_lines;
    eInstruction							_instruction;

};
#endif