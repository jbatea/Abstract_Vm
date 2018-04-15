#ifndef ABSTRACTVM_CLASS_HPP
#define ABSTRACTVM_CLASS_HPP

class AbstractVm {

	public:

    AbstractVm( void ); // Default constructor
    AbstractVm( AbstractVm const & src ); // Copy constructor
    AbstractVm( int ac, char **av ); // Constructor
    ~AbstractVm( void ); // Destructor
    AbstractVm & operator=( AbstractVm const & rhs );// Assignement

	Lexer const &				            getLexer() const;
	Parser const &                          getParser() const;
    void                                    start(int ac, char **av);

	private:

    Lexer                           _lexer;
    Parser                          _parser;
};
#endif
