// CircularContainer.c

#include <assert.h>
#include <math.h>

#include <kiku/CircularContainer.h>

#ifndef TYPE
#error
#endif

#define CALL_HELPER2(a, b) a ## _ ## b
#define CALL_HELPER(a, b) CALL_HELPER2(a, b)
#define CALL(x) CALL_HELPER(TYPE, x)

struct oblique{
    size_t a;
    char b;
};

int main(){
#if defined(CLIST_H)
    TYPE int_list = CALL(init)(sizeof(int));
    TYPE double_list = CALL(init)(sizeof(double));
    TYPE oblique_list = CALL(init)(sizeof(struct oblique));
#endif
#ifdef VECTOR_H
#endif
    /* basic checks */
    assert(BidirectionalContainer_begin(&int_list) == BidirectionalContainer_end(&int_list));
    assert(BidirectionalContainer_begin(&double_list) == BidirectionalContainer_end(&double_list));
    assert(BidirectionalContainer_begin(&oblique_list) == BidirectionalContainer_end(&oblique_list));
    assert(BidirectionalContainer_size(&int_list) == 0);
    assert(BidirectionalContainer_size(&double_list) == 0);
    assert(BidirectionalContainer_size(&oblique_list) == 0);
    /* TYPE_pushBack */
    for(int i=0; i <= 0; i++){
        BidirectionalContainer_pushBack(&int_list, &i);
    }
    assert(BidirectionalContainer_size(&int_list) == 1);
    assert(BidirectionalContainer_begin(&int_list) == BidirectionalContainer_tail(&int_list));
    BidirectionalContainer_clear(&int_list);
    /* TYPE_tail */
    for(int i=1; i <= 10; i++){
        BidirectionalContainer_pushBack(&int_list, &i);
        assert(*(int *)BidirectionalContainer_tail(&int_list) == i);
        assert(BidirectionalContainer_size(&int_list) == (size_t)i);
    }
    for(double i=1; i <= 10; i++){
        BidirectionalContainer_pushBack(&double_list, &i);
        assert(*(double *)BidirectionalContainer_tail(&double_list) == i);
        assert(BidirectionalContainer_size(&double_list) == i);
    }
    for(struct oblique i = {1, 1}; i.a <= 10; i.a++, i.b++){
        BidirectionalContainer_pushBack(&oblique_list, &i);
        assert(((struct oblique *)BidirectionalContainer_tail(&oblique_list))->a == i.a);
        assert(((struct oblique *)BidirectionalContainer_tail(&oblique_list))->b == i.b);
        assert(BidirectionalContainer_size(&oblique_list) == i.a);
    }
    /* TYPE_prev */
    struct oblique against = {10, 10};
    for(void *tmp = BidirectionalContainer_tail(&oblique_list);
            tmp;
            tmp = BidirectionalContainer_prev(&oblique_list, tmp)){
        assert(((struct oblique *)tmp)->a == against.a);
        assert(((struct oblique *)tmp)->b == against.b);
        against.a--;
        against.b--;
        if(tmp == BidirectionalContainer_begin(&oblique_list)){
            break;
        }
    }
    /* TYPE_popBack */
    for(struct oblique i = {10, 10}; i.a >= 1; i.a--, i.b--){
        assert(((struct oblique *)BidirectionalContainer_tail(&oblique_list))->a == i.a);
        assert(((struct oblique *)BidirectionalContainer_tail(&oblique_list))->b == i.b);
        assert(BidirectionalContainer_size(&oblique_list) == i.a);
        BidirectionalContainer_popBack(&oblique_list);
    }
    assert(BidirectionalContainer_size(&oblique_list) == 0);
    assert(BidirectionalContainer_begin(&oblique_list) == NULL);
    assert(BidirectionalContainer_tail(&oblique_list) == NULL);
    /* TYPE_insertBefore */
    against = (struct oblique){1, 1};
    BidirectionalContainer_insertBefore(&oblique_list, BidirectionalContainer_begin(&oblique_list), &against);
    against = (struct oblique){3, 3};
    BidirectionalContainer_insertBefore(&oblique_list, BidirectionalContainer_end(&oblique_list), &against);
    against = (struct oblique){2, 2};
    BidirectionalContainer_insertBefore(&oblique_list, BidirectionalContainer_tail(&oblique_list), &against);
    assert(((struct oblique *)BidirectionalContainer_begin(&oblique_list))->a == 1);
    assert(((struct oblique *)BidirectionalContainer_begin(&oblique_list))->b == 1);
    assert(((struct oblique *)BidirectionalContainer_tail(&oblique_list))->a == 3);
    assert(((struct oblique *)BidirectionalContainer_tail(&oblique_list))->b == 3);
    /* TYPE_eraseBefore */
    BidirectionalContainer_eraseBefore(&oblique_list, BidirectionalContainer_end(&oblique_list));
    assert(((struct oblique *)BidirectionalContainer_tail(&oblique_list))->a == 2);
    assert(((struct oblique *)BidirectionalContainer_tail(&oblique_list))->b == 2);
    /* bench part of benchtest */
    /* (yes that's a joke) */
    /* free memory */
    CALL(free)(&int_list);
    CALL(free)(&double_list);
    CALL(free)(&oblique_list);
    return 0;
}
