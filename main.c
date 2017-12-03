/****************************************************/
/* File: main.c                                     */
/* Main program for SIC assembler                   */
/* System Software Mini-Project	  	            */
/*          ZEBRA  	                            */
/****************************************************/

#include "globals.h"

/* set PASS1 to TRUE to get a PASS1-only assembler */
#define PASS1 FALSE

#include "symtab.h"
#include "optab.h"
#include "pass1.h"
#include "pass2.h"
/* allocate global variables */
int locctr ;
int start_addr;/*starting address*/
int pgm_length;/*Program length*/

FILE * source;
FILE * listing;
FILE * inter; /* intermediate file  */
FILE * objpgm;/* Object program */
FILE * symbol;


/* allocate and set tracing flags */
int EchoSymTab = TRUE;


int Error = FALSE;

int main( int argc, char * argv[] )
{ 
  
  char pgm[120]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  if (strchr (pgm, '.') == NULL)
     strcat(pgm,".sic");
  source = fopen(pgm,"r");
  inter = fopen("inter","w");
  symbol=fopen("symtab.txt","w");
  if (source==NULL)
  { fprintf(stderr,"File %s not found\n",pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing,"\nSIC COMPILATION: %s\n",pgm);

  pass1();
  fclose(inter);
  fclose(symbol);
  
  
#if !PASS1
  inter=fopen("inter","r");
  objpgm=fopen("objpgm","w+");
  pass2();
#else
  
#endif
  fclose(source);
  fclose(objpgm);
  return 0;
}

