/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
SYSCALL getprio(int pid)
{
        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][3][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		return(SYSERR);
	}
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][3][0] == 0){
               syscall_info[currpid][3][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][3][1] = (((syscall_info[currpid][3][0] - 1) * syscall_info[currpid][3][1]) + (stop_time - start_time))/syscall_info[currpid][3][0];
           }
        }

	return(pptr->pprio);
}
