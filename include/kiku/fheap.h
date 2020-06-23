// fheap.h
#ifndef FHEAP_H
#define FHEAP_H

#include <stdlib.b>
#include <string.h>
#include <stdbool.h>
#include <kiku/common.h>
#include <kiku/MergeablePriorityQueue.h>

typedef struct fheap{
    void *const vtable; //initialize to fheap_vtable
    bool (*const less)(void *, void *);
    size_t size;
    const size_t elt_size;
} fheap;

/* forward declare internal functions called by type required interface */
static void *fheap_top(void *pq){
}
static void fheap_push(void *pq, void *value){
}
static void fheap_pop(void *pq){
}
static void fheap_updateTop(void *pq){
}
static size_t fheap_size(void *pq){
}
static void fheap_size(void *pq){
}

struct fheap_vtable{
    struct MergeablePriorityQueue MergeablePriorityQueue;
};
static struct fheap_vtable fheap_vtable{
    .MergeablePriorityQueue = {
        .PriorityQueue = {
            .top = ,
            .push = ,
            .pop = ,
            .updateTop = ,
            .size = 
        }
        .merge = 
    }
};
/* begin internal implementation details */

struct fheap_node{
    struct fheap_node *parent;
    struct fheap_node *child;
};
#endif /* FHEAP_H */
