/* Copyright 2024 Finalkey
 * Copyright 2024 LiWenLiu <https://github.com/LiuLiuQMK>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "rdmctmzt_common.h"

#if defined(EEPROM_CUSTOM)
/* Exported Constants --------------------------------------------------------*/
/* Define the size of the sectors to be used */
#define MCU_PAGE_SIZE           (uint32_t)0x200   /* MCU page size = 0.5kB */
#define PAGE_SIZE               (uint32_t)0x2000  /* Page size = 8kB */
#define MCU_PAGE_NUM            PAGE_SIZE / MCU_PAGE_SIZE

/* EEPROM start address in Flash */
#define EEPROM_START_ADDRESS  ((uint32_t)0x1C000)

/* Pages 0 and 1 base and end addresses */
#define PAGE0_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS))
#define PAGE0_END_ADDRESS     ((uint32_t)(PAGE0_BASE_ADDRESS + (PAGE_SIZE - 1)))

#define PAGE1_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS + PAGE_SIZE))
#define PAGE1_END_ADDRESS     ((uint32_t)(PAGE1_BASE_ADDRESS + (PAGE_SIZE - 1)))

/* Used Flash pages for EEPROM emulation */
#define PAGE0                 ((uint32_t)0x00000000)
#define PAGE1                 ((uint32_t)0x00000001)

/* No valid page define */
#define NO_VALID_PAGE         ((uint32_t)0x000000AB)

/* Page status definitions */
#define ERASED                ((uint32_t)0xFFFFFFFF)     /* Page is empty */
#define RECEIVE_DATA          ((uint32_t)0xEEEEEEEE)     /* Page is marked to receive data */
#define VALID_PAGE            ((uint32_t)0x00000000)     /* Page containing valid data */

/* Valid pages in read and write defines */
#define READ_FROM_VALID_PAGE  ((uint8_t)0x00)
#define WRITE_IN_VALID_PAGE   ((uint8_t)0x01)

/* Page full define */
#define PAGE_FULL             ((uint8_t)0x80)

/* Variables' number */
#define NB_OF_VAR             (EEPROM_SIZE)
#define NB_OF_PRIVATE_VAR     (64)

#define ES_MCU_MEM_REMAP_OFFSET  ((((SYSCFG->REMAP)&SYSCFG_REMAP_REALBASE_MSK) >> SYSCFG_REMAP_REALBASE_POSS) << 12)

//__attribute__((aligned(4))) static uint8_t g_es_flash_eeprom_table[EEPROM_SIZE + 2];
__attribute__((aligned(4))) static uint8_t g_es_flash_eeprom_table[EEPROM_SIZE + NB_OF_PRIVATE_VAR + 2];

volatile uint32_t g_tst_remap_offset;

static uint32_t ee_format(void);
static uint32_t ee_find_valid_page(uint8_t operation);
static uint32_t ee_verify_pagefull_write_variable(uint32_t virt_address, uint32_t data);
static uint32_t ee_page_transfer(uint32_t virt_address, uint32_t data);

static uint32_t IAPROM_PAGE_ERASE(uint32_t addr)
{   
    md_fc_ControlTypeDef SErasePara;

    if ((addr & 0x1ff) != 0)
    {
        return !SET;
    }

    __disable_irq();

    md_fc_unlock();

    SErasePara.SAddr = addr;
    SErasePara.SAddrC = ~(addr);

    md_fc_page_erase(&SErasePara);

    md_fc_lock();

    __enable_irq();

    return SET;
}

static uint32_t IAPROM_WORD_PROGRAM(uint32_t addr,uint32_t data)
{                     
    md_fc_ControlTypeDef ProgramPara;

    if ((addr & 0x3) != 0)
    {
        return !SET;
    }

    if ((((uint32_t)(&data)) & 0x3) != 0)
    {
        return !SET;
    }
  
    __disable_irq();

    md_fc_unlock();

    ProgramPara.BCnt = 4;
    ProgramPara.pU32Buf = &data;
    ProgramPara.SAddr = addr;
    ProgramPara.SAddrC = ~(addr);

    md_fc_program(&ProgramPara);

    md_fc_lock();

    __enable_irq();

    return SET;
}

