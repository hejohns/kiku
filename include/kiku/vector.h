// vector.h
#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>

#include <kiku/common.h>
#include <kiku/RandomAccessContainer.h>

typedef struct vector{
    void *const vtable; //initialize to vector_vtable
    void *arr;
    size_t size;
    const size_t elt_size;
    size_t capacity;
} vector;

/* forward declare internal functions called by type required interface */
static void *vector_begin(void *cont);
static void *vector_end(void *cont);
static void *vector_next(void *cont, void *node);
static size_t vector_size(void *cont);
static void vector_pushFront(void *cont, void *value);
static void vector_popFront(void *cont);
static void vector_insertAfter(void *cont, void *node, void *value);
static void vector_eraseAfter(void *cont, void *node);
static void vector_merge(void *cont, void* cont_other);
static void vector_clear(void *cont);
static void *vector_prev(void *cont, void *node);
static void *vector_tail(void *cont);
static void vector_pushBack(void *cont, void *value);
static void vector_popBack(void *cont);
static void vector_insertBefore(void *cont, void *node, void *value);
static void vector_eraseBefore(void *cont, void *node);
static void *vector_at(void *cont, size_t index);

struct vector_vtable{
    struct RandomAccessContainer RandomAccessContainer;
};
static struct vector_vtable vector_vtable = {
    .RandomAccessContainer = {
        .BidirectionalContainer = {
            .DirectionalContainer = {
                .begin = vector_begin,
                .end = vector_end,
                .next = vector_next,
                .size = vector_size,
                .pushFront = vector_pushFront,
                .popFront = vector_popFront,
                .insertAfter = vector_insertAfter,
                .eraseAfter = vector_eraseAfter,
                .merge = vector_merge,
                .clear = vector_clear
            },
            .prev = vector_prev,
            .tail = vector_tail,
            .pushBack = vector_pushBack,
            .popBack = vector_popBack,
            .insertBefore = vector_insertBefore,
            .eraseBefore = vector_eraseBefore
        },
        .at = vector_at
    }
};
/* begin internal implementation details */

#define VECTOR_GROWTH_FACTOR 2
#define VECTOR_DEFAULT_CAPACITY 16

static inline vector vector_init(
        size_t initial_capacity,
        size_t elt_size){
    return (vector){
        .vtable = &vector_vtable,
        .arr = kiku_malloc(initial_capacity*elt_size),
        .size = 0,
        .elt_size = elt_size,
        .capacity = initial_capacity
    };
}

static inline void vector_free(vector *cont){
    free(cont->arr);
    cont->arr = NULL;
    cont->size = 0;
    cont->capacity = 0;
}

static void vector_clear(void *cont){
    vector_free(cont);
}

static void *vector_begin(void *cont){
    return ((vector *)cont)->arr;
}

static void *vector_end(void *cont){
    return (char *)((vector *)cont)->arr + ((vector *)cont)->size*((vector *)cont)->elt_size;
}

static void *vector_next(void *cont, void *node){
    return (char *)node + ((vector *)cont)->elt_size;
}

static size_t vector_size(void *cont){
    return ((vector *)cont)->size;
}

static inline void vector_grow_internal(vector *cont){
    if(cont->size){
        cont->arr = kiku_realloc(cont->arr, VECTOR_GROWTH_FACTOR*cont->size*cont->elt_size);
        cont->capacity = VECTOR_GROWTH_FACTOR*cont->size;
    }
    else{
        cont->arr = kiku_realloc(cont->arr, VECTOR_DEFAULT_CAPACITY*cont->elt_size);
        cont->capacity = VECTOR_DEFAULT_CAPACITY;
    }
}

static inline void vector_pushFront_internal(vector *cont, void *value){
    if(!(cont->size < cont->capacity)){
        vector_grow_internal(cont);
    }
    memmove((char *)vector_begin(cont) + cont->elt_size, vector_begin(cont), cont->size*cont->elt_size);
    memcpy(vector_begin(cont), value, cont->elt_size);
    cont->size++;
}
static void vector_pushFront(void *cont, void *value){
    vector_pushFront_internal(cont, value);
}

