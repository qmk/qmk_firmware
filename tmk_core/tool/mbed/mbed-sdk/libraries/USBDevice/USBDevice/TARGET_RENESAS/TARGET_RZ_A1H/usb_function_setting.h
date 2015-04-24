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
* Copyright (C) 2014 - 2015 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/

#ifndef USB_FUNCTION_SETTING_H
#define USB_FUNCTION_SETTING_H

#ifdef __cplusplus
extern "C" {
#endif

#define USB_FUNCTION_CH                       0
#define USB_FUNCTION_HISPEED                  1

#if (USB_FUNCTION_CH == 0)
#include "usb0_function.h"
#define USB20X                                USB200
#define USBIX_IRQn                            USBI0_IRQn
#define g_usbx_function_bit_set               g_usb0_function_bit_set
#define g_usbx_function_PipeDataSize          g_usb0_function_PipeDataSize
#define g_usbx_function_data_count            g_usb0_function_data_count
#define g_usbx_function_PipeTbl               g_usb0_function_PipeTbl
#define g_usbx_function_DmaStatus             g_usb0_function_DmaStatus
#define g_usbx_function_pipecfg               g_usb0_function_pipecfg
#define g_usbx_function_pipe_status           g_usb0_function_pipe_status
#define g_usbx_function_data_pointer          g_usb0_function_data_pointer
#define g_usbx_function_pipebuf               g_usb0_function_pipebuf
#define g_usbx_function_pipemaxp              g_usb0_function_pipemaxp
#define g_usbx_function_pipeperi              g_usb0_function_pipeperi
#define g_usbx_function_TestModeFlag          g_usb0_function_TestModeFlag
#define usbx_function_BRDYInterruptPIPE0      usb0_function_BRDYInterruptPIPE0
#define usbx_function_BRDYInterrupt           usb0_function_BRDYInterrupt
#define usbx_function_NRDYInterruptPIPE0      usb0_function_NRDYInterruptPIPE0
#define usbx_function_NRDYInterrupt           usb0_function_NRDYInterrupt
#define usbx_function_BEMPInterruptPIPE0      usb0_function_BEMPInterruptPIPE0
#define usbx_function_BEMPInterrupt           usb0_function_BEMPInterrupt
#define usbx_function_read_buffer_c           usb0_function_read_buffer_c
#define usbx_function_set_pid_buf             usb0_function_set_pid_buf
#define usbx_function_disable_brdy_int        usb0_function_disable_brdy_int
#define usbx_function_set_pid_stall           usb0_function_set_pid_stall
#define usbx_function_dma_interrupt_d0fifo    usb0_function_dma_interrupt_d0fifo
#define usbx_function_read_dma                usb0_function_read_dma
#define usbx_function_dma_interrupt_d1fifo    usb0_function_dma_interrupt_d1fifo
#define usbx_function_write_buffer            usb0_function_write_buffer
#define usbx_function_set_pid_nak             usb0_function_set_pid_nak
#define usbx_function_get_mbw                 usb0_function_get_mbw
#define usbx_function_set_curpipe             usb0_function_set_curpipe
#define usbx_function_aclrm                   usb0_function_aclrm
#define usbx_function_enable_nrdy_int         usb0_function_enable_nrdy_int
#define usbx_function_enable_brdy_int         usb0_function_enable_brdy_int
#define usbx_function_get_pid                 usb0_function_get_pid
#define usbx_function_get_inbuf               usb0_function_get_inbuf
#define usbx_function_disable_bemp_int        usb0_function_disable_bemp_int
#define usbx_function_EpToPipe                usb0_function_EpToPipe
#define usbx_function_clear_pipe_tbl          usb0_function_clear_pipe_tbl
#define Userdef_USB_usbx_function_d0fifo_dmaintid Userdef_USB_usb0_function_d0fifo_dmaintid
#define Userdef_USB_usbx_function_d1fifo_dmaintid Userdef_USB_usb0_function_d1fifo_dmaintid
#define usbx_function_reset_module            usb0_function_reset_module
#define usbx_function_init_status             usb0_function_init_status
#define usbx_function_InitModule              usb0_function_InitModule
#define usbx_function_clear_alt               usb0_function_clear_alt
#define usbx_function_set_sqclr               usb0_function_set_sqclr
#define usbx_api_function_CtrlWriteStart      usb0_api_function_CtrlWriteStart
#define usbx_api_function_CtrlReadStart       usb0_api_function_CtrlReadStart
#define usbx_function_write_buffer_c          usb0_function_write_buffer_c
#define usbx_api_function_check_pipe_status   usb0_api_function_check_pipe_status
#define usbx_api_function_set_pid_nak         usb0_api_function_set_pid_nak
#define usbx_api_function_clear_pipe_status   usb0_api_function_clear_pipe_status
#define usbx_api_function_start_receive_transfer usb0_api_function_start_receive_transfer
#define usbx_function_read_buffer             usb0_function_read_buffer
#define usbx_api_function_start_send_transfer usb0_api_function_start_send_transfer
#define usbx_function_stop_transfer           usb0_function_stop_transfer
#define usbx_function_clear_pid_stall         usb0_function_clear_pid_stall
#define usbx_function_CheckVBUStaus           usb0_function_CheckVBUStaus
#define usbx_function_USB_FUNCTION_Attach     usb0_function_USB_FUNCTION_Attach
#define usbx_function_USB_FUNCTION_Detach     usb0_function_USB_FUNCTION_Detach
#define usbx_function_is_hispeed              usb0_function_is_hispeed
#define usbx_function_ResetDescriptor         usb0_function_ResetDescriptor
#define usbx_function_USB_FUNCTION_Suspend    usb0_function_USB_FUNCTION_Suspend
#define usbx_function_USB_FUNCTION_TestMode   usb0_function_USB_FUNCTION_TestMode
#else
#include "usb1_function.h"
#define USB20X                                USB201
#define USBIX_IRQn                            USBI1_IRQn
#define g_usbx_function_bit_set               g_usb1_function_bit_set
#define g_usbx_function_PipeDataSize          g_usb1_function_PipeDataSize
#define g_usbx_function_data_count            g_usb1_function_data_count
#define g_usbx_function_PipeTbl               g_usb1_function_PipeTbl
#define g_usbx_function_DmaStatus             g_usb1_function_DmaStatus
#define g_usbx_function_pipecfg               g_usb1_function_pipecfg
#define g_usbx_function_pipe_status           g_usb1_function_pipe_status
#define g_usbx_function_data_pointer          g_usb1_function_data_pointer
#define g_usbx_function_pipebuf               g_usb1_function_pipebuf
#define g_usbx_function_pipemaxp              g_usb1_function_pipemaxp
#define g_usbx_function_pipeperi              g_usb1_function_pipeperi
#define g_usbx_function_TestModeFlag          g_usb1_function_TestModeFlag
#define usbx_function_BRDYInterruptPIPE0      usb1_function_BRDYInterruptPIPE0
#define usbx_function_BRDYInterrupt           usb1_function_BRDYInterrupt
#define usbx_function_NRDYInterruptPIPE0      usb1_function_NRDYInterruptPIPE0
#define usbx_function_NRDYInterrupt           usb1_function_NRDYInterrupt
#define usbx_function_BEMPInterruptPIPE0      usb1_function_BEMPInterruptPIPE0
#define usbx_function_BEMPInterrupt           usb1_function_BEMPInterrupt
#define usbx_function_read_buffer_c           usb1_function_read_buffer_c
#define usbx_function_set_pid_buf             usb1_function_set_pid_buf
#define usbx_function_disable_brdy_int        usb1_function_disable_brdy_int
#define usbx_function_set_pid_stall           usb1_function_set_pid_stall
#define usbx_function_dma_interrupt_d0fifo    usb1_function_dma_interrupt_d0fifo
#define usbx_function_read_dma                usb1_function_read_dma
#define usbx_function_dma_interrupt_d1fifo    usb1_function_dma_interrupt_d1fifo
#define usbx_function_write_buffer            usb1_function_write_buffer
#define usbx_function_set_pid_nak             usb1_function_set_pid_nak
#define usbx_function_get_mbw                 usb1_function_get_mbw
#define usbx_function_set_curpipe             usb1_function_set_curpipe
#define usbx_function_aclrm                   usb1_function_aclrm
#define usbx_function_enable_nrdy_int         usb1_function_enable_nrdy_int
#define usbx_function_enable_brdy_int         usb1_function_enable_brdy_int
#define usbx_function_get_pid                 usb1_function_get_pid
#define usbx_function_get_inbuf               usb1_function_get_inbuf
#define usbx_function_disable_bemp_int        usb1_function_disable_bemp_int
#define usbx_function_EpToPipe                usb1_function_EpToPipe
#define usbx_function_clear_pipe_tbl          usb1_function_clear_pipe_tbl
#define Userdef_USB_usbx_function_d0fifo_dmaintid Userdef_USB_usb1_function_d0fifo_dmaintid
#define Userdef_USB_usbx_function_d1fifo_dmaintid Userdef_USB_usb1_function_d1fifo_dmaintid
#define usbx_function_reset_module            usb1_function_reset_module
#define usbx_function_init_status             usb1_function_init_status
#define usbx_function_InitModule              usb1_function_InitModule
#define usbx_function_clear_alt               usb1_function_clear_alt
#define usbx_function_set_sqclr               usb1_function_set_sqclr
#define usbx_api_function_CtrlWriteStart      usb1_api_function_CtrlWriteStart
#define usbx_api_function_CtrlReadStart       usb1_api_function_CtrlReadStart
#define usbx_function_write_buffer_c          usb1_function_write_buffer_c
#define usbx_api_function_check_pipe_status   usb1_api_function_check_pipe_status
#define usbx_api_function_set_pid_nak         usb1_api_function_set_pid_nak
#define usbx_api_function_clear_pipe_status   usb1_api_function_clear_pipe_status
#define usbx_api_function_start_receive_transfer usb1_api_function_start_receive_transfer
#define usbx_function_read_buffer             usb1_function_read_buffer
#define usbx_api_function_start_send_transfer usb1_api_function_start_send_transfer
#define usbx_function_stop_transfer           usb1_function_stop_transfer
#define usbx_function_clear_pid_stall         usb1_function_clear_pid_stall
#define usbx_function_CheckVBUStaus           usb1_function_CheckVBUStaus
#define usbx_function_USB_FUNCTION_Attach     usb1_function_USB_FUNCTION_Attach
#define usbx_function_USB_FUNCTION_Detach     usb1_function_USB_FUNCTION_Detach
#define usbx_function_is_hispeed              usb1_function_is_hispeed
#define usbx_function_ResetDescriptor         usb1_function_ResetDescriptor
#define usbx_function_USB_FUNCTION_Suspend    usb1_function_USB_FUNCTION_Suspend
#define usbx_function_USB_FUNCTION_TestMode   usb1_function_USB_FUNCTION_TestMode
#endif


#ifdef __cplusplus
}
#endif

#endif  /* USB_FUNCTION_SETTING_H */
