all: schema.o alloc.o query.o attmap.o

schema.o: schema.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c schema.c

alloc.o: alloc.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c alloc.c

query.o: query.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c query.c

attmap.o: attmap.c
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c attmap.c

clean:
	rm -f *.o
