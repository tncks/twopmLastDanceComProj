#ifndef _yy_defines_h_
#define _yy_defines_h_

#define K_INT 257
#define WHILE 258
#define ELSE 259
#define IF 260
#define RETURN 261
#define VOID 262
#define INTEGER 263
#define IDENTIFIER 264
#define GE 265
#define LE 266
#define EQ 267
#define NE 268
#define EOF_TOKEN 269
#define ERROR 270
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE {
    int iValue;
    struct id_{ unsigned int line; unsigned int col; unsigned int length; char* name; } id;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
