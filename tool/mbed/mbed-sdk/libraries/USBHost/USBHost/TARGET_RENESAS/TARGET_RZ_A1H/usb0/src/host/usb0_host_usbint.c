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
* File Name    : usb0_host_usbint.c
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
#include "usb0_host.h"
#if(1) /* ohci_wrapp */
#include "ohci_wrapp_RZ_A1_local.h"
#endif


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
static void usb0_host_interrupt1(void);
static void usb0_host_BRDYInterrupt(uint16_t Status, uint16_t Int_enbl);
static void usb0_host_NRDYInterrupt(uint16_t Status, uint16_t Int_enbl);
static void usb0_host_BEMPInterrupt(uint16_t Status, uint16_t Int_enbl);


/*******************************************************************************
Private global variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: usb0_host_interrupt
* Description  : Executes USB interrupt.
*              : Register this function in the USB interrupt handler.
*              : Set CFIF0 in the pipe set before the interrupt after executing
*              : this function.
* Arguments    : uint32_t int_sense ; Interrupts detection mode
*              :                    ;  INTC_LEVEL_SENSITIVE : Level sense
*              :                    ;  INTC_EDGE_TRIGGER : Edge trigger
* Return Value : none
*******************************************************************************/
void usb0_host_interrupt (uint32_t int_sense)
{
    uint16_t savepipe1;
    uint16_t savepipe2;
    uint16_t buffer;

    savepipe1 = USB200.CFIFOSEL;
    savepipe2 = USB200.PIPESEL;
    usb0_host_interrupt1();

    /* Control transmission changes ISEL within interruption processing. */
    /* For this reason, write return of ISEL cannot be performed. */
    buffer = USB200.CFIFOSEL;
    buffer &= (uint16_t)~(USB_HOST_BITCURPIPE);
    buffer |= (uint16_t)(savepipe1 & USB_HOST_BITCURPIPE);
    USB200.CFIFOSEL = buffer;
    USB200.PIPESEL = savepipe2;
}

/*******************************************************************************
* Function Name: usb0_host_interrupt1
* Description  : Execue the USB interrupt.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb0_host_interrupt1 (void)
{
    uint16_t intsts0;
    uint16_t intsts1;
    uint16_t intenb0;
    uint16_t intenb1;
    uint16_t brdysts;
    uint16_t nrdysts;
    uint16_t bempsts;
    uint16_t brdyenb;
    uint16_t nrdyenb;
    uint16_t bempenb;
    volatile uint16_t dumy_sts;

    intsts0 = USB200.INTSTS0;
    intsts1 = USB200.INTSTS1;
    intenb0 = USB200.INTENB0;
    intenb1 = USB200.INTENB1;

    if ((intsts1 & USB_HOST_BITBCHG) && (intenb1 & USB_HOST_BITBCHGE))
    {
            USB200.INTSTS1 = (uint16_t)~USB_HOST_BITBCHG;
            RZA_IO_RegWrite_16(&USB200.INTENB1,
                                0,
                                USB_INTENB1_BCHGE_SHIFT,
                                USB_INTENB1_BCHGE);
            g_usb0_host_bchg_flag = USB_HOST_YES;
    }
    else if ((intsts1 & USB_HOST_BITSACK) && (intenb1 & USB_HOST_BITSACKE))
    {
        USB200.INTSTS1 = (uint16_t)~USB_HOST_BITSACK;
#if(1) /* ohci_wrapp */
        ohciwrapp_loc_TransEnd(USB_HOST_PIPE0, TD_CC_NOERROR);
#else
        g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
        g_usb0_host_CmdStage |= USB_HOST_CMD_DONE;
