/*
Copyright 2019 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "bmp.h"
#include "bmp_config.h"
#include "bmp_encoder.h"
#include "bmp_custom_keycode.h"
#include "bmp_process_extended_keycode.h"
#include "bmp_indicator_led.h"
#include "keycode_str_converter.h"

#include <stdint.h>
#include "quantum.h"
#include "keyboard.h"
#include "matrix.h"
#include "host.h"
#include "led.h"
#include "keycode.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "command.h"
#include "util.h"
#include "sendchar.h"
#include "eeconfig.h"
#include "backlight.h"
#include "action_layer.h"
#ifdef BOOTMAGIC_ENABLE
#   include "bootmagic.h"
#else
#   include "magic.h"
#endif
#ifdef MOUSEKEY_ENABLE
#   include "mousekey.h"
#endif
#ifdef PS2_MOUSE_ENABLE
#   include "ps2_mouse.h"
#endif
#ifdef SERIAL_MOUSE_ENABLE
#   include "serial_mouse.h"
#endif
#ifdef ADB_MOUSE_ENABLE
#   include "adb.h"
#endif
#ifdef RGBLIGHT_ENABLE
#   include "rgblight.h"
#endif
#ifdef STENO_ENABLE
#   include "process_steno.h"
#endif
#ifdef FAUXCLICKY_ENABLE
#   include "fauxclicky.h"
#endif
#ifdef SERIAL_LINK_ENABLE
#   include "serial_link/system/serial_link.h"
#endif
#ifdef VISUALIZER_ENABLE
#   include "visualizer/visualizer.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
#   include "pointing_device.h"
#endif
#ifdef MIDI_ENABLE
#   include "process_midi.h"
#endif
#ifdef HD44780_ENABLE
#   include "hd44780.h"
#endif
#ifdef QWIIC_ENABLE
#   include "qwiic.h"
#endif
#ifdef OLED_DRIVER_ENABLE
    #include "oled_driver.h"
#endif
#ifdef VELOCIKEY_ENABLE
  #include "velocikey.h"
#endif

#include "keycode_str_converter.h"
#include "config_file_util.h"
#include "apidef.h"
#include "cli.h"
#include "bmp_matrix.h"

#ifndef DISABLE_MSC
#define DISABLE_MSC 0
#endif

#ifndef BMP_FORCE_SAFE_MODE
#define BMP_FORCE_SAFE_MODE false
#endif


void bmp_action_exec(keyevent_t event)
{
    bmp_action_exec_impl(event);
    action_exec(event);
}

static int sleep_enter_counter = -1;
int reset_counter = -1;

/** \brief Keyboard task: Do keyboard routine jobs
 *
 * Do routine keyboard jobs:
 *
 * * scan matrix
 * * handle mouse movements
 * * run visualizer code
 * * handle midi commands
 * * light LEDs
 *
 * This is repeatedly called as fast as possible.
 */
