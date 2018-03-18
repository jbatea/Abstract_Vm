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
# include <sstream>
# include <fstream>
# include <string>
# include <float.h>

enum eOperandType
{
    INT8,
    INT16,
    INT32,
    FLOAT,
    DOUBLE
};

enum eInstruction
{
	PUSH,
	POP,
	DUMP,
	ASSERT,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    PRINT,
    EXIT
};

enum eCategory {
	INSTR,
	VALUE,
	SEP,
	COM
};

# include "./AbstractVmException.class.hpp"
# include "./IOperand.class.hpp"
# include "./Factory.class.hpp"
# include "./Operand.class.hpp"
# include "./Lexeme.class.hpp"
# include "./AbstractVm.class.hpp"

#endif
