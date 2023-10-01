#ifndef   US
#define   US
/**********************************************************************/
/* Machine Dependent Processing                                       */
/**********************************************************************/
#ifndef   DOS
#define   __far
#define   O_RAW        0  
#endif

#ifndef   NULL
#undef    NULL
#endif
#define   NULL         0L

/**********************************************************************/
/* Determine Name of Utility from ARGV[0]                             */
/**********************************************************************/
#ifdef DOS
#define US_NAME(arg) if(arg=strchr(argv[0],'.')) *arg = '\0'; \
                     arg = argv[0]; \
                     while(*arg) {*arg=tolower(*arg);arg++;} \
                     arg = argv[0];
#else
#define US_NAME(arg) arg = argv[0] + strlen(argv[0]); \
                     while(arg != argv[0] && arg[-1] != '/') arg--;
#endif

/**********************************************************************/
/* Declare Utility Subsystem Messages                                 */
/**********************************************************************/
#define   US_RELEASE   "1"
#define   US_COPYRIGHT "Version %s.%s  Copyright (c) 1989,1997 Greg Grimes\n",\
                       US_RELEASE,VERSION
#define   US_FLAGV     "   -V   Verbose:  include debugging information\n"
#define   US_FLAGX     "   -X   Show all lines in hexadecimal dump\n"
#define   US_FLAGY     "   -Yn  1: show graphics   2: show most all chars\n"
#define   US_FLAGZ     "   -Z   Incredibly cryptic additional info\n"

#endif  /*US*/