static uint32_t ee_init(void)
{
    uint32_t page_status0 = 6U, page_status1 = 6U;
    uint32_t var_idx = 0U;
    uint32_t eeprom_status = 0U;
    uint32_t flash_status;
    uint8_t addr_index;
    uint32_t rom_read_end;

    /* Get Page0 status */
    page_status0 = (*(__IO uint32_t *)(PAGE0_BASE_ADDRESS - ES_MCU_MEM_REMAP_OFFSET));
    /* Get Page1 status */
    page_status1 = (*(__IO uint32_t *)(PAGE1_BASE_ADDRESS - ES_MCU_MEM_REMAP_OFFSET));

    if(page_status0 == VALID_PAGE)
    {
        rom_read_end = PAGE0_END_ADDRESS - ES_MCU_MEM_REMAP_OFFSET;
        for(var_idx = PAGE0_BASE_ADDRESS - ES_MCU_MEM_REMAP_OFFSET + 4;var_idx < rom_read_end;var_idx += 4)
        {
            if(((*(__IO uint32_t *)var_idx) >> 16) < NB_OF_VAR)
            {
                *(((uint16_t*)((uint32_t)g_es_flash_eeprom_table)) + ((*(__IO uint32_t *)var_idx) >> 16)) = (*(__IO uint32_t *)var_idx) & 0xFFFF;
            }
            else
            {
                break;
            }
        }
    }

    if(page_status1 == VALID_PAGE)
    {
        rom_read_end = PAGE1_END_ADDRESS - ES_MCU_MEM_REMAP_OFFSET;
        for(var_idx = PAGE1_BASE_ADDRESS - ES_MCU_MEM_REMAP_OFFSET + 4;var_idx < rom_read_end;var_idx += 4)
        {
            if(((*(__IO uint32_t *)var_idx) >> 16) < NB_OF_VAR)
            {
                *(((uint16_t*)((uint32_t)g_es_flash_eeprom_table)) + ((*(__IO uint32_t *)var_idx) >> 16)) = (*(__IO uint32_t *)var_idx) & 0xFFFF;
            }
            else
            {
                break;
            }
        }
    }

    /* Check for invalid header states and repair if necessary */
    switch (page_status0)
    {
        case ERASED:
            if (page_status1 == VALID_PAGE) /* Page0 erased, Page1 valid */
            {
                /* Erase Page0 */
                for (addr_index = 0; addr_index < MCU_PAGE_NUM; addr_index++)
                {
                    IAPROM_PAGE_ERASE(PAGE0_BASE_ADDRESS + addr_index * MCU_PAGE_SIZE);
                }
            }
            else if (page_status1 == RECEIVE_DATA) /* Page0 erased, Page1 receive */
            {
                /* Erase Page0 */
                for (addr_index = 0; addr_index < MCU_PAGE_NUM; addr_index++)
                {
                    IAPROM_PAGE_ERASE(PAGE0_BASE_ADDRESS + addr_index * MCU_PAGE_SIZE);
                }

                IAPROM_WORD_PROGRAM(PAGE1_BASE_ADDRESS, VALID_PAGE);
            }
            else /* First EEPROM access (Page0&1 are erased) or invalid state -> format EEPROM */
            {
                /* Erase both Page0 and Page1 and set Page0 as valid page */
                flash_status = ee_format();

                if (flash_status != SET)
                    return flash_status;
            }

            break;

        case RECEIVE_DATA:
            if (page_status1 == VALID_PAGE) /* Page0 receive, Page1 valid */
            {
                /* Transfer data from Page1 to Page0 */
                for (var_idx = 0; var_idx < (NB_OF_VAR / 2 + 1); var_idx++)
                {
                    if((*(((__IO uint16_t*)((uint32_t)g_es_flash_eeprom_table)) + var_idx)) != 0)
                    {
                        /* Transfer the variable to the Page0 */
                            eeprom_status = ee_verify_pagefull_write_variable(var_idx, (*(((__IO uint16_t*)((uint32_t)g_es_flash_eeprom_table)) + var_idx)));

                            /* If program operation was failed, a Flash error code is returned */
                            if (eeprom_status != SET)
                                return eeprom_status;
                    }
                }

                IAPROM_WORD_PROGRAM(PAGE0_BASE_ADDRESS, VALID_PAGE);

                /* Erase Page1 */
                for (addr_index = 0; addr_index < MCU_PAGE_NUM; addr_index++)
                {
                    IAPROM_PAGE_ERASE(PAGE1_BASE_ADDRESS + addr_index * MCU_PAGE_SIZE);
                }
            }
            else if (page_status1 == ERASED) /* Page0 receive, Page1 erased */
            {
                /* Erase Page1 */
                for (addr_index = 0; addr_index < MCU_PAGE_NUM; addr_index++)
                {
                    IAPROM_PAGE_ERASE(PAGE1_BASE_ADDRESS + addr_index * MCU_PAGE_SIZE);
                }

                IAPROM_WORD_PROGRAM(PAGE0_BASE_ADDRESS, VALID_PAGE);
            }
            else /* Invalid state -> format eeprom */
            {
                flash_status = ee_format();
                if (flash_status != SET)
                    return flash_status;
            }

            break;

        case VALID_PAGE:
            if (page_status1 == VALID_PAGE) /* Invalid state -> format eeprom */
            {
                flash_status = ee_format();
                if (flash_status != SET)
                    return flash_status;
            }
            else if (page_status1 == ERASED) /* Page0 valid, Page1 erased */
            {
                for (addr_index = 0; addr_index < MCU_PAGE_NUM; addr_index++)
                {
                    IAPROM_PAGE_ERASE(PAGE1_BASE_ADDRESS + addr_index * MCU_PAGE_SIZE);
                }
            }
            else /* Page0 valid, Page1 receive */
            {
                /* Transfer data from Page0 to Page1 */
                for (var_idx = 0; var_idx < (NB_OF_VAR / 2 + 1); var_idx++)
                {
                    if((*(((__IO uint16_t*)((uint32_t)g_es_flash_eeprom_table)) + var_idx)) != 0)
                    {
                        /* Transfer the variable to the Page0 */
                            eeprom_status = ee_verify_pagefull_write_variable(var_idx, (*(((__IO uint16_t*)((uint32_t)g_es_flash_eeprom_table)) + var_idx)));

                            /* If program operation was failed, a Flash error code is returned */
                            if (eeprom_status != SET)
                                return eeprom_status;
                    }
                }

                IAPROM_WORD_PROGRAM(PAGE1_BASE_ADDRESS, VALID_PAGE);

                for (addr_index = 0; addr_index < MCU_PAGE_NUM; addr_index++)
                {
                    IAPROM_PAGE_ERASE(PAGE0_BASE_ADDRESS + addr_index * MCU_PAGE_SIZE);
                }
            }

            break;

        default:  /* Any other state -> format eeprom */
            flash_status = ee_format();
            if (flash_status != SET)
                return flash_status;

            break;
    }

    return SET;
}

