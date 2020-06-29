// doubleList.h
#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <assert.h>

#include <kiku/common.h>
#include <kiku/BidirectionalContainer.h>
#include <kiku/singleList.h>

typedef struct doubleList{
    void *const vtable; //initialize to doubleList_vtable
    void *head;
    void *tail;
    size_t size;
    const size_t elt_size;
} doubleList;

/* forward declare internal functions called by type required interface */
static void doubleList_pushFront(void *cont, void *value);
static void doubleList_popFront(void *cont);
static void doubleList_insertAfter(void *cont, void *node, void *value);
static void doubleList_eraseAfter(void *cont, void *node);
static void doubleList_merge(void *cont, void *cont_other);
static void doubleList_clear(void *cont);
static void *doubleList_prev(void *cont, void *node);
static void *doubleList_tail(void *cont);
static void doubleList_pushBack(void *cont, void *value);
static void doubleList_popBack(void *cont);
static void doubleList_insertBefore(void *cont, void *node, void *value);
static void doubleList_eraseBefore(void *cont, void *node);

struct doubleList_vtable{
    struct BidirectionalContainer BidirectionalContainer;
};
static struct doubleList_vtable doubleList_vtable = {
    .BidirectionalContainer = {
        .DirectionalContainer = {
            .begin = singleList_begin,
            .end = singleList_end,
            .next = singleList_next,
            .size = singleList_size,
            .pushFront = doubleList_pushFront,
            .popFront = doubleList_popFront,
            .insertAfter = doubleList_insertAfter,
            .eraseAfter = doubleList_eraseAfter,
            .merge = doubleList_merge,
            .clear = doubleList_clear
        },
        .prev = doubleList_prev,
        .tail = doubleList_tail,
        .pushBack = doubleList_pushBack,
        .popBack = doubleList_popBack,
        .insertBefore = doubleList_insertBefore,
        .eraseBefore = doubleList_eraseBefore
    }
};
/* begin internal implementation details */

/* imaginary node definition
 * -- note datum comes first for alignment
 * and so node address == datum address
 * -- next is first to maintain compatibility
 * with singleList
 *
struct doubleList_node{
    char datum[elt_size];
    void *next;
    void *prev;
};
*/

static inline size_t doubleList_node_size_internal(doubleList *cont){ 
    return (cont->elt_size % sizeof(void *))? 
        cont->elt_size - (cont->elt_size % sizeof(void *)) + 3*sizeof(void *)
        :
        cont->elt_size + 2*sizeof(void *);
}

static inline doubleList doubleList_init(size_t elt_size){
    return (doubleList){
        .vtable = &doubleList_vtable,
        .head = NULL,
        .tail = NULL,
        .size = 0,
        .elt_size = elt_size
    };

}

static inline void **doubleList_prev_internal(doubleList *cont, void *node){ //returns address of pointer to prev node
    if(cont->elt_size % sizeof(void *)){
        return (void **)((char *)node + cont->elt_size - (cont->elt_size % sizeof(void *)) + 2*sizeof(void *));
    }
    else{
        return (void **)((char *)node + cont->elt_size + sizeof(void *));
    }
}
static void *doubleList_prev(void *cont, void *node){
    return *doubleList_prev_internal(cont, node);
}

static void doubleList_clear(void *cont){
    singleList_clear(cont);
    ((doubleList *)cont)->tail = NULL;
}

static inline void doubleList_free(doubleList *cont){
    doubleList_clear(cont);
}

static inline void doubleList_insertAfter_internal(doubleList *cont, void *node, void *value){
    if(node){
        void *new_node = kiku_malloc(doubleList_node_size_internal(cont));
        memcpy(new_node, value, cont->elt_size);
        *doubleList_prev_internal(cont, new_node) = node;
        void *node_after = singleList_next(cont, node);
        *singleList_next_internal(cont, new_node) = node_after;
        *singleList_next_internal(cont, node) = new_node;
        if(node_after){
            *doubleList_prev_internal(cont, node_after) = new_node;
        }
        else{
            cont->tail = new_node;
        }
        cont->size++;
    }
    else{ //to allow insertAfter on begin on an empty list
        assert(cont->size == 0);
        void *new_node = kiku_malloc(doubleList_node_size_internal(cont));
        memcpy(new_node, value, cont->elt_size);
        *doubleList_prev_internal(cont, new_node) = NULL;
        *singleList_next_internal(cont, new_node) = NULL;
        cont->begin = new_node;
        cont->tail = new_node;
        cont->size++;
    }
}
static void doubleList_insertAfter(void *cont, void *node, void *value){
    doubleList_insertAfter_internal(cont, node, value);
}