void bmp_keyboard_task(void)
{
    static matrix_row_t matrix_prev[32];
    static uint8_t led_status = 0;
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;
#ifdef QMK_KEYS_PER_SCAN
    uint8_t keys_processed = 0;
#endif

    uint32_t key_event_cnt = matrix_scan();

    bmp_encoder_read(get_bmp_encoder_config(), key_event_cnt);

    const bmp_api_config_t * config = BMPAPI->app.get_config();

    if (is_keyboard_master()) {
        for (uint8_t r = 0; r < config->matrix.rows; r++) {
            matrix_row = matrix_get_row(r);
            matrix_change = matrix_row ^ matrix_prev[r];
            if (matrix_change) {
#ifdef MATRIX_HAS_GHOST
                if (has_ghost_in_row(r, matrix_row)) { continue; }
#endif
                if (debug_matrix) matrix_print();
                for (uint8_t c = 0; c < config->matrix.cols; c++) {
                    if (matrix_change & ((matrix_row_t)1<<c)) {
                        bmp_action_exec((keyevent_t){
                            .key = (keypos_t){ .row = r, .col = c },
                            .pressed = (matrix_row & ((matrix_row_t)1<<c)),
                            .time = (timer_read() | 1) /* time should not be 0 */
                        });
                        // record a processed key
                        matrix_prev[r] ^= ((matrix_row_t)1<<c);
#ifdef QMK_KEYS_PER_SCAN
                        // only jump out if we have processed "enough" keys.
                        if (++keys_processed >= QMK_KEYS_PER_SCAN)
#endif
                        // process a key per task call
                        goto MATRIX_LOOP_END;
                    }
                }
            }
        }
    }
    // call with pseudo tick event when no real key event.
#ifdef QMK_KEYS_PER_SCAN
    // we can get here with some keys processed now.
    if (!keys_processed)
#endif
    bmp_action_exec(TICK);

MATRIX_LOOP_END:

#ifdef QWIIC_ENABLE
    qwiic_task();
#endif

#ifdef OLED_DRIVER_ENABLE
    oled_task();
#ifndef OLED_DISABLE_TIMEOUT
    // Wake up oled if user is using those fabulous keys!
    if (ret)
        oled_on();
#endif
#endif

#ifdef MOUSEKEY_ENABLE
    // mousekey repeat & acceleration
    mousekey_task();
#endif

#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_task();
#endif

#ifdef SERIAL_MOUSE_ENABLE
    serial_mouse_task();
#endif

#ifdef ADB_MOUSE_ENABLE
    adb_mouse_task();
#endif

#ifdef SERIAL_LINK_ENABLE
	serial_link_update();
#endif

#ifdef VISUALIZER_ENABLE
    visualizer_update(default_layer_state, layer_state, visualizer_get_mods(), host_keyboard_leds());
#endif

#ifdef POINTING_DEVICE_ENABLE
    pointing_device_task();
#endif

#ifdef MIDI_ENABLE
    midi_task();
#endif

#ifdef VELOCIKEY_ENABLE
    if (velocikey_enabled()) { velocikey_decelerate();  }
#endif

    // update LED
    if (led_status != host_keyboard_leds()) {
        led_status = host_keyboard_leds();
        keyboard_set_leds(led_status);
    }

    // sleep flag check
    if (sleep_enter_counter > 0)
    {
        sleep_enter_counter--;
        if (sleep_enter_counter == 0)
        {
            BMPAPI->app.enter_sleep_mode();
        }
    }

    // reset flag check
    if (reset_counter > 0)
    {
        reset_counter--;
        if (reset_counter == 0)
        {
            // reset without safemode flag
            BMPAPI->app.reset(0);
        }
    }
}

bmp_error_t nus_rcv_callback(const uint8_t* dat, uint32_t len)
{
    if (len == sizeof(rgblight_syncinfo_t))
    {
        rgblight_update_sync((rgblight_syncinfo_t*)dat, false);
    }
    return BMP_OK;
}

bmp_error_t bmp_state_change_cb(bmp_api_event_t event)
{
  switch (event)
  {
    case USB_CONNECTED:
      update_config_files();
      break;

    case BLE_ADVERTISING_START:
      bmp_indicator_set(INDICATOR_ADVERTISING, 0);
      break;

    case BLE_ADVERTISING_STOP:
      bmp_indicator_set(INDICATOR_TURN_OFF, 0);
      sleep_enter_counter = 1;
      break;

    case BLE_CONNECTED:
      bmp_indicator_set(INDICATOR_CONNECTED, 0);
      break;

    default:
      break;
  }
  return BMP_OK;
}

