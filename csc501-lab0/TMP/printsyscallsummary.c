/* printcallsummary.c - syscallsummary_start, syscallsummary_stop, printsyscallsummary */
#include <stdio.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

/*
extern int syscall;             //syscall is a flag, 1 - start recording and 0 - stop recording
extern int syscall_info[27][2]; //an array with the i = number of system calls and j = 0 -> count, j = 1 -> avg run time
*/
/*-------------------------------------------------------------------------------------
 * * Function that provides stats of the system calls
 * *--------------------------------------------------------------------------------------
 * */

int syscall;
int syscall_info[50][27][2];

void syscallsummary_start(){
  int i;
  syscall = 1;

  for(i=0; i<27; i=i+1){
    syscall_info[currpid][i][0] = 0;
    syscall_info[currpid][i][1] = 0;
  }
}

void syscallsummary_stop(){
  syscall = 0;
}

void printsyscallsummary(){
  int i, j, first_time;
  char *syscall_list[27];

  syscall_list[0] = "sys_freemem";
  syscall_list[1] = "sys_chprio";
  syscall_list[2] = "sys_getpid";
  syscall_list[3] = "sys_getprio";
  syscall_list[4] = "sys_gettime";
  syscall_list[5] = "sys_kill";
  syscall_list[6] = "sys_receive";
  syscall_list[7] = "sys_recvclr";
  syscall_list[8] = "sys_recvtim";
  syscall_list[9] = "sys_resume";
  syscall_list[10] = "sys_scount";
  syscall_list[11] = "sys_sdelete";
  syscall_list[12] = "sys_send";
  syscall_list[13] = "sys_setdev";
  syscall_list[14] = "sys_setnok";
  syscall_list[15] = "sys_screate";
  syscall_list[16] = "sys_signal";
  syscall_list[17] = "sys_signaln";
  syscall_list[18] = "sys_sleep";
  syscall_list[19] = "sys_sleep10";
  syscall_list[20] = "sys_sleep100";
  syscall_list[21] = "sys_sleep1000";
  syscall_list[22] = "sys_sreset";
  syscall_list[23] = "sys_stacktrace";
  syscall_list[24] = "sys_suspend";
  syscall_list[25] = "sys_unsleep";
  syscall_list[26] = "sys_wait";

  if (syscall == 1){
    kprintf("Stop recording first. Call syscallsummary_stop()");
  }
  else {
    for(i=0; i<NPROC; i=i+1){
       first_time = 1;
       for(j=0; j<27; j=j+1){
          if(syscall_info[i][j][0] > 0){
             if(first_time == 1){
                kprintf("\nPID:%d",i);
                first_time = 0;
             }
             kprintf("\nSyscall: %s count = %d, avg execution time = %dms", syscall_list[j], syscall_info[i][j][0], syscall_info[i][j][1]);
          }  
       }   
    }  
  }
}  
