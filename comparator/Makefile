all: cnf.o compare.o alloc.o

cnf.o: cnf.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c cnf.c

compare.o: compare.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c compare.c

alloc.o: alloc.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

clean:
	rm -f *.o
