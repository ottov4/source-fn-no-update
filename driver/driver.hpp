#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>

uintptr_t virtualaddy;

#define PaysonMemory CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFAC7, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define PaysonBase CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFAC9, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define PaysonSecurity 0x3B1CA69

typedef struct _ReadWriteRequest {
    INT32 Security;
    INT32 ProcessId;
    ULONGLONG Address;
    ULONGLONG Buffer;
    ULONGLONG Size;
    BOOLEAN Write;
} ReadWriteRequest, * PReadWriteRequest;

typedef struct _BaseAddressRequest {
    INT32 Security;
    INT32 ProcessId;
    ULONGLONG* Address;
} BaseAddressRequest, * PBaseAddressRequest;

namespace PaysonDRV {
    HANDLE DeviceHandle;
    INT32 ProcessID;

    bool DriverInit() {
        DeviceHandle = CreateFileW(L"\\\\.\\AndreuDickRidesPaysonNiggaCheats", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        return (DeviceHandle != INVALID_HANDLE_VALUE);
    }

    void ReadPhysicalMemory(PVOID address, PVOID buffer, DWORD size) {
        ReadWriteRequest request = { 0 };
        request.Security = PaysonSecurity;
        request.ProcessId = ProcessID;
        request.Address = (ULONGLONG)address;
        request.Buffer = (ULONGLONG)buffer;
        request.Size = size;
        request.Write = FALSE;

        DeviceIoControl(DeviceHandle, PaysonMemory, &request, sizeof(request), nullptr, 0, nullptr, nullptr);
    }

    void WritePhysicalMemory(PVOID address, PVOID buffer, DWORD size) {
        ReadWriteRequest request = { 0 };
        request.Security = PaysonSecurity;
        request.ProcessId = ProcessID;
        request.Address = (ULONGLONG)address;
        request.Buffer = (ULONGLONG)buffer;
        request.Size = size;
        request.Write = TRUE;

        DeviceIoControl(DeviceHandle, PaysonMemory, &request, sizeof(request), nullptr, 0, nullptr, nullptr);
    }

    uintptr_t GetBaseAddress() {
        uintptr_t ImageAddress = 0;
        BaseAddressRequest request = { 0 };
        request.Security = PaysonSecurity;
        request.ProcessId = ProcessID;
        request.Address = (ULONGLONG*)&ImageAddress;

        DeviceIoControl(DeviceHandle, PaysonBase, &request, sizeof(request), nullptr, 0, nullptr, nullptr);
        return ImageAddress;
    }

    INT32 FindProcessID(LPCTSTR process_name) {
        PROCESSENTRY32 pt;
        HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        pt.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hsnap, &pt)) {
            do {
                if (!lstrcmpi(pt.szExeFile, process_name)) {
                    CloseHandle(hsnap);
                    ProcessID = pt.th32ProcessID;
                    return pt.th32ProcessID;
                }
            } while (Process32Next(hsnap, &pt));
        }
        CloseHandle(hsnap);
        return 0;
    }
}

template <typename T>
T read(uint64_t address) {
    T buffer{ };
    PaysonDRV::ReadPhysicalMemory((PVOID)address, &buffer, sizeof(T));
    return buffer;
}

template <typename T>
T write(uint64_t address, T buffer) {

    PaysonDRV::WritePhysicalMemory((PVOID)address, &buffer, sizeof(T));
    return buffer;
}

bool IsValid(const uint64_t address)
{
    return (address > 0x400000 && address != 0xCCCCCCCCCCCCCCCC && reinterpret_cast<void*>(address) != nullptr && address < 0x7FFFFFFFFFFFFFFF);
}

template<typename T>
bool ReadArray(uintptr_t address, T out[], size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        out[i] = read<T>(address + i * sizeof(T));
    }
    return true;
}

template<typename T>
bool ReadArray2(uint64_t address, T* out, size_t len)
{
    if (!PaysonDRV::DeviceHandle || PaysonDRV::DeviceHandle == INVALID_HANDLE_VALUE)
    {
        if (!PaysonDRV::DriverInit())
        {
            return false;
        }
    }
    if (!out || len == 0)
    {
        return false;
    }
    for (size_t i = 0; i < len; ++i)
    {
        if (!IsValid(address + i * sizeof(T)))
        {
            return false;
        }
        out[i] = read<T>(address + i * sizeof(T));
    }
    return true;
}