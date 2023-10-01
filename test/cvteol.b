Usage:
   cvteol [flags] infile outfile

   Copies infile to outfile converting the end-of-line
   characters as needed to PC, UNIX, or Macintosh style
   end-of-line characters.  The default is to end lines
   with single newlines (UNIX style text).

   Please note that PC and UNIX style print files use
   carriage returns for overstiking.  Each of these
   will be turned into a new end-of-line.

flags:
   -M   make each line end with a single carriage
        return (Macintosh style text)
   -P   make each line end with a carriage return-
        line feed pair (PC style text)
   -U   make each line end with a single newline
        (UNIX style text)
   -V   massive volumes of debug output

Version 1.04  Copyright (c) 1989,1995 Greg Grimes
