/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the SIC assembler     */
/* System Software Mini-Project			    */
/*           ZEBRA                                  */
/****************************************************/
#ifndef _SYMTAB_H_
#define _SYMTAB_H_

struct SymTab
   { char label[20];
     int memloc ; /* memory location for variable */
     struct SymTab * next;
   } ;
/* Procedure st_insert inserts label and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time,
 */
void st_insert( char * name, int loc );

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name1 );

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab();

int getAddr( char* name1 );

#endif
