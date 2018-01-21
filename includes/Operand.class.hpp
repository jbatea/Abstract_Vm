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

	Operand<T>(eOperandType type, std::string value) {
		this->_value = value;
		this->_type = type;
		std::cout << "Operand():: value -> " << this->toString()  << std::endl;
		return;
	}

	~Operand<T>( void ) {
		return;
	}; // Destructor

	Operand<T> & operator=( Operand<T> const & rhs ) {
		if (this != &rhs) {
			this->_value = rhs.getValue();
			this->type = rhs.getType();
		 }
		 return *this;
	 };

	IOperand const *    operator+( IOperand const & rhs ) const {
		std::string value;
		value = std::to_string(stoi(this->toString()) + stoi(rhs.toString()));
   		return Factory::getFactory()->createOperand(INT8, value);
	}; // Sum

	IOperand const *    operator-( IOperand const & rhs ) const {
		std::string value;
		value = std::to_string(stoi(this->toString()) - stoi(rhs.toString()));
   		return Factory::getFactory()->createOperand(INT8, value);
	}; // Difference

	IOperand const *    operator*( IOperand const & rhs ) const {
		std::string value;
		value = std::to_string(stoi(this->toString()) * stoi(rhs.toString()));
   		return Factory::getFactory()->createOperand(INT8, value);
	}; // Product

	IOperand const *    operator/( IOperand const & rhs ) const {
		std::string value;
		value = std::to_string(stoi(this->toString()) / stoi(rhs.toString()));
   		return Factory::getFactory()->createOperand(INT8, value);
	}; // Quotient

	IOperand const *    operator%( IOperand const & rhs ) const {
		std::string value;
		value = std::to_string(stoi(this->toString()) % stoi(rhs.toString()));
   		return Factory::getFactory()->createOperand(INT8, value);
	}; // Modulo

	eOperandType        getType(void) const {
		return this->_type;
	}; // Type of the instance
	int                 getPrecision(void) const { return this->_type;}; // Precision of the type of the instance

	std::string const & toString( void ) const {
		return this->_value;
	}; // String representation of value

	private:

	std::string 		_value;
	eOperandType		_type;
};

#endif