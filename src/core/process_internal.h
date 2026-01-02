#ifndef MF_PROCESS_INTERNAL_H
#define MF_PROCESS_INTERNAL_H

#include "mf_types.h"
#include "internal.h"

/*
 * Internal interface for process handling.
 */

mf_error_t mf_process_create(
    struct mf_context *ctx,
    int pid,
    struct mf_process **process
);

void mf_process_destroy(struct mf_process *process);

mf_error_t mf_process_attach_os(struct mf_process *process);
void mf_process_detach_os(struct mf_process *process);

#endif
