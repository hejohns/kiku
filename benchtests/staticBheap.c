#include <stdio.h>

#include <kiku/common.h>
#include <kiku/staticBheap.h>

static bool less_int(void *restrict left, void *restrict right){
    return *(int *)left > *(int*)right;
}

int main(){
    int array[1<<10];
    size_t sz = 1<<10;
    staticBheap inst = staticBheap_init(less_int, sz, sizeof(int), array);
    int tmp;
    srand(0);
    for(size_t i=0; i<sz; i++){
        tmp = rand()%100;
        printf("pushed: %d\n", tmp);
        PriorityQueue_push(&inst, &tmp);
    }
    for(size_t i=0; i<sz; i++){
        printf("top: %d\n", *(int *)(PriorityQueue_top(&inst)));
        PriorityQueue_pop(&inst);
    }
    staticBheap_free(&inst);
    return 0;
}
