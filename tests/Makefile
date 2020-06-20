CC := clang
CFLAGS := -std=c11 -Wpedantic -Wall -ggdb -O0

export CPATH := ../include:

.PHONY: default clean

default:
	make clean
bheap.exe: bheap.c
	$(CC) $(CFLAGS) $< -o $@
clean: 
	rm *.o *.exe
