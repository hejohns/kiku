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

#endif /* PRIORITY_QUEUE_H */
