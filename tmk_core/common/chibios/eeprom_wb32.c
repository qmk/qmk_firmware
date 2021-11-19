/*
    Copyright (C) 2021 Westberry Technology (ChangZhou) Corp., Ltd

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "debug.h"

#include "eeprom_wb32_defs.h"
#if !defined(FEE_PAGE_SIZE) || !defined(FEE_PAGE_COUNT) || !defined(FEE_MCU_FLASH_SIZE) || !defined(FEE_PAGE_BASE_ADDRESS)
#    error "not implemented."
#endif

// #define DEBUG_EEPROM_OUTPUT

/*
 * Debug print utils
 */

#if defined(DEBUG_EEPROM_OUTPUT)

#    define debug_eeprom debug_enable
#    define eeprom_println(s) println(s)
#    define eeprom_printf(fmt, ...) xprintf(fmt, ##__VA_ARGS__);

#else /* NO_DEBUG */

#    define debug_eeprom false
#    define eeprom_println(s)
#    define eeprom_printf(fmt, ...)

#endif /* NO_DEBUG */

/*****************************************************************************
 * Allows to use the internal flash to store non volatile data. To initialize
 * the functionality use the EEPROM_Init() function. Be sure that by reprogramming
 * of the controller just affected pages will be deleted. In other case the non
 * volatile data will be lost.
 ******************************************************************************/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// __ASM void FLASH_OP_EXEC_RAM(uint32_t code, uint32_t fmc_base)
// {
//   STR   R0, [R1, #0x00]   // FMC->CON = 0x00800080; # WR=1
//   NOP
// LB_CK
//   LDR   R0, [R1, #0x00]
//   LSLS  R0, R0, #24
//   BMI   LB_CK             // while(FMC->CON & FMC_CON_WR);
//   BX    LR
// }
/* Do not change if it is not necessary */
// #define FLASH_OP_RAM_CODE {0xBF006008, 0x06006808, 0x4770D4FC}

typedef enum { FLASH_BUSY = 1, FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_ERROR_OPT, FLASH_COMPLETE, FLASH_TIMEOUT, FLASH_BAD_ADDRESS } FLASH_Status;
static const uint32_t pre_op_code[] = {0x4FF0E92D, 0x21034832, 0x210C6281, 0xF8DF62C1, 0x2100C0C4, 0x1000F8CC, 0xF44F4608, 0x1C40767A, 0xDBFC42B0, 0xF8CC2201, 0x20002000, 0x42B01C40, 0x4829DBFC, 0xF0436803, 0x60030380, 0x302C4826, 0xF4436803, 0x60036320, 0x46104691, 0x323C4A22, 0x468A6010, 0x49214608, 0x48216008, 0x0340F8D0, 0x25004F1E, 0x5107F3C0, 0x3BFFF04F, 0x22001F3F, 0x4610465C, 0xEA5F683B, 0xD10678C0, 0xD10142A3, 0xE0002401, 0x44222400, 0x1C40461C, 0xDBF12814, 0xD91B2A02, 0xD9012910, 0xE0003910, 0x480D2100, 0x68021F00, 0x627FF022, 0x5201EA42, 0xF8CC6002, 0x2000A000, 0x42B01C40, 0xF8CCDBFC, 0x20009000, 0x42B01C40, 0x1C6DDBFC, 0xDBD02D05, 0x8FF0E8BD, 0x40010000, 0x40010438, 0x40010C20, 0x4000B804, 0x1FFFF000};
#define PRE_OP() ((void (*)(void))((unsigned int)(pre_op_code) | 0x01))()
/* Functions -----------------------------------------------------------------*/

uint8_t DataBuf[FEE_PAGE_SIZE];
/*****************************************************************************
 *  Delete Flash Space used for user Data, deletes the whole space between
 *  RW_PAGE_BASE_ADDRESS and the last uC Flash Page
 ******************************************************************************/
static uint16_t EEPROM_Init(void) {
    /* Unlocks write to ANCTL registers */
    PWR->ANAKEY1 = 0x03;
    PWR->ANAKEY2 = 0x0C;
    /* Enables or disables the Internal 48MHz oscillator (FHSI). */
    ANCTL->FHSIENR = (uint32_t)ENABLE;
    /* Locks write to ANCTL registers */
    PWR->ANAKEY1 = 0x00;
    PWR->ANAKEY2 = 0x00;

    return FEE_DENSITY_BYTES;
}

/*****************************************************************************
 *  Execute FLASH operation.
 ******************************************************************************/

static uint32_t FLASH_OP_EXEC(uint32_t op) {
    // volatile uint32_t flash_op_ram_code[] = FLASH_OP_RAM_CODE;

    /* Start FLASH operation and wait for a FLASH operation to complete  */
    RCC->PCLKENR = 0x01;
    FMC->CON     = 0x7F5F0D40 | (op & 0x1F); /* [14:8]=0x0D, WREN=1, [4:0]=op */
    FMC->KEY     = 0x5188DA08;
    FMC->KEY     = 0x12586590;
    // ((void(*)(uint32_t, uint32_t))((unsigned int)(flash_op_ram_code) | 0x01))(0x00800080, FMC_BASE);
    FMC->CON = 0x00800080;
    while (FMC->CON & FMC_CON_WR)
        ;

    RCC->PCLKENR = 0x00;
    /* Clear WREN and OP[4:0] bits */
    FMC->CON = 0x005F0000;

    if (FMC->STAT & FMC_STAT_ERR)
        return 1; /* Any error occur */
    else
        return 0; /* FLASH operation complete */
}

/*****************************************************************************
 *  Programs the data to the specified page address.
 ******************************************************************************/
