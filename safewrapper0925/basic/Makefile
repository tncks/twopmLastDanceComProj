# Makefile for C-Minus Scanner
# ./lex/tiny.l --> ./cminus.l

CC = gcc 

CFLAGS = -W -Wall

LEX = flex
YACC = yacc
LIBS = -ll -lm

PARSER = parser.y
LEXER = cminus.l
MAIN = main.c

YACC_OUTPUT = y.tab.c y.tab.h
LEX_OUTPUT = lex.yy.c

OBJS = main.o util.o scan.o 
#OBJS_LEX = main.o util.o lex.yy.o

.PHONY: all clean
#all: cminus_cimpl cminus_lex
all: cminus_cimpl

clean:
	-rm -vf cminus_cimpl *.o

cminus_cimpl: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) 

#cminus_lex: $(YACC_OUTPUT) $(LEX_OUTPUT) $(MAIN)
#	$(CC) $(CFLAGS) -o $@ $(YACC_OUTPUT) $(LEX_OUTPUT) $(MAIN) $(LIBS)

$(YACC_OUTPUT): $(PARSER)
	$(YACC) -d $<

$(LEX_OUTPUT): $(LEXER)
	$(LEX) $<

main.o: main.c globals.h util.h scan.h
	$(CC) $(CFLAGS) -c -o $@ $<

scan.o: scan.c globals.h util.h scan.h
	$(CC) $(CFLAGS) -c -o $@ $<

util.o: util.c globals.h util.h
	$(CC) $(CFLAGS) -c -o $@ $<

lex.yy.o: lex.yy.c globals.h util.h scan.h
	$(CC) $(CFLAGS) -c -o $@ $<

lex.yy.c: cminus.l
	flex -o $@ $<

