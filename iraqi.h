#include <windows.h>
#include <iostream>

typedef struct _Function
{
    BYTE SSN;
    PVOID Address;
} Function, * PFUNCTION;

struct NAO
{
    DWORD* nameTable;
    DWORD* addressTable;
    WORD* ordinalTable;
};

#define TEXT_NTDLL (L"ntdll.dll")

namespace syscall
{
    inline PVOID NTDLL;

    // Function to initialize NTDLL handle
    inline void InitNtdll()
    {
        if (!syscall::NTDLL)
        {
            syscall::NTDLL = GetModuleHandle(TEXT_NTDLL);
        }
    }

    namespace headers
    {
        extern IMAGE_DOS_HEADER* DOS_HEADERS;
        extern IMAGE_NT_HEADERS* NT_HEADERS;
        extern IMAGE_DATA_DIRECTORY EXPORTS;
        extern PIMAGE_EXPORT_DIRECTORY EXPORT_DIR;

        void InitHeaders();
    }

    inline NAO GetNAO()
    {
        NAO x;
        x.nameTable = reinterpret_cast<DWORD*>(reinterpret_cast<DWORD_PTR>(syscall::NTDLL) + headers::EXPORT_DIR->AddressOfNames);
        x.addressTable = reinterpret_cast<DWORD*>(reinterpret_cast<DWORD_PTR>(syscall::NTDLL) + headers::EXPORT_DIR->AddressOfFunctions);
        x.ordinalTable = reinterpret_cast<WORD*>(reinterpret_cast<DWORD_PTR>(syscall::NTDLL) + headers::EXPORT_DIR->AddressOfNameOrdinals);
        return x;
    }

    inline char* GetFunctionName(int x)
    {
        return reinterpret_cast<char*>(reinterpret_cast<DWORD_PTR>(syscall::NTDLL) + GetNAO().nameTable[x]);
    }

    inline bool IsNtFunction(char* FunctionName)
    {
        if (FunctionName && strlen(FunctionName) >= 2)
        {
            return FunctionName[0] == 'N' && FunctionName[1] == 't';
        }
        return false;
    }

}
