#ifndef OPERAND_CLASS_HPP
#define OPERAND_CLASS_HPP
#include <cxxabi.h>

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

	Operand<T>(eOperandType type, T value) {
		this->_value = value;
		this->_type = type;
		this->_string = std::to_string(value);
		std::cout << "Operand():: value -> " << this->toString()  << std::endl;
		return;
	}

	~Operand<T>( void ) {
		return;
	}; // Destructor

	Operand<T> & operator=( Operand<T> const & rhs ) {
		if (this != &rhs) {
			this->_value = rhs.getValue();
			this->_type = rhs.getType();
			this->_string = rhs.toString();
		 }
		 return *this;
	 };

	IOperand const *    operator+( IOperand const & rhs ) const {
		T value;
		value = this->_value + (dynamic_cast<Operand<T> const *>(&rhs))->getValue();

   		return Factory::getFactory()->createOperand(INT8, std::to_string(value));
	}; // Sum

	IOperand const *    operator-( IOperand const & rhs ) const {
		T value;
    	value = this->_value - (dynamic_cast<Operand<T> const *>(&rhs))->getValue();

       	return Factory::getFactory()->createOperand(INT8, std::to_string(value));
	}; // Difference

	IOperand const *    operator*( IOperand const & rhs ) const {
		T value;
    	value = this->_value * (dynamic_cast<Operand<T> const *>(&rhs))->getValue();

       	return Factory::getFactory()->createOperand(INT8, std::to_string(value));
	}; // Product

	IOperand const *    operator/( IOperand const & rhs ) const {
		T value;
        value = this->_value / (dynamic_cast<Operand<T> const *>(&rhs))->getValue();

        return Factory::getFactory()->createOperand(INT8, std::to_string(value));
	}; // Quotient

	IOperand const *    operator%( IOperand const & rhs ) const {
		T value;
        value = fmod(this->_value, (dynamic_cast<Operand<T> const *>(&rhs))->getValue());

        return Factory::getFactory()->createOperand(INT8, std::to_string(value));
	}; // Modulo

	eOperandType        getType(void) const {
		return this->_type;
	}; // Type of the instance

	int                 getPrecision(void) const { return this->_type; }; // Precision of the type of the instance

	std::string const & toString( void ) const {
		return this->_string;
	}; // String representation of value

	T					getValue() const {
		return this->_value;
	}

	private:

	T 					_value;
	std::string			_string;
	eOperandType		_type;
};

#endif