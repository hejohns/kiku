CC := clang
CFLAGS := -std=c11 -Wpedantic -Wall -Wextra -ggdb -O0

export CPATH := ../include:

# really all targets should phony but I didn't want to complicate things
.PHONY: default clean

default:
	make clean
bheap: PriorityQueue.c
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 1, $^) -o $@.exe
	valgrind --tool=memcheck ./$@.exe
clist: CircularContainer.c
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 1, $^) -o $@.exe
	valgrind --tool=memcheck ./$@.exe
dlist: BidirectionalContainer.c DirectionalContainer.c
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 2, $^) -o $@.exe
	valgrind --tool=memcheck ./$@.exe
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 1, $^) -o $@.exe
	valgrind --tool=memcheck ./$@.exe
slist: DirectionalContainer.c
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 1, $^) -o $@.exe
	valgrind --tool=memcheck ./$@.exe
staticBheap.exe: StaticPriorityQueue.c
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 1, $^) -o $@.exe
	valgrind --tool=memcheck ./$@.exe
vector.exe: vector.c
	$(CC) $(CFLAGS) $< -o $@
clean: 
	rm *.o *.exe
