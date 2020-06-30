// StaticPriorityQueue.h
#ifndef STATICPRIORITYQUEUE_H
#define STATICPRIORITYQUEUE_H

struct StaticPriorityQueue{
    struct PriorityQueue PriorityQueue;
};

static inline void *StaticPriorityQueue_top(void *pq){
    return (*(struct PriorityQueue **)pq)->top(pq);
}
static inline void StaticPriorityQueue_push(void *pq, void *value){
    (*(struct PriorityQueue **)pq)->push(pq, value);
}
static inline void StaticPriorityQueue_pop(void *pq){
    (*(struct PriorityQueue **)pq)->pop(pq);
}
static inline void StaticPriorityQueue_updateTop(void *pq){
    (*(struct PriorityQueue **)pq)->updateTop(pq);
}
static inline size_t StaticPriorityQueue_size(void *pq){
    return (*(struct PriorityQueue **)pq)->size(pq);
}

#endif /* STATICPRIORITYQUEUE_H */
