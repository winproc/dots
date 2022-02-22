#include "main.hpp"
#include "reader.hpp"


HANDLE OpenFile(LPCWSTR filename) {
    return CreateFileW(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

void printArray(TCHAR* start, int nSize) {
    for (int i = 0; i < nSize; i++) {
        std::cout << start[i];
    }
    std::cout << std::endl;
}

template <class T>
void printVector(std::vector<T> vector) {
    for (typename std::vector<T>::iterator it = vector.begin(); it != vector.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    DWORD bytesRead;
    
    HANDLE hFile = OpenFile(L"main.dts");

    LARGE_INTEGER fileSize;
    GetFileSizeEx(hFile, &fileSize);
    TCHAR *tBuffer = (TCHAR*)malloc(sizeof(TCHAR) * fileSize.QuadPart);

    if (GetLastError() == ERROR_FILE_NOT_FOUND) {
        std::cout << "Failed to get main.dts" << std::endl;
    } else if (ReadFile(hFile, tBuffer, (DWORD)64, &bytesRead, NULL)) {
        Interpreter reader;
        Opcodes opcodes = reader.GetOpcodes(tBuffer, bytesRead);
        reader.ExecOpcode(&opcodes);
    } else {
        std::cout << GetLastError() << std::endl;
        
    }
    free(tBuffer);
    
    return 0;
}