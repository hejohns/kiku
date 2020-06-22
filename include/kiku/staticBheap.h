// staticBheap.h
#ifndef STATICBHEAP_H
#define STATICBHEAP_H

#include <stdlib.h>
#include <kiku/bheap.h>

typedef bheap staticBheap;

/* forward declare internal functions called by type required interface */
static void staticBheap_push_internal(staticBheap *pq, void *value);

static void staticBheap_push(void *pq, void *value){
    staticBheap_push_internal((bheap *)pq, value);
}

static struct bheap_vtable staticBheap_vtable = {
    .PriorityQueue = {
        .top = bheap_top,
        .push = staticBheap_push,
        .pop = bheap_pop,
        .updateTop = bheap_updateTop,
        .size = bheap_size
    }
};
/* begin internal implementation details */

static inline staticBheap staticBheap_init(
        bool (*const less)(void *, void *),
        size_t size,
        size_t elt_size,
        void *arr){
    return (staticBheap){
        .vtable = &staticBheap_vtable,
        .arr = arr,
        .less = less,
        .size = 0,
        .elt_size = elt_size,
        .capacity = size
    };
}

static inline void staticBheap_free(staticBheap *pq){
    // do nothing
    (void)pq;
}

static void staticBheap_push_internal(staticBheap *pq, void *value){
    if(!(pq->size < pq->capacity)){
        exit(EXIT_FAILURE); //can't grow statically allocated storage
    }
    memcpy((char*)pq->arr + (pq->size)*pq->elt_size, value, pq->elt_size);
    pq->size++;
    bheap_siftUp(pq, pq->size-1);
}

static inline void staticBheap_make_heap(staticBheap *pq){
    /* Floyd's heap algorithm */
    /* O(size) */
    if(pq->size <= 1){
        return;
    }
    size_t height = 0;
    for(size_t sz = pq->size >> 1; sz; height++, sz >>= 1){}
    for(size_t i=(1<<height)-2; i > 0; i--){
        bheap_siftDown(pq, i);
    }
    bheap_siftDown(pq, 0);
}

static inline void heapsort(void *base, size_t nmemb, size_t size,
        bool (*const less)(void *, void *)){
    staticBheap tmp = staticBheap_init(less, nmemb, size, base);
    staticBheap_make_heap(&tmp);
    for(size_t i=nmemb-1; i > 0; i--){
        memswp((char *)tmp.arr + i*tmp.elt_size, (char *)tmp.arr, tmp.elt_size);
        tmp.size--;
        bheap_siftDown(&tmp, 0);
    }
    staticBheap_free(&tmp);
}

#endif /* STATICBHEAP_H */

