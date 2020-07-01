all: selop.o proj.o

selop.o: selop.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c selop.c

proj.o: proj.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c proj.c

clean:
	rm -f *.o
