#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>

#include "process_memory.h"

mf_error_t mf_windows_read_memory( struct mf_process *process, uintptr_t address, void *buffer, size_t size) {
    SIZE_T bytes_read;
    int success;

    if (process == NULL || buffer == NULL || size == 0) {
        return MF_ERR_INVALID_ARGUMENT;
    }

    success = ReadProcessMemory(process->os_handle, (LPCVOID)address, buffer, size, &bytes_read);

    if (!success) {
        return MF_ERR_PROCESS_ACCESS;
    }

    if (bytes_read != size) {
        return MF_ERR_PROCESS_ACCESS;
    }

    return MF_OK;
}
