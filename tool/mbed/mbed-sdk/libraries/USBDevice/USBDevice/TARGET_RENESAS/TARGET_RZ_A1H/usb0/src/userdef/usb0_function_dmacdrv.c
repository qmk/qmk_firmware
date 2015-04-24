/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2012 - 2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : usb0_function_dmacdrv.c
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Device(s)    : RZ/A1H
* Tool-Chain   :
* OS           : None
* H/W Platform :
* Description  : RZ/A1H R7S72100 USB Sample Program
* Operation    :
* Limitations  :
*******************************************************************************/


/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdio.h>
#include "r_typedefs.h"
#include "iodefine.h"
#include "rza_io_regrw.h"
#include "usb0_function_dmacdrv.h"


/*******************************************************************************
Typedef definitions
*******************************************************************************/


/*******************************************************************************
Macro definitions
*******************************************************************************/
#define DMAC_INDEFINE   (255)       /* Macro definition when REQD bit is not used */

/* ==== Request setting information for on-chip peripheral module ==== */
typedef enum dmac_peri_req_reg_type
{
    DMAC_REQ_MID,
    DMAC_REQ_RID,
    DMAC_REQ_AM,
    DMAC_REQ_LVL,
    DMAC_REQ_REQD
} dmac_peri_req_reg_type_t;


/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


/*******************************************************************************
Private global variables and functions
*******************************************************************************/
/* ==== Prototype declaration ==== */

/* ==== Global variable ==== */
/* On-chip peripheral module request setting table */
static const uint8_t usb0_function_dmac_peri_req_init_table[8][5] =
{
    /* MID,RID,AM,LVL,REQD */
    {32, 3, 2, 1, 1},    /* USB_0 channel 0 transmit FIFO empty */
    {32, 3, 2, 1, 0},    /* USB_0 channel 0 receive FIFO full   */
    {33, 3, 2, 1, 1},    /* USB_0 channel 1 transmit FIFO empty */
    {33, 3, 2, 1, 0},    /* USB_0 channel 1 receive FIFO full   */
    {34, 3, 2, 1, 1},    /* USB_1 channel 0 transmit FIFO empty */
    {34, 3, 2, 1, 0},    /* USB_1 channel 0 receive FIFO full   */
    {35, 3, 2, 1, 1},    /* USB_1 channel 1 transmit FIFO empty */
    {35, 3, 2, 1, 0},    /* USB_1 channel 1 receive FIFO full   */
};


