all: selop.o proj.o

selop.o: selop.c selop.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c selop.c

proj.o: proj.c proj.h
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c proj.c

clean:
	rm -f *.o
