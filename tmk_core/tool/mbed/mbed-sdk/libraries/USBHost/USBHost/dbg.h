/* mbed USBHost Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef USB_DEBUG_H
#define USB_DEBUG_H

//Debug is disabled by default
#define DEBUG 3 /*INFO,ERR,WARN*/
#define DEBUG_TRANSFER 0
#define DEBUG_EP_STATE 0
#define DEBUG_EVENT 0

#if (DEBUG > 3)
#define USB_DBG(x, ...) std::printf("[USB_DBG: %s:%d]" x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define USB_DBG(x, ...)
#endif

#if (DEBUG > 2)
#define USB_INFO(x, ...) std::printf("[USB_INFO: %s:%d]" x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define USB_INFO(x, ...)
#endif

#if (DEBUG > 1)
#define USB_WARN(x, ...) std::printf("[USB_WARNING: %s:%d]" x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define USB_WARN(x, ...)
#endif

#if (DEBUG > 0)
#define USB_ERR(x, ...) std::printf("[USB_ERR: %s:%d]" x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define USB_ERR(x, ...)
#endif

#if (DEBUG_TRANSFER)
#define USB_DBG_TRANSFER(x, ...) std::printf("[USB_TRANSFER: %s:%d]" x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define USB_DBG_TRANSFER(x, ...)
#endif

#if (DEBUG_EVENT)
#define USB_DBG_EVENT(x, ...) std::printf("[USB_EVENT: %s:%d]" x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define USB_DBG_EVENT(x, ...)
#endif


#endif



