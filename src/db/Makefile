all: schema.o alloc.o query.o

schema.o: schema.c schema.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c schema.c

alloc.o: alloc.c alloc.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

query.o: query.c query.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c query.c

clean:
	rm -f *.o
