/* receive.c - receive */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return it
 *------------------------------------------------------------------------
 */
SYSCALL	receive()
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][6][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	struct	pentry	*pptr;
	WORD	msg;

	disable(ps);
	pptr = &proctab[currpid];
	if ( !pptr->phasmsg ) {		/* if no message, wait for one	*/
		pptr->pstate = PRRECV;
		resched();
	}
	msg = pptr->pmsg;		/* retrieve message		*/
	pptr->phasmsg = FALSE;
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][6][0] == 0){
               syscall_info[currpid][6][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][6][1] = (((syscall_info[currpid][6][0] - 1) * syscall_info[currpid][6][1]) + (stop_time - start_time))/syscall_info[currpid][6][0];
           }
        }

	return(msg);
}
