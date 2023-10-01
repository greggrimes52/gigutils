#define   VERSION   "06"
#include "us.h"
#include "usargs.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#ifndef _NOSTDLIB
#include <stdlib.h>
#endif

/**********************************************************************/
/* Global variables                                                   */
/**********************************************************************/
   static char *Pname;                 /* Program name for error msgs */
   static FILE *fp;                    /* buffered file being changed */
   static char  inputline[128];        /* buffer for reading stdin    */

#ifdef _NOPROTOS
   static int   do_it();
#else
   static int   do_it(char*);
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
/* Set up program name for error messages and help                    */
/**********************************************************************/
   US_NAME(Pname)

/**********************************************************************/
/* Process command line arguments and get first address               */
/**********************************************************************/
   arg=USARGS();

/**********************************************************************/
/* Show help, if requested                                            */
/**********************************************************************/
   if(!arg || FLAG(?))
      {
      printf("Usage:\n");
      printf("   %s [flags] filename < dumpin\n",Pname);
      printf("\n");
      printf("   Makes byte for byte changes to the specified file\n");
      printf("   by reading dump format records from stdin and\n");
      printf("   writing the bytes of the hexadecimal dump to the\n");
      printf("   locations specified by the displacements.\n");
      printf("\n");
      printf("flags:\n");
      printf(US_FLAGV);
      printf("\n");
      printf(US_COPYRIGHT);
      exit(0);
      }

/**********************************************************************/
/* Process the arguments                                              */
/**********************************************************************/
   do {
      do_it(arg);
      } while(arg=USARGS());

/**********************************************************************/
/* Return                                                             */
/**********************************************************************/
   return 0;

}


/******************/
/******************/
/**              **/
/** Main Routine **/
/**              **/
/******************/
/******************/
static int do_it(fname)
 char *fname;
{
   char *p;
   long  dec;
   long  hex;
   int   byte;
   int   n1,n2;
   int   i,c;

/**********************************************************************/
/* Parse the arguments                                                */
/**********************************************************************/
   fp = fopen( fname, "r+b");          /* open the file R/W binary    */
   if(fp == NULL)
      {
      printf("Unable to open file \"%s\"\n",fname);
      return 1;
      }

   if(FLAG(v))
      printf("Zapping file \"%s\"\n",fname);

/**********************************************************************/
/* Loop through input making the specified changes.                   */
/**********************************************************************/
   while(gets(inputline) != NULL)      /* read all of stdin           */
     {
      if(FLAG(v)) puts(inputline);     /* echo line, if need be       */
      p = inputline;                   /* start at beginning of line  */

      while(*p == ' ') p++;            /* skip some blanks            */
      dec = 0L;                        /* compute the decimal value   */
      while(*p != ' ' && *p != '/')    /*    of the displacement      */
        {
         dec *= 10L;
         dec += *p - '0';
         p++;
        }
      while(*p == ' ') p++;            /* skip some blanks            */
      if(*p == '/')
         p++;
      else
        {
         fprintf(stderr,
            "Error:  missing slash between displacements.\n");
         break;
        }

      while(*p == ' ') p++;            /* skip some blanks            */
      hex = 0L;                        /* compute the hex value       */
      while(*p != ' ' && *p != ':')    /*    of the displacement      */
        {
         hex *= 16L;
         hex += (*p <= '9')? *p - '0' : toupper(*p) - 'A' + 10;
         p++;
        }
      while(*p == ' ') p++;            /* skip some blanks            */
      if(*p == ':')
         p++;
      else
        {
         fprintf(stderr,
            "Error:  missing colon after displacements.\n");
         break;
        }

      if(dec != hex)
        {
         fprintf(stderr,
            "Error:  decimal and hex displacements are not the same.\n");
         break;
        }
      if(FLAG(v))
         printf("   Seek to %ld (0x%lX).\n",dec,hex);
      if(fseek(fp,dec,0) < 0)          /* seek to the displacement    */
        {
         fprintf(stderr,
            "Error trying to seek to file displacement.\n");
         perror(Pname);
         break;
        }

      while(*p == ' ') p++;            /* skip some blanks            */
      c = 0;                           /* only 16 bytes per dump line */
      while(c < 16)
        {
         if(! *p) break;               /* end of string?  bail out    */
         n1 = (*p <= '9')? *p - '0' : toupper(*p) - 'A' + 10;
         p++;
         n2 = (*p <= '9')? *p - '0' : toupper(*p) - 'A' + 10;
         p++;
         byte = (n1 << 4) | n2;
         c++;
         fputc(byte,fp);               /* write the byte to the file  */

         if(FLAG(v))
            printf("   Write byte %2.2X.\n",byte);

         i=0;                          /* more than three blanks      */
         while(*p == ' ') {p++;i++;}   /* means end of hex dump       */
         if(i > 3) break;
        }
     }

/**********************************************************************/
/* Close all files and return                                         */
/**********************************************************************/
   fclose(fp);                         /* close the file being zapped */

}
