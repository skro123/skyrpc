#ifndef SKYRPC_MACRO_H
#define SKYRPC_MACRO_H

#include <assert.h>
#include <stdlib.h>
#include <string>
#include "util.h"

#if defined(__GNUC__)  || defined(__llvm__)
#   define SKYRPC_LIKELY(x)       __builtin_expect(!!(x), 1)
#   define SKYRPC_UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
#   define SKYRPC_LIKELY(x)       (x)
#   define SKYRPC_UNLIKELY(x)     (x)
#endif

#define SKYRPC_ASSERT(x) \
if(SKYRPC_UNLIKELY(!(x))){          \
    SKYRPC_LOG_ERROR(SKYRPC_LOG_ROOT()) << "ASSERTION: " << #x \
        << "\nbacktrace:\n" << skyrpc::BacktraceToString(100,2,"    "); \
    assert(x);         \
    exit(1);                       \
}
#define SKYRPC_ASSERT2(x,m) \
if(SKYRPC_UNLIKELY(!(x))){                 \
    SKYRPC_LOG_ERROR(SKYRPC_LOG_ROOT()) << "ASSERTION: " << #x \
        << "\n" << m <<"\n"              \
        << "\nbacktrace:\n" << skyrpc::BacktraceToString(100,2,"    "); \
    assert(x);            \
    exit(1);                       \
}

#define SKYRPC_STATIC_ASSERT(x) \
if constexpr(!(x)){          \
    SKYRPC_LOG_ERROR(SKYRPC_LOG_ROOT()) << "ASSERTION: " << #x \
        << "\nbacktrace:\n" << skyrpc::BacktraceToString(100,2,"    "); \
    exit(1);                          \
}

#endif //SKYRPC_MACRO_H
