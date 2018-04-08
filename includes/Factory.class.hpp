#ifndef FACTORY_CLASS_HPP
#define FACTORY_CLASS_HPP

class Factory {

	public:

	static Factory * getFactory();
  	static void      deleteFactory();
    IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	Factory( void ); // Default constructor
    Factory( Factory const & src ); // Copy constructor
    ~Factory( void ); // Destructor
    Factory & operator=( Factory const & rhs );// Assignement

	private:

	IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;
    long double 	 _checkRange(std::string const & value, eOperandType type) const noexcept(false);

    static Factory *_factory;
};

#endif