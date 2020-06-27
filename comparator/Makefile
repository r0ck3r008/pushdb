all: cnf.o alloc.o

cnf.o: cnf.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c cnf.c

alloc.o: alloc.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

clean:
	rm -f *.o
