/****************************************************/
/* File: optab.c                                    */
/* The Optab implementation for SIC assembler	    */
/* System Software Mini-Project			    */
/*           ZEBRA                                  */
/****************************************************/
#include "globals.h"
#include "optab.h"


/* lookup table of reserved words */
static struct
{
  char *nemonic;
  int opcode;
} OpTab[MAXOP] =
{
"ADD", 0x18,
    "AND", 0x40,
    "COMP", 0x28,
    "DIV", 0x24,
    "J", 0x3C,
    "JEQ", 0x30,
    "JGT", 0x34,
    "JLT", 0x38,
    "JSUB", 0x48,
    "LDA", 0x00,
    "LDCH", 0x50,
    "LDL", 0x08,
    "LDX", 0x04,
    "MUL", 0x20,
    "OR", 0x44,
    "RD", 0xD8,
    "RSUB", 0x4C,
    "STA", 0x0C,
    "STCH", 0x54,
    "STL", 0x14,
    "STSW", 0xE8,
    "STX", 0x10, "SUB", 0x1C, "TD", 0xE0, "TIX", 0x2C, "WD", 0xDC};

/* function opcodeLookup returns the 
 * opcode if found -1 otherwise
 */
/* uses linear search */
int
opcodeLookup (char *s)
{
  int i;
  for (i = 0; i < MAXOP; i++)
    if (!strcmp (s, OpTab[i].nemonic))
      return 1;
  return 0;
}

int
getOpcode (char *s)
{
  int i;
  for (i = 0; i < MAXOP; i++)
    if (!strcmp (s, OpTab[i].nemonic))
      return OpTab[i].opcode;
  return 0;
}
