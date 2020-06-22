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

static inline void vector_free(vector *cont){
    free(cont->arr);
    cont->arr = NULL;
    cont->size = 0;
    cont->capacity = 9;
}

#endif /* VECTOR_H */
