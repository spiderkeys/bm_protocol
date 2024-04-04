#ifndef BCMP_SYSTEM_PLATFORM_COMMON_H
#define BCMP_SYSTEM_PLATFORM_COMMON_H

#include <stdint.h>

#include "bcmp/config.h"

// Platform-specific definitions
#if defined(BCMP_FREERTOS_LWIP)
#include "bcmp/system/platform/freertos_lwip.h"
#elif defined(BCMP_UNIX)
#include "bcmp/system/platform/unix.h"
#else
#error "Unknown platform"
#endif

// Common APIs around system types (mutexes, etc)
#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* BCMP_SYSTEM_PLATFORM_COMMON_H */