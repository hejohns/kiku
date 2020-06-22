// PriorityQueue.h
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

struct PriorityQueue{
    void *(*const top)(void *);
    void (*const push)(void *, void *);
    void (*const pop)(void *);
    void (*const updateTop)(void *);
    size_t (*const size)(void *);
};

static inline void *PriorityQueue_top(void *pq){
    return (*(struct PriorityQueue **)pq)->top(pq);
}
static inline void PriorityQueue_push(void *pq, void *value){
    (*(struct PriorityQueue **)pq)->push(pq, value);
}
static inline void PriorityQueue_pop(void *pq){
    (*(struct PriorityQueue **)pq)->pop(pq);
}
static inline void PriorityQueue_updateTop(void *pq){
    (*(struct PriorityQueue **)pq)->update_top(pq);
}
static inline size_t PriorityQueue_size(void *pq){
    return (*(struct PriorityQueue **)pq)->size(pq);
}

#endif /* PRIORITYQUEUE_H */
