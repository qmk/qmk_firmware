/* Copyright (c) 2010-2011 mbed.org, MIT License
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following
* conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the
* Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
* KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#if defined(TARGET_RZ_A1H)

/*
  This class can use the pipe1, pipe3 and pipe6 only. You should
  re-program this class if you wanted to use other pipe.
 */

/*************************************************************************/
extern "C"
{
#include "r_typedefs.h"
#include "iodefine.h"
}
#include "USBHAL.h"
#include "devdrv_usb_function_api.h"
#include "usb_iobitmask.h"
#include "rza_io_regrw.h"
#include "USBDevice_Types.h"
#include "usb_function_setting.h"


/*************************************************************************/
/* constants */
const struct PIPECFGREC {
    uint16_t    endpoint;
    uint16_t    pipesel;
    uint16_t    pipecfg;
    uint16_t    pipebuf;
    uint16_t    pipemaxp;
    uint16_t    pipeperi;
} def_pipecfg[] = {
    /*EP0OUT and EP0IN are configured by USB IP*/
    {
        EP1OUT, /*EP1: Host -> Func, INT*/
        6 | USB_FUNCTION_D0FIFO_USE,
        USB_FUNCTION_INTERRUPT |
        USB_FUNCTION_BFREOFF   |
        USB_FUNCTION_DBLBOFF   |
        USB_FUNCTION_CNTMDON   |
        USB_FUNCTION_SHTNAKOFF |
        USB_FUNCTION_DIR_P_OUT |
        USB_FUNCTION_EP1,
        ( ( (  64) / 64 - 1 ) << 10 ) | 0x04u,
        MAX_PACKET_SIZE_EP1,
        DEVDRV_USBF_OFF |
        ( 3 << USB_PIPEPERI_IITV_SHIFT ),
    },
    {
        EP1IN,  /*EP1: Host <- Func, INT*/
        7 | USB_FUNCTION_D1FIFO_USE,
        USB_FUNCTION_INTERRUPT |
        USB_FUNCTION_BFREOFF   |
        USB_FUNCTION_DBLBOFF   |
        USB_FUNCTION_CNTMDOFF  |
        USB_FUNCTION_SHTNAKOFF |
        USB_FUNCTION_DIR_P_IN  |
        USB_FUNCTION_EP1,
        ( ( (  64) / 64 - 1 ) << 10 ) | 0x05u,
        MAX_PACKET_SIZE_EP1,
        DEVDRV_USBF_OFF |
        ( 3 << USB_PIPEPERI_IITV_SHIFT ),
    },
    {
        EP2OUT, /*EP2: Host -> Func, BULK*/
        3 | USB_FUNCTION_D0FIFO_USE,
        USB_FUNCTION_BULK      |
        USB_FUNCTION_BFREOFF   |
        USB_FUNCTION_DBLBON    |
        USB_FUNCTION_CNTMDON   |
        USB_FUNCTION_SHTNAKON  |
        USB_FUNCTION_DIR_P_OUT |
        USB_FUNCTION_EP2,
        ( ( (2048) / 64 - 1 ) << 10 ) | 0x30u,
        MAX_PACKET_SIZE_EP2,
        DEVDRV_USBF_OFF |
        ( 0 << USB_PIPEPERI_IITV_SHIFT ),
    },
    {
        EP2IN,  /*EP2: Host <- Func, BULK*/
        4 | USB_FUNCTION_D1FIFO_USE,
        USB_FUNCTION_BULK      |
        USB_FUNCTION_BFREOFF   |
        USB_FUNCTION_DBLBOFF   |
        USB_FUNCTION_CNTMDON   |
        USB_FUNCTION_SHTNAKOFF |
        USB_FUNCTION_DIR_P_IN  |
        USB_FUNCTION_EP2,
        ( ( (2048) / 64 - 1 ) << 10 ) | 0x50u,
        MAX_PACKET_SIZE_EP2,
        DEVDRV_USBF_OFF |
        ( 0 << USB_PIPEPERI_IITV_SHIFT ),
    },
    {
        EP3OUT, /*EP3: Host -> Func, ISO*/
        1 | USB_FUNCTION_D0FIFO_USE,
        USB_FUNCTION_ISO       |
        USB_FUNCTION_BFREOFF   |
        USB_FUNCTION_DBLBON    |
        USB_FUNCTION_CNTMDOFF  |
        USB_FUNCTION_SHTNAKON  |
        USB_FUNCTION_DIR_P_OUT |
        USB_FUNCTION_EP3,
        ( ( ( 512) / 64 - 1 ) << 10 ) | 0x10u,
        MAX_PACKET_SIZE_EP3,
        DEVDRV_USBF_OFF |
        ( 0 << USB_PIPEPERI_IITV_SHIFT ),
    },
    {
        EP3IN,  /*EP3: Host <- Func, ISO*/
        2 | USB_FUNCTION_D1FIFO_USE,
        USB_FUNCTION_ISO       |
        USB_FUNCTION_BFREOFF   |
        USB_FUNCTION_DBLBON    |
        USB_FUNCTION_CNTMDOFF  |
        USB_FUNCTION_SHTNAKOFF |
        USB_FUNCTION_DIR_P_IN  |
        USB_FUNCTION_EP3,
        ( ( ( 512) / 64 - 1 ) << 10 ) | 0x20u,
        MAX_PACKET_SIZE_EP3,
        DEVDRV_USBF_OFF |
        ( 0 << USB_PIPEPERI_IITV_SHIFT ),
    },
    { /*terminator*/
        0, 0, 0, 0, 0,
    },
};


/*************************************************************************/
/* workareas */
USBHAL * USBHAL::instance;

static IRQn_Type    int_id;         /* interrupt ID          */
static uint16_t     int_level;      /* initerrupt level      */
static uint16_t     clock_mode;     /* input clock selector  */
static uint16_t     mode;           /* USB speed (HIGH/FULL) */

//static DigitalOut *usbx_en;

static uint16_t     EP0_read_status;
static uint16_t     EPx_read_status;

static uint16_t setup_buffer[MAX_PACKET_SIZE_EP0 / 2];

/* 0: not used / other: a pipe number to use recv_buffer*/
static uint8_t  recv_buffer[MAX_PACKET_SIZE_EPBULK];
volatile static uint16_t    recv_error;


/*************************************************************************/
/* prototypes for C */
extern "C" {
    void usbx_function_BRDYInterruptPIPE0 (uint16_t status, uint16_t intenb,
        USBHAL *object, void (USBHAL::*EP0func)(void));

    void usbx_function_BRDYInterrupt (uint16_t status, uint16_t intenb,
        USBHAL *object, bool (USBHAL::*epCallback[])(void));

    void usbx_function_NRDYInterruptPIPE0(uint16_t status, uint16_t intenb,
        USBHAL *object, void (USBHAL::*EP0func)(void));

    void usbx_function_NRDYInterrupt (uint16_t status, uint16_t intenb,
        USBHAL *object, bool (USBHAL::*epCallback[])(void));

    void usbx_function_BEMPInterruptPIPE0(uint16_t status, uint16_t intenb,
        USBHAL *object, void (USBHAL::*EP0func)(void));

    void usbx_function_BEMPInterrupt (uint16_t status, uint16_t intenb,
        USBHAL *object, bool (USBHAL::*epCallback[])(void));
}


