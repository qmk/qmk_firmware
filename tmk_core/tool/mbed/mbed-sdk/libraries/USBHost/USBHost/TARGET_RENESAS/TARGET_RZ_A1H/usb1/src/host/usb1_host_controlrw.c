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
* File Name    : usb1_host_controlrw.c
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
#include "usb1_host.h"
#include "dev_drv.h"


/*******************************************************************************
Typedef definitions
*******************************************************************************/


/*******************************************************************************
Macro definitions
*******************************************************************************/


/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


/*******************************************************************************
Private global variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: usb1_host_CtrlTransStart
* Description  : Executes USB control transfer.
* Arguments    : uint16_t devadr ; device address
*              : uint16_t Req   ; bmRequestType & bRequest
*              : uint16_t Val   ; wValue
*              : uint16_t Indx  ; wIndex
*              : uint16_t Len   ; wLength
*              : uint8_t  *Buf  ; Data buffer
* Return Value : DEVDRV_SUCCESS     ;   SUCCESS
*              : DEVDRV_ERROR       ;   ERROR
*******************************************************************************/
int32_t usb1_host_CtrlTransStart (uint16_t devadr, uint16_t Req, uint16_t Val,
                            uint16_t Indx, uint16_t Len, uint8_t * Buf)
{
    if (g_usb1_host_UsbDeviceSpeed == USB_HOST_LOW_SPEED)
    {
        RZA_IO_RegWrite_16(&USB201.SOFCFG,
                            1,
                            USB_SOFCFG_TRNENSEL_SHIFT,
                            USB_SOFCFG_TRNENSEL);
    }
    else
    {
        RZA_IO_RegWrite_16(&USB201.SOFCFG,
                            0,
                            USB_SOFCFG_TRNENSEL_SHIFT,
                            USB_SOFCFG_TRNENSEL);
    }

    USB201.DCPMAXP = (uint16_t)((uint16_t)(devadr << 12) + g_usb1_host_default_max_packet[devadr]);

    if (g_usb1_host_pipe_status[USB_HOST_PIPE0] == USB_HOST_PIPE_IDLE)
    {
        g_usb1_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_WAIT;
        g_usb1_host_PipeIgnore[USB_HOST_PIPE0]  = 0;                    /* Ignore count clear */
        g_usb1_host_CmdStage = (USB_HOST_STAGE_SETUP | USB_HOST_CMD_IDLE);

        if (Len == 0)
        {
            g_usb1_host_CmdStage |= USB_HOST_MODE_NO_DATA;              /* No-data Control */
        }
        else
        {
            if ((Req & 0x0080) != 0)
            {
                g_usb1_host_CmdStage |= USB_HOST_MODE_READ;             /* Control Read */
            }
            else
            {
                g_usb1_host_CmdStage |= USB_HOST_MODE_WRITE;            /* Control Write */
            }
        }

        g_usb1_host_SavReq  = Req;                                      /* save request */
        g_usb1_host_SavVal  = Val;
        g_usb1_host_SavIndx = Indx;
        g_usb1_host_SavLen  = Len;
    }
    else
    {
        if ((g_usb1_host_SavReq  != Req)  || (g_usb1_host_SavVal != Val)
         || (g_usb1_host_SavIndx != Indx) || (g_usb1_host_SavLen != Len))
        {
            return DEVDRV_ERROR;
        }
    }

    switch ((g_usb1_host_CmdStage & (USB_HOST_STAGE_FIELD | USB_HOST_CMD_FIELD)))
    {
        /* --------------- SETUP STAGE --------------- */
        case (USB_HOST_STAGE_SETUP | USB_HOST_CMD_IDLE):
            usb1_host_SetupStage(Req, Val, Indx, Len);
        break;

        case (USB_HOST_STAGE_SETUP | USB_HOST_CMD_DOING):
            /* do nothing */
        break;

        case (USB_HOST_STAGE_SETUP | USB_HOST_CMD_DONE):                /* goto next stage */
            g_usb1_host_PipeIgnore[USB_HOST_PIPE0]  = 0;                /* Ignore count clear */
            switch ((g_usb1_host_CmdStage & (USB_HOST_MODE_FIELD)))
            {
                case USB_HOST_MODE_WRITE:
                    g_usb1_host_CmdStage &= (~USB_HOST_STAGE_FIELD);
                    g_usb1_host_CmdStage |= USB_HOST_STAGE_DATA;
                break;

                case USB_HOST_MODE_READ:
                    g_usb1_host_CmdStage &= (~USB_HOST_STAGE_FIELD);
                    g_usb1_host_CmdStage |= USB_HOST_STAGE_DATA;
                break;

                case USB_HOST_MODE_NO_DATA:
                    g_usb1_host_CmdStage &= (~USB_HOST_STAGE_FIELD);
                    g_usb1_host_CmdStage |= USB_HOST_STAGE_STATUS;
                break;

                default:
                break;
            }
            g_usb1_host_CmdStage &= (~USB_HOST_CMD_FIELD);
            g_usb1_host_CmdStage |= USB_HOST_CMD_IDLE;
        break;

        case (USB_HOST_STAGE_SETUP | USB_HOST_CMD_NORES):
            if (g_usb1_host_PipeIgnore[USB_HOST_PIPE0] == 3)
            {
                g_usb1_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_NORES;  /* exit NORES */
            }
            else
            {
                g_usb1_host_PipeIgnore[USB_HOST_PIPE0]++;                       /* Ignore count */
                g_usb1_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                g_usb1_host_CmdStage |= USB_HOST_CMD_IDLE;
            }
        break;

        /* --------------- DATA STAGE --------------- */
        case (USB_HOST_STAGE_DATA | USB_HOST_CMD_IDLE):
            switch ((g_usb1_host_CmdStage & (USB_HOST_MODE_FIELD)))
            {
                case USB_HOST_MODE_WRITE:
                    usb1_host_CtrlWriteStart((uint32_t)Len, Buf);
                break;

                case USB_HOST_MODE_READ:
                    usb1_host_CtrlReadStart((uint32_t)Len, Buf);
                break;

                default:
                break;
            }
        break;

        case (USB_HOST_STAGE_DATA | USB_HOST_CMD_DOING):
            /* do nothing */
        break;

        case (USB_HOST_STAGE_DATA | USB_HOST_CMD_DONE):                         /* goto next stage */
            g_usb1_host_PipeIgnore[USB_HOST_PIPE0]  = 0;                        /* Ignore count clear */
            g_usb1_host_CmdStage &= (~USB_HOST_STAGE_FIELD);
            g_usb1_host_CmdStage |= USB_HOST_STAGE_STATUS;
            g_usb1_host_CmdStage &= (~USB_HOST_CMD_FIELD);
            g_usb1_host_CmdStage |= USB_HOST_CMD_IDLE;
        break;

        case (USB_HOST_STAGE_DATA | USB_HOST_CMD_NORES):
            if (g_usb1_host_PipeIgnore[USB_HOST_PIPE0] == 3)
            {
                g_usb1_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_NORES;  /* exit NORES */
            }
            else
            {
                g_usb1_host_PipeIgnore[USB_HOST_PIPE0]++;                       /* Ignore count */
                g_usb1_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                g_usb1_host_CmdStage |= USB_HOST_CMD_DOING;
                usb1_host_clear_pid_stall(USB_HOST_PIPE0);
                usb1_host_set_pid_buf(USB_HOST_PIPE0);
            }
        break;

        case (USB_HOST_STAGE_DATA | USB_HOST_CMD_STALL):
            g_usb1_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_STALL;      /* exit STALL */
        break;

        /* --------------- STATUS STAGE --------------- */
        case (USB_HOST_STAGE_STATUS | USB_HOST_CMD_IDLE):
            usb1_host_StatusStage();
        break;

        case (USB_HOST_STAGE_STATUS | USB_HOST_CMD_DOING):
            /* do nothing */
        break;

        case (USB_HOST_STAGE_STATUS | USB_HOST_CMD_DONE):                       /* end of Control transfer */
            usb1_host_set_pid_nak(USB_HOST_PIPE0);
            g_usb1_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_DONE;       /* exit DONE */
        break;

        case (USB_HOST_STAGE_STATUS | USB_HOST_CMD_NORES):
            if (g_usb1_host_PipeIgnore[USB_HOST_PIPE0] == 3)
            {
                g_usb1_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_NORES;  /* exit NORES */
            }
            else
            {
                g_usb1_host_PipeIgnore[USB_HOST_PIPE0]++;                       /* Ignore count */
                g_usb1_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                g_usb1_host_CmdStage |= USB_HOST_CMD_DOING;
                usb1_host_clear_pid_stall(USB_HOST_PIPE0);
                usb1_host_set_pid_buf(USB_HOST_PIPE0);
            }
        break;

        case (USB_HOST_STAGE_STATUS | USB_HOST_CMD_STALL):
            g_usb1_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_STALL;      /* exit STALL */
        break;

        default:
        break;
    }

    if (g_usb1_host_pipe_status[USB_HOST_PIPE0] != USB_HOST_PIPE_WAIT)
    {
        RZA_IO_RegWrite_16(&USB201.SOFCFG,
                            0,
                            USB_SOFCFG_TRNENSEL_SHIFT,
                            USB_SOFCFG_TRNENSEL);
    }

    return DEVDRV_SUCCESS;
}