/*******************************************************************************
* Function Name: usb0_function_DMAC1_PeriReqInit
* Description  : Sets the register mode for DMA mode and the on-chip peripheral
*              : module request for transfer request for DMAC channel 1.
*              : Executes DMAC initial setting using the DMA information
*              : specified by the argument *trans_info and the enabled/disabled
*              : continuous transfer specified by the argument continuation.
*              : Registers DMAC channel 1 interrupt handler function and sets
*              : the interrupt priority level. Then enables transfer completion
*              : interrupt.
* Arguments    : dmac_transinfo_t *trans_info   : Setting information to DMAC register
*              : uint32_t          dmamode      : DMA mode (only for DMAC_MODE_REGISTER)
*              : uint32_t          continuation : Set continuous transfer to be valid
*              :                                  after DMA transfer has been completed
*              :             DMAC_SAMPLE_CONTINUATION : Execute continuous transfer
*              :             DMAC_SAMPLE_SINGLE       : Do not execute continuous transfer
*              : uint32_t request_factor        : Factor for on-chip peripheral module request
*              :             DMAC_REQ_OSTM0TINT       : OSTM_0 compare match
*              :             DMAC_REQ_OSTM1TINT       : OSTM_1 compare match
*              :             DMAC_REQ_TGI0A           : MTU2_0 input capture/compare match
*              :                  :
*              : uint32_t          req_direction: Setting value of CHCFG_n register REQD bit
* Return Value : none
*******************************************************************************/
void usb0_function_DMAC1_PeriReqInit (const dmac_transinfo_t * trans_info,
                                      uint32_t dmamode, uint32_t continuation,
                                      uint32_t request_factor, uint32_t req_direction)
{
    /* ==== Register mode ==== */
    if (DMAC_MODE_REGISTER == dmamode)
    {
        /* ==== Next0 register set ==== */
        DMAC1.N0SA_n = trans_info->src_addr;        /* Start address of transfer source      */
        DMAC1.N0DA_n = trans_info->dst_addr;        /* Start address of transfer destination */
        DMAC1.N0TB_n = trans_info->count;           /* Total transfer byte count             */

        /* DAD : Transfer destination address counting direction */
        /* SAD : Transfer source address counting direction      */
        /* DDS : Transfer destination transfer size              */
        /* SDS : Transfer source transfer size                   */
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            trans_info->daddr_dir,
                            DMAC1_CHCFG_n_DAD_SHIFT,
                            DMAC1_CHCFG_n_DAD);
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            trans_info->saddr_dir,
                            DMAC1_CHCFG_n_SAD_SHIFT,
                            DMAC1_CHCFG_n_SAD);
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            trans_info->dst_size,
                            DMAC1_CHCFG_n_DDS_SHIFT,
                            DMAC1_CHCFG_n_DDS);
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            trans_info->src_size,
                            DMAC1_CHCFG_n_SDS_SHIFT,
                            DMAC1_CHCFG_n_SDS);

        /* DMS  : Register mode                            */
        /* RSEL : Select Next0 register set                */
        /* SBE  : No discharge of buffer data when aborted */
        /* DEM  : No DMA interrupt mask                    */
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            0,
                            DMAC1_CHCFG_n_DMS_SHIFT,
                            DMAC1_CHCFG_n_DMS);
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            0,
                            DMAC1_CHCFG_n_RSEL_SHIFT,
                            DMAC1_CHCFG_n_RSEL);
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            0,
                            DMAC1_CHCFG_n_SBE_SHIFT,
                            DMAC1_CHCFG_n_SBE);
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            0,
                            DMAC1_CHCFG_n_DEM_SHIFT,
                            DMAC1_CHCFG_n_DEM);

        /* ---- Continuous transfer ---- */
        if (DMAC_SAMPLE_CONTINUATION == continuation)
        {
            /* REN : Execute continuous transfer                         */
            /* RSW : Change register set when DMA transfer is completed. */
            RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                                1,
                                DMAC1_CHCFG_n_REN_SHIFT,
                                DMAC1_CHCFG_n_REN);
            RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                                1,
                                DMAC1_CHCFG_n_RSW_SHIFT,
                                DMAC1_CHCFG_n_RSW);
        }
        /* ---- Single transfer ---- */
        else
        {
            /* REN : Do not execute continuous transfer                         */
            /* RSW : Do not change register set when DMA transfer is completed. */
            RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                                0,
                                DMAC1_CHCFG_n_REN_SHIFT,
                                DMAC1_CHCFG_n_REN);
            RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                                0,
                                DMAC1_CHCFG_n_RSW_SHIFT,
                                DMAC1_CHCFG_n_RSW);
        }

        /* TM  : Single transfer                          */
        /* SEL : Channel setting                          */
        /* HIEN, LOEN : On-chip peripheral module request */
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            0,
                            DMAC1_CHCFG_n_TM_SHIFT,
                            DMAC1_CHCFG_n_TM);
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            1,
                            DMAC1_CHCFG_n_SEL_SHIFT,
                            DMAC1_CHCFG_n_SEL);
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            1,
                            DMAC1_CHCFG_n_HIEN_SHIFT,
                            DMAC1_CHCFG_n_HIEN);
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            0,
                            DMAC1_CHCFG_n_LOEN_SHIFT,
                            DMAC1_CHCFG_n_LOEN);

        /* ---- Set factor by specified on-chip peripheral module request ---- */
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_AM],
                            DMAC1_CHCFG_n_AM_SHIFT,
                            DMAC1_CHCFG_n_AM);
        RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                            usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_LVL],
                            DMAC1_CHCFG_n_LVL_SHIFT,
                            DMAC1_CHCFG_n_LVL);

        if (usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_REQD] != DMAC_INDEFINE)
        {
            RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                                usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_REQD],
                                DMAC1_CHCFG_n_REQD_SHIFT,
                                DMAC1_CHCFG_n_REQD);
        }
        else
        {
            RZA_IO_RegWrite_32(&DMAC1.CHCFG_n,
                                req_direction,
                                DMAC1_CHCFG_n_REQD_SHIFT,
                                DMAC1_CHCFG_n_REQD);
        }

        RZA_IO_RegWrite_32(&DMAC01.DMARS,
                            usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_RID],
                            DMAC01_DMARS_CH1_RID_SHIFT,
                            DMAC01_DMARS_CH1_RID);
        RZA_IO_RegWrite_32(&DMAC01.DMARS,
                            usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_MID],
                            DMAC01_DMARS_CH1_MID_SHIFT,
                            DMAC01_DMARS_CH1_MID);

        /* PR : Round robin mode */
        RZA_IO_RegWrite_32(&DMAC07.DCTRL_0_7,
                            1,
                            DMAC07_DCTRL_0_7_PR_SHIFT,
                            DMAC07_DCTRL_0_7_PR);
    }
}

