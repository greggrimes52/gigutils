#define   VERSION   "04"
#include "us.h"
#include "usargs.h"
#include "usdump.h"
#ifdef    DOS
#include "usextm.h"
#include <dos.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>

   static int  argnum;
   static int  beenhere;
   static int  length;
   static long address;
   static long limit;
   static union
      {
      char __far *ptr;
      int word[2];
      } x;  

#ifdef _NOPROTOS
   static int  do_it();
   static int  argvalue();
#else
   static int  do_it(void);
   static int  argvalue(char*);
#endif


/******************/
/******************/
/**              **/
/** Main Routine **/
/**              **/
/******************/
/******************/
int main(argc,argv)
 int argc;
 char *argv[];
{
   char *arg;

/**********************************************************************/
/* Process command line arguments and get first address               */
/**********************************************************************/
   arg=USARGS();

/**********************************************************************/
/* Show help, if requested                                            */
/**********************************************************************/
   if(FLAG(?) || (!arg && !FLAG(e)))
      {
      US_NAME(arg)
      printf("Usage:\n");
      printf("   %s [flags] [address]...\n",arg);
      printf("\n");
      printf("   Displays memory starting at the specified address(es)\n");
      printf("   entered as segment:offset or absolute address.\n");
      printf("\n");
      printf("flags:\n");
      printf("   -En  display extended memory nK\n");   
      printf("   -Ln  display n bytes of memory (0<n<32767)\n");
      printf(US_FLAGV);
      printf(US_FLAGX);
      printf(US_FLAGY);
      printf(US_FLAGZ);
      printf("\n");
      printf(US_COPYRIGHT);
      exit(0);
      }

/**********************************************************************/
/* Special options processing                                         */
/**********************************************************************/
   if(FLAG(L))
      length = FLAG(L);
   else
      length = 256;

/**********************************************************************/
/* Process the arguments                                              */
/**********************************************************************/
   if(arg)
      {
      do {
         argnum=0;
         argvalue(arg);
         if(arg=strchr(arg,':'))   /* Find ':' in seg:off */
            argvalue(arg+1);
         do_it();
         } while(arg=USARGS());
      }
   else if(!FLAG(E))
      {
      address = 0L;
      do_it();
      }

/**********************************************************************/
/* Process -E switch                                                  */
/**********************************************************************/
   if(FLAG(E))
      {
      if(!FLAG(L)) length = 1024;
      address = 0x100000L + (FLAG(E)-1) * 1024L;
      do_it();
      }

/**********************************************************************/
/* Return                                                             */
/**********************************************************************/
   return 0;

}


/*************************/
/*************************/
/**                     **/
/** Memory Dump Routine **/
/**                     **/
/*************************/
/*************************/
static int do_it()
{
   int    rc;
   char __far *buffer;
#ifdef DOS
   union  REGS regs;
#endif

/**********************************************************************/
/* Split up multiple dumps                                            */
/**********************************************************************/
   if(!beenhere)
      beenhere++;
   else
      printf("\n\n");

/**********************************************************************/
/* Copy memory, if needed                                             */
/**********************************************************************/
#ifdef DOS
   if(address >= 0x100000L)
      {
      if(limit == 0)
         {
         regs.h.ah = 0x88;
         int86(0x15,&regs,&regs);
         limit = ((regs.x.ax + 1024L) * 1024L) - 1L;
         if(FLAG(V))
            printf("Debug:  Extended Memory Limit is %ld (0x%lX).\n",
               limit,limit);
         }
      if(address > limit)
         {
         printf("Address %ld (0x%lX) is greater than\n",address,address);
         printf("  limit %ld (0x%lX) of Extended Memory.\n",limit,limit);
         return 1;
         }
      if((address+length) > limit)
         {
         length = limit - address + 1;
         }
      printf("Extended Memory Dump starting at %ld (0x%lX).\n\n",
         address,address);
      buffer = (char __far *)malloc(length);
      if(rc = usextm(address,PHYS(buffer),length))
         {
         printf("USEXTM returned %d.\n",rc);
         return 1;
         }
      }
   else
      {
      printf("Memory Dump starting at %lp which is %ld (0x%lX).\n\n",
         x.ptr,address,address);
      buffer = x.ptr;
      }
#else
   printf("Memory Dump starting at %ld (0x%lX).\n\n",
      address,address);
   buffer = (char __far *)address;
#endif

/**********************************************************************/
/* Dump Memory                                                        */
/**********************************************************************/
   USDUMP( buffer, length, address );

/**********************************************************************/
/* Return                                                             */
/**********************************************************************/
   return 0;

}


/************************/
/************************/
/**                    **/
/** Argument Processor **/
/**                    **/
/************************/
/************************/
static int argvalue(arg)
 char *arg;
{
   int  k,n;
   long value;

   k=0;
   if     (arg[0]=='0'&&arg[1]!= 0 ) k++;
   if     (arg[k]=='O'||arg[k]=='o') n=sscanf(arg+k+1,"%lo",&value);
   else if(arg[k]=='D'||arg[k]=='d') n=sscanf(arg+k+1,"%ld",&value);
   else if(arg[k]=='X'||arg[k]=='x') n=sscanf(arg+k+1,"%lx",&value);
   else                              n=sscanf(arg+k  ,"%lx",&value);
   if(n!=1)
      {
      printf("Unable to decifer address token \"%s\" (n=%d)\n",
         arg,n);
      exit(1);
      }

   if(FLAG(V))
      printf("Debug:  \"%s\" decifered as %ld (0x%lX).\n",
         arg,value,value);

   switch(++argnum)
      {
      case 1:
         x.word[0] = (int)value;     /* Offset */
         address   =      value;
         break;
      case 2:
         x.word[1] = (int)address;   /* Segment */
         x.word[0] = (int)value;     /* Offset  */
         address   = (address << 4) + value;
         break;
      default:
         printf("Ignoring extra parameter \"%s\"\n",arg);
      }

   if(FLAG(V))
      {
      printf("        Address is now %ld (0x%lX).\n",address,address);
      printf("        Pointer is now %lp\n",x.ptr);
      }

   return 0;
}
