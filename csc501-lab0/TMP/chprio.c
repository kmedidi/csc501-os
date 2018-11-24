/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
SYSCALL chprio(int pid, int newprio)
{
        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][1][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		return(SYSERR);
	}
	pptr->pprio = newprio;
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][1][0] == 0){
               syscall_info[currpid][1][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][1][1] = (((syscall_info[currpid][1][0] - 1) * syscall_info[currpid][1][1]) + (stop_time - start_time))/syscall_info[currpid][1][0];
           }
        }

	return(newprio);
}
