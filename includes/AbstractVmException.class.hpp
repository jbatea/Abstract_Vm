#ifndef ABSTRACTVMEXCEPTION_CLASS_HPP
#define ABSTRACTVMEXCEPTION_CLASS_HPP

class AbstractVmException : public std::exception {

	public:

	AbstractVmException( void );
	AbstractVmException(std::string const & exception);
	AbstractVmException(eOperandType type, std::string const & exception);
	AbstractVmException(AbstractVmException const & src);
	~AbstractVmException( void );
	AbstractVmException & operator=( AbstractVmException const & rhs );
	const char * what() const noexcept;

	 private:

	const std::string						_getTypeAsString(eOperandType type) const;
	std::string _exception;
};

#endif