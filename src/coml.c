#define   VERSION   "04"
#include "us.h"
#include "usargs.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#ifndef _NOSTDLIB
#include <stdlib.h>
#endif

#define   CHAR            unsigned char
#define   MAX             32
#define   ITEMSIZE        256

   static int   spit;
   static int   nomore;
   static int   nodiffs = 1;
   static int   notitle = 1;
   static int   count   = 0;
   static int   size    = 12;
   static char *title   = "items in these lists";
   static int   num;
   static FILE *file[MAX];
   static int   next[MAX];
   static char *name[MAX];
   static CHAR *item[MAX];
   static CHAR  line[MAX][ITEMSIZE];
   static char    hyphens[ITEMSIZE+1];

main(argc,argv)
 int argc;
 char **argv;
{
   register int   i,rc;
   register char *arg;
   register CHAR *lowest;

/**********************************
 * Parse the command line options *
 **********************************/
   while(arg=USARGS())
     {
      if (num >= MAX)
        {
         fprintf(stderr,
            "Oops!  We can't handle more than MAX (%d) files.",MAX);
         exit(2);
        }
      name[num] =       arg;
      file[num] = fopen(arg,"r");
      if (file[num])
         num++;
      else
        {
         fprintf(stderr,"Unable to open file %s for read.\n",arg);
         exit(2);
        }
     }

   if (FLAG(S)) size = FLAG(S);

/************************
 * Check we can proceed *
 ************************/
   if (num < 2 || FLAG(?))
     {
      US_NAME(arg);
      printf("Usage:\n");
      printf("   %s [flags] file1 file2...\n",arg);
      printf("\n");
      printf("   Reads two or more files, each containing sorted\n");
      printf("   lists of items, and displays the differences as\n");
      printf("   missing items in a table.  A maximum of %d files\n",MAX);
      printf("   can be processed concurrently, and each item, or\n");
      printf("   line, cannot exceed %d bytes.\n",ITEMSIZE-1);
      printf("\n");
      printf("flags:\n");
      printf("   -A   Include common entries in lists.\n");
      printf("   -C   Show only the common entries.\n");
      printf("   -L   Show a list instead of a table.\n");
      printf("   -Sn  Size of table columns (now %d bytes).\n",size);
#if 0
      printf("   -T 'title'  Substitute title for differences.\n");
#endif
      printf("   -V   Debug mode.  Read the code.\n");
      printf("\n");
      printf(US_COPYRIGHT);
      exit(0);
     }

/******************************
 * If debug, show all options *
 ******************************/
   if (FLAG(V))
     {
      fprintf(stderr,"File names:\n");
      for(i=0;i<num;i++)
         fprintf(stderr,"   name[%d] = %s\n",i,name[i]);
     }

/********************************
 * A little more initialization *
 ********************************/
   for(i=0;i<ITEMSIZE;i++)
      hyphens[i] = '-';
   hyphens[ITEMSIZE] = 0;

/*******************************************************
 * Get the first line from each file to prime the pump *
 *******************************************************/
   for(i=0;i<num;i++)
     {
      line[i][ITEMSIZE-1] = 0;
      fgets(line[i],ITEMSIZE-1,file[i]);
      if (!feof(file[i]))
         line[i][strlen(line[i])-1] = 0;
      else
        {
         line[i][0] = 128;
         line[i][1] = 0;
        }
     }

/*******************
 * More debug code *
 *******************/
   if (FLAG(V))
     {
      fprintf(stderr,"First lines of files:\n");
      for(i=0;i<num;i++)
         fprintf(stderr,"   file[%d] = '%s'\n",i,line[i]);
     }

/************************************
 * Run through and show differences *
 ************************************/
   while(1)
     {
      /* Point to the next item from each file */
      count++;
      for(i=0;i<num;i++)
         item[i] = line[i];

      /* Determine the lowest alphabetical line */
      spit = 0;
      lowest = line[0];
      for(i=1;i<num;i++)
        {
         if ((rc=strcmp(lowest,line[i])) != 0)
           {
            spit = 1;
            nodiffs = 0;
            if (rc > 0) lowest = line[i];
           }
        }

      /* Substitute dashes for columns missing this line */
      for(i=0;i<num;i++)
        {
         if ((rc=strcmp(lowest,line[i])) == 0)
            next[i] = 1;
         else
           {
            next[i] = 0;
            item[i] = "-";
           }
        }

      /* If we're printing only common items, reverse sense of spit */
      if (FLAG(C)) spit = !spit;

      /* Spit out this observation, if called for */
      if (spit || FLAG(A))
        {
         if (FLAG(L))
           {
            for(i=0;i<num;i++)
               if ((rc=strcmp(item[i],"-"))!=0)
                  break;
            if (rc==0) i--;
            printf("%s\n",item[i]);
           }
         else
           {
            if (notitle)
              {
               notitle = 0;
               printf("%s between %s\n  ",
                  (FLAG(C))?"Common items":"Differences",
                  title);
               for(i=0;i<num;i++)
                  printf(" %-*.*s",size,size,name[i]);
               printf("\n  ");
               for(i=0;i<num;i++)
                  printf(" %-*.*s",size,size,hyphens);
               printf("\n");
              }
            printf("  ");
            for(i=0;i<num;i++)
               printf(" %-*.*s",size,size,item[i]);
            printf("\n");
           }
        }

      /* Read the next line from the appropriate files */
      for(i=0;i<num;i++)
         if (next[i])
           {
            if (line[i][0] != 128)
              {
               fgets(line[i],ITEMSIZE,file[i]);
               if (!feof(file[i]))
                  line[i][strlen(line[i])-1] = 0;
               else
                 {
                  line[i][0] = 128;
                  line[i][1] = 0;
                 }
              }
           }

      /* Continue loop if more to go */
      nomore = 1;
      for(i=0;i<num;i++)
         if (line[i][0] != 128) nomore = 0;
      if (nomore) break;

     }

/***********************************************************
 * Spit out a positive summary, if nothing else was output *
 ***********************************************************/
   if (nodiffs && !FLAG(L))
      printf("All %4d %s are the same.\n",count,title);

/*******************
 * Close all files *
 *******************/
   for(i=0;i<num;i++)
      fclose(file[i]);
}
