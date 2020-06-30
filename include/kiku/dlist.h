// dlist.h
#ifndef DLIST_H
#define DLIST_H

#include <assert.h>

#include <kiku/common.h>
#include <kiku/BidirectionalContainer.h>
#include <kiku/slist.h>

typedef struct dlist{
#define DLIST_STRUCT                                       \
    struct{ /* thus this anonymous struct should be identical to slist */\
        SLIST_STRUCT                                       \
    };                                                     \
    void *tail; /* tail at end to maintain compatibility with slist */
    DLIST_STRUCT
} dlist;

/* forward declare internal functions called by type required interface */
static void dlist_pushFront(void *cont, void *value);
static void dlist_popFront(void *cont);
static void dlist_insertAfter(void *cont, void *node, void *value);
static void dlist_eraseAfter(void *cont, void *node);
static void dlist_merge(void *cont, void *cont_other);
static void dlist_clear(void *cont);
static void *dlist_prev(void *cont, void *node);
static void *dlist_tail(void *cont);
static void dlist_pushBack(void *cont, void *value);
static void dlist_popBack(void *cont);
static void dlist_insertBefore(void *cont, void *node, void *value);
static void dlist_eraseBefore(void *cont, void *node);

struct dlist_vtable{
    struct BidirectionalContainer BidirectionalContainer;
};
static struct dlist_vtable dlist_vtable = {
    .BidirectionalContainer = {
        .DirectionalContainer = {
            .begin = slist_begin,
            .end = slist_end,
            .next = slist_next,
            .size = slist_size,
            .pushFront = dlist_pushFront,
            .popFront = dlist_popFront,
            .insertAfter = dlist_insertAfter,
            .eraseAfter = dlist_eraseAfter,
            .merge = dlist_merge,
            .clear = dlist_clear
        },
        .prev = dlist_prev,
        .tail = dlist_tail,
        .pushBack = dlist_pushBack,
        .popBack = dlist_popBack,
        .insertBefore = dlist_insertBefore,
        .eraseBefore = dlist_eraseBefore
    }
};
/* begin internal implementation details */

/* imaginary node definition
 * -- note datum comes first for alignment
 * and so node address == datum address
 * -- next is first to maintain compatibility
 * with slist
 *
struct dlist_node{
    char datum[elt_size];
    void *next;
    void *prev;
};
*/

static inline size_t dlist_node_size_internal(dlist *cont){
    return (cont->elt_size % sizeof(void *))?
        cont->elt_size - (cont->elt_size % sizeof(void *)) + 3*sizeof(void *)
        :
        cont->elt_size + 2*sizeof(void *);
}

static inline dlist dlist_init(size_t elt_size){
    return (dlist){
        .vtable = &dlist_vtable,
        .head = NULL,
        .size = 0,
        .elt_size = elt_size,
        .tail = NULL
    };

}

static inline void **dlist_prev_internal(dlist *cont, void *node){ //returns address of pointer to prev node
    if(cont->elt_size % sizeof(void *)){
        return (void **)((char *)node + cont->elt_size - (cont->elt_size % sizeof(void *)) + 2*sizeof(void *));
    }
    else{
        return (void **)((char *)node + cont->elt_size + sizeof(void *));
    }
}
static void *dlist_prev(void *cont, void *node){
    return *dlist_prev_internal(cont, node);
}

static void dlist_clear(void *cont){
    slist_clear(cont);
    ((dlist *)cont)->tail = NULL;
}

static inline void dlist_free(dlist *cont){
    dlist_clear(cont);
}

static inline void dlist_pushFront_internal(dlist *cont, void *value){
    void *new_node = kiku_malloc(dlist_node_size_internal(cont));
    memcpy(new_node, value, cont->elt_size);
    *slist_next_internal((slist *)cont, new_node) = cont->head;
    *dlist_prev_internal(cont, new_node) = NULL;
    if(cont->size){
        *dlist_prev_internal(cont, cont->head) = new_node;
    }
    else{
        cont->tail = new_node;
    }
    cont->head= new_node;
    cont->size++;
}
static void dlist_pushFront(void *cont, void *value){
    dlist_pushFront_internal(cont, value);
}

static inline void dlist_pushBack_internal(dlist *cont, void *value){
    void *new_node = kiku_malloc(dlist_node_size_internal(cont));
    memcpy(new_node, value, cont->elt_size);
    *slist_next_internal((slist *)cont, new_node) = NULL;
    *dlist_prev_internal(cont, new_node) = cont->tail;
    if(cont->size){
        *slist_next_internal((slist *)cont, cont->tail) = new_node;
    }
    else{
        cont->head = new_node;
    }
    cont->tail = new_node;
    cont->size++;
}
static void dlist_pushBack(void *cont, void *value){
    dlist_pushBack_internal(cont, value);
}

