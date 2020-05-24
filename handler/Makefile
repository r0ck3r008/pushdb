all: handler.o ddl.o

handler.o: handler.c handler.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c handler.c

ddl.o: ddl.c ddl.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c ddl.c
