extern void printsegaddress();
extern void printtos();
extern void printprocstks(int priority);

extern int syscall;             //syscall is a flag, 1 - start recording and 0 - stop recording
extern int syscall_info[50][27][2]; //an array with the i = number of system calls and j = 0 -> count, j = 1 -> avg run time

extern void syscallsummary_start();
extern void syscallsummary_stop();
extern void printsyscallsummary();

extern long zfunction(long param);
