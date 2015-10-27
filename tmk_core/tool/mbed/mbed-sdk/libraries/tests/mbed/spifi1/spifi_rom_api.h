/* definitions for ROM API for SPIFI in NXP MCUs
   copyright (c) 2010 NXP Semiconductors
   written by CAM  start                                     4/16/10
                   first testing                             5/12/10
                   OK with first SST & Winbond devices       6/8/10
				   OK with Gigadevice, Numonyx, Atmel,
				                              some Macronyx  7/13/10
				   consensus with BK, performance optimized  8/24/10
   this file is largely platform-independent */

#ifndef SPIFI_ROM_API_H
#define SPIFI_ROM_API_H


#define SPIFI_MEM_BASE 0x28000000
/* allocated size of the SPIFI memory area on this device */
#define MEM_AREA_SIZE  0x00001000
#define SPIFI_ROM_PTR  0x1FFF1FF8

/* define the symbol TESTING in the environment	if test output desired */

/* maintain LONGEST_PROT >= the length (in bytes) of the largest
	protection block of any serial flash that this driver handles */
#define LONGEST_PROT 68

/* protection/sector descriptors */
typedef struct {
	unsigned base;
	uint8_t flags;
	signed char log2;
	uint16_t rept;
} protEnt;

typedef union {
	uint16_t hw;
	uint8_t byte[2];
}stat_t;

/* the object that init returns, and other routines use as an operand */
typedef struct {
	unsigned base, regbase, devSize, memSize;
	uint8_t mfger, devType, devID, busy;
	stat_t stat;
	uint16_t reserved;
	uint16_t set_prot, write_prot;
	unsigned mem_cmd, prog_cmd;
	uint16_t sectors, protBytes;
	unsigned opts, errCheck;
	uint8_t erase_shifts[4], erase_ops[4];
	protEnt *protEnts;
	char prot[LONGEST_PROT];
} SPIFIobj;

/* operands of program and erase */
typedef struct {
    char *dest;			/* starting address for programming or erasing */
    unsigned length;	/* number of bytes to be programmed or erased */
    char *scratch;		/* address of work area or NULL */
    int protect;		/* protection to apply after programming/erasing is done */
    unsigned options;	/* see the table below */
} SPIFIopers;


/* bits in options operands (MODE3, RCVCLK, and FULLCLK
	have the same relationship as in the Control register) */
#define S_MODE3 1
#define S_MODE0 0
#define S_MINIMAL 2
#define S_MAXIMAL 0
#define S_FORCE_ERASE 4
#define S_ERASE_NOT_REQD 8
#define S_CALLER_ERASE 8
#define S_ERASE_AS_REQD 0
#define S_VERIFY_PROG 0x10
#define S_VERIFY_ERASE 0x20
#define S_NO_VERIFY 0
#define S_RCVCLK 0x80
#define S_INTCLK 0
#define S_FULLCLK 0x40
#define S_HALFCLK 0
#define S_DUAL 0x100
#define S_CALLER_PROT 0x200
#define S_DRIVER_PROT 0

/* the length of a standard	program command is 256 on all devices */
#define PROG_SIZE 256

/* interface to ROM API */
typedef struct {
  int (*spifi_init)      (SPIFIobj *obj, unsigned csHigh, unsigned options,
                          unsigned mhz);
  int (*spifi_program)   (SPIFIobj *obj, char *source, SPIFIopers *opers);
  int (*spifi_erase)     (SPIFIobj *obj, SPIFIopers *opers);
  /* mode switching */
  void (*cancel_mem_mode)(SPIFIobj *obj);
  void (*set_mem_mode)   (SPIFIobj *obj);

  /* mid level functions */
  int (*checkAd)         (SPIFIobj *obj, SPIFIopers *opers);
  int (*setProt)         (SPIFIobj *obj, SPIFIopers *opers, char *change,
                          char *saveProt);
  int (*check_block)     (SPIFIobj *obj, char *source, SPIFIopers *opers,
                          unsigned check_program);
  int (*send_erase_cmd)  (SPIFIobj *obj, unsigned char op, unsigned addr);
  unsigned (*ck_erase)   (SPIFIobj *obj, unsigned *addr, unsigned length);
  int (*prog_block)      (SPIFIobj *obj, char *source, SPIFIopers *opers,
                          unsigned *left_in_page);
  unsigned (*ck_prog)    (SPIFIobj *obj, char *source, char *dest, unsigned length);

  /* low level functions */
  void(*setSize)         (SPIFIobj *obj, int value);
  int (*setDev)          (SPIFIobj *obj, unsigned opts, unsigned mem_cmd,
                          unsigned prog_cmd);
  unsigned (*cmd)        (uint8_t op, uint8_t addrLen, uint8_t intLen, unsigned short len);
  unsigned (*readAd)     (SPIFIobj *obj, unsigned cmd, unsigned addr);
  void (*send04)         (SPIFIobj *obj, uint8_t op, uint8_t len, unsigned value);
  void (*wren_sendAd)    (SPIFIobj *obj, unsigned cmd, unsigned addr, unsigned value);
  int (*write_stat)      (SPIFIobj *obj, uint8_t len, uint16_t value);
  int (*wait_busy)       (SPIFIobj *obj, uint8_t prog_or_erase);
} SPIFI_RTNS;

//#define define_spifi_romPtr(name) const SPIFI_RTNS *name=*((SPIFI_RTNS **)SPIFI_ROM_PTR)

/* example of using this interface:
#include "spifi_rom_api.h"
#define CSHIGH 4
#define SPIFI_MHZ 80
#define source_data_ad (char *)1234

	int rc;
	SPIFIopers opers;

	define_spifi_romPtr(spifi);
	SPIFIobj *obj = malloc(sizeof(SPIFIobj));
	if (!obj) { can't allocate memory }

	rc = spifi->spifi_init (obj, CSHIGH, S_FULLCLK+S_RCVCLK, SPIFI_MHZ);
	if (rc) { investigate init error rc }
	printf ("the serial flash contains %d bytes\n", obj->devSize);

	opers.dest = where_to_program;
	opers.length = how_many_bytes;
	opers.scratch = NULL;			// unprogrammed data is not saved/restored
	opers.protect = -1;				// save & restore protection
	opers.options = S_VERIFY_PROG;

	rc = spifi->spifi_program (obj, source_data_ad, &opers);
	if (rc) { investigate program error rc }
*/

/* these are for normal users, including boot code */
int spifi_init (SPIFIobj *obj, unsigned csHigh, unsigned options, unsigned mhz);
int spifi_program (SPIFIobj *obj, char *source, SPIFIopers *opers);
int spifi_erase (SPIFIobj *obj, SPIFIopers *opers);

/* these are used by the manufacturer-specific init functions */
void setSize (SPIFIobj *obj, int value);
int setDev (SPIFIobj *obj, unsigned opts, unsigned mem_cmd, unsigned prog_cmd);
unsigned read04(SPIFIobj *obj, uint8_t op, uint8_t len);
int write_stat (SPIFIobj *obj, uint8_t len, uint16_t value);
void setProtEnts(SPIFIobj *obj, const protEnt *p, unsigned protTabLen);

#endif


