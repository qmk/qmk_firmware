// Copyright 2020-2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Raspberry Pi Pico  **************************
                    ====
         +----------====-----------+
         | GP0/UART0 TX       VBUS |
     C15 | GP1/UART0 Rx       VSYS |
         | GND                 GND |
     C14 | GP2              3V3_EN |
     C13 | GP3             3V3(out)|
         | GP4/I2C0 SDA   ADC_VREF |
         | GP5/I2C0 SCL       GP28 | C0
         | GND                 GND |
     C12 | GP6                GP27 | C1
     C11 | GP7                GP26 | C2
     C10 | GP8                 RUN |
     C9  | GP9                GP22 | C3
         | GND                 GND |
     C8  | GP10               GP21 | C4
      R0 | GP11               GP20 | C5
      R1 | GP12       SPIO TX/GP19 | C6
      R2 | GP13      SPIO SCK/GP18 | C7
         | GND                 GND |
      R3 | GP14      SPIO CSn/GP17 | DEBUG_MATRIX_SCAN
      R4 | GP15       SPIO RX/GP16 | DEBUG_MATRIX_DELAY
         +-------O----O----O-------+
               SWCLK GND SWDIO
https://datasheets.raspberrypi.com/pico/Pico-R3-A4-Pinout.pdf
************************************************/

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef DEBUG_CONFIG
#    define MATRIX_DEBUG_PIN GP17,GP16
#    include "../debug_config.h"
#endif
