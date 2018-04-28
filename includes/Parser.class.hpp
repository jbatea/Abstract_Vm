#ifndef PARSER_CLASS_HPP
#define PARSER_CLASS_HPP

class Parser {

		public:
	   
	    Parser( void ); // Default constructor
        Parser( Parser const & src ); // Copy constructor
        ~Parser( void ); // Destructor
        Parser & operator=( Parser const & rhs );// Assignement

        void						            parseLexemes( Lexer const & lexer ) noexcept(false);
        std::deque<const IOperand *> const &    getStack( void ) const;
        void                                    pop( void ) noexcept(false);
        void                                    dump( void );
        void                                    print( void ) noexcept(false);
        void                                    assert(eOperandType type, std::string const & value ) noexcept(false);
        void              			            create(eOperandType type, std::string const & value );

        private:

        std::string                             _getInstr(eInstruction instr) const;
		std::string					            _parseValue(std::string const & value);
		eOperandType				            _parseType(std::string const & value);
		void						            _doOp(eInstruction op) noexcept(false);
        void                                    _doInstr(eInstruction instr, std::string value);
        std::deque<const IOperand *> &          _getStackRef( void ); // Stack getter
        void						            _push( const IOperand *operand );

		std::deque<const IOperand *>            _stack;
};
#endif