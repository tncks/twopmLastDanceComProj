#include "globals.h"
#include "util.h"
#include "symbol.h"
#include "y.tab.h"

void printToken( int token, const char* tokenString )
{ switch (token)
  { 
    case IF:
    case ELSE:
    case WHILE:
    case RETURN:
    case K_INT:
    case VOID:
      printf("reserved word: %s\n",tokenString);
      break;
    case EQ: printf("==\n"); break;
    case NE: printf("!=\n"); break;
    case GE: printf(">=\n"); break;
    case LE: printf("<=\n"); break;
    case 40: printf("(\n"); break; // 40 -> LPAREN
    case 41: printf(")\n"); break; // 41 -> RPAREN
    case 42: printf("*\n"); break; // 42 -> STAR
    case 43: printf("+\n"); break; // 43 -> PLUS
    case 44: printf(",\n"); break; // 44 -> COMMA
    case 45: printf("-\n"); break; // 45 -> MINUS
    case 47: printf("/\n"); break; // 47 -> SLASH
    case 59: printf(";\n"); break; // 59 -> SEMI
    case 60: printf("<\n"); break; // 60 -> LT
    case 61: printf("=\n"); break; // 61 -> ASSIGN
    case 62: printf(">\n"); break; // 62 -> GT
    case 91: printf("[\n"); break; // 91 -> LBRAKET
    case 93: printf("]\n"); break; // 93 -> RBRAKET
    case 123: printf("{\n"); break; // 123 -> LCURLY
    case 125: printf("}\n"); break; // 125 -> RCURLY
    case EOF_TOKEN: printf("EOF\n"); break;
    case INTEGER:
      printf(
          "NUM, val= %s\n",tokenString);
      break;
    case IDENTIFIER:
      printf(
          "ID, name= %s\n",tokenString);
      break;
    case ERROR:
      printf(
          "ERROR: %s\n",tokenString);
      break;
    default: /* should never happen */
      printf("Unknown token: %d\n",token);
  }
}
