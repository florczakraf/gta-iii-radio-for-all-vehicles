#include "pch.h"
#include <stdint.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    const unsigned char* V1_0_OFFSET_1 = (unsigned char*)0x601048;
    const unsigned int* V1_0_OFFSET_2 = (unsigned int*)0x5f3e18;
    const int8_t* V1_1_OFFSET = (int8_t*)0x601048;
    const unsigned char JMP = 0xEB;

    DWORD original_protection_status;
    DWORD tmp_protection_status;
    unsigned char* utility_vehicles_radio_jmp;
    unsigned char* law_enforcement_vehicles_radio_jmp;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Sleep(1000);  // arbitary sleep

        if (*V1_0_OFFSET_1 == 'o' && *V1_0_OFFSET_2 == 0x33617467 /*GTA3*/)  // v1.0
        {
            utility_vehicles_radio_jmp = (unsigned char*)0x57e50a;
            law_enforcement_vehicles_radio_jmp = (unsigned char*)0x57e6b5;
        }
        else if (*V1_1_OFFSET == -0x33)  // v1.1 retail
        {
            utility_vehicles_radio_jmp = (unsigned char*)0x57e85a;
            law_enforcement_vehicles_radio_jmp = (unsigned char*)0x57ea05;
        }
        else if (*V1_1_OFFSET == -0x5B)  // v1.1 steam
        {
            utility_vehicles_radio_jmp = (unsigned char*)0x57e75a;
            law_enforcement_vehicles_radio_jmp = (unsigned char*)0x57e905;
        }
        else
        {
            return TRUE;
        }

        VirtualProtect(utility_vehicles_radio_jmp, 1, 0x40, &original_protection_status);
        *utility_vehicles_radio_jmp = JMP;
        VirtualProtect(utility_vehicles_radio_jmp, 1, original_protection_status, &tmp_protection_status);

        VirtualProtect(law_enforcement_vehicles_radio_jmp, 1, 0x40, &original_protection_status);
        *law_enforcement_vehicles_radio_jmp = JMP;
        VirtualProtect(law_enforcement_vehicles_radio_jmp, 1, original_protection_status, &tmp_protection_status);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

