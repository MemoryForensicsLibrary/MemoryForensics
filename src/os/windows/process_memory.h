#ifndef MF_WINDOWS_PROCESS_MEMORY_H
#define MF_WINDOWS_PROCESS_MEMORY_H

#include <stddef.h>
#include <stdint.h>
#include "internal.h"
#include "mf_types.h"

mf_error_t mf_windows_read_memory(
    struct mf_process *process,
    uintptr_t address,
    void *buffer,
    size_t size
);

#endif
