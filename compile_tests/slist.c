// slist.c

#include <assert.h>
#include <math.h>

#include <kiku/slist.h>

struct oblique{
    size_t a;
    char b;
};

int main(){
    slist int_list = slist_init(sizeof(int));
    slist double_list = slist_init(sizeof(double));
    slist oblique_list = slist_init(sizeof(struct oblique));
    /* basic checks */
    assert(DirectionalContainer_begin(&int_list) == DirectionalContainer_end(&int_list));
    assert(DirectionalContainer_begin(&double_list) == DirectionalContainer_end(&double_list));
    assert(DirectionalContainer_begin(&oblique_list) == DirectionalContainer_end(&oblique_list));
    assert(DirectionalContainer_size(&int_list) == 0);
    assert(DirectionalContainer_size(&double_list) == 0);
    assert(DirectionalContainer_size(&oblique_list) == 0);
    /* slist_pushFront */
    int int_tmp;
    double double_tmp;
    struct oblique oblique_tmp;
    int_tmp=10, DirectionalContainer_pushFront(&int_list, &int_tmp);
    assert(DirectionalContainer_size(&int_list) == 1);
    double_tmp=20, DirectionalContainer_pushFront(&double_list, &double_tmp);
    double_tmp=10, DirectionalContainer_pushFront(&double_list, &double_tmp);
    assert(DirectionalContainer_size(&double_list) == 2);
    oblique_tmp=(struct oblique){30, 3}, DirectionalContainer_pushFront(&oblique_list, &oblique_tmp);
    oblique_tmp=(struct oblique){20, 2}, DirectionalContainer_pushFront(&oblique_list, &oblique_tmp);
    oblique_tmp=(struct oblique){10, 1}, DirectionalContainer_pushFront(&oblique_list, &oblique_tmp);
    assert(DirectionalContainer_size(&oblique_list) == 3);
    /* slist_next */
    int against = 10;
    for(void *tmp = DirectionalContainer_begin(&int_list);
            tmp != DirectionalContainer_end(&int_list);
            tmp = DirectionalContainer_next(&int_list, tmp)){
        assert(*(int *)tmp == against);
        against += 10;
    }
    against = 10;
    for(void *tmp = DirectionalContainer_begin(&double_list);
            tmp != DirectionalContainer_end(&double_list);
            tmp = DirectionalContainer_next(&double_list, tmp)){
        assert(fabs(*(double *)tmp - against) < .01);
        against += 10;
    }
    against = 10;
    for(void *tmp = DirectionalContainer_begin(&oblique_list);
            tmp != DirectionalContainer_end(&oblique_list);
            tmp = DirectionalContainer_next(&oblique_list, tmp)){
        assert(((struct oblique *)tmp)->a == against);
        against += 10;
    }
    /* slist_insertAfter */
    /* free memory */
    slist_free(&int_list);
    slist_free(&double_list);
    slist_free(&oblique_list);
    return 0;
}
