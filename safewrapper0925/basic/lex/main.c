#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#include "y.tab.h"
#include "globals.h"
#include "util.h"
#include "scan.h"

//FILE *source;
extern int lineno;
extern FILE *yyin;
//extern FILE *yyout;
//extern FILE *listing;
// Current token's lexeme
extern char *yytext;
// The source file name
extern char *currentFileName;
// From lex.yy.c, returns the next token.
// Ends with EOF
int yylex();
void printToken(int, const char*);

int main(int argc, char* argv[])
{
  char pgm[120];
  if (argc != 2)
  {
    printf("usage: %s <filename>\n", argv[0]);
    exit(1);
  }
  strncpy(pgm, argv[1], strlen(argv[1])+1);
  yyin = fopen(pgm, "r");
  if (yyin == NULL)
  {
    printf("File %s not found.\n", pgm);
    exit(1);
  }

  int currentToken;
  int TraceScan = 1;
  while (1)
  {
    currentToken = yylex();
    if(currentToken == EOF_TOKEN) break;
    strncpy(tokenString, yytext, MAXTOKENLEN);
    if (TraceScan){ // TraceScan in expression?
	printToken(currentToken, tokenString);
    }

    //printf("(test and debug) Token: %d: '%s'\n", currentToken, yytext);
  }
  if(currentToken == EOF_TOKEN) printToken(currentToken, "EOF");
  //printf("EOF\n");
  return 0;
}