static uint32_t FMC_ProgramPage(uint32_t Page_Address) {
    uint32_t ret;
    int      state;

    state = __get_PRIMASK();
    __disable_irq();
    PRE_OP();
    FMC->ADDR = Page_Address;
    ret       = FLASH_OP_EXEC(0x0C);
    if (!state) {
        __enable_irq();
    }

    return ret;
}

/*****************************************************************************
 *  Erase a specified FLASH page.
 ******************************************************************************/
static uint32_t FMC_ErasePage(uint32_t Page_Address) {
    uint32_t ret;
    int      state;

    state = __get_PRIMASK();
    __disable_irq();
    PRE_OP();
    FMC->ADDR = Page_Address;
    ret       = FLASH_OP_EXEC(0x08);
    if (!state) {
        __enable_irq();
    }

    return ret;
}

/*****************************************************************************
 *  Clear page latches.
 ******************************************************************************/
static uint32_t FMC_ClearPageLatch(void) {
    uint32_t ret;
    int      state;

    state = __get_PRIMASK();
    __disable_irq();
    ret = FLASH_OP_EXEC(0x04);
    if (!state) {
        __enable_irq();
    }

    return ret;
}

/*****************************************************************************
 *  Erase the whole reserved Flash Space used for user Data.
 ******************************************************************************/
static void EEPROM_Erase(void) {
    int page_num = 0;

    eeprom_println("EEPROM_Erase");

    /* delete all pages from specified start page to the last page.*/
    do {
        FMC_ErasePage(FEE_PAGE_BASE_ADDRESS + (page_num * FEE_PAGE_SIZE));
        page_num++;
    } while (page_num < FEE_PAGE_COUNT);
}

/*****************************************************************************
 *  Read flash data.
 ******************************************************************************/
static void WBFLASH_Read(uint32_t ReadAddr, uint8_t *ReadDest, uint16_t ReadLen) {
    uint16_t i;

    for (i = 0; i < ReadLen; i++) {
        ReadDest[i] = (__IO uint8_t)(*(__IO uint8_t *)ReadAddr);
        ReadAddr++;
    }
}
/*****************************************************************************
 *  Writes once data byte to flash on specified address. If a byte is already
 *  written, the whole page must be copied to a buffer, the byte changed and
 *  the manipulated buffer written after PageErase.
 *******************************************************************************/
static uint8_t wb_flash_buffer[FEE_PAGE_SIZE] = {0};
static int EEPROM_WriteDataPage(uint16_t Addr, uint8_t *WriteSrc, size_t Len) {
    uint16_t     PageReamin;
    uint16_t     PageOff;
    uint32_t     PagePos;
    uint32_t     WriteAddr;
    uint32_t     WriteLen;

    /* exit if desired address is above the limit (Over maximum capacity).*/
    if (Addr > FEE_DENSITY_BYTES) {
        eeprom_printf("EEPROM_WriteDataByte(0x%04x) [BAD ADDRESS]\n", Addr);
        return -1;
    }

    /* calculate which page is affected (Pagenum1/Pagenum2...PagenumN).*/
    PagePos    = (Addr + FEE_PAGE_BASE_ADDRESS) / FEE_PAGE_SIZE;
    PageOff    = (Addr + FEE_PAGE_BASE_ADDRESS) % FEE_PAGE_SIZE;
    PageReamin = FEE_PAGE_SIZE - PageOff;
    WriteAddr  = PagePos * FEE_PAGE_SIZE;

    WriteLen = (Len < PageReamin) ? Len : PageReamin;

    if (WriteLen != FEE_PAGE_SIZE) {
        WBFLASH_Read(WriteAddr, wb_flash_buffer, FEE_PAGE_SIZE);
        memcpy(wb_flash_buffer + PageOff, WriteSrc, WriteLen);
        /* Erase the specified FLASH page */
        FMC_ErasePage(WriteAddr);
        /* Clear page latch */
        FMC_ClearPageLatch();

        for (int i = 0; i < (FEE_PAGE_SIZE >> 2); i++) {
            FMC->BUF[i] = (*((volatile uint32_t *)(wb_flash_buffer + i * 4)));
        }
        /* Program data in page latch to the specified FLASH page */
        FMC_ProgramPage(WriteAddr);
        return WriteLen;
    } else {
        /* Erase the specified FLASH page */
        FMC_ErasePage(WriteAddr);
        /* Clear page latch */
        FMC_ClearPageLatch();

        for (int i = 0; i < (FEE_PAGE_SIZE >> 2); i++) {
            FMC->BUF[i] = (*((volatile uint32_t *)(WriteSrc + i * 4)));
        }
        /* Program data in page latch to the specified FLASH page */
        FMC_ProgramPage(WriteAddr);
        return WriteLen;
    }

    return -1;
}
/*****************************************************************************
 *  Read once data byte from a specified address.
 *******************************************************************************/
static uint8_t EEPROM_ReadDataByte(uint16_t Address) {
    uint8_t DataByte = 0x00;

    // Get Byte from specified address
    DataByte = (*(__IO uint8_t *)(FEE_PAGE_BASE_ADDRESS + (Address)));

    return DataByte;
}

/*****************************************************************************
 *  Bind to eeprom_driver.c
 *******************************************************************************/
void eeprom_driver_init(void) { EEPROM_Init(); }

void eeprom_driver_erase(void) { EEPROM_Erase(); }

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = EEPROM_ReadDataByte((uint32_t)p++);
    }
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uint8_t *dest = (uint8_t *)addr;
    uint8_t *src  = (uint8_t *)buf;
    int retval;

    while (len) {
        retval = EEPROM_WriteDataPage((uintptr_t)((uint16_t *)dest), src, len);
        if (retval == -1) {
            eeprom_println("EEPROM Write Failed");
            return;
        }

        len  -= retval;
        dest += retval;
        src  += retval;
    }
}
