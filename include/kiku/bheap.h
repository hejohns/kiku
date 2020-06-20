// bheap.h
#ifndef BHEAP_H
#define BHEAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <kiku/common.h>
#include <kiku/priority_queue.h>

typedef struct bheap{
    void *const vtable; //initialize to bheap_vtable
    void *arr;
    bool (*const less)(void *, void *);
    size_t size;
    const size_t elt_size;
    size_t capacity;
} bheap;

#define BHEAP_GROWTH_FACTOR 2

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
        void *tmp = realloc(pq->arr, BHEAP_GROWTH_FACTOR*(pq->size*pq->elt_size));
        if(tmp){
            pq->arr = tmp;
            pq->capacity *= BHEAP_GROWTH_FACTOR;
        }
        else{
            exit(EXIT_FAILURE); //realloc failure
        }
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
        pq->size--;
    }
    else{
        exit(EXIT_FAILURE); //Can't pop from an empty heap
    }
}

static void *bheap_top(void *pq){
    return ((bheap *)pq)->arr;
}
static void bheap_push(void *pq, void *value){
    bheap_push_internal((bheap *)pq, value);
}
static void bheap_pop(void *pq){
    bheap_pop_internal((bheap *)pq);
}
static void bheap_update_top(void *pq){
    bheap_siftDown((bheap *)pq, 0);
}
static size_t bheap_size(void *pq){
    return ((bheap *)pq)->size;
}

struct bheap_vtable{
    struct priority_queue priority_queue;
};
static struct bheap_vtable bheap_vtable = {
    .priority_queue = {
        .top = bheap_top,
        .push = bheap_push,
        .pop = bheap_pop,
        .update_top = bheap_update_top,
        .size = bheap_size
    }
};

static inline bheap bheap_init(
        bool (*const less)(void *, void *),
        size_t size,
        size_t elt_size
        ){
    void *tmp = malloc(size*elt_size);
    if(!tmp && size){ //malloc failure
        exit(EXIT_FAILURE);
    }
    return (bheap){
        .vtable = &bheap_vtable,
        .arr = tmp,
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

static inline void bheap_make_heap(bheap *pq){
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
    bheap tmp = {
        .arr = base,
        .less = less,
        .elt_size = size,
        .size = nmemb
    };
    bheap_make_heap(&tmp);
    for(size_t i=nmemb-1; i > 0; i--){
        memswp((char *)tmp.arr + i*tmp.elt_size, (char *)tmp.arr, tmp.elt_size);
        tmp.size--;
        bheap_siftDown(&tmp, 0);
    }
}

#endif /* BHEAP_H */
