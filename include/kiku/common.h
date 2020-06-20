// common.h
#ifndef COMMON_H
#define COMMON_H

#include <string.h>

/* define KIKU_USE_VLA to use vla/memcpy for memswp
 *
 * default is as in glibc, to be safe and only use a char buffer
 */
static inline void memswp(void *restrict a, void *restrict b, size_t size){
#ifdef KIKU_USE_VLA
    char tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
#else
    for(; size; size--){
        char tmp = *(char *)a;
        *((char *)a) = *(char *)b;
        a = (char *)a + 1;
        *((char *)b) = tmp;
        b = (char *)b + 1;
    }
#endif
}

#endif /* COMMON_H */
