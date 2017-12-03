/****************************************************/
/* File: optab.h                                    */
/* The optab interface for the SIC assembler        */
/* System Software Mini-Project			    */
/*           ZEBRA                                  */
/****************************************************/
#ifndef _OPTAB_H_
#define _OPTAB_H_


/* function opcodeLookup returns the 
 * opcode if found -1 otherwise
 */
 int opcodeLookup (char * s);
 int getOpcode (char * s);

#endif
