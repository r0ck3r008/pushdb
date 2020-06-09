all: record.o alloc.o file.o page.o
file.o: file.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c file.c

record.o: record.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c record.c

alloc.o: alloc.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

page.o: page.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c page.c

clean:
	rm -f *.o