static inline void vector_popFront_internal(vector *cont){
    assert(cont->size);
    memmove(vector_begin(cont), (char *)vector_begin(cont) + cont->elt_size, (cont->size-1)*cont->elt_size);
    cont->size--;
}
static void vector_popFront(void *cont){
    vector_popFront_internal(cont);
}

static inline void vector_insertAfter_internal(vector *cont, char *node, void *value){
    assert(vector_begin(cont) <= (void *)node && node + cont->elt_size <= (char *)vector_end(cont));
    assert(!(((char *)vector_end(cont) - node) % cont->elt_size));
    if(!(cont->size < cont->capacity)){
        vector_grow_internal(cont);
    }
    memmove(node + 2*cont->elt_size, node + cont->elt_size, (char *)vector_end(cont) - node);
    memcpy(node + cont->elt_size, value, cont->elt_size);
    cont->size++;
}
static void vector_insertAfter(void *cont, void *node, void *value){
    vector_insertAfter_internal(cont, node, value);
}

static inline void vector_eraseAfter_internal(vector *cont, char *node){
    assert(cont->size);
    assert(vector_begin(cont) <= (void *)node && node + cont->elt_size <= (char *)vector_end(cont));
    assert(!(((char *)vector_end(cont) - node) % cont->elt_size));
    memmove(node + cont->elt_size, node + 2*cont->elt_size, (char *)vector_end(cont) - (node + 2*cont->elt_size));
    cont->size--;
}
static void vector_eraseAfter(void *cont, void *node){
    vector_eraseAfter_internal(cont, node);
}

static inline void vector_merge_internal(vector *cont, vector *cont_other){
    assert(cont->elt_size == cont_other->elt_size);
    if(!(cont->size + cont_other->size < cont->capacity)){
        cont->arr = kiku_realloc(cont->arr, (cont->size + cont_other->size)*cont->elt_size);
        cont->capacity = cont->size + cont_other->size;
    }
    memcpy(vector_end(cont), vector_begin(cont_other), cont_other->size);
    cont->size += cont_other->size;
    vector_clear(cont_other);
}
static void vector_merge(void *cont, void *cont_other){
    vector_merge_internal(cont, cont_other);
}

static void *vector_prev(void *cont, void *node){
    return (char *)node - ((vector *)cont)->elt_size;
}

static void *vector_tail(void *cont){
    if(((vector *)cont)->size){
        return vector_prev(cont, vector_end(cont));
    }
    else{
        return vector_begin(cont);
    }
}

static inline void vector_pushBack_internal(vector *cont, void *value){
    if(!(cont->size < cont->capacity)){
        vector_grow_internal(cont);
    }
    memcpy(vector_end(cont), value, cont->elt_size);
    cont->size++;
}
static void vector_pushBack(void *cont, void *value){
    vector_pushBack_internal(cont, value);
}

static void vector_popBack(void *cont){
    assert(cont->size);
    ((vector *)cont)->size--;
}

static inline void vector_insertBefore_internal(vector *cont, char *node, void *value){
    if(!(cont->size < cont->capacity)){
        vector_grow_internal(cont);
    }
    assert(!(((char *)vector_end(cont) - node) % cont->elt_size));
    memmove(node + cont->elt_size, node, (char *)vector_end(cont) - node);
    memcpy(node, value, cont->elt_size);
    cont->size++;
}
static void vector_insertBefore(void *cont, void *node, void *value){
    assert(vector_begin(cont) <= node && node <= vector_end(cont));
    vector_insertBefore_internal(cont, node, value);
}

static inline void vector_eraseBefore_internal(vector *cont, char *node){
    assert(cont->size);
    assert((char *)vector_begin(cont) + cont->elt_size <= node && (void *)node <= vector_end(cont));
    assert(!(((char *)vector_end(cont) - node) % cont->elt_size));
    memmove(node - cont->elt_size, node, (char *)vector_end(cont) - node);
    cont->size--;
}
static void vector_eraseBefore(void *cont, void *node){
    vector_eraseBefore_internal(cont, node);
}

static void *vector_at(void *cont, size_t index){
    return (char *)((vector *)cont)->arr + index*((vector *)cont)->elt_size;
}

#undef VECTOR_GROWTH_FACTOR
#undef VECTOR_DEFAULT_CAPACITY

#endif /* VECTOR_H */
