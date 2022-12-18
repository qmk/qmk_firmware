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

#include "i2c.h"

static const uint8_t LPME_ADDR_LIST[] = {
    I2C_7BIT_ADDR(0x20),
    I2C_7BIT_ADDR(0x74),
    I2C_7BIT_ADDR(0x24),
};

MSCMD_USER_RESULT usrcmd_lpme_test(MSOPT *msopt, MSCMD_USER_OBJECT usrobj)
{
    static const uint8_t lpme_pin_def[24] = {
        0, // pin number in config starts from 1
        0, 1, 16, 16, 16, 16,
        2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13,
        14, 15, 16, 16, 16
    };
    uint8_t pin;
    uint8_t res = 0;
    uint8_t res_temp;

    uint8_t send[2] = {0x00, 0x00};

    for (int idx=1; idx<24; idx++)
    {
        if (lpme_pin_def[idx] != 16) {
            setPinInputHigh(idx);
        }
    }

    i2c_init();

    uint8_t lpme_addr = 0xff;
    // find lpme version
    for (int idx = 0; idx < sizeof(LPME_ADDR_LIST); idx++) {
        res = i2c_writeReg(LPME_ADDR_LIST[idx], 0x06, send, 2, 0);
        if (res == 0) {
            lpme_addr = LPME_ADDR_LIST[idx];
            xprintf("LPME ADDR:0x%2X\n", lpme_addr);
            break;
        }
    }

    if (lpme_addr == 0xff) {
        xprintf("LPME not found\n");
        i2c_uninit();

        setPinInputHigh(5);
        setPinInputHigh(6);

        return 1;
    }

    // set all port output
    res |= i2c_writeReg(lpme_addr, 0x06, send, 2, 0);

    send[0] = 0xFF;
    send[1] = 0xFF;

    for (int idx=1; idx<24; idx++)
    {
        if (lpme_pin_def[idx]==16) {
            continue;
        }

        pin = lpme_pin_def[idx];
        if (pin < 8) {
            send[0] &= ~(1<<pin);
        }
        else {
            send[1] &= ~(1<<(pin-8));
        }

        res |= i2c_writeReg(lpme_addr, 0x02, send, 2, 0);

        for (int bmp=1; bmp<24; bmp++)
        {
            if (lpme_pin_def[bmp]==16) {
                continue;
            }

            if (bmp == idx) {
                res_temp = (readPin(bmp) != 0);
            } else {
                res_temp = (readPin(bmp) == 0);
            }

            if (res_temp != 0) {
                xprintf("NG:lpme:%02x bmp:%02x\r\n", idx, bmp);
                res = 1;
            }

        }

        if (pin < 8) {
            send[0] |= (1<<pin);
        }
        else {
            send[1] |= (1<<(pin-8));
        }
    }

    i2c_writeReg(lpme_addr, 0x02, send, 2, 0);


    i2c_uninit();

    setPinInputHigh(5);
    setPinInputHigh(6);

    if (res == 0) {
        xprintf("OK\n");
    }

    return 0;
}
