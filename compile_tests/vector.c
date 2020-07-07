#include <kiku/vector.h>

int main(){
    vector inst = vector_init(sizeof(int), 8);
    int tmp;
    tmp=1, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=2, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=3, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=4, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=5, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=6, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=7, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=8, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=9, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=10, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=11, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=12, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=13, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=14, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=15, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=16, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=17, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=18, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=19, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=20, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=21, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=22, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=23, RandomAccessContainer_pushBack(&inst, &tmp);
    tmp=24, RandomAccessContainer_pushBack(&inst, &tmp);
    vector_free(&inst);
    return 0;
}
