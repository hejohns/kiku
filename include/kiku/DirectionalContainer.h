// DirectionalContainer.h
#ifndef DIRECTIONALCONTAINER_H
#define DIRECTIONALCONTAINER_H

#include <stddef.h>

struct DirectionalContainer{
    void *(*const begin)(void *);
    void *(*const end)(void *);
    void *(*const next)(void *, void *);
    size_t (*const size)(void *);
    void (*const pushFront)(void *, void *);
    void (*const popFront)(void *);
    void (*const insertAfter)(void *, void *, void *);
    void (*const eraseAfter)(void *, void *);
    void (*const merge)(void *, void *);
    void (*const clear)(void *);
};

static inline void *DirectionalContainer_begin(void *cont){
    return (*(struct DirectionalContainer **)cont)->begin(cont);
}
static inline void *DirectionalContainer_end(void *cont){
    return (*(struct DirectionalContainer **)cont)->end(cont);
}
static inline void *DirectionalContainer_next(void *cont, void *node){
    return (*(struct DirectionalContainer **)cont)->next(cont, node);
}
static inline size_t DirectionalContainer_size(void *cont){
    return (*(struct DirectionalContainer **)cont)->size(cont);
}
static inline void DirectionalContainer_pushFront(void *cont, void *value){
    (*(struct DirectionalContainer **)cont)->pushFront(cont, value);
}
static inline void DirectionalContainer_popFront(void *cont){
    (*(struct DirectionalContainer **)cont)->popFront(cont);
}
static inline void DirectionalContainer_insertAfter(void *cont, void *node, void *value){
    (*(struct DirectionalContainer **)cont)->insertAfter(cont, node, value);
}
static inline void DirectionalContainer_eraseAfter(void *cont, void *node){
    (*(struct DirectionalContainer **)cont)->eraseAfter(cont, node);
}
static inline void DirectionalContainer_merge(void *cont, void *cont_other){
    (*(struct DirectionalContainer **)cont)->merge(cont, cont_other);
}
static inline void DirectionalContainer_clear(void *cont){
    (*(struct DirectionalContainer **)cont)->clear(cont);
}

#endif /* DIRECTIONALCONTAINER_H */
