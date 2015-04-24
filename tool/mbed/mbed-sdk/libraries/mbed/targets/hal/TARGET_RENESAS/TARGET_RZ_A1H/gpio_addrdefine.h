#ifndef __GPIO_ADDRDEFINE__
#define __GPIO_ADDRDEFINE__

#define GPIO_BASE  ((long)0xFCFE3000uL) /* GPIO */

#define PORT(n)    (volatile unsigned short *)(GPIO_BASE + 0x000 + ((n)*4))
#define PSR(n)     (volatile unsigned  long *)(GPIO_BASE + 0x100 + ((n)*4))
#define PPR(n)     (volatile unsigned short *)(GPIO_BASE + 0x200 + ((n)*4))
#define PM(n)      (volatile unsigned short *)(GPIO_BASE + 0x300 + ((n)*4))
#define PMC(n)     (volatile unsigned short *)(GPIO_BASE + 0x400 + ((n)*4))
#define PFC(n)     (volatile unsigned short *)(GPIO_BASE + 0x500 + ((n)*4))
#define PFCE(n)    (volatile unsigned short *)(GPIO_BASE + 0x600 + ((n)*4))
#define PNOT(n)    (volatile unsigned short *)(GPIO_BASE + 0x700 + ((n)*4))
#define PMSR(n)    (volatile unsigned  long *)(GPIO_BASE + 0x800 + ((n)*4))
#define PMCSR(n)   (volatile unsigned  long *)(GPIO_BASE + 0x900 + ((n)*4))
#define PFCAE(n)   (volatile unsigned short *)(GPIO_BASE + 0xa00 + ((n)*4))
#define PIBC(n)    (volatile unsigned short *)(GPIO_BASE + 0x4000 +((n)*4))
#define PBDC(n)    (volatile unsigned short *)(GPIO_BASE + 0x4100 +((n)*4))
#define PIPC(n)    (volatile unsigned short *)(GPIO_BASE + 0x4200 +((n)*4))

#endif/*__GPIO_ADDRDEFINE__*/

