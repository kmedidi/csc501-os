/* printtos.c - printtos */
#include <stdio.h>
#include <kernel.h>
#include <proc.h>

static unsigned long *ebp;

/*---------------------------------------------------------------------------------
 * * Prints the contents of current, Preceeding and Succeeding to top of stack;
 * * Prints the contents of the stack upto four locations from top
 * *------------------------------------------------------------------------------------
 * */

void printtos()
{
  int i;
  asm("movl %ebp,ebp");
  kprintf("\nOutput of printtos()");
  kprintf("\nBefore[0x%08x]=0x%08x", ebp + 2, *(ebp + 2));
  kprintf("\nAfter[0x%08x]=0x%08x\n", ebp, *(ebp));
  
  for(i=1; i<=4; i=i+1){
     kprintf("\nContents[0x%08x]=0x%08x", ebp - i, *(ebp - i));
     }
}
