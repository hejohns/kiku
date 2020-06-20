// static_priority_queue.h
#ifndef STATIC_PRIORITY_QUEUE_H
#define STATIC_PRIORITY_QUEUE_H

struct static_priority_queue{
    void *(*const top)(void *);
    void (*const push)(void *, void *);
    void (*const pop)(void *);
    void (*const update_top)(void *);
    size_t (*const size)(void *);
};

#endif /* STATIC_PRIORITY_QUEUE_H */
