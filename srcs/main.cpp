
#include "../includes/Avm.hpp"

int     main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    Operand<int8_t> _int8;
    Operand<int16_t> _int16;
    Operand<int32_t> _int32;
    Operand<float> _float;
    Operand<double> _double;

    _int8.setValue(std::numeric_limits<int8_t>::max());
    std::cout << "value = " << _int8.getValue() << std::endl;
    std::cout << "string = " << _int8.toString() << std::endl;

    _int16.setValue(std::numeric_limits<int16_t>::max());
    std::cout << "value = " << _int16.getValue() << std::endl;
    std::cout << "string = " << _int16.toString() << std::endl;

    _int32.setValue(std::numeric_limits<int32_t>::max());
    std::cout << "value = " << _int32.getValue() << std::endl;
    std::cout << "string = " << _int32.toString() << std::endl;

    _float.setValue(std::numeric_limits<float>::max());
    std::cout << "value = " << _float.getValue() << std::endl;
    std::cout << "string = " << _float.toString() << std::endl;

    _double.setValue(std::numeric_limits<double>::max());
    std::cout << "value = " << _double.getValue() << std::endl;
    std::cout << "string = " << _double.toString() << std::endl;
    return 0;
}
