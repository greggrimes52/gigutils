#include <ctype.h>
#include <stdio.h>
#include "usargs.h"
int main(argc,argv)
 int  argc;
 char     *argv[];
{
   int   i;
   char *x;

   /* Show all arguments */
   printf("argc    = %d\n",argc);
   for(i=0;i<argc;i++)
      printf("argv[%d] = \"%s\"\n",i,argv[i]);
   printf("\n");

   /* Show those arguments filtered by USARGS */
   i=0;
   while(x=USARGS())
      printf("arg #%d  = \"%s\"\n",++i,x);
   printf("\n");

   /* Show all flags set by USARGS */
   for(i=0;i<256;i++)
      {
      if(args[i])
         {
         printf("%7d (0x%*.*X) is the value of args[0x%2.2X]",
            args[i],(int)(sizeof(int)*2),(int)(sizeof(int)*2),args[i],i);
         if(isprint(i))
            printf(" which is FLAG(%c)",i);
         printf("\n");
         }
      }   

   /* That is all */
   return 0;
}
