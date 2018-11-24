/* resume.c - resume */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * resume  --  unsuspend a process, making it ready; return the priority
 *------------------------------------------------------------------------
 */
SYSCALL resume(int pid)
{
        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][9][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority to return		*/

	disable(ps);
	if (isbadpid(pid) || (pptr= &proctab[pid])->pstate!=PRSUSP) {
		restore(ps);
		return(SYSERR);
	}
	prio = pptr->pprio;
	ready(pid, RESCHYES);
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][9][0] == 0){
               syscall_info[currpid][9][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][9][1] = (((syscall_info[currpid][9][0] - 1) * syscall_info[currpid][9][1]) + (stop_time - start_time))/syscall_info[currpid][9][0];
           }
        }

	return(prio);
}