#endif
    }
    else if ((intsts1 & USB_HOST_BITSIGN) && (intenb1 & USB_HOST_BITSIGNE))
    {
        USB200.INTSTS1 = (uint16_t)~USB_HOST_BITSIGN;
#if(1) /* ohci_wrapp */
        g_usb0_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_NORES;  /* exit NORES */
        ohciwrapp_loc_TransEnd(USB_HOST_PIPE0, TD_CC_STALL);
#else
        g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
        g_usb0_host_CmdStage |= USB_HOST_CMD_NORES;
#endif
    }
    else if (((intsts1 & USB_HOST_BITDTCH) == USB_HOST_BITDTCH)
          && ((intenb1 & USB_HOST_BITDTCHE) == USB_HOST_BITDTCHE))
    {
        USB200.INTSTS1 = (uint16_t)~USB_HOST_BITDTCH;
        RZA_IO_RegWrite_16(&USB200.INTENB1,
                            0,
                            USB_INTENB1_DTCHE_SHIFT,
                            USB_INTENB1_DTCHE);
        g_usb0_host_detach_flag = USB_HOST_YES;

        Userdef_USB_usb0_host_detach();

        usb0_host_UsbDetach2();
    }
    else if (((intsts1 & USB_HOST_BITATTCH) == USB_HOST_BITATTCH)
          && ((intenb1 & USB_HOST_BITATTCHE) == USB_HOST_BITATTCHE))
    {
        USB200.INTSTS1 = (uint16_t)~USB_HOST_BITATTCH;
        RZA_IO_RegWrite_16(&USB200.INTENB1,
                            0,
                            USB_INTENB1_ATTCHE_SHIFT,
                            USB_INTENB1_ATTCHE);
        g_usb0_host_attach_flag = USB_HOST_YES;

        Userdef_USB_usb0_host_attach();

        usb0_host_UsbAttach();
    }
    else if ((intsts0 & intenb0 & (USB_HOST_BITBEMP | USB_HOST_BITNRDY | USB_HOST_BITBRDY)))
    {
        brdysts = USB200.BRDYSTS;
        nrdysts = USB200.NRDYSTS;
        bempsts = USB200.BEMPSTS;
        brdyenb = USB200.BRDYENB;
        nrdyenb = USB200.NRDYENB;
        bempenb = USB200.BEMPENB;

        if ((intsts0 & USB_HOST_BITBRDY) && (intenb0 & USB_HOST_BITBRDYE) && (brdysts & brdyenb))
        {
            usb0_host_BRDYInterrupt(brdysts, brdyenb);
        }
        else if ((intsts0 & USB_HOST_BITBEMP) && (intenb0 & USB_HOST_BITBEMPE) && (bempsts & bempenb))
        {
            usb0_host_BEMPInterrupt(bempsts, bempenb);
        }
        else if ((intsts0 & USB_HOST_BITNRDY) && (intenb0 & USB_HOST_BITNRDYE) && (nrdysts & nrdyenb))
        {
            usb0_host_NRDYInterrupt(nrdysts, nrdyenb);
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    /* Three dummy read for clearing interrupt requests */
    dumy_sts = USB200.INTSTS0;
    dumy_sts = USB200.INTSTS1;

}

/*******************************************************************************
* Function Name: usb0_host_BRDYInterrupt
* Description  : Executes USB BRDY interrupt.
* Arguments    : uint16_t Status   ; BRDYSTS Register Value
*              : uint16_t Int_enbl ; BRDYENB Register Value
* Return Value : none
*******************************************************************************/
void usb0_host_BRDYInterrupt (uint16_t Status, uint16_t Int_enbl)
{
    uint16_t          buffer;
    volatile uint16_t dumy_sts;

    if ((Status & g_usb0_host_bit_set[USB_HOST_PIPE0]) && (Int_enbl & g_usb0_host_bit_set[USB_HOST_PIPE0]))
    {
        USB200.BRDYSTS = (uint16_t)~g_usb0_host_bit_set[USB_HOST_PIPE0];

#if(1) /* ohci_wrapp */
        switch ((g_usb0_host_CmdStage & (USB_HOST_STAGE_FIELD | USB_HOST_CMD_FIELD)))
        {
            case (USB_HOST_STAGE_STATUS | USB_HOST_CMD_DOING):
                buffer  = usb0_host_read_buffer_c(USB_HOST_PIPE0);
                usb0_host_disable_brdy_int(USB_HOST_PIPE0);
                g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                g_usb0_host_CmdStage |= USB_HOST_CMD_DONE;
                ohciwrapp_loc_TransEnd(USB_HOST_PIPE0, TD_CC_NOERROR);
            break;

            case (USB_HOST_STAGE_DATA | USB_HOST_CMD_DOING):
                buffer  = usb0_host_read_buffer_c(USB_HOST_PIPE0);
                switch (buffer)
                {
                    case USB_HOST_READING:                  /* Continue of data read */
                    break;

                    case USB_HOST_READEND:                  /* End of data read */
                    case USB_HOST_READSHRT:                 /* End of data read */
                        usb0_host_disable_brdy_int(USB_HOST_PIPE0);
                        g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                        g_usb0_host_CmdStage |= USB_HOST_CMD_DONE;
                        ohciwrapp_loc_TransEnd(USB_HOST_PIPE0, TD_CC_NOERROR);
                    break;

                    case USB_HOST_READOVER:                 /* buffer over */
                        USB200.CFIFOCTR = USB_HOST_BITBCLR;
                        usb0_host_disable_brdy_int(USB_HOST_PIPE0);
                        g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                        g_usb0_host_CmdStage |= USB_HOST_CMD_DONE;
                        ohciwrapp_loc_TransEnd(USB_HOST_PIPE0, TD_CC_NOERROR);
                    break;

                    case USB_HOST_FIFOERROR:                    /* FIFO access error */
                    default:
                    break;
                }
            break;

            default:
            break;
        }
#else
        switch ((g_usb0_host_CmdStage & (USB_HOST_MODE_FIELD | USB_HOST_STAGE_FIELD | USB_HOST_CMD_FIELD)))
        {
            case (USB_HOST_MODE_WRITE   | USB_HOST_STAGE_STATUS | USB_HOST_CMD_DOING):
            case (USB_HOST_MODE_NO_DATA | USB_HOST_STAGE_STATUS | USB_HOST_CMD_DOING):
                buffer  = usb0_host_read_buffer_c(USB_HOST_PIPE0);
                usb0_host_disable_brdy_int(USB_HOST_PIPE0);
                g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                g_usb0_host_CmdStage |= USB_HOST_CMD_DONE;
            break;

            case (USB_HOST_MODE_READ   | USB_HOST_STAGE_DATA | USB_HOST_CMD_DOING):
                buffer  = usb0_host_read_buffer_c(USB_HOST_PIPE0);

                switch (buffer)
                {
                    case USB_HOST_READING:                  /* Continue of data read */
                    break;

                    case USB_HOST_READEND:                  /* End of data read */
                    case USB_HOST_READSHRT:                 /* End of data read */
                        usb0_host_disable_brdy_int(USB_HOST_PIPE0);
                        g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                        g_usb0_host_CmdStage |= USB_HOST_CMD_DONE;
                    break;

                    case USB_HOST_READOVER:                 /* buffer over */
                        USB200.CFIFOCTR = USB_HOST_BITBCLR;
                        usb0_host_disable_brdy_int(USB_HOST_PIPE0);
                        g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                        g_usb0_host_CmdStage |= USB_HOST_CMD_DONE;
                    break;

                    case USB_HOST_FIFOERROR:                    /* FIFO access error */
                    default:
                    break;
                }
            break;

            default:
            break;
        }
#endif
    }
    else
    {
        usb0_host_brdy_int(Status, Int_enbl);
    }

    /* Three dummy reads for clearing interrupt requests */
    dumy_sts = USB200.BRDYSTS;
}

/*******************************************************************************
* Function Name: usb0_host_NRDYInterrupt
* Description  : Executes USB NRDY interrupt.
* Arguments    : uint16_t Status        ; NRDYSTS Register Value
*              : uint16_t Int_enbl      ; NRDYENB Register Value
* Return Value : none
*******************************************************************************/
void usb0_host_NRDYInterrupt (uint16_t Status, uint16_t Int_enbl)
{
    uint16_t          pid;
    volatile uint16_t dumy_sts;

    if ((Status & g_usb0_host_bit_set[USB_HOST_PIPE0]) && (Int_enbl & g_usb0_host_bit_set[USB_HOST_PIPE0]))
    {
        USB200.NRDYSTS = (uint16_t)~g_usb0_host_bit_set[USB_HOST_PIPE0];
        pid = usb0_host_get_pid(USB_HOST_PIPE0);

        if ((pid == USB_HOST_PID_STALL) || (pid == USB_HOST_PID_STALL2))
        {
            g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
            g_usb0_host_CmdStage |= USB_HOST_CMD_STALL;
#if(1) /* ohci_wrapp */
            g_usb0_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_STALL;
            ohciwrapp_loc_TransEnd(USB_HOST_PIPE0, TD_CC_STALL);
#endif
        }
        else if (pid  == USB_HOST_PID_NAK)
        {
            g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
            g_usb0_host_CmdStage |= USB_HOST_CMD_NORES;
#if(1) /* ohci_wrapp */
            g_usb0_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_NORES;
            ohciwrapp_loc_TransEnd(USB_HOST_PIPE0, TD_CC_STALL);
#endif
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        usb0_host_nrdy_int(Status, Int_enbl);
    }

    /* Three dummy reads for clearing interrupt requests */
    dumy_sts = USB200.NRDYSTS;
}

/*******************************************************************************
* Function Name: usb0_host_BEMPInterrupt
* Description  : Executes USB BEMP interrupt.
* Arguments    : uint16_t Status        ; BEMPSTS Register Value
*              : uint16_t Int_enbl      ; BEMPENB Register Value
* Return Value : none
*******************************************************************************/
void usb0_host_BEMPInterrupt (uint16_t Status, uint16_t Int_enbl)
{
    uint16_t          buffer;
    uint16_t          pid;
    volatile uint16_t dumy_sts;

    if ((Status & g_usb0_host_bit_set[USB_HOST_PIPE0]) && (Int_enbl & g_usb0_host_bit_set[USB_HOST_PIPE0]))
    {
        USB200.BEMPSTS = (uint16_t)~g_usb0_host_bit_set[USB_HOST_PIPE0];
        pid = usb0_host_get_pid(USB_HOST_PIPE0);

        if ((pid == USB_HOST_PID_STALL) || (pid == USB_HOST_PID_STALL2))
        {
            g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
            g_usb0_host_CmdStage |= USB_HOST_CMD_STALL;
#if(1) /* ohci_wrapp */
            g_usb0_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_STALL;      /* exit STALL */
            ohciwrapp_loc_TransEnd(USB_HOST_PIPE0, TD_CC_STALL);
#endif
        }
        else
        {
#if(1) /* ohci_wrapp */
            switch ((g_usb0_host_CmdStage & (USB_HOST_STAGE_FIELD | USB_HOST_CMD_FIELD)))
            {
                case (USB_HOST_STAGE_STATUS | USB_HOST_CMD_DOING):
                    g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                    g_usb0_host_CmdStage |= USB_HOST_CMD_DONE;
                    ohciwrapp_loc_TransEnd(USB_HOST_PIPE0, TD_CC_NOERROR);
                break;

                case (USB_HOST_STAGE_DATA | USB_HOST_CMD_DOING):
                    buffer  = usb0_host_write_buffer(USB_HOST_PIPE0);
                    switch (buffer)
                    {
                        case USB_HOST_WRITING:                  /* Continue of data write */
                        case USB_HOST_WRITEEND:                 /* End of data write (zero-length) */
                        break;

                        case USB_HOST_WRITESHRT:                    /* End of data write */
                            g_usb0_host_CmdStage &= (~USB_HOST_STAGE_FIELD);
                            g_usb0_host_CmdStage |= USB_HOST_STAGE_STATUS;
                            ohciwrapp_loc_TransEnd(USB_HOST_PIPE0, TD_CC_NOERROR);
                        break;

                        case USB_HOST_FIFOERROR:                    /* FIFO access error */
                        default:
                        break;
                    }
                break;

                default:
                    /* do nothing */
                break;
            }
#else
            switch ((g_usb0_host_CmdStage & (USB_HOST_MODE_FIELD | USB_HOST_STAGE_FIELD | USB_HOST_CMD_FIELD)))
            {
                case (USB_HOST_MODE_READ | USB_HOST_STAGE_STATUS | USB_HOST_CMD_DOING):
                    g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                    g_usb0_host_CmdStage |= USB_HOST_CMD_DONE;
                break;

                case (USB_HOST_MODE_WRITE | USB_HOST_STAGE_DATA | USB_HOST_CMD_DOING):
                    buffer  = usb0_host_write_buffer(USB_HOST_PIPE0);
                    switch (buffer)
                    {
                        case USB_HOST_WRITING:                  /* Continue of data write */
                        case USB_HOST_WRITEEND:                 /* End of data write (zero-length) */
                        break;

                        case USB_HOST_WRITESHRT:                    /* End of data write */
                            g_usb0_host_CmdStage &= (~USB_HOST_STAGE_FIELD);
                            g_usb0_host_CmdStage |= USB_HOST_STAGE_STATUS;
                        break;

                        case USB_HOST_FIFOERROR:                    /* FIFO access error */
                        default:
                        break;
                    }
                break;

                case (USB_HOST_MODE_WRITE | USB_HOST_STAGE_STATUS | USB_HOST_CMD_DOING):
                    g_usb0_host_CmdStage &= (~USB_HOST_CMD_FIELD);
                    g_usb0_host_CmdStage |= USB_HOST_CMD_IDLE;
                break;

                default:
                    /* do nothing */
                break;
            }
#endif
        }
    }
    else
    {
        usb0_host_bemp_int(Status, Int_enbl);
    }

    /* Three dummy reads for clearing interrupt requests */
    dumy_sts = USB200.BEMPSTS;
}

/* End of File */