static uint32_t ee_write_variable(uint32_t virt_address)
{
    uint32_t status = 0U;
    uint16_t data;

    if(virt_address >= NB_OF_VAR)
    {
        return !SET;
    }
    
    virt_address = virt_address / 2;
    
    data = *(((uint16_t*)((uint32_t)g_es_flash_eeprom_table)) + virt_address);

    /* Write the variable virtual address and value in the EEPROM */
    status = ee_verify_pagefull_write_variable(virt_address, data);

    /* In case the EEPROM active page is full */
    if (status == PAGE_FULL)
        status = ee_page_transfer(virt_address, data);  /* Perform Page transfer */

    /* Return last operation status */
    return status;
}

static uint32_t ee_format(void)
{
    uint32_t flash_status = SET;
    uint8_t addr_index;

    /* Erase Page0 */
    for (addr_index = 0; addr_index < MCU_PAGE_NUM; addr_index++)
    {
        IAPROM_PAGE_ERASE(PAGE0_BASE_ADDRESS + addr_index * MCU_PAGE_SIZE);
    }

    /* Set Page0 as valid page: Write VALID_PAGE at Page0 base address */
    IAPROM_WORD_PROGRAM(PAGE0_BASE_ADDRESS, VALID_PAGE);

    /* Erase Page1 */
    for (addr_index = 0; addr_index < MCU_PAGE_NUM; addr_index++)
    {
        IAPROM_PAGE_ERASE(PAGE1_BASE_ADDRESS + addr_index * MCU_PAGE_SIZE);
    }

    /* Return Page1 erase operation status */
    return flash_status;
}

