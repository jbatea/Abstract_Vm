#include "../includes/Avm.hpp"

AbstractVmException::AbstractVmException( void )  {
	this->_error = "Unknow Error";
	this->_value = "Unkow Value";
	return;
}; // Default constructor

AbstractVmException::AbstractVmException(AbstractVmException const & src) {
	this->_error = src._error;
	this->_value = src._value;
	return;
}; // Copy constructor

AbstractVmException::AbstractVmException(std::string const & exception, std::string const & value) {
	this->_error = exception;
	this->_value = value;
//	std:: cout << this->_exception << std::endl;
	return;
}

AbstractVmException::AbstractVmException(eOperandType type, std::string const & exception, std::string const & value) {
	this->_error = exception + " " + VAL + this->_getTypeAsString(type) + RESET;
	this->_value = value;
	return;
}

AbstractVmException::~AbstractVmException( void ) {
	return;
}; // Destructor

AbstractVmException & AbstractVmException::operator=( AbstractVmException const & rhs ) {
	if (this != &rhs) {
		this->_error = rhs._error;
		this->_value = rhs._value;
	}

	return *this;
};

const char* AbstractVmException::what() const noexcept {
	return (this->_error + this->_value).c_str();
}


void AbstractVmException::toString() const noexcept {
	std::string cpy = this->_value;
	cpy.erase(remove_if(cpy.begin(),cpy.end(), [](char x) {return !isprint(x);}), cpy.end());
	std::cout << EXCEPTION << this->_error << VAL << cpy << RESET << std::endl;
	return;
}

const std::string  AbstractVmException::_getTypeAsString(eOperandType type) const {
	const std::string typeList[] = {"INT8", "INT16", "INT32", "FLOAT", "DOUBLE"};
	return typeList[type];
}