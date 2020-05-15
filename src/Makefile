COMPILER := gcc
GTEST_COMPILER := g++
COMPILER_FLAGS := -g
LINKER_FLAGS := -o
COMPILE_PATH := ${PWD}

all: db_objs fs_objs

tests: test_objs

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

clean: clean_objs
