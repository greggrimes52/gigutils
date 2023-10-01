#include "us.h"                          /* declare:  box specifics   */
#include "usargs.h"                      /* declare:  args            */
#include "usdump.h"                      /* declare:  usdump proto    */
#include <stdio.h>                       /* declare:  sprintf         */

/**********************************************************************/
/* Function to display hex dump of buffer                             */
/**********************************************************************/
 long usdump(buf,cnt,disp)
 unsigned
 char __far *buf;                        /* buffer to dump            */
 int             cnt;                    /* buffer size               */
 long                disp;               /* displacement to show      */
{

/**********************************************************************/
/* Declare local variables                                            */
/**********************************************************************/
   int            same = 0;              /* line same as last line    */
   int            scnt = 0;              /* suppressed line counter   */
   int            p    = 0;              /* read buffer index         */
   int            numb;                  /* number of bytes in line   */
   int            c;                     /* character from buffer     */
   int            n;                     /* character count in buffer */
   int            i;                     /* index for loop            */
   unsigned char *hptr;                  /* pointer to hbuf           */
   unsigned char *pptr;                  /* pointer to pbuf           */
   unsigned char  hbuf[41];              /* buffer for hex conversion */
   unsigned char  pbuf[17];              /* buffer for printables     */
   unsigned char  cbuf[16];              /* buffer for previous line  */
   unsigned char  sbuf[16];              /* buffer for current  line  */

/**********************************************************************/
/* Extract option flags and print parameters for debug                */
/**********************************************************************/
   if(FLAG(z))
     {
      printf("   USDUMP:\n");
      printf("      buffer = %lp\n", buf);
      printf("      size   = %d\n",  cnt);
      printf("      disp   = %ld\n", disp);
      printf("      flag x = %d\n",  FLAG(x));
      printf("      flag y = %d\n",  FLAG(y));
      printf("      flag z = %d\n",  FLAG(z));
     }

/**********************************************************************/
/* Dump buffer contents in hex                                        */
/**********************************************************************/
   n = cnt;                                     /* set buffer counter */
   cbuf[0] = buf[0] ^ 15;                       /* insure not same    */
   while( n > 0 )                               /* for every buffer   */
    {
      hptr = hbuf;                              /* initialize hptr    */
      pptr = pbuf;                              /* initialize pptr    */
      numb = 0;                                 /* initialize counter */
      for ( i = 0; i < 16; i++ )                /* loop 16 times      */
       {
         c = buf[p++];                          /* get a buffer char  */
         if ( i && i %  4 == 0 ) *hptr++ = ' ';
         if ( i && i %  8 == 0 ) *hptr++ = ' ';
         if ( i && i % 16 == 0 ) *hptr++ = ' ';
         sbuf[i] = c;                           /* same check buffer  */
         sprintf(hptr,"%02x",c);                /* format char in hex */
         hptr += 2;                             /* advance pointer    */
         *pptr = c;                             /* format unprintable */
         switch(FLAG(y))
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
              n = 0;                            /*  we're done        */
              break;                            /*  get out           */
           }
       }
      same = 1;                                 /* assume duplicate   */
      for ( i = 0; i < 16; i++ )                /* check              */
         if ( cbuf[i] != sbuf[i] )              /*  current/previous  */
           {
              same = 0;                         /*  if not the same   */
              break;                            /*  be sure to print  */
           }
      if ( !same || n == 0 || FLAG(x) )         /* if not the same    */
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
/* Return next displacement value                                     */
/**********************************************************************/
   return(disp);
}
