/* signaln.c - signaln */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  signaln -- signal a semaphore n times
 *------------------------------------------------------------------------
 */
SYSCALL signaln(int sem, int count)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][17][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	struct	sentry	*sptr;

	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE || count<=0) {
		restore(ps);
		return(SYSERR);
	}
	sptr = &semaph[sem];
	for (; count > 0  ; count--)
		if ((sptr->semcnt++) < 0)
			ready(getfirst(sptr->sqhead), RESCHNO);
	resched();
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][17][0] == 0){
               syscall_info[currpid][17][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][17][1] = (((syscall_info[currpid][17][0] - 1) * syscall_info[currpid][17][1]) + (stop_time - start_time))/syscall_info[currpid][17][0];
           }
        }

	return(OK);
}
