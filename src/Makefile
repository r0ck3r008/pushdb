COMPILER := gcc
GTEST_COMPILER := g++
COMPILER_FLAGS := -g
LINKER_FLAGS := -o
GTEST_LINKER_FLAGS := -lgtest
COMPILE_PATH := ${PWD}

TEST_OBJS := tests/*.o

all: db_objs fs_objs

tests: test_objs test_bin

test_bin:
	${GTEST_COMPILER} ${GTEST_LINKER_FLAGS} ${TEST_OBJS} -o bin/tests.out

test_objs:
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${GTEST_COMPILER} \
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
	rm -f bin/*.out

clean: clean_objs
