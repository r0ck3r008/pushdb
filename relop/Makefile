all: readop.o selop.o proj.o

readop.o: readop.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c readop.c

selop.o: selop.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c selop.c

proj.o: proj.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c proj.c

clean:
	rm -f *.o
