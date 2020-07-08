// BidirectionalContainer.h
#ifndef BIDIRECTIONALCONTAINER_H
#define BIDIRECTIONALCONTAINER_H

#include <kiku/DirectionalContainer.h>

struct BidirectionalContainer{
    struct DirectionalContainer DirectionalContainer;
    void *(*const prev)(void *, void *);
    void *(*const tail)(void *);
    void (*const pushBack)(void *, void *);
    void (*const popBack)(void *);
    void (*const insertBefore)(void *, void *, void *);
    void (*const eraseBefore)(void *, void *);
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
static inline void BidirectionalContainer_pushFront(void *cont, void *value){
    (*(struct DirectionalContainer **)cont)->pushFront(cont, value);
}
static inline void BidirectionalContainer_popFront(void *cont){
    (*(struct DirectionalContainer **)cont)->popFront(cont);
}
static inline void BidirectionalContainer_insertAfter(void *cont, void *node, void *value){
    (*(struct DirectionalContainer **)cont)->insertAfter(cont, node, value);
}
static inline void BidirectionalContainer_eraseAfter(void *cont, void *node){
    (*(struct DirectionalContainer **)cont)->eraseAfter(cont, node);
}
static inline void BidirectionalContainer_merge(void *cont, void *cont_other){
    (*(struct DirectionalContainer **)cont)->merge(cont, cont_other);
}
static inline void BidirectionalContainer_clear(void *cont){
    (*(struct DirectionalContainer **)cont)->clear(cont);
}
static inline void *BidirectionalContainer_prev(void *cont, void *node){
    return (*(struct BidirectionalContainer **)cont)->prev(cont, node);
}
static inline void *BidirectionalContainer_tail(void *cont){
    return (*(struct BidirectionalContainer **)cont)->tail(cont);
}
static inline void BidirectionalContainer_pushBack(void *cont, void *value){
    (*(struct BidirectionalContainer **)cont)->pushBack(cont, value);
}
static inline void BidirectionalContainer_popBack(void *cont){
    (*(struct BidirectionalContainer **)cont)->popBack(cont);
}
static inline void BidirectionalContainer_insertBefore(void *cont, void *node, void *value){
    (*(struct BidirectionalContainer **)cont)->insertBefore(cont, node, value);
}
static inline void BidirectionalContainer_eraseBefore(void *cont, void *node){
    (*(struct BidirectionalContainer **)cont)->eraseBefore(cont, node);
}
/* additional functions for convenience */

static inline void BidirectionalContainer_erase(void *cont, void *node){
    BidirectionalContainer_eraseBefore(cont, BidirectionalContainer_next(cont, node));
}

static inline void *BidirectionalContainer_rbegin(void *cont){
    if(BidirectionalContainer_size(cont)){
        return BidirectionalContainer_prev(cont, BidirectionalContainer_begin(cont));
    }
    else{
        return BidirectionalContainer_begin(cont);
    }
}

#endif /* BIDIRECTIONALCONTAINER_H */

