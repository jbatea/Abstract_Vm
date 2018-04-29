#ifndef LEXER_CLASS_HPP
#define LEXER_CLASS_HPP

class Lexer {

	public:

 	Lexer( void ); // Default constructor
 	Lexer( Lexer const & src ); // Copy constructor
 	~Lexer( void ); // Destructor
 	Lexer & operator=( Lexer const & rhs );// Assignement

   	void 									getArg( int ac, char **av ) noexcept(false);
	std::deque<const Lexeme *> const & 		getLexemes( void ) const;

	private:

	void 									_lexer( std::string const & line ) noexcept(false);
	eCategory								_getLexemeCategory(std::string const & _lexeme);
    void                                    _getLines(std::vector<std::string> lines) noexcept(false);
    void                                    _getFile(char *av ) noexcept(false);
    void                                    _getInput( void );
    void                                    _checkArgs(int ac) const noexcept(false);
    void                                    _timeoutHandler(bool *timeout);

	std::deque<const Lexeme *>				_lexemes;
};
#endif