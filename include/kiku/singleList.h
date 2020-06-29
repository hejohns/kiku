// singleList.h
#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <stdlib.h>
#include <assert.h>

#include <kiku/DirectionalContainer.h>
#include <kiku/common.h>

typedef struct singleList{
    void *const vtable; //initialize to singleList_vtable
    void *head;
    void *tail;
    size_t size;
    const size_t elt_size;
} singleList;

/* forward declare internal functions called by type required interface */
static void *singleList_begin(void *cont);
static void *singleList_end(void *cont);
static void *singleList_next(void *cont, void *node);
static size_t singleList_size(void *cont);
static void singleList_pushFront(void *cont, void *value);
static void singleList_popFront(void *cont);
static void singleList_insertAfter(void *cont, void *node, void *value);
static void singleList_eraseAfter(void *cont, void *node);
static void singleList_merge(void *cont, void *cont_other);
static void singleList_clear(void *cont);

struct singleList_vtable{
    struct DirectionalContainer DirectionalContainer;
};
static struct singleList_vtable singleList_vtable = {
    .DirectionalContainer = {
        .begin = singleList_begin,
        .end = singleList_end,
        .next = singleList_next,
        .size = singleList_size,
        .pushFront = singleList_pushFront,
        .popFront = singleList_popFront,
        .insertAfter = singleList_insertAfter,
        .eraseAfter = singleList_eraseAfter,
        .merge = singleList_merge,
        .clear = singleList_clear
    }
};
/* begin internal implementation details */

/* imaginary node definition
 * -- note datum comes first for alignment
 * and so node address == datum address
 *
struct singleList_node{
    char datum[elt_size];
    void *next;
};
*/

static inline size_t singleList_node_size_internal(singleList *cont){ 
    return (cont->elt_size % sizeof(void *))? 
        cont->elt_size - (cont->elt_size % sizeof(void *)) + 2*sizeof(void *)
        :
        cont->elt_size + sizeof(void *);
}

static inline singleList singleList_init(size_t elt_size){
    return (singleList){
        .vtable = &singleList_vtable,
        .head = NULL,
        .tail = NULL,
        .size = 0,
        .elt_size = elt_size
    };

}

static inline void **singleList_next_internal(singleList *cont, void *node){ //returns address of pointer to next node
    if(cont->elt_size % sizeof(void *)){
        return (void **)((char *)node + cont->elt_size - (cont->elt_size % sizeof(void *)) + sizeof(void *));
    }
    else{
        return (void **)((char *)node + cont->elt_size);
    }
}
static void *singleList_next(void *cont, void *node){
    return *singleList_next_internal(cont, node);
}

static inline void singleList_clear_internal(singleList *cont){
    for(void *tmp = cont->head, *after_tmp; tmp && tmp != cont->head; tmp = after_tmp){
        *after_tmp = singleList_next(cont, tmp);
        free(tmp);
    }
    cont->head = NULL;
    cont->tail = NULL;
    cont->size = 0;
}
static void singleList_clear(void *cont){
    singleList_clear_internal(cont);
}

static inline void singleList_free(singleList *cont){
    singleList_clear(cont);
}

static void *singleList_begin(void *cont){
    return ((singleList *)cont)->head;
}

static void *singleList_end(void *cont){
    (void)cont;
    return NULL;
}

static size_t singleList_size(void *cont){
    return ((singleList *)cont)->size;
}

static inline void singleList_insertAfter_internal(singleList *cont, void *node, void *value){
    if(node){
        void *new_node = kiku_malloc(singleList_node_size_internal(cont));
        memcpy(new_node, value, cont->elt_size);
        *singleList_prev_internal(cont, new_node) = node;
        void *node_after = singleList_next(cont, node);
        *singleList_next_internal(cont, new_node) = node_after;
        *singleList_next_internal(cont, node) = new_node;
        if(node_after){
            *singleList_prev_internal(cont, node_after) = new_node;
        }
        else{
            cont->tail = new_node;
        }
        cont->size++;
    }
    else{ //to allow insertAfter on begin on an empty list
        assert(cont->size == 0);
        void *new_node = kiku_malloc(singleList_node_size_internal(cont));
        memcpy(new_node, value, cont->elt_size);
        *singleList_prev_internal(cont, new_node) = NULL;
        *singleList_next_internal(cont, new_node) = NULL;
        cont->begin = new_node;
        cont->tail = new_node;
        cont->size++;
    }
}
static void singleList_insertAfter(void *cont, void *node, void *value){
    singleList_insertAfter_internal(cont, node, value);
}

