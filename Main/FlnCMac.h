/** 
 * \file  flnCMac.h 
 * \brief Типовые макросы для удобства программирования 
*/ 

#ifndef  FLNCMAC_H
#define  FLNCMAC_H

//Определения типов величин
typedef unsigned char           U8;    /*  8 bit unsigned */
typedef signed char             S8;    /*  8 bit signed   */
typedef unsigned short          U16;   /* 16 bit unsigned */
typedef signed short            S16;   /* 16 bit signed */
typedef unsigned long int       U32;   /* 32 bit unsigned */
typedef signed long int         S32;   /* 32 bit signed */

//Макросы установки, сброса и тестирования бита
#define BIT_SET(address,bit)    (address |= (1 << bit))
#define BIT_CLR(address,bit)    (address &= ~(1 << bit))
#define BIT_TEST(address,bit)   (address & (1 << bit))
#define BIT_XOR(address,bit)    (address ^= (1 << bit))

#endif // end of FLNCMAC_H
