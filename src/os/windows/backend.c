#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "backend.h"
#include "process_maps.h"
#include "process_memory.h"


static mf_error_t windows_attach_process(struct mf_process *process)
{
    if (process == NULL) {
        return MF_ERR_INVALID_ARGUMENT;
    }

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process->pid);

    if (hProcess == NULL) {
        return MF_ERR_PROCESS_ACCESS;
    }

    process->os_handle = hProcess;

    return MF_OK;
}


static void windows_detach_process(struct mf_process *process)
{
    if (process && process->os_handle) {
        CloseHandle(process->os_handle);
        process->os_handle = NULL;
    }
}


static struct mf_os_backend windows_backend = {
    .name = "windows",

    .attach_process = windows_attach_process,
    .detach_process = windows_detach_process,
    .enumerate_regions = mf_windows_enumerate_maps,
    .read_memory = mf_windows_read_memory
};

struct mf_os_backend *mf_windows_backend(void)
{
    return &windows_backend;
}
