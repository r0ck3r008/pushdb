all: record.o alloc.o
file.o: file.c file.h
	${COMPILER} -I${COMPILER_PATH} ${COMPILER_FLAGS} -c file.c

record.o: record.c record.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c record.c

alloc.o: alloc.c alloc.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

clean:
	rm -f *.o
