/* wait.c - wait */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * wait  --  make current process wait on a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL	wait(int sem)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][26][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	struct	sentry	*sptr;
	struct	pentry	*pptr;

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
		return(SYSERR);
	}
	
	if (--(sptr->semcnt) < 0) {
		(pptr = &proctab[currpid])->pstate = PRWAIT;
		pptr->psem = sem;
		enqueue(currpid,sptr->sqtail);
		pptr->pwaitret = OK;
		resched();
		restore(ps);
		return pptr->pwaitret;
	}
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][26][0] == 0){
               syscall_info[currpid][26][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][26][1] = (((syscall_info[currpid][26][0] - 1) * syscall_info[currpid][26][1]) + (stop_time - start_time))/syscall_info[currpid][26][0];
           }
        }
	return(OK);
}
