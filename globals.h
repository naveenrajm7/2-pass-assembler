/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for SIC assembler          */
/* must come before other include files             */
/* System Software Mini-Project			    */
/*           ZEBRA                                  */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXOP = the number of Operation codes */
#define MAXOP 26



extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* inter; /* intermediate file  */
extern FILE* objpgm;/* Object program */
extern FILE* symbol;/*symtab*/

extern int locctr; /* source line number for listing */
extern int start_addr;/*starting address*/
extern int pgm_length;/*Program length*/


/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/


/* EchoSymTab = TRUE SymTab to be echoed
 * to the listing file during pass1
 */
extern int EchoSymTab;


extern int Error; 
#endif
