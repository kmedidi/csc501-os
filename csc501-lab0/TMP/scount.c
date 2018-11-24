/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <proc.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][10][0];
           start_time = ctr1000;
        }

extern	struct	sentry	semaph[];

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][10][0] == 0){
               syscall_info[currpid][10][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][10][1] = (((syscall_info[currpid][10][0] - 1) * syscall_info[currpid][10][1]) + (stop_time - start_time))/syscall_info[currpid][10][0];
           }
        }

	if (isbadsem(sem) || semaph[sem].sstate==SFREE)
		return(SYSERR);
	return(semaph[sem].semcnt);
}
