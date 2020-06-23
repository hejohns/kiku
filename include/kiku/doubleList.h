// doubleList.h
#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <stddef.h>

#include <kiku/BidirectionalContainer.h>
#include <kiku/deque.h>

typedef struct doubleList{
    void *const vtable; //initialize to doubleList_vtable
    struct doubleList_node *head;
    struct doubleList_node *tail;
    size_t size;
    const size_t elt_size;
} doubleList;

/* forward declare internal functions called by type required interface */
static void *doubleList_begin(void *cont);
static void *doubleList_end(void *cont);
static void *doubleList_next(void *cont, void *node);
static size_t doubleList_size(void *cont);
static void doubleList_pushFront(void *cont, void *value);
static void doubleList_popFront(void *cont);
static void *doubleList_prev(void *cont, void *node);
static void *doubleList_tail(void *cont);
static void doubleList_pushBack(void *cont, void *value);
static void doubleList_popBack(void *cont);

struct doubleList_vtable{
    struct BidirectionalContainer BidirectionalContainer;
};
static struct doubleList_vtable doubleList_vtable{
    .BidirectionalContainer = {
        .DirectionalContainer = {
            .begin = doubleList_begin,
            .end = doublList_end,
            .next = doubleList_next,
            .size = doubleList_size,
            .pushFront = doubleList_pushFront,
            .popFront = doubleList_popFront
        },
        .prev = doubleList_prev,
        .tail = doubleList_tail,
        .pushBack = doubleList_pushBack,
        .popBack = doubleList_popBack
    }
};
/* begin internal implementation details */

/* imaginary node definition
 * -- note datum comes first for alignment
 *
struct doubleList_node{
    char datum[elt_size];
    void *prev;
    void *next;
};
*/

static inline doubleList doubleList_init(size_t elt_size){
    return (doubleList){
        .vtable = &doubleList_vtable,
        .head = NULL,
        .tail = NULL,
        .size = 0,
        .elt_size = elt_size
    }

}

static inline void *doubleList_next_internal(doubleList *cont, void *node){
    if(cont->elt_size % sizeof(void *)){
        return (char *)node + cont->elt_size - (cont->elt_size % sizeof(void *)) + 2*sizeof(void *);
    }
    else{
        return (char *)node + cont->elt_size + 2*sizeof(void *);
    }
}
static inline void *doubleList_next(void *cont, void *node){
    return doubleList_next_internal(cont, node);
}

static inline void *doubleList_prev_internal(doubleList *cont, void *node){
    if(cont->elt_size % sizeof(void *)){
        return (char *)node + cont->elt_size - (cont->elt_size % sizeof(void *)) + sizeof(void *);
    }
    else{
        return (char *)node + cont->elt_size + sizeof(void *);
    }
}
static inline void *doubleList_prev(void *cont, void *node){
    return doubleList_prev_internal(cont, node);
}

static inline void doubleList_free(doubleList *cont){
    void *tmp = cont->begin;
    while(tmp){
        void *tmp2 = doubleList_next(cont, tmp);
        free(tmp);
        tmp = tmp2;
    }
    cont->tail = NULL;
    cont->size = 0;
}

static void *doubleList_begin(void *cont){
    return ((doubleList *)cont)->head;
}

#endif /* DOUBLELIST_H */
