CC := clang
CFLAGS := -std=c11 -Wpedantic -Wall -Wextra -ggdb -O0

export CPATH := ../include:

.PHONY: default clean

default:
	make clean
bheap.exe: bheap.c
	$(CC) $(CFLAGS) $< -o $@
static_bheap.exe: static_bheap.c
	$(CC) $(CFLAGS) $< -o $@
clean: 
	rm *.o *.exe
