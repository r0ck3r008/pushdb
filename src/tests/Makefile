all: main_test.o fs_tests

main_test.o: main_test.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c main_test.c

fs_tests:
	COMPILER=${COMPILER} \
		 COMPILE_PATH=${COMPILE_PATH} \
		 COMPILER_OPTIONS=${COMPILER_OPTIONS} make -C fs/

clean:
	make -C fs/ clean
	rm -f *.o
