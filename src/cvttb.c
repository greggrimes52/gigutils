#define   VERSION   "05"
#include "us.h"
#include "usargs.h"
#include "usdump.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#ifndef _NOSTDLIB
#include <stdlib.h>
#endif

#define   DEL 0x7F
/**********************************************************************/
/* Declare variables                                                  */
/**********************************************************************/
                        /*   0....+....1....+....2....+....3....+...  */
   static char  ctrl1[] = { "NSSEEEABBHLVFCSSDDDDDNSECESEFGRUS.L.R.D" };
   static char  ctrl2[] = { "UOTTONCESTFTFROILCCCCAYTAMUSSSSSP.B.B.E" };
   static char  ctrl3[] = { "LHXXTQKL        E1234KNBN BC     . . .L" };

   static char  code[8];

   static FILE *file1,*file2;
   static char *name1,*name2;
   static long  size1, size2;

   static int   byte, base, value;

#ifdef _NOPROTOS
   static int   readbyte();
#else
   static int   readbyte(void);
#endif

int main(argc,argv)
 int argc;
 char   **argv;
{
   char *arg;
   int   i,j;

/**********************************************************************/
/* Process the command line arguments                                 */
/**********************************************************************/
   FLAG(s) = 1;                       /* Summary messages are default */
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
            if((file1=fopen(name1,"rb")) == NULL)
               {
               printf("Unable to open %s, errno=%d (0x%0X).\n",
                  name1,errno,errno);
               exit(1);
               }
            break;
         case 2:
            name2 = arg;
#ifdef DOS
            while(*arg) {*arg=toupper(*arg);arg++;}
#endif
            if((file2=fopen(name2,"wb")) == NULL)
               {
               printf("Unable to open %s, errno=%d (0x%0X).\n",
                  name2,errno,errno);
               exit(1);
               }  
            break;
         default:
            printf("Ignoring extra argument:  %s\n",arg);
            break;
         }
      }

/**********************************************************************/
/* Show help, if requested                                            */
/**********************************************************************/
   if(file1==NULL || file2==NULL || FLAG(?))
      {
      US_NAME(arg)
      printf("Usage:\n");
      printf("   %s [flags] txtfile binfile\n",arg);
      printf("\n");
      printf("   Converts a text file containing special codes\n");
      printf("   for uneditable characters into a binary file.\n");
      printf("\n");
      printf("flags:\n");
      printf("  --S   Suppress summary messages\n");
      printf("\n");
      printf(US_COPYRIGHT);
      exit(0);
      }

/**********************************************************************/
/* Conversion loop                                                    */
/**********************************************************************/
   if(FLAG(s))
      printf("Converting text file \"%s\" into binary image \"%s\".\n",
         name1,name2);
   size1 = size2 = 0;
   while(1)
      {
      if((byte=readbyte()) == EOF) break;

      if (byte == '[')
         {
         for(i=0;i<sizeof(code);i++)
            {
            code[i] = byte = readbyte();
            if (byte == EOF)
               {
               printf("   End of file in the middle of an escape code.\n");
               break;
               }
            if (code[i] == ']') break;
            }
         if (i >= sizeof(code)) i--;
         value = 0;
         base  = 0;
         j     = 0;
         if ('1'<=code[j] && code[j]<='9')
            {
            value = code[j]-'0';
            base  = 10;
            j++;
            }
         else if ('0'==code[j])
            {
            base = 8;
            j++;
            if      (toupper(code[j]) == 'X') {base=16; j++;}
            else if (toupper(code[j]) == 'D') {base=10; j++;}
            else if (toupper(code[j]) == 'O') {base= 8; j++;}
            }
         if (base)
            {
            while(code[j] != ']')
               {
               byte = 0;
               if      ('0'<=code[j] && code[j]<='9') byte = code[j]-'0';
               else if ('A'<=code[j] && code[j]<='F') byte = code[j]-'A'+10;
               else if ('a'<=code[j] && code[j]<='f') byte = code[j]-'a'+10;
               else         
                  {
                  printf("   Non-digit in numeric escape code.\n");
                  value = -1;
                  break;
                  }
               if (byte > base)
                  {
                  printf("   Numeric escape code digit invalid for base %d.\n",base);
                  value = -1;
                  break;
                  }
               value = value * base + byte;
               j++;
               }
            }
         else
            {
            if (i == 2) code[i] = ' ';
            value = -1;
            for(i=0; i<sizeof(ctrl1); i++)
               if (ctrl1[i] == toupper(code[0]))
                  if (ctrl2[i] == toupper(code[1]))
                     if (ctrl3[i] == toupper(code[2]))
                        {
                        if      (i<=32) value = i;
                        else if (i==34) value = '[';
                        else if (i==36) value = ']';
                        else            value = DEL;
                        }
            }
         if (value < 0)
            {
            if (i == 2) code[i] = ']';
            printf("Unknown escape code:  [");
            for(j=0;j<=i;j++) printf("%c",code[j]);
            printf("\n");
            continue;
            }
         byte = value;
         }
   
      fputc(byte,file2);
      size2++;
      }
   
/**********************************************************************/
/* Produce summary messages, if requested                             */
/**********************************************************************/
   if(FLAG(s))
      {
      printf("%9ld byte(s) read  from %s\n",size1,name1);
      printf("%9ld byte(s) written to %s\n",size2,name2);
      }

/**********************************************************************/
/* Return after turning out the lights                                */
/**********************************************************************/
   fclose(file1);
   fclose(file2);
   return 0;
}



/**********************************************************************/
/* Read a text file character, skipping white space                   */
/**********************************************************************/
static int readbyte()
{
   int c;
   do {
      if ((c=fgetc(file1)) != EOF)  size1++;
      } while ((c != EOF) && (c <= ' '));
   return c;
}
