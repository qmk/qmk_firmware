/*============================================================================
* File    : integer_division_uint8.h
* Purpose : macros for integer division of uint8 values
------------------------------------------------------------------------------
* Version : 1
* Date    : 15th June 2009
* Author  : Alan Bowens
------------------------------------------------------------------------------
* Based on the article "Division of integers by constants" by Nigel Jones,
* http://www.embeddedgurus.net/stack-overflow/2009/06/division-of-integers-by-constants.html
* This article is also cross posted at his website: www.rmbconsulting.us.
*
* The above article was in turn based upon a paper by Doug Jones available 
* at http://www.cs.uiowa.edu/~jones/bcd/divide.html
*
* The latest version of this file may be downloaded from my blog 
* at http://codereview.blogspot.com/.
*
* This code is supplied as is. It comes with no warranty and no guarantee. Use 
* it at your own risk. You are free to use it and modify it in any way you see 
* fit, provided that this notice is included in its entirety.
============================================================================*/

#ifndef INTEGER_DIVISION_UINT8
#define INTEGER_DIVISION_UINT8

/* macros to perform 8-bit integer division by article recipes 1 and 2 */
#define U8REC1(A, M, S) (uint8_t)( (((uint16_t)(A) * (uint16_t)(M)) >> 8u) >> (S) )
#define U8REC2(A, M, S) (uint8_t)( (((((uint16_t)(A) * (uint16_t)(M)) >> 8u) + (A)) >> 1u) >> (S) )

