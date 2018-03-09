#include "../includes/Avm.hpp"

AbstractVmException::AbstractVmException( void )  {
	this->_exception = "AbstractVmException::Unknow Error";
	return;
}; // Default constructor

AbstractVmException::AbstractVmException(AbstractVmException const & src) {
	*this = src;
	return;
}; // Copy constructor

AbstractVmException::AbstractVmException(std::string const & exception) {
	this->_exception = "AbstractVmException::" + exception;
	return;
}

AbstractVmException::~AbstractVmException( void ) {
	return;
}; // Destructor

AbstractVmException & AbstractVmException::operator=( AbstractVmException const & rhs ) {
	if (this != &rhs) {
		this->_exception = rhs.what();
	}
	return *this;
};

const char* AbstractVmException::what() const noexcept {
	return this->_exception.c_str();
}


