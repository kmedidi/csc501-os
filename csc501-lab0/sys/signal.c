/* signal.c - signal */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * signal  --  signal a semaphore, releasing one waiting process
 *------------------------------------------------------------------------
 */
SYSCALL signal(int sem)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][16][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	register struct	sentry	*sptr;

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
		return(SYSERR);
	}
	if ((sptr->semcnt++) < 0)
		ready(getfirst(sptr->sqhead), RESCHYES);
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][16][0] == 0){
               syscall_info[currpid][16][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][16][1] = (((syscall_info[currpid][16][0] - 1) * syscall_info[currpid][16][1]) + (stop_time - start_time))/syscall_info[currpid][16][0];
           }
        }

	return(OK);
}
