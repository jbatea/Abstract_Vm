#ifndef ABSTRACTVM_CLASS_HPP
#define ABSTRACTVM_CLASS_HPP

class AbstractVm {

public:

    AbstractVm( void ); // Default constructor
    AbstractVm( AbstractVm const & src ); // Copy constructor
    ~AbstractVm( void ); // Destructor
    AbstractVm & operator=( AbstractVm const & rhs );// Assignement

    std::deque<const IOperand *> &          getStackRef( void ); // Stack getter
    void                                    pop( void ) noexcept(false);
    void                                    dump( void );
    void                                    print( void ) noexcept(false);
    void                                    assert( eOperandType type, std::string const & value ) noexcept(false);
    void                                    exit( std::string const & error );
    void                                    add( void ) noexcept(false);
    void                                    sub( void ) noexcept(false);
    void                                    mul( void ) noexcept(false);
    void                                    div( void ) noexcept(false);
    void                                    mod( void ) noexcept(false);
    void              						create( eOperandType type, std::string const & value );


	private:

	const std::string						_getTypeAsString(eOperandType type) const;
	void									_push( const IOperand *operand );
    std::deque<const IOperand *>            _stack;
};
#endif
