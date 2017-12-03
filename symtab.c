/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the SIC assembler*/
/* System Software Mini-Project			    */
/*           ZEBRA                                  */
/****************************************************/

#include "symtab.h"
#include "globals.h"

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */


struct SymTab *
getnode ()
{
  return ((struct SymTab *) malloc (sizeof (struct SymTab)));
}

static struct SymTab *head = NULL;
static struct SymTab *tail = NULL;
static struct SymTab *temp;

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void
st_insert (char *name, int loc)
{

  if (head == NULL)
    {
      head = tail = getnode ();
      strcpy (head->label, name);
      head->memloc = loc;
      head->next = NULL;
      fprintf (symbol, "Label_Name  Location  \n");
      fprintf (symbol, "----------  --------  \n");
      fprintf (symbol, "%-14s ", head->label);
      fprintf (symbol, "%-8X  ", head->memloc);
      fprintf (symbol, "\n");
    }
  else
    {

      temp = getnode ();
      strcpy (temp->label, name);
      temp->memloc = loc;
      temp->next = NULL;
      tail->next = temp;
      tail = temp;
      fprintf (symbol, "%-14s ", temp->label);
      fprintf (symbol, "%-8X  ", temp->memloc);
      fprintf (symbol, "\n");
    }

}				/* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int
st_lookup (char *name1)
{
  temp = head;
  while (temp != NULL)
    {
      if (strcmp (name1, temp->label) == 0)
	return 1;
      else
	temp = temp->next;
    }
  return 0;
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void
printSymTab ()
{
  temp = head;
  fprintf (listing, "Label Name  Location  \n");
  fprintf (listing, "----------  --------  \n");
  while (temp != NULL)
    {
      fprintf (listing, "%-14s ", temp->label);
      fprintf (listing, "%-8X  ", temp->memloc);

      fprintf (listing, "\n");
      temp = temp->next;
    }
}				/* printSymTab */

/* Function getAddr returns address of the 
*   symbol in Symtab*
*/
int
getAddr (char *name1)
{
  temp = head;
  while (temp != NULL)
    {
      if (strcmp (name1, temp->label) == 0)
	return temp->memloc;
      else
	temp = temp->next;
    }
  return 0;
}
