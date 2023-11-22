Usage:
   cvtbt [flags] binfile txtfile

   Converts a file containing uneditable characters into an editable text
   file containing codes for the characters considered uneditable.

flags:
  --S   Suppress summary messages
   -Ln  Produce a new line after <n> bytes.  Default is 72.
   -Pn  Produce a form feed after <n> lines.  No default.
   -Gt  Consider data (1) Tektronix (2) DDL graphics data.
   -A   Use numeric codes for editable characters
        instead of the characters themselves.
   -N   Use numeric codes for uneditable characters
        instead of the characters' code names.
   -Hx  Numeric codes are produced in hexadecimal.
   -Dx  Numeric codes are produced in decimal.
   -Ox  Numeric codes are produced in octal.
where x means:
     1  [0x00], [0d000], [0o000].
     2  [0x0],  [0],     [00].

Version 1.05  Copyright (c) 1989,2023 Greg Grimes
