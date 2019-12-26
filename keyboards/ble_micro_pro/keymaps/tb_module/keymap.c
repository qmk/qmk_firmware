/* Copyright 2019 sekigon-gonnoc
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
#include QMK_KEYBOARD_H
#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"
#include "i2c.h"
#include "pointing_device.h"

uint8_t tb_button    = 0;
uint8_t tb_scrl_flag = false;
report_mouse_t mouse_rep;
void           send_mouse(report_mouse_t *report);

static inline int sgn(int16_t x) {
    if (x > 0) {
        return 1;
    } else if (x < 0) {
        return -1;
    } else {
        return 0;
    }
}


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    LOWER = BMP_SAFE_RANGE,
    RAISE,
};

const key_string_map_t custom_keys_user =
{
    .start_kc = LOWER,
    .end_kc = RAISE,
    .key_strings = "LOWER\0RAISE\0"
};

enum layers {
    _BASE, _LOWER, _RAISE, _ADJUST
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{
    KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I,
        KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S
    }}
};

uint32_t keymaps_len() {
  return sizeof(keymaps)/sizeof(uint16_t);
}

typedef struct {
  int16_t x;
  int16_t y;
  uint8_t surface;
  uint8_t motion_flag;
} trackball_info_t;

static inline void to_tb_info(trackball_info_t* const tb_info, uint8_t dat1,
                              uint8_t dat2, uint8_t dat3) {
  tb_info->x = (int16_t)(((int16_t)dat1 << 4) | (((int16_t)dat3 >> 4) << 12));
  tb_info->y = (int16_t)(((int16_t)dat2 << 4) | (((int16_t)dat3 & 0x0F) << 12));
}

void  matrix_init_user() {
    // i2c_init();
}

void  matrix_scan_user() {
    static uint8_t rcv[5] = {0};
    static int cnt;
    trackball_info_t tb_info;
    i2c_init();
    i2c_receive(I2C_7BIT_ADDR(0x1E), rcv, 5, 100);
    i2c_uninit();

    to_tb_info(&tb_info, rcv[2], rcv[3], rcv[4]);
    tb_info.motion_flag = rcv[1];
    //
    if (++cnt == 3) {
        cnt = 0;
        dprintf("0x%02x %5d  %5d\n", rcv[1], tb_info.x, tb_info.y);
    }

    int16_t tb_div = 64;

    static int16_t          x_surplus, y_surplus;
    bool                    btn_change;

    btn_change        = (mouse_rep.buttons != tb_button);
    mouse_rep.buttons = tb_button;

    if (layer_state == 0) {
        tb_scrl_flag = 0;
        tb_div = 64;
    } else if (layer_state == 0b100) {
        tb_scrl_flag = 1;
        tb_div = 64;
    } else if (layer_state == 0b10) {
        tb_scrl_flag = 0;
        tb_div = 256;
    }

    if (!tb_scrl_flag) {
        mouse_rep.h = 0;
        mouse_rep.v = 0;
        mouse_rep.x = (tb_info.x + x_surplus) / tb_div;
        mouse_rep.y = (tb_info.y + y_surplus) / tb_div;

        if (tb_info.x > 400 || tb_info.x < -400) {
            mouse_rep.x *= 2;
        }

        if (tb_info.y > 400 || tb_info.y < -400) {
            mouse_rep.y *= 2;
        }


        x_surplus = (tb_info.x + x_surplus) % tb_div;
        y_surplus = (tb_info.y + y_surplus) % tb_div;
    } else {
        mouse_rep.h = 1 * sgn((tb_info.x + x_surplus) / tb_div);
        mouse_rep.v = -1 * sgn((tb_info.y + y_surplus) / tb_div);
        mouse_rep.x = 0;
        mouse_rep.y = 0;

        x_surplus = (tb_info.x + x_surplus) % tb_div;
        y_surplus = (tb_info.y + y_surplus) % tb_div;
    }

    if (btn_change || (tb_info.motion_flag & 0x80)) {
        pointing_device_set_report(mouse_rep);
    }

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool continue_process = process_record_user_bmp(keycode, record);
  if (continue_process == false)
  {
    return false;
  }

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    default:
      break;
  }

  return true;
}
