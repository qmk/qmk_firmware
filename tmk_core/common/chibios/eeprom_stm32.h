/*
 * This software is experimental and a work in progress.
 * Under no circumstances should these files be used in relation to any critical system(s).
 * Use of these files is at your own risk.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This files are free to use from http://engsta.com/stm32-flash-memory-eeprom-emulator/ by
 * Artur F.
 *
 * Modifications for QMK and STM32F303 by Yiancar
 *
 * This library assumes 8-bit data locations. To add a new MCU, please provide the flash
 * page size and the total flash size in Kb. The number of available pages must be a multiple
 * of 2. Only half of the pages account for the total EEPROM size.
 * This library also assumes that the pages are not used by the firmware.
 */

#pragma once

#include <ch.h>
#include <hal.h>
#include "flash_stm32.h"

// HACK ALERT. This definition may not match your processor
// To Do. Work out correct value for EEPROM_PAGE_SIZE on the STM32F103CT6 etc
#if defined(EEPROM_EMU_STM32F303xC)
#    define MCU_STM32F303CC
#elif defined(EEPROM_EMU_STM32F103xB)
#    define MCU_STM32F103RB
#elif defined(EEPROM_EMU_STM32F072xB)
#    define MCU_STM32F072CB
#elif defined(EEPROM_EMU_STM32F042x6)
#    define MCU_STM32F042K6
#elif defined(EEPROM_EMU_STM32F411xC)
#    define MCU_STM32F411xC
#endif

/* The page_size * density_pages should provide 8k of space, split 4k/4k between snapshot and writelog in the default config */
#ifndef FEE_DENSITY_PAGES
#    if defined(MCU_STM32F103RB) || defined(MCU_STM32F042K6)
#        define FEE_PAGE_SIZE (uint16_t)0x400  // Page size = 1KByte
#        define FEE_DENSITY_PAGES 8            // How many pages are used
#    elif defined(MCU_STM32F103ZE) || defined(MCU_STM32F103RE) || defined(MCU_STM32F103RD) || defined(MCU_STM32F303CC) || defined(MCU_STM32F072CB)
#        define FEE_PAGE_SIZE (uint16_t)0x800  // Page size = 2KByte
#        define FEE_DENSITY_PAGES 4            // How many pages are used
#    elif defined(MCU_STM32F411xC)
#        define FEE_PAGE_SIZE (uint32_t)0x20000  // Page size = 128KByte
#        define FEE_DENSITY_PAGES 1              // How many pages are used
#        define FEE_SECTOR_ID 5                  // sector id of the flash
#    else
#        error "No MCU type specified and FEE_DENSITY_PAGES not defined.\
Add something like -DMCU_STM32F103RB to your compiler arguments (probably in a Makefile)\
or define FEE_DENSITY_PAGES yourself."
#    endif
#endif

#ifndef FEE_MCU_FLASH_SIZE
#    if defined(MCU_STM32F103RB) || defined(MCU_STM32F072CB)
#        define FEE_MCU_FLASH_SIZE 128  // Size in Kb
#    elif defined(MCU_STM32F042K6)
#        define FEE_MCU_FLASH_SIZE 32  // Size in Kb
#    elif defined(MCU_STM32F103ZE) || defined(MCU_STM32F103RE)
#        define FEE_MCU_FLASH_SIZE 512  // Size in Kb
#    elif defined(MCU_STM32F103RD)
#        define FEE_MCU_FLASH_SIZE 384  // Size in Kb
#    elif defined(MCU_STM32F303CC)
#        define FEE_MCU_FLASH_SIZE 256  // Size in Kb
#    elif defined(MCU_STM32F411xC)
#        define FEE_MCU_FLASH_SIZE 256  // Size in Kb
#    else
#        error "No MCU type specified and FEE_MCU_FLASH_SIZE not defined.\
Add something like -DMCU_STM32F103RB to your compiler arguments (probably in a Makefile)\
or define FEE_MCU_FLASH_SIZE yourself."
#    endif
#endif

#ifndef FEE_BASE_ADDRESS
    /* Start of the emulated eeprom flash area, place it at the end of the flash memory */
    #define FEE_BASE_ADDRESS ((uint32_t)(0x8000000 + FEE_MCU_FLASH_SIZE * 1024 - FEE_DENSITY_PAGES * FEE_PAGE_SIZE))
#endif

#ifndef FEE_SNAPSHOT_SIZE
    /* Size of eeprom snapshot, in bytes. This is equal to emulated eeprom size. */
    #define FEE_SNAPSHOT_SIZE 4096
#endif

#ifndef FEE_WRITELOG_SIZE
    /* Size of eeprom writelog, in bytes. By default, use all the remaining amount of flash bank. */
    #define FEE_WRITELOG_SIZE (FEE_DENSITY_PAGES * FEE_PAGE_SIZE - FEE_SNAPSHOT_SIZE)
#endif

/* Flash word value after erase */
#define FEE_EMPTY_WORD ((uint16_t)0xFFFF)

/* Size of emulated eeprom */
#define FEE_DENSITY_BYTES FEE_SNAPSHOT_SIZE

void     EEPROM_Init(void);
void     EEPROM_Erase(void);
