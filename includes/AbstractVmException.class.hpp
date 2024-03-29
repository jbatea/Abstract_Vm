#ifndef ABSTRACTVMEXCEPTION_CLASS_HPP
#define ABSTRACTVMEXCEPTION_CLASS_HPP

class AbstractVmException : public std::exception {

	public:

	AbstractVmException( void ); // Default constructor
	AbstractVmException(std::string const & exception, std::string const & value);
	~AbstractVmException( void );// Destructor
	AbstractVmException & operator=( AbstractVmException const & rhs );// Assignement
	AbstractVmException(AbstractVmException const & src); // Copy constructor

	AbstractVmException(eOperandType type, std::string const & exception, std::string const & value);
	const char * what() const noexcept;
	void toString() const noexcept;

	private:

	const std::string						_getTypeAsString(eOperandType type) const;

	std::string _error;
	std::string _value;
};

#endif