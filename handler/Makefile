all: handler.o ddl.o alloc.o

handler.o: handler.c handler.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c handler.c

ddl.o: ddl.c ddl.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c ddl.c

alloc.o: alloc.c alloc.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

clean:
	rm -f *.o