/*******************************************************************************
* Function Name: usb0_function_DMAC1_Open
* Description  : Enables DMAC channel 1 transfer.
* Arguments    : uint32_t req : DMAC request mode
* Return Value :  0 : Succeeded in enabling DMA transfer
*              : -1 : Failed to enable DMA transfer (due to DMA operation)
*******************************************************************************/
int32_t usb0_function_DMAC1_Open (uint32_t req)
{
    int32_t ret;
    volatile uint8_t dummy;

    /* Transferable? */
    if ((0 == RZA_IO_RegRead_32(&DMAC1.CHSTAT_n,
                                DMAC1_CHSTAT_n_EN_SHIFT,
                                DMAC1_CHSTAT_n_EN)) &&
        (0 == RZA_IO_RegRead_32(&DMAC1.CHSTAT_n,
                                DMAC1_CHSTAT_n_TACT_SHIFT,
                                DMAC1_CHSTAT_n_TACT)))
    {
        /* Clear Channel Status Register */
        RZA_IO_RegWrite_32(&DMAC1.CHCTRL_n,
                            1,
                            DMAC1_CHCTRL_n_SWRST_SHIFT,
                            DMAC1_CHCTRL_n_SWRST);
        dummy = RZA_IO_RegRead_32(&DMAC1.CHCTRL_n,
                                DMAC1_CHCTRL_n_SWRST_SHIFT,
                                DMAC1_CHCTRL_n_SWRST);
        /* Enable DMA transfer */
        RZA_IO_RegWrite_32(&DMAC1.CHCTRL_n,
                            1,
                            DMAC1_CHCTRL_n_SETEN_SHIFT,
                            DMAC1_CHCTRL_n_SETEN);

        /* ---- Request by software ---- */
        if (DMAC_REQ_MODE_SOFT == req)
        {
            /* DMA transfer Request by software */
            RZA_IO_RegWrite_32(&DMAC1.CHCTRL_n,
                                1,
                                DMAC1_CHCTRL_n_STG_SHIFT,
                                DMAC1_CHCTRL_n_STG);
        }

        ret = 0;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

/*******************************************************************************
* Function Name: usb0_function_DMAC1_Close
* Description  : Aborts DMAC channel 1 transfer. Returns the remaining transfer
*              : byte count at the time of DMA transfer abort to the argument
*              : *remain.
* Arguments    : uint32_t * remain : Remaining transfer byte count when
*              :                   : DMA transfer is aborted
* Return Value : none
*******************************************************************************/
void usb0_function_DMAC1_Close (uint32_t * remain)
{

    /* ==== Abort transfer ==== */
    RZA_IO_RegWrite_32(&DMAC1.CHCTRL_n,
                        1,
                        DMAC1_CHCTRL_n_CLREN_SHIFT,
                        DMAC1_CHCTRL_n_CLREN);

    while (1 == RZA_IO_RegRead_32(&DMAC1.CHSTAT_n,
                                DMAC1_CHSTAT_n_TACT_SHIFT,
                                DMAC1_CHSTAT_n_TACT))
    {
        /* Loop until transfer is aborted */
    }

    while (1 == RZA_IO_RegRead_32(&DMAC1.CHSTAT_n,
                                DMAC1_CHSTAT_n_EN_SHIFT,
                                DMAC1_CHSTAT_n_EN))
    {
        /* Loop until 0 is set in EN before checking the remaining transfer byte count */
    }
    /* ==== Obtain remaining transfer byte count ==== */
    *remain = DMAC1.CRTB_n;
}

/*******************************************************************************
* Function Name: usb0_function_DMAC1_Load_Set
* Description  : Sets the transfer source address, transfer destination
*              : address, and total transfer byte count respectively
*              : specified by the argument src_addr, dst_addr, and count to
*              : DMAC channel 1 as DMA transfer information.
*              : Sets the register set selected by the CHCFG_n register
*              : RSEL bit from the Next0 or Next1 register set.
*              : This function should be called when DMA transfer of DMAC
*              : channel 1 is aboted.
* Arguments    : uint32_t src_addr : Transfer source address
*              : uint32_t dst_addr : Transfer destination address
*              : uint32_t count    : Total transfer byte count
* Return Value : none
*******************************************************************************/
void usb0_function_DMAC1_Load_Set (uint32_t src_addr, uint32_t dst_addr, uint32_t count)
{
    uint8_t reg_set;

    /* Obtain register set in use */
    reg_set = RZA_IO_RegRead_32(&DMAC1.CHSTAT_n,
                                DMAC1_CHSTAT_n_SR_SHIFT,
                                DMAC1_CHSTAT_n_SR);

    /* ==== Load ==== */
    if (0 == reg_set)
    {
        /* ---- Next0 Register Set ---- */
        DMAC1.N0SA_n = src_addr;    /* Start address of transfer source      */
        DMAC1.N0DA_n = dst_addr;    /* Start address of transfer destination */
        DMAC1.N0TB_n = count;       /* Total transfer byte count             */
    }
    else
    {
        /* ---- Next1 Register Set ---- */
        DMAC1.N1SA_n = src_addr;    /* Start address of transfer source      */
        DMAC1.N1DA_n = dst_addr;    /* Start address of transfer destination */
        DMAC1.N1TB_n = count;       /* Total transfer byte count             */
     }
}

/*******************************************************************************
* Function Name: usb0_function_DMAC2_PeriReqInit
* Description  : Sets the register mode for DMA mode and the on-chip peripheral
*              : module request for transfer request for DMAC channel 2.
*              : Executes DMAC initial setting using the DMA information
*              : specified by the argument *trans_info and the enabled/disabled
*              : continuous transfer specified by the argument continuation.
*              : Registers DMAC channel 2 interrupt handler function and sets
*              : the interrupt priority level. Then enables transfer completion
*              : interrupt.
* Arguments    : dmac_transinfo_t * trans_info : Setting information to DMAC
*              :                               : register
*              : uint32_t dmamode      : DMA mode (only for DMAC_MODE_REGISTER)
*              : uint32_t continuation : Set continuous transfer to be valid
*              :                       : after DMA transfer has been completed
*              :         DMAC_SAMPLE_CONTINUATION : Execute continuous transfer
*              :         DMAC_SAMPLE_SINGLE       : Do not execute continuous
*              :                                  : transfer
*              : uint32_t request_factor : Factor for on-chip peripheral module
*              :                         : request
*              :         DMAC_REQ_OSTM0TINT : OSTM_0 compare match
*              :         DMAC_REQ_OSTM1TINT : OSTM_1 compare match
*              :         DMAC_REQ_TGI0A     : MTU2_0 input capture/compare match
*              :                 :
*              : uint32_t req_direction : Setting value of CHCFG_n register
*              :                        : REQD bit
*******************************************************************************/
void usb0_function_DMAC2_PeriReqInit (const dmac_transinfo_t * trans_info,
                                      uint32_t dmamode, uint32_t continuation,
                                      uint32_t request_factor, uint32_t req_direction)
{
    /* ==== Register mode ==== */
    if (DMAC_MODE_REGISTER == dmamode)
    {
        /* ==== Next0 register set ==== */
        DMAC2.N0SA_n = trans_info->src_addr;        /* Start address of transfer source      */
        DMAC2.N0DA_n = trans_info->dst_addr;        /* Start address of transfer destination */
        DMAC2.N0TB_n = trans_info->count;           /* Total transfer byte count             */

        /* DAD : Transfer destination address counting direction */
        /* SAD : Transfer source address counting direction      */
        /* DDS : Transfer destination transfer size              */
        /* SDS : Transfer source transfer size                   */
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            trans_info->daddr_dir,
                            DMAC2_CHCFG_n_DAD_SHIFT,
                            DMAC2_CHCFG_n_DAD);
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            trans_info->saddr_dir,
                            DMAC2_CHCFG_n_SAD_SHIFT,
                            DMAC2_CHCFG_n_SAD);
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            trans_info->dst_size,
                            DMAC2_CHCFG_n_DDS_SHIFT,
                            DMAC2_CHCFG_n_DDS);
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            trans_info->src_size,
                            DMAC2_CHCFG_n_SDS_SHIFT,
                            DMAC2_CHCFG_n_SDS);

        /* DMS  : Register mode                            */
        /* RSEL : Select Next0 register set                */
        /* SBE  : No discharge of buffer data when aborted */
        /* DEM  : No DMA interrupt mask                    */
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            0,
                            DMAC2_CHCFG_n_DMS_SHIFT,
                            DMAC2_CHCFG_n_DMS);
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            0,
                            DMAC2_CHCFG_n_RSEL_SHIFT,
                            DMAC2_CHCFG_n_RSEL);
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            0,
                            DMAC2_CHCFG_n_SBE_SHIFT,
                            DMAC2_CHCFG_n_SBE);
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            0,
                            DMAC2_CHCFG_n_DEM_SHIFT,
                            DMAC2_CHCFG_n_DEM);

        /* ---- Continuous transfer ---- */
        if (DMAC_SAMPLE_CONTINUATION == continuation)
        {
            /* REN : Execute continuous transfer                         */
            /* RSW : Change register set when DMA transfer is completed. */
            RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                                1,
                                DMAC2_CHCFG_n_REN_SHIFT,
                                DMAC2_CHCFG_n_REN);
            RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                                1,
                                DMAC2_CHCFG_n_RSW_SHIFT,
                                DMAC2_CHCFG_n_RSW);
        }
        /* ---- Single transfer ---- */
        else
        {
            /* REN : Do not execute continuous transfer                         */
            /* RSW : Do not change register set when DMA transfer is completed. */
            RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                                0,
                                DMAC2_CHCFG_n_REN_SHIFT,
                                DMAC2_CHCFG_n_REN);
            RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                                0,
                                DMAC2_CHCFG_n_RSW_SHIFT,
                                DMAC2_CHCFG_n_RSW);
        }

        /* TM  : Single transfer                          */
        /* SEL : Channel setting                          */
        /* HIEN, LOEN : On-chip peripheral module request */
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            0,
                            DMAC2_CHCFG_n_TM_SHIFT,
                            DMAC2_CHCFG_n_TM);
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            2,
                            DMAC2_CHCFG_n_SEL_SHIFT,
                            DMAC2_CHCFG_n_SEL);
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            1,
                            DMAC2_CHCFG_n_HIEN_SHIFT,
                            DMAC2_CHCFG_n_HIEN);
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            0,
                            DMAC2_CHCFG_n_LOEN_SHIFT,
                            DMAC2_CHCFG_n_LOEN);

        /* ---- Set factor by specified on-chip peripheral module request ---- */
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_AM],
                            DMAC2_CHCFG_n_AM_SHIFT,
                            DMAC2_CHCFG_n_AM);
        RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                            usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_LVL],
                            DMAC2_CHCFG_n_LVL_SHIFT,
                            DMAC2_CHCFG_n_LVL);
        if (usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_REQD] != DMAC_INDEFINE)
        {
            RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                                usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_REQD],
                                DMAC2_CHCFG_n_REQD_SHIFT,
                                DMAC2_CHCFG_n_REQD);
        }
        else
        {
            RZA_IO_RegWrite_32(&DMAC2.CHCFG_n,
                                req_direction,
                                DMAC2_CHCFG_n_REQD_SHIFT,
                                DMAC2_CHCFG_n_REQD);
        }
        RZA_IO_RegWrite_32(&DMAC23.DMARS,
                            usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_RID],
                            DMAC23_DMARS_CH2_RID_SHIFT,
                            DMAC23_DMARS_CH2_RID);
        RZA_IO_RegWrite_32(&DMAC23.DMARS,
                            usb0_function_dmac_peri_req_init_table[request_factor][DMAC_REQ_MID],
                            DMAC23_DMARS_CH2_MID_SHIFT,
                            DMAC23_DMARS_CH2_MID);

        /* PR : Round robin mode */
        RZA_IO_RegWrite_32(&DMAC07.DCTRL_0_7,
                            1,
                            DMAC07_DCTRL_0_7_PR_SHIFT,
                            DMAC07_DCTRL_0_7_PR);
    }
}

