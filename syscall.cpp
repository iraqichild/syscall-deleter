#include "iraqi.h"


int main()
{
	printf("syscall\n");

	syscall::InitNtdll();
	syscall::headers::InitHeaders();

	NAO ntdllNAO = syscall::GetNAO();

    int NumberOfNames = syscall::headers::EXPORT_DIR->NumberOfNames;

    for (DWORD i = 0; i < NumberOfNames; ++i)
    {
        char* FunctionName = syscall::GetFunctionName(i);
        if (!syscall::IsNtFunction(FunctionName))
            continue;

        DWORD funcAddressRVA = ntdllNAO.addressTable[ntdllNAO.ordinalTable[i]];
        PVOID funcAddressCalc = reinterpret_cast<PVOID>((DWORD_PTR)syscall::NTDLL + funcAddressRVA);

        printf("\n\n");
        printf("==============================================\n");
        printf("[) Function #%d: \033[1;36m%s\033[0m\n", i + 1, FunctionName);
        printf("[) Address: \033[1;35m0x%p\033[0m\n", funcAddressCalc);
        printf("==============================================\n");

        BYTE SSN;
        BYTE NEWSSN = 0x00;
        PVOID SSNADDRESS = (PVOID)((DWORD_PTR)funcAddressCalc + 0x4);
        DWORD OLDPROTECT;

        memcpy(&SSN, SSNADDRESS, sizeof(BYTE));
        printf("[) SSN -> \033[1;32m%x\033[0m\n", SSN);

        VirtualProtect(SSNADDRESS, sizeof(BYTE), PAGE_EXECUTE_WRITECOPY, &OLDPROTECT);
        memcpy(SSNADDRESS, &NEWSSN, sizeof(BYTE));
        VirtualProtect(SSNADDRESS, sizeof(BYTE), OLDPROTECT, NULL);

        memcpy(&SSN, SSNADDRESS, sizeof(BYTE));
        printf("[) Overwritten SSN -> \033[1;31m%x\033[0m\n", SSN);

        printf("[) Done\n");
        printf("==============================================\n");
    }






	getchar();
	return 0;
}