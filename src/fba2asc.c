#include <errno.h>
#include <stdio.h>

   static char buffer[1024];

main(argc,argv)
 int argc;
 char **argv;
{
   FILE *fbafile;
   FILE *ascfile;
   char *bufs;
   char *bufe;
   int  first;

   if(argc < 3)
     {
      printf("Usage:  %s <fbaFile> <ascFile>\n",argv[0]);
      exit(0);
     }

   if(!(fbafile=fopen(argv[1],"rb")))
     {
      printf("Unable to open input (fba) file \"%s\".",argv[1]);
      perror(argv[0]);
      exit(1);
     }

   if(!(ascfile=fopen(argv[2],"wb")))
     {
      printf("Unable to open output (asc) file \"%s\".",argv[2]);
      perror(argv[0]);
      exit(1);
     }

   first = 1;
   while(1)
     {
      /* Read in the line to process next */
      bufs = buffer + 10;
      bufe = fgets(bufs,1014,fbafile);
      if(bufe == NULL) break;

      /* Trim blanks and trailing line feed */
      bufe = bufs + strlen(bufs) - 1;
      if   (*bufe == 0x0A) *bufe-- = 0;
      if   (*bufe == 0x0D) *bufe-- = 0;
      if   ( bufe <  bufs) *bufe   = 0;
      while(*bufe ==  ' ') *bufe-- = 0;
      if   ( bufe <  bufs) *++bufe = ' ';
      *++bufe = 0x0D;

      /* Now handle Carriage Control */
      switch(*bufs)
        {
         case '+':
            bufs++;
            break;
         case ' ':
            bufs[0] = 0x0A; /* LF */
            break;
         case '1':
            bufs -= 1;
            bufs[0] = 0x0A; /* LF */
            bufs[1] = 0x0C; /* FF */
            break;
         case '-':
            bufs -= 4;
            bufs[0] = 0x0A; /* LF */
            bufs[1] = 0x0D; /* CR */
            bufs[2] = 0x0A; /* LF */
            bufs[3] = 0x0D; /* CR */
            bufs[4] = 0x0A; /* LF */
            break;
         case '0':
            bufs -= 2;
            bufs[0] = 0x0A; /* LF */
            bufs[1] = 0x0D; /* CR */
            bufs[2] = 0x0A; /* LF */
            break;
         default:
            fprintf(stderr,"Unknown CC:  '%c' (0x%2.2X)\n",*bufs,*bufs);
            bufs++;
        }
      if(first && *bufs == 0x0A) bufs++; 
      first = 0;
      fputs(bufs,ascfile);
     }
   fputc(0x0A,ascfile);
   fclose(ascfile);
   fclose(fbafile);
}
