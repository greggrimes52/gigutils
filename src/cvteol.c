#define   VERSION   "04"
#include "us.h"
#include "usargs.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#ifndef _NOSTDLIB
#include <stdlib.h>
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
   char          *ipath;                 /* input  file path name     */
   char          *opath;                 /* output file path name     */
   int            ifile;                 /* input  file handle        */
   int            ofile;                 /* output file handle        */
   unsigned char  ibuf[BUFSIZ];          /* read  buffer              */
   unsigned char  obuf[BUFSIZ+2];        /* write buffer              */
   unsigned char *iptr;                  /* read  buffer pointer      */
   unsigned char *optr;                  /* write buffer pointer      */
   unsigned int   icnt;                  /* read  buffer count        */
   unsigned int   ocnt;                  /* write buffer count        */
   int            eof;                   /* end of file indicator     */
   int            lastcr;                /* indicates CR was prev     */
   char          *p;                     /* temp pointer              */

/**********************************************************************/
/* Process command line arguments and get first address               */
/**********************************************************************/
   ipath=USARGS();                       /* input  file path name     */
   opath=USARGS();                       /* output file path name     */

/**********************************************************************/
/* Show help, if requested                                            */
/**********************************************************************/
   if(!ipath || !opath || FLAG(?))
      {
      US_NAME(p)
      printf("Usage:\n");
      printf("   %s [flags] infile outfile\n",p);
      printf("\n");
      printf("   Copies infile to outfile converting the end-of-line\n");
      printf("   characters as needed to PC, UNIX, or Macintosh style\n");
      printf("   end-of-line characters.  The default is to end lines\n");
#ifdef DOS
      printf("   with carriage return-line feed pairs (PC style text).\n");
#else
      printf("   with single newlines (UNIX style text).\n");
#endif
      printf("\n");
      printf("   Please note that PC and UNIX style print files use\n");
      printf("   carriage returns for overstiking.  Each of these\n");
      printf("   will be turned into a new end-of-line.\n");
      printf("\n");
      printf("flags:\n");
      printf("   -M   make each line end with a single carriage\n");
      printf("        return (Macintosh style text)\n");
      printf("   -P   make each line end with a carriage return-\n");
      printf("        line feed pair (PC style text)\n");
      printf("   -U   make each line end with a single newline\n");
      printf("        (UNIX style text)\n");
      printf("   -V   massive volumes of debug output\n");
      printf("\n");
      printf(US_COPYRIGHT);
      exit(0);
      }

/**********************************************************************/
/* Determine the default behavior, if necessary.                      */
/**********************************************************************/
   lastcr = 0;
   if (FLAG(m))  lastcr++;
   if (FLAG(p))  lastcr++;
   if (FLAG(u))  lastcr++;
   if (lastcr > 1)
     {
      fprintf(stderr,
         "ERROR: Only one of -M, -P, or -U may be specified.\n");
      exit(1);
     }
   else if (lastcr == 0)
     {
#ifdef DOS
      FLAG(p) = 1;
#else
      FLAG(u) = 1;
#endif
     }

/**********************************************************************/
/* Open the input file.                                               */
/**********************************************************************/
#ifdef DOS
   p = ipath;
   while(*p) {*p=toupper(*p);p++;}
#endif
   /* open input file */
   ifile = open( ipath, O_RDONLY | O_RAW );
   if(ifile < 0)
      {
      fprintf(stderr,"Unable to open file \"%s\"\n",ipath);
      exit(2);
      }

/**********************************************************************/
/* Open the output file.                                              */
/**********************************************************************/
#ifdef DOS
   p = opath;
   while(*p) {*p=toupper(*p);p++;}
#endif
   /* open output file */
   ofile = open( opath, O_WRONLY | O_RAW | O_CREAT | O_TRUNC, 0666 );
   if(ofile < 0)
      {
      fprintf(stderr,"Unable to open file \"%s\"\n",opath);
      exit(2);
      }

/**********************************************************************/
/* Copy input to output translating as needed.                        */
/**********************************************************************/
   ocnt = icnt = eof = lastcr = 0;
   optr = obuf;
   while(! eof)
    {
     if (icnt <= 0)
       {
        /*
         * Grab a buffer of input to work with.
         * Set EOF when we attempt to read and
         * can't get anything.  Then EOF also
         * means there's no input to process.
         */
        iptr = ibuf;
        icnt = read(ifile,ibuf,BUFSIZ);
        if (icnt <= 0)
          {
           eof = 1;
          }
        if (FLAG(v))
           printf("DEBUG: eof=%d icnt=%d after reading a block\n",
              eof,icnt);
       }
     if (icnt > 0)
       {
        if (*iptr == '\r' || *iptr == '\n')
          {
           /*
            * We've stumbled onto an end-of-line.
            * Now insert the whatever is appropriate
            * for the ends-of-lines we're building,
            * unless the last char was CR and this
            * one is LF.
            */
           if (!lastcr || *iptr != '\n')
             {
              if (FLAG(p) || FLAG(m))
                {
                 *optr++ = '\r';
                 ocnt++;
                 if (FLAG(v))
                    printf("DEBUG: lastcr=%d after adding   0x%2.2X\n",
                       lastcr,'\r');
                }
              if (FLAG(p) || FLAG(u))
                {
                 *optr++ = '\n';
                 ocnt++;
                 if (FLAG(v))
                    printf("DEBUG: lastcr=%d after adding   0x%2.2X\n",
                       lastcr,'\n');
                }
             }
           /*
            * Skip past the CRLF (PC), CR (Mac),
            * or LF (UNIX).
            */
           if (*iptr == '\r')
              lastcr = 1;
           else
              lastcr = 0;
           iptr++;
           icnt--;
           if (FLAG(v))
              printf("DEBUG: lastcr=%d after skipping 0x%2.2X\n",
                 lastcr,iptr[-1]);
          }
        else
          {
           /*
            * Normal text simply gets copied
            * from the input buffer to the
            * output buffer.
            */
           *optr++ = *iptr++;
           icnt--;
           ocnt++;
           lastcr = 0;
          }
       }
     if (FLAG(v))
       {
        printf("DEBUG: eof=%d ",eof);
        printf("icnt=%d iptr=%X iptr[-1]=%2.2X(%c) ",
                icnt,   iptr,     iptr[-1],
               (isprint(iptr[-1])?iptr[-1]:' '));
        printf("ocnt=%d optr=%X optr[-1]=%2.2X(%c)\n",
                ocnt,   optr,     optr[-1],
               (isprint(optr[-1])?optr[-1]:' '));
       }
     if (ocnt >= BUFSIZ || eof)
       {
        if (FLAG(v))
           printf("DEBUG: eof=%d ocnt=%d before writing a block\n",
              eof,ocnt);
        if (write(ofile,obuf,ocnt) != ocnt)
          {
           fprintf(stderr,"ERROR writing to output file.\n");
           exit(3);
          }
        optr = obuf;
        ocnt = 0;
       }
    }

/**********************************************************************/
/* Close files and exit.                                              */
/**********************************************************************/
   close( ifile );                              /* close input  file  */
   close( ofile );                              /* close output file  */
   exit(0);
}
