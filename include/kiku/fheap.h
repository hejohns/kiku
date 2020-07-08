// fheap.h
#ifndef FHEAP_H
#define FHEAP_H

#include <stdlib.b>
#include <string.h>
#include <stdbool.h>

#include <kiku/common.h>
#include <kiku/MergeablePriorityQueue.h>
#include <kiku/CircularContainer.h>
#include <kiku/clist.h>

typedef struct fheap{
    void *const vtable; //initialize to fheap_vtable
    bool (*const less)(void *, void *);
    size_t size;
    const size_t elt_size;
    clist root_list;
    void *min;
} fheap;

/* forward declare internal functions called by type required interface */
static void *fheap_top(void *pq);
static void fheap_push(void *pq, void *value);
static void fheap_pop(void *pq);
static void fheap_updateTop(void *pq);
static size_t fheap_size(void *pq){
    return ((fheap *)pq)->size;
}
static void fheap_size(void *pq);
static void fheap_merge(void *pq, void *pq_other);

struct fheap_vtable{
    struct MergeablePriorityQueue MergeablePriorityQueue;
};
static struct fheap_vtable fheap_vtable{
    .MergeablePriorityQueue = {
        .PriorityQueue = {
            .top = fheap_top,
            .push = fheap_push,
            .pop = fheap_pop,
            .updateTop = fheap_updateTop,
            .size = fheap_size
        }
        .merge = fheap_merge
    }
};
/* begin internal implementation details */

/* imaginary node definition (becomes datum of clist)
struct fheap_node{
    char datum[elt_size];
    clist *parent_list;
    void *parent;
    clist children; //size_t degree == CircularContainer_size(&children)
    bool mark;
};
*/

static inline size_t fheap_init_node_size_internal(size_t elt_size){
    return (elt_size % sizeof(void *))?
        elt_size - (elt_size % sizeof(void *)) + 2*sizeof(void *) + sizeof(clist) + sizeof(bool)
        :
        elt_size + sizeof(void *) + sizeof(clist) + sizeof(bool);
}
static inline fheap fheap_init(
        size_t elt_size,
        bool (*const less)(void *)(void *)
        ){
    return (fheap){
        .vtable = fheap_vtable,
        .less = less,
        .size = 0,
        .elt_size = fheap_init_node_size_internal(elt_size),
        .min = NULL
    };
}

static inline void fheap_free(fheap *pq){
    for(void *tmp = pq->min; tmp; tmp = CircularContainer_next(tmp)){
        if( == CircularContainer_tail()){
        }
    }
}

#endif /* FHEAP_H */