static bool checkKeyIsPressedOnStartup(bmp_api_config_t const * const config, uint8_t row, uint8_t col)
{
  int8_t low_side_pin, high_side_pin;
  if (config->matrix.diode_direction == MATRIX_COL2ROW
    || config->matrix.diode_direction == MATRIX_COL2ROW2COL
    || config->matrix.diode_direction == MATRIX_COL2ROW_LPME) {
    high_side_pin = col;
    low_side_pin = row;
  }
  else if (config->matrix.diode_direction == MATRIX_ROW2COL
    || config->matrix.diode_direction == MATRIX_ROW2COL2ROW
    || config->matrix.diode_direction == MATRIX_ROW2COL_LPME) {
    high_side_pin = row;
    low_side_pin = col;
  }
  else {
    // return default value
    return false;
  }

  setPinInput(high_side_pin);
  setPinOd(low_side_pin);
  writePinLow(low_side_pin);

  uint8_t pin_state = readPin(high_side_pin);

  writePinLow(low_side_pin);

  return pin_state == 0;
}

static inline bool checkSafemodeFlag(bmp_api_config_t const * const config)
{
    return checkKeyIsPressedOnStartup(config, config->matrix.row_pins[0],
            config->matrix.col_pins[0]);
}

#if defined(ALLOW_MSC_ROW_PIN) && defined(ALLOW_MSC_COL_PIN)
static inline bool checkMscDisableFlag(bmp_api_config_t const * const config)
{
  if (checkKeyIsPressedOnStartup(config,
    ALLOW_MSC_ROW_PIN, ALLOW_MSC_COL_PIN) == 0) {
    // enable MSC
    return false;
  } else {
    // disable MSC
    return true;
  }
}
#endif

static bool has_ble = true;
static bool has_usb = true;
static bool is_safe_mode_ = false;

bool is_safe_mode() { return is_safe_mode_; }

void bmp_init()
{

  if (BMPAPI->api_version != API_VERSION)
  {
    BMPAPI->bootloader_jump();
  }

  BMPAPI->logger.init();
  BMPAPI->logger.info("logger init");
  static const bmp_api_config_t default_config = {
      .version = CONFIG_VERSION,
      .mode = BMP_DEFAULT_MODE == 0 ? SINGLE:
                BMP_DEFAULT_MODE == 1 ? SPLIT_MASTER:
                BMP_DEFAULT_MODE == 2 ? SPLIT_SLAVE : SINGLE,
      .device_info = {PRODUCT_ID, VENDOR_ID,
        STR(PRODUCT), STR(MANUFACTURER), STR(DESCRIPTION)},
      .matrix = {
          .rows = MATRIX_ROWS_DEFAULT,
          .cols = MATRIX_COLS_DEFAULT,
          .device_rows = THIS_DEVICE_ROWS,
          .device_cols = THIS_DEVICE_COLS,
          .debounce = 1,
          .is_left_hand = IS_LEFT_HAND ? 1:0,
          .diode_direction = DIODE_DIRECTION == ROW2COL ? 1:0,
          .row_pins = MATRIX_ROW_PINS,
          .col_pins = MATRIX_COL_PINS,
          .layout = MATRIX_LAYOUT,
      },
      .param_peripheral = {60, 30, 7},
      .param_central = {60, 30, 7},
      .led = {.pin = RGB_DI_PIN, .num = RGBLED_NUM_DEFAULT},
      .keymap = {.locale = KEYMAP_PRIOR_LOCALE, .use_ascii = KEYMAP_ASCII}
  };

  is_safe_mode_ = (BMPAPI->app.init(&default_config) > 0);

  const bmp_api_config_t * config = BMPAPI->app.get_config();


  if (checkSafemodeFlag(config) || BMP_FORCE_SAFE_MODE)
  {
    // start in safe mode
    BMPAPI->app.set_config(&default_config);
    config = &default_config;
    is_safe_mode_ = true;
  }

  BMPAPI->usb.set_msc_write_cb(msc_write_callback);
  BMPAPI->app.set_state_change_cb(bmp_state_change_cb);

  uint16_t vcc_mv = BMPAPI->app.get_vcc_mv();
  int32_t battery_level = 1;
  if (vcc_mv > 2700) {
    battery_level = 3;
  }
  else if (vcc_mv > 2400) {
    battery_level = 2;
  }

  bmp_indicator_set(INDICATOR_BATTERY, battery_level);


  if (!is_safe_mode_) {
#if defined(ALLOW_MSC_ROW_PIN) && defined(ALLOW_MSC_COL_PIN)
    BMPAPI->usb.init(config, checkMscDisableFlag(config));
#else
    BMPAPI->usb.init(config, DISABLE_MSC);
#endif
  } else {
      BMPAPI->usb.init(config, DISABLE_MSC);
  }

  BMPAPI->ble.init(config);

  BMPAPI->logger.info("usb init");
  cli_init();

  bmp_api_keymap_info_t keymap_info;
  BMPAPI->app.get_keymap_info(&keymap_info);
  if (keymap_info.len == 0)
  {
    BMPAPI->app.set_keymap((uint16_t*)keymaps, keymaps_len(), keymap_info.layout_name); // load default keymap
    BMPAPI->app.get_keymap_info(&keymap_info);
  }

  if (config->mode == SPLIT_SLAVE)
  {
    BMPAPI->ble.set_nus_rcv_cb(nus_rcv_callback);
  }

  load_ex_keycode_file(); // load exkc before tapping_term
  load_tapping_term_file();
  load_eeprom_emulation_file();
  load_encoder_config_file();

  if (config->mode == WEBNUS_CONFIG)
  {
    update_config_files();
    BMPAPI->web_config.set_rcv_callback(webnus_write_callback);
    has_ble = false;
  }
  else if ((config->mode == SINGLE || config->mode == SPLIT_MASTER) &&
    config->startup == 1)
  {
    BMPAPI->ble.advertise(255);
  }

  BMPAPI->usb.enable();
  BMPAPI->logger.info("usb enable");
}

