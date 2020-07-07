all: record.o alloc.o file.o fcache.o page.o

file.o: file.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c file.c

fcache.o: fcache.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c fcache.c

record.o: record.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c record.c

alloc.o: alloc.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

page.o: page.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c page.c

clean:
	rm -f *.o
