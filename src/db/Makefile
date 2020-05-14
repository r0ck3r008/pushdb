all: schema.o alloc.o

schema.o: schema.c schema.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c schema.c

alloc.o: alloc.c alloc.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

clean:
	rm -f *.o
