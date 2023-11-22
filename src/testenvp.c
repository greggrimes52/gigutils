#include <stdio.h>

int main(argc,argv,envp)
 int     argc;
 char        *argv[];
 char             *envp[];
{
   int i=0;
   if ( (argc <= 1) ||
        (argv[1][0] != '-') ||
        (argv[1][1] != '?') ||
        (argv[1][2] !=   0) )
     {
      while (envp[i]!=0)
         printf("envp[%02d] = \"%s\"\n",i,envp[i++]);
     }
   else
     {
      printf("Prints the environment variables "
             "which are different in each environment.\n");
     }
   return 0;
}
