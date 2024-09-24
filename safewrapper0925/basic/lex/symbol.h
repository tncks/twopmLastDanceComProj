#ifndef __SYMBOL
#define __SYMBOL


// Stores the coordinate in source file
typedef struct
{
  // Length is for an expression
  unsigned int line, col, length;
} Coordinate;

typedef struct
{
  Coordinate src;
  char *name;
} IdStruct;

#endif