static bool usb_enabled = true;
static bool ble_enabled = true;

bool get_ble_enabled() { return ble_enabled & has_ble; }
void set_ble_enabled(bool enabled) { ble_enabled = enabled; }
bool get_usb_enabled() { return usb_enabled & has_usb; }
void set_usb_enabled(bool enabled) { usb_enabled = enabled; }

bool process_record_user_bmp(uint16_t keycode, keyrecord_t *record)
{
  char str[16];

  switch (keycode) {
    case xEISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;

    case xKANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;

    default:
      break;
  }

  if (record->event.pressed) {
    switch (keycode) {
      case BLE_DIS:
        set_ble_enabled(false);
        return false;
      case BLE_EN:
        set_ble_enabled(true);
        return false;
      case USB_DIS:
        set_usb_enabled(false);
        return false;
      case USB_EN:
        set_usb_enabled(true);
        return false;
      case SEL_BLE:
        set_usb_enabled(false);
        set_ble_enabled(true);
        return false;
      case SEL_USB:
        set_ble_enabled(false);
        set_usb_enabled(true);
        return false;
      case ADV_ID0...ADV_ID7:
        BMPAPI->ble.advertise(keycode - ADV_ID0);
        return false;
      case AD_WO_L:
        BMPAPI->ble.advertise(255);
        return false;
      case DEL_ID0...DEL_ID7:
        BMPAPI->ble.delete_bond(keycode - DEL_ID0);
        return false;
      case DELBNDS:
        BMPAPI->ble.delete_bond(255);
        return false;
      case ENT_DFU:
        BMPAPI->bootloader_jump();
        return false;
      case ENT_WEB:
        BMPAPI->web_config.enter();
        return false;
      case BATT_LV:
        snprintf(str, sizeof(str), "%4dmV", BMPAPI->app.get_vcc_mv());
        send_string(str);
        return false;
      case SAVE_EE:
        save_eeprom_emulation_file();
        return false;
      case DEL_EE:
        BMPAPI->app.delete_file(QMK_EE_RECORD);
        return false;
    }
  }
  else if (!record->event.pressed) {
    switch  (keycode) {
    case ENT_SLP:
    sleep_enter_counter = 10;
    return false;
    }
  }

  return true;
}

__attribute__((weak))uint32_t keymaps_len()
{
  return 0;
}

