/* printsegaddress.c - printsegaddress */
#include <stdio.h>

extern long etext, edata, end;

/*-----------------------------------------------------------------------------------------------------
 * *  printsegaddress - Prints the values of etext, edata and ebss for current, Preceeding and Succeeding
 * *                    4 byte contents
 * *-------------------------------------------------------------------------------------------------------
 * */
void printsegaddress()
{
  kprintf("\nOutput of printsegaddress()");
  kprintf("\nCurrent: etext[0x%08x]=0x%08x,  edata[0x%08x]==0x%08x,   ebss[0x%08x]==0x%08x", &etext, (long *)etext, &edata, (long *)edata, &end, (long *)end);
  kprintf("\nPreceeding: etext[0x%08x]=0x%08x,  edata[0x%08x]=0x%08x,   ebss[0x%08x]=0x%08x", &etext-1, (long *)(&etext-1), &edata-1, (long *)(&edata-1), &end-1, (long *)(&end-1));
  kprintf("\nAfter: etext[0x%08x]=0x%08x,  edata[0x%08x]=0x%08x,   ebss[0x%08x]=0x%08x", &etext+1, (long *)(&etext+1), &edata+1, (long *)(&edata+1), &end+1, (long *)(&end+1)); 
}