static uint32_t ee_find_valid_page(uint8_t operation)
{
    uint32_t page_status0 = 6U, page_status1 = 6U;

    /* Get Page0 status */
    page_status0 = (*(__IO uint32_t *)(PAGE0_BASE_ADDRESS - ES_MCU_MEM_REMAP_OFFSET));
    /* Get Page1 status */
    page_status1 = (*(__IO uint32_t *)(PAGE1_BASE_ADDRESS - ES_MCU_MEM_REMAP_OFFSET));

    /* Write or read operation */
    switch (operation)
    {
        case WRITE_IN_VALID_PAGE:   /* ---- Write operation ---- */
            if (page_status1 == VALID_PAGE)
            {
                /* Page0 receiving data */
                if (page_status0 == RECEIVE_DATA)
                    return PAGE0;         /* Page0 valid */
                else
                    return PAGE1;         /* Page1 valid */
            }
            else if (page_status0 == VALID_PAGE)
            {
                /* Page1 receiving data */
                if (page_status1 == RECEIVE_DATA)
                    return PAGE1;         /* Page1 valid */
                else
                    return PAGE0;         /* Page0 valid */
            }
            else
            {
                return NO_VALID_PAGE;   /* No valid Page */
            }

        case READ_FROM_VALID_PAGE:  /* ---- Read operation ---- */
            if (page_status0 == VALID_PAGE)
                return PAGE0;           /* Page0 valid */
            else if (page_status1 == VALID_PAGE)
                return PAGE1;           /* Page1 valid */
            else
                return NO_VALID_PAGE ;  /* No valid Page */

        default:
            return PAGE0;             /* Page0 valid */
    }
}

static uint32_t ee_verify_pagefull_write_variable(uint32_t virt_address, uint32_t data)
{
    uint32_t flash_status = SET;
    uint32_t valid_page = PAGE0;
    uint32_t address = EEPROM_START_ADDRESS;
    uint32_t page_endaddress = EEPROM_START_ADDRESS + PAGE_SIZE;

    /* Get valid Page for write operation */
    valid_page = ee_find_valid_page(WRITE_IN_VALID_PAGE);

    /* Check if there is no valid page */
    if (valid_page == NO_VALID_PAGE)
        return NO_VALID_PAGE;

    /* Get the valid Page start address */
    address = (uint32_t)(EEPROM_START_ADDRESS + (uint32_t)(valid_page * PAGE_SIZE)) - ES_MCU_MEM_REMAP_OFFSET;

    /* Get the valid Page end address */
    page_endaddress = (uint32_t)((EEPROM_START_ADDRESS - 4) + (uint32_t)((1 + valid_page) * PAGE_SIZE)) - ES_MCU_MEM_REMAP_OFFSET;

    /* Check each active page address starting from begining */
    while (address <= page_endaddress)
    {
        /* Verify if address and address+4 contents are 0xFFFFFFFF */
        if ((*(__IO uint32_t *)address) == 0xFFFFFFFF)
        {
            /* Set variable virtual address and data */
            flash_status = IAPROM_WORD_PROGRAM(address + ES_MCU_MEM_REMAP_OFFSET, (virt_address << 16) | data);
            /* Return program operation status */
            return flash_status;
        }
        else
        {
            /* Next address location */
            address = address + 4;
        }
    }

    /* Return PAGE_FULL in case the valid page is full */
    return PAGE_FULL;
}

