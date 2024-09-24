# Makefile for C-Minus Scanner

CC = gcc
CFLAGS = -W -Wall
LEX = flex
YACC = yacc
LIBS = -lfl -lm

# Source files
PARSER = parser.y
LEXER = cminus.l
MAIN = main.c
UTIL = util.c
SYMBOL = symbol.h

# Output executable name
EXECUTABLE = cminus_lex
YACC_OUTPUT = y.tab.c y.tab.h
LEX_OUTPUT = lex.yy.c

.PHONY: all clean

# Default target
all: $(EXECUTABLE)

# Build the executable
$(EXECUTABLE): $(SYMBOL) $(YACC_OUTPUT) $(LEX_OUTPUT) $(MAIN) $(UTIL)
	$(CC) $(CFLAGS) -o $@ $(SYMBOL) $(YACC_OUTPUT) $(LEX_OUTPUT) $(MAIN) $(UTIL) $(LIBS)

# Generate parser and header files
$(YACC_OUTPUT): $(PARSER)
	$(YACC) -d $<

# Generate lexer source file
$(LEX_OUTPUT): $(LEXER)
	$(LEX) -o $@ $<

clean:
	-rm -vf $(EXECUTABLE) $(YACC_OUTPUT) $(LEX_OUTPUT) *.o

