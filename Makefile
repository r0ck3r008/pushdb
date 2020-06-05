# COMPILER CONFIG
COMPILER := gcc
COMPILER_FLAGS := '-g -Wall'
LINKER_FLAGS := -pthread
COMPILE_PATH := ${PWD}/include

# OBJECT DEFINITIONS
ALL_OBJS := entrypoint/*.o fs/*.o db/*.o parser/*.o comparator/*.o handler/*.o

# TARGETS
all: pushdb_bin

pushdb_bin: entrypoint_objs db_objs fs_objs parser_objs comparator_objs handler_objs tpch_bin
	${COMPILER} ${LINKER_FLAGS} ${ALL_OBJS} -o bin/pushdb.out
	make clean_objs

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

entrypoint_objs:
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${COMPILER} \
		     COMPILER_FLAGS=${COMPILER_FLAGS} make -C entrypoint/

handler_objs:
	COMPILE_PATH=${COMPILE_PATH} \
		     COMPILER=${COMPILER} \
		     COMPILER_FLAGS=${COMPILER_FLAGS} make -C handler/

tpch_bin:
	make -C tpch-dbgen/

clean_objs:
	make -C db/ clean
	make -C fs/ clean
	make -C parser/ clean
	make -C comparator/ clean
	make -C entrypoint/ clean
	make -C handler/ clean

clean: clean_objs
	rm -f bin/*.out
	make -C tpch-dbgen/ clean
