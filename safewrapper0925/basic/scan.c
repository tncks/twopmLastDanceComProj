/****************************************************/
/* File: scan.c                                     */
/* The scanner implementation                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/* states in scanner DFA */
typedef enum
   { START,INASSIGN,INCOMMENT,INCOMMENT_,INNUM,INID,INEQ,INLT,INGT,INNE,INOVER,DONE }
   StateType;

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];

// Constants
//IF,ELSE,WHILE,RETURN,INT,VOID,
const char KWlist[KWLIST_SIZE][7] = {"IF", "ELSE", "WHILE", "RETURN", "INT", "VOID"};
const char KWcode[] = "xilwriv"; // Single character for identifiers

char Look;
extern char Value[MAX_LENGTH];
extern TokenType currentToken;

void GetChar();
void Expected(const char *msg);
int IsAlpha(char ch);
int IsDigit(char ch);
int IsOp(char ch);
void GetName();
void GetNum();
void GetOp();
void SkipWhite();
void Scan();
void Init();
static int Lookup(const char *, int );

/* BUFLEN = length of the input buffer for
   source code lines */
#define BUFLEN 256

static char lineBuf[BUFLEN]; /* holds the current line */
static int linepos = 0; /* current position in LineBuf */
static int bufsize = 0; /* current size of buffer string */
static int EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */

/* getNextChar fetches the next non-blank character
   from lineBuf, reading in a new line if lineBuf is
   exhausted */
static int getNextChar(void)
{ if (!(linepos < bufsize))
  { lineno++;
    if (fgets(lineBuf,BUFLEN-1,source))
    { if (EchoSource) fprintf(listing,"%4d: %s",lineno,lineBuf);
      bufsize = strlen(lineBuf);
      linepos = 0;
      return lineBuf[linepos++];
    }
    else
    { EOF_flag = TRUE;
      return EOF;
    }
  }
  else return lineBuf[linepos++];
}

/* ungetNextChar backtracks one character
   in lineBuf */
static void ungetNextChar(void)
{ if (!EOF_flag) linepos-- ;}

/* lookup table of reserved words */
static struct
{ 
    char* str;
    TokenType tok;
} reservedWords[MAXRESERVED] = {
    {"IF", IF},
    {"ELSE", ELSE},
    {"WHILE", WHILE},
    {"RETURN", RETURN},
    {"INT", INT},
    {"VOID", VOID},
};

/* lookup an identifier to see if it is a reserved word */
/* uses linear search */
static TokenType reservedLookup (char * s)
{ int i;
  for (i=0;i<MAXRESERVED;i++)
    if (!strcmp(s,reservedWords[i].str))
      return reservedWords[i].tok;
  return ID;
}

//


/*simple utils and condition checkers*/
void Init() {
    Look = getchar(); // Initialize Look with first character
}

// Get the next character from input
void GetChar() {
    Look = getchar();
}

// Report an expected character
void Expected(const char *msg) {
    fprintf(stderr, "Expected %s\n", msg);
    exit(1);
}

// Check if character is alphabetic
int IsAlpha(char ch) {
    return isalpha(ch);
}

// Check if character is a digit
int IsDigit(char ch) {
    return isdigit(ch);
}

// Check if character is an operator
int IsOp(char ch) {
    return strchr("+-*/=<>!;,(){}[]", ch) != NULL; // future:todo;more operators as needed
}


//

// Get an identifier
void GetName() {
    int index = 0;
    if (!IsAlpha(Look)) Expected("Name");
    while (IsAlpha(Look) || IsDigit(Look)) {
        if (index < MAX_LENGTH - 1) {
            Value[index++] = toupper(Look); // Convert to uppercase
        }
        GetChar();
    }
    Value[index] = '\0'; // Null-terminate the string
}

// Get a number
void GetNum() {
    int index = 0;
    if (!IsDigit(Look)) Expected("Integer");
    while (IsDigit(Look)) {
        if (index < MAX_LENGTH - 1) {
            Value[index++] = Look;
        }
        GetChar();
    }
    Value[index] = '\0'; // Null-terminate
    currentToken = NUM; // Indicate a number
}

// Get an operator
void GetOp() {
    int index = 0;
    if (!IsOp(Look)) Expected("Operator");
    while (IsOp(Look)) {
        if (index < MAX_LENGTH - 1) {
            Value[index++] = Look;
        }
        GetChar();
    }
    Value[index] = '\0'; // Null-terminate
    currentToken = COMMA; // Indicate operator // change needed here. COMMA -> other.. logic.. switchcase if-else
}

