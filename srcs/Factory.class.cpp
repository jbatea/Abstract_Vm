	#include "../includes/Avm.hpp"

    // Default constructor
    Factory::Factory( void ) {
        return;
    }

     // Copy constructor
     Factory::Factory(Factory const & src) {
         *this = src;
         return;
     }

     // Destructor
    Factory::~Factory( void ) {
        return;
    }

    // Assignement
    Factory & Factory::operator=( Factory const & rhs) {

        if (this != &rhs)
            *this = rhs;
        return *this;
    }

   	Factory * Factory::getFactory()
    {
        if (!_factory) _factory =  new Factory();
        return _factory;
    }

    void Factory::deleteFactory()
    {
       if (_factory)
       {
       		delete _factory;
           	_factory = NULL;
       }
    }

	IOperand const *    Factory::createOperand( eOperandType type, std::string const & value ) const {

		typedef IOperand const *(Factory::*createPtr)(std::string const &) const;
		createPtr a[] = {
			&Factory::createInt8 ,
			&Factory::createInt16 ,
			&Factory::createInt32,
			&Factory::createFloat,
			&Factory::createDouble
		 };
		 return (this->*a[type]) (value);
	}; // Create new operand

	IOperand const *    Factory::createInt8( std::string const & value ) const {
		if (stof(value) < INT8_MIN)	throw AbstractVmException("INT8::UNDERFLOW Value -> " + value);
		if (stof(value) > INT8_MAX) throw AbstractVmException("INT8::OVERFLOW Value -> " + value);
		return new Operand<int8_t>(INT8, stoi(value));
	}; // Create int8 operand

	IOperand const *    Factory::createInt16( std::string const & value ) const {
//      std::cout << "Create int16:: value -> " << value  << std::endl;
		if (stof(value) < INT16_MIN)	throw AbstractVmException("INT16::UNDERFLOW Value -> " + value);
		if (stof(value) > INT16_MAX) throw AbstractVmException("INT16::OVERFLOW Value -> " + value);
		return new Operand<int16_t>(INT16, stoi(value));
	}; // Create int16 operand

	IOperand const *    Factory::createInt32( std::string const & value ) const {
//      std::cout << "Create int32:: value -> " << value  << std::endl;
		if (stof(value) < INT32_MIN) throw AbstractVmException("INT32::UNDERFLOW Value -> " + value);
		if (stof(value) > INT32_MAX) throw AbstractVmException("INT32::OVERFLOW Value -> " + value);
		return new Operand<int32_t>(INT32, stoi(value));
	}; // Create int32 operand

	IOperand const *    Factory::createFloat( std::string const & value ) const {
//      std::cout << "Create float:: value -> " << value  << std::endl;
		if (stod(value) < FLT_MIN)	throw AbstractVmException("FLOAT::UNDERFLOW Value -> " + value);
		if (stod(value) > FLT_MAX) throw AbstractVmException("FLOAT::OVERFLOW Value -> " + value);
		return new Operand<float>(FLOAT, stof(value));
	}; // Create float operand

	IOperand const *    Factory::createDouble( std::string const & value ) const {
//      std::cout << "Create double:: value -> " << value  << std::endl;
		if (stold(value) < DBL_MIN)	throw AbstractVmException("DOUBLE::UNDERFLOW Value -> " + value);
		if (stold(value) > DBL_MAX) throw AbstractVmException("DOUBLE::OVERFLOW Value -> " + value);
		return new Operand<double>(DOUBLE, stod(value));
	}; // Create double operand