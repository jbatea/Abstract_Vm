#ifndef OPERAND_CLASS_HPP
#define OPERAND_CLASS_HPP

template <typename T>
class Operand : public IOperand {

	public:

	Operand<T>( void )  {
		return;
	}; // Default constructor

	Operand<T>(T const & src) {
		*this = src;
		return;
	}; // Copy constructor

	Operand<T>(eOperandType type, std::string const & string) {
		this->_type = type;
		this->_string = string;
		this->_value = stof(string);
//		std::cout << "Create Operand:: value -> " <<  (int16_t)value
//			<< " string -> " << this->_string << " type -> " << this->_type << std::endl;

		return;
	}

	~Operand<T>( void ) {
		return;
	}; // Destructor

	Operand<T> & operator=( Operand<T> const & rhs ) {
		if (this != &rhs) {
			this->_type = rhs.getType();
			this->_string = rhs.toString();
			this->_value = stof(rhs.toString());
		 }
		 return *this;
	 };

	IOperand const *    operator+( IOperand const & rhs ) const {
   		return Factory::getFactory()->createOperand(getType(rhs),
   			toString(this->_value + stof(rhs.toString())));
	}; // Sum

	IOperand const *    operator-( IOperand const & rhs ) const {
	return Factory::getFactory()->createOperand(getType(rhs),
			toString(this->_value - stof(rhs.toString())));
	}; // Difference

	IOperand const *    operator*( IOperand const & rhs ) const {
       	return Factory::getFactory()->createOperand(getType(rhs),
       		toString(this->_value * stof(rhs.toString())));
	}; // Product

	IOperand const *    operator/( IOperand const & rhs ) const {
        return Factory::getFactory()->createOperand(getType(rhs),
			toString(this->_value / stof(rhs.toString())));
	}; // Quotient

	IOperand const *    operator%( IOperand const & rhs ) const {
        return Factory::getFactory()->createOperand(getType(rhs),
        	toString(fmod(this->_value, stof(rhs.toString()))));
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

	std::string const toString(double value) const {
        std::ostringstream str;
        str << value;
        std::string string = str.str();
        return string;
    }


	private:

	T 					_value;
	std::string			_string;
	eOperandType		_type;
};

#endif