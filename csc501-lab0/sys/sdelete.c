/* sdelete.c - sdelete */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * sdelete  --  delete a semaphore by releasing its table entry
 *------------------------------------------------------------------------
 */
SYSCALL sdelete(int sem)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][11][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	int	pid;
	struct	sentry	*sptr;

	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE) {
		restore(ps);
		return(SYSERR);
	}
	sptr = &semaph[sem];
	sptr->sstate = SFREE;
	if (nonempty(sptr->sqhead)) {
		while( (pid=getfirst(sptr->sqhead)) != EMPTY)
		  {
		    proctab[pid].pwaitret = DELETED;
		    ready(pid,RESCHNO);
		  }
		resched();
	}
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][11][0] == 0){
               syscall_info[currpid][11][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][11][1] = (((syscall_info[currpid][11][0] - 1) * syscall_info[currpid][11][1]) + (stop_time - start_time))/syscall_info[currpid][11][0];
           }
        }

	return(OK);
}
