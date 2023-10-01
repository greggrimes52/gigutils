#include "usbits.h"

unsigned char x;
unsigned char ones = 255;

main()
{
   printf("\nOne Bit Macros\n");

   x=0;    SET01(x,ones);
   printf("SET01(x,ones) = %2.2X, ",x);
   printf("GET01(x) = %2.2X\n",
           GET01(x));

   x=0;    SET02(x,ones);
   printf("SET02(x,ones) = %2.2X, ",x);
   printf("GET02(x) = %2.2X\n",
           GET02(x));

   x=0;    SET04(x,ones);
   printf("SET04(x,ones) = %2.2X, ",x);
   printf("GET04(x) = %2.2X\n",
           GET04(x));

   x=0;    SET08(x,ones);
   printf("SET08(x,ones) = %2.2X, ",x);
   printf("GET08(x) = %2.2X\n",
           GET08(x));

   x=0;    SET10(x,ones);
   printf("SET10(x,ones) = %2.2X, ",x);
   printf("GET10(x) = %2.2X\n",
           GET10(x));

   x=0;    SET20(x,ones);
   printf("SET20(x,ones) = %2.2X, ",x);
   printf("GET20(x) = %2.2X\n",
           GET20(x));

   x=0;    SET40(x,ones);
   printf("SET40(x,ones) = %2.2X, ",x);
   printf("GET40(x) = %2.2X\n",
           GET40(x));

   x=0;    SET80(x,ones);
   printf("SET80(x,ones) = %2.2X, ",x);
   printf("GET80(x) = %2.2X\n",
           GET80(x));


   printf("\nTwo Bit Macros\n");

   x=0;    SET03(x,ones);
   printf("SET03(x,ones) = %2.2X, ",x);
   printf("GET03(x) = %2.2X\n",
           GET03(x));

   x=0;    SET06(x,ones);
   printf("SET06(x,ones) = %2.2X, ",x);
   printf("GET06(x) = %2.2X\n",
           GET06(x));

   x=0;    SET0C(x,ones);
   printf("SET0C(x,ones) = %2.2X, ",x);
   printf("GET0C(x) = %2.2X\n",
           GET0C(x));

   x=0;    SET18(x,ones);
   printf("SET18(x,ones) = %2.2X, ",x);
   printf("GET18(x) = %2.2X\n",
           GET18(x));

   x=0;    SET30(x,ones);
   printf("SET30(x,ones) = %2.2X, ",x);
   printf("GET30(x) = %2.2X\n",
           GET30(x));

   x=0;    SET60(x,ones);
   printf("SET60(x,ones) = %2.2X, ",x);
   printf("GET60(x) = %2.2X\n",
           GET60(x));

   x=0;    SETC0(x,ones);
   printf("SETC0(x,ones) = %2.2X, ",x);
   printf("GETC0(x) = %2.2X\n",
           GETC0(x));


   printf("\nThree Bit Macros\n");

   x=0;    SET07(x,ones);
   printf("SET07(x,ones) = %2.2X, ",x);
   printf("GET07(x) = %2.2X\n",
           GET07(x));

   x=0;    SET0E(x,ones);
   printf("SET0E(x,ones) = %2.2X, ",x);
   printf("GET0E(x) = %2.2X\n",
           GET0E(x));

   x=0;    SET1C(x,ones);
   printf("SET1C(x,ones) = %2.2X, ",x);
   printf("GET1C(x) = %2.2X\n",
           GET1C(x));

   x=0;    SET38(x,ones);
   printf("SET38(x,ones) = %2.2X, ",x);
   printf("GET38(x) = %2.2X\n",
           GET38(x));

   x=0;    SET70(x,ones);
   printf("SET70(x,ones) = %2.2X, ",x);
   printf("GET70(x) = %2.2X\n",
           GET70(x));

   x=0;    SETE0(x,ones);
   printf("SETE0(x,ones) = %2.2X, ",x);
   printf("GETE0(x) = %2.2X\n",
           GETE0(x));


   printf("\nFour Bit Macros\n");

   x=0;    SET0F(x,ones);
   printf("SET0F(x,ones) = %2.2X, ",x);
   printf("GET0F(x) = %2.2X\n",
           GET0F(x));

   x=0;    SET1E(x,ones);
   printf("SET1E(x,ones) = %2.2X, ",x);
   printf("GET1E(x) = %2.2X\n",
           GET1E(x));

   x=0;    SET3C(x,ones);
   printf("SET3C(x,ones) = %2.2X, ",x);
   printf("GET3C(x) = %2.2X\n",
           GET3C(x));

   x=0;    SET78(x,ones);
   printf("SET78(x,ones) = %2.2X, ",x);
   printf("GET78(x) = %2.2X\n",
           GET78(x));

   x=0;    SETF0(x,ones);
   printf("SETF0(x,ones) = %2.2X, ",x);
   printf("GETF0(x) = %2.2X\n",
           GETF0(x));


   printf("\nFive Bit Macros\n");

   x=0;    SET1F(x,ones);
   printf("SET1F(x,ones) = %2.2X, ",x);
   printf("GET1F(x) = %2.2X\n",
           GET1F(x));

   x=0;    SET3E(x,ones);
   printf("SET3E(x,ones) = %2.2X, ",x);
   printf("GET3E(x) = %2.2X\n",
           GET3E(x));

   x=0;    SET7C(x,ones);
   printf("SET7C(x,ones) = %2.2X, ",x);
   printf("GET7C(x) = %2.2X\n",
           GET7C(x));

   x=0;    SETF8(x,ones);
   printf("SETF8(x,ones) = %2.2X, ",x);
   printf("GETF8(x) = %2.2X\n",
           GETF8(x));


   printf("\nSix Bit Macros\n");

   x=0;    SET3F(x,ones);
   printf("SET3F(x,ones) = %2.2X, ",x);
   printf("GET3F(x) = %2.2X\n",
           GET3F(x));

   x=0;    SET7E(x,ones);
   printf("SET7E(x,ones) = %2.2X, ",x);
   printf("GET7E(x) = %2.2X\n",
           GET7E(x));

   x=0;    SETFC(x,ones);
   printf("SETFC(x,ones) = %2.2X, ",x);
   printf("GETFC(x) = %2.2X\n",
           GETFC(x));


   printf("\nSeven Bit Macros\n");

   x=0;    SET7F(x,ones);
   printf("SET7F(x,ones) = %2.2X, ",x);
   printf("GET7F(x) = %2.2X\n",
           GET7F(x));

   x=0;    SETFE(x,ones);
   printf("SETFE(x,ones) = %2.2X, ",x);
   printf("GETFE(x) = %2.2X\n",
           GETFE(x));



   printf("\nOne Bit Macros\n");

   x=ones; SET01(x,0);
   printf("SET01(x,0) = %2.2X\n",x);

   x=ones; SET02(x,0);
   printf("SET02(x,0) = %2.2X\n",x);

   x=ones; SET04(x,0);
   printf("SET04(x,0) = %2.2X\n",x);

   x=ones; SET08(x,0);
   printf("SET08(x,0) = %2.2X\n",x);

   x=ones; SET10(x,0);
   printf("SET10(x,0) = %2.2X\n",x);

   x=ones; SET20(x,0);
   printf("SET20(x,0) = %2.2X\n",x);

   x=ones; SET40(x,0);
   printf("SET40(x,0) = %2.2X\n",x);

   x=ones; SET80(x,0);
   printf("SET80(x,0) = %2.2X\n",x);


   printf("\nTwo Bit Macros\n");

   x=ones; SET03(x,0);
   printf("SET03(x,0) = %2.2X\n",x);

   x=ones; SET06(x,0);
   printf("SET06(x,0) = %2.2X\n",x);

   x=ones; SET0C(x,0);
   printf("SET0C(x,0) = %2.2X\n",x);

   x=ones; SET18(x,0);
   printf("SET18(x,0) = %2.2X\n",x);

   x=ones; SET30(x,0);
   printf("SET30(x,0) = %2.2X\n",x);

   x=ones; SET60(x,0);
   printf("SET60(x,0) = %2.2X\n",x);

   x=ones; SETC0(x,0);
   printf("SETC0(x,0) = %2.2X\n",x);


   printf("\nThree Bit Macros\n");

   x=ones; SET07(x,0);
   printf("SET07(x,0) = %2.2X\n",x);

   x=ones; SET0E(x,0);
   printf("SET0E(x,0) = %2.2X\n",x);

   x=ones; SET1C(x,0);
   printf("SET1C(x,0) = %2.2X\n",x);

   x=ones; SET38(x,0);
   printf("SET38(x,0) = %2.2X\n",x);

   x=ones; SET70(x,0);
   printf("SET70(x,0) = %2.2X\n",x);

   x=ones; SETE0(x,0);
   printf("SETE0(x,0) = %2.2X\n",x);


   printf("\nFour Bit Macros\n");

   x=ones; SET0F(x,0);
   printf("SET0F(x,0) = %2.2X\n",x);

   x=ones; SET1E(x,0);
   printf("SET1E(x,0) = %2.2X\n",x);

   x=ones; SET3C(x,0);
   printf("SET3C(x,0) = %2.2X\n",x);

   x=ones; SET78(x,0);
   printf("SET78(x,0) = %2.2X\n",x);

   x=ones; SETF0(x,0);
   printf("SETF0(x,0) = %2.2X\n",x);


   printf("\nFive Bit Macros\n");

   x=ones; SET1F(x,0);
   printf("SET1F(x,0) = %2.2X\n",x);

   x=ones; SET3E(x,0);
   printf("SET3E(x,0) = %2.2X\n",x);

   x=ones; SET7C(x,0);
   printf("SET7C(x,0) = %2.2X\n",x);

   x=ones; SETF8(x,0);
   printf("SETF8(x,0) = %2.2X\n",x);


   printf("\nSix Bit Macros\n");

   x=ones; SET3F(x,0);
   printf("SET3F(x,0) = %2.2X\n",x);

   x=ones; SET7E(x,0);
   printf("SET7E(x,0) = %2.2X\n",x);

   x=ones; SETFC(x,0);
   printf("SETFC(x,0) = %2.2X\n",x);


   printf("\nSeven Bit Macros\n");

   x=ones; SET7F(x,0);
   printf("SET7F(x,0) = %2.2X\n",x);

   x=ones; SETFE(x,0);
   printf("SETFE(x,0) = %2.2X\n",x);



   printf("\nOne Bit Macros\n");

   printf("GET01(ones) = %2.2X\n",
           GET01(ones));

   printf("GET02(ones) = %2.2X\n",
           GET02(ones));

   printf("GET04(ones) = %2.2X\n",
           GET04(ones));

   printf("GET08(ones) = %2.2X\n",
           GET08(ones));

   printf("GET10(ones) = %2.2X\n",
           GET10(ones));

   printf("GET20(ones) = %2.2X\n",
           GET20(ones));

   printf("GET40(ones) = %2.2X\n",
           GET40(ones));

   printf("GET80(ones) = %2.2X\n",
           GET80(ones));


   printf("\nTwo Bit Macros\n");

   printf("GET03(ones) = %2.2X\n",
           GET03(ones));

   printf("GET06(ones) = %2.2X\n",
           GET06(ones));

   printf("GET0C(ones) = %2.2X\n",
           GET0C(ones));

   printf("GET18(ones) = %2.2X\n",
           GET18(ones));

   printf("GET30(ones) = %2.2X\n",
           GET30(ones));

   printf("GET60(ones) = %2.2X\n",
           GET60(ones));

   printf("GETC0(ones) = %2.2X\n",
           GETC0(ones));


   printf("\nThree Bit Macros\n");

   printf("GET07(ones) = %2.2X\n",
           GET07(ones));

   printf("GET0E(ones) = %2.2X\n",
           GET0E(ones));

   printf("GET1C(ones) = %2.2X\n",
           GET1C(ones));

   printf("GET38(ones) = %2.2X\n",
           GET38(ones));

   printf("GET70(ones) = %2.2X\n",
           GET70(ones));

   printf("GETE0(ones) = %2.2X\n",
           GETE0(ones));


   printf("\nFour Bit Macros\n");

   printf("GET0F(ones) = %2.2X\n",
           GET0F(ones));

   printf("GET1E(ones) = %2.2X\n",
           GET1E(ones));

   printf("GET3C(ones) = %2.2X\n",
           GET3C(ones));

   printf("GET78(ones) = %2.2X\n",
           GET78(ones));

   printf("GETF0(ones) = %2.2X\n",
           GETF0(ones));


   printf("\nFive Bit Macros\n");

   printf("GET1F(ones) = %2.2X\n",
           GET1F(ones));

   printf("GET3E(ones) = %2.2X\n",
           GET3E(ones));

   printf("GET7C(ones) = %2.2X\n",
           GET7C(ones));

   printf("GETF8(ones) = %2.2X\n",
           GETF8(ones));


   printf("\nSix Bit Macros\n");

   printf("GET3F(ones) = %2.2X\n",
           GET3F(ones));

   printf("GET7E(ones) = %2.2X\n",
           GET7E(ones));

   printf("GETFC(ones) = %2.2X\n",
           GETFC(ones));


   printf("\nSeven Bit Macros\n");

   printf("GET7F(ones) = %2.2X\n",
           GET7F(ones));

   printf("GETFE(ones) = %2.2X\n",
           GETFE(ones));



   return 0;
}