/*************************************************************************/
/* macros */

/******************************************************************************
 * Function Name: usbx_function_BRDYInterruptPIPE0
 * Description  : Executes BRDY interrupt for pipe0.
 * Arguments    : uint16_t status       ; BRDYSTS Register Value
 *              : uint16_t intenb       ; BRDYENB Register Value
 * Return Value : none
 *****************************************************************************/
extern "C" {
    void usbx_function_BRDYInterruptPIPE0 (
        uint16_t status,
        uint16_t intenb,
        USBHAL *object,
        void (USBHAL::*EP0func)(void)
    )
    {
        volatile uint16_t dumy_sts;
        uint16_t read_status;

        USB20X.BRDYSTS =
            (uint16_t)~g_usbx_function_bit_set[USB_FUNCTION_PIPE0];
        RZA_IO_RegWrite_16(
            &USB20X.CFIFOSEL, USB_FUNCTION_PIPE0,
            USB_CFIFOSEL_CURPIPE_SHIFT, USB_CFIFOSEL_CURPIPE);

        g_usbx_function_PipeDataSize[USB_FUNCTION_PIPE0] =
            g_usbx_function_data_count[USB_FUNCTION_PIPE0];

        read_status = usbx_function_read_buffer_c(USB_FUNCTION_PIPE0);

        g_usbx_function_PipeDataSize[USB_FUNCTION_PIPE0] -=
            g_usbx_function_data_count[USB_FUNCTION_PIPE0];

        switch (read_status) {
            case USB_FUNCTION_READING:      /* Continue of data read */
            case USB_FUNCTION_READEND:      /* End of data read */
                /* PID = BUF */
                usbx_function_set_pid_buf(USB_FUNCTION_PIPE0);

                /*callback*/
                (object->*EP0func)();
                break;

            case USB_FUNCTION_READSHRT:     /* End of data read */
                usbx_function_disable_brdy_int(USB_FUNCTION_PIPE0);
                /* PID = BUF */
                usbx_function_set_pid_buf(USB_FUNCTION_PIPE0);

                /*callback*/
                (object->*EP0func)();
                break;

            case USB_FUNCTION_READOVER:     /* FIFO access error */
                /* Buffer Clear */
                USB20X.CFIFOCTR = USB_FUNCTION_BITBCLR;
                usbx_function_disable_brdy_int(USB_FUNCTION_PIPE0);
                /* Req Error */
                usbx_function_set_pid_stall(USB_FUNCTION_PIPE0);

                /*callback*/
                (object->*EP0func)();
                break;

            case DEVDRV_USBF_FIFOERROR:     /* FIFO access error */
            default:
                usbx_function_disable_brdy_int(USB_FUNCTION_PIPE0);
                /* Req Error */
                usbx_function_set_pid_stall(USB_FUNCTION_PIPE0);
                break;
        }
        /* Three dummy reads for clearing interrupt requests */
        dumy_sts = USB20X.BRDYSTS;
    }
}


/******************************************************************************
 * Function Name: usbx_function_BRDYInterrupt
 * Description  : Executes BRDY interrupt uxclude pipe0.
 * Arguments    : uint16_t status       ; BRDYSTS Register Value
 *              : uint16_t intenb       ; BRDYENB Register Value
 * Return Value : none
 *****************************************************************************/
