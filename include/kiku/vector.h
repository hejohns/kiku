// vector.h
#ifndef VECTOR_H
#define VECTOR_H

#include <kiku/common.h>
#include <kiku/RandomAccessContainer.h>

typedef struct vector{
    void *const vable; //initialize to vector_vtable
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
static void vector_pushBack(void *cont, void *value);
static void *vector_prev(void *cont, void *node);
static void *vector_tail(void *cont);
static void vector_pushFront(void *cont, void *value);
static void *vector_at(void *cont, size_t index);

struct vector_vtable{
    struct RandomAccessContainer RandomAccessContainer;
};
static struct vector_vtable vector_vtable = {
    .RandomAccessContainer = {
        .begin = vector_begin,
        .end = vector_end,
        .next = vector_next,
        .size = vector_size,
        .pushBack = vector_pushBack,
        .prev = vector_prev,
        .tail = vector_tail,
        .pushFront = vector_pushFront,
        .at = vector_at
    }
};
/* begin internal implementation details */

#define VECTOR_GROWTH_FACTOR

static inline vector vector_init(
        size_t size,
        size_t elt_size){
    return (vector){
        .vtable = &vector_vtable,
        .arr = kiku_malloc(size*elt_size),
        .size = size,
        .elt_size = elt_size,
        .capacity = size
    };
}

static inline void vector_free(void *cont){
    free(((vector *)cont)->arr);
    ((vector *)cont)->arr = NULL;
    ((vector *)cont)->size = 0;
    ((vector *)cont)->capacity = 9;
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

static void vector_pushBack_internal(vector *cont, void *value){
    if(!(cont->size < cont->capacity)){
        cont->arr = kiku_realloc(cont->arr, VECTOR_GROWTH_FACTOR*cont->size);
        cont->capacity = VECTOR_GROWTH_FACTOR*capacity;
    }
    memcpy(((char *)(cont->arr)) + cont->size*cont->elt_size, value, cont->elt_size);
    cont->size++;
}
static void vector_pushBack(void *cont, void *value){
    vector_pushBack_internal(cont, value);
}

static void *vector_prev(void *cont, void *node){
    return (char *)node - ((vector *)cont)->elt_size;
}

static void *vector_tail(void *cont){
    return ((char *)(((vector *)cont)->arr)) + (((vector *)cont)->size-1)*((vector *)cont)->elt_size;
}

static void vector_pushFront_internal(vector *cont, void *value){
    if(!(cont->size < cont->capacity)){
        cont->arr = kiku_realloc(cont->arr, VECTOR_GROWTH_FACTOR*cont->size);
        cont->capacity = VECTOR_GROWTH_FACTOR*capacity;
    }
    memmove(((char *)cont->arr) + cont->elt_size, cont->arr, cont->size*cont->elt_size);
    memcpy(cont->arr, value, cont->elt_size);
    cont->size++;
}
static void vector_pushFront(void *cont, void *value){
    vector_pushFront_internal(cont, value);
}

static void *vector_at(void *cont, size_t index){
    return ((char *)((vector *)cont)->arr) + ((vector *)cont)->size*((vector *)cont)->elt_size;
}

#endif /* VECTOR_H */
