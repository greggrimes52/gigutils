#ifndef   USBITS
#define   USBITS

/***
* Insert or Extract bit fields from variables
***/


#define  GET(x,m)     ((x) & (m))
#define  SET(x,m,v)   ((x) = ((x) & ~(m)) | ((v) & (m)))
#define SGET(x,m,s)  (((x) & (m)) >> (s))
#define SSET(x,m,s,v) ((x) = ((x) & ~(m)) | (((v) << (s)) & (m)))


/* 1 bit fields */
#define GET01(x)    GET(x,0x01)
#define SET01(x,v)  SET(x,0x01,v)

#define GET02(x)   SGET(x,0x02,1)
#define SET02(x,v) SSET(x,0x02,1,v)

#define GET04(x)   SGET(x,0x04,2)
#define SET04(x,v) SSET(x,0x04,2,v)

#define GET08(x)   SGET(x,0x08,3)
#define SET08(x,v) SSET(x,0x08,3,v)

#define GET10(x)   SGET(x,0x10,4)
#define SET10(x,v) SSET(x,0x10,4,v)

#define GET20(x)   SGET(x,0x20,5)
#define SET20(x,v) SSET(x,0x20,5,v)

#define GET40(x)   SGET(x,0x40,6)
#define SET40(x,v) SSET(x,0x40,6,v)

#define GET80(x)   SGET(x,0x80,7)
#define SET80(x,v) SSET(x,0x80,7,v)


/* 2 bit fields */
#define GET03(x)    GET(x,0x03)
#define SET03(x,v)  SET(x,0x03,v)

#define GET06(x)   SGET(x,0x06,1)
#define SET06(x,v) SSET(x,0x06,1,v)

#define GET0C(x)   SGET(x,0x0C,2)
#define SET0C(x,v) SSET(x,0x0C,2,v)

#define GET18(x)   SGET(x,0x18,3)
#define SET18(x,v) SSET(x,0x18,3,v)

#define GET30(x)   SGET(x,0x30,4)
#define SET30(x,v) SSET(x,0x30,4,v)

#define GET60(x)   SGET(x,0x60,5)
#define SET60(x,v) SSET(x,0x60,5,v)

#define GETC0(x)   SGET(x,0xC0,6)
#define SETC0(x,v) SSET(x,0xC0,6,v)


/* 3 bit fields */
#define GET07(x)    GET(x,0x07)
#define SET07(x,v)  SET(x,0x07,v)

#define GET0E(x)   SGET(x,0x0E,1)
#define SET0E(x,v) SSET(x,0x0E,1,v)

#define GET1C(x)   SGET(x,0x1C,2)
#define SET1C(x,v) SSET(x,0x1C,2,v)

#define GET38(x)   SGET(x,0x38,3)
#define SET38(x,v) SSET(x,0x38,3,v)

#define GET70(x)   SGET(x,0x70,4)
#define SET70(x,v) SSET(x,0x70,4,v)

#define GETE0(x)   SGET(x,0xE0,5)
#define SETE0(x,v) SSET(x,0xE0,5,v)


/* 4 bit fields */
#define GET0F(x)    GET(x,0x0F)
#define SET0F(x,v)  SET(x,0x0F,v)

#define GET1E(x)   SGET(x,0x1E,1)
#define SET1E(x,v) SSET(x,0x1E,1,v)

#define GET3C(x)   SGET(x,0x3C,2)
#define SET3C(x,v) SSET(x,0x3C,2,v)

#define GET78(x)   SGET(x,0x78,3)
#define SET78(x,v) SSET(x,0x78,3,v)

#define GETF0(x)   SGET(x,0xF0,4)
#define SETF0(x,v) SSET(x,0xF0,4,v)


/* 5 bit fields */
#define GET1F(x)    GET(x,0x1F)
#define SET1F(x,v)  SET(x,0x1F,v)

#define GET3E(x)   SGET(x,0x3E,1)
#define SET3E(x,v) SSET(x,0x3E,1,v)

#define GET7C(x)   SGET(x,0x7C,2)
#define SET7C(x,v) SSET(x,0x7C,2,v)

#define GETF8(x)   SGET(x,0xF8,3)
#define SETF8(x,v) SSET(x,0xF8,3,v)


/* 6 bit fields */
#define GET3F(x)    GET(x,0x3F)
#define SET3F(x,v)  SET(x,0x3F,v)

#define GET7E(x)   SGET(x,0x7E,1)
#define SET7E(x,v) SSET(x,0x7E,1,v)

#define GETFC(x)   SGET(x,0xFC,2)
#define SETFC(x,v) SSET(x,0xFC,2,v)


/* 7 bit fields */
#define GET7F(x)    GET(x,0x7F)
#define SET7F(x,v)  SET(x,0x7F,v)

#define GETFE(x)   SGET(x,0xFE,1)
#define SETFE(x,v) SSET(x,0xFE,1,v)

#endif /* USBITS */
