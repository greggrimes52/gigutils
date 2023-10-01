main(argc,argv,envp)
 int argc;
 char    *argv[];
 char         *envp[];
{
   int i=0;
   while (envp[i]!=0)
      printf("envp[%02d] = \"%s\"\n",i,envp[i++]);
   return 0;
}
