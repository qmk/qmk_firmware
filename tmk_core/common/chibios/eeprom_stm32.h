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
 * This files are free to use from https://github.com/rogerclarkmelbourne/Arduino_STM32 and
 * https://github.com/leaflabs/libmaple
 *
 * Modifications for QMK and STM32F303 by Yiancar
 */

// This file must be modified if the MCU is not defined below.
// This library also assumes that the pages are not used by the firmware.

#ifndef __EEPROM_H
#define __EEPROM_H

#include "ch.h"
#include "hal.h"
#include "flash_stm32.h"

// HACK ALERT. This definition may not match your processor
// To Do. Work out correct value for EEPROM_PAGE_SIZE on the STM32F103CT6 etc
#if defined(EEPROM_EMU_STM32F303xC)
  #define MCU_STM32F303CC
#elif defined(EEPROM_EMU_STM32F103xB)
  #define MCU_STM32F103RB
#else
  #error "not implemented."
#endif

#ifndef EEPROM_PAGE_SIZE
    #if defined (MCU_STM32F103RB)
        #define EEPROM_PAGE_SIZE    (uint16_t)0x400  /* Page size = 1KByte */
    #elif defined (MCU_STM32F103ZE) || defined (MCU_STM32F103RE) || defined (MCU_STM32F103RD) || defined (MCU_STM32F303CC)
        #define EEPROM_PAGE_SIZE    (uint16_t)0x800  /* Page size = 2KByte */
    #else
        #error  "No MCU type specified. Add something like -DMCU_STM32F103RB to your compiler arguments (probably in a Makefile)."
    #endif
#endif

#ifndef EEPROM_START_ADDRESS
    #if defined (MCU_STM32F103RB)
        #define EEPROM_START_ADDRESS    ((uint32_t)(0x8000000 + 128 * 1024 - 2 * EEPROM_PAGE_SIZE))
    #elif defined (MCU_STM32F103ZE) || defined (MCU_STM32F103RE)
        #define EEPROM_START_ADDRESS    ((uint32_t)(0x8000000 + 512 * 1024 - 2 * EEPROM_PAGE_SIZE))
    #elif defined (MCU_STM32F103RD)
        #define EEPROM_START_ADDRESS    ((uint32_t)(0x8000000 + 384 * 1024 - 2 * EEPROM_PAGE_SIZE))
    #elif defined (MCU_STM32F303CC)
        #define EEPROM_START_ADDRESS    ((uint32_t)(0x8000000 + 256 * 1024 - 2 * EEPROM_PAGE_SIZE))
    #else
        #error  "No MCU type specified. Add something like -DMCU_STM32F103RB to your compiler arguments (probably in a Makefile)."
    #endif
#endif

/* Pages 0 and 1 base and end addresses */
#define EEPROM_PAGE0_BASE       ((uint32_t)(EEPROM_START_ADDRESS + 0x000))
#define EEPROM_PAGE1_BASE       ((uint32_t)(EEPROM_START_ADDRESS + EEPROM_PAGE_SIZE))

/* Page status definitions */
#define EEPROM_ERASED           ((uint16_t)0xFFFF)  /* PAGE is empty */
#define EEPROM_RECEIVE_DATA     ((uint16_t)0xEEEE)  /* PAGE is marked to receive data */
#define EEPROM_VALID_PAGE       ((uint16_t)0x0000)  /* PAGE containing valid data */

/* Page full define */
enum uint16_t
    {
    EEPROM_OK               = ((uint16_t)0x0000),
    EEPROM_OUT_SIZE         = ((uint16_t)0x0081),
    EEPROM_BAD_ADDRESS      = ((uint16_t)0x0082),
    EEPROM_BAD_FLASH        = ((uint16_t)0x0083),
    EEPROM_NOT_INIT         = ((uint16_t)0x0084),
    EEPROM_SAME_VALUE       = ((uint16_t)0x0085),
    EEPROM_NO_VALID_PAGE    = ((uint16_t)0x00AB)
    };

#define EEPROM_DEFAULT_DATA     0xFFFF

    uint16_t EEPROM_init(void);
    uint16_t EEPROM_format(void);
    uint16_t EEPROM_erases(uint16_t *);
    uint16_t EEPROM_read (uint16_t address, uint16_t *data);
    uint16_t EEPROM_write(uint16_t address, uint16_t data);
    uint16_t EEPROM_update(uint16_t address, uint16_t data);
    uint16_t EEPROM_count(uint16_t *);
    uint16_t EEPROM_maxcount(void);

#endif  /* __EEPROM_H */
