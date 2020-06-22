// BidirectionalContainer.h
#ifndef BIDIRECTIONALCONTAINER_H
#define BIDIRECTIONALCONTAINER_H

#include "DirectionalContainer.h"

struct BidirectionalContainer{
    struct DirectionalContainer;
    void *(*const prev)(void *, void *);
    void *(*const tail)(void *);
    void (*const pushFront)(void *, void *);
};

static inline void *BidirectionalContainer_begin(void *cont){
    return (*(struct DirectionalContainer **)cont)->begin(cont);
}
static inline void *BidirectionalContainer_end(void *cont){
    return (*(struct DirectionalContainer **)cont)->end(cont);
}
static inline void *BidirectionalContainer_next(void *cont, void *node){
    return (*(struct DirectionalContainer **)cont)->next(cont, node);
}
static inline size_t BidirectionalContainer_size(void *cont){
    return (*(struct DirectionalContainer **)cont)->size(cont);
}
static inline void BidirectionalContainer_pushBack(void *cont, void *value){
    (*(struct DirectionalContainer **)cont)->pushBack(cont, value);
}
static inline void *BidirectionalContainer_prev(void *cont, void *node){
    return (*(struct BidirectionalContainer **)cont)->prev(cont, node);
}
static inline void *BidirectionalContainer_tail(void *cont){
    return (*(struct BidirectionalContainer **)cont)->tail(cont);
}
static inline void *BidirectionalContainer_pushFront(void *cont, void *value){
    return (*(struct BidirectionalContainer **)cont)->pushFront(cont, value);
}

#endif /* BIDIRECTIONALCONTAINER_H */

