#include <stdio.h>
#include <kiku/vector.h>

int main(){
    vector inst = vector_init(8, sizeof(int));
    int tmp;
    size_t sz = 1<<24;
    for(size_t i=0; i<sz; i++){
        tmp=i, RandomAccessContainer_pushBack(&inst, &tmp);
    }
    for(size_t i=0; i<sz; i++){
        printf("at %ld: %d\n", i, *(int *)RandomAccessContainer_at(&inst, i));
    }
    vector_free(&inst);
    return 0;
}
