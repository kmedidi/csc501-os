/* sreset.c - sreset */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  sreset  --  reset the count and queue of a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL sreset(int sem, int count)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][22][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	struct	sentry	*sptr;
	int	pid;
	int	slist;

	disable(ps);
	if (isbadsem(sem) || count<0 || semaph[sem].sstate==SFREE) {
		restore(ps);
		return(SYSERR);
	}
	sptr = &semaph[sem];
	slist = sptr->sqhead;
	while ((pid=getfirst(slist)) != EMPTY)
		ready(pid,RESCHNO);
	sptr->semcnt = count;
	resched();
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][22][0] == 0){
               syscall_info[currpid][22][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][22][1] = (((syscall_info[currpid][22][0] - 1) * syscall_info[currpid][22][1]) + (stop_time - start_time))/syscall_info[currpid][22][0];
           }
        }

	return(OK);
}
