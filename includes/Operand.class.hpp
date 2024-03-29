#ifndef OPERAND_CLASS_HPP
#define OPERAND_CLASS_HPP

template <typename T>
class Operand : public IOperand {

	public:

	Operand<T>( void )  {
		return;
	}; // Default constructor

	Operand<T>(Operand<T> const & src) {
		this->_string = src.toString();
		this->_type = src.getType();
		this->_value = src.getValue();
		return;
	}; // Copy constructor

	Operand<T>(eOperandType type, std::string const & value) {
    	this->_type = type;
    	this->_string = value;
    	this->_value = stold(value);
    	return;
    }

	~Operand<T>( void ) {
		return;
	}; // Destructor

	Operand<T> & operator=( Operand<T> const & rhs ) {
		if (*this != rhs) {
			this->_type = rhs.getType();
			this->_string = rhs.toString();
			this->_value = rhs.getValue();
		 }
		 return *this;
	 };

	IOperand const *    operator+( IOperand const & rhs ) const {
   		return Factory::getFactory()->createOperand(getType(rhs),
   			std::to_string(this->_value + stold(rhs.toString())));
	}; // Sum

	IOperand const *    operator-( IOperand const & rhs ) const {
	return Factory::getFactory()->createOperand(getType(rhs),
			std::to_string(this->_value - stold(rhs.toString())));
	}; // Difference

	IOperand const *    operator*( IOperand const & rhs ) const {
       	return Factory::getFactory()->createOperand(getType(rhs),
       		std::to_string(this->_value * stold(rhs.toString())));
	}; // Product

	IOperand const *    operator/( IOperand const & rhs ) const {
        return Factory::getFactory()->createOperand(getType(rhs),
			std::to_string(this->_value / stold(rhs.toString())));
	}; // Quotient

	IOperand const *    operator%( IOperand const & rhs ) const {
        return Factory::getFactory()->createOperand(getType(rhs),
        	std::to_string(fmod(this->_value, stold(rhs.toString()))));
	}; // Modulo

	int                 getPrecision(void) const {
		return this->_type;
	}; // Precision of the type of the instance

	eOperandType        getType(void) const {
		return this->_type;
	}; // Type of the instance

	eOperandType		getType(IOperand const & rhs) const {
    		return (rhs.getPrecision() < getPrecision()) ?
    			getType() : rhs.getType();
    }

	std::string const & toString( void ) const {
		return this->_string;
	}; // String representation of value

	T       const & getValue(void) const {
		return this->_value;
	}

	T 					_value;
	std::string			_string;
	eOperandType		_type;
};

#endif