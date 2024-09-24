%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "symbol.h"
#include "y.tab.h"
#include "globals.h" //added
#include "util.h"
#include "scan.h"

#define MAX_STR_CONST 1000
#define yyterminate() return EOF_TOKEN
#define YY_USER_ACTION \
  col += yyleng;
extern char *currentFileName;
char tokenString[MAXTOKENLEN+1];
int col = 1;
int lineno = 1;
int yyerror(char* s);

void point_at_in_line(int lineno, int from, int to);

%}

alpha [a-zA-Z]
alphanum [a-zA-Z0-9]
digit [0-9]
nonzero [1-9]

%x comment

%%

  /* Keywords */
"int" { return K_INT;} 
"while" { return WHILE;} 
"else" { return ELSE;} 
"if" { return IF;} 
"return" { return RETURN;}
"void" { return VOID;}
  /* */

[-+*/] return *yytext;
[;,()] return *yytext;
[\{\}\[\]] return *yytext;
[=<>] return *yytext;
  
"==" { return EQ;}
">=" { return GE;}
"<=" { return LE;}
"!=" { return NE;}


 /* Identifiers */
(_|{alpha})((_|{alphanum}))* {
  yylval.id.name = malloc(strlen(yytext)+1);
  yylval.id.line = lineno;
  yylval.id.col = col - yyleng;
  strcpy(yylval.id.name, yytext);
  return IDENTIFIER;  
}

  /* Integers */
0 { yylval.iValue = 0; return INTEGER;}
{nonzero}({digit})*([eE][-+]?[0-9]+)? { yylval.iValue = (int)round(atof(yytext)); return INTEGER;}

  /* Comments*/

"/*" BEGIN(comment);
<comment>"\n" { col = 1; lineno++;}
<comment>"*/" { BEGIN(INITIAL);}
<comment><<EOF>> { BEGIN(INITIAL); return EOF_TOKEN;}
<comment>. ;

  /* Whitespace */
[ \t\r] ;
\n { col = 1; lineno++;}

. { yyerror("Error: Invalid character"); return ERROR;}


%%
int yywrap(){
  yyterminate();
  return EOF_TOKEN;
}

int yyerror(char *s){
  fprintf(stderr,  "%s[%d:%d] " "%s"  " at '%s'\n", currentFileName, lineno, col-1, s, yytext);
  point_at_in_line(lineno-1, col - yyleng-2, col-2);
  exit(1);
}

char *getlineat(int lineno)
{
  FILE *file = fopen(currentFileName, "r");
  // read the line `lineno` from file
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0;
  while ((read = getline(&line, &len, file)) != -1)
  {
    if (i == lineno)
    {
      return line;
    }
    i++;
  }
  return (char*)0;
}


void point_at_in_line(int lineno, int from, int to)
{
  // print the line and show a caret from bottom line at position `col`
  char *line = getlineat(lineno);
  if(!line || strlen(line) == 0){
    fprintf(stderr, "\tError at [End of file]\n");
    return;
  }
  // Recover silently and gracefully in invalid inputs
  if (from > to)
  {
    int temp = from;
    from = to;
    to = temp;
  }
  if (strlen(line) < to)
  {
    to = strlen(line);
  }
  if (strlen(line) < from)
  {
    from = strlen(line);
  }
  from = (from < 0) ? 0 : from;
  // print all characters till 'from'
  fprintf(stderr, "   %d | %.*s", lineno+1, from, line);
  // color characters enclosed in from-to with red and boldface
  fprintf(stderr, "\e[31;1m%.*s\e[0m", to - from, line + from);
  // print all characters from 'to' till end of line
  fprintf(stderr, "%s", line + to);

  //check if last character was newline, if not print it
  if(line[strlen(line)-1] != '\n'){
    fprintf(stderr, "\n");
  }

  //find number of digits in lineno for the left offset
  int offset = 0;
  lineno++;
  while((lineno) > 0){
    offset++;
    lineno /= 10;
  }
  //add the left padding
  offset+=3;
  while(offset--){
    fprintf(stderr, " ");
  }
  fprintf(stderr, " | ");

  for (int i = 0; i < from; i++)
  {
    fprintf(stderr, " ");
  }
  //place the caret
  fprintf(stderr, "\e[32;1m"  "^");
  //underline the rest of the characters
  for(int i=from; i < to-1; i++){
    fprintf(stderr, "~");
  }
  fprintf(stderr,  "\n");
}
