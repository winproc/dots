#include "reader.hpp"


Opcodes Interpreter::GetOpcodes(TCHAR* array, int nSize) {
    Opcodes opcodes;
    int iterator = 0;
    int arrayCursor = 0;
    for (int i = 0; i < nSize; i++) {
        if (array[i] == '.') {
            iterator++;
        } else if (array[i] == ' ') {
            opcodes.OpcodesArray.push_back(iterator);
            iterator = 0;
            arrayCursor++;
        }
    }
    opcodes.nSize = opcodes.OpcodesArray.size();
    return opcodes;
}

PrMessage Interpreter::ExecOpcode(POpcodes opcode) {
    PrMessage message;
    message.Success = true;

    std::vector<int> arrayVec = opcode->OpcodesArray;
    for (std::vector<int>::iterator it = arrayVec.begin(); it != arrayVec.end(); it++) {
        if ((it - arrayVec.begin()) % 2) { continue; } // if iterator is at odd index then ignore iteration
        switch(*it) {
            case 1:
                std::cout << *(it + 0x1) << std::endl;
                break;
            default:
                break;
        }
    }
    return message;
}
