/* setdev.c - setdev */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL	setdev(int pid, int dev1, int dev2)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][13][0];
           start_time = ctr1000;
        }

	short	*nxtdev;

	if (isbadpid(pid))
		return(SYSERR);
	nxtdev = (short *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][13][0] == 0){
               syscall_info[currpid][13][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][13][1] = (((syscall_info[currpid][13][0] - 1) * syscall_info[currpid][13][1]) + (stop_time - start_time))/syscall_info[currpid][13][0];
           }
        }

	return(OK);
}
