#define   VERSION   "05"
#include "us.h"
#include "usargs.h"
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#ifndef _NOSTDLIB
#include <stdlib.h>
#endif

   static struct tm *tmptr;
   static long       tvalue;
   static long       convert();

   static int        showday;
   static int        showdate;
   static int        showtime;

   static char      *weekday[] = {"Sunday",  "Monday",  "Tuesday","Wednesday",
                                  "Thursday","Friday",  "Saturday"};
   static char      *month[]   = {"January", "February","March",
                                  "April",   "May",     "June",
                                  "July",    "August",  "September",
                                  "October", "November","December"};
   static char      *number[]  = {NULL,   "one", "two","three",
                                  "four", "five","six","seven",
                                  "eight","nine","ten","eleven","twelve"};
   static char      *minute[]  = {NULL,"five","ten","a quarter",
                                  "twenty","twenty-five"};
   static char      *about[]   = {"nearly","almost",NULL,
                                  "just past","just after"};
   static char      *geton[]   = {"comin' up on",
                                  "pret' near",
                                  "just at",
                                  "shufflin' past",
                                  "done left behind"};

#ifdef _NOPROTOS
   static int        do_it();
   static int        print_cute();
   static long       convert();
#else
   static int        do_it(long);
   static int        print_cute(struct tm *);
   static long       convert(char*);
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
   int   i;

/**********************************************************************/
/* Process command line arguments and get first address               */
/**********************************************************************/
   arg=USARGS();

/**********************************************************************/
/* Show help, if requested                                            */
/**********************************************************************/
   if (FLAG(?))
      {
      US_NAME(arg)
      printf("Usage:\n");
      printf("   %s [flags] [value]...\n",arg);
      printf("\n");
      printf("   Displays the current date and time in one of a variety\n");
      printf("   of formats.  A time value may be substituted for the\n");
      printf("   current time by entering the number of seconds since\n");
      printf("   midnight, Jan 1, 1970, as a single, numeric value.\n");
      printf("\n");
      printf("flags:\n");
      printf("        To display the day of the week:\n");
      printf("   -Wn  (1) Sunday             (2) Sun\n");
      printf("        To display the date:\n");
      printf("   -Cn  (1) November 13, 1989  (2) 13Nov89\n");
      printf("   -Dn  (1) 11/13/89           (2) 89/11/13\n");
      printf("   -Jn  (1) 89.317             (2) 89317\n");
      printf("        To display the time:\n");
      printf("   -Tn  (1) 07:29:33pm         (2) 19:29:33\n");
      printf("   -Qn  (1) It's just at noon  (2) It's noon\n");
      printf("        Miscellaneous:\n");
      printf(US_FLAGV);
      printf("\n");
      printf(US_COPYRIGHT);
      exit(0);
      }

/**********************************************************************/
/* Default options processing                                         */
/**********************************************************************/
   i = FLAG(c) + FLAG(d) + FLAG(j) +
       FLAG(t) + FLAG(q) + FLAG(w);
   if (i == 0)
      {
      FLAG(w) = 1;
      FLAG(c) = 1;
      FLAG(t) = 1;
      }
   showday  = FLAG(w);
   showdate = FLAG(c)+FLAG(d)+FLAG(j);
   showtime = FLAG(t)+FLAG(q);

/**********************************************************************/
/* Process the arguments                                              */
/**********************************************************************/
   if(arg)
      {
      do {
         if ((tvalue=convert(arg)) == -1)
            printf("   Skipping argument %s.\n",arg);
         else
            do_it(tvalue);
         } while(arg=USARGS());
      }
   else             
      {
      tvalue=time(NULL);
      do_it(tvalue);
      }

/**********************************************************************/
/* Return                                                             */
/**********************************************************************/
   return 0;

}



