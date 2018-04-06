#ifndef LEXEME_CLASS_HPP
#define LEXEME_CLASS_HPP

class Lexeme {

	public:
    
        Lexeme( void ); // Default constructor
        Lexeme( std::string const & value, eCategory category); // Default constructor
        Lexeme( Lexeme const & src ); // Copy constructor
        ~Lexeme( void ); // Destructor
        Lexeme & operator=( Lexeme const & rhs );// Assignement
        std::string const getCategory() const;
        void		setCategory(eCategory category);
        std::string const & getValue() const;
        void		setValue(std::string const & value);
        eInstruction    getInstruction() const;

    private:
		void            _setInstruction( void );
		eCategory 		_category;
		std::string		_value;
		eInstruction    _instruction;
};

#endif