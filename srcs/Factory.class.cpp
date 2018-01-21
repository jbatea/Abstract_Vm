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
      //std::cout << "Create int8:: value -> " << value  << std::endl;
		return new Operand<int8_t>(INT8, value);
	}; // Create int8 operand

	IOperand const *    Factory::createInt16( std::string const & value ) const {
		return new Operand<int16_t>(INT16, value);
	}; // Create int16 operand

	IOperand const *    Factory::createInt32( std::string const & value ) const {
		return new Operand<int32_t>(INT32, value);
	}; // Create int32 operand

	IOperand const *    Factory::createFloat( std::string const & value ) const {
		return new Operand<float>(FLOAT, value);
	}; // Create float operand

	IOperand const *    Factory::createDouble( std::string const & value ) const {
		return new Operand<double>(DOUBLE, value);
	}; // Create double operand