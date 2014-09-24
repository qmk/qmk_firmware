/*
NeXT non-ADB Keyboard USB Converter
 
Copyright 2013, Benjamin Gould (bgould@github.com)

Based on:
TMK firmware code Copyright 2011,2012 Jun WAKO <wakojun@gmail.com>
Arduino code by "Ladyada" Limor Fried (http://ladyada.net/, http://adafruit.com/), released under BSD license

Timing reference thanks to http://m0115.web.fc2.com/ (dead link), http://cfile7.uf.tistory.com/image/14448E464F410BF22380BB
Pinouts thanks to http://www.68k.org/~degs/nextkeyboard.html
Keycodes from http://ftp.netbsd.org/pub/NetBSD/NetBSD-release-6/src/sys/arch/next68k/dev/

This software is licensed with a Modified BSD License.
All of this is supposed to be Free Software, Open Source, DFSG-free,
GPL-compatible, and OK to use in both free and proprietary applications.
Additions and corrections to this file are welcome.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in
  the documentation and/or other materials provided with the
  distribution.

* Neither the name of the copyright holders nor the names of
  contributors may be used to endorse or promote products derived
  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#define VENDOR_ID       0xBCBC
#define PRODUCT_ID      0xBCBC
#define DEVICE_VER      0x0500
#define MANUFACTURER    t.m.k.
#define PRODUCT         NeXT Keyboard to USB converter
#define DESCRIPTION     USB converter for NeXT non-ADB Keyboard

/* matrix size */
#define MATRIX_ROWS 12  // keycode bit: 3-0
#define MATRIX_COLS  8  // keycode bit: 6-4

//#define DEBUG_ON_INIT 1

//#define TEENSY_CONFIG 1
#define PRO_MICRO_CONFIG 1
//#define TMK_CONFIG 1

// comment out if you don't want the keyboard's LEDs to flash upon initialization
#define NEXT_KBD_INIT_FLASH_LEDS

//============= Start of Arduino Pro Micro Configuration ==============
#ifdef PRO_MICRO_CONFIG

// this is the debugging LED that flashes when a key is being pressed
// comment out in order to disable debugging LED
#define NEXT_KBD_LED1_PORT  PORTD
#define NEXT_KBD_LED1_PIN   PIND
#define NEXT_KBD_LED1_DDR   DDRD
#define NEXT_KBD_LED1_BIT   5

#define NEXT_KBD_LED1_ON    NEXT_KBD_LED1_PORT &= ~(1<<NEXT_KBD_LED1_BIT);
#define NEXT_KBD_LED1_OFF   NEXT_KBD_LED1_PORT |=  (1<<NEXT_KBD_LED1_BIT);

// reserved for future use
#define NEXT_KBD_LED2_PORT  PORTB
#define NEXT_KBD_LED2_PIN   PINB
#define NEXT_KBD_LED2_DDR   DDRB
#define NEXT_KBD_LED2_BIT   6

#define NEXT_KBD_LED2_ON    NEXT_KBD_LED2_PORT &= ~(1<<NEXT_KBD_LED2_BIT);
#define NEXT_KBD_LED2_OFF   NEXT_KBD_LED2_PORT |=  (1<<NEXT_KBD_LED2_BIT);

// corresponds to the Keyboard In wire on the NeXT connector
// (red wire in NeXT connector) - pin 2 on the Pro Micro
#define NEXT_KBD_OUT_PORT  PORTD
#define NEXT_KBD_OUT_PIN   PIND
#define NEXT_KBD_OUT_DDR   DDRD
#define NEXT_KBD_OUT_BIT   1

// corresponds to the Keyboard Out wire on the NeXT connector
// (orange wire in NeXT connector) - pin 3 on the Pro Micro
#define NEXT_KBD_IN_PORT   PORTD
#define NEXT_KBD_IN_PIN    PIND
#define NEXT_KBD_IN_DDR    DDRD
#define NEXT_KBD_IN_BIT    0

