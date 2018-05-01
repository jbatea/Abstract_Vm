	#include "../includes/Avm.hpp"


    // Default constructor
    Factory::Factory( void ) {
        return;
    }

     // Copy constructor
     Factory::Factory(Factory const & src) {
         this->_factory = src.getFactory();
         return;
     }

     // Destructor
    Factory::~Factory( void ) {
        return;
    }

    // Assignement
    Factory & Factory::operator=( Factory const & rhs) {
        if (this != &rhs)
            this->_factory = rhs.getFactory();
        return *this;
    }

   	Factory * Factory::getFactory() {
        if (!_factory) _factory =  new Factory();
        return _factory;
    }

    void Factory::deleteFactory() {
       if (_factory) {
       		delete _factory;
           	_factory = NULL;
       }
    }

	IOperand const *    Factory::createOperand( eOperandType type, std::string const & value ) const {
		 std::vector<IOperand const *(Factory::*)(std::string const &) const> factory {
		    &Factory::createInt8, &Factory::createInt16, &Factory::createInt32,
		    &Factory::createFloat, &Factory::createDouble
		 };
		 return (this->*factory[type]) (value);
	}; // Create new operand

	IOperand const *    Factory::createInt8( std::string const & value ) const {
		return new Operand<int8_t>(INT8, this->_checkRange(value, INT8));
	}; // Create int8 operand

	IOperand const *    Factory::createInt16( std::string const & value ) const {
	   return new Operand<int16_t>(INT16, this->_checkRange(value, INT16));
	}; // Create int16 operand

	IOperand const *    Factory::createInt32( std::string const & value) const {
		return new Operand<int32_t>(INT32, this->_checkRange(value, INT32));
	}; // Create int32 operand

	IOperand const *    Factory::createFloat( std::string const & value ) const {
		return new Operand<float>(FLOAT, this->_checkRange(value, FLOAT));
	}; // Create float operand

	IOperand const *    Factory::createDouble( std::string const & value ) const {
		return new Operand<double>(DOUBLE, this->_checkRange(value, DOUBLE));
	}; // Create double operand

	long double Factory::_checkRange(std::string const & value, eOperandType type) const noexcept(false) {
		long double _value;
		long double min;
		long double max;

        try { _value = stold(value);
        } catch (std::out_of_range e) {
        	throw AbstractVmException(type,"Out of range:: ", value);
        }
        switch (type) {
        	case INT8: min = INT8_MIN; max = INT8_MAX; break;
        	case INT16: min = INT16_MIN; max = INT16_MAX; break;
        	case INT32: min = INT32_MIN; max = INT32_MAX; break;
        	case FLOAT: min = std::numeric_limits<float>::lowest(); max = FLT_MAX; break;
        	case DOUBLE: min = std::numeric_limits<double>::lowest(); max = DBL_MAX; break;
        	default: break;
        }
		if (_value < min) throw AbstractVmException(type,"Underflow:: ", value);
		if (_value > max) throw AbstractVmException(type,"Overflow:: ", value);
        return _value;
	}
