/****************************************************/
/* File: pass1.c                                    */
/* The Pass1 implimentation for SIC assembler	    */
/* System Software Mini-Project			    */
/*           ZEBRA                                  */
/****************************************************/

#include "globals.h"
#include "pass1.h"
#include "symtab.h"
#include "optab.h"

int atoh (char s[]);
void readnextLine ();
char LABEL[20], OPCODE[20], OPERAND[20], w;
char wl[100];


void
pass1 ()
{

  readnextLine ();
  if (strcmp (OPCODE, "START") == 0)
    {
      start_addr = atoh (OPERAND);
      locctr = start_addr;
      fprintf (inter, "%X\t%s\t%s\t%s\n", locctr, LABEL, OPCODE, OPERAND);
      readnextLine ();
    }
  else
    locctr = 0;

  while (strcmp (OPCODE, "END") != 0)
    {
      if (strcmp (LABEL, "-") != 0)
	{
	  if (st_lookup (LABEL))
	    {
	      fprintf (stderr, "duplicate symbol %s\n", LABEL);
	      Error = 1;
	    }
	  else
	    {
	      st_insert (LABEL, locctr);
	    }
	}

      fprintf (inter, "%X\t%s\t%s\t%s\n", locctr, LABEL, OPCODE, OPERAND);
      if (opcodeLookup (OPCODE) == 1)
	locctr = locctr + 3;
      else if (strcmp (OPCODE, "WORD") == 0)
	locctr = locctr + 3;
      else if (strcmp (OPCODE, "RESW") == 0)
	locctr = locctr + (3 * atoi (OPERAND));
      else if (strcmp (OPCODE, "RESB") == 0)
	locctr = locctr + atoi (OPERAND);
      else if (strcmp (OPCODE, "BYTE") == 0)
	{
	  if (OPERAND[0] == 'C')
	    locctr = locctr + (strlen (OPERAND) - 3);
	  else
	    locctr = locctr + 1;
	}
      else
	{
	  fprintf (stderr, "invalid opcode %s", OPCODE);
	  Error = 1;
	}

      readnextLine ();

    }

  fprintf (inter, "%X\t%s\t%s\t%s\n", locctr, LABEL, OPCODE, OPERAND);
  pgm_length = locctr - start_addr;

  if (EchoSymTab)
    {
      printf ("Echo:Symbol Table\n");
      printSymTab ();
    }
}

/*ascii to hexa*/
int
atoh (char s[])
{
  int i, n, sign;
  for (i = 0; isspace (s[i]); i++);
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  /* skip white space */
  /* skip sign */
  for (n = 0; isdigit (s[i]); i++)
    n = 16 * n + (s[i] - '0');
  return sign * n;
}

/*Read next Line from Source File*/
void
readnextLine ()
{
  w = getc (source);
  if (w == '.' || w == '\0')
    {
      fgets (wl, 100, source);
      readnextLine ();
    }
  else
    {
      ungetc (w, source);
      fscanf (source, "%s%s%s\n", LABEL, OPCODE, OPERAND);
    }
}
