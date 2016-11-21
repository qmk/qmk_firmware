/* 
 * Copyright 2012 Jun Wako <wakojun@gmail.com>
 * This file is based on:
 *     LUFA-120219/Demos/Device/Lowlevel/KeyboardMouse
 *     LUFA-120219/Demos/Device/Lowlevel/GenericHID
 */

/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#ifndef _LUFA_H_
#define _LUFA_H_

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <string.h>
#include <LUFA/Version.h>
#include <LUFA/Drivers/USB/USB.h>
#include "host.h"
#ifdef MIDI_ENABLE
  #include "midi.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif

extern host_driver_t lufa_driver;

#ifdef __cplusplus
}
#endif

/* extra report structure */
typedef struct {
    uint8_t  report_id;
    uint16_t usage;
} __attribute__ ((packed)) report_extra_t;

#ifdef MIDI_ENABLE
  #define MIDI_SYSEX_BUFFER 16 
  void MIDI_Task(void);
  MidiDevice midi_device;

  void sysex_callback(MidiDevice * device, uint16_t start, uint8_t length, uint8_t * data);
  uint32_t decode_uint32_chunk(uint8_t * data);
  uint32_t decode_uint8_chunk(uint8_t * data);
  void encode_uint32_chunk(uint32_t data, uint8_t * pointer);
  void encode_uint8_chunk(uint8_t data, uint8_t * pointer);
  void sysex_buffer_callback(MidiDevice * device, uint8_t length, uint8_t * data);
  void send_unicode_midi(uint32_t unicode);
  void send_bytes_sysex(uint8_t type, uint8_t * bytes, uint8_t length);
#endif

// #if LUFA_VERSION_INTEGER < 0x120730
//     /* old API 120219 */
//     #define ENDPOINT_CONFIG(epnum, eptype, epdir, epsize, epbank)    Endpoint_ConfigureEndpoint(epnum, eptype, epdir, epsize, epbank)
// #else
    /* new API >= 120730 */
    #define ENDPOINT_BANK_SINGLE 1
    #define ENDPOINT_BANK_DOUBLE 2
    #define ENDPOINT_CONFIG(epnum, eptype, epdir, epsize, epbank)    Endpoint_ConfigureEndpoint((epdir) | (epnum) , eptype, epsize, epbank)
// #endif

#endif
