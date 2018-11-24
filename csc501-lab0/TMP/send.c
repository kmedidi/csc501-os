/* send.c - send */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  send  --  send a message to another process
 *------------------------------------------------------------------------
 */
SYSCALL	send(int pid, WORD msg)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][12][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || ( (pptr= &proctab[pid])->pstate == PRFREE)
	   || pptr->phasmsg != 0) {
		restore(ps);
		return(SYSERR);
	}
	pptr->pmsg = msg;
	pptr->phasmsg = TRUE;
	if (pptr->pstate == PRRECV)	/* if receiver waits, start it	*/
		ready(pid, RESCHYES);
	else if (pptr->pstate == PRTRECV) {
		unsleep(pid);
		ready(pid, RESCHYES);
	}
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][12][0] == 0){
               syscall_info[currpid][12][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][12][1] = (((syscall_info[currpid][12][0] - 1) * syscall_info[currpid][12][1]) + (stop_time - start_time))/syscall_info[currpid][12][0];
           }
        }

	return(OK);
}
