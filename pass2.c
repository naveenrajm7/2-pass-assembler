/****************************************************/
/* File: pass2.c                                    */
/* The Pass2 implimentation for SIC assembler	    */
/* System Software Mini-Project			    */
/*           ZEBRA                                  */
/****************************************************/

#include "globals.h"
#include "pass2.h"
#include "symtab.h"
#include "optab.h"


char ILABEL[20], IOPCODE[20], IOPERAND[20], c;
int IADDR;
int ROPCODE, RADDR;

void
pass2 ()
{
  int *t;
  t = (int *) malloc (sizeof (int) * 20);
  int n = 0, j;

  int cnt = 0;
  fscanf (inter, "%X%s%s%s", &IADDR, ILABEL, IOPCODE, IOPERAND);

  if (strcmp (IOPCODE, "START") == 0)
    {
      fprintf (objpgm, "H^%-6s^%06X^%06X", ILABEL, start_addr, pgm_length);
      fscanf (inter, "%X%s%s%s", &IADDR, ILABEL, IOPCODE, IOPERAND);
    }
  else
    {
      fprintf (objpgm, "\nH%-6s%6X%6X", ILABEL, 0, pgm_length);
      fscanf (inter, "%X%s%s%s", &IADDR, ILABEL, IOPCODE, IOPERAND);
    }

  while (strcmp (IOPCODE, "END") != 0)
    {
      if (cnt == 0 && strcmp (IOPCODE, "RESB") && strcmp (IOPCODE, "RESW"))
	{

	  fprintf (objpgm, "\nT^%06X^__", IADDR);
	  n = n + 1;
	  cnt = cnt + 9;
	}
      else
	{
	}
      if (opcodeLookup (IOPCODE) == 1)
	{
	  ROPCODE = getOpcode (IOPCODE);
	  if (strcmp (IOPERAND, "-") != 0)
	    {
	      RADDR = getAddr (IOPERAND);
	    }
	  else
	    RADDR = 0;
	  if (cnt + 6 <= 69)
	    {
	      fprintf (objpgm, "^%02X%04X", ROPCODE, RADDR);
	      cnt = cnt + 6;
	    }
	  else
	    {
	      *(t + n) = (cnt - 9) / 2;
	      cnt = 0;
	      fprintf (objpgm, "\nT^%06X^__^%02X%4X", IADDR, ROPCODE, RADDR);
	      n = n + 1;
	      cnt = cnt + 15;
	    }
	}
      else if (strcmp (IOPCODE, "WORD") == 0)
	{
	  ROPCODE = atoi (IOPERAND);
	  if (cnt + 6 <= 69)
	    {
	      fprintf (objpgm, "^%06X", ROPCODE);
	      cnt = cnt + 6;
	    }
	  else
	    {
	      *(t + n) = (cnt - 9) / 2;
	      cnt = 0;
	      fprintf (objpgm, "\nT^%06X^__^%06X", IADDR, ROPCODE);
	      n++;
	      cnt = cnt + 15;
	    }

	}
      else if (strcmp (IOPCODE, "BYTE") == 0)
	{
	  int l, i, temp;
	  l = strlen (IOPERAND);
	  if (cnt + l - 3 > 69)
	    {
	      *(t + n) = (cnt - 9) / 2;
	      cnt = 0;
	      fprintf (objpgm, "\nT^%06X^__", IADDR);
	      cnt = cnt + 9;
	      n++;
	    }
	  fprintf (objpgm, "^");
	  if (IOPERAND[0] == 'C')
	    {
	      for (i = 2; i < l - 1; i++)
		{
		  temp = (int) IOPERAND[i];
		  fprintf (objpgm, "%X", temp);
		  cnt = cnt + 2;
		}
	    }
	  else
	    {
	      //temp=atoi(IOPERAND+2);
	      fprintf (objpgm, "%s", IOPERAND + 2);
	      cnt = cnt + 2;
	    }

	}
      else if ((strcmp (IOPCODE, "RESW") == 0)
	       || (strcmp (IOPCODE, "RESB") == 0))
	{
	  if (cnt != 0)
	    *(t + n) = (cnt - 9) / 2;
	  cnt = 0;
	}
      else
	{
	  fprintf (stderr, "invalid opcode %s", IOPCODE);
	  Error = 1;
	}

      fscanf (inter, "%X%s%s%s", &IADDR, ILABEL, IOPCODE, IOPERAND);
    }

  if (cnt != 0)
    *(t + n) = (cnt - 9) / 2;

  fprintf (objpgm, "\nE^%06X", start_addr);	//end record

/*Text record lengths
	for(j=1;j<=n;j++)
	{
		printf("%X\n",*(t+j));
	}
*/
  fclose (objpgm);

  objpgm = fopen ("objpgm", "r+");

  //Adding text record length
  for (j = 1; j <= n; j++)
    {
      c = getc (objpgm);
      while (c != '_')
	c = getc (objpgm);
      ungetc (c, objpgm);
      fprintf (objpgm, "%02X", t[j]);
    }



}
