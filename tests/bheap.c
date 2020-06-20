#include <kiku/common.h>
#include <kiku/bheap.h>

static bool less_int(void *restrict left, void *restrict right){
    return *(int *)left < *(int*)right;
}

static void push_into_pq(void *restrict pq, void *restrict value){
    (*(struct priority_queue **)pq)->push(pq, value);
}

int main(){
    bheap inst = bheap_init(less_int, 16, sizeof(int));
    int tmp;
    tmp = 6, push_into_pq(&inst, &tmp);
    tmp = 3, push_into_pq(&inst, &tmp);
    tmp = 2, push_into_pq(&inst, &tmp);
    tmp = 1, push_into_pq(&inst, &tmp);
    tmp = 9, push_into_pq(&inst, &tmp);
    tmp = 8, push_into_pq(&inst, &tmp);
    tmp = 0, push_into_pq(&inst, &tmp);
    tmp = 4, push_into_pq(&inst, &tmp);
    bheap_free(&inst);
    return 0;
}
