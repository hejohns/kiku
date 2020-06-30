// clist.h
#ifndef CLIST_H
#define CLIST_H

#include <assert.h>

#include <kiku/common.h>
#include <kiku/CircularContainer.h>
#include <kiku/dlist.h>

typedef dlist clist;

/* forward declare internal functions called by type required interface */
static void *clist_next(void *cont, void *node);
static void *clist_prev(void *cont, void *node);

struct clist_vtable{
    struct CircularContainer CircularContainer;
};
static struct clist_vtable clist_vtable = {
    .CircularContainer = {
        .BidirectionalContainer = {
            .DirectionalContainer = {
                .begin = slist_begin,
                .end = slist_end,
                .next = clist_next,
                .size = slist_size,
                .pushFront = dlist_pushFront,
                .popFront = dlist_popFront,
                .insertAfter = dlist_insertAfter,
                .eraseAfter = dlist_eraseAfter,
                .merge = dlist_merge,
                .clear = dlist_clear
            },
            .prev = clist_prev,
            .tail = dlist_tail,
            .pushBack = dlist_pushBack,
            .popBack = dlist_popBack,
            .insertBefore = dlist_insertBefore,
            .eraseBefore = dlist_eraseBefore
        }
    }
};
/* begin internal implementation details */

static inline clist clist_init(size_t elt_size){
    return (clist){
        .vtable = &dlist_vtable,
        .head = NULL,
        .size = 0,
        .elt_size = elt_size,
        .tail = NULL
    };

}

static inline void *clist_next_internal(clist *cont, void *node){
    if(node == cont->tail){
        return cont->head;
    }
    else{
        return slist_next((slist *)cont, node);
    }
}
static void *clist_next(void *cont, void *node){
    return clist_next_internal(cont, node);
}

static inline void *clist_prev_internal(clist *cont, void *node){
    if(node == cont->head){
        return cont->tail;
    }
    else{
        return dlist_prev(cont, node);
    }
}
static void *clist_prev(void *cont, void *node){
    return clist_prev_internal(cont, node);
}

static inline void clist_free(clist *cont){
    dlist_clear(cont);
}

#endif /* CLIST_H */

