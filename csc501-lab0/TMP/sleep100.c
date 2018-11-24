/* sleep100.c - sleep100 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * sleep100  --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep100(int n)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][20][0];
           start_time = ctr1000;
        }

	STATWORD ps;    

	if (n < 0  || clkruns==0)
	         return(SYSERR);
	disable(ps);
	if (n == 0) {		/* sleep100(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*10);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][20][0] == 0){
               syscall_info[currpid][20][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][20][1] = (((syscall_info[currpid][20][0] - 1) * syscall_info[currpid][20][1]) + (stop_time - start_time))/syscall_info[currpid][20][0];
           }
        }

	return(OK);
}
