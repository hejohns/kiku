#include <assert.h>

#include <kiku/BidirectionalContainer.h>
#include <kiku/doubleList.h>

struct weird{
    int a;
    char b;
    int c;
    char d;
};

int main(){
    {
        doubleList inst = doubleList_init(sizeof(int));
        int tmp;
        tmp=1, BidirectionalContainer_pushBack(&inst, &tmp);
        assert(inst.head == inst.tail);
        assert(*(int *)BidirectionalContainer_begin(&inst) == tmp);
        tmp=2, BidirectionalContainer_pushFront(&inst, &tmp);
        assert(*(int *)BidirectionalContainer_begin(&inst) == tmp);
        assert(*(int *)BidirectionalContainer_next(&inst, BidirectionalContainer_begin(&inst)) == 1);
        assert(inst.head != inst.tail);
        doubleList_free(&inst);
    }
    {
        doubleList inst = doubleList_init(sizeof(double));
        double tmp;
        tmp=1.5, BidirectionalContainer_pushBack(&inst, &tmp);
        assert(inst.head == inst.tail);
        assert(*(double *)BidirectionalContainer_begin(&inst) == tmp);
        tmp=2.5, BidirectionalContainer_pushFront(&inst, &tmp);
        assert(*(double *)BidirectionalContainer_begin(&inst) == tmp);
        assert(*(double *)BidirectionalContainer_next(&inst, BidirectionalContainer_begin(&inst)) == 1.5);
        assert(inst.head != inst.tail);
        doubleList_free(&inst);
    }
    {
        doubleList inst = doubleList_init(sizeof(struct weird));
        struct weird tmp;
        tmp=(struct weird){8, 8, 8, 8}, BidirectionalContainer_pushBack(&inst, &tmp);
        assert(inst.head == inst.tail);
        assert(((struct weird *)BidirectionalContainer_begin(&inst))->a == 8);
        tmp=(struct weird){9, 9, 9, 9}, BidirectionalContainer_pushFront(&inst, &tmp);
        assert(((struct weird *)BidirectionalContainer_begin(&inst))->a == 9);
        assert((((struct weird *)BidirectionalContainer_next(&inst, BidirectionalContainer_begin(&inst)))->a == 8));
        assert(inst.head != inst.tail);
        doubleList_free(&inst);
    }
    return 0;
}
