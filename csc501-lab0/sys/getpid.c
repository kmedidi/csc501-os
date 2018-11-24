/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{

        unsigned long start_time, stop_time;
        if(syscall == 1){
           ++syscall_info[currpid][2][0];
           start_time = ctr1000;
        }

        if(syscall == 1){
           stop_time = ctr1000;
           if(syscall_info[currpid][2][0] == 0){
               syscall_info[currpid][2][1] = stop_time - start_time;
           }
           else{
               syscall_info[currpid][2][1] = (((syscall_info[currpid][2][0] - 1) * syscall_info[currpid][2][1]) + (stop_time - start_time))/syscall_info[currpid][2][0];
           }
        }

	return(currpid);
}