static uint32_t ee_page_transfer(uint32_t virt_address, uint32_t data)
{
    uint32_t flash_status = SET;
    uint32_t new_pageaddress = EEPROM_START_ADDRESS;
    uint32_t old_pageaddress;
    uint32_t valid_page = PAGE0, var_idx = 0U;
    uint32_t eeprom_status = 0U;
    uint8_t addr_index;

    /* Get active Page for read operation */
    valid_page = ee_find_valid_page(READ_FROM_VALID_PAGE);

    if (valid_page == PAGE1)       /* Page1 valid */
    {
        /* New page address where variable will be moved to */
        new_pageaddress = PAGE0_BASE_ADDRESS;

        /* Old page ID where variable will be taken from */
        old_pageaddress = PAGE1_BASE_ADDRESS;
    }
    else if (valid_page == PAGE0)  /* Page0 valid */
    {
        /* New page address  where variable will be moved to */
        new_pageaddress = PAGE1_BASE_ADDRESS;

        /* Old page ID where variable will be taken from */
        old_pageaddress = PAGE0_BASE_ADDRESS;
    }
    else
    {
        return NO_VALID_PAGE;       /* No valid Page */
    }
    
    /* Erase the new Page*/
    for (addr_index = 0; addr_index < MCU_PAGE_NUM; addr_index++)
    {
        IAPROM_PAGE_ERASE(new_pageaddress + addr_index * MCU_PAGE_SIZE);
    }

    /* Set the new Page status to RECEIVE_DATA status */
    IAPROM_WORD_PROGRAM(new_pageaddress, RECEIVE_DATA);

    /* Write the variable passed as parameter in the new active page */
    eeprom_status = ee_verify_pagefull_write_variable(virt_address, data);

    /* If program operation was failed, a Flash error code is returned */
    if (eeprom_status != SET)
        return eeprom_status;

    /* Transfer process: transfer variables from old to the new active page */
    //for (var_idx = 0; var_idx < NB_OF_VAR; var_idx++)
    {
                /* Transfer data from Page1 to Page0 */
                for (var_idx = 0; var_idx < (NB_OF_VAR / 2 + 1); var_idx++)
                {
                    if((*(((__IO uint16_t*)((uint32_t)g_es_flash_eeprom_table)) + var_idx)) != 0)
                    {
                        /* Transfer the variable to the Page0 */
                            eeprom_status = ee_verify_pagefull_write_variable(var_idx, (*(((__IO uint16_t*)((uint32_t)g_es_flash_eeprom_table)) + var_idx)));

                            /* If program operation was failed, a Flash error code is returned */
                            if (eeprom_status != SET)
                                return eeprom_status;
                    }
                }
    }

    /* Erase the old Page: Set old Page status to ERASED status */
    for (addr_index = 0; addr_index < MCU_PAGE_NUM; addr_index++)
    {
        IAPROM_PAGE_ERASE(old_pageaddress + addr_index * MCU_PAGE_SIZE);
    }

    /* Set new Page status to VALID_PAGE status */
    IAPROM_WORD_PROGRAM(new_pageaddress, VALID_PAGE);

    /* Return last operation flash status */
    return flash_status;
}

size_t clamp_length(intptr_t offset, size_t len) {
    if (offset + len > EEPROM_SIZE) {
        len = EEPROM_SIZE - offset;
    }

    return len;
}

size_t clamp_length_user(intptr_t offset, size_t len) {
    if (offset + len > NB_OF_PRIVATE_VAR) {
        len = NB_OF_PRIVATE_VAR - offset;
    }

    return len;
}

