all: schema.o

schema.o: schema.c schema.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c schema.c

clean:
	rm -f *.o