/*******************************************************************************
* Function Name: usb0_function_DMAC2_Open
* Description  : Enables DMAC channel 2 transfer.
* Arguments    : uint32_t req : DMAC request mode
* Return Value :  0 : Succeeded in enabling DMA transfer
*              : -1 : Failed to enable DMA transfer (due to DMA operation)
*******************************************************************************/
int32_t usb0_function_DMAC2_Open (uint32_t req)
{
    int32_t ret;
    volatile uint8_t dummy;

    /* Transferable? */
    if ((0 == RZA_IO_RegRead_32(&DMAC.CHSTAT_2,
                                DMAC2_CHSTAT_n_EN_SHIFT,
                                DMAC2_CHSTAT_n_EN)) &&
        (0 == RZA_IO_RegRead_32(&DMAC.CHSTAT_2,
                                DMAC2_CHSTAT_n_TACT_SHIFT,
                                DMAC2_CHSTAT_n_TACT)))
    {
        /* Clear Channel Status Register */
        RZA_IO_RegWrite_32(&DMAC2.CHCTRL_n,
                            1,
                            DMAC2_CHCTRL_n_SWRST_SHIFT,
                            DMAC2_CHCTRL_n_SWRST);
        dummy = RZA_IO_RegRead_32(&DMAC2.CHCTRL_n,
                                DMAC2_CHCTRL_n_SWRST_SHIFT,
                                DMAC2_CHCTRL_n_SWRST);
        /* Enable DMA transfer */
        RZA_IO_RegWrite_32(&DMAC2.CHCTRL_n,
                            1,
                            DMAC2_CHCTRL_n_SETEN_SHIFT,
                            DMAC2_CHCTRL_n_SETEN);

        /* ---- Request by software ---- */
        if (DMAC_REQ_MODE_SOFT == req)
        {
            /* DMA transfer Request by software */
            RZA_IO_RegWrite_32(&DMAC2.CHCTRL_n,
                                1,
                                DMAC2_CHCTRL_n_STG_SHIFT,
                                DMAC2_CHCTRL_n_STG);
        }

        ret = 0;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

/*******************************************************************************
* Function Name: usb0_function_DMAC2_Close
* Description  : Aborts DMAC channel 2 transfer. Returns the remaining transfer
*              : byte count at the time of DMA transfer abort to the argument
*              : *remain.
* Arguments    : uint32_t * remain : Remaining transfer byte count when
*              :                   : DMA transfer is aborted
* Return Value : none
*******************************************************************************/
void usb0_function_DMAC2_Close (uint32_t * remain)
{

    /* ==== Abort transfer ==== */
    RZA_IO_RegWrite_32(&DMAC2.CHCTRL_n,
                        1,
                        DMAC2_CHCTRL_n_CLREN_SHIFT,
                        DMAC2_CHCTRL_n_CLREN);

    while (1 == RZA_IO_RegRead_32(&DMAC2.CHSTAT_n,
                                DMAC2_CHSTAT_n_TACT_SHIFT,
                                DMAC2_CHSTAT_n_TACT))
    {
        /* Loop until transfer is aborted */
    }

    while (1 == RZA_IO_RegRead_32(&DMAC2.CHSTAT_n,
                                DMAC2_CHSTAT_n_EN_SHIFT,
                                DMAC2_CHSTAT_n_EN))
    {
        /* Loop until 0 is set in EN before checking the remaining transfer byte count */
    }
    /* ==== Obtain remaining transfer byte count ==== */
    *remain = DMAC2.CRTB_n;
}

/*******************************************************************************
* Function Name: usb0_function_DMAC2_Load_Set
* Description  : Sets the transfer source address, transfer destination
*              : address, and total transfer byte count respectively
*              : specified by the argument src_addr, dst_addr, and count to
*              : DMAC channel 2 as DMA transfer information.
*              : Sets the register set selected by the CHCFG_n register
*              : RSEL bit from the Next0 or Next1 register set.
*              : This function should be called when DMA transfer of DMAC
*              : channel 2 is aboted.
* Arguments    : uint32_t src_addr : Transfer source address
*              : uint32_t dst_addr : Transfer destination address
*              : uint32_t count    : Total transfer byte count
* Return Value : none
*******************************************************************************/
void usb0_function_DMAC2_Load_Set (uint32_t src_addr, uint32_t dst_addr, uint32_t count)
{
    uint8_t reg_set;

    /* Obtain register set in use */
    reg_set = RZA_IO_RegRead_32(&DMAC2.CHSTAT_n,
                                DMAC2_CHSTAT_n_SR_SHIFT,
                                DMAC2_CHSTAT_n_SR);

    /* ==== Load ==== */
    if (0 == reg_set)
    {
        /* ---- Next0 Register Set ---- */
        DMAC2.N0SA_n = src_addr;     /* Start address of transfer source      */
        DMAC2.N0DA_n = dst_addr;     /* Start address of transfer destination */
        DMAC2.N0TB_n = count;        /* Total transfer byte count             */
    }
    else
    {
        /* ---- Next1 Register Set ---- */
        DMAC2.N1SA_n = src_addr;     /* Start address of transfer source      */
        DMAC2.N1DA_n = dst_addr;     /* Start address of transfer destination */
        DMAC2.N1TB_n = count;        /* Total transfer byte count             */
     }
}

/* End of File */