/*******************************************************************************
* Function Name: usb1_host_SetupStage
* Description  : Executes USB control transfer/set up stage.
* Arguments    : uint16_t Req           ; bmRequestType & bRequest
*              : uint16_t Val           ; wValue
*              : uint16_t Indx          ; wIndex
*              : uint16_t Len           ; wLength
* Return Value : none
*******************************************************************************/
void usb1_host_SetupStage (uint16_t Req, uint16_t Val, uint16_t Indx, uint16_t Len)
{
    g_usb1_host_CmdStage &= (~USB_HOST_CMD_FIELD);
    g_usb1_host_CmdStage |= USB_HOST_CMD_DOING;

    USB201.INTSTS1 = (uint16_t)~(USB_HOST_BITSACK | USB_HOST_BITSIGN);  /* Status Clear */
    USB201.USBREQ  = Req;
    USB201.USBVAL  = Val;
    USB201.USBINDX = Indx;
    USB201.USBLENG = Len;
    USB201.DCPCTR  = USB_HOST_BITSUREQ;                                 /* PID=NAK & Send Setup */
}

/*******************************************************************************
* Function Name: usb1_host_StatusStage
* Description  : Executes USB control transfer/status stage.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_StatusStage (void)
{
    uint8_t Buf1[16];

    switch ((g_usb1_host_CmdStage & (USB_HOST_MODE_FIELD)))
    {
        case USB_HOST_MODE_READ:
            usb1_host_CtrlWriteStart((uint32_t)0, (uint8_t*)&Buf1);
        break;

        case USB_HOST_MODE_WRITE:
            usb1_host_CtrlReadStart((uint32_t)0, (uint8_t*)&Buf1);
        break;

        case USB_HOST_MODE_NO_DATA:
            usb1_host_CtrlReadStart((uint32_t)0, (uint8_t*)&Buf1);
        break;

        default:
        break;
    }
}

/*******************************************************************************
* Function Name: usb1_host_CtrlWriteStart
* Description  : Executes USB control transfer/data stage(write).
* Arguments    : uint32_t Bsize     ; Data Size
*              : uint8_t  *Table    ; Data Table Address
* Return Value : USB_HOST_WRITESHRT ; End of data write
*              : USB_HOST_WRITEEND  ; End of data write (not null)
*              : USB_HOST_WRITING   ; Continue of data write
*              : USB_HOST_FIFOERROR ; FIFO access error
*******************************************************************************/
uint16_t usb1_host_CtrlWriteStart (uint32_t Bsize, uint8_t * Table)
{
    uint16_t EndFlag_K;
    uint16_t mbw;

    g_usb1_host_CmdStage &= (~USB_HOST_CMD_FIELD);
    g_usb1_host_CmdStage |= USB_HOST_CMD_DOING;

    usb1_host_set_pid_nak(USB_HOST_PIPE0);                              /* Set NAK */
    g_usb1_host_data_count[USB_HOST_PIPE0]   = Bsize;                   /* Transfer size set */
    g_usb1_host_data_pointer[USB_HOST_PIPE0] = Table;                   /* Transfer address set */

    USB201.DCPCTR = USB_HOST_BITSQSET;                                  /* SQSET=1, PID=NAK */
#if(1) /* ohci_wrapp */
    Userdef_USB_usb1_host_delay_10us(3);
#endif
    RZA_IO_RegWrite_16(&USB201.DCPCFG,
                        1,
                        USB_DCPCFG_DIR_SHIFT,
                        USB_DCPCFG_DIR);

    mbw = usb1_host_get_mbw(g_usb1_host_data_count[USB_HOST_PIPE0], (uint32_t)g_usb1_host_data_pointer[USB_HOST_PIPE0]);
    usb1_host_set_curpipe(USB_HOST_PIPE0, USB_HOST_CUSE, USB_HOST_BITISEL, mbw);
    USB201.CFIFOCTR = USB_HOST_BITBCLR;                                 /* Buffer Clear */

    usb1_host_clear_pid_stall(USB_HOST_PIPE0);
    EndFlag_K = usb1_host_write_buffer_c(USB_HOST_PIPE0);
    /* Host Control sequence */
    switch (EndFlag_K)
    {
        case USB_HOST_WRITESHRT:                                        /* End of data write */
            g_usb1_host_CmdStage &= (~USB_HOST_STAGE_FIELD);
            g_usb1_host_CmdStage |= USB_HOST_STAGE_STATUS;
            usb1_host_enable_nrdy_int(USB_HOST_PIPE0);                  /* Error (NORES or STALL) */
            usb1_host_enable_bemp_int(USB_HOST_PIPE0);                  /* Enable Empty Interrupt */
        break;

        case USB_HOST_WRITEEND:                                         /* End of data write (not null) */
        case USB_HOST_WRITING:                                          /* Continue of data write */
            usb1_host_enable_nrdy_int(USB_HOST_PIPE0);                  /* Error (NORES or STALL) */
            usb1_host_enable_bemp_int(USB_HOST_PIPE0);                  /* Enable Empty Interrupt */
        break;

        case USB_HOST_FIFOERROR:                                        /* FIFO access error */
        break;

        default:
        break;
    }
    usb1_host_set_pid_buf(USB_HOST_PIPE0);                              /* Set BUF */
    return (EndFlag_K);                                                 /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_CtrlReadStart
* Description  : Executes USB control transfer/data stage(read).
* Arguments    : uint32_t Bsize     ; Data Size
*              : uint8_t  *Table    ; Data Table Address
* Return Value : none
*******************************************************************************/
void usb1_host_CtrlReadStart (uint32_t Bsize, uint8_t * Table)
{
    uint16_t mbw;

    g_usb1_host_CmdStage &= (~USB_HOST_CMD_FIELD);
    g_usb1_host_CmdStage |= USB_HOST_CMD_DOING;

    usb1_host_set_pid_nak(USB_HOST_PIPE0);                  /* Set NAK */
    g_usb1_host_data_count[USB_HOST_PIPE0]   = Bsize;       /* Transfer size set */
    g_usb1_host_data_pointer[USB_HOST_PIPE0] = Table;       /* Transfer address set */

    USB201.DCPCTR     = USB_HOST_BITSQSET;                  /* SQSET=1, PID=NAK */
#if(1) /* ohci_wrapp */
    Userdef_USB_usb1_host_delay_10us(3);
#endif
    RZA_IO_RegWrite_16(&USB201.DCPCFG,
                        0,
                        USB_DCPCFG_DIR_SHIFT,
                        USB_DCPCFG_DIR);

    mbw = usb1_host_get_mbw(g_usb1_host_data_count[USB_HOST_PIPE0], (uint32_t)g_usb1_host_data_pointer[USB_HOST_PIPE0]);
    usb1_host_set_curpipe(USB_HOST_PIPE0, USB_HOST_CUSE, USB_HOST_NO, mbw);
    USB201.CFIFOCTR = USB_HOST_BITBCLR;                     /* Buffer Clear */

    usb1_host_enable_nrdy_int(USB_HOST_PIPE0);              /* Error (NORES or STALL) */
    usb1_host_enable_brdy_int(USB_HOST_PIPE0);              /* Ok */
    usb1_host_clear_pid_stall(USB_HOST_PIPE0);
    usb1_host_set_pid_buf(USB_HOST_PIPE0);                  /* Set BUF */
}

/* End of File */