// this pin is an input for the power key on the NeXT keyboard
// as the keyboard is powered on this should be normally high;
// if it is pulled low it means the power button is being preseed
// (yellow wire in NeXT connector) - pin 4 on the Pro Micro
#define NEXT_KBD_PWR_PORT  PORTD
#define NEXT_KBD_PWR_PIN   PIND
#define NEXT_KBD_PWR_DDR   DDRD
#define NEXT_KBD_PWR_BIT   4

#endif
//============== End of Arduino Pro Micro Configuration ===============


//================ Start of Teensy 2.0 Configuration =================
#ifdef TEENSY_CONFIG

// this is the debugging LED that flashes when a key is being pressed
// comment out in order to disable debugging LED
#define NEXT_KBD_LED_PORT  PORTD
#define NEXT_KBD_LED_PIN   PIND
#define NEXT_KBD_LED_DDR   DDRD
#define NEXT_KBD_LED_BIT   6

#define NEXT_KBD_LED_ON  NEXT_KBD_LED_PORT |=  (1<<NEXT_KBD_LED_BIT);
#define NEXT_KBD_LED_OFF NEXT_KBD_LED_PORT &= ~(1<<NEXT_KBD_LED_BIT);

// corresponds to the Keyboard In wire on the NeXT connector
// (red wire in NeXT connector)
#define NEXT_KBD_OUT_PORT  PORTB
#define NEXT_KBD_OUT_PIN   PINB
#define NEXT_KBD_OUT_DDR   DDRB
#define NEXT_KBD_OUT_BIT   1

// corresponds to the Keyboard Out wire on the NeXT connector
// (orange wire in NeXT connector)
#define NEXT_KBD_IN_PORT   PORTB
#define NEXT_KBD_IN_PIN    PINB
#define NEXT_KBD_IN_DDR    DDRB
#define NEXT_KBD_IN_BIT    0

#endif
//================= End of Teensy 2.0 Configuration ==================


//================ Start of TMK converter Configuration =================
#ifdef TMK_CONFIG

// this is the debugging LED that flashes when a key is being pressed
// comment out in order to disable debugging LED
#define NEXT_KBD_LED1_PORT  PORTD
#define NEXT_KBD_LED1_PIN   PIND
#define NEXT_KBD_LED1_DDR   DDRD
#define NEXT_KBD_LED1_BIT   6

#define NEXT_KBD_LED1_ON    NEXT_KBD_LED1_PORT |=  (1<<NEXT_KBD_LED1_BIT);
#define NEXT_KBD_LED1_OFF   NEXT_KBD_LED1_PORT &= ~(1<<NEXT_KBD_LED1_BIT);

// corresponds to the Keyboard In wire on the NeXT connector
#define NEXT_KBD_OUT_PORT  PORTD
#define NEXT_KBD_OUT_PIN   PIND
#define NEXT_KBD_OUT_DDR   DDRD
#define NEXT_KBD_OUT_BIT   1

// corresponds to the Keyboard Out wire on the NeXT connector
#define NEXT_KBD_IN_PORT   PORTD
#define NEXT_KBD_IN_PIN    PIND
#define NEXT_KBD_IN_DDR    DDRD
#define NEXT_KBD_IN_BIT    0

// this pin is an input for the power key on the NeXT keyboard
// as the keyboard is powered on this should be normally high;
// if it is pulled low it means the power button is being preseed
#define NEXT_KBD_PWR_PORT  PORTD
#define NEXT_KBD_PWR_PIN   PIND
#define NEXT_KBD_PWR_DDR   DDRD
#define NEXT_KBD_PWR_BIT   4

#endif
//================= End of TMK converter Configuration ==================

/* key combination for command */
#define IS_COMMAND() ( \
    (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))|| \
    (keyboard_report->mods == (MOD_BIT(KC_RALT) | MOD_BIT(KC_RCTL)))  \
)
