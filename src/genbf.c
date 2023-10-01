#define   VERSION   "05"
#include "us.h"
#include "usargs.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#ifndef _NOSTDLIB
#include <stdlib.h>
#endif

   static char buffer[32768];

int main(argc,argv)
 int argc;
 char *argv[];
{
   int   i;    
   int   n;
   FILE *file;
   char *arg;
   char *fname;

/**********************************************************************/
/* Process command line arguments and get file name                   */
/**********************************************************************/
   arg=USARGS();

/**********************************************************************/
/* Show help, if requested                                            */
/**********************************************************************/
   if(FLAG(?) || arg==NULL) 
      {
      US_NAME(arg)
      printf("Usage:\n");
      printf("   %s [flags] filename\n",arg);
      printf("\n");
      printf("   Builds a file with various binary structures.\n");
      printf("\n");
      printf("flags:\n");
      printf("   -Rn  include n blocks containing 0xFF through 0x00\n");
      printf("   -Bn  include n \"custom\" blocks\n");
      printf("   -Cn  custom blocks use byte value n (0<=n<=255)\n");
      printf("   -Ln  custom blocks are n bytes long (1<=n<=32767)\n");
      printf("   -Fn  include n blocks containing 0x00 through 0xFF\n");  
      printf(US_FLAGV);
      printf("\n");
      printf(US_COPYRIGHT);
      exit(0);
      }

/**********************************************************************/
/* Report file name to be generated                                   */
/**********************************************************************/
   fname = arg;
#ifdef DOS
   while(*arg) {*arg=toupper(*arg);arg++;}
#endif
   printf("Generate binary file named \"%s\".\n",fname);

/**********************************************************************/
/* Check for something to write                                       */
/**********************************************************************/
   if(FLAG(B)==0 && FLAG(C)==0 && FLAG(L)==0 && 
      FLAG(R)==0 && FLAG(F)==0)
      {
      printf("   No block types specified.");
      printf("   Using -R1 -B2 -C33 -L256 -F1.\n");
      FLAG(R) = 1;
      FLAG(B) = 2;
      FLAG(C) = 33;
      FLAG(L) = 256;
      FLAG(F) = 1;
      }

/**********************************************************************/
/* Validate Block Values                                              */
/**********************************************************************/
   if(FLAG(R) < 0)
      {
      printf("   Instead of -R%d, using -R1.\n",FLAG(R));
      FLAG(R) = 1;
      }

   if(FLAG(B)!=0 || FLAG(C)!=0 || FLAG(L)!=0)
      {
      if(FLAG(B) < 1)
         {
         printf("   Instead of -B%d, using -B1.\n",FLAG(B));
         FLAG(B) = 1;
         }
      if(FLAG(C) < 0  ||  FLAG(C) > 255)
         {
         printf("   Instead of -C%d (0x%2.2X = '%c'),\n",
            FLAG(C),FLAG(C),FLAG(C));
         FLAG(C) = '!';
         printf("        using -C%d (0x%2.2X = '%c').\n",
            FLAG(C),FLAG(C),FLAG(C));
         }
      if(FLAG(L) < 1  ||  FLAG(L) > 32767)
         {
         printf("   Instead of -L%d, using -L256.\n",FLAG(L));
         FLAG(L) = 256;
         }
      }

   if(FLAG(F) < 0)
      {
      printf("   Instead of -F%d, using -F1.\n",FLAG(F));
      FLAG(F) = 1;
      }

/**********************************************************************/
/* Debug information                                                  */
/**********************************************************************/
   if(FLAG(V))
      {
      if(FLAG(R))
         printf("   %2d Reverse block(s).\n",FLAG(R));
      else
         printf("   No Reverse blocks.\n");

      if(FLAG(B))
         {
         printf("   %2d Custom  block(s) of %d bytes",FLAG(B),FLAG(L));
         printf(" with value %d (0x%2.2X = '%c').\n",FLAG(C),FLAG(C),FLAG(C));
         }
      else
         printf("   No Custom  blocks.\n");

      if(FLAG(F))
         printf("   %2d Forward block(s).\n",FLAG(F));
      else
         printf("   No Forward blocks.\n");
      }

/**********************************************************************/
/* Open the file to be generated                                      */
/**********************************************************************/
   file = fopen(fname,"wb");
   if(file == NULL)
      {
      printf("Unable to open %s for output, errno=%d (0x%0X).\n",
         fname,errno,errno);
      exit(1);
      }
   if(FLAG(V))
      printf("   File opened with file pointer %p, errno=%d (0x%0X).\n",
         file,errno,errno);

/**********************************************************************/
/* Build and write "Reverse" blocks                                   */
/**********************************************************************/
   if(FLAG(R))
      {
      if(FLAG(V))  printf("   Building Reverse buffer.\n");
      for(i=0;i<256;i++)
         buffer[i]=255-i;
      if(FLAG(V))  printf("   Writing %d buffer images.\n",FLAG(R));
      for(n=0;n<FLAG(R);n++)
         fwrite(buffer,256,1,file);
      }

/**********************************************************************/
/* Build and write "Custom" blocks                                    */
/**********************************************************************/
   if(FLAG(B))
      {
      if(FLAG(V))  printf("   Building Custom buffer.\n");
      for(i=0;i<FLAG(L);i++)
         buffer[i]=FLAG(C);
      if(FLAG(V))  printf("   Writing %d buffer images.\n",FLAG(B));
      for(n=0;n<FLAG(B);n++)
         fwrite(buffer,FLAG(L),1,file);
      }

/**********************************************************************/
/* Build and write "Forward" blocks                                   */
/**********************************************************************/
   if(FLAG(F))
      {
      if(FLAG(V))  printf("   Building Forward buffer.\n");
      for(i=0;i<256;i++)
         buffer[i]=i;
      if(FLAG(V))  printf("   Writing %d buffer images.\n",FLAG(F));
      for(n=0;n<FLAG(F);n++)
         fwrite(buffer,256,1,file);
      }

/**********************************************************************/
/* Close the generated file                                           */
/**********************************************************************/
   i = fclose(file);
   if(FLAG(V))
      printf("   File closed with rc=%d (0x%0X), errno=%d (0x%0X).\n",
         i,i,errno,errno);

/**********************************************************************/
/* Return                                                             */
/**********************************************************************/
   return 0;
}
