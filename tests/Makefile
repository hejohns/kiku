CC := clang
CFLAGS := -std=c11 -Wpedantic -Wall -Wextra -ggdb -O0

export CPATH := ../include:

.PHONY: default clean

default:
	make clean
bheap.exe: bheap.c
	$(CC) $(CFLAGS) $< -o $@
doubleList.exe: doubleList.c
	$(CC) $(CFLAGS) $< -o $@
singleList.exe: singleList.c
	$(CC) $(CFLAGS) $< -o $@
staticBheap.exe: staticBheap.c
	$(CC) $(CFLAGS) $< -o $@
vector.exe: vector.c
	$(CC) $(CFLAGS) $< -o $@
clean: 
	rm *.o *.exe
