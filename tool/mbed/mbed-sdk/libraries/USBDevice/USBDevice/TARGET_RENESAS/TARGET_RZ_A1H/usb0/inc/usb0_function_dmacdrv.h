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
* File Name    : usb0_function_dmacdrv.h
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Description  : RZ/A1H R7S72100 USB Sample Program
*******************************************************************************/
#ifndef USB0_FUNCTION_DMACDRV_H
#define USB0_FUNCTION_DMACDRV_H


/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
Typedef definitions
*******************************************************************************/
typedef struct dmac_transinfo
{
    uint32_t src_addr;      /* Transfer source address                */
    uint32_t dst_addr;      /* Transfer destination address           */
    uint32_t count;         /* Transfer byte count                    */
    uint32_t src_size;      /* Transfer source data size              */
    uint32_t dst_size;      /* Transfer destination data size         */
    uint32_t saddr_dir;     /* Transfer source address direction      */
    uint32_t daddr_dir;     /* Transfer destination address direction */
} dmac_transinfo_t;


/*******************************************************************************
Macro definitions
*******************************************************************************/
/* ==== Transfer specification of the sample program ==== */
#define DMAC_SAMPLE_SINGLE          (0)     /* Single transfer                   */
#define DMAC_SAMPLE_CONTINUATION    (1)     /* Continuous transfer (use REN bit) */

/* ==== DMA modes ==== */
#define DMAC_MODE_REGISTER          (0)     /* Register mode */
#define DMAC_MODE_LINK              (1)     /* Link mode     */

/* ==== Transfer requests ==== */
#define DMAC_REQ_MODE_EXT           (0)     /* External request                   */
#define DMAC_REQ_MODE_PERI          (1)     /* On-chip peripheral module request  */
#define DMAC_REQ_MODE_SOFT          (2)     /* Auto-request (request by software) */

/* ==== DMAC transfer sizes ==== */
#define DMAC_TRANS_SIZE_8           (0)     /* 8 bits    */
#define DMAC_TRANS_SIZE_16          (1)     /* 16 bits   */
#define DMAC_TRANS_SIZE_32          (2)     /* 32 bits   */
#define DMAC_TRANS_SIZE_64          (3)     /* 64 bits   */
#define DMAC_TRANS_SIZE_128         (4)     /* 128 bits  */
#define DMAC_TRANS_SIZE_256         (5)     /* 256 bits  */
#define DMAC_TRANS_SIZE_512         (6)     /* 512 bits  */
#define DMAC_TRANS_SIZE_1024        (7)     /* 1024 bits */

/* ==== Address increment for transferring ==== */
#define DMAC_TRANS_ADR_NO_INC       (1)     /* Not increment */
#define DMAC_TRANS_ADR_INC          (0)     /* Increment     */

/* ==== Method for detecting DMA request ==== */
#define DMAC_REQ_DET_FALL           (0)     /* Falling edge detection */
#define DMAC_REQ_DET_RISE           (1)     /* Rising edge detection  */
#define DMAC_REQ_DET_LOW            (2)     /* Low level detection    */
#define DMAC_REQ_DET_HIGH           (3)     /* High level detection   */

/* ==== Request Direction ==== */
#define DMAC_REQ_DIR_SRC            (0)     /* DMAREQ is the source/ DMAACK is active when reading      */
#define DMAC_REQ_DIR_DST            (1)     /* DMAREQ is the destination/ DMAACK is active when writing */

/* ==== Descriptors ==== */
#define DMAC_DESC_HEADER            (0)     /* Header              */
#define DMAC_DESC_SRC_ADDR          (1)     /* Source Address      */
#define DMAC_DESC_DST_ADDR          (2)     /* Destination Address */
#define DMAC_DESC_COUNT             (3)     /* Transaction Byte    */
#define DMAC_DESC_CHCFG             (4)     /* Channel Confg       */
#define DMAC_DESC_CHITVL            (5)     /* Channel Interval    */
#define DMAC_DESC_CHEXT             (6)     /* Channel Extension   */
#define DMAC_DESC_LINK_ADDR         (7)     /* Link Address        */

/* ==== On-chip peripheral module requests ===== */
typedef enum dmac_request_factor
{
    DMAC_REQ_USB0_DMA0_TX,      /* USB_0 channel 0 transmit FIFO empty            */
    DMAC_REQ_USB0_DMA0_RX,      /* USB_0 channel 0 receive FIFO full              */
    DMAC_REQ_USB0_DMA1_TX,      /* USB_0 channel 1 transmit FIFO empty            */
    DMAC_REQ_USB0_DMA1_RX,      /* USB_0 channel 1 receive FIFO full              */
    DMAC_REQ_USB1_DMA0_TX,      /* USB_1 channel 0 transmit FIFO empty            */
    DMAC_REQ_USB1_DMA0_RX,      /* USB_1 channel 0 receive FIFO full              */
    DMAC_REQ_USB1_DMA1_TX,      /* USB_1 channel 1 transmit FIFO empty            */
    DMAC_REQ_USB1_DMA1_RX,      /* USB_1 channel 1 receive FIFO full              */
} dmac_request_factor_t;


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
void usb0_function_DMAC1_PeriReqInit(const dmac_transinfo_t *trans_info, uint32_t dmamode, uint32_t continuation,
                                        uint32_t request_factor, uint32_t req_direction);
int32_t usb0_function_DMAC1_Open(uint32_t req);
void usb0_function_DMAC1_Close(uint32_t *remain);
void usb0_function_DMAC1_Load_Set(uint32_t src_addr, uint32_t dst_addr, uint32_t count);

void usb0_function_DMAC2_PeriReqInit(const dmac_transinfo_t *trans_info, uint32_t dmamode, uint32_t continuation,
                                        uint32_t request_factor, uint32_t req_direction);
int32_t usb0_function_DMAC2_Open(uint32_t req);
void usb0_function_DMAC2_Close(uint32_t *remain);
void usb0_function_DMAC2_Load_Set(uint32_t src_addr, uint32_t dst_addr, uint32_t count);

#ifdef __cplusplus
}
#endif

#endif /* USB0_FUNCTION_DMACDRV_H */

/* End of File */
