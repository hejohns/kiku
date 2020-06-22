// bheap.h
#ifndef BHEAP_H
#define BHEAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <kiku/common.h>
#include <kiku/PriorityQueue.h>

typedef struct bheap{
    void *const vtable; //initialize to bheap_vtable
    void *arr;
    bool (*const less)(void *, void *);
    size_t size;
    const size_t elt_size;
    size_t capacity;
} bheap;

/* forward declare internal functions called by type required interface */
static void bheap_push_internal(bheap *pq, const void *value);
static void bheap_pop_internal(bheap *pq);
static void bheap_siftDown(bheap *pq, size_t index);

static void *bheap_top(void *pq){
    return (((bheap *)pq)->size) ? ((bheap *)pq)->arr : (exit(EXIT_FAILURE), (void *)0);
}
static void bheap_push(void *pq, void *value){
    bheap_push_internal((bheap *)pq, value);
}
static void bheap_pop(void *pq){
    bheap_pop_internal((bheap *)pq);
}
static void bheap_updateTop(void *pq){
    bheap_siftDown((bheap *)pq, 0);
}
static size_t bheap_size(void *pq){
    return ((bheap *)pq)->size;
}

struct bheap_vtable{
    struct PriorityQueue PriorityQueue;
};
static struct bheap_vtable bheap_vtable = {
    .PriorityQueue = {
        .top = bheap_top,
        .push = bheap_push,
        .pop = bheap_pop,
        .updateTop = bheap_updateTop,
        .size = bheap_size
    }
};
/* begin internal implementation details */

#define BHEAP_GROWTH_FACTOR 2

static inline bheap bheap_init(
        bool (*const less)(void *, void *),
        size_t size,
        size_t elt_size
        ){
    return (bheap){
        .vtable = &bheap_vtable,
        .arr = kiku_malloc(size*elt_size),
        .less = less,
        .size = 0,
        .elt_size = elt_size,
        .capacity = size
    };
}

static inline void bheap_free(bheap *pq){
    free(pq->arr);
    pq->arr = NULL;
    pq->size = 0;
    pq->capacity = 0;
}

static void bheap_siftDown(bheap *pq, size_t index){
    /* O(log(height of tree - height of index)) */
    size_t index_lchild; /* left child or lesser child */
    while(2*index+1 <= pq->size-1){
        index_lchild = 2*index+1;
        if(index_lchild+1 <= pq->size-1){
            if(pq->less((char *)pq->arr + index_lchild*pq->elt_size, (char *)pq->arr + (index_lchild+1)*pq->elt_size)){
                index_lchild++;
            }
        }
        if(pq->less((char *)pq->arr + index_lchild*pq->elt_size, (char *)pq->arr + index*pq->elt_size)){
            break;
        }
        else{
            memswp((char *)pq->arr + (index_lchild*pq->elt_size), (char *)pq->arr + (index*pq->elt_size), pq->elt_size);
        }
        index = index_lchild;
    }
}

static void bheap_siftUp(bheap *pq, size_t index){
    /* O(log(height of index)) */
    while(index != 0){
        if(pq->less((char *)pq->arr+((index-1)/2)*pq->elt_size, (char *)pq->arr+index*pq->elt_size)){
            memswp((char *)pq->arr + (((index-1)/2)*pq->elt_size), (char *)pq->arr + (index*pq->elt_size), pq->elt_size);
            index = (index-1)/2;
        }
        else{
            break;
        }
    }
}

static void bheap_push_internal(bheap *pq, const void *value){
    /* O(log size) */
    if(!(pq->size < pq->capacity)){
        pq->arr = kiku_realloc(pq->arr, BHEAP_GROWTH_FACTOR*(pq->size*pq->elt_size));
        pq->capacity *= BHEAP_GROWTH_FACTOR;
    }
    memcpy((char *)pq->arr + (pq->size)*pq->elt_size, value, pq->elt_size);
    pq->size++;
    bheap_siftUp(pq, pq->size-1);
}

static void bheap_pop_internal(bheap *pq){
    /* O(log size) */
    if(pq->size > 1){
        memcpy((char *)pq->arr, (char *)pq->arr + (pq->size-1)*pq->elt_size, pq->elt_size);
        pq->size--;
        bheap_siftDown(pq, 0);
    }
    else if(pq->size == 1){
        pq->size--; //prevent wrap around
    }
    else{
        exit(EXIT_FAILURE); //Can't pop from an empty heap
    }
}

#endif /* BHEAP_H */
