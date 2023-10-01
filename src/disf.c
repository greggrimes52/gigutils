#define   VERSION   "06"
#include "us.h"
#include "usargs.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#ifndef _NOSTDLIB
#include <stdlib.h>
#endif

   static int  beenhere;

#ifdef _NOPROTOS
   static int  do_it();
#else
   static int  do_it(char*);
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
   if(!arg || FLAG(?))
      {
      US_NAME(arg)
      printf("Usage:\n");
      printf("   %s [flags] filename...\n",arg);
      printf("\n");
      printf("   Displays the named file(s) in Hexadecimal and ASCII.\n");
      printf("\n");
      printf("flags:\n");
      printf(US_FLAGX);
      printf(US_FLAGY);
      printf(US_FLAGZ);
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


/***********************/
/***********************/
/**                   **/
/** File Dump Routine **/
/**                   **/
/***********************/
/***********************/
static int do_it(fname)
 char *fname;
{
/**********************************************************************/
/* Declare variables                                                  */
/**********************************************************************/
   long           disp = 0;              /* displacement within file  */
   int            same = 0;              /* line same as last line    */
   int            scnt = 0;              /* suppressed line counter   */
   int            numb;                  /* number of bytes in line   */
   int            f;                     /* file to read data from    */
   int            p;                     /* read buffer index         */
   int            c;                     /* character from buffer     */
   int            n;                     /* character count in buffer */
   int            i;                     /* index for loop            */
   unsigned char *hptr;                  /* pointer to hbuf           */
   unsigned char *pptr;                  /* pointer to pbuf           */
   unsigned char  buffer[BUFSIZ];        /* read buffer               */
   unsigned char  hbuf[41];              /* buffer for hex conversion */
   unsigned char  pbuf[17];              /* buffer for printables     */
   unsigned char  cbuf[16];              /* buffer for previous line  */
   unsigned char  sbuf[16];              /* buffer for current  line  */

/**********************************************************************/
/* Split up multiple dumps                                            */
/**********************************************************************/
   if(!beenhere)
      beenhere++;
   else
      printf("\n\n");

/**********************************************************************/
/* Parse the arguments                                                */
/**********************************************************************/
#ifdef DOS
   hptr = fname;
   while(*hptr) {*hptr=toupper(*hptr);hptr++;}
#endif
   f = open( fname, O_RDONLY | O_RAW );         /* open input  file   */
   if(f < 0)
      {
      printf("Unable to open file \"%s\"\n",fname);
      return 1;
      }

   printf("Hex dump file \"%s\"\n",fname);

/**********************************************************************/
/* Loop through input dumping to output.                              */
/**********************************************************************/
   p = 0;                                       /* initialize index   */
   n = read( f, buffer, BUFSIZ );               /* read a buffer      */
   cbuf[0] = buffer[0] ^ 15;                    /* insure not same    */
   while( n > 0 )                               /* for every buffer   */
    {
      hptr = hbuf;                              /* initialize hptr    */
      pptr = pbuf;                              /* initialize pptr    */
      numb = 0;                                 /* initialize counter */
      for ( i = 0; i < 16; i++ )                /* loop 16 times      */
       {
         c = buffer[p++];                       /* get a file char    */
         if ( i && i %  4 == 0 ) *hptr++ = ' ';
         if ( i && i %  8 == 0 ) *hptr++ = ' ';
         if ( i && i % 16 == 0 ) *hptr++ = ' ';
         sbuf[i] = c;                           /* same check buffer  */
         sprintf(hptr,"%02x",c);                /* format char in hex */
         hptr += 2;                             /* advance pointer    */
         *pptr = c;                             /* format unprintable */
         switch(FLAG(Y))
           {                                    /* printable type?    */
           case 0:  if(*pptr>0x7E) *pptr = '.'; /*  strict ascii only */
           case 1:  if(*pptr<0x20) *pptr = '.'; /*  non-ctrl chars    */
                    break;                      /* or                 */
           default: if(*pptr == 0x00 ||         /*  only              */
                       *pptr == 0x07 ||         /*   displayable      */
                       *pptr == 0x08 ||         /*    using           */
                       *pptr == 0x09 ||         /*     runtime        */
                       *pptr == 0x0A ||         /*      file          */
                       *pptr == 0x0D ||         /*       I/O          */
                       *pptr == 0x1A ||         /*                    */
                       *pptr == 0x1B ||         /*                    */
                       *pptr == 0x7F)           /*  otherwise,        */
                       *pptr  = '.';            /*  only print "."    */
           }
         pptr++;                                /* incr print pointer */
         numb++;                                /* incr displacement  */
         if ( p >= n )                          /* buffer exhausted?  */
           {
              p = 0;                            /*  re-init index     */
              n = read( f, buffer, BUFSIZ );    /*  read another      */
              if ( n == 0 ) break;              /*  EOF if 0 read     */
           }
       }
      same = 1;                                 /* assume duplicate   */
      for ( i = 0; i < 16; i++ )                /* check              */
         if ( cbuf[i] != sbuf[i] )              /*  current/previous  */
           { 
              same = 0;                         /*  if not the same   */
              break;                            /*  be sure to print  */
           }
      if ( !same || n == 0 || FLAG(X) )         /* if not the same    */
        {
         if ( scnt )                            /*  suppressed lines? */
              printf(                           /*   yes, say so      */
                 "                             - %d lines the same -\n",
                 scnt );
         scnt  = 0;                             /* reset suppress cnt */
         *hptr = 0;                             /* terminate hbuf str */
         *pptr = 0;                             /* terminate pbuf str */
         printf( " %8ld / %6lx:  %-36.36s  %-16.16s\n", 
                   disp,  disp,  hbuf,     pbuf );           /* print */
         for ( i = 0; i < 16; i++ )             /* copy buffer for    */
           cbuf[i] = sbuf[i];                   /*  future compare    */
        }
      else
         scnt++;                                /* count suppressed   */
      disp += numb;                             /* adjust displacement*/
    }

/**********************************************************************/
/* Close all files and return                                         */
/**********************************************************************/
   close( f );                                  /* close input  file  */

}
