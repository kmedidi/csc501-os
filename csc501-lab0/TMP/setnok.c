/* setnok.c - setnok */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  setnok  -  set next-of-kin (notified at death) for a given process
 *------------------------------------------------------------------------
 */
SYSCALL	setnok(int nok, int pid)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][14][0];
           start_time = ctr1000;
        }

	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid)) {
		restore(ps);
		return(SYSERR);
	}
	pptr = &proctab[pid];
	pptr->pnxtkin = nok;
	restore(ps);

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][14][0] == 0){
               syscall_info[currpid][14][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][14][1] = (((syscall_info[currpid][14][0] - 1) * syscall_info[currpid][14][1]) + (stop_time - start_time))/syscall_info[currpid][14][0];
           }
        }

	return(OK);
}
