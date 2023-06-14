/* Copyright 2019 kakunpc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#define USE_LED_RIPPLE_EFFECT
// #define RANDOM_RIPPLE_EFFECT

#include QMK_KEYBOARD_H
#include "lufa.h"

#ifdef USE_LED_RIPPLE_EFFECT
struct keybuf {
  char col, row;
  char frame;
};
struct keybuf keybufs[256];
unsigned char keybuf_begin, keybuf_end;

unsigned char r = 0;
unsigned char g = 112;
unsigned char b = 255;
int col, row;
#endif


enum layers{
    BASE = 0,
    COMMAND
};

#define KC_COMMAND_NUM    LT(COMMAND,KC_F13)
#define KC_COMMAND_KANA   LT(COMMAND,KC_F14)
#define KC_COMMAND        LT(COMMAND,KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_all(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_COMMAND_NUM, KC_SPC, KC_SPC, KC_SPC, KC_COMMAND_KANA, KC_RALT, MO(COMMAND),KC_RCTL),
    [COMMAND] = LAYOUT_all(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_BSPC,
        KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LCTL, KC_NO,  KC_NO, _______, KC_NO, RGB_MOD, KC_NO,  _______, KC_NO,  _______, KC_NO),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef USE_LED_RIPPLE_EFFECT
    col = record->event.key.col;
    row = record->event.key.row;
    if (record->event.pressed) {
      int end = keybuf_end;
      keybufs[end].col = col;
      keybufs[end].row = row;
      keybufs[end].frame = 0;
      keybuf_end ++;
    }
#endif
  return true;
}

void keyboard_post_init_user(void) {
#ifdef USE_LED_RIPPLE_EFFECT
    rgblight_enable_noeeprom();
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
#endif
}

#ifdef USE_LED_RIPPLE_EFFECT
int scan_count = -10;
int keys[] = { 14, 14, 13, 12, 11 };
int keys_sum[] = { 0, 14, 28, 41, 53 };
unsigned char rgb[14][5][3];
int row_max = 12;
int ToIndex(char _col, char _row) {
    return (_col * row_max) + _row;
}

void led_ripple_effect(void){
    if (scan_count == -1) {
      rgblight_enable_noeeprom();
      rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    } else if (scan_count >= 0 && scan_count < 5) {
      for (unsigned char c=keybuf_begin; c!=keybuf_end; c++) {
        int i = c;
        // FIXME:

        int index = ToIndex(keybufs[i].col,keybufs[i].row);
        int coll = 0;
        for(int s = 4; s >= 0; --s){
            if( index >= keys_sum[s]){
                coll = s;
                break;
            }
        }
        int roww = MAX(0,index - keys_sum[coll]);

        int y = scan_count;
        int dist_y = abs(y - coll);
        for (int x=0; x<keys[y]; x++) {
          int dist = abs(x - roww) + dist_y;
          if (dist <= keybufs[i].frame) {
            int elevation = MAX(0, (8 + dist - keybufs[i].frame)) << 2;
            if (elevation) {
              if ((rgb[x][y][0] != 255) && r) { rgb[x][y][0] = MIN(255, elevation + rgb[x][y][0]); }
              if ((rgb[x][y][1] != 255) && g) { rgb[x][y][1] = MIN(255, elevation + rgb[x][y][1]); }
              if ((rgb[x][y][2] != 255) && b) { rgb[x][y][2] = MIN(255, elevation + rgb[x][y][2]); }
            }
          }
        }
      }
    } else if (scan_count == 5) {
      for (unsigned char c=keybuf_begin; c!=keybuf_end; c++) {
        int i = c;
        if (keybufs[i].frame < 64) {
          keybufs[i].frame ++;
        } else {
          keybuf_begin ++;
        }
      }
    } else if (scan_count >= 6 && scan_count <= 10) {
      int y = scan_count - 6;
      for (int x=0; x<keys[y]; x++) {
        int at = keys_sum[y] + x;
        led[at].r = rgb[x][y][0];
        led[at].g = rgb[x][y][1];
        led[at].b = rgb[x][y][2];
      }
      rgblight_set();
    } else if (scan_count == 11) {
      memset(rgb, 0, sizeof(rgb));
    }
    scan_count++;
    if (scan_count >= 12) { scan_count = 0; }
}

#endif

void matrix_scan_user(void) {
#ifdef USE_LED_RIPPLE_EFFECT
#ifdef RANDOM_RIPPLE_EFFECT
    static int timer = 0;
    static int timeout = 300;
    timer++;
    if(timer > timeout){
      int end = keybuf_end;
      col = rand() % 6;
      row = rand() % 12;
      keybufs[end].col = col;
      keybufs[end].row = row;
      keybufs[end].frame = 0;
      keybuf_end ++;
      timer = rand() % timeout;
    }
#endif
    led_ripple_effect();
#endif
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
  oled_write_P(PSTR("Layer: "), false);
  switch (get_highest_layer(layer_state)) {
    case BASE:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case COMMAND:
      oled_write_P(PSTR("COMMAND\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding 'n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    return false;
}
#endif
