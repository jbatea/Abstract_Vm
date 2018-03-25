#ifndef LEXER_CLASS_HPP
#define LEXER_CLASS_HPP

class Lexer {

	public:

 	Lexer( void ); // Default constructor
 	Lexer( Lexer const & src ); // Copy constructor
 	~Lexer( void ); // Destructor
 	Lexer & operator=( Lexer const & rhs );// Assignement
   	void 									checkArg( int ac, char **av ) noexcept(false);
    void									printLexemes( void );
	void									setInstruction(eInstruction instruction);
	eInstruction							getInstruction();

	private:

	void 									_lexer( std::string const & line ) noexcept(false);
	std::deque<const Lexeme *> & 			_getLexemes( void );
	eCategory								_getLexemeCategory(std::string const & _lexeme);
	void 									_addLexeme(std::string const & lexeme, eCategory category);
    void 									_getFile( char *av ) noexcept(false);
    void 									_getInput( void ) noexcept(false);

	std::deque<const Lexeme *>				_lines;
    eInstruction							_instruction;

};
#endif