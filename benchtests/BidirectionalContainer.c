// BidirectionalContainer.c

#include <assert.h>
#include <math.h>

#include <kiku/BidirectionalContainer.h>

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
#if defined(_doubleList) || defined(_singleList)
    TYPE int_list = CALL(init)(sizeof(int));
    TYPE double_list = CALL(init)(sizeof(double));
    TYPE oblique_list = CALL(init)(sizeof(struct oblique));
#endif
#ifdef _vector 
#endif
    /* basic checks */
    /* TYPE_pushFront */
    /* TYPE_next */
    /* TYPE_insertAfter */
    /* TYPE_eraseAfter */
    /* TYPE_merge */
    /* bench part of benchtest */
    /* (yes that's a joke) */
    /* free memory */
    CALL(free)(&int_list);
    CALL(free)(&double_list);
    CALL(free)(&oblique_list);
    return 0;
}
