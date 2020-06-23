// RandomAccessContainer.h
#ifndef RANDOMACCESSCONTAINER_H
#define RANDOMACCESSCONTAINER_H

#include <kiku/BidirectionalContainer.h>

struct RandomAccessContainer{
    struct BidirectionalContainer BidirectionalContainer;
    void *(*const at)(void *, size_t);
};

static inline void *RandomAccessContainer_begin(void *cont){
    return (*(struct DirectionalContainer **)cont)->begin(cont);
}
static inline void *RandomAccessContainer_end(void *cont){
    return (*(struct DirectionalContainer **)cont)->end(cont);
}
static inline void *RandomAccessContainer_next(void *cont, void *node){
    return (*(struct DirectionalContainer **)cont)->next(cont, node);
}
static inline size_t RandomAccessContainer_size(void *cont){
    return (*(struct DirectionalContainer **)cont)->size(cont);
}
static inline void RandomAccessContainer_pushBack(void *cont, void *value){
    (*(struct DirectionalContainer **)cont)->pushBack(cont, value);
}
static inline void *RandomAccessContainer_prev(void *cont, void *node){
    return (*(struct BidirectionalContainer **)cont)->prev(cont, node);
}
static inline void *RandomAccessContainer_tail(void *cont){
    return (*(struct BidirectionalContainer **)cont)->tail(cont);
}
static inline void RandomAccessContainer_pushFront(void *cont, void *value){
    (*(struct BidirectionalContainer **)cont)->pushFront(cont, value);
}
static inline void *RandomAccessContainer_at(void *cont, size_t index){
    return (*(struct RandomAccessContainer **)cont)->at(cont, index);
}

#endif /* RANDOMACCESSCONTAINER_H */
