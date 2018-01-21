#ifndef FACTORY_CLASS_HPP
#define FACTORY_CLASS_HPP

class Factory {

	public:

	static Factory *getFactory()
  	{
    	if (!_factory) _factory =  new Factory();
    	return _factory;
  	}

  	static void deleteFactory()
  	{
    if (_factory)
    {
       delete _factory;
       _factory = NULL;
    }
  }
    IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	private:

   	Factory( void ); // Default constructor
    Factory( Factory const & src ); // Copy constructor
    ~Factory( void ); // Destructor
    Factory & operator=( Factory const & rhs );// Assignement
	IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;

    static Factory *_factory;
};

#endif