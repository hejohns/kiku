// slist.h
#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <assert.h>

#include <kiku/common.h>
#include <kiku/DirectionalContainer.h>

typedef struct slist{
    void *const vtable; //initialize to slist_vtable
    void *head;
    void *tail;
    size_t size;
    const size_t elt_size;
} slist;

/* forward declare internal functions called by type required interface */
static void *slist_begin(void *cont);
static void *slist_end(void *cont);
static void *slist_next(void *cont, void *node);
static size_t slist_size(void *cont);
static void slist_pushFront(void *cont, void *value);
static void slist_popFront(void *cont);
static void slist_insertAfter(void *cont, void *node, void *value);
static void slist_eraseAfter(void *cont, void *node);
static void slist_merge(void *cont, void *cont_other);
static void slist_clear(void *cont);

struct slist_vtable{
    struct DirectionalContainer DirectionalContainer;
};
static struct slist_vtable slist_vtable = {
    .DirectionalContainer = {
        .begin = slist_begin,
        .end = slist_end,
        .next = slist_next,
        .size = slist_size,
        .pushFront = slist_pushFront,
        .popFront = slist_popFront,
        .insertAfter = slist_insertAfter,
        .eraseAfter = slist_eraseAfter,
        .merge = slist_merge,
        .clear = slist_clear
    }
};
/* begin internal implementation details */

/* imaginary node definition
 * -- note datum comes first for alignment
 * and so node address == datum address
 *
struct slist_node{
    char datum[elt_size];
    void *next;
};
*/

static inline size_t slist_node_size_internal(slist *cont){ 
    return (cont->elt_size % sizeof(void *))? 
        cont->elt_size - (cont->elt_size % sizeof(void *)) + 2*sizeof(void *)
        :
        cont->elt_size + sizeof(void *);
}

static inline slist slist_init(size_t elt_size){
    return (slist){
        .vtable = &slist_vtable,
        .head = NULL,
        .tail = NULL,
        .size = 0,
        .elt_size = elt_size
    };

}

static inline void **slist_next_internal(slist *cont, void *node){ //returns address of pointer to next node
    if(cont->elt_size % sizeof(void *)){
        return (void **)((char *)node + cont->elt_size - (cont->elt_size % sizeof(void *)) + sizeof(void *));
    }
    else{
        return (void **)((char *)node + cont->elt_size);
    }
}
static void *slist_next(void *cont, void *node){
    return *slist_next_internal(cont, node);
}

static inline void slist_clear_internal(slist *cont){
    for(void *tmp = cont->head, *after_tmp; tmp; tmp = after_tmp){
        after_tmp = slist_next(cont, tmp);
        free(tmp);
    }
    cont->head = NULL;
    cont->size = 0;
}
static void slist_clear(void *cont){
    slist_clear_internal(cont);
}

static inline void slist_free(slist *cont){
    slist_clear(cont);
}

static void *slist_begin(void *cont){
    return ((slist *)cont)->head;
}

static void *slist_end(void *cont){
    (void)cont;
    return NULL;
}

static size_t slist_size(void *cont){
    return ((slist *)cont)->size;
}

static inline void slist_insertAfter_internal(slist *cont, void *node, void *value){
    if(node){
        void *new_node = kiku_malloc(slist_node_size_internal(cont));
        memcpy(new_node, value, cont->elt_size);
        void *node_after = slist_next(cont, node);
        *slist_next_internal(cont, node) = new_node;
        *slist_next_internal(cont, new_node) = node_after;
    }
    else{ //to allow insertAfter on begin on an empty list
        assert(cont->size == 0);
        void *new_node = kiku_malloc(slist_node_size_internal(cont));
        memcpy(new_node, value, cont->elt_size);
        *slist_next_internal(cont, new_node) = NULL;
        cont->head = new_node;
    }
    cont->size++;
}
static void slist_insertAfter(void *cont, void *node, void *value){
    slist_insertAfter_internal(cont, node, value);
}

static inline void slist_eraseAfter_internal(slist *cont, void *node){
    assert(cont->size > 0 && node);
    void *node_after = slist_next(cont, node);
    assert(node_after);
    void *node_after_after = slist_next(cont, node_after);
    *slist_next_internal(cont, node) = node_after_after;
    free(node_after);
    cont->size--;
}
static void slist_eraseAfter(void *cont, void *node){
    slist_eraseAfter_internal(cont, node);
}

static void slist_pushFront_internal(slist *cont, void *value){
    void *new_node = kiku_malloc(slist_node_size_internal(cont));
    memcpy(new_node, value, cont->elt_size);
    *slist_next_internal(cont, new_node) = cont->head;
    cont->head = new_node;
    cont->size++;
}
static void slist_pushFront(void *cont, void *value){
    slist_pushFront_internal(cont, value);
}

static void slist_popFront_internal(slist *cont){
    assert(cont->size > 0);
    void *node_after = slist_next(cont, cont->head);
    free(cont->head);
    cont->head = node_after;
    cont->size--;
}
static void slist_popFront(void *cont){
    slist_popFront_internal(cont);
}

static inline void slist_merge_internal(slist *cont, slist *cont_other){
    void *cont_tail;
    for(cont_tail = cont->head;
            slist_next(cont, cont_tail);
            cont_tail = slist_next(cont, cont_tail)){
    }
    *slist_next_internal(cont, cont_tail) = cont_other->head;
    cont->size += cont_other->size;
    cont_other->head = NULL;
    cont_other->size = 0;
}
static void slist_merge(void *cont, void *cont_other){
    slist_merge_internal(cont, cont_other);
}

#endif /* SINGLELIST_H */

