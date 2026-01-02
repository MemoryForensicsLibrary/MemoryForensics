#ifndef MEMORY_FORENSICS_H
#define MEMORY_FORENSICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include "mf_types.h"


/*
 * Memory Forensics Library
 *
 * Public API for live process memory inspection and runtime integrity analysis.
 *
 * This library provides controlled, read-only access to process memory,
 * allowing snapshot creation, comparison, and anomaly detection.
 *
 * Platform-specific details are intentionally hidden from the public API.
 */

/* ============================
 * Versioning
 * ============================ */

#define MF_VERSION_MAJOR 0
#define MF_VERSION_MINOR 1
#define MF_VERSION_PATCH 0

/* ============================
 * Forward Declarations
 * ============================ */

/* Opaque handles */
typedef struct mf_context        mf_context_t;
typedef struct mf_process        mf_process_t;
typedef struct mf_snapshot       mf_snapshot_t;
typedef struct mf_diff           mf_diff_t;

/* ============================
 * Error Handling
 * ============================ */

typedef enum {
    MF_OK = 0,

    MF_ERR_INVALID_ARGUMENT,
    MF_ERR_NO_MEMORY,
    MF_ERR_NOT_SUPPORTED,
    MF_ERR_PERMISSION_DENIED,

    MF_ERR_PROCESS_NOT_FOUND,
    MF_ERR_PROCESS_ACCESS,

    MF_ERR_SNAPSHOT_FAILED,
    MF_ERR_DIFF_FAILED,

    MF_ERR_INTERNAL
} mf_error_t;

/* ============================
 * Library Lifecycle
 * ============================ */

/*
 * Initializes the memory forensics library.
 *
 * Must be called before any other API function.
 */
mf_error_t mf_init(mf_context_t **ctx);

/*
 * Releases all resources associated with the library context.
 */
void mf_shutdown(mf_context_t *ctx);

/* ============================
 * Process Handling
 * ============================ */

/*
 * Attaches the library to a target process.
 *
 * pid: Target process ID.
 */
mf_error_t mf_process_attach(
    mf_context_t  *ctx,
    int            pid,
    mf_process_t **process
);

/*
 * Detaches from a previously attached process.
 */
void mf_process_detach(mf_process_t *process);

/* ============================
 * Snapshot Management
 * ============================ */

/*
 * Creates a snapshot of the current process memory state.
 */
mf_error_t mf_snapshot_create(
    mf_process_t  *process,
    mf_snapshot_t **snapshot
);

/*
 * Releases a snapshot.
 */
void mf_snapshot_destroy(mf_snapshot_t *snapshot);

/* ============================
 * Snapshot Comparison
 * ============================ */

/*
 * Compares two memory snapshots and produces a diff object.
 */
mf_error_t mf_snapshot_diff(
    const mf_snapshot_t *old_snapshot,
    const mf_snapshot_t *new_snapshot,
    mf_diff_t          **diff
);

/*
 * Releases a diff object.
 */
void mf_diff_destroy(mf_diff_t *diff);

/* ============================
 * Analysis & Reporting
 * ============================ */

/*
 * Returns the number of modified memory regions detected in a diff.
 */
size_t mf_diff_modified_region_count(const mf_diff_t *diff);

/*
 * Returns the number of bytes changed across all regions.
 */
size_t mf_diff_modified_bytes(const mf_diff_t *diff);

/* ============================
 * Utility
 * ============================ */

/*
 * Returns a human-readable string for an error code.
 */
const char *mf_strerror(mf_error_t err);

#ifdef __cplusplus
}
#endif

#endif /* MEMORY_FORENSICS_H */
