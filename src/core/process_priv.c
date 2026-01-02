#include <stdlib.h>
#include <string.h>

#include "mf_types.h"      // mf_error_t, MF_ERR_*
#include "internal.h"      // struct mf_process, ctx, os backend
#include "process_internal.h"


/* ============================
 * Internal implementation
 * ============================ */

mf_error_t mf_process_create(
    struct mf_context *ctx,
    int pid,
    struct mf_process **process
)
{
    struct mf_process *p = calloc(1, sizeof(*p));
    if (!p) {
        return MF_ERR_NO_MEMORY;
    }

    p->pid = pid;
    p->ctx = ctx;

    mf_error_t err = mf_process_attach_os(p);
    if (err != MF_OK) {
        free(p);
        return err;
    }

    *process = p;
    return MF_OK;
}

void mf_process_destroy(struct mf_process *process)
{
    if (!process) {
        return;
    }

    mf_process_detach_os(process);
    free(process);
}

mf_error_t mf_process_attach_os(struct mf_process *process)
{
    if (!process || !process->ctx || !process->ctx->os) {
        return MF_ERR_INTERNAL;
    }

    if (process->ctx->os->attach_process(process) != 0) {
        return MF_ERR_PROCESS_ACCESS;
    }

    return MF_OK;
}

void mf_process_detach_os(struct mf_process *process)
{
    if (!process || !process->ctx || !process->ctx->os) {
        return;
    }

    if (process->ctx->os->detach_process) {
        process->ctx->os->detach_process(process);
    }
}
