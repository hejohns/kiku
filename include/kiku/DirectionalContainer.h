// DirectionalContainer.h
#ifndef DIRECTIONALCONTAINER_H
#define DIRECTIONALCONTAINER_H

struct DirectionalContainer{
    void *(*const begin)(void *);
    void *(*const end)(void *);
    void *(*const next)(void *, void *);
    size_t (*const size)(void *);
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

#endif /* DIRECTIONALCONTAINER_H */
