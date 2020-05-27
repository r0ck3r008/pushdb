all: compare.o alloc.o

compare.o: compare.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c compare.c

alloc.o: alloc.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

clean:
	rm -f *.o
