// common.h
#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <string.h>

/* define KIKU_USE_VLA to use vla/memcpy for memswp
 *
 * default is as in glibc, to be safe and only use a single char buffer
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
        *(char *)a = *(char *)b;
        a = (char *)a + 1;
        *(char *)b = tmp;
        b = (char *)b + 1;
    }
#endif
}

static inline void *kiku_malloc(size_t size){
    void *tmp = malloc(size);
    if(!tmp && size){
        exit(EXIT_FAILURE);
    }
    return tmp;
}

static inline void *kiku_calloc(size_t nmemb, size_t size){
    void *tmp = calloc(nmemb, size);
    if(!tmp && nmemb && size){
        exit(EXIT_FAILURE);
    }
    return tmp;
}

static inline void *kiku_realloc(void *ptr, size_t size){
    void *tmp = realloc(ptr, size);
    if(tmp){
        return tmp;
    }
    else{
        exit(EXIT_FAILURE);
    }
}

#endif /* COMMON_H */
