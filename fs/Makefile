all: record.o alloc.o # file.o
#file.o: file.c
#	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c file.c

record.o: record.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c record.c

alloc.o: alloc.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

clean:
	rm -f *.o
