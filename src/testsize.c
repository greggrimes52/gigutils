#include <stdio.h>

int main()
{
   printf("%3d is the sizeof( char   )\n", (int)sizeof( char   ) );
   printf("%3d is the sizeof( short  )\n", (int)sizeof( short  ) );
   printf("%3d is the sizeof( int    )\n", (int)sizeof( int    ) );
   printf("%3d is the sizeof( long   )\n", (int)sizeof( long   ) );
   printf("%3d is the sizeof( float  )\n", (int)sizeof( float  ) );
   printf("%3d is the sizeof( double )\n", (int)sizeof( double ) );
   printf("\n");
#define show(x) printf("%3d is the sizeof( \"%s\" )\n",(int)sizeof(x),x)
   show("");
   show(".");
   show("....+");
   show("....+....1");
   show("....+....1....+....2....+....3....+....4....+....5");
   return 0;
}
