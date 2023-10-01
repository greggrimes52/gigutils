#include "us.h"
#define   USRTN 1
#include "usargs.h"                      /* declare:  USARGS flags    */
#include <ctype.h>                       /* declare:  isalpha         */
#ifndef _NOSTDLIB
#include <stdlib.h>                      /* declare:  atoi            */
#endif
#ifdef    DOS
#define   ISarg(char)  (char == '-' || char == '/')
#else
#define   ISarg(char)  (char == '-')
#endif

/**********************************************************************/
/* Function to parse argument flags                                   */
/**********************************************************************/
 char *usargs(argc,argv)
 int          argc;                      /* argument count            */
 char             *argv[];               /* argument string array     */
{

/**********************************************************************/
/* Declare local variables                                            */
/**********************************************************************/
   auto   char *argptr;                  /* pointer to argument       */
   static int   argnum;                  /* argument counter          */
   auto   int   argchar;                 /* argument character        */
   auto   int   argsign;                 /* argument negation flag    */
   auto   int   argvalue;                /* argument value            */

/**********************************************************************/
/* Check if we've already parsed all the flags                        */
/**********************************************************************/
   if(args[0]==0)
     {
      args[0] =1;

   /*******************************************************************/
   /* Loop through all arguments looking for flag indicator           */
   /*******************************************************************/
      for(argnum=0;argnum<argc;argnum++)
        {
         argsign = 1;
         argptr  = argv[argnum];
         if(ISarg(*argptr))
           {
            argptr++;
   
         /*************************************************************/
         /* Check for negation indicator                              */
         /*************************************************************/
            if(argptr[1] != '\0')
              {
               if(*argptr == '-' || *argptr == '!')
                 {
                  argptr++;
                  argsign = -1;
                 }
              }
   
         /*************************************************************/
         /* Get argument flag name (the character)                    */
         /*************************************************************/
            argchar = *argptr++;
   
         /*************************************************************/
         /* Determine argument value                                  */
         /*************************************************************/
            if(*argptr == '\0')
               argvalue = argsign;
            else
               argvalue = argsign * atoi(argptr);
   
         /*************************************************************/
         /* Assign appropriate value to args array element            */
         /*************************************************************/
            args[argchar] += argvalue;
   
         /*************************************************************/
         /* Handle folded alphabetic flags                            */
         /*************************************************************/
            if(isalpha(argchar))
              {
               argchar ^= ' ';  /* magic: change case (upper<->lower) */
               args[argchar] += argvalue;
              }
           }
        }

   /*******************************************************************/
   /* Initialize argument counter for passing back arguments          */
   /*******************************************************************/
      argnum = 0;
     }

/**********************************************************************/
/* Run through remaining arguments and return first non-flag          */
/**********************************************************************/
   for(++argnum;argnum<argc;argnum++)
     {
      argptr = argv[argnum];
      if(!ISarg(*argptr))  return argptr;
     }

/**********************************************************************/
/* We're always okay                                                  */
/**********************************************************************/
   return NULL;
}
