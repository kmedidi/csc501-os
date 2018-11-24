/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{       
        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][18][0];
           start_time = ctr1000;
        } 

	STATWORD ps;    
	if (n<0 || clkruns==0)
		return(SYSERR);
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10*n);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][18][0] == 0){
               syscall_info[currpid][18][1] = stop_time - start_time; 
           }
           else{
               syscall_info[currpid][18][1] = (((syscall_info[currpid][18][0] - 1) * syscall_info[currpid][18][1]) + (stop_time - start_time))/syscall_info[currpid][18][0];
           }
        }
        
        return(OK);
}
