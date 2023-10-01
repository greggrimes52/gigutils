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

#define   ESC 0x1B
#define   GSx 0x1D
#define   USx 0x1F
#define   DEL 0x7F
/**********************************************************************/
/* Declare variables                                                  */
/**********************************************************************/
                        /*   0....+....1....+....2....+....3....+...  */
   static char  ctrl1[] = { "NSSEEEABBHLVFCSSDDDDDNSECESEFGRUS.L.R.D" };
   static char  ctrl2[] = { "UOTTONCESTFTFROILCCCCAYTAMUSSSSSP.B.B.E" };
   static char  ctrl3[] = { "LHXXTQKL        E1234KNBN BC     . . .L" };

   static char  string[16];

   static FILE *file1,*file2;
   static char *name1,*name2;
   static long  size1, size2;

   static int   byte, type;
   static long  numbytes = 0;
   static long  numlines = 1;
   static long  totbytes = 0;
   static long  totlines = 1;
   static long  totpages = 1;

main(argc,argv)
 int argc;
 char   **argv;
{
   char *arg;
   int   i;

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
            if((file2=fopen(name2,"w")) == NULL)
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
   if(FLAG(l) == 0)
      FLAG(l) = 72;                      /* Default lines to 72 bytes */


/**********************************************************************/
/* Show help, if requested                                            */
/**********************************************************************/
   if(file1==NULL || file2==NULL || FLAG(?))
      {
      US_NAME(arg)
      printf("Usage:\n");
      printf("   %s [flags] binfile txtfile\n",arg);
      printf("\n");
      printf("   Converts a file containing uneditable characters into an editable text\n");
      printf("   file containing codes for the characters considered uneditable.\n");
      printf("\n");
      printf("flags:\n");
      printf("  --S   Suppress summary messages\n");
      printf("   -Ln  Produce a new line after <n> bytes.  Default is 72.\n");
      printf("   -Pn  Produce a form feed after <n> lines.  No default.\n");
      printf("   -Gt  Consider data (1) Tektronix (2) DDL graphics data.\n");
      printf("   -A   Use numeric codes for editable characters\n");
      printf("        instead of the characters themselves.\n");
      printf("   -N   Use numeric codes for uneditable characters\n");
      printf("        instead of the characters' code names.\n");
      printf("   -Hx  Numeric codes are produced in hexadecimal.\n");
      printf("   -Dx  Numeric codes are produced in decimal.\n");
      printf("   -Ox  Numeric codes are produced in octal.\n");
      printf("where x means:\n");
      printf("     1  [0x00], [0d000], [0o000].\n");
      printf("     2  [0x0],  [0],     [00].\n");
      printf("\n");
      printf(US_COPYRIGHT);
      exit(0);
      }

/**********************************************************************/
/* Conversion loop                                                    */
/**********************************************************************/
   if(FLAG(s))
      printf("Converting binary file \"%s\" into editable image \"%s\".\n",
         name1,name2);
   size1 = size2 = 0;
   while( (byte=fgetc(file1)) != EOF )
      {
      size1++;
      /* Check for graphics stream */
      if(FLAG(g)==1)                         /* Tektronix data stream */
         if(byte==ESC ||
            byte==USx ||
            byte==GSx)   numbytes += FLAG(l);
      if(FLAG(g)==2)                               /* DDL data stream */
         if(byte=='\\')  numbytes += FLAG(l);
      /* Determine output type */
                             type = 0;          /* Editable character */
      if(byte<=' ')          type = 1;   /* Uneditable character name */ 
      if(byte=='[')          type = 1;
      if(byte==']')          type = 1;
      if(byte==DEL)          type = 1;
      if(byte >DEL)          type = 2;                /* Numeric code */
      if(type==0 && FLAG(a)) type = 2;
      if(type==1 && FLAG(n)) type = 2;
      if(type==1)
         {
         if(byte=='[')       byte = 34;
         if(byte==']')       byte = 36;
         if(byte==DEL)       byte = 38;
         }
      if(type==2)
         {                                   /* Long hexadecimal code */
         if(FLAG(h)>1)       type = 3;      /* Short hexadecimal code */
         if(FLAG(d)>0)       type = 4;           /* Long decimal code */
         if(FLAG(d)>1)       type = 5;          /* Short decimal code */
         if(FLAG(o)>0)       type = 6;             /* Long octal code */
         if(FLAG(o)>1)       type = 7;            /* Short octal code */
         }
      switch(type)
         {
         case 0:                                /* Editable character */
            string[0] = byte;
            string[1] = 0;
            break;
         case 1:                         /* Uneditable character name */
            string[0] = '[';
            string[1] = ctrl1[byte];
            string[2] = ctrl2[byte];
            string[3] = ctrl3[byte];
            i = (string[3]==' ')? 3 : 4;
            string[i] = ']';
            string[i+1] = 0;
            break;
         case 2:                             /* Long hexadecimal code */
            sprintf(string,"[0x%2.2X]",byte);
            break;
         case 3:                            /* Short hexadecimal code */
            sprintf(string,   "[0x%X]",byte);
            break;
         case 4:                                 /* Long decimal code */
            sprintf(string,"[0d%3.3d]",byte);
            break;
         case 5:                                /* Short decimal code */
            sprintf(string,     "[%d]",byte);
            break;
         case 6:                                   /* Long octal code */
            sprintf(string,"[0o%3.3o]",byte);
            break;
         case 7:                                  /* Short octal code */
            sprintf(string,    "[0%o]",byte);
            break;
         }
      size2 = strlen(string);
      numbytes += size2;
      totbytes += size2;
      if(FLAG(l) && FLAG(l) < numbytes)
         {
         numbytes = size2;
         totbytes++;
         numlines++;
         totlines++;
         fputc('\n',file2);
         if(FLAG(p) && FLAG(p) < numlines)
            {
            numbytes++;
            totbytes++;
            numlines = 1;
            totpages++;
            fputc('\f',file2);
            }
         }
      for(i=0; string[i]; i++)
         fputc(string[i],file2);
      }
   totbytes++;
   fputc('\n',file2);
   
/**********************************************************************/
/* Produce summary messages, if requested                             */
/**********************************************************************/
   if(FLAG(s))
      {
      printf("%9ld byte(s) read  from %s\n",      size1,name1);
      printf("%9ld byte(s) written to %s in\n",totbytes,name2);
      printf("%9ld line(s)",                   totlines);
      if(FLAG(p))
         printf(" and %ld page(s)",            totpages);
      printf(".\n");
      }

/**********************************************************************/
/* Return after turning out the lights                                */
/**********************************************************************/
   fclose(file1);
   fclose(file2);
   return 0;
}