extern "C" {
    void usbx_function_BRDYInterrupt(
        uint16_t status,
        uint16_t intenb,
        USBHAL *object,
        bool (USBHAL::*epCallback[])(void)
    )
    {
        volatile uint16_t dumy_sts;

        /**************************************************************
         * Function Name: usbx_function_brdy_int
         * Description  : Executes BRDY interrupt(USB_FUNCTION_PIPE1-9).
         *              : According to the pipe that interrupt is generated in,
         *              : reads/writes buffer allocated in the pipe.
         *              : This function is executed in the BRDY
         *              : interrupt handler.  This function
         *              : clears BRDY interrupt status and BEMP
         *              : interrupt status.
         * Arguments    : uint16_t Status    ; BRDYSTS Register Value
         *              : uint16_t Int_enbl  ; BRDYENB Register Value
         * Return Value : none
         *************************************************************/
        /* copied from usbx_function_intrn.c */
        uint32_t int_sense = 0;
        uint16_t pipe;
        uint16_t pipebit;
        uint16_t ep;

        for (pipe = USB_FUNCTION_PIPE1; pipe <= USB_FUNCTION_MAX_PIPE_NO; pipe++) {
            pipebit = g_usbx_function_bit_set[pipe];

            if ((status & pipebit) && (intenb & pipebit)) {
                USB20X.BRDYSTS = (uint16_t)~pipebit;
                USB20X.BEMPSTS = (uint16_t)~pipebit;

                switch (g_usbx_function_PipeTbl[pipe] & USB_FUNCTION_FIFO_USE) {
                    case USB_FUNCTION_D0FIFO_DMA:
                        if (g_usbx_function_DmaStatus[USB_FUNCTION_D0FIFO] != USB_FUNCTION_DMA_READY) {
                            /*now, DMA is not supported*/
                            usbx_function_dma_interrupt_d0fifo(int_sense);
                        }

                        if (RZA_IO_RegRead_16(
                                &g_usbx_function_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 0) {
                            /*now, DMA is not supported*/
                            usbx_function_read_dma(pipe);
                            usbx_function_disable_brdy_int(pipe);
                        } else {
                            USB20X.D0FIFOCTR = USB_FUNCTION_BITBCLR;
                            g_usbx_function_pipe_status[pipe] = DEVDRV_USBF_PIPE_DONE;
                        }
                        break;

                    case USB_FUNCTION_D1FIFO_DMA:
                        if (g_usbx_function_DmaStatus[USB_FUNCTION_D1FIFO] != USB_FUNCTION_DMA_READY) {
                            /*now, DMA is not supported*/
                            usbx_function_dma_interrupt_d1fifo(int_sense);
                        }

                        if (RZA_IO_RegRead_16(
                                &g_usbx_function_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 0) {
                            /*now, DMA is not supported*/
                            usbx_function_read_dma(pipe);
                            usbx_function_disable_brdy_int(pipe);
                        } else {
                            USB20X.D1FIFOCTR = USB_FUNCTION_BITBCLR;
                            g_usbx_function_pipe_status[pipe] = DEVDRV_USBF_PIPE_DONE;
                        }
                        break;

                    default:
                        ep = (g_usbx_function_pipecfg[pipe] & USB_PIPECFG_EPNUM) >> USB_PIPECFG_EPNUM_SHIFT;
                        ep <<= 1;
                        if (RZA_IO_RegRead_16(
                                &g_usbx_function_pipecfg[pipe], USB_PIPECFG_DIR_SHIFT, USB_PIPECFG_DIR) == 0) {
                            /* read */
                            EPx_read_status = DEVDRV_USBF_PIPE_WAIT;
                            (object->*(epCallback[ep - 2])) ();
                            EPx_read_status = DEVDRV_USBF_PIPE_DONE;
                        } else {
                            /* write */
                            EPx_read_status = DEVDRV_USBF_PIPE_WAIT;
                            (object->*(epCallback[ep - 2 + 1])) ();
                            EPx_read_status = DEVDRV_USBF_PIPE_DONE;
                            usbx_function_write_buffer(pipe);
                        }
                }
            }
        }
        /* Three dummy reads for clearing interrupt requests */
        dumy_sts = USB20X.BRDYSTS;
    }
}


/******************************************************************************
 * Function Name: usbx_function_NRDYInterruptPIPE0
 * Description  : Executes NRDY interrupt for pipe0.
 * Arguments    : uint16_t status       ; NRDYSTS Register Value
 *              : uint16_t intenb       ; NRDYENB Register Value
 * Return Value : none
 *****************************************************************************/
extern "C" {
    void usbx_function_NRDYInterruptPIPE0(
        uint16_t status,
        uint16_t intenb,
        USBHAL *object,
        void (USBHAL::*EP0func)(void)
    )
    {
        volatile uint16_t dumy_sts;

        USB20X.NRDYSTS =
            (uint16_t)~g_usbx_function_bit_set[USB_FUNCTION_PIPE0];

        /* Three dummy reads for clearing interrupt requests */
        dumy_sts = USB20X.NRDYSTS;
    }
}


/******************************************************************************
 * Function Name: usbx_function_NRDYInterrupt
 * Description  : Executes NRDY interrupt exclude pipe0.
 * Arguments    : uint16_t status       ; NRDYSTS Register Value
 *              : uint16_t intenb       ; NRDYENB Register Value
 * Return Value : none
 *****************************************************************************/
extern "C" {
    void usbx_function_NRDYInterrupt(
        uint16_t status,
        uint16_t intenb,
        USBHAL *object,
        bool (USBHAL::*epCallback[])(void)
    )
    {
        volatile uint16_t dumy_sts;

        /**************************************************************
         * Function Name: usbx_function_nrdy_int
         * Description  : Executes NRDY interrupt(USB_FUNCTION_PIPE1-9).
         *              : Checks NRDY interrupt cause by PID. When the cause if STALL,
         *              : regards the pipe state as STALL and ends the processing.
         *              : Then the cause is not STALL, increments the error count to
         *              : communicate again. When the error count is 3, determines
         *              : the pipe state as DEVDRV_USBF_PIPE_NORES and ends the processing.
         *              : This function is executed in the NRDY interrupt handler.
         *              : This function clears NRDY interrupt status.
         * Arguments    : uint16_t status       ; NRDYSTS Register Value
         *              : uint16_t int_enb      ; NRDYENB Register Value
         * Return Value : none
         *************************************************************/
        /* copied from usbx_function_intrn.c */
#if 0
        uint16_t usefifo;
#endif
        uint16_t pid;
        uint16_t pipe;
        uint16_t bitcheck;
#if 0
        uint16_t mbw;
        uint32_t size;
#endif
        uint16_t ep;

        bitcheck = (uint16_t)(status & intenb);

        USB20X.NRDYSTS = (uint16_t)~status;


        if (RZA_IO_RegRead_16(&USB20X.SYSCFG0, USB_SYSCFG_DCFM_SHIFT, USB_SYSCFG_DCFM) == 1) {
            /* USB HOST */
            /* not support */

        } else {
            /* USB Function */
            for (pipe = USB_FUNCTION_PIPE1; pipe <= USB_FUNCTION_MAX_PIPE_NO; pipe++) {
                if ((bitcheck&g_usbx_function_bit_set[pipe]) != g_usbx_function_bit_set[pipe]) {
                    continue;
                }

                if (g_usbx_function_pipe_status[pipe] != DEVDRV_USBF_PIPE_WAIT) {
                    continue;
                }

#if 0
                usbx_function_set_pid_nak(pipe);

                size = (uint32_t)g_usbx_function_data_count[pipe];
                mbw = usbx_function_get_mbw(
                    size, (uint32_t)g_usbx_function_data_pointer[pipe]);

                usefifo = (uint16_t)(g_usbx_function_PipeTbl[pipe] & USB_FUNCTION_FIFO_USE);
                switch (usefifo) {

                    case USB_FUNCTION_D0FIFO_USE:
                        usbx_function_set_curpipe(
                            pipe, USB_FUNCTION_D0USE, DEVDRV_USBF_NO, mbw);
                        USB20X.D0FIFOCTR = USB_FUNCTION_BITBCLR;
                        break;

                    case USB_FUNCTION_D1FIFO_USE:
                        usbx_function_set_curpipe(
                            pipe, USB_FUNCTION_D1USE, DEVDRV_USBF_NO, mbw);
                        USB20X.D1FIFOCTR = USB_FUNCTION_BITBCLR;
                        break;

                    default:
                        usbx_function_set_curpipe(
                            pipe, USB_FUNCTION_CUSE, USB_FUNCTION_CFIFO_READ, mbw);
                        USB20X.CFIFOCTR = USB_FUNCTION_BITBCLR;
                        break;
                }

                usbx_function_aclrm(pipe);

                usbx_function_enable_nrdy_int(pipe);
                usbx_function_enable_brdy_int(pipe);

                usbx_function_set_pid_buf(pipe);
#endif

                pid = usbx_function_get_pid(pipe);
                if ((pid == DEVDRV_USBF_PID_STALL) || (pid == DEVDRV_USBF_PID_STALL2)) {
                    g_usbx_function_pipe_status[pipe] = DEVDRV_USBF_PIPE_STALL;
                } else {
                    usbx_function_set_pid_buf(pipe);
                }

                ep = (g_usbx_function_pipecfg[pipe] & USB_PIPECFG_EPNUM) >> USB_PIPECFG_EPNUM_SHIFT;
                ep <<= 1;
                if (RZA_IO_RegRead_16(
                        &g_usbx_function_pipecfg[pipe], USB_PIPECFG_DIR_SHIFT, USB_PIPECFG_DIR) == 0) {
                    /* read */
                    __NOP();
                } else {
                    /* write */
                    __NOP();
                }
            }
        }

        /* Three dummy reads for clearing interrupt requests */
        dumy_sts = USB20X.NRDYSTS;
    }
}

/******************************************************************************
 * Function Name: usbx_function_BEMPInterruptPIPE0
 * Description  : Executes BEMP interrupt for pipe0.
 * Arguments    : uint16_t status       ; BEMPSTS Register Value
 *              : uint16_t intenb       ; BEMPENB Register Value
 * Return Value : none
 *****************************************************************************/
extern "C" {
    void usbx_function_BEMPInterruptPIPE0(
        uint16_t status,
        uint16_t intenb,
        USBHAL *object,
        void (USBHAL::*EP0func)(void)
    )
    {
        volatile uint16_t dumy_sts;

        USB20X.BEMPSTS =
            (uint16_t)~g_usbx_function_bit_set[USB_FUNCTION_PIPE0];
        RZA_IO_RegWrite_16(
            &USB20X.CFIFOSEL, USB_FUNCTION_PIPE0,
            USB_CFIFOSEL_CURPIPE_SHIFT, USB_CFIFOSEL_CURPIPE);

        /*usbx_function_write_buffer_c(USB_FUNCTION_PIPE0);*/
        (object->*EP0func)();

        /* Three dummy reads for clearing interrupt requests */
        dumy_sts = USB20X.BEMPSTS;
    }
}


/******************************************************************************
 * Function Name: usbx_function_BEMPInterrupt
 * Description  : Executes BEMP interrupt exclude pipe0.
 * Arguments    : uint16_t status       ; BEMPSTS Register Value
 *              : uint16_t intenb       ; BEMPENB Register Value
 * Return Value : none
 *****************************************************************************/
extern "C" {
    void usbx_function_BEMPInterrupt(
        uint16_t status,
        uint16_t intenb,
        USBHAL *object,
        bool (USBHAL::*epCallback[])(void)
    )
    {
        volatile uint16_t dumy_sts;

        /**************************************************************
         * Function Name: usbx_function_bemp_int
         * Description  : Executes BEMP interrupt(USB_FUNCTION_PIPE1-9).
         * Arguments    : uint16_t status       ; BEMPSTS Register Value
         *              : uint16_t intenb      ; BEMPENB Register Value
         * Return Value : none
         *************************************************************/
        /* copied from usbx_function_intrn.c */
        uint16_t pid;
        uint16_t pipe;
        uint16_t bitcheck;
        uint16_t inbuf;
        uint16_t ep;

        bitcheck = (uint16_t)(status & intenb);

        USB20X.BEMPSTS = (uint16_t)~status;

        for (pipe = USB_FUNCTION_PIPE1; pipe <= USB_FUNCTION_MAX_PIPE_NO; pipe++) {
            if ((bitcheck&g_usbx_function_bit_set[pipe]) != g_usbx_function_bit_set[pipe]) {
                continue;
            }

            pid = usbx_function_get_pid(pipe);

            if ((pid == DEVDRV_USBF_PID_STALL) ||
                (pid == DEVDRV_USBF_PID_STALL2)) {
                g_usbx_function_pipe_status[pipe] = DEVDRV_USBF_PIPE_STALL;

            } else {
                inbuf = usbx_function_get_inbuf(pipe);

                if (inbuf == 0) {
                    usbx_function_disable_bemp_int(pipe);
                    usbx_function_set_pid_nak(pipe);
                    g_usbx_function_pipe_status[pipe] = DEVDRV_USBF_PIPE_DONE;

                    switch (g_usbx_function_PipeTbl[pipe] & USB_FUNCTION_FIFO_USE) {
                        case USB_FUNCTION_D0FIFO_DMA:
                            /*now, DMA is not supported*/
                            break;

                        case USB_FUNCTION_D1FIFO_DMA:
                            /*now, DMA is not supported*/
                            break;

                        default:
                            ep = (g_usbx_function_pipecfg[pipe] & USB_PIPECFG_EPNUM) >> USB_PIPECFG_EPNUM_SHIFT;
                            ep <<= 1;
                            if (RZA_IO_RegRead_16(
                                    &g_usbx_function_pipecfg[pipe], USB_PIPECFG_DIR_SHIFT, USB_PIPECFG_DIR) == 0) {
                                /* read */
                                __NOP();
                            } else {
                                /* write */
                                EPx_read_status = DEVDRV_USBF_PIPE_WAIT;
                                (object->*(epCallback[ep - 2 + 1])) ();
                                EPx_read_status = DEVDRV_USBF_PIPE_DONE;
                            }
                    }
                }
            }
        }

        /* Three dummy reads for clearing interrupt requests */
        dumy_sts = USB20X.BEMPSTS;
    }
}

/******************************************************************************
 * Function Name: EP2PIPE
 * Description  : Converts from endpoint to pipe
 * Arguments    : number of endpoint
 * Return Value : number of pipe
 *****************************************************************************/
/*EP2PIPE converter is for pipe1, pipe3 and pipe6 only.*/
#define EP2PIPE(endpoint)   ((uint32_t)usbx_function_EpToPipe(endpoint))


/******************************************************************************
 * Function Name: usbx_function_save_request
 * Description  : Retains the USB request information in variables.
 * Arguments    : none
 * Return Value : none
 *****************************************************************************/
#define  usbx_function_save_request()                       \
    {                                                       \
        uint16_t *bufO = &setup_buffer[0];                  \
                                                            \
        USB20X.INTSTS0 = (uint16_t)~USB_FUNCTION_BITVALID;  \
        /*data[0] <= bmRequest, data[1] <= bmRequestType */ \
        *bufO++ = USB20X.USBREQ;                            \
        /*data[2] data[3] <= wValue*/                       \
        *bufO++ = USB20X.USBVAL;                            \
        /*data[4] data[5] <= wIndex*/                       \
        *bufO++ = USB20X.USBINDX;                           \
        /*data[6] data[6] <= wIndex*/                       \
        *bufO++ = USB20X.USBLENG;                           \
    }


/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

/*************************************************************************/
/* constructor */
USBHAL::USBHAL(void)
{
    /* ---- P4_1 : P4_1 (USB0_EN for GR-PEACH) ---- */
    //usbx_en = new DigitalOut(P4_1, 1);

    /* some constants */
    int_id          = USBIX_IRQn;
    int_level       = ( 2 << 3 );
    clock_mode      = USBFCLOCK_X1_48MHZ;
#if (USB_FUNCTION_HISPEED == 0)
    mode            = USB_FUNCTION_FULL_SPEED;
#else
    mode            = USB_FUNCTION_HIGH_SPEED;
#endif
    EP0_read_status = DEVDRV_USBF_WRITEEND;
    EPx_read_status = DEVDRV_USBF_PIPE_DONE;

    /* Disables interrupt for usb */
    GIC_DisableIRQ(int_id);

    /* Setup the end point */
    epCallback[ 0] = &USBHAL::EP1_OUT_callback;
    epCallback[ 1] = &USBHAL::EP1_IN_callback;
    epCallback[ 2] = &USBHAL::EP2_OUT_callback;
    epCallback[ 3] = &USBHAL::EP2_IN_callback;
    epCallback[ 4] = &USBHAL::EP3_OUT_callback;
    epCallback[ 5] = &USBHAL::EP3_IN_callback;
    epCallback[ 6] = &USBHAL::EP4_OUT_callback;
    epCallback[ 7] = &USBHAL::EP4_IN_callback;
    epCallback[ 8] = &USBHAL::EP5_OUT_callback;
    epCallback[ 9] = &USBHAL::EP5_IN_callback;
    epCallback[10] = &USBHAL::EP6_OUT_callback;
    epCallback[11] = &USBHAL::EP6_IN_callback;
    epCallback[12] = &USBHAL::EP7_OUT_callback;
    epCallback[13] = &USBHAL::EP7_IN_callback;
    epCallback[14] = &USBHAL::EP8_OUT_callback;
    epCallback[15] = &USBHAL::EP8_IN_callback;
    epCallback[16] = &USBHAL::EP9_OUT_callback;
    epCallback[17] = &USBHAL::EP9_IN_callback;
    epCallback[18] = &USBHAL::EP10_OUT_callback;
    epCallback[19] = &USBHAL::EP10_IN_callback;
    epCallback[20] = &USBHAL::EP11_OUT_callback;
    epCallback[21] = &USBHAL::EP11_IN_callback;
    epCallback[22] = &USBHAL::EP12_OUT_callback;
    epCallback[23] = &USBHAL::EP12_IN_callback;
    epCallback[24] = &USBHAL::EP13_OUT_callback;
    epCallback[25] = &USBHAL::EP13_IN_callback;
    epCallback[26] = &USBHAL::EP14_OUT_callback;
    epCallback[27] = &USBHAL::EP14_IN_callback;
    epCallback[28] = &USBHAL::EP15_OUT_callback;
    epCallback[29] = &USBHAL::EP15_IN_callback;

    /* registers me */
    instance = this;

    /* Clear pipe table */
    usbx_function_clear_pipe_tbl();

/******************************************************************************
 * Function Name: usbx_api_function_init
 * Description  : Initializes the USB module in the USB function mode.
 *****************************************************************************/
    /* The clock of USB0 modules is permitted */
#if (USB_FUNCTION_CH == 0)
    CPG.STBCR7 &= ~(CPG_STBCR7_MSTP71);
#else
    CPG.STBCR7 &= ~(CPG_STBCR7_MSTP71 | CPG_STBCR7_MSTP70);
#endif
    volatile uint8_t    dummy8;
    dummy8 = CPG.STBCR7;

    {
/******************************************************************************
 * Function Name: usbx_function_setting_interrupt
 * Description  : Sets the USB module interrupt level.
 *****************************************************************************/
#if 0   /*DMA is not supported*/
        IRQn_Type d0fifo_dmaintid;
        IRQn_Type d1fifo_dmaintid;
#endif

        InterruptHandlerRegister(int_id, &_usbisr);
        GIC_SetPriority(int_id, int_level);
        GIC_EnableIRQ(int_id);

#if 0   /*DMA is not supported*/
        d0fifo_dmaintid = Userdef_USB_usbx_function_d0fifo_dmaintid();
        if (d0fifo_dmaintid != 0xFFFF) {
            InterruptHandlerRegister(d0fifo_dmaintid, usbx_function_dma_interrupt_d0fifo);
            GIC_SetPriority(d0fifo_dmaintid, int_level);
            GIC_EnableIRQ(d0fifo_dmaintid);
        }
#endif

#if 0   /*DMA is not supported*/
        d1fifo_dmaintid = Userdef_USB_usbx_function_d1fifo_dmaintid();
        if (d1fifo_dmaintid != 0xFFFF) {
            InterruptHandlerRegister(d1fifo_dmaintid, usbx_function_dma_interrupt_d1fifo);
            GIC_SetPriority(d1fifo_dmaintid, int_level);
            GIC_EnableIRQ(d1fifo_dmaintid);
        }
#endif
/*****************************************************************************/
    }

    /* reset USB module with setting tranciever and HSE=1 */
    usbx_function_reset_module(clock_mode);

    /* clear variables */
    usbx_function_init_status();

    /* select USB Function and Interrupt Enable */
    /* Detect USB Device to attach or detach    */
    usbx_function_InitModule(mode);

    {
        uint16_t buf;
        buf  = USB20X.INTENB0;
        buf |= USB_INTENB0_SOFE;
        USB20X.INTENB0 = buf;
    }
}

/*************************************************************************/
USBHAL::~USBHAL(void)
{
    /* Disables interrupt for usb */
    GIC_DisableIRQ( int_id );
    /* Unregisters interrupt function and priority */
    InterruptHandlerRegister( int_id, (uint32_t)NULL );

    //usbx_en  = NULL;
    instance = NULL;
}

/*************************************************************************/
void USBHAL::connect(void)
{
    /* Activates USB0_EN */
    //(*usbx_en) = 0;
}


/*************************************************************************/
void USBHAL::disconnect(void)
{
    /* Deactivates USB0_EN */
    //(*usbx_en) = 1;
}


/*************************************************************************/
void USBHAL::configureDevice(void)
{
    /*The pipes set up in USBHAL::realiseEndpoint*/
    /*usbx_function_clear_alt();*/      /* Alternate setting clear */
    /*usbx_function_set_pid_buf(USB_FUNCTION_PIPE0);*/
}


/*************************************************************************/
void USBHAL::unconfigureDevice(void)
{
    /* The Interface would be managed by USBDevice */
    /*usbx_function_clear_alt();*/      /* Alternate setting clear */
    /*usbx_function_set_pid_buf(USB_FUNCTION_PIPE0);*/
}


/*************************************************************************/
void USBHAL::setAddress(uint8_t address)
{
    if (address <= 127) {
        usbx_function_set_pid_buf(USB_FUNCTION_PIPE0);      /* OK */
    } else {
        usbx_function_set_pid_stall(USB_FUNCTION_PIPE0);    /* Not Spec */
    }
}


/*************************************************************************/
bool USBHAL::realiseEndpoint(uint8_t endpoint, uint32_t maxPacket, uint32_t flags)
{
    const struct PIPECFGREC *cfg;
    uint16_t pipe;
    uint16_t buf;

    if ( (EP0OUT == endpoint) || (EP0IN  == endpoint) ) {
        return true;
    }

    for (cfg = &def_pipecfg[0]; cfg->pipesel != 0; cfg++) {
        if (cfg->endpoint == endpoint) {
            break;
        }
    }
    if (cfg->pipesel == 0) {
        return false;
    }

    pipe = ((cfg->pipesel & USB_PIPESEL_PIPESEL) >> USB_PIPESEL_PIPESEL_SHIFT);

    g_usbx_function_PipeTbl[ pipe ] = (uint16_t)(endpoint | ((cfg->pipesel & USB_FUNCTION_FIFO_USE) << 0));

    /* There are maintenance routine of SHTNAK and BFRE bits
     * in original sample program. This sample is not
     * programmed. Do maintenance the "def_pipecfg" array if
     * you want it. */

    /* Interrupt Disable */
    buf  = USB20X.BRDYENB;
    buf &= (uint16_t)~g_usbx_function_bit_set[pipe];
    USB20X.BRDYENB = buf;
    buf  = USB20X.NRDYENB;
    buf &= (uint16_t)~g_usbx_function_bit_set[pipe];
    USB20X.NRDYENB = buf;
    buf  = USB20X.BEMPENB;
    buf &= (uint16_t)~g_usbx_function_bit_set[pipe];
    USB20X.BEMPENB = buf;

    usbx_function_set_pid_nak(pipe);

    /* CurrentPIPE Clear */
    if (RZA_IO_RegRead_16(&USB20X.CFIFOSEL, USB_CFIFOSEL_CURPIPE_SHIFT, USB_CFIFOSEL_CURPIPE) == pipe) {
        RZA_IO_RegWrite_16(&USB20X.CFIFOSEL, 0, USB_CFIFOSEL_CURPIPE_SHIFT, USB_CFIFOSEL_CURPIPE);
    }

    if (RZA_IO_RegRead_16(&USB20X.D0FIFOSEL, USB_DnFIFOSEL_CURPIPE_SHIFT, USB_DnFIFOSEL_CURPIPE) == pipe) {
        RZA_IO_RegWrite_16(&USB20X.D0FIFOSEL, 0, USB_DnFIFOSEL_CURPIPE_SHIFT, USB_DnFIFOSEL_CURPIPE);
    }

    if (RZA_IO_RegRead_16(&USB20X.D1FIFOSEL, USB_DnFIFOSEL_CURPIPE_SHIFT, USB_DnFIFOSEL_CURPIPE) == pipe) {
        RZA_IO_RegWrite_16(&USB20X.D1FIFOSEL, 0, USB_DnFIFOSEL_CURPIPE_SHIFT, USB_DnFIFOSEL_CURPIPE);
    }

    /* PIPE Configuration */
    USB20X.PIPESEL  = pipe;
    USB20X.PIPECFG  = cfg->pipecfg;
    USB20X.PIPEBUF  = cfg->pipebuf;
    USB20X.PIPEMAXP = cfg->pipemaxp;
    USB20X.PIPEPERI = cfg->pipeperi;

    g_usbx_function_pipecfg[pipe]  = cfg->pipecfg;
    g_usbx_function_pipebuf[pipe]  = cfg->pipebuf;
    g_usbx_function_pipemaxp[pipe] = cfg->pipemaxp;
    g_usbx_function_pipeperi[pipe] = cfg->pipeperi;

    /* Buffer Clear */
    usbx_function_set_sqclr(pipe);
    usbx_function_aclrm(pipe);

    /* init Global */
    g_usbx_function_pipe_status[pipe]  = DEVDRV_USBF_PIPE_IDLE;
    g_usbx_function_PipeDataSize[pipe] = 0;

    return true;
}


/*************************************************************************/
// read setup packet
void USBHAL::EP0setup(uint8_t *buffer)
{
    memcpy(buffer, setup_buffer, MAX_PACKET_SIZE_EP0);
}


/*************************************************************************/
void USBHAL::EP0readStage(void)
{
    // No implements
}


/*************************************************************************/
void USBHAL::EP0read(void)
{
    uint8_t *buffer;
    uint32_t size;

    /* remain of last writing */
    while (EP0_read_status != DEVDRV_USBF_WRITEEND) {
        static uint8_t bbb[2] = { 255, 255 };
        EP0write(&bbb[0], 0);
    }

    buffer = (uint8_t*)(&setup_buffer[4]);
    size   = (MAX_PACKET_SIZE_EP0 / 2) - 8;
    usbx_api_function_CtrlWriteStart(size, buffer);
}


/*************************************************************************/
uint32_t USBHAL::EP0getReadResult(uint8_t *buffer)
{
    memcpy(buffer, (uint8_t*)(&setup_buffer[4]), g_usbx_function_PipeDataSize[USB_FUNCTION_PIPE0]);

    return g_usbx_function_PipeDataSize[USB_FUNCTION_PIPE0];
}


/*************************************************************************/
void USBHAL::EP0write(uint8_t *buffer, uint32_t size)
{
    /* zero byte writing */
    if ( (size == 0) && (EP0_read_status == DEVDRV_USBF_WRITEEND) ) {
        return;
    }

    if (EP0_read_status == DEVDRV_USBF_WRITEEND) {
        /*1st block*/
        EP0_read_status = usbx_api_function_CtrlReadStart(size, buffer);
    } else {
        /* waits the last transmission */
        /*other blocks*/
        g_usbx_function_data_count[ USB_FUNCTION_PIPE0 ]    = size;
        g_usbx_function_data_pointer [ USB_FUNCTION_PIPE0 ] = buffer;
        EP0_read_status = usbx_function_write_buffer_c(USB_FUNCTION_PIPE0);
    }
    /*max size may be deblocking outside*/
    if (size == MAX_PACKET_SIZE_EP0) {
        EP0_read_status = DEVDRV_USBF_WRITING;
    }
}


/*************************************************************************/
#if 0   // No implements
void USBHAL::EP0getWriteResult(void)
{
}
#endif

/*************************************************************************/
void USBHAL::EP0stall(void)
{
    stallEndpoint( 0 );
}


/*************************************************************************/
EP_STATUS USBHAL::endpointRead(uint8_t endpoint, uint32_t max_size)
{
    uint32_t    pipe = EP2PIPE(endpoint);
    uint32_t    pipe_size;
    uint16_t    pipe_status;
    EP_STATUS status = EP_COMPLETED;

    pipe_status = usbx_api_function_check_pipe_status(pipe, &pipe_size);

    switch (pipe_status) {
        case DEVDRV_USBF_PIPE_IDLE:
        case DEVDRV_USBF_PIPE_WAIT:
            usbx_api_function_set_pid_nak(pipe);
            usbx_api_function_clear_pipe_status(pipe);

            usbx_api_function_start_receive_transfer(pipe, max_size, recv_buffer);
            break;

        default:
            status = EP_PENDING;
            break;
    }

    return status;
}


/*************************************************************************/
EP_STATUS USBHAL::endpointReadResult(uint8_t endpoint, uint8_t *buffer, uint32_t *bytes_read )
{
    uint32_t pipe = EP2PIPE(endpoint);
    uint16_t pipe_status;
    uint16_t err;
    EP_STATUS status = EP_PENDING;


    if (EPx_read_status != DEVDRV_USBF_PIPE_WAIT) {
        return status;
    }

    pipe_status = usbx_api_function_check_pipe_status(pipe, bytes_read);
    switch (pipe_status) {
        case DEVDRV_USBF_PIPE_IDLE:
            return EP_COMPLETED;

        case DEVDRV_USBF_PIPE_DONE:
            return EP_COMPLETED;

        case DEVDRV_USBF_PIPE_WAIT:
            break;

        default:
            return status;
    }

    /* sets the output buffer and size */
    g_usbx_function_data_pointer[pipe] = buffer;

    /* receives data from pipe */
    err = usbx_function_read_buffer(pipe);
    recv_error = err;
    switch (err) {
        case USB_FUNCTION_READEND:
        case USB_FUNCTION_READSHRT:
        case USB_FUNCTION_READOVER:
            *bytes_read = g_usbx_function_PipeDataSize[pipe];
            break;

        case USB_FUNCTION_READING:
        case DEVDRV_USBF_FIFOERROR:
            break;
    }

    pipe_status = usbx_api_function_check_pipe_status(pipe, bytes_read);
    switch (pipe_status) {
        case DEVDRV_USBF_PIPE_DONE:
            status = EP_COMPLETED;
            break;

        case DEVDRV_USBF_PIPE_IDLE:
        case DEVDRV_USBF_PIPE_NORES:
        case DEVDRV_USBF_PIPE_STALL:
        case DEVDRV_USBF_FIFOERROR:
        default:
            break;
    }

    return status;
}


/*************************************************************************/
EP_STATUS USBHAL::endpointWrite(uint8_t endpoint, uint8_t *data, uint32_t size)
{
    uint32_t pipe = EP2PIPE(endpoint);
    uint32_t pipe_size;
    uint16_t pipe_status;
    uint16_t err;
    uint16_t count;
    EP_STATUS status = EP_PENDING;

    pipe_status = usbx_api_function_check_pipe_status(pipe, &pipe_size);

    /* waits the last transmission */
    count = 30000;
    while ((pipe_status == DEVDRV_USBF_PIPE_WAIT) || (pipe_status == DEVDRV_USBF_PIPE_DONE)) {
        pipe_status = usbx_api_function_check_pipe_status(pipe, &pipe_size);
        if( --count == 0 ) {
            pipe_status = DEVDRV_USBF_PIPE_STALL;
            break;
        }
    }

    switch (pipe_status) {
        case DEVDRV_USBF_PIPE_IDLE:
            err = usbx_api_function_start_send_transfer(pipe, size, data);

            switch (err) {
                    /* finish to write */
                case DEVDRV_USBF_WRITEEND:
                    /* finish to write, but data is short */
                case DEVDRV_USBF_WRITESHRT:
                    /* continue to write */
                case DEVDRV_USBF_WRITING:
                    /* use DMA */
                case DEVDRV_USBF_WRITEDMA:
                    /* error */
                case DEVDRV_USBF_FIFOERROR:
                    status = EP_PENDING;
                    break;
            }
            break;

        case DEVDRV_USBF_PIPE_WAIT:
        case DEVDRV_USBF_PIPE_DONE:
            status = EP_PENDING;
            break;

        case DEVDRV_USBF_PIPE_NORES:
        case DEVDRV_USBF_PIPE_STALL:
        default:
            status = EP_STALLED;
            break;
    }

    return status;
}


/*************************************************************************/
EP_STATUS USBHAL::endpointWriteResult(uint8_t endpoint)
{
    uint32_t    pipe = EP2PIPE(endpoint);
    uint32_t    pipe_size;
    uint16_t    pipe_status;
    EP_STATUS status = EP_PENDING;

    pipe_status = usbx_api_function_check_pipe_status(pipe, &pipe_size);

    switch (pipe_status) {
        case DEVDRV_USBF_PIPE_IDLE:
            status = EP_COMPLETED;
            break;

        case DEVDRV_USBF_PIPE_WAIT:
            status = EP_PENDING;
            break;

        case DEVDRV_USBF_PIPE_DONE:
            usbx_function_stop_transfer(pipe);
            status = EP_COMPLETED;
            break;

        case DEVDRV_USBF_PIPE_NORES:
            status = EP_STALLED;
            break;

        case DEVDRV_USBF_PIPE_STALL:
            status = EP_STALLED;
            break;

        default:
            status = EP_PENDING;
    }

    return status;
}


/*************************************************************************/
void USBHAL::stallEndpoint(uint8_t endpoint)
{
    uint32_t pipe = EP2PIPE(endpoint);

    usbx_function_clear_pid_stall(pipe);
}


/*************************************************************************/
void USBHAL::unstallEndpoint(uint8_t endpoint)
{
    uint32_t pipe = EP2PIPE(endpoint);

    usbx_function_set_pid_stall( pipe );
}


/*************************************************************************/
bool USBHAL::getEndpointStallState(uint8_t endpoint)
{
    // No implemens
    return false;
}


/*************************************************************************/
#if 0   // No implements
void USBHAL::remoteWakeup(void)
{
}
#endif

/*************************************************************************/
void USBHAL::_usbisr(void)
{
    instance->usbisr();
}


/*************************************************************************/
void USBHAL::usbisr(void)
{
    uint16_t            int_sts0;
    uint16_t            int_sts1;
    uint16_t            int_sts2;
    uint16_t            int_sts3;
    uint16_t            int_enb0;
    uint16_t            int_enb2;
    uint16_t            int_enb3;
    uint16_t            int_enb4;
    volatile uint16_t   dumy_sts;


    int_sts0 = USB20X.INTSTS0;

    if (!(int_sts0 & (
                USB_FUNCTION_BITVBINT |
                USB_FUNCTION_BITRESM  |
                USB_FUNCTION_BITSOFR  |
                USB_FUNCTION_BITDVST  |
                USB_FUNCTION_BITCTRT  |
                USB_FUNCTION_BITBEMP  |
                USB_FUNCTION_BITNRDY  |
                USB_FUNCTION_BITBRDY ))) {
        return;
    }

    int_sts1 = USB20X.BRDYSTS;
    int_sts2 = USB20X.NRDYSTS;
    int_sts3 = USB20X.BEMPSTS;
    int_enb0 = USB20X.INTENB0;
    int_enb2 = USB20X.BRDYENB;
    int_enb3 = USB20X.NRDYENB;
    int_enb4 = USB20X.BEMPENB;

    if ((int_sts0 & USB_FUNCTION_BITRESM) &&
            (int_enb0 & USB_FUNCTION_BITRSME)) {
        USB20X.INTSTS0 = (uint16_t)~USB_FUNCTION_BITRESM;
        RZA_IO_RegWrite_16(&USB20X.INTENB0, 0, USB_INTENB0_RSME_SHIFT, USB_INTENB0_RSME);
        /*usbx_function_USB_FUNCTION_Resume();*/
        suspendStateChanged(1);
    } else if (
        (int_sts0 & USB_FUNCTION_BITVBINT) &&
        (int_enb0 & USB_FUNCTION_BITVBSE)) {
        USB20X.INTSTS0 = (uint16_t)~USB_FUNCTION_BITVBINT;

        if (usbx_function_CheckVBUStaus() == DEVDRV_USBF_ON) {
            usbx_function_USB_FUNCTION_Attach();
        } else {
            usbx_function_USB_FUNCTION_Detach();
        }
    } else if (
        (int_sts0 & USB_FUNCTION_BITSOFR) &&
        (int_enb0 & USB_FUNCTION_BITSOFE)) {
        USB20X.INTSTS0 = (uint16_t)~USB_FUNCTION_BITSOFR;
        SOF((USB20X.FRMNUM & USB_FRMNUM_FRNM) >> USB_FRMNUM_FRNM_SHIFT);
    } else if (
        (int_sts0 & USB_FUNCTION_BITDVST) &&
        (int_enb0 & USB_FUNCTION_BITDVSE)) {
        USB20X.INTSTS0 = (uint16_t)~USB_FUNCTION_BITDVST;
        switch (int_sts0 & USB_FUNCTION_BITDVSQ) {
            case USB_FUNCTION_DS_POWR:
                break;

            case USB_FUNCTION_DS_DFLT:
                /*****************************************************************************
                 * Function Name: usbx_function_USB_FUNCTION_BusReset
                 * Description  : This function is executed when the USB device is transitioned
                 *              : to POWERD_STATE. Sets the device descriptor according to the
                 *              : connection speed determined by the USB reset hand shake.
                 * Arguments    : none
                 * Return Value : none
                 *****************************************************************************/
                usbx_function_init_status();            /* memory clear */

#if 0
                /* You would program those steps in USBCallback_busReset
                 * if the system need the comment out steps.
                 */

                if (usbx_function_is_hispeed() == USB_FUNCTION_HIGH_SPEED) {
                    /* Device Descriptor reset */
                    usbx_function_ResetDescriptor(USB_FUNCTION_HIGH_SPEED);
                } else {
                    /* Device Descriptor reset */
                    usbx_function_ResetDescriptor(USB_FUNCTION_FULL_SPEED);
                }
#endif
                /* Default Control PIPE reset */
                /*****************************************************************************
                 * Function Name: usbx_function_ResetDCP
                 * Description  : Initializes the default control pipe(DCP).
                 * Outline      : Reset default control pipe
                 * Arguments    : none
                 * Return Value : none
                 *****************************************************************************/
                USB20X.DCPCFG  = 0;
                USB20X.DCPMAXP = 64;    /*TODO: This value is copied from sample*/

                USB20X.CFIFOSEL  = (uint16_t)(USB_FUNCTION_BITMBW_8 | USB_FUNCTION_BITBYTE_LITTLE);
                USB20X.D0FIFOSEL = (uint16_t)(USB_FUNCTION_BITMBW_8 | USB_FUNCTION_BITBYTE_LITTLE);
                USB20X.D1FIFOSEL = (uint16_t)(USB_FUNCTION_BITMBW_8 | USB_FUNCTION_BITBYTE_LITTLE);

                busReset();
                break;

            case USB_FUNCTION_DS_ADDS:
                break;

            case USB_FUNCTION_DS_CNFG:
                break;

            case USB_FUNCTION_DS_SPD_POWR:
            case USB_FUNCTION_DS_SPD_DFLT:
            case USB_FUNCTION_DS_SPD_ADDR:
            case USB_FUNCTION_DS_SPD_CNFG:
                suspendStateChanged(0);
                /*usbx_function_USB_FUNCTION_Suspend();*/
                break;

            default:
                break;
        }
    } else if (
        (int_sts0 & USB_FUNCTION_BITBEMP) &&
        (int_enb0 & USB_FUNCTION_BITBEMP) &&
        ((int_sts3 & int_enb4) & g_usbx_function_bit_set[USB_FUNCTION_PIPE0])) {
        /* ==== BEMP PIPE0 ==== */
        usbx_function_BEMPInterruptPIPE0(int_sts3, int_enb4, this, &USBHAL::EP0in);
    } else if (
        (int_sts0 & USB_FUNCTION_BITBRDY) &&
        (int_enb0 & USB_FUNCTION_BITBRDY) &&
        ((int_sts1 & int_enb2) & g_usbx_function_bit_set[USB_FUNCTION_PIPE0])) {
        /* ==== BRDY PIPE0 ==== */
        usbx_function_BRDYInterruptPIPE0(int_sts1, int_enb2, this, &USBHAL::EP0out);
    } else if (
        (int_sts0 & USB_FUNCTION_BITNRDY) &&
        (int_enb0 & USB_FUNCTION_BITNRDY) &&
        ((int_sts2 & int_enb3) & g_usbx_function_bit_set[USB_FUNCTION_PIPE0])) {
        /* ==== NRDY PIPE0 ==== */
        usbx_function_NRDYInterruptPIPE0(int_sts2, int_enb3, this, NULL);
    } else if (
        (int_sts0 & USB_FUNCTION_BITCTRT) && (int_enb0 & USB_FUNCTION_BITCTRE)) {
        int_sts0 = USB20X.INTSTS0;
        USB20X.INTSTS0 = (uint16_t)~USB_FUNCTION_BITCTRT;

        if (((int_sts0 & USB_FUNCTION_BITCTSQ) == USB_FUNCTION_CS_RDDS) ||
                ((int_sts0 & USB_FUNCTION_BITCTSQ) == USB_FUNCTION_CS_WRDS) ||
                ((int_sts0 & USB_FUNCTION_BITCTSQ) == USB_FUNCTION_CS_WRND)) {

            /* remake EP0 into buffer */
            usbx_function_save_request();
            if ((USB20X.INTSTS0 & USB_FUNCTION_BITVALID) && (
                        ((int_sts0 & USB_FUNCTION_BITCTSQ) == USB_FUNCTION_CS_RDDS) ||
                        ((int_sts0 & USB_FUNCTION_BITCTSQ) == USB_FUNCTION_CS_WRDS) ||
                        ((int_sts0 & USB_FUNCTION_BITCTSQ) == USB_FUNCTION_CS_WRND))) {
                /* New SETUP token received */
                /* Three dummy reads for cleearing interrupt requests */
                dumy_sts = USB20X.INTSTS0;
                dumy_sts = USB20X.INTSTS0;
                dumy_sts = USB20X.INTSTS0;
                return;
            }
        }

        switch (int_sts0 & USB_FUNCTION_BITCTSQ) {
            case USB_FUNCTION_CS_IDST:
                if (g_usbx_function_TestModeFlag == DEVDRV_USBF_YES) {
                    /* ==== Test Mode ==== */
                    usbx_function_USB_FUNCTION_TestMode();
                }
                /* Needs not procedure in this state */
                break;

            case USB_FUNCTION_CS_RDDS:
                /* Reads a setup packet */
                EP0setupCallback();
                break;

            case USB_FUNCTION_CS_WRDS:
                /* Original code was the SetDescriptor was called */
                EP0setupCallback();
                break;

            case USB_FUNCTION_CS_WRND:
                EP0setupCallback();

                /*The EP0setupCallback should finish in successful */
                usbx_function_set_pid_buf(USB_FUNCTION_PIPE0);

                RZA_IO_RegWrite_16(&USB20X.DCPCTR, 1, USB_DCPCTR_CCPL_SHIFT, USB_DCPCTR_CCPL);
                break;

            case USB_FUNCTION_CS_RDSS:
                RZA_IO_RegWrite_16(&USB20X.DCPCTR, 1, USB_DCPCTR_CCPL_SHIFT, USB_DCPCTR_CCPL);
                break;

            case USB_FUNCTION_CS_WRSS:
                RZA_IO_RegWrite_16(&USB20X.DCPCTR, 1, USB_DCPCTR_CCPL_SHIFT, USB_DCPCTR_CCPL);
                break;

            case USB_FUNCTION_CS_SQER:
                usbx_function_set_pid_stall(USB_FUNCTION_PIPE0);
                break;

            default:
                usbx_function_set_pid_stall(USB_FUNCTION_PIPE0);
                break;
        }
    } else if (
        (int_sts0 & USB_FUNCTION_BITBEMP) &&
        (int_enb0 & USB_FUNCTION_BITBEMP) &&
        (int_sts3 & int_enb4) ) {
        /* ==== BEMP PIPEx ==== */
        usbx_function_BEMPInterrupt(int_sts3, int_enb4, this, epCallback);
    } else if (
        (int_sts0 & USB_FUNCTION_BITBRDY) &&
        (int_enb0 & USB_FUNCTION_BITBRDY) &&
        (int_sts1 & int_enb2) ) {
        /* ==== BRDY PIPEx ==== */
        usbx_function_BRDYInterrupt(int_sts1, int_enb2, this, epCallback);
    } else if (
        (int_sts0 & USB_FUNCTION_BITNRDY) &&
        (int_enb0 & USB_FUNCTION_BITNRDY) &&
        (int_sts2 & int_enb3)) {
        /* ==== NRDY PIPEx ==== */
        usbx_function_NRDYInterrupt(int_sts2, int_enb3, this, epCallback);
    } else {
        /* Do Nothing */
    }

    /* Three dummy reads for cleearing interrupt requests */
    dumy_sts = USB20X.INTSTS0;
    dumy_sts = USB20X.INTSTS1;
}

/*************************************************************************/
#endif
/*************************************************************************/
/*EOF*/
