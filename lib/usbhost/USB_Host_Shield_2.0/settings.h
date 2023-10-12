/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */

#ifndef USB_HOST_SHIELD_SETTINGS_H
#define USB_HOST_SHIELD_SETTINGS_H
#include "macros.h"

////////////////////////////////////////////////////////////////////////////////
// DEBUGGING
////////////////////////////////////////////////////////////////////////////////

/* Set this to 1 to activate serial debugging */
#define ENABLE_UHS_DEBUGGING 0

/* This can be used to select which serial port to use for debugging if
 * multiple serial ports are available.
 * For example Serial3.
 */
#ifndef USB_HOST_SERIAL
#define USB_HOST_SERIAL Serial
#endif

////////////////////////////////////////////////////////////////////////////////
// Manual board activation
////////////////////////////////////////////////////////////////////////////////

/* Set this to 1 if you are using an Arduino Mega ADK board with MAX3421e built-in */
#define USE_UHS_MEGA_ADK 0 // If you are using Arduino 1.5.5 or newer there is no need to do this manually

/* Set this to 1 if you are using a Black Widdow */
#define USE_UHS_BLACK_WIDDOW 0

/* Set this to a one to use the xmem2 lock. This is needed for multitasking and threading */
#define USE_XMEM_SPI_LOCK 0

////////////////////////////////////////////////////////////////////////////////
// Wii IR camera
////////////////////////////////////////////////////////////////////////////////

/* Set this to 1 to activate code for the Wii IR camera */
#define ENABLE_WII_IR_CAMERA 0

////////////////////////////////////////////////////////////////////////////////
// MASS STORAGE
////////////////////////////////////////////////////////////////////////////////
// <<<<<<<<<<<<<<<< IMPORTANT >>>>>>>>>>>>>>>
// Set this to 1 to support single LUN devices, and save RAM. -- I.E. thumb drives.
// Each LUN needs ~13 bytes to be able to track the state of each unit.
#ifndef MASS_MAX_SUPPORTED_LUN
#define MASS_MAX_SUPPORTED_LUN 8
#endif

////////////////////////////////////////////////////////////////////////////////
// Set to 1 to use the faster spi4teensy3 driver.
////////////////////////////////////////////////////////////////////////////////
#ifndef USE_SPI4TEENSY3
#define USE_SPI4TEENSY3 1
#endif

////////////////////////////////////////////////////////////////////////////////
// AUTOMATIC Settings
////////////////////////////////////////////////////////////////////////////////

// No user serviceable parts below this line.
// DO NOT change anything below here unless you are a developer!

#include "version_helper.h"

#if defined(__GNUC__) && defined(__AVR__)
#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif
#if GCC_VERSION < 40602 // Test for GCC < 4.6.2
#ifdef PROGMEM
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data"))) // Workaround for http://gcc.gnu.org/bugzilla/show_bug.cgi?id=34734#c4
#ifdef PSTR
#undef PSTR
#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];})) // Copied from pgmspace.h in avr-libc source
#endif
#endif
#endif
#endif

#if !defined(DEBUG_USB_HOST) && ENABLE_UHS_DEBUGGING
#define DEBUG_USB_HOST
#endif

#if !defined(WIICAMERA) && ENABLE_WII_IR_CAMERA
#define WIICAMERA
#endif

// To use some other locking (e.g. freertos),
// define XMEM_ACQUIRE_SPI and XMEM_RELEASE_SPI to point to your lock and unlock.
// NOTE: NO argument is passed. You have to do this within your routine for
// whatever you are using to lock and unlock.
#if !defined(XMEM_ACQUIRE_SPI)
#if USE_XMEM_SPI_LOCK || defined(USE_MULTIPLE_APP_API)
#include <xmem.h>
#else
#define XMEM_ACQUIRE_SPI() (void(0))
#define XMEM_RELEASE_SPI() (void(0))
#endif
#endif

#if !defined(EXT_RAM) && defined(EXT_RAM_STACK) || defined(EXT_RAM_HEAP)
#include <xmem.h>
#else
#define EXT_RAM 0
#endif

#if defined(CORE_TEENSY) && (defined(__MK20DX128__) || defined(__MK20DX256__))
#define USING_SPI4TEENSY3 USE_SPI4TEENSY3
#else
#define USING_SPI4TEENSY3 0
#endif

#if ((defined(ARDUINO_SAM_DUE) && defined(__SAM3X8E__)) || defined(RBL_NRF51822) || defined(__ARDUINO_X86__) || ARDUINO >= 10600) && !USING_SPI4TEENSY3
#include <SPI.h> // Use the Arduino SPI library for the Arduino Due, RedBearLab nRF51822, Intel Galileo 1 & 2, Intel Edison or if the SPI library with transaction is available
#endif
#if defined(__PIC32MX__) || defined(__PIC32MZ__)
#include <../../../../hardware/pic32/libraries/SPI/SPI.h> // Hack to use the SPI library
#endif

#endif /* SETTINGS_H */
