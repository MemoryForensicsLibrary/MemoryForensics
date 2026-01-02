#ifndef MF_INTERNAL_H
#define MF_INTERNAL_H

#include <stddef.h>
#include <stdint.h>
#include "mf_types.h"


/*
 * Internal structures and interfaces for Memory Forensics Library.
 *
 * This header is NOT part of the public API.
 * It defines internal representations and OS abstraction layers.
 */

/* ============================
 * Forward declarations
 * ============================ */

struct mf_os_backend;

/* ============================
 * Context
 * ============================ */

struct mf_context {
    struct mf_os_backend *os;
};

/* ============================
 * Process
 * ============================ */

struct mf_process {
    int pid;

    void *os_handle;      /* OS-specific process handle */
    struct mf_context *ctx;
};

/* ============================
 * Memory Region
 * ============================ */

struct mf_mem_region {
    uintptr_t start;
    uintptr_t end;

    uint32_t permissions; /* R/W/X flags */
};

/* ============================
 * Snapshot
 * ============================ */

struct mf_snapshot {
    struct mf_process *process;

    struct mf_mem_region *regions;
    size_t region_count;

    uint8_t **region_hashes; /* Per-region hash/checksum */
};

/* ============================
 * Diff
 * ============================ */

struct mf_diff {
    size_t modified_regions;
    size_t modified_bytes;
};

/* ============================
 * OS Backend Interface
 * ============================ */

struct mf_os_backend {
    const char *name;

    int (*attach_process)(
        struct mf_process *process
    );

    void (*detach_process)(
        struct mf_process *process
    );

    int (*enumerate_regions)(
        struct mf_process *process,
        struct mf_mem_region **regions,
        size_t *count
    );

    int (*read_memory)(
        struct mf_process *process,
        uintptr_t address,
        void *buffer,
        size_t size
    );
};

#endif /* MF_INTERNAL_H */
