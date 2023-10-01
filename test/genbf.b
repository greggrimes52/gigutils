Usage:
   genbf [flags] filename

   Builds a file with various binary structures.

flags:
   -Rn  include n blocks containing 0xFF through 0x00
   -Bn  include n "custom" blocks
   -Cn  custom blocks use byte value n (0<=n<=255)
   -Ln  custom blocks are n bytes long (1<=n<=32767)
   -Fn  include n blocks containing 0x00 through 0xFF
   -V   Verbose:  include debugging information

Version 1.05  Copyright (c) 1989,1995 Greg Grimes
