#include <stdio.h>
#include <assert.h>
#include <kiku/vector.h>

int main(){
    vector inst = vector_init(sizeof(int), 8);
    int tmp;
    size_t sz = 1<<16;
    for(size_t i=0; i<sz; i++){
        tmp=i, RandomAccessContainer_pushBack(&inst, &tmp);
    }
    assert(RandomAccessContainer_size(&inst) == sz);
    for(size_t i=0; i<sz; i++){
        assert(i == *(int *)RandomAccessContainer_at(&inst, i));
    }
    for(size_t i=0; i<sz; i++){
        RandomAccessContainer_popFront(&inst);
    }
    assert(RandomAccessContainer_size(&inst) == 0);
    for(size_t i=0; i<sz; i++){
        tmp=i, RandomAccessContainer_pushFront(&inst, &tmp);
    }
    assert(RandomAccessContainer_size(&inst) == sz);
    for(size_t i=0; i<sz; i++){
        assert((sz-1-i) == *(int *)RandomAccessContainer_at(&inst, i));
    }
    for(size_t i=0; i<sz; i++){
        RandomAccessContainer_popBack(&inst);
    }
    assert(RandomAccessContainer_size(&inst) == 0);
    vector_free(&inst);
    return 0;
}
