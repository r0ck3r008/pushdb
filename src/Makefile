# COMPILER CONFIG
COMPILER := gcc
COMPILER_FLAGS := -g
LINKER_FLAGS := -lcheck -pthread
COMPILE_PATH := ${PWD}

# OBJECT DEFINITIONS
ALL_OBJS := fs/*.o db/*.o
TEST_OBJS := tests/main_test.o tests/fs/*.o ${ALL_OBJS}

# TARGETS
all: db_objs fs_objs
tests: test_objs all test_bin

test_bin:
	${COMPILER} ${LINKER_FLAGS} ${TEST_OBJS} -o bin/tests.out
	make clean_objs

test_objs:
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${COMPILER} \
		     COMPILER_FLAGS=${COMPILER_FLAGS} make -C tests/

db_objs:
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${COMPILER} \
		     COMPILER_FLAGS=${COMPILER_FLAGS} make -C db/
fs_objs:
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${COMPILER} \
		     COMPILER_FLAGS=${COMPILER_FLAGS} make -C fs/

clean_objs:
	make -C db/ clean
	make -C fs/ clean
	make -C tests/ clean

clean: clean_objs
	rm -f bin/*.out
