#ifndef ABSTRACTVM_CLASS_HPP
#define ABSTRACTVM_CLASS_HPP

class AbstractVm {

public:

    AbstractVm( void ); // Default constructor
    AbstractVm( AbstractVm const & src ); // Copy constructor
    ~AbstractVm( void ); // Destructor
    AbstractVm & operator=( AbstractVm const & rhs );// Assignement

    void                                    pop( unsigned long erase ) noexcept(false);
    void									doOp(eOperator op) noexcept(false);
    void                                    dump( void );
    void                                    print( void ) noexcept(false);
    void                                    assert( eOperandType type, std::string const & value ) noexcept(false);
    void                                    exit( std::string const & error );
    void              						create( eOperandType type, std::string const & value );


	private:

    std::deque<const IOperand *> &          _getStackRef( void ); // Stack getter
	const std::string						_getTypeAsString(eOperandType type) const;
	const std::string						_getOpAsString(eOperator op) const;
	void									_push( const IOperand *operand );
    std::deque<const IOperand *>            _stack;
};
#endif
