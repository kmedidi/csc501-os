/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <date.h>
#include <lab0.h>

extern unsigned long ctr1000;
extern int getutim(unsigned long *);

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
SYSCALL	gettime(long *timvar)
{
    /* long	now; */

	/* FIXME -- no getutim */
        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][4][0];
           start_time = ctr1000;
        }

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][4][0] == 0){
               syscall_info[currpid][4][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][4][1] = (((syscall_info[currpid][4][0] - 1) * syscall_info[currpid][4][1]) + (stop_time - start_time))/syscall_info[currpid][4][0];
           }
        }

    return OK;
}
