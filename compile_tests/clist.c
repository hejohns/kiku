#include <kiku/clist.h>

int main(){
    clist clist_inst = clist_init(sizeof(int));
    clist_free(&clist_inst);
    return 0;
}
