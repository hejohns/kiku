CC := clang
CFLAGS := -std=c11 -Wpedantic -Wall -Wextra -ggdb -O3

export CPATH := ../include:

.PHONY: default clean

default:
	make clean
bheap.exe: bheap.c
	$(CC) $(CFLAGS) $< -o $@
doubleList: BidirectionalContainer.c DirectionalContainer.c
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 1, $^) -o $@.exe
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 2, $^) -o $@.exe
singleList: DirectionalContainer.c
	$(CC) $(CFLAGS) -DTYPE=$@ -include kiku/$@.h $(word 1, $^) -o $@.exe
	valgrind --tool=memcheck ./$@.exe
staticBheap.exe: staticBheap.c
	$(CC) $(CFLAGS) $< -o $@
vector.exe: vector.c
	$(CC) $(CFLAGS) $< -o $@
clean: 
	rm *.o *.exe
