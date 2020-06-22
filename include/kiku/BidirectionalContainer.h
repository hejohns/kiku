// BidirectionalContainer.h
#ifndef BIDIRECTIONALCONTAINER_H
#define BIDIRECTIONALCONTAINER_H

struct BidirectionalContainer{
    struct DirectionalContainer;
    void *(*const prev)(void *, void *);
    void *(*const tail)(void *);
};

static inline void *BidirectionalContainer_prev(void *cont, void *node){
    return (*(struct BidirectionalContainer **)cont)->prev(cont, node);
}
static inline void *BidirectionalContainer_tail(void *cont){
    return (*(struct BidirectionalContainer **)cont)->tail(cont);
}

#endif /* BIDIRECTIONALCONTAINER_H */

