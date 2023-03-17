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
#include "bmp_pin_def.h"
#include "pointing_device.h"
#include "keycode_str_converter.h"
#include "pmw3360.h"
#include "lib_keyball.h"

#define F4 PIN20

//#include "rgblight.h"
//extern rgblight_config_t rgblight_config;

bool IsReady = false; //トラボ持ってるか
report_mouse_t mouse_report;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes
{
  CPI_I100 = BMP_SAFE_RANGE,
  CPI_D100,
  CPI_I1K,
  CPI_D1K,
  SCRL_TO,
  SCRL_MO,
  SCRL_DVI,
  SCRL_DVD,
  MY_MS_BTN1, // 左クリック用
  MY_MS_BTN2, // 右クリック用
  MY_MS_BTN3, // ボタン3用
  MY_MS_SCR,  // スクロール
  KC_TO_CLICKABLE_INC,
  KC_TO_CLICKABLE_DEC,
  KC_TO_CLICKABLE_TIME_INC,
  KC_TO_CLICKABLE_TIME_DEC,
  MY_SAFE_RANGE //
};

const key_string_map_t custom_keys_user =
    {
        .start_kc = CPI_I100,
        .end_kc = MY_SAFE_RANGE,
        .key_strings = "CPI_I100\0CPI_D100\0CPI_I1K\0CPI_D1K\0SCRL_TO\0SCRL_MO\0SCRL_DVI\0SCRL_DVD\0MY_MS_BTN1\0MY_MS_BTN2\0MY_MS_BTN3\0MY_MS_SCR\0KC_TO_CLICKABLE_INC\0KC_TO_CLICKABLE_DEC\0KC_TO_CLICKABLE_TIME_INC\0KC_TO_CLICKABLE_TIME_DEC\0MY_SAFE_RANGE\0"};

enum layers
{
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I,
      KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S}}};

uint32_t keymaps_len()
{
  return sizeof(keymaps) / sizeof(uint16_t);
}

void pointing_device_init(void)
{
  IsReady = pmw3360_init();
  if (IsReady)
    pmw3360_reg_write(REG_Motion_Burst, 0);
}

// マウスポーリング
void pointing_device_task()
{
  pmw3360_motion_t data = {0};
  if (IsReady && pmw3360_motion_burst(&data))
  {
    if (!keyball_get_scroll_mode())
    {
      mouse_report.x = constrain_hid(data.y);
      mouse_report.y = constrain_hid(data.x);
      mouse_report.h = 0;
      mouse_report.v = 0;
    }
    else
    {
      mouse_report.x = 0;
      mouse_report.y = 0;
      keyball_motion_to_mouse_scroll(&mouse_report, data.x, data.y);
    }
    pointing_device_set_report(mouse_report);
    pointing_device_send();
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

  // BMPのキーコード処理用
  bool continue_process = process_record_user_bmp(keycode, record);
  if (continue_process == false)
  {
    return false;
  }

  switch(keycode){

    case SCRL_MO:
      keyball_set_scroll_mode(record->event.pressed);
      return false;

    case MY_MS_BTN1:
    case MY_MS_BTN2:
    case MY_MS_BTN3:
    {
      // マウスの状態取得とキーコード取得
      // btnのbitmapを考慮して、BTN4以降を追加する場合はBTN3と連続になるように規定要。
      mouse_report = pointing_device_get_report();
      uint8_t btn = 1 << (keycode - MY_MS_BTN1);

      // ドラッグ&ドロップ対応用
      if (record->event.pressed)
      {
        mouse_report.buttons |= btn;
      }
      else
      {
        mouse_report.buttons &= ~btn;
      }

      pointing_device_set_report(mouse_report);
      pointing_device_send();
      return false;
    }
  }

  if (record->event.pressed)
  {
    switch (keycode)
    {
    case CPI_I100:
      keyball_add_cpi(1);
      break;

    case CPI_D100:
      keyball_add_cpi(-1);
      break;

    case CPI_I1K:
      keyball_add_cpi(10);
      break;

    case CPI_D1K:
      keyball_add_cpi(-10);
      break;

    case SCRL_TO:
      keyball_scroll_toggle();
      break;

    case SCRL_DVI:
      keyball_add_scroll_div(1);
      break;
    case SCRL_DVD:
      keyball_add_scroll_div(-1);
      break;

    case MY_MS_SCR:

      return false;

    case KC_TO_CLICKABLE_INC:

      return false;

    case KC_TO_CLICKABLE_DEC:

      return false;

    case KC_TO_CLICKABLE_TIME_INC:

      return false;

    case KC_TO_CLICKABLE_TIME_DEC:

      return false;

    default:
      break;
    }
  }

  return true;
}
