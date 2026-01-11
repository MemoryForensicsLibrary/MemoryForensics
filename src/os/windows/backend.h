#ifndef MF_WINDOWS_BACKEND_H
#define MF_WINDOWS_BACKEND_H

#include "internal.h"

/*
 * Returns a pointer to the Windows OS backend.
 * Singleton-style backend descriptor.
 */
struct mf_os_backend *mf_windows_backend(void);

#endif