void eeprom_driver_erase(void) {
    ee_format();
    memset(g_es_flash_eeprom_table, 0x00, sizeof(g_es_flash_eeprom_table));
}

#define USER_EEPROM_START_ADDRESS1  (EEPROM_START_ADDRESS - (MCU_PAGE_SIZE))
volatile uint8_t es_eeprom_init_flag = 0U;

void eeprom_driver_init(void) {
    if(es_eeprom_init_flag)
        return;

    g_tst_remap_offset = ES_MCU_MEM_REMAP_OFFSET;
    (void)g_tst_remap_offset;
    memset(g_es_flash_eeprom_table, 0x00, sizeof(g_es_flash_eeprom_table));
    ee_init();
    memcpy(g_es_flash_eeprom_table, (uint8_t*)(USER_EEPROM_START_ADDRESS1 - ES_MCU_MEM_REMAP_OFFSET), NB_OF_PRIVATE_VAR);
    es_eeprom_init_flag = 1;
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    intptr_t offset = (intptr_t)addr;
    memset(buf, 0x00, len);
    len = clamp_length(offset, len);
    if (len > 0) {
        memcpy(buf, &g_es_flash_eeprom_table[NB_OF_PRIVATE_VAR + offset], len);
    }
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uint16_t i;
    intptr_t offset = (intptr_t)addr;
    len             = clamp_length(offset, len);
    if (len > 0) {
        for(i = 0;i < len;i++)
        {
            if(g_es_flash_eeprom_table[i + offset + NB_OF_PRIVATE_VAR] != (*((uint8_t*)((uint32_t)buf) + i)))
            {
                g_es_flash_eeprom_table[i + offset + NB_OF_PRIVATE_VAR] = (*((uint8_t*)((uint32_t)buf) + i));
                ee_write_variable(i + offset + NB_OF_PRIVATE_VAR);

            }
        }
        
        memcpy(&g_es_flash_eeprom_table[offset + NB_OF_PRIVATE_VAR], buf, len);
    }
}

void eeprom_read_block_user(void *buf, const void *addr, size_t len) {
    intptr_t offset = (intptr_t)addr;
    memset(buf, 0x00, len);
    len = clamp_length_user(offset, len);
    if (len > 0) {
        memcpy(buf, (uint8_t*)(USER_EEPROM_START_ADDRESS1 - ES_MCU_MEM_REMAP_OFFSET) + offset, len);
    }
}

void eeprom_write_block_user(const void *buf, void *addr, size_t len) {
    md_fc_ControlTypeDef ProgramPara;
    intptr_t offset = (intptr_t)addr;
    len             = clamp_length_user(offset, len);
    if (len > 0) {
        __disable_irq();
            if(memcmp(buf,(uint8_t*)(USER_EEPROM_START_ADDRESS1 - ES_MCU_MEM_REMAP_OFFSET) + offset,len))
            {
                    memcpy(&g_es_flash_eeprom_table[offset], buf, len);

                    md_fc_unlock();
                    ProgramPara.SAddr = USER_EEPROM_START_ADDRESS1;
                    ProgramPara.SAddrC = ~(USER_EEPROM_START_ADDRESS1);
                    md_fc_page_erase(&ProgramPara);
                    md_fc_lock();

                    md_fc_unlock();
                    ProgramPara.BCnt = NB_OF_PRIVATE_VAR;
                    ProgramPara.pU32Buf = (uint32_t*)(&g_es_flash_eeprom_table);
                    ProgramPara.SAddr = USER_EEPROM_START_ADDRESS1;
                    ProgramPara.SAddrC = ~(USER_EEPROM_START_ADDRESS1);
                    md_fc_program(&ProgramPara);
                    md_fc_lock();
            }
        __enable_irq();
    }
}
#endif

bool Save_Flash = false;
bool Reset_Save_Flash = false;
uint16_t Save_Flash_3S_Count = 0;
bool Led_Flash_Busy = false;

void Save_Flash_Set(void) {
    Save_Flash = true;
    Save_Flash_3S_Count = 0;
}