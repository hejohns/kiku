#include <kiku/common.h>
#include <kiku/static_bheap.h>

static bool less_int(void *restrict left, void *restrict right){
    return *(int *)left < *(int*)right;
}

static void push_into_pq(void *restrict pq, void *restrict value){
    (*(struct priority_queue **)pq)->push(pq, value);
}

int main(){
    int array[16];
    static_bheap inst = static_bheap_init(less_int, 16, sizeof(int), array);
    int tmp;
    tmp = 6, push_into_pq(&inst, &tmp);
    tmp = 3, push_into_pq(&inst, &tmp);
    tmp = 2, push_into_pq(&inst, &tmp);
    tmp = 1, push_into_pq(&inst, &tmp);
    tmp = 9, push_into_pq(&inst, &tmp);
    tmp = 8, push_into_pq(&inst, &tmp);
    tmp = 0, push_into_pq(&inst, &tmp);
    tmp = 4, push_into_pq(&inst, &tmp);
    static_bheap_free(&inst);
    return 0;
}
