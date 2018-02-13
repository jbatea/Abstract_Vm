#ifndef AVM_H
#define AVM_H

# include <iostream>
# include <cstdlib>
# include <cstdint>
# include <cstring>
# include <limits>
# include <deque>
# include <map>
# include <memory>
# include <functional>
# include <math.h>

enum eOperandType
{
    INT8,
    INT16,
    INT32,
    FLOAT,
    DOUBLE
};

# include "./IOperand.class.hpp"
# include "./Factory.class.hpp"
# include "./Operand.class.hpp"
# include "./AbstractVm.class.hpp"

#endif
