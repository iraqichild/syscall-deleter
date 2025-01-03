#include "iraqi.h"


namespace syscall {
    namespace headers {
        IMAGE_DOS_HEADER* DOS_HEADERS = nullptr;
        IMAGE_NT_HEADERS* NT_HEADERS = nullptr;
        IMAGE_DATA_DIRECTORY EXPORTS = { 0 };
        PIMAGE_EXPORT_DIRECTORY EXPORT_DIR = nullptr;

        void InitHeaders()
        {
            if (syscall::NTDLL) {
                DOS_HEADERS = reinterpret_cast<IMAGE_DOS_HEADER*>(syscall::NTDLL);
                NT_HEADERS = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<DWORD_PTR>(syscall::NTDLL) + DOS_HEADERS->e_lfanew);
                EXPORT_DIR = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(reinterpret_cast<DWORD_PTR>(syscall::NTDLL) + NT_HEADERS->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
                EXPORTS = NT_HEADERS->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
            }
        }
    }
}