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
static inline void RandomAccessContainer_pushFront(void *cont, void *value){
    (*(struct DirectionalContainer **)cont)->pushFront(cont, value);
}
static inline void RandomAccessContainer_popFront(void *cont){
    (*(struct DirectionalContainer **)cont)->popFront(cont);
}
static inline void RandomAccessContainer_insertAfter(void *cont, void *node, void *value){
    (*(struct DirectionalContainer **)cont)->insertAfter(cont, node, value);
}
static inline void RandomAccessContainer_eraseAfter(void *cont, void *node){
    (*(struct DirectionalContainer **)cont)->eraseAfter(cont, node);
}
static inline void RandomAccessContainer_merge(void *cont, void *cont_other){
    (*(struct DirectionalContainer **)cont)->merge(cont, cont_other);
}
static inline void RandomAccessContainer_clear(void *cont){
    (*(struct DirectionalContainer **)cont)->clear(cont);
}
static inline void *RandomAccessContainer_prev(void *cont, void *node){
    return (*(struct BidirectionalContainer **)cont)->prev(cont, node);
}
static inline void *RandomAccessContainer_tail(void *cont){
    return (*(struct BidirectionalContainer **)cont)->tail(cont);
}
static inline void RandomAccessContainer_pushBack(void *cont, void *value){
    (*(struct BidirectionalContainer **)cont)->pushBack(cont, value);
}
static inline void RandomAccessContainer_popBack(void *cont){
    (*(struct BidirectionalContainer **)cont)->popBack(cont);
}
static inline void RandomAccessContainer_insertBefore(void *cont, void *node void *value){
    (*(struct BidirectionalContainer **)cont)->insertBefore(cont, node, value);
}
static inline void RandomAccessContainer_eraseBefore(void *cont, void *node){
    (*(struct BidirectionalContainer **)cont)->eraseBefore(cont, node);
}
static inline void *RandomAccessContainer_at(void *cont, size_t index){
    return (*(struct RandomAccessContainer **)cont)->at(cont, index);
}
/* additional functions for convenience */

static inline void RandomAccessContainer_erase(void *cont, void *node){
    (*(struct BidirectionalContainer **)cont)->eraseBefore(cont,
            (*(struct DirectionalContainer **)cont)->next(cont, node));
}

#endif /* RANDOMACCESSCONTAINER_H */
