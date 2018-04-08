#ifndef LEXEME_CLASS_HPP
#define LEXEME_CLASS_HPP

class Lexeme {

	public:
    
        Lexeme( void ); // Default constructor
        Lexeme( std::string const & value, eCategory category); // Constructor
        Lexeme( Lexeme const & src ); // Copy constructor
        ~Lexeme( void ); // Destructor
        Lexeme & operator=( Lexeme const & rhs );// Assignement

        eCategory           getCategory() const;
        std::string const & getValue() const;
        eInstruction        getInstruction() const;

    private:

		eCategory 		_category;
		std::string		_value;
};

#endif