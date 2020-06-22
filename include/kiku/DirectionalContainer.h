// DirectionalContainer.h
#ifndef DIRECTIONALCONTAINER_H
#define DIRECTIONALCONTAINER_H

struct DirectionalContainer{
    void *(*const begin)(void *);
    void *(*const end)(void *);
    void *(*const next)(void *, void *);
    size_t (*const size)(void *);
    void (*const pushBack)(void *, void *);
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
static inline void DirectionalContainer_pushBack(void *cont, void *value){
    (*(struct DirectionalContainer **)cont)->pushBack(cont, value);
}

#endif /* DIRECTIONALCONTAINER_H */