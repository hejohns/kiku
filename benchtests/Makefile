CC := clang
CFLAGS := -std=c11 -Wpedantic -Wall -Wextra -ggdb -O3

export CPATH := ../include:

.PHONY: default clean

default:
	make clean
bheap.exe: bheap.c
	$(CC) $(CFLAGS) $< -o $@
singleList.exe: DirectionalContainer.c
	$(CC) $(CFLAGS) -DTYPE=singleList -include kiku/singleList.h $< -o $@
staticBheap.exe: staticBheap.c
	$(CC) $(CFLAGS) $< -o $@
vector.exe: vector.c
	$(CC) $(CFLAGS) $< -o $@
clean: 
	rm *.o *.exe