static inline void dlist_insertAfter_internal(dlist *cont, void *node, void *value){
    if(node){
        void *new_node = kiku_malloc(dlist_node_size_internal(cont));
        memcpy(new_node, value, cont->elt_size);
        void *node_after = slist_next((slist *)cont, node);
        *slist_next_internal((slist *)cont, node) = new_node;
        *slist_next_internal((slist *)cont, new_node) = node_after;
        *dlist_prev_internal(cont, new_node) = node;
        if(node_after){
            *dlist_prev_internal(cont, node_after) = new_node;
        }
        else{
            cont->tail = new_node;
        }
        cont->size++;
    }
    else{ //to allow insertAfter on begin on an empty list
        assert(cont->size == 0);
        dlist_pushFront(cont, value);
    }
}
static void dlist_insertAfter(void *cont, void *node, void *value){
    dlist_insertAfter_internal(cont, node, value);
}

static inline void dlist_insertBefore_internal(dlist *cont, void *node, void *value){
    if(node){
        void *new_node = kiku_malloc(dlist_node_size_internal(cont));
        memcpy(new_node, value, cont->elt_size);
        void *node_before = dlist_prev(cont, node);
        *dlist_prev_internal(cont, new_node) = node_before;
        *dlist_prev_internal(cont, node) = new_node;
        *slist_next_internal((slist *)cont, new_node) = node;
        if(node_before){
            *slist_next_internal((slist *)cont, node_before) = new_node;
        }
        else{
            cont->head = new_node;
        }
        cont->size++;
    }
    else{ //to act like stl's insert before end iterator
        dlist_pushBack(cont, value);
    }
}
static void dlist_insertBefore(void *cont, void *node, void *value){
    dlist_insertBefore_internal(cont, node, value);
}

static inline void dlist_popFront_internal(dlist *cont){
    assert(cont->size > 0);
    if(cont->size >= 2){
        dlist_eraseBefore(cont, slist_next((slist *)cont, cont->head));
    }
    else{
        dlist_clear(cont);
    }
}
static void dlist_popFront(void *cont){
    dlist_popFront_internal(cont);
}

static inline void dlist_popBack_internal(dlist *cont){
    assert(cont->size > 0);
    if(cont->size >= 2){
        dlist_eraseAfter(cont, dlist_prev(cont, cont->tail));
    }
    else{
        dlist_clear(cont);
    }
}
static void dlist_popBack(void *cont){
    dlist_popBack_internal(cont);
}

static inline void dlist_eraseAfter_internal(dlist *cont, void *node){
    assert(cont->size > 0);
    assert(node);
    void *node_after = slist_next((slist *)cont, node);
    assert(node_after);
    void *node_after_after = slist_next((slist *)cont, node_after);
    *slist_next_internal((slist *)cont, node) = node_after_after;
    if(node_after_after){
        *dlist_prev_internal(cont, node_after_after) = node;
    }
    else{
        cont->tail = node;
    }
    free(node_after);
    cont->size--;
}
static void dlist_eraseAfter(void *cont, void *node){
    dlist_eraseAfter_internal(cont, node);
}

static inline void dlist_eraseBefore_internal(dlist *cont, void *node){
    assert(cont->size > 0);
    if(node){
        void *node_before = dlist_prev(cont, node);
        assert(node_before);
        void *node_before_before = dlist_prev(cont, node_before);
        *dlist_prev_internal(cont, node) = node_before_before;
        if(node_before_before){
            *slist_next_internal((slist *)cont, node_before_before) = node;
        }
        else{
            cont->head = node;
        }
        free(node_before);
        cont->size--;
    }
    else{ //act as erase before end, i.e. erase tail
        dlist_popBack(cont);
    }
}
static void dlist_eraseBefore(void *cont, void *node){
    dlist_eraseBefore_internal(cont, node);
}

static void *dlist_tail(void *cont){
    return ((dlist *)cont)->tail;
}

static inline void dlist_merge_internal(dlist *cont, dlist *cont_other){
    assert(cont->elt_size == cont_other->elt_size); //strange bugs will silently occur otherwise
    *slist_next_internal((slist *)cont, cont->tail) = cont_other->head;
    if(cont_other->head){
        *dlist_prev_internal(cont_other, cont_other->head) = cont->tail;
    }
    cont->tail = cont_other->tail;
    cont->size += cont_other->size;
    cont_other->head = NULL;
    cont_other->tail = NULL;
    cont_other->size = 0;
}
static void dlist_merge(void *cont, void *cont_other){
    dlist_merge_internal(cont, cont_other);
}

#endif /* DLIST_H */
