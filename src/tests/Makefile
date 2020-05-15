all: main_test.o record_test.o

main_test.o: main_test.cc
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c main_test.cc

record_test.o: record_test.cc
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c record_test.cc

clean:
	rm -f *.o
