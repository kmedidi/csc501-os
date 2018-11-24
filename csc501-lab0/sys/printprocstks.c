#include <kernel.h>
#include <proc.h>
#include <stdio.h>

static unsigned long *esp;

/*----------------------------------------------------------------------------------------
 * * Function to print the process parameters if the priority is greater than the given value
 * *-----------------------------------------------------------------------------------------
 * */

void printprocstks(int priority)
{
  int i;
  struct pentry *proc; 
  asm("movl %esp,esp");
  kprintf("\nOutput of printprocstks()");
  for(i=0; i<NPROC; i=i+1){
    proc = &proctab[i];
    if(proc->pprio >= priority){
       kprintf("\nProcess [%s]",proc->pname);
       kprintf("\nPID:%d", i);
       kprintf("\nPriority:%d", proc->pprio);
       kprintf("\nBase:0x%08x", proc->pbase);
       kprintf("\nLimit:0x%08x", proc->plimit);
       kprintf("\nLen:%d", proc->pstklen);
       if(i == currpid){
          kprintf("\nPointer:0x%08x", esp);
       }
       else{
          kprintf("\nPointer:0x%08x", proc->pesp);
       }
    }
  }
}
