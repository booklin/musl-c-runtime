// © 2021 Qualcomm Innovation Center, Inc. All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause

// Local version of the standard-defined string.h
//
// Only the memory block manipulation functions (mem*()) are declared. The
// hypervisor has no need to operate on real strings, so the string
// manipulation functions (str*()) are left undefined.
//
// Note: MISRA Required Rule 21.2 states that reserved identifiers are not to
// be declared, and gives a memcpy declaration as a specific non-conforming
// example. However, the identifiers declared here (including memcpy) are
// _not_ reserved: the hypervisor is built in freestanding mode (as asserted
// below), which does not guarantee their presence and therefore must not give
// them special behaviour (see C18 clause 4, item 6). The Clang/GCC option
// -ffreestanding implies -fno-builtin for this reason.
//
// Also, we _must_ implement these functions ourselves with their standard
// semantics (regardless of MISRA 21.2) because the LLVM and GCC backends
// assume they are provided by the environment, and will generate calls to
// them even when the frontend is in freestanding mode.

#if !defined(HYP_STANDALONE_TEST)
_Static_assert(__STDC_HOSTED__ == 0,
	       "This file deviates from MISRA rule 21.2 in hosted mode");
#endif

// Define size_t, ssize_t and NULL
#include <stddef.h>
#define __NEED_ssize_t
#include <bits/alltypes.h>

extern void *
memcpy(void *restrict s1, const void *restrict s2, size_t n);

extern void *
memmove(void *s1, const void *s2, size_t n);

extern void *
memset(void *s, int c, size_t n);

extern void *
memchr(const void *s, int c, size_t n);

extern int
strcmp(const char *s1, const char *s2);

extern size_t
strlen(const char *str);

extern ssize_t
strscpy(char *dest, const char *str, size_t count);
