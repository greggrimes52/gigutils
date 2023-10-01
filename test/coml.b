Usage:
   coml [flags] file1 file2...

   Reads two or more files, each containing sorted
   lists of items, and displays the differences as
   missing items in a table.  A maximum of 32 files
   can be processed concurrently, and each item, or
   line, cannot exceed 255 bytes.

flags:
   -A   Include common entries in lists.
   -C   Show only the common entries.
   -L   Show a list instead of a table.
   -Sn  Size of table columns (now 12 bytes).
   -V   Debug mode.  Read the code.

Version 1.04  Copyright (c) 1989,1995 Greg Grimes
