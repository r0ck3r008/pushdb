# COMPILER CONFIG
COMPILER := gcc
COMPILER_FLAGS := -g
TEST_COMPILER_FLAGS := '-g -fpic'
TEST_LINKER_FLAGS := -lcheck -pthread -L${PWD}/bin -lpushdb
LIB_LINKER_FLAGS := -shared
COMPILE_PATH := ${PWD}

# OBJECT DEFINITIONS
ALL_OBJS := fs/*.o db/*.o
TEST_OBJS := tests/main_test.o tests/fs/*.o

# TARGETS
all: db_objs fs_objs
tests: test_bin

test_bin: test_lib
	${COMPILER} ${TEST_LINKER_FLAGS} ${TEST_OBJS} -o bin/tests.out
	make clean_objs

test_lib: test_objs
	${COMPILER} ${LIB_LINKER_FLAGS} ${ALL_OBJS} -o bin/libpushdb.so

test_objs:
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${COMPILER} \
		     COMPILER_FLAGS=${TEST_COMPILER_FLAGS} make -C db/
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${COMPILER} \
		     COMPILER_FLAGS=${TEST_COMPILER_FLAGS} make -C fs/
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
