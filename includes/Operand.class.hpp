#ifndef INT8_CLASS_HPP
#define INT8_CLASS_HPP

#include "Avm.hpp"

template <typename T>
class Operand : public IOperand {

public:
    Operand<T>( void ) { return; };
    Operand<T>(T const & src) { *this = src; return; };
    ~Operand<T>( void ) { return; };
    int getPrecision(void) const { return 1;}; // Precision of the type of the instance
    eOperandType getType(void) const { return INT8; }; // Type of the instance
    IOperand const * operator+( IOperand const & rhs ) const { return &rhs; }; // Sum
    IOperand const * operator-( IOperand const & rhs ) const { return &rhs; }; // Difference
    IOperand const * operator*( IOperand const & rhs ) const { return &rhs; }; // Product
    IOperand const * operator/( IOperand const & rhs ) const { return &rhs; }; // Quotient
    IOperand const * operator%( IOperand const & rhs ) const { return &rhs; }; // Modulo
    std::string const & toString( void ) const { return this->_string; };
    T getValue( void ) const { return this->_value; }; //Getter
    T getString( void ) const { return this->_string; }; //Getter
    void setValue( T value ) {this->_value = value; this->setString(std::to_string(value)); return;}; //Setter
    void setString( std::string string ) {this->_string = string; return;}; //Setter
    Operand<T> & operator=( Operand<T> const & rhs ) { if (this != &rhs)
        { this->setValue(rhs.getValue()); this->setString(rhs.getString()); return *this;} }; // Equal

private:
    T           _value;
    std::string _string;

};

#endif
