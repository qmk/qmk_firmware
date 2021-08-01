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

#include "flash_stm32.h"

#if defined(EEPROM_EMU_STM32F103xB)
#    define FLASH_SR_WRPERR FLASH_SR_WRPRTERR
#endif

#if defined(EEPROM_EMU_STM32F4)
#    define FLASH_PSIZE_HFWORD FLASH_CR_PSIZE_0
#    define FLASH_PSIZE_WORD FLASH_CR_PSIZE_1
#    define FLASH_CR_SNB_POS 3
/* the flash key was not defined in the CMSIS used by current chibios */
#    define FLASH_KEY1 0x45670123
#    define FLASH_KEY2 0xCDEF89AB
#    define FLASH_SR_FLAGS (FLASH_SR_PGAERR|FLASH_SR_PGPERR|FLASH_SR_PGSERR|FLASH_SR_WRPERR)
#else
#    define FLASH_SR_FLAGS (FLASH_SR_EOP | FLASH_SR_PGERR | FLASH_SR_WRPERR)
#endif

/* Delay definition */
#define EraseTimeout ((uint32_t)0x00000FFF)
#define ProgramTimeout ((uint32_t)0x0000001F)

#define ASSERT(exp) (void)((0))

/**
 * @brief  Inserts a time delay.
 * @param  None
 * @retval None
 */
static void delay(void) {
    __IO uint32_t i = 0;
    for (i = 0xFF; i != 0; i--) {
    }
}

/**
 * @brief  Returns the FLASH Status.
 * @param  None
 * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *   FLASH_ERROR_WRP or FLASH_COMPLETE
 */
FLASH_Status FLASH_GetStatus(void) {
    if ((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY) return FLASH_BUSY;

#if defined(EEPROM_EMU_STM32F4)
    if ((FLASH->SR & (FLASH_SR_PGSERR | FLASH_SR_PGPERR | FLASH_SR_PGAERR))) return FLASH_ERROR_PG;
    if ((FLASH->SR & FLASH_SR_WRPERR)) return FLASH_ERROR_WRP;
#else
    if ((FLASH->SR & FLASH_SR_PGERR) != 0) return FLASH_ERROR_PG;
    if ((FLASH->SR & FLASH_SR_WRPERR) != 0) return FLASH_ERROR_WRP;
    if ((FLASH->SR & FLASH_OBR_OPTERR) != 0) return FLASH_ERROR_OPT;
#endif

    return FLASH_COMPLETE;
}

/**
 * @brief  Waits for a Flash operation to complete or a TIMEOUT to occur.
 * @param  Timeout: FLASH progamming Timeout
 * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
 *   FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout) {
    FLASH_Status status;

    /* Check for the Flash Status */
    status = FLASH_GetStatus();
    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while ((status == FLASH_BUSY) && (Timeout != 0x00)) {
        delay();
        status = FLASH_GetStatus();
        Timeout--;
    }
    if (Timeout == 0) status = FLASH_TIMEOUT;
    /* Return the operation status */
    return status;
}

/**
 * @brief  Erases a specified FLASH page.
 * @param  Page_Address: The page address or sector to be erased.
 * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *   FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address) {
    FLASH_Status status = FLASH_COMPLETE;
#ifndef EEPROM_EMU_STM32F4
    /* Check the parameters */
    ASSERT(IS_FLASH_ADDRESS(Page_Address));
#endif
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if (status == FLASH_COMPLETE) {
        /* if the previous operation is completed, proceed to erase the page */
#if defined(EEPROM_EMU_STM32F4)
        FLASH->CR &= ~FLASH_CR_SNB;
        FLASH->CR |= FLASH_CR_SER | (Page_Address << FLASH_CR_SNB_POS);
#else
        FLASH->CR |= FLASH_CR_PER;
        FLASH->AR = Page_Address;
#endif
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);
        if (status != FLASH_TIMEOUT) {
            /* clear the SER or PER Bit */
#if defined(EEPROM_EMU_STM32F4)
            FLASH->CR &= ~(FLASH_CR_SER | FLASH_CR_SNB);
#else
            FLASH->CR &= ~FLASH_CR_PER;
#endif
        }
        FLASH_ClearFlag(FLASH_SR_FLAGS);
    }
    /* Return the Erase Status */
    return status;
}

/**
 * @brief  Programs a half word at a specified address.
 * @param  Address: specifies the address to be programmed.
 * @param  Data: specifies the data to be programmed.
 * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
 *   FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data) {
    FLASH_Status status = FLASH_BAD_ADDRESS;

    if (IS_FLASH_ADDRESS(Address) && (Address % sizeof(Data)) == 0) {
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        if (status == FLASH_COMPLETE) {
            /* if the previous operation is completed, proceed to program the new data */
#if defined(EEPROM_EMU_STM32F4)
            FLASH->CR &= ~FLASH_CR_PSIZE;
            FLASH->CR |= FLASH_PSIZE_HFWORD;
#endif
            FLASH->CR |= FLASH_CR_PG;
            *(__IO uint16_t*)Address = Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
            if (status != FLASH_TIMEOUT) {
                /* if the program operation is completed, disable the PG Bit */
                FLASH->CR &= ~FLASH_CR_PG;
            }
            FLASH_ClearFlag(FLASH_SR_FLAGS);
        }
    }
    return status;
}

/**
 * @brief  Unlocks the FLASH Program Erase Controller.
 * @param  None
 * @retval None
 */
void FLASH_Unlock(void) {
    if (FLASH->CR & FLASH_CR_LOCK) {
        /* Authorize the FPEC Access */
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

/**
 * @brief  Locks the FLASH Program Erase Controller.
 * @param  None
 * @retval None
 */
void FLASH_Lock(void) {
    /* Set the Lock Bit to lock the FPEC and the FCR */
    FLASH->CR |= FLASH_CR_LOCK;
}

/**
 * @brief  Clears the FLASH's pending flags.
 * @param  FLASH_FLAG: specifies the FLASH flags to clear.
 *   This parameter can be any combination of the following values:
 *     @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
 *     @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
 *     @arg FLASH_FLAG_EOP: FLASH End of Programming flag
 * @retval None
 */
void FLASH_ClearFlag(uint32_t FLASH_FLAG) {
    /* Clear the flags */
    FLASH->SR = FLASH_FLAG;
}