// Skip whitespace characters
void SkipWhite() {
    while (isspace(Look)) {
        GetChar();
    }
}

// Table Lookup
int Lookup(const char *s, int n) {
    for (int i = 0; i < n; i++) {
        if (!strcmp(s,reservedWords[i].str)) {
            return i+1; 
        }
    }
    return -1; // change name to reservedlookup() function name
}



void Scan() {
  StateType state = START; // as first.

  while (Look == '\n') // Consume new lines
        GetChar();

  SkipWhite();
  
  state = START;
  if (state == START) {

    if (IsAlpha(Look)) {
        GetName();
        int k = Lookup(Value, KWLIST_SIZE);
        if (k == -1) {
          currentToken = ID; // Not a keyword
        } else {
		//if k == 1 then currentToken = k-1
          currentToken = (TokenType)(k-1); // Map to appropriate token
        }
        state = DONE;
    } else if (IsDigit(Look)) {
        GetNum();
        state = DONE;
    } else if (IsOp(Look)) {
        GetOp();
        state = DONE;
        currentToken = COMMA; // comment or not (need check and debug once)
    } else {
	//printf("ascii look: %c and decimal %d\n", (char)Look, (int)Look);
	if(Look == -1) currentToken = ENDFILE;
	else {
          Value[0] = Look;
          Value[1] = '\0';
	  GetChar();
	
	}
        //Value[0] = Look;
        //Value[1] = '\0';
        //GetChar();
        state = DONE;
    }

  }

  //SkipWhite
}


/****************************************/
/* the primary function of the scanner  */
/****************************************/
/* function getToken returns the 
 * next token in source file
 */
/*TokenType getToken(void) //temporary disabled
{  
   int tokenStringIndex = 0;
   
   //TokenType currentToken; //changed on top of file -> global var declared: currentToken
   
   StateType state = START;
   
   int save; // TRUE or FALSE

   //START,INASSIGN,INCOMMENT,INCOMMENT_,INNUM,INID,INEQ,INLT,INGT,INNE,INOVER,DONE .
   
   while (state != DONE)
   { int c = getNextChar();
     save = TRUE;
     switch (state)
     { case START:
         if (...)
           state = ...;
         else if (...)
           state = ...;
         else if (...)
           state = ...;
         else if (...)
           save = ...;
         else if (...)
         { save = ...;
           state = ...;
         }
         else
         { state = DONE;
           switch (c)
           { case EOF:
               save = ...;
               currentToken = ...;
               break;
             case ...:
               currentToken = ...;
               break;
             case ...:
               currentToken = ...;
               break;
             case ...:
               currentToken = ...;
               break;
             case ...:
               currentToken = ...;
               break;
             case ...:
               currentToken = ...;
               break;
             case ...:
               currentToken = ...;
               break;
             case ...:
               currentToken = ...;
               break;
             case ...:
               currentToken = ...;
               break;
             case ...:
               currentToken = ...;
               break;
             case ...:
               currentToken = ...;
               break;
             default:
               currentToken = ERROR;
               break;
           }
         }
         break;
       case INCOMMENT:
         save = ...;
         if (...)
         { state = ...;
           currentToken = ...;
         }
         else if (...) state = ...;
         break;
       case ...:
         state = ...;
         if (...)
           currentToken = ...;
         else
         { 
           ungetNextChar();
           save = ...;
           currentToken = ...;
         }
         break;
       case ...:
         if (...)
         { 
           ungetNextChar();
           save = ...;
           state = ...;
           currentToken = ...;
         }
         break;
       case ...:
         if (...)
         { 
           ungetNextChar();
           save = ...;
           state = ...;
           currentToken = ...;
         }
         break;
       case DONE:
       default: 
         fprintf(listing,"Scanner Bug: state= %d\n",state);
         state = DONE;
         currentToken = ERROR;
         break;
     }
     if ((save) && (tokenStringIndex <= MAXTOKENLEN))
       tokenString[tokenStringIndex++] = (char) c;
     if (state == DONE)
     { tokenString[tokenStringIndex] = '\0';
       if (currentToken == ID)
         currentToken = reservedLookup(tokenString);
     }
   }
   if (TraceScan) {
     fprintf(listing,"\t%d: ",lineno);
     printToken(currentToken,tokenString);
   }
   return currentToken;
}*/

