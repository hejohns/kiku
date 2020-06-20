// static_bheap.h
#ifndef STATIC_BHEAP_H
#define STATIC_BHEAP_H

#include <stdlib.h>
#include <kiku/bheap.h>

typedef bheap static_bheap;

static void static_bheap_push_internal(static_bheap *pq, void *value){
    if(!(pq->size < pq->capacity)){
        exit(EXIT_FAILURE); //can't grow statically allocated storage
    }
    memcpy((char*)pq->arr + (pq->size)*pq->elt_size, value, pq->elt_size);
    pq->size++;
    bheap_siftUp(pq, pq->size-1);
}

static void static_bheap_push(void *pq, void *value){
    static_bheap_push_internal(pq, value);
}

static struct bheap_vtable static_bheap_vtable = {
    .priority_queue = {
        .top = bheap_top,
        .push = static_bheap_push,
        .pop = bheap_pop,
        .update_top = bheap_update_top,
        .size = bheap_size
    }
};

static inline static_bheap static_bheap_init(
        bool (*const less)(void *, void *),
        size_t size,
        size_t elt_size,
        void *arr){
    return (static_bheap){
        .vtable = &static_bheap_vtable,
        .arr = arr,
        .less = less,
        .size = 0,
        .elt_size = elt_size,
        .capacity = size
    };
}

static void static_bheap_free(static_bheap *pq){
    // do nothing
    (void)pq;
}

#endif /* STATIC_BHEAP_H */
