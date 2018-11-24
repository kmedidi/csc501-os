/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
int main()
{
	kprintf("\n\nHello World, Xinu lives\n\n");
        kprintf("\nzfunction output: 0x%08x\n\n",zfunction(0xaabbccdd));
        printsegaddress();
        kprintf("\n\n");
        printtos();
        kprintf("\n\n");
        printprocstks(10);
        kprintf("\n\n");
        syscallsummary_start();
        sleep(1);
        sleep(2);
        syscallsummary_stop();
        kprintf("\nPrintsyscallsummary output\n");
        printsyscallsummary();
	return 0; 
}
