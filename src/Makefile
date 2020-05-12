COMPILER := gcc
COMPILER_FLAGS := -g
LINKER_FLAGS := -o
COMPILE_PATH := ${PWD}

all: db_objs

db_objs:
	COMPILE_PATH=${COMPILE_PATH} COMPILER=${COMPILER} COMPILER_FLAGS=${COMPILER_FLAGS} make -C db/

clean_objs:
	make -C db/ clean

clean: clean_objs
