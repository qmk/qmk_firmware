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
  void sysex_buffer_callback(MidiDevice * device, uint8_t length, uint8_t * data);
  void send_bytes_sysex(uint8_t message_type, uint8_t data_type, uint8_t * bytes, uint8_t length);
  void dword_to_bytes(uint32_t dword, uint8_t * bytes);
  uint32_t bytes_to_dword(uint8_t * bytes, uint8_t index);

  __attribute__ ((weak))
  bool sysex_process_quantum(uint8_t length, uint8_t * data);

  __attribute__ ((weak))
  bool sysex_process_keyboard(uint8_t length, uint8_t * data);

  __attribute__ ((weak))
  bool sysex_process_user(uint8_t length, uint8_t * data);

  enum MESSAGE_TYPE {
      MT_GET_DATA =      0x10, // Get data from keyboard
      MT_GET_DATA_ACK =  0x11, // returned data to process (ACK)
      MT_SET_DATA =      0x20, // Set data on keyboard
      MT_SET_DATA_ACK =  0x21, // returned data to confirm (ACK)
      MT_SEND_DATA =     0x30, // Sending data/action from keyboard
      MT_SEND_DATA_ACK = 0x31, // returned data/action confirmation (ACK)
      MT_EXE_ACTION =    0x40, // executing actions on keyboard
      MT_EXE_ACTION_ACK =0x41, // return confirmation/value (ACK)
      MT_TYPE_ERROR =    0x80 // type not recofgnised (ACK)
  };

  enum DATA_TYPE {
      DT_NONE = 0x00,
      DT_HANDSHAKE,
      DT_DEFAULT_LAYER,
      DT_CURRENT_LAYER,
      DT_KEYMAP_OPTIONS,
      DT_BACKLIGHT,
      DT_RGBLIGHT,
      DT_UNICODE,
      DT_DEBUG,
      DT_AUDIO,
      DT_QUANTUM_ACTION,
      DT_KEYBOARD_ACTION,
      DT_USER_ACTION,

  };


  #define MT_GET_DATA(data_type, data, length) send_bytes_sysex(MT_GET_DATA, data_type, data, length)
  #define MT_GET_DATA_ACK(data_type, data, length) send_bytes_sysex(MT_GET_DATA_ACK, data_type, data, length)
  #define MT_SET_DATA(data_type, data, length) send_bytes_sysex(MT_SET_DATA, data_type, data, length)
  #define MT_SET_DATA_ACK(data_type, data, length) send_bytes_sysex(MT_SET_DATA_ACK, data_type, data, length)
  #define MT_SEND_DATA(data_type, data, length) send_bytes_sysex(MT_SEND_DATA, data_type, data, length)
  #define MT_SEND_DATA_ACK(data_type, data, length) send_bytes_sysex(MT_SEND_DATA_ACK, data_type, data, length)
  #define MT_EXE_ACTION(data_type, data, length) send_bytes_sysex(MT_EXE_ACTION, data_type, data, length)
  #define MT_EXE_ACTION_ACK(data_type, data, length) send_bytes_sysex(MT_EXE_ACTION_ACK, data_type, data, length)

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
