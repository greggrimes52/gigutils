#ifndef   USARGS
/**********************************************************************/
/* Declare the function                                               */
/**********************************************************************/
/*                                                                    */
/* string = USARGS();                                                 */
/*                                                                    */
/* string points to the first non-flag argument.  Successive calls    */
/* return successive non-flag arguments.                              */
/*                                                                    */
#ifdef _NOPROTOS
   extern char *usargs();
#else
   extern char *usargs(int,char**);
#endif

/**********************************************************************/
/* Declare the static structure                                       */
/**********************************************************************/
#ifndef   USRTN
   extern
#endif  /*USRTN*/
   int    args[256]
#ifdef    USRTN
   = {0}
#endif  /*USRTN*/
   ;

/**********************************************************************/
/* Declare the macros to invoke the function and use the arguments    */
/**********************************************************************/
#ifdef    __STDC__
#define     FLAG(x) args[#x[0]]
#else
#define     FLAG(x) args['x']
#endif

#define   USARGS() usargs(argc,argv)

#endif  /*USARGS*/
