#ifndef   USDUMP
/**********************************************************************/
/* Declare the function                                               */
/**********************************************************************/
#ifdef _NOPROTOS
 extern long usdump();
#else
 extern long usdump(unsigned char __far *,int,long);
#endif

/**********************************************************************/
/* Declare the macro to invoke the function                           */
/**********************************************************************/
#define   USDUMP(ptr,cnt,disp) \
 usdump(\
 (unsigned char __far *)(ptr), \
                   (int)(cnt), \
                  (long)(disp) \
 )

#endif  /*USDUMP*/
