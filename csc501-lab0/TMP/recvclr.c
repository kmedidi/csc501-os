/* recvclr.c - recvclr */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  recvclr  --  clear messages, returning waiting message (if any)
 *------------------------------------------------------------------------
 */
SYSCALL	recvclr()
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][7][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	WORD	msg;

	disable(ps);
	if (proctab[currpid].phasmsg) {
		proctab[currpid].phasmsg = 0;
		msg = proctab[currpid].pmsg;
	} else
		msg = OK;
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][7][0] == 0){
               syscall_info[currpid][7][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][7][1] = (((syscall_info[currpid][7][0] - 1) * syscall_info[currpid][7][1]) + (stop_time - start_time))/syscall_info[currpid][7][0];
           }
        }

	return(msg);
}
