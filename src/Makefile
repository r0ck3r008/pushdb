# COMPILER CONFIG
COMPILER := gcc
COMPILER_FLAGS := -g
TEST_COMPILER_FLAGS := '-g -fpic'
TEST_LINKER_FLAGS := -lcheck -pthread -L${PWD}/bin -lpushdb
LIB_LINKER_FLAGS := -shared
COMPILE_PATH := ${PWD}

# OBJECT DEFINITIONS
ALL_OBJS := fs/*.o db/*.o parser/*.o comparator/*.o
TEST_OBJS := tests/main_test.o tests/fs/*.o tests/parser/*.o

# TARGETS
all: db_objs fs_objs parser_objs comparator_objs
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
		     COMPILER_FLAGS=${TEST_COMPILER_FLAGS} make -C parser/
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${COMPILER} \
		     COMPILER_FLAGS=${TEST_COMPILER_FLAGS} make -C comparator/
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

parser_objs:
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${COMPILER} \
		     COMPILER_FLAGS=${COMPILER_FLAGS} make -C parser/

comparator_objs:
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${COMPILER} \
		     COMPILER_FLAGS=${COMPILER_FLAGS} make -C comparator/

clean_objs:
	make -C db/ clean
	make -C fs/ clean
	make -C parser/ clean
	make -C comparator/ clean
	make -C tests/ clean

clean: clean_objs
	rm -f bin/*.out
	rm -f bin/*.so
