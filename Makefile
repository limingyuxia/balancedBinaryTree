
all: bTree

bTree: bTree.o demo.o
	$(CC) $^ -o $@

clean:
	rm -rf bTree *.o