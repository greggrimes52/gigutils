main()
{
   printf("%3d is the sizeof( char   )\n", sizeof( char   ) );
   printf("%3d is the sizeof( short  )\n", sizeof( short  ) );
   printf("%3d is the sizeof( int    )\n", sizeof( int    ) );
   printf("%3d is the sizeof( long   )\n", sizeof( long   ) );
   printf("%3d is the sizeof( float  )\n", sizeof( float  ) );
   printf("%3d is the sizeof( double )\n", sizeof( double ) );
   printf("\n");
#define show(x) printf("%3d is the sizeof( \"%s\" )\n",sizeof(x),x)
   show("");
   show(".");
   show("....+");
   show("....+....1");
   show("....+....1....+....2....+....3....+....4....+....5");
   return 0;
}
