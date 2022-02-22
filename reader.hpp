#include "main.hpp"

typedef struct {
    std::vector<int> OpcodesArray;
    int nSize;
} Opcodes, *POpcodes;

typedef struct {
    bool Success;
    std::string errorMessage;
} PrMessage;

class Interpreter {
    public:
        Opcodes GetOpcodes(TCHAR* array, int nSize);
        PrMessage ExecOpcode(POpcodes opcode);
};