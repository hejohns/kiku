CC := clang
CFLAGS := -std=c11 -Wpedantic -Wall -Wextra -ggdb -O3

export CPATH := ../include:

# really all targets should phony but I didn't want to complicate things
.PHONY: default clean

default:
	make clean
bheap: PriorityQueue.c
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 1, $^) -o $@.exe
	valgrind --tool=memcheck ./$@.exe
doubleList: BidirectionalContainer.c DirectionalContainer.c
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 1, $^) -o $@.exe
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 2, $^) -o $@.exe
singleList: DirectionalContainer.c
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 1, $^) -o $@.exe
	valgrind --tool=memcheck ./$@.exe
staticBheap.exe: StaticPriorityQueue.c
	$(CC) $(CFLAGS) -DTYPE=$@ -DINIT_ARGS=less_int,16,sizeof(int) -include kiku/$@.h $(word 1, $^) -o $@.exe
	valgrind --tool=memcheck ./$@.exe
vector.exe: vector.c
	$(CC) $(CFLAGS) $< -o $@
clean: 
	rm *.o *.exe
