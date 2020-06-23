// MergeablePriorityQueue.h
#ifndef MERGEABLEPRIORITYQUEUE_H
#define MERGEABLEPRIORITYQUEUE_H

struct MergeablePriorityQueue{
    struct PriorityQueue PriorityQueue;
    void (*const merge)(void *, void *);
};

static inline void *MergeablePriorityQueue_top(void *pq){
    return (*(struct PriorityQueue **)pq)->top(pq);
}
static inline void MergeablePriorityQueue_push(void *pq, void *value){
    (*(struct PriorityQueue **)pq)->push(pq, value);
}
static inline void MergeablePriorityQueue_pop(void *pq){
    (*(struct PriorityQueue **)pq)->pop(pq);
}
static inline void MergeablePriorityQueue_updateTop(void *pq){
    (*(struct PriorityQueue **)pq)->updateTop(pq);
}
static inline size_t MergeablePriorityQueue_size(void *pq){
    return (*(struct PriorityQueue **)pq)->size(pq);
}
static inline void MergeablePriorityQueue_merge(void *pq, void *pq_other){
    (*(struct MergeablePriorityQueue **)pq)->merge(pq, pq_other);
}

#endif /* MERGEABLEPRIORITYQUEUE_H */

