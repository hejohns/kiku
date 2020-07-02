// CircularContainer.h
#ifndef CIRCULARCONTAINER_H
#define CIRCULARCONTAINER_H

#include <kiku/BidirectionalContainer.h>

struct CircularContainer{
    struct BidirectionalContainer BidirectionalContainer;
};

static inline void *CircularContainer_begin(void *cont){
    return (*(struct DirectionalContainer **)cont)->begin(cont);
}
static inline void *CircularContainer_end(void *cont){
    return (*(struct DirectionalContainer **)cont)->end(cont);
}
static inline void *CircularContainer_next(void *cont, void *node){
    return (*(struct DirectionalContainer **)cont)->next(cont, node);
}
static inline size_t CircularContainer_size(void *cont){
    return (*(struct DirectionalContainer **)cont)->size(cont);
}
static inline void CircularContainer_pushFront(void *cont, void *value){
    (*(struct DirectionalContainer **)cont)->pushFront(cont, value);
}
static inline void CircularContainer_popFront(void *cont){
    (*(struct DirectionalContainer **)cont)->popFront(cont);
}
static inline void CircularContainer_insertAfter(void *cont, void *node, void *value){
    (*(struct DirectionalContainer **)cont)->insertAfter(cont, node, value);
}
static inline void CircularContainer_eraseAfter(void *cont, void *node){
    (*(struct DirectionalContainer **)cont)->eraseAfter(cont, node);
}
static inline void CircularContainer_merge(void *cont, void *cont_other){
    (*(struct DirectionalContainer **)cont)->merge(cont, cont_other);
}
static inline void CircularContainer_clear(void *cont){
    (*(struct DirectionalContainer **)cont)->clear(cont);
}
static inline void *CircularContainer_prev(void *cont, void *node){
    return (*(struct BidirectionalContainer **)cont)->prev(cont, node);
}
static inline void *CircularContainer_tail(void *cont){
    return (*(struct BidirectionalContainer **)cont)->tail(cont);
}
static inline void CircularContainer_pushBack(void *cont, void *value){
    (*(struct BidirectionalContainer **)cont)->pushBack(cont, value);
}
static inline void CircularContainer_popBack(void *cont){
    (*(struct BidirectionalContainer **)cont)->popBack(cont);
}
static inline void CircularContainer_insertBefore(void *cont, void *node, void *value){
    (*(struct BidirectionalContainer **)cont)->insertBefore(cont, node, value);
}
static inline void CircularContainer_eraseBefore(void *cont, void *node){
    (*(struct BidirectionalContainer **)cont)->eraseBefore(cont, node);
}
/* additional functions for convenience */

static inline void CircularContainer_erase(void *cont, void *node){
    if(node == CircularContainer_begin(cont)){
        CircularContainer_popFront(cont);
    }
    else if(node == CircularContainer_tail(cont)){
        CircularContainer_popBack(cont);
    }
    else{
        CircularContainer_eraseBefore(cont, CircularContainer_next(cont, node));
    }
}

#endif /* CIRCULARCONTAINER_H */

