/*

M4cs Keymap for dekuNukem/duckyPad QMK firmware

Copyright (C) 2020 Max Bridgland

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "stdio.h"
#include "raw_hid.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LOGO_SIZE 384

bool rgbToggled = false;
bool altToggled = false;
bool sysToggled = false;

enum layer_codes {
  RGB_LAYER = SAFE_RANGE,
  ALT_LAYER,
  SYS_LAYER,
  CLOCK_TOGGLE
};

#define MAC_1 LCTL(LALT(KC_MINS))
#define MAC_2 LCTL(LALT(KC_EQL))
#define MAC_3 LCTL(LALT(KC_LBRC))
#define MAC_4 LCTL(LALT(KC_RBRC))
#define MAC_5 LCTL(LALT(KC_BSLS))
#define MAC_6 LCTL(LALT(KC_SCLN))
#define MAC_7 LCTL(LALT(KC_QUOT))
#define MAC_8 LCTL(LALT(KC_COMM))
#define MAC_9 LCTL(LALT(KC_SLSH))

#define MAC_10 LCTL(LSFT(KC_MINS))
#define MAC_11 LCTL(LSFT(KC_EQL))
#define MAC_12 LCTL(LSFT(KC_SLSH))
#define MAC_13 LCTL(LSFT(KC_LBRC))
#define MAC_14 LCTL(LSFT(KC_RBRC))
#define MAC_15 LCTL(LSFT(KC_BSLS))
#define MAC_16 LCTL(LSFT(KC_SCLN))
#define MAC_17 LCTL(LSFT(KC_QUOT))
#define MAC_18 LCTL(LSFT(KC_COMM))

#define _DEFAULT 0
#define _RGB 1
#define _ALT 2
#define _SYS 3

float cpuFreq = 0;
int memPerc = 0;
int gpuLoad = 0;
int temp = 0;
int hour = 0;
int minute = 0;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
  ,=========================================.
  | Media Prev. | Media Play  | Media Next  |
  |=========================================|
  | Mute Sound  | Volume Do.  | Volume Up   |
  |=========================================|
  | Macro 1     | Macro 2     | Macro 3     |
  |=========================================|
  | Macro 4     | Macro 5     | Macro 6     |
  |=========================================| ,---------------------.
  | Macro 7     | Macro 8     | Sys. Info   | | RGB Menu | Alt Menu |
  `=========================================' `--------------------'
  */
  [_DEFAULT] = LAYOUT(
      KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK,
      KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,
      MAC_1, MAC_2, MAC_3,
      MAC_4, MAC_5, MAC_6,
      CLOCK_TOGGLE, MAC_8, SYS_LAYER,
      RGB_LAYER, ALT_LAYER
  ),
  /*
  ,=========================================.
  | Plain RGB   | Breathe RGB | Rainbow RGB |
  |=========================================|
  | Swirl RGB   | Speed Down  | Speed Up    |
  |=========================================|
  | Effect Up   | Sat. Down   | Sat. Up     |
  |=========================================|
  | Effect Down | Hue Down    | Hue Up      |
  |=========================================| ,----------------------.
  | Toggle RGB  | Brt. Down   | Brt. Up     | | Norm Menu | Alt Menu |
  `=========================================' `---------------------'
  */
  [_RGB] = LAYOUT(
      RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_RAINBOW,
      RGB_MODE_SWIRL, RGB_SPD, RGB_SPI,
      RGB_MOD, RGB_SAD, RGB_SAI,
      RGB_RMOD, RGB_HUD, RGB_HUI,
      RGB_TOG, RGB_VAD, RGB_VAI,
      RGB_LAYER, ALT_LAYER
  ),
  /*
  ,=========================================.
  | Macro 10    | Macro 11    | Macro 12    |
  |=========================================|
  | Undo        | Cut         | Copy        |
  |=========================================|
  | Paste       | Find        | Prnt Scrn.  |
  |=========================================|
  | Macro 13    | Macro 14    | Macro 15    |
  |=========================================| ,----------------------.
  | Macro 16    | Macro 17    | Sys. Info   | | Norm Menu | Alt Menu |
  `=========================================' `---------------------'
  */
  [_ALT] = LAYOUT(
      MAC_10, MAC_11, MAC_12,
      KC_UNDO, KC_CUT, KC_COPY,
      KC_PASTE, KC_FIND, KC_PSCR,
      MAC_13, MAC_14, MAC_15,
      CLOCK_TOGGLE, MAC_17, SYS_LAYER,
      RGB_LAYER, ALT_LAYER
  ),
  [_SYS] = LAYOUT(
      KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO,
      CLOCK_TOGGLE, KC_NO, SYS_LAYER,
      RGB_LAYER, ALT_LAYER
  )
};

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,128,128,128,128,128,  0,  0,252,252,252,  0,  0,  0,128,128,128,  0,  0,  0,  0,  0,128,128,128,  0,  0,  0,  0,  0,128,128,128,128,128,  0,  0,  0,  0,  0,252,252,252,  0,  0,  0,  0,  0,128,128,128,128,128,128,  0,  0,  0,  0,  0,  0,128,128,128,128,  0,248,248,248, 56, 56, 56, 56, 56, 56,120,240,224,192,  0,  0,128,128,128,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,128,128,  0,  0,252,252,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,248,254,255,143,  7,  3,  3,  3,  7,142,255,255,255,  0,  0,  0,255,255,255,  0,  0,  0,  0,  0,255,255,255,  0,248,254,255,143,  7,  3,  3,  3,  3,143,  7,  2,  0,  0,255,255,255,240,120,252,254,231,131,  1,  0,  1,  7, 63,254,240,192,  0,224,252,127, 31,  3,  0,  0,255,255,255,112,112,112,112,112,112, 56, 63, 31, 15,193,231,243,115, 51, 51, 51, 55,255,255,252,  0,  0,248,254,255,143,  7,  3,  3,  3,  7,142,255,255,255,  0,  0,  0,  0,192,240,240, 96, 48, 48,  0, 12, 12,134,198,230,126, 60,  0,  0,  0,
        0,  0,  3,  7, 15, 15, 14, 14, 14,  7,  3, 15, 15, 15,  0,  0,  0,  3,  7, 15, 15, 14, 14,  6,  3, 15, 15, 15,  0,  0,  3,  7,  7, 15, 14, 14, 14, 14,  7,  7,  2,  0,  0, 15, 15, 15,  0,  0,  0,  1,  3, 15, 15, 12,136,224,224,224,247,127,127, 31,  3,  0,  0,  0,  0,  0, 15, 15, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 14, 14, 14,  6,  3, 15, 15, 15,  0,  0,  0,  3,  7, 15, 15, 14, 14, 14,  7,  3, 15, 15, 15,  0,  0,  0, 12, 15,  7,  0,  0,  0, 12, 14, 15, 15, 13, 13, 12, 12,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

