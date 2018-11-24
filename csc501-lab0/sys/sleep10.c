/* sleep10.c - sleep10 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * sleep10  --  delay the caller for a time specified in tenths of seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep10(int n)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][19][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	if (n < 0  || clkruns==0)
	         return(SYSERR);
	disable(ps);
	if (n == 0) {		/* sleep10(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*100);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][19][0] == 0){
               syscall_info[currpid][19][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][19][1] = (((syscall_info[currpid][19][0] - 1) * syscall_info[currpid][19][1]) + (stop_time - start_time))/syscall_info[currpid][19][0];
           }
        }

	return(OK);
}
