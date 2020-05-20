all: compare.o alloc.o

compare.o: compare.c compare.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c compare.c

alloc.o: alloc.c alloc.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

clean:
	rm -f *.o