/* macros to perform 8-bit integer division by 3..128 */
#define U8DIVBY3(A)    U8REC1(A, 0xABu, 1u)
#define U8DIVBY4(A)    U8REC1(A, 0x80u, 1u)
#define U8DIVBY5(A)    U8REC1(A, 0xCDu, 2u)
#define U8DIVBY6(A)    U8REC1(A, 0xABu, 2u)
#define U8DIVBY7(A)    U8REC2(A, 0x25u, 2u)
#define U8DIVBY8(A)    U8REC1(A, 0x80u, 2u)
#define U8DIVBY9(A)    U8REC1(A, 0xE4u, 3u)
#define U8DIVBY10(A)    U8REC1(A, 0xCDu, 3u)
#define U8DIVBY11(A)    U8REC2(A, 0x75u, 3u)
#define U8DIVBY12(A)    U8REC1(A, 0xABu, 3u)
#define U8DIVBY13(A)    U8REC1(A, 0x9Eu, 3u)
#define U8DIVBY14(A)    U8REC2(A, 0x25u, 3u)
#define U8DIVBY15(A)    U8REC1(A, 0x89u, 3u)
#define U8DIVBY16(A)    U8REC1(A, 0x80u, 3u)
#define U8DIVBY17(A)    U8REC1(A, 0xF1u, 4u)
#define U8DIVBY18(A)    U8REC1(A, 0xE4u, 4u)
#define U8DIVBY19(A)    U8REC1(A, 0xD8u, 4u)
#define U8DIVBY20(A)    U8REC1(A, 0xCDu, 4u)
#define U8DIVBY21(A)    U8REC2(A, 0x87u, 4u)
#define U8DIVBY22(A)    U8REC2(A, 0x75u, 4u)
#define U8DIVBY23(A)    U8REC2(A, 0x65u, 4u)
#define U8DIVBY24(A)    U8REC1(A, 0xABu, 4u)
#define U8DIVBY25(A)    U8REC1(A, 0xA4u, 4u)
#define U8DIVBY26(A)    U8REC1(A, 0x9Eu, 4u)
#define U8DIVBY27(A)    U8REC1(A, 0x98u, 4u)
#define U8DIVBY28(A)    U8REC2(A, 0x25u, 4u)
#define U8DIVBY29(A)    U8REC2(A, 0x1Bu, 4u)
#define U8DIVBY30(A)    U8REC1(A, 0x89u, 4u)
#define U8DIVBY31(A)    U8REC2(A, 0x09u, 4u)
#define U8DIVBY32(A)    U8REC1(A, 0x80u, 4u)
#define U8DIVBY33(A)    U8REC1(A, 0xF9u, 5u)
#define U8DIVBY34(A)    U8REC1(A, 0xF1u, 5u)
#define U8DIVBY35(A)    U8REC1(A, 0xEBu, 5u)
#define U8DIVBY36(A)    U8REC1(A, 0xE4u, 5u)
#define U8DIVBY37(A)    U8REC1(A, 0xDEu, 5u)
#define U8DIVBY38(A)    U8REC1(A, 0xD8u, 5u)
#define U8DIVBY39(A)    U8REC2(A, 0xA5u, 5u)
#define U8DIVBY40(A)    U8REC1(A, 0xCDu, 5u)
#define U8DIVBY41(A)    U8REC1(A, 0xC8u, 5u)
#define U8DIVBY42(A)    U8REC2(A, 0x87u, 5u)
#define U8DIVBY43(A)    U8REC1(A, 0xBFu, 5u)
#define U8DIVBY44(A)    U8REC1(A, 0xBBu, 5u)
#define U8DIVBY45(A)    U8REC2(A, 0x6Du, 5u)
#define U8DIVBY46(A)    U8REC2(A, 0x65u, 5u)
#define U8DIVBY47(A)    U8REC1(A, 0xAFu, 5u)
#define U8DIVBY48(A)    U8REC1(A, 0xABu, 5u)
#define U8DIVBY49(A)    U8REC2(A, 0x4Fu, 5u)
#define U8DIVBY50(A)    U8REC1(A, 0xA4u, 5u)
#define U8DIVBY51(A)    U8REC1(A, 0xA1u, 5u)
#define U8DIVBY52(A)    U8REC1(A, 0x9Eu, 5u)
#define U8DIVBY53(A)    U8REC1(A, 0x9Bu, 5u)
#define U8DIVBY54(A)    U8REC1(A, 0x98u, 5u)
#define U8DIVBY55(A)    U8REC1(A, 0x95u, 5u)
#define U8DIVBY56(A)    U8REC2(A, 0x25u, 5u)
#define U8DIVBY57(A)    U8REC1(A, 0x90u, 5u)
#define U8DIVBY58(A)    U8REC2(A, 0x1Bu, 5u)
#define U8DIVBY59(A)    U8REC1(A, 0x8Bu, 5u)
#define U8DIVBY60(A)    U8REC1(A, 0x89u, 5u)
#define U8DIVBY61(A)    U8REC2(A, 0x0Du, 5u)
#define U8DIVBY62(A)    U8REC2(A, 0x09u, 5u)
#define U8DIVBY63(A)    U8REC2(A, 0x05u, 5u)
#define U8DIVBY64(A)    U8REC1(A, 0x80u, 5u)
#define U8DIVBY65(A)    U8REC1(A, 0xFDu, 6u)
#define U8DIVBY66(A)    U8REC1(A, 0xF9u, 6u)
#define U8DIVBY67(A)    U8REC1(A, 0xF5u, 6u)
#define U8DIVBY68(A)    U8REC1(A, 0xF1u, 6u)
#define U8DIVBY69(A)    U8REC1(A, 0xEEu, 6u)
#define U8DIVBY70(A)    U8REC1(A, 0xEBu, 6u)
#define U8DIVBY71(A)    U8REC1(A, 0xE7u, 6u)
#define U8DIVBY72(A)    U8REC1(A, 0xE4u, 6u)
#define U8DIVBY73(A)    U8REC1(A, 0xE1u, 6u)
#define U8DIVBY74(A)    U8REC1(A, 0xDEu, 6u)
#define U8DIVBY75(A)    U8REC1(A, 0xDBu, 6u)
#define U8DIVBY76(A)    U8REC1(A, 0xD8u, 6u)
#define U8DIVBY77(A)    U8REC1(A, 0xD5u, 6u)
#define U8DIVBY78(A)    U8REC2(A, 0xA5u, 6u)
#define U8DIVBY79(A)    U8REC1(A, 0xD0u, 6u)
#define U8DIVBY80(A)    U8REC1(A, 0xCDu, 6u)
#define U8DIVBY81(A)    U8REC1(A, 0xCBu, 6u)
#define U8DIVBY82(A)    U8REC1(A, 0xC8u, 6u)
#define U8DIVBY83(A)    U8REC1(A, 0xC6u, 6u)
#define U8DIVBY84(A)    U8REC2(A, 0x87u, 6u)
#define U8DIVBY85(A)    U8REC1(A, 0xC1u, 6u)
#define U8DIVBY86(A)    U8REC1(A, 0xBFu, 6u)
#define U8DIVBY87(A)    U8REC1(A, 0xBDu, 6u)
#define U8DIVBY88(A)    U8REC1(A, 0xBBu, 6u)
#define U8DIVBY89(A)    U8REC1(A, 0xB9u, 6u)
#define U8DIVBY90(A)    U8REC1(A, 0xB7u, 6u)
#define U8DIVBY91(A)    U8REC1(A, 0xB5u, 6u)
#define U8DIVBY92(A)    U8REC1(A, 0xB3u, 6u)
#define U8DIVBY93(A)    U8REC1(A, 0xB1u, 6u)
#define U8DIVBY94(A)    U8REC1(A, 0xAFu, 6u)
#define U8DIVBY95(A)    U8REC1(A, 0xADu, 6u)
#define U8DIVBY96(A)    U8REC1(A, 0xABu, 6u)
#define U8DIVBY97(A)    U8REC1(A, 0xA9u, 6u)
#define U8DIVBY98(A)    U8REC1(A, 0xA8u, 6u)
#define U8DIVBY99(A)    U8REC1(A, 0xA6u, 6u)
#define U8DIVBY100(A)    U8REC1(A, 0xA4u, 6u)
#define U8DIVBY101(A)    U8REC1(A, 0xA3u, 6u)
#define U8DIVBY102(A)    U8REC1(A, 0xA1u, 6u)
#define U8DIVBY103(A)    U8REC2(A, 0x3Fu, 6u)
#define U8DIVBY104(A)    U8REC1(A, 0x9Eu, 6u)
#define U8DIVBY105(A)    U8REC2(A, 0x39u, 6u)
#define U8DIVBY106(A)    U8REC1(A, 0x9Bu, 6u)
#define U8DIVBY107(A)    U8REC2(A, 0x33u, 6u)
#define U8DIVBY108(A)    U8REC1(A, 0x98u, 6u)
#define U8DIVBY109(A)    U8REC1(A, 0x97u, 6u)
#define U8DIVBY110(A)    U8REC1(A, 0x95u, 6u)
#define U8DIVBY111(A)    U8REC1(A, 0x94u, 6u)
#define U8DIVBY112(A)    U8REC2(A, 0x25u, 6u)
#define U8DIVBY113(A)    U8REC1(A, 0x91u, 6u)
#define U8DIVBY114(A)    U8REC1(A, 0x90u, 6u)
#define U8DIVBY115(A)    U8REC1(A, 0x8Fu, 6u)
#define U8DIVBY116(A)    U8REC2(A, 0x1Bu, 6u)
#define U8DIVBY117(A)    U8REC2(A, 0x19u, 6u)
#define U8DIVBY118(A)    U8REC1(A, 0x8Bu, 6u)
#define U8DIVBY119(A)    U8REC1(A, 0x8Au, 6u)
#define U8DIVBY120(A)    U8REC1(A, 0x89u, 6u)
#define U8DIVBY121(A)    U8REC2(A, 0x0Fu, 6u)
#define U8DIVBY122(A)    U8REC2(A, 0x0Du, 6u)
#define U8DIVBY123(A)    U8REC2(A, 0x0Bu, 6u)
#define U8DIVBY124(A)    U8REC2(A, 0x09u, 6u)
#define U8DIVBY125(A)    U8REC2(A, 0x07u, 6u)
#define U8DIVBY126(A)    U8REC2(A, 0x05u, 6u)
#define U8DIVBY127(A)    U8REC2(A, 0x03u, 6u)
#define U8DIVBY128(A)    U8REC1(A, 0x80u, 6u)

#endif /* INTEGER_DIVISION_UINT8 */