static inline void doubleList_insertBefore_internal(doubleList *cont, void *node, void *value){
    if(node){
        void *new_node = kiku_malloc(doubleList_node_size_internal(cont));
        memcpy(new_node, value, cont->elt_size);
        *singleList_next_internal(cont, new_node) = node;
        void *node_before = doubleList_prev(cont, node);
        *doubleList_prev_internal(cont, new_node) = node_before;
        *doubleList_prev_internal(cont, node) = new_node;
        if(node_before){
            *singleList_next_internal(cont, node_before) = new_node;
        }
        else{
            cont->head = new_node;
        }
        cont->size++;
    }
    else{ //to act like stl's insert before end iterator
        doubleList_insertAfter(cont, cont->tail, value);
    }
}
static void doubleList_insertBefore(void *cont, void *node, void *value){
    doubleList_insertBefore_internal(cont, node, value);
}

static inline void doubleList_eraseAfter_internal(doubleList *cont, void *node){
    assert(cont->size > 0);
    assert(node);
    void *node_after = singleList_next(cont, node);
    assert(node_after);
    void *node_after_after = singleList_next(cont, node_after);
    *singleList_next_internal(cont, node) = node_after_after;
    if(node_after_after){
        *doubleList_prev_internal(cont, node_after_after) = node;
    }
    else{
        cont->tail = node;
    }
    free(node_after);
    cont->size--;
}
static void doubleList_eraseAfter(void *cont, void *node){
    doubleList_eraseAfter_internal(cont, node);
}

static inline void doubleList_eraseBefore_internal(doubleList *cont, void *node){
    assert(cont->size > 0);
    if(node){
        void *node_before = doubleList_prev(cont, node);
        assert(node_before);
        void *node_before_before = doubleList_prev(cont, node_before);
        *doubleList_prev_internal(cont, node) = node_before_before;
        if(!node_before_before){
            cont->head = node;
        }
        free(node_before);
    }
    else{ //act as erase end, i.e. erase tail
        void *node_before = doubleList_prev(cont->tail);
        if(node_before){
            free(cont->tail);
            *singleList_next_internal(cont, node_before) = NULL;
            cont->tail = node_before;
        }
        else{
            assert(cont->size == 1);
            doubleList_clear(cont);
            return;
        }
    }
    cont->size--;
}
static void doubleList_eraseBefore(void *cont, void *node){
    doubleList_eraseBefore_internal(cont, node);
}

static void doubleList_pushFront(void *cont, void *value){
    doubleList_insertBefore(cont, ((doubleList *)cont)->head, value);
}

static void doubleList_popFront(void *cont){
    doubleList_eraseBefore(cont, singleList_next(cont, ((doubleList *)cont)->head));
}

static void *doubleList_tail(void *cont){
    return ((doubleList *)cont)->tail;
}

static void doubleList_pushBack(void *cont, void *value){
    doubleList_insertBefore(cont, doubleList_end(cont), value);
}

static void doubleList_popBack(void *cont){
    doubleList_eraseBefore(cont, doubleList_end(cont));
}

static inline void doubleList_merge_internal(doubleList *cont, doubleList *cont_other){
    *singleList_next_internal(cont, cont->tail) = cont_other->head;
    cont->tail = cont_other->tail;
    cont->size += cont_other->size;
    cont_other->head = NULL;
    cont_other->tail = NULL;
    cont_other->size = 0;
}
static void doubleList_merge(void *cont, void *cont_other){
    doubleList_merge_internal(cont, cont_other);
}

#endif /* DOUBLELIST_H */
