// singleList.c

#include <assert.h>
#include <math.h>

#include <kiku/singleList.h>

struct oblique{
    size_t a;
    char b;
};

int main(){
    singleList int_list = singleList_init(sizeof(int));
    singleList double_list = singleList_init(sizeof(double));
    singleList oblique_list = singleList_init(sizeof(struct oblique));
    /* basic checks */
    assert(DirectionalContainer_begin(&int_list) == DirectionalContainer_end(&int_list));
    assert(DirectionalContainer_begin(&double_list) == DirectionalContainer_end(&double_list));
    assert(DirectionalContainer_begin(&oblique_list) == DirectionalContainer_end(&oblique_list));
    assert(DirectionalContainer_size(&int_list) == 0);
    assert(DirectionalContainer_size(&double_list) == 0);
    assert(DirectionalContainer_size(&oblique_list) == 0);
    /* singleList_pushFront */
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
    /* singleList_next */
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
        assert(((struct oblique *)tmp)->a == (size_t)against);
        against += 10;
    }
    /* singleList_insertAfter */
    oblique_tmp=(struct oblique){11, 1}, DirectionalContainer_insertAfter(&oblique_list, DirectionalContainer_begin(&oblique_list), &oblique_tmp);
    oblique_tmp=(struct oblique){12, 1}, DirectionalContainer_insertAfter(&oblique_list, DirectionalContainer_next(&oblique_list, DirectionalContainer_begin(&oblique_list)), &oblique_tmp);
    do{
        int sw=0;
        for(void *tmp = DirectionalContainer_begin(&oblique_list);
                tmp != DirectionalContainer_end(&oblique_list);
                tmp = DirectionalContainer_next(&oblique_list, tmp)){
            switch(sw){
                case 0:
                    assert(((struct oblique *)tmp)->a == 10);
                    break;
                case 1:
                    assert(((struct oblique *)tmp)->a == 11);
                    break;
                case 2:
                    assert(((struct oblique *)tmp)->a == 12);
                    break;
                case 3:
                    assert(((struct oblique *)tmp)->a == 20);
                    break;
                case 4:
                    assert(((struct oblique *)tmp)->a == 30);
                    break;
            }
            sw++;
        }
    } while(0);
    /* singleList_eraseAfter */
    DirectionalContainer_eraseAfter(&oblique_list, DirectionalContainer_begin(&oblique_list));
    DirectionalContainer_eraseAfter(&oblique_list, DirectionalContainer_begin(&oblique_list));
    do{
        int sw=0;
        for(void *tmp = DirectionalContainer_begin(&oblique_list);
                tmp != DirectionalContainer_end(&oblique_list);
                tmp = DirectionalContainer_next(&oblique_list, tmp)){
            switch(sw){
                case 0:
                    assert(((struct oblique *)tmp)->a == 10);
                    break;
                case 1:
                    assert(((struct oblique *)tmp)->a == 20);
                    break;
                case 2:
                    assert(((struct oblique *)tmp)->a == 30);
                    break;
            }
            sw++;
        }
    } while(0);
    /* singleList_merge */
    singleList oblique_list2 = singleList_init(sizeof(struct oblique));
    for(void *tmp = DirectionalContainer_begin(&oblique_list);
            tmp != DirectionalContainer_end(&oblique_list);
            tmp = DirectionalContainer_next(&oblique_list, tmp)){
        DirectionalContainer_pushFront(&oblique_list2, tmp);
    }
    DirectionalContainer_merge(&oblique_list, &oblique_list2);
    do{
        int sw=0;
        for(void *tmp = DirectionalContainer_begin(&oblique_list);
                tmp != DirectionalContainer_end(&oblique_list);
                tmp = DirectionalContainer_next(&oblique_list, tmp)){
            switch(sw){
                case 0:
                    assert(((struct oblique *)tmp)->a == 10);
                    break;
                case 1:
                    assert(((struct oblique *)tmp)->a == 20);
                    break;
                case 2:
                    assert(((struct oblique *)tmp)->a == 30);
                    break;
                case 3:
                    assert(((struct oblique *)tmp)->a == 30);
                    break;
                case 4:
                    assert(((struct oblique *)tmp)->a == 20);
                    break;
                case 5:
                    assert(((struct oblique *)tmp)->a == 10);
                    break;
            }
            sw++;
        }
    } while(0);
    singleList_free(&oblique_list2);
    /* bench part of benchtest */
    DirectionalContainer_clear(&oblique_list);
    for(size_t i=1; i <= 1<<20; i++){
        // abusing struct layout (struct oblique.b's are totally corrupted)
        DirectionalContainer_pushFront(&oblique_list, &i);
    }
    for(size_t i=1<<20; i>0; i--){
        assert(((struct oblique *)DirectionalContainer_begin(&oblique_list))->a
                == i);
        DirectionalContainer_popFront(&oblique_list);
    }
    assert(DirectionalContainer_size(&oblique_list) == 0);
    /* free memory */
    singleList_free(&int_list);
    singleList_free(&double_list);
    singleList_free(&oblique_list);
    return 0;
}
