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
# include <vector>
# include <regex>
#include <thread>
#include <atomic>
# include <iomanip>

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

#define EXCEPTION (std::string)"\033[1;31m"
#define SUCCESS     (std::string)"\033[1;32m"
#define VAL       (std::string)"\033[1;34m"
#define RESET      (std::string)"\033[0m"

# include "./AbstractVmException.class.hpp"
# include "./IOperand.class.hpp"
# include "./Factory.class.hpp"
# include "./Operand.class.hpp"
# include "./Lexeme.class.hpp"
# include "./Lexer.class.hpp"
# include "./Parser.class.hpp"
# include "./AbstractVm.class.hpp"

#endif
