#include <kiku/common.h>
#include <kiku/bheap.h>

static bool less_int(void *restrict left, void *restrict right){
    return *(int *)left < *(int*)right;
}

int main(){
    bheap inst = bheap_init(less_int, 16, sizeof(int));
    int tmp;
    tmp = 6, priority_queue_push(&inst, &tmp);
    tmp = 3, priority_queue_push(&inst, &tmp);
    tmp = 2, priority_queue_push(&inst, &tmp);
    tmp = 1, priority_queue_push(&inst, &tmp);
    tmp = 9, priority_queue_push(&inst, &tmp);
    tmp = 8, priority_queue_push(&inst, &tmp);
    tmp = 0, priority_queue_push(&inst, &tmp);
    tmp = 4, priority_queue_push(&inst, &tmp);
    bheap_free(&inst);
    return 0;
}
