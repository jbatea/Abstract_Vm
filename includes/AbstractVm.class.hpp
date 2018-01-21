#ifndef ABSTRACTVM_CLASS_HPP
#define ABSTRACTVM_CLASS_HPP

class AbstractVm {

public:

    AbstractVm( void ); // Default constructor
    AbstractVm( AbstractVm const & src ); // Copy constructor
    ~AbstractVm( void ); // Destructor
    AbstractVm & operator=( AbstractVm const & rhs );// Assignement

    std::deque<const IOperand *> &          getStackRef( void ); // Stack getter
    void                                    pop( void );
    void                                    dump( void );
    void                                    print( void );
    void                                    assert( std::string const & value );
    void                                    exit( std::string const & error );
    void                                    add( void );
    void                                    sub( void );
    void                                    mul( void );
    void                                    div( void );
    void                                    mod( void );
    void              						create( eOperandType type, std::string const & value );


	private:

	void									push( const IOperand *operand );
    std::deque<const IOperand *>            _stack;
};
#endif
