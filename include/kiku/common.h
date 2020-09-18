// common.h
#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* 
 * define KIKU_USE_STATIC_BUF to use a static char buffer
 * of size KIKU_MEMSWP_BUFSIZ chars
 *
 * define KIKU_USE_VLA to use vla/memcpy for memswp
 *
 * define KIKU_USE_DUFFS to use duff's device for memswp
 *
 * default is as in glibc, to be safe and only use a single char buffer
 */
static inline void memswp(void *restrict a, void *restrict b, size_t size){
    assert(((void)"memswp breaks on size == 0 to improve performance", size));
#if defined(KIKU_USE_STATIC_BUF)
#  if !defined(KIKU_MEMSWP_BUFSIZ)
#  error "must define a non-zero size for KIKU_MEMSWP_BUFSIZ"
#  endif
#  warning "Using KIKU_USE_STATIC_BUF"
static_assert(
        KIKU_MEMSWP_BUFSIZ / sizeof(size_t) > 0,
        "KIKU_MEMSWP_BUFSIZ needs to be at least sizeof(size_t)"
        );
    static size_t tmp[KIKU_MEMSWP_BUFSIZ / sizeof(size_t)];
    assert(((void)"KIKU_MEMSWP_BUFSIZ exceeded", KIKU_MEMSWP_BUFSIZ >= size));
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
#elif defined(KIKU_USE_VLA)
#  if defined(__STDC_NO_VLA__)
#  error "compiler does not support VLA"
#  endif
#  warning "Using KIKU_USE_VLA"
    char tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
#elif defined(KIKU_USE_DUFFS)
#  if defined(MEMSWP_SWAP)
#  error "MEMSWP_SWAP should not be defined outside of here"
#  endif
#  warning "Using KIKU_USE_DUFFS"
#define MEMSWP_SWAP                                        \
    tmp = *(char *)a;                                      \
    *(char *)a = *(char *)b;                               \
    a = (char *)a + 1;                                     \
    *(char *)b = tmp;                                      \
    b = (char *)b + 1;                                     \
    (void)0 /* force semicolon w/o do/while(0) loop */

    size_t iter = (size + 15)/16;
    register char tmp;
    switch(size & (16U-1)){ //equivalent to switch(size % 16)
        do{
        case 0: MEMSWP_SWAP;
        case 15: MEMSWP_SWAP;
        case 14: MEMSWP_SWAP;
        case 13: MEMSWP_SWAP;
        case 12: MEMSWP_SWAP;
        case 11: MEMSWP_SWAP;
        case 10: MEMSWP_SWAP;
        case 9: MEMSWP_SWAP;
        case 8: MEMSWP_SWAP;
        case 7: MEMSWP_SWAP;
        case 6: MEMSWP_SWAP;
        case 5: MEMSWP_SWAP;
        case 4: MEMSWP_SWAP;
        case 3: MEMSWP_SWAP;
        case 2: MEMSWP_SWAP;
        case 1: MEMSWP_SWAP;
        } while(--iter);
    }
#undef MEMSWP_SWAP
#else
#warning "Using default (slow) memswp"
    register char tmp;
    do{
        tmp = *(char *)a;
        *(char *)a = *(char *)b;
        a = (char *)a + 1;
        *(char *)b = tmp;
        b = (char *)b + 1;
    } while(--size);
#endif
}

static inline void *kiku_malloc(size_t size){
    void *tmp = malloc(size);
    assert(((void)"malloc failed", !(!tmp && size)));
    return tmp;
}

/* usage is different than stdlib's free()
 *
 * void *ptr = kiku_malloc(1);     vs     void *ptr = malloc(1);
 * kiku_free(&ptr);                       free(ptr), ptr = NULL;
 */
static inline void kiku_free(void **ptr){
    free(*ptr);
    *ptr = NULL;
}

static inline void *kiku_calloc(size_t nmemb, size_t size){
    void *tmp = calloc(nmemb, size);
    assert(((void)"calloc failed", !(!tmp && nmemb && size)));
    return tmp;
}

static inline void *kiku_realloc(void *ptr, size_t size){
    void *tmp = realloc(ptr, size);
    assert(((void)"realloc failed", !(!tmp && size)));
    return tmp;
}

#endif /* COMMON_H */
