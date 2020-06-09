all: y.tab.o lex.yy.o

y.tab.o: parser.y
	yacc -d parser.y
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c y.tab.c

lex.yy.o: lexer.l
	lex lexer.l
	${COMPILER} ${COMPILE_PATH} ${COMPILER_FLAGS} -c lex.yy.c

clean:
	rm -f ./*.o
	rm -f y.tab.*
	rm -f lex.yy.c
