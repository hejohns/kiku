// priority_queue.h
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

struct priority_queue{
    void *(*const top)(void *);
    void (*const push)(void *, void *);
    void (*const pop)(void *);
    void (*const update_top)(void *);
    size_t (*const size)(void *);
};

static inline void *priority_queue_top(void *pq){
    return (*(struct priority_queue **)pq)->top(pq);
}
static inline void priority_queue_push(void *restrict pq, void *restrict value){
    (*(struct priority_queue **)pq)->push(pq, value);
}
static inline void priority_queue_pop(void *pq){
    (*(struct priority_queue **)pq)->pop(pq);
}
static inline void priority_queue_update_top(void *pq){
    (*(struct priority_queue **)pq)->update_top(pq);
}
static inline size_t priority_queue_size(void *pq){
    return (*(struct priority_queue **)pq)->size(pq);
}

#endif /* PRIORITY_QUEUE_H */
