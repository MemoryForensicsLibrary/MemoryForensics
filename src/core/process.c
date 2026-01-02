#include <stdlib.h>

#include <memory_forensics.h>
#include "process_internal.h"

/* ============================
 * Public API
 * ============================ */

mf_error_t mf_process_attach(
    mf_context_t *ctx,
    int pid,
    mf_process_t **process
)
{
    if (!ctx || !process || pid <= 0) {
        return MF_ERR_INVALID_ARGUMENT;
    }

    return mf_process_create(ctx, pid, process);
}

void mf_process_detach(mf_process_t *process)
{
    if (!process) {
        return;
    }

    mf_process_destroy(process);
}
