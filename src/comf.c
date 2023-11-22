#define   VERSION   "06"
#include "us.h"
#include "usargs.h"
#include "usdump.h"
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#ifndef _NOSTDLIB
#include <stdlib.h>
#endif
#define   BUFSIZE 16

int main(argc,argv)
 int argc;
 char   **argv;
{
   FILE *file1,*file2;
   int   read1, read2;
   int   i,issame;
   long  size1;
   long  size2;
   long  same,diff;
   char *name1,buff1[BUFSIZE];
   char *name2,buff2[BUFSIZE];
   char *arg,buffer[80];

   FLAG(C) = 1;   /* Comparison messages are default */
   FLAG(S) = 1;   /* Summary messages are default */

   i=0;
   file1 = file2 = NULL;
   while(arg=USARGS())
      {
      switch(++i)
         {
         case 1:
            name1 = arg;
#ifdef DOS
            while(*arg) {*arg=toupper(*arg);arg++;}
#endif
            if((file1=fopen(name1,"r")) < 0)
               {
               printf("Unable to fopen %s, errno=%d (0x%0X).\n",
                  name1,errno,errno);
               exit(1);
               }
            break;
         case 2:
            name2 = arg;
#ifdef DOS
            while(*arg) {*arg=toupper(*arg);arg++;}
#endif
            if((file2=fopen(name2,"r")) < 0)
               {
               printf("Unable to fopen %s, errno=%d (0x%0X).\n",
                  name2,errno,errno);
               exit(1);
               }  
            break;
         default:
            printf("Ignoring extra argument:  %s\n",arg);
            break;
         }
      }

   if(file1==NULL || file2==NULL || FLAG(?))
      {
      US_NAME(arg)
      printf("Usage:\n");
      printf("   %s [flags] file1 file2\n",arg);
      printf("\n");
      printf("   Performs a byte for byte comparison between file1 and file2,\n");
      printf("   reporting the differences with asterisks in a hexadecimal\n");
      printf("   and ASCII dump.\n");
      printf("\n");
      printf("flags:\n");
      printf("  --C   Suppress comparison differences messages\n");
      printf("  --S   Suppress summary messages\n");
      printf("   -V   Verbose:  Hex dump all of the files\n");
      printf(US_FLAGY);
      printf(US_FLAGZ);
      printf("\n");
      printf(US_COPYRIGHT);
      exit(0);
      }

   if(FLAG(C) || FLAG(S))
      printf("Comparing \"%s\" with \"%s\", byte for byte.\n",name1,name2);
   same  = diff  = 0;
   size1 = size2 = 0;
   read1 = read2 = 1;
   while(1)
      {
      for(i=0;i<BUFSIZE;i++) buff1[0] = buff2[0] ^ 15;

      if(read1) size1 += read1 = fread(buff1,1,BUFSIZE,file1);
      if(read2) size2 += read2 = fread(buff2,1,BUFSIZE,file2);

      if(!read1 && !read2)  break;

      issame = 1;
      for(i=0;i<read1&&i<read2;i++)
         if(buff1[i] == buff2[i])
            same++;
         else
            {
            diff++;
            issame = 0;
            }

      if((!issame || FLAG(V)) && FLAG(C))
         {
         printf("\n");
         USDUMP(buff1,read1,size1-BUFSIZE);
         if(!issame && read1 && read2)
            {
            for(i=0;i<79;i++) buffer[i] = ' ';
            buffer[79] = '\0';
            arg = buffer + 21;
            for(i=0;i<read1&&i<read2;i++)
               {
               if( i && i %  4 == 0 ) arg++;
               if( i && i %  8 == 0 ) arg++;
               if( i && i % 16 == 0 ) arg++;
               if(buff1[i]==buff2[i])
                  arg += 2;
               else
                  {
                  *arg++ = '*';
                  *arg++ = '*';
                  buffer[59+i] = '*';
                  }
               }
            puts(buffer);
            }
         USDUMP(buff2,read2,size2-BUFSIZE);
         }
      }

   if(FLAG(S))
      {
      printf("\n");
      printf("%9ld byte(s) in %s\n",size1,name1);
      printf("%9ld byte(s) in %s\n",size2,name2);
      printf("%9ld byte(s) are the same\n",same);
      printf("%9ld byte(s) are different\n",diff);
      }

   fclose(file1);
   fclose(file2);

   if(diff>255)
      exit(255);
   else
      exit((int)diff);
}
