#ifndef _yy_defines_h_
#define _yy_defines_h_

#define K_INT 257
#define K_FLOAT 258
#define K_CHAR 259
#define FOR 260
#define WHILE 261
#define ELSE 262
#define IF 263
#define SWITCH 264
#define CASE 265
#define RETURN 266
#define CONTINUE 267
#define BREAK 268
#define DEFAULT 269
#define INTEGER 270
#define FLOAT 271
#define CHARACTER 272
#define STRING 273
#define IDENTIFIER 274
#define AND 275
#define OR 276
#define GE 277
#define LE 278
#define EQ 279
#define NE 280
#define EOF_TOKEN 281
#define ERROR 282
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE {
    int iValue;
    float fValue;
    char* sValue;
    IdStruct id;
    char cValue;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
