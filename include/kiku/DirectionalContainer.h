// DirectionalContainer.h
#ifndef DIRECTIONALCONTAINER_H
#define DIRECTIONALCONTAINER_H

struct DirectionalContainer{
    void *(*const begin)(void *);
    void *(*const end)(void *);
    void *(const next)(void *, void *);
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

#endif /* DIRECTIONALCONTAINER_H */