/*******************************/
/*******************************/
/**                           **/
/** Date/Time Display Routine **/
/**                           **/
/*******************************/
/*******************************/
static int do_it(tvalue)
 long tvalue;
{
   char *ampm;

/**********************************************************************/
/* Display date/time before conversion, if requested                  */
/**********************************************************************/
   if (FLAG(v))
      {
      printf("DEBUG:\n");
      printf("   tvalue   = %ld (0x%lX)\n",tvalue,tvalue);
      }

/**********************************************************************/
/* Convert time to date/time pieces                                   */
/**********************************************************************/
   tmptr = localtime(&tvalue);
   if (FLAG(v))
      {
      printf("DEBUG:  localtime returned,\n");
      printf("   tm_sec   = %d\n",tmptr->tm_sec);
      printf("   tm_min   = %d\n",tmptr->tm_min);
      printf("   tm_hour  = %d\n",tmptr->tm_hour);
      printf("   tm_mday  = %d\n",tmptr->tm_mday);
      printf("   tm_mon   = %d\n",tmptr->tm_mon);
      printf("   tm_year  = %d\n",tmptr->tm_year);
      printf("   tm_wday  = %d\n",tmptr->tm_wday);
      printf("   tm_yday  = %d\n",tmptr->tm_yday);
      printf("   tm_isdst = %d\n",tmptr->tm_isdst);
      }

/**********************************************************************/
/* Display the word "On," if required                                 */
/**********************************************************************/
   if (FLAG(q) && (showday+showdate))
      printf("On ");

/**********************************************************************/
/* Display the day of the week                                        */
/**********************************************************************/
   if (showday)
      {
      if (FLAG(w)>1)
         printf("%3.3s",weekday[tmptr->tm_wday]);
      else
         printf("%s",   weekday[tmptr->tm_wday]);
      if (showdate+showtime) printf(", ");
      }

/**********************************************************************/
/* Display the date                                                   */
/**********************************************************************/
   if (showdate)
      {
      if (FLAG(c)==1)
         printf("%s %d, %d",
            month[tmptr->tm_mon],tmptr->tm_mday,tmptr->tm_year+1900);
      else if (FLAG(c)==2)
         printf("%2.2d%3.3s%2.2d",
            tmptr->tm_mday,month[tmptr->tm_mon],tmptr->tm_year);
      else if (FLAG(d)==1)
         printf("%2.2d/%2.2d/%2.2d",
            tmptr->tm_mon+1,tmptr->tm_mday,tmptr->tm_year);
      else if (FLAG(d)==2)
         printf("%2.2d/%2.2d/%2.2d",
            tmptr->tm_year,tmptr->tm_mon+1,tmptr->tm_mday);
      else if (FLAG(j)==1)
         printf("%2.2d.%3.3d",
            tmptr->tm_year,tmptr->tm_yday);
      else if (FLAG(j)==2)
         printf("%2.2d%3.3d",
            tmptr->tm_year,tmptr->tm_yday);
      if (showtime) printf(", ");
      }

/**********************************************************************/
/* Display the time of day                                            */
/**********************************************************************/
   if (showtime)
      {
      if (FLAG(t)==1)
         {
         ampm = "am";
         if (tmptr->tm_hour == 12) ampm = "pm";
         if (tmptr->tm_hour ==  0) tmptr->tm_hour = 12;
         if (tmptr->tm_hour  > 12)
            {
            ampm = "pm";
            tmptr->tm_hour  -= 12;
            }
         printf("%2.2d:%2.2d:%2.2d%s",
            tmptr->tm_hour,tmptr->tm_min,tmptr->tm_sec,ampm);
         }
      else if (FLAG(t)==2)
         printf("%2.2d:%2.2d:%2.2d",
            tmptr->tm_hour,tmptr->tm_min,tmptr->tm_sec);
      else if (FLAG(q)) 
         print_cute(tmptr);
      }

/**********************************************************************/
/* Return                                                             */
/**********************************************************************/
   printf("\n");
   return 0;

}


/************************/
/************************/
/**                    **/
/** Display Cute Time  **/
/**                    **/
/************************/
/************************/
static int print_cute(tmptr)
 struct tm *tmptr;
{
   int  min,hour,chunk,after;
   char *afto,*kinda,*miname,*ofday,cap;

