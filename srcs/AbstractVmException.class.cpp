#include "../includes/Avm.hpp"

AbstractVmException::AbstractVmException( void )  {
	this->_exception = "Unknow Error";
	return;
}; // Default constructor

AbstractVmException::AbstractVmException(AbstractVmException const & src) {
	this->_exception = src._exception;
	return;
}; // Copy constructor

AbstractVmException::AbstractVmException(std::string const & exception) {
	this->_exception = exception;
//	std:: cout << this->_exception << std::endl;
	return;
}

AbstractVmException::AbstractVmException(eOperandType type, std::string const & exception) {
	this->_exception = exception + " " + VAL + this->_getTypeAsString(type) + RESET;
	return;
}

AbstractVmException::~AbstractVmException( void ) {
	return;
}; // Destructor

AbstractVmException & AbstractVmException::operator=( AbstractVmException const & rhs ) {
	if (this != &rhs)
		this->_exception = rhs._exception;
	return *this;
};

const char* AbstractVmException::what() const noexcept {
	return this->_exception.c_str();
}


void AbstractVmException::toString() const noexcept {
	std::cout << EXCEPTION << this->_exception << RESET << std::endl;
	return;
}

const std::string  AbstractVmException::_getTypeAsString(eOperandType type) const {
	const std::string typeList[] = {"INT8", "INT16", "INT32", "FLOAT", "DOUBLE"};
	return typeList[type];
}