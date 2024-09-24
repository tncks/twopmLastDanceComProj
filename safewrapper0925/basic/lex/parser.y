%{
#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"



char *currentFileName;
extern int lineno, col;
int yyerror(char *s);
int yylex();
%}

%union {
    int iValue;
    struct id_{ unsigned int line; unsigned int col; unsigned int length; char* name; } id;
};


/* Keywords */
%token <iValue> K_INT/*K_FLOAT K_CHAR*/ 
%token /*FOR*/ WHILE ELSE IF /*SWITCH CASE*/ RETURN /*CONTINUE BREAK DEFAULT*/ VOID
/* Literals */
%token <iValue> INTEGER
/*%token <fValue> FLOAT
%token <cValue> CHARACTER
%token <sValue> STRING*/
/* Variables and functions */
%token <id> IDENTIFIER
/* Operators && || >= <= == != */
%token /*AND OR */GE LE EQ NE
/* Other operators are returned as ASCII */

/* End of file token */
%token EOF_TOKEN ERROR

%%
/* Dummy grammar */
program: IDENTIFIER;
%%
// Error routine
/*int yyerror(char *s){
  exit(1);
  return 1;
} */