   hour = tmptr->tm_hour;
   min  = tmptr->tm_min;

                         cap = 'I';
   if (showday+showdate) cap = 'i';

   after = 1;
   if (min > 32)
      {
      min = 60 - min;
      hour ++;
      after = 0;
      }
   chunk  = (min+2)/5;
   min    = min - (chunk*5) + 2;
   if (after == 0)
      min = 4 - min;

   miname = minute[chunk];

   if (FLAG(q)==1)
      {
      kinda = geton[min];
      afto  = (after)? "after" : "til";
                       ofday = "in the morning";
      if (hour ==  0)  ofday = "midnight";
      if (hour == 12) {ofday = "noon"; hour=0;}
      if (hour  > 12)  ofday = "in the afternoon";
      if (hour  > 16)  ofday = "in the evening";
      if (hour  > 20)  ofday = "at night";
      if (hour  > 12)  hour -= 12;
      }
   else
      {
      kinda = about[min];
      afto  = (after)? "past" : "to";
      if (hour ==  0)  hour  = 12;
      if (hour  > 12)  hour -= 12;
      if (chunk == 0)
         ofday = "o'clock";
      else
         {
         ofday = number[hour];
         hour  = 0;
         }
      }

   if (chunk == 6)
      {
      miname = "half";
      afto   = "past";
      }

                       printf("%ct's ",cap);
   if (kinda  != NULL) printf("%s ",   kinda);
   if (miname != NULL) printf("%s %s ",miname,afto);
   if (hour)           printf("%s ",   number[hour]);
                       printf("%s.",   ofday);

   if (FLAG(v))
      {
      printf("\nDEBUG:  Cute values.\n");
      printf("   tm_hour = %d\n",tmptr->tm_hour);
      printf("   tm_min  = %d\n",tmptr->tm_min);
      printf("   hour    = %d\n",hour);
      printf("   chunk   = %d\n",chunk);
      printf("   min     = %d",  min);
      }

   return 0;

}


/************************/
/************************/
/**                    **/
/** Conversion Routine **/
/**                    **/
/************************/
/************************/
static long convert(arg)
 char *arg;
{
   int  j,base,byte;
   long value;

   if (FLAG(v)) printf("DEBUG:  Conversion of %s.\n",arg);
   value = 0;
   base  = 0;
   j     = 0;
   if ('1'<=arg[j] && arg[j]<='9')
      {
      value = arg[j]-'0';
      base  = 10;
      j++;
      }
   else if ('0'==arg[j])
      {
      base = 8;
      j++;
      if      (toupper(arg[j]) == 'X') {base=16; j++;}
      else if (toupper(arg[j]) == 'D') {base=10; j++;}
      else if (toupper(arg[j]) == 'O') {base= 8; j++;}
      }
   if (FLAG(v))
      printf("   j=%2d, arg[j]=%c, base=%3d, value=%ld (0x%lX)\n",
         j-1,arg[j-1],base,value,value);
   if (base == 0)
      {
      printf("   Argument is not a recognizable numeric constant.\n");
      return -1;
      }
   while(arg[j])
      {
      byte = 0;
      if      ('0'<=arg[j] && arg[j]<='9') byte = arg[j]-'0';
      else if ('A'<=arg[j] && arg[j]<='F') byte = arg[j]-'A'+10;
      else if ('a'<=arg[j] && arg[j]<='f') byte = arg[j]-'a'+10;
      else         
         {
         printf("   Character %c is not a valid digit.\n",arg[j]);
         return -1;
         }
      if (byte >= base)
         {
         printf("   Character %c is invalid for base %d.\n",arg[j],base);
         return -1;
         }
      value = value * base + byte;
      if (FLAG(v))
         printf("   j=%2d, arg[j]=%c, byte=%3d, value=%ld (0x%lX)\n",
            j,arg[j],byte,value,value);
      j++;
      }

   return value;
}
