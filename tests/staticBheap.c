#include <kiku/common.h>
#include <kiku/staticBheap.h>

static bool less_int(void *restrict left, void *restrict right){
    return *(int *)left < *(int*)right;
}

int main(){
    int array[16];
    staticBheap inst = staticBheap_init(less_int, 16, sizeof(int), array);
    int tmp;
    tmp = 6, PriorityQueue_push(&inst, &tmp);
    tmp = 3, PriorityQueue_push(&inst, &tmp);
    tmp = 2, PriorityQueue_push(&inst, &tmp);
    tmp = 1, PriorityQueue_push(&inst, &tmp);
    tmp = 9, PriorityQueue_push(&inst, &tmp);
    tmp = 8, PriorityQueue_push(&inst, &tmp);
    tmp = 0, PriorityQueue_push(&inst, &tmp);
    tmp = 4, PriorityQueue_push(&inst, &tmp);
    staticBheap_free(&inst);
    return 0;
}