static inline void singleList_insertBefore_internal(singleList *cont, void *node, void *value){
    if(node){
        void *new_node = kiku_malloc(singleList_node_size_internal(cont));
        memcpy(new_node, value, cont->elt_size);
        *singleList_next_internal(cont, new_node) = node;
        void *node_before = singleList_prev(cont, node);
        *singleList_prev_internal(cont, new_node) = node_before;
        *singleList_prev_internal(cont, node) = new_node;
        if(node_before){
            *singleList_next_internal(cont, node_before) = new_node;
        }
        else{
            cont->head = new_node;
        }
        cont->size++;
    }
    else{ //to act like stl's insert before end iterator
        singleList_insertAfter(cont, cont->tail, value);
    }
}
static void singleList_insertBefore(void *cont, void *node, void *value){
    singleList_insertBefore_internal(cont, node, value);
}

static inline void singleList_eraseAfter_internal(singleList *cont, void *node){
    assert(cont->size > 0);
    assert(node);
    void *node_after = singleList_next(cont, node);
    assert(node_after);
    void *node_after_after = singleList_next(cont, node_after);
    *singleList_next_internal(cont, node) = node_after_after;
    if(node_after_after){
        *singleList_prev_internal(cont, node_after_after) = node;
    }
    else{
        cont->tail = node;
    }
    free(node_after);
    cont->size--;
}
static void singleList_eraseAfter(void *cont, void *node){
    singleList_eraseAfter_internal(cont, node);
}

static inline void singleList_eraseBefore_internal(singleList *cont, void *node){
    assert(cont->size > 0);
    if(node){
        void *node_before = singleList_prev(cont, node);
        assert(node_before);
        void *node_before_before = singleList_prev(cont, node_before);
        *singleList_prev_internal(cont, node) = node_before_before;
        if(!node_before_before){
            cont->head = node;
        }
        free(node_before);
    }
    else{ //act as erase end, i.e. erase tail
        void *node_before = singleList_prev(cont->tail);
        if(node_before){
            free(cont->tail);
            *singleList_next_internal(cont, node_before) = NULL;
            cont->tail = node_before;
        }
        else{
            assert(cont->size == 1);
            singleList_clear(cont);
            return;
        }
    }
    cont->size--;
}
static void singleList_eraseBefore(void *cont, void *node){
    singleList_eraseBefore_internal(cont, node);
}

static void singleList_pushFront(void *cont, void *value){
    singleList_insertBefore(cont, ((singleList *)cont)->head, value);
}

static void singleList_popFront(void *cont){
    singleList_eraseBefore(cont, singleList_next(cont, ((singleList *)cont)->head));
}

static void *singleList_tail(void *cont){
    return ((singleList *)cont)->tail;
}

static void singleList_pushBack(void *cont, void *value){
    singleList_insertBefore(cont, singleList_end(cont), value);
}

static void singleList_popBack(void *cont){
    singleList_eraseBefore(cont, singleList_end(cont));
}

static inline void singleList_merge_internal(singleList *cont, singleList *cont_other){
    *singleList_next_internal(cont, cont->tail) = cont_other->head;
    cont->tail = cont_other->tail;
    cont->size += cont_other->size;
    cont_other->head = NULL;
    cont_other->tail = NULL;
    cont_other->size = 0;
}
static void singleList_merge(void *cont, void *cont_other){
    singleList_merge_internal(cont, cont_other);
}

#endif /* SINGLELIST_H */