char* make_menu_text(void){
  char *s = malloc((30 * 4) * sizeof(*s));
  int width = 3;
  snprintf(s, 120, "%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s",
    width, MT_0_0, width, MT_0_1, width, MT_0_2,
    width, MT_0_3, width, MT_0_4, width, MT_0_5,
    width, MT_0_6, width, MT_0_7, width, MT_0_8,
    width, MT_0_9, width, MT_0_10, width,MT_0_11,
    width, MT_0_12, width, MT_0_13, width, MT_0_14
  );
  return s;
};

char* make_rgb_text(void){
  char *s = malloc((30 * 4) * sizeof(*s));
  int width = 3;
  snprintf(
    s, 120, "%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s",
    width, MT_1_0, width, MT_1_1, width, MT_1_2,
    width, MT_1_3, width, MT_1_4, width, MT_1_5,
    width, MT_1_6, width, MT_1_7, width, MT_1_8,
    width, MT_1_9, width, MT_1_10, width,MT_1_11,
    width, MT_1_12, width, MT_1_13, width, MT_1_14
  );
  return s;
};

char* make_alt_text(void){
  char *s = malloc((30 * 4) * sizeof(*s));
  int width = 3;
  snprintf(
    s,  120, "%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s",
    width, MT_2_0, width, MT_2_1, width, MT_2_2,
    width, MT_2_3, width, MT_2_4, width, MT_2_5,
    width, MT_2_6, width, MT_2_7, width, MT_2_8,
    width, MT_2_9, width, MT_2_10, width,MT_2_11,
    width, MT_2_12, width, MT_2_13, width, MT_2_14
  );
  return s;
};

char* make_sys_info_text(void) {
  char *s = malloc((30 * 5) * sizeof(*s));
  snprintf(s, 150, "    cpu: %.1fGHz\n      mem: %d%%\n      gpu: %d%%\n     temp: %dC\n    time: %d:%d", cpuFreq, memPerc, gpuLoad, temp, hour, minute);
  return s;
};


bool oled_task_user(void) {
  if (!sysToggled) {
    render_logo();
    oled_set_cursor(0,3);
    if (rgbToggled) {
        char *s = make_rgb_text();
        oled_write_ln(s, false);
        free(s);
    } else if (altToggled) {
        char *s = make_alt_text();
        oled_write_ln(s, false);
        free(s);
    } else {
        char *s = make_menu_text();
        oled_write_ln(s, false);
        free(s);
    }
  }
    return false;
};

int concat(int a, int b) {
    char s1[20];
    char s2[20];
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);
    strcat(s1, s2);
    int c = atoi(s1);

    return c;
};

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (sysToggled) {
        oled_clear();
        render_logo();
        int i;
        int stepper = 0;
        int toWrite;
        for (i=0; i < length; i++) {
            if (data[i] != 13) {
                toWrite = concat(toWrite, data[i]);
            } else {
                switch (stepper) {
                    case 0:
                        cpuFreq = floor(100*toWrite)/10000;
                        break;
                    case 1:
                        memPerc = toWrite / 10;
                        break;
                    case 2:
                        gpuLoad = toWrite;
                        break;
                    case 3:
                        temp = toWrite;
                        break;
                    case 4:
                        hour = toWrite;
                        break;
                    case 5:
                        minute = toWrite;
                        break;
                    default:
                        break;
                }
                toWrite = 0;
                stepper++;
            }
        }
        oled_set_cursor(0,3);
        char *s = make_sys_info_text();
        oled_write_ln(s, false);
        free(s);
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_LAYER:
      if (record->event.pressed) {
        if (rgbToggled) {
          rgbToggled = false;
          altToggled = false;
          sysToggled = false;
          oled_clear();
          layer_clear();
        } else {
          rgbToggled = true;
          altToggled = false;
          sysToggled = false;
          layer_on(_RGB);
        }
      }
      return false;
    case ALT_LAYER:
      if (record->event.pressed) {
        if (altToggled) {
          rgbToggled = false;
          altToggled = false;
          sysToggled = false;
          oled_clear();
          layer_clear();
        } else {
          rgbToggled = false;
          sysToggled = false;
          altToggled = true;
          layer_on(_ALT);
        }
      }
      return false;
    case SYS_LAYER:
        if (record->event.pressed) {
            if (sysToggled) {
                rgbToggled = false;
                altToggled = false;
                sysToggled = false;
                oled_clear();
                layer_clear();
            } else {
                rgbToggled = false;
                sysToggled = true;
                altToggled = false;
                layer_on(_SYS);
            }
        }
    default:
      return true;
  }
  return false;
};
