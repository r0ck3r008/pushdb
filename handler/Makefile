all: handler.o ddl.o alloc.o

handler.o: handler.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c handler.c

ddl.o: ddl.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c ddl.c

alloc.o: alloc.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

clean:
	rm -f *.o
