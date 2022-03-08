#include "main.hpp"

#define MAX_INPUT 4096

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
    private:
        bool TextMode = false;
        int sVar[2048] = { 0 };
        int sVarPtr = 0;
};