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
    eOperandType        getType(void) const { return this->_type; }; // Type of the instance
    void                setType( eOperandType type ) { this->_type = type; return; }
    int                 getPrecision(void) const { return this->_type;}; // Precision of the type of the instance
    IOperand const *    createOperand( eOperandType type, std::string const & value ) const { typedef IOperand const *(Operand::*createPtr)(std::string const &) const; createPtr a[] = { &Operand<T>::createInt8 , &Operand<T>::createInt16 , &Operand<T>::createInt32, &Operand<T>::createFloat, &Operand<T>::createDouble }; return (this->*a[type]) (value); }; // Create new operand

    private:

    T                   _value; // Value of the corresponding type
    std::string         _string; // String representation of value
    eOperandType        _type; // Precision of value
    IOperand const *    createInt8( std::string const & value ) const { Operand<T> * _int8 = new Operand<T>; _int8->setValue(static_cast<int8_t>(atoi(value.c_str()))); _int8->setType(INT8); return _int8; }; // Create int8 operand
    IOperand const *    createInt16( std::string const & value ) const { Operand<T> * _int16 = new Operand<T>; _int16->setValue(static_cast<int16_t>(atoi(value.c_str()))); _int16->setType(INT16); return _int16; }; // Create int16 operand
    IOperand const *    createInt32( std::string const & value ) const { Operand<T> * _int32 = new Operand<T>; _int32->setValue(static_cast<int32_t>(atoi(value.c_str()))); _int32->setType(INT32); return _int32; }; // Create int32 operand
    IOperand const *    createFloat( std::string const & value ) const {  Operand<T> * _float = new Operand<T>; _float->setValue(static_cast<float>(atof(value.c_str()))); _float->setType(FLOAT); return _float; }; // Create float operand
    IOperand const *    createDouble( std::string const & value ) const {  Operand<T> * _double = new Operand<T>; _double->setValue(static_cast<double>(atof(value.c_str()))); _double->setType(DOUBLE); return _double; }; // Create double operand

};

#endif
