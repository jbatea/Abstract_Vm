#ifndef INT8_CLASS_HPP
#define INT8_CLASS_HPP

#include "Avm.hpp"

template <typename T>
class Operand : public IOperand {

public:

    Operand<T>( void )  { return; }; // Default constructor
    Operand<T>(T const & src) { *this = src; return; }; // Copy constructor
    ~Operand<T>( void ) { return; }; // Destructor
    Operand<T> &        operator=( Operand<T> const & rhs ) { if (this != &rhs) // Assignement
        { this->setValue(rhs.getValue()); this->setString(rhs.getString()); return *this;} };
    IOperand const *    operator+( IOperand const & rhs ) const { return &rhs; }; // Sum
    IOperand const *    operator-( IOperand const & rhs ) const { return &rhs; }; // Difference
    IOperand const *    operator*( IOperand const & rhs ) const { return &rhs; }; // Product
    IOperand const *    operator/( IOperand const & rhs ) const { return &rhs; }; // Quotient
    IOperand const *    operator%( IOperand const & rhs ) const { return &rhs; }; // Modulo

    std::string const & toString( void ) const { return this->_string; }; // String representation of value
    void                setString( std::string string ) { this->_string = string; return; }; //String representation Setter
    T                   getValue( void ) const { return this->_value; }; // Value getter
    void                setValue( T value ) { this->_value = value; this->setString(std::to_string(value)); return; }; // Value setter
    int                 getPrecision(void) const { return 1;}; // Precision of the type of the instance
    eOperandType        getType(void) const { return INT8; }; // Type of the instance
    IOperand const *    createOperand( eOperandType type, std::string const & value ) const {
        (void)type;
        return createInt8(value);
    }; // Create new operand

private:

    T                   _value; // Value of the corresponding type
    std::string         _string; // String representation of value
    IOperand const *    createInt8( std::string const & value ) const { Operand<int8_t> * _int8 = new Operand<int8_t>; _int8->_string = value; return _int8; }; // Create int8 operand
    IOperand const *    createInt16( std::string const & value ) const {  Operand<int16_t> * _int16 = new Operand<int16_t>; _int16->_string = value; return _int16; }; // Create int16 operand
    IOperand const *    createInt32( std::string const & value ) const {  Operand<int32_t> * _int32 = new Operand<int32_t>; _int32->_string = value; return _int32; }; // Create int32 operand
    IOperand const *    createFloat( std::string const & value ) const {  Operand<float> * _float = new Operand<float>; _float->_string = value; return _float; }; // Create float operand
    IOperand const *    createDouble( std::string const & value ) const {  Operand<double> * _double = new Operand<double>; _double->_string = value; return _double; }; // Create double operand

};

#endif
