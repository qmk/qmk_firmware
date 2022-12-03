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

#include <hal.h>
#include "legacy_flash_ops.h"

#if defined(STM32F1XX)
#    define FLASH_SR_WRPERR FLASH_SR_WRPRTERR
#endif

#if defined(MCU_GD32V)
/* GigaDevice GD32VF103 is a STM32F103 clone at heart. */
#    include "gd32v_compatibility.h"
#endif

#if defined(STM32F4XX)
#    define FLASH_SR_PGERR (FLASH_SR_PGSERR | FLASH_SR_PGPERR | FLASH_SR_PGAERR)

#    define FLASH_KEY1 0x45670123U
#    define FLASH_KEY2 0xCDEF89ABU

static uint8_t ADDR2PAGE(uint32_t Page_Address) {
    switch (Page_Address) {
        case 0x08000000 ... 0x08003FFF:
            return 0;
        case 0x08004000 ... 0x08007FFF:
            return 1;
        case 0x08008000 ... 0x0800BFFF:
            return 2;
        case 0x0800C000 ... 0x0800FFFF:
            return 3;
    }

    // TODO: bad times...
    return 7;
}
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

    if ((FLASH->SR & FLASH_SR_PGERR) != 0) return FLASH_ERROR_PG;

    if ((FLASH->SR & FLASH_SR_WRPERR) != 0) return FLASH_ERROR_WRP;

#if defined(FLASH_OBR_OPTERR)
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
 * @param  Page_Address: The page address to be erased.
 * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *   FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address) {
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    ASSERT(IS_FLASH_ADDRESS(Page_Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if (status == FLASH_COMPLETE) {
        /* if the previous operation is completed, proceed to erase the page */
#if defined(FLASH_CR_SNB)
        FLASH->CR &= ~FLASH_CR_SNB;
        FLASH->CR |= FLASH_CR_SER | (ADDR2PAGE(Page_Address) << FLASH_CR_SNB_Pos);
#else
        FLASH->CR |= FLASH_CR_PER;
        FLASH->AR = Page_Address;
#endif
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);
        if (status != FLASH_TIMEOUT) {
            /* if the erase operation is completed, disable the configured Bits */
#if defined(FLASH_CR_SNB)
            FLASH->CR &= ~(FLASH_CR_SER | FLASH_CR_SNB);
#else
            FLASH->CR &= ~FLASH_CR_PER;
#endif
        }
        FLASH->SR = (FLASH_SR_EOP | FLASH_SR_PGERR | FLASH_SR_WRPERR);
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

    if (IS_FLASH_ADDRESS(Address)) {
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        if (status == FLASH_COMPLETE) {
            /* if the previous operation is completed, proceed to program the new data */

#if defined(FLASH_CR_PSIZE)
            FLASH->CR &= ~FLASH_CR_PSIZE;
            FLASH->CR |= FLASH_CR_PSIZE_0;
#endif
            FLASH->CR |= FLASH_CR_PG;
            *(__IO uint16_t*)Address = Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
            if (status != FLASH_TIMEOUT) {
                /* if the program operation is completed, disable the PG Bit */
                FLASH->CR &= ~FLASH_CR_PG;
            }
            FLASH->SR = (FLASH_SR_EOP | FLASH_SR_PGERR | FLASH_SR_WRPERR);
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
