// PriorityQueue.c

#include <assert.h>

#include <kiku/PriorityQueue.h>

#ifndef TYPE
#error
#endif

#define CALL_HELPER2(a, b) a ## _ ## b
#define CALL_HELPER(a, b) CALL_HELPER2(a, b)
#define CALL(x) CALL_HELPER(TYPE, x)

static bool less_int(void *left, void *right){
    return *(int *)left < *(int*)right;
}

int main(){
#ifdef BHEAP_H
    TYPE inst = CALL(init)(less_int, 16, sizeof(int));
#endif
#ifdef staticBheap
#endif
    int tmp;
    srand(0);
    size_t sz = 1<<20;
    for(size_t i=0; i<sz; i++){
        tmp = rand()%100;
        PriorityQueue_push(&inst, &tmp);
    }
    for(size_t i=0; i<sz; i++){
        PriorityQueue_pop(&inst);
    }
    CALL(free)(&inst);
    return 0;
}
