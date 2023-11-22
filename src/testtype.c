#include <ctype.h>
#include <stdio.h>

int main(argc,argv)
 int argc;
 char *argv[];
{
   int c;
   int x;

   for(c=0;c<256;c++)
      {
      x = isprint(c)? c : ' ';
      printf(" %c %3d (0x%2.2X):  %s %s %s %s %s %s %s %s %s %s %s\n",
               x, c,     c
         ,isalnum(c)?   "alnum":"     "
         ,isalpha(c)?   "alpha":"     "
         ,iscntrl(c)?   "cntrl":"     "
         ,isdigit(c)?   "digit":"     "
         ,isgraph(c)?   "graph":"     "
         ,islower(c)?   "lower":"     "
         ,isprint(c)?   "print":"     "
         ,ispunct(c)?   "punct":"     "
         ,isspace(c)?   "space":"     "
         ,isupper(c)?   "upper":"     "
         ,isxdigit(c)? "xdigit":"      "
         );
      }

   return 0;
}
