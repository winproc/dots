#include "reader.hpp"

// function to flip bool
bool flip(bool *val) {
    bool dref = *val;
    if (dref) {
        *val = false;
        return false;
    } else { 
        *val = true;
        return true;
    }
}

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
            case 1: // output
            {
                int outval =  sVar[sVarPtr] ? sVar[sVarPtr] : *(it + 0x1); // use custom val if selected loc is null, otherwise use selected loc
                if (!TextMode) {
                    std::cout << outval;
                } else {
                    std::cout << (char)(96 + outval); // 96 is ascii offset 
                }
                break;
            }
            case 2: // get input
            {
                char buf[MAX_INPUT];
                std::cin >> buf;
                int val = *(it + 0x1);
                if (sVarPtr) { sVar[sVarPtr] = val; } // set val if pointer is not at 0th loc
                break;
            }
            case 3: // select loc
            {
                int selector = *(it + 0x1) - 1;
                sVarPtr = selector;
                break;
            }
            case 4: // int/ascii mode
            {
                flip(&TextMode);
                break;
            }
            case 5: // clear val location
            {
                sVar[sVarPtr] = 0x0;
                break;
            }
            default:
                break;
            case 6: // newline
            {
                std::cout << "\n";
                break;
            }
        }
    }
    return message;
}
