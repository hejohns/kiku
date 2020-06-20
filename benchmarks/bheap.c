#include <stdio.h>

#include <kiku/common.h>
#include <kiku/bheap.h>

static bool less_int(void *restrict left, void *restrict right){
    return *(int *)left < *(int*)right;
}

int main(){
    bheap inst = bheap_init(less_int, 16, sizeof(int));
    int tmp;
    srand(0);
    size_t sz = 1<<24;
    for(size_t i=0; i<sz; i++){
        tmp = rand()%100;
        printf("pushed: %d\n", tmp);
        priority_queue_push(&inst, &tmp);
    }
    for(size_t i=0; i<sz; i++){
        printf("top: %d\n", *(int *)(priority_queue_top(&inst)));
        priority_queue_pop(&inst);
    }
    bheap_free(&inst);
    return 0;
}
