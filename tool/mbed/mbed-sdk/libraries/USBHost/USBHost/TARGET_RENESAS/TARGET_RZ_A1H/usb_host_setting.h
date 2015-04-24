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

#ifndef USB_HOST_SETTING_H
#define USB_HOST_SETTING_H

#ifdef __cplusplus
extern "C" {
#endif

#define USB_HOST_CH                           0
#define USB_HOST_HISPEED                      1

#define INT_TRANS_MAX_NUM                     4    /* min:1 max:4 */
#define ISO_TRANS_MAX_NUM                     0    /* min:0 max:2 */

#if (USB_HOST_CH == 0)
#include "usb0_host.h"
#define USB20X                                USB200
#define USBIXUSBIX                            USBI0_IRQn
#define g_usbx_host_SupportUsbDeviceSpeed     g_usb0_host_SupportUsbDeviceSpeed
#define g_usbx_host_UsbDeviceSpeed            g_usb0_host_UsbDeviceSpeed
#define g_usbx_host_CmdStage                  g_usb0_host_CmdStage
#define g_usbx_host_pipe_status               g_usb0_host_pipe_status
#define g_usbx_host_data_pointer              g_usb0_host_data_pointer
#define g_usbx_host_data_count                g_usb0_host_data_count
#define usbx_api_host_init                    usb0_api_host_init
#define usbx_host_UsbBusReset                 usb0_host_UsbBusReset
#define usbx_host_get_devadd                  usb0_host_get_devadd
#define usbx_host_set_devadd                  usb0_host_set_devadd
#define usbx_host_SetupStage                  usb0_host_SetupStage
#define usbx_host_CtrlWriteStart              usb0_host_CtrlWriteStart
#define usbx_host_CtrlReadStart               usb0_host_CtrlReadStart
#define usbx_api_host_SetEndpointTable        usb0_api_host_SetEndpointTable
#define usbx_host_start_send_transfer         usb0_host_start_send_transfer
#define usbx_host_start_receive_transfer      usb0_host_start_receive_transfer
#define usbx_host_stop_transfer               usb0_host_stop_transfer
#define usbx_host_set_sqclr                   usb0_host_set_sqclr
#define usbx_host_set_sqset                   usb0_host_set_sqset
#define usbx_host_CheckAttach                 usb0_host_CheckAttach
#define usbx_host_UsbDetach                   usb0_host_UsbDetach
#define usbx_host_UsbAttach                   usb0_host_UsbAttach
#define usbx_host_init_pipe_status            usb0_host_init_pipe_status
#define usbx_host_get_sqmon                   usb0_host_get_sqmon
#else
#include "usb1_host.h"
#define USB20X                                USB201
#define USBIXUSBIX                            USBI1_IRQn
#define g_usbx_host_SupportUsbDeviceSpeed     g_usb1_host_SupportUsbDeviceSpeed
#define g_usbx_host_UsbDeviceSpeed            g_usb1_host_UsbDeviceSpeed
#define g_usbx_host_CmdStage                  g_usb1_host_CmdStage
#define g_usbx_host_pipe_status               g_usb1_host_pipe_status
#define g_usbx_host_data_pointer              g_usb1_host_data_pointer
#define g_usbx_host_data_count                g_usb1_host_data_count
#define usbx_api_host_init                    usb1_api_host_init
#define usbx_host_UsbBusReset                 usb1_host_UsbBusReset
#define usbx_host_get_devadd                  usb1_host_get_devadd
#define usbx_host_set_devadd                  usb1_host_set_devadd
#define usbx_host_SetupStage                  usb1_host_SetupStage
#define usbx_host_CtrlWriteStart              usb1_host_CtrlWriteStart
#define usbx_host_CtrlReadStart               usb1_host_CtrlReadStart
#define usbx_api_host_SetEndpointTable        usb1_api_host_SetEndpointTable
#define usbx_host_start_send_transfer         usb1_host_start_send_transfer
#define usbx_host_start_receive_transfer      usb1_host_start_receive_transfer
#define usbx_host_stop_transfer               usb1_host_stop_transfer
#define usbx_host_set_sqclr                   usb1_host_set_sqclr
#define usbx_host_set_sqset                   usb1_host_set_sqset
#define usbx_host_CheckAttach                 usb1_host_CheckAttach
#define usbx_host_UsbDetach                   usb1_host_UsbDetach
#define usbx_host_UsbAttach                   usb1_host_UsbAttach
#define usbx_host_init_pipe_status            usb1_host_init_pipe_status
#define usbx_host_get_sqmon                   usb1_host_get_sqmon
#endif


#ifdef __cplusplus
}
#endif

#endif  /* USB_HOST_SETTING_H */
