/* Copyright (c) 2010-2011 mbed.org, MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef USBENDPOINTS_H
#define USBENDPOINTS_H

/* SETUP packet size */
#define SETUP_PACKET_SIZE (8)

/* Options flags for configuring endpoints */
#define DEFAULT_OPTIONS     (0)
#define SINGLE_BUFFERED     (1U << 0)
#define ISOCHRONOUS         (1U << 1)
#define RATE_FEEDBACK_MODE  (1U << 2) /* Interrupt endpoints only */

/* Endpoint transfer status, for endpoints > 0 */
typedef enum {
    EP_COMPLETED,   /* Transfer completed */
    EP_PENDING,     /* Transfer in progress */
    EP_INVALID,     /* Invalid parameter */
    EP_STALLED,     /* Endpoint stalled */
} EP_STATUS;

/* Include configuration for specific target */
#if defined(TARGET_LPC1768) || defined(TARGET_LPC2368) || defined(TARGET_LPC4088) || defined(TARGET_LPC4088_DM)
#include "USBEndpoints_LPC17_LPC23.h"
#elif defined(TARGET_LPC11UXX) || defined(TARGET_LPC1347) || defined (TARGET_LPC11U6X) || defined (TARGET_LPC1549)
#include "USBEndpoints_LPC11U.h"
#elif defined(TARGET_KL25Z) | defined(TARGET_KL43Z) | defined(TARGET_KL46Z) | defined(TARGET_K20D50M) | defined(TARGET_K64F) | defined(TARGET_K22F) | defined(TARGET_TEENSY3_1)
#include "USBEndpoints_KL25Z.h"
#elif defined (TARGET_STM32F4)
#include "USBEndpoints_STM32F4.h"
#elif defined (TARGET_RZ_A1H)
#include "USBEndpoints_RZ_A1H.h"
#elif defined(TARGET_Maxim)
#include "USBEndpoints_Maxim.h"
#else
#error "Unknown target type"
#endif

#endif
