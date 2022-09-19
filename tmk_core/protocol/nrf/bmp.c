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
#include "bmp_macro.h"
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
#include "action_layer.h"
#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif
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
#ifdef OLED_ENABLE
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

int sleep_enter_counter = -1;
int reset_counter = -1;
int bootloader_jump_counter = -1;

void bmp_mode_transition_check(void) {
    // sleep flag check
    if (sleep_enter_counter > 0)
    {
        sleep_enter_counter--;
        if (sleep_enter_counter == 0)
        {
            bmp_enter_sleep();
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

    // bootloader jump flag check
    if (bootloader_jump_counter > 0) {
        bootloader_jump_counter--;
        if (bootloader_jump_counter == 0) {
            BMPAPI->bootloader_jump();
        }
    }
}

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
#ifndef PROCESS_MATRIX_REVERSE
        for (uint8_t r = 0; r < config->matrix.rows; r++) {
#else
        for (int r = config->matrix.rows - 1; r >= 0; r--) {
#endif
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

#ifdef OLED_ENABLE
    oled_task();
#ifndef OLED_DISABLE_TIMEOUT
    // Wake up oled if user is using those fabulous keys!
    if (key_event_cnt)
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

    bmp_macro_task();

    // update LED
    if (led_status != host_keyboard_leds()) {
        led_status = host_keyboard_leds();
        keyboard_set_leds(led_status);
    }

    // auto sleep check
    static uint32_t last_event_time = 0;
    uint32_t auto_sleep_timeout = BMPAPI->app.get_config()->reserved[2] * 10 *
                                  60 * 1000;  // * 10min * 60s/min * 1000ms/s

    if (auto_sleep_timeout && key_event_cnt == 0 && !is_usb_connected()) {
        if (timer_elapsed32(last_event_time) > auto_sleep_timeout) {
            sleep_enter_counter = 1;
        }
    } else {
        last_event_time = timer_read32();
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

static bool is_usb_connected_ = false;
static bool is_usb_powered_   = false;
static bool is_ble_connected_ = false;

bool is_usb_connected() { return is_usb_connected_; }
bool is_usb_powered() { return is_usb_powered_; }
bool is_ble_connected() { return is_ble_connected_; }

__attribute__((weak)) void bmp_state_change_cb_user(bmp_api_event_t event) {}
__attribute__((weak)) void bmp_state_change_cb_kb(bmp_api_event_t event) {
    bmp_state_change_cb_user(event);
}
void bmp_user_data_recv_cb_kb(uint8_t id, uint8_t data) {
    xprintf("Receive user data: id:%d, data:%d\n", id, data);
}

bmp_error_t bmp_state_change_cb(bmp_api_event_t event)
{
  switch (event)
  {
    case USB_CONNECTED:
        is_usb_powered_ = true;
        break;

    case USB_HID_READY:
        is_usb_powered_   = true;
        is_usb_connected_ = true;
        if (!is_ble_connected()) {
            select_usb();
        }
        update_config_files();
        break;

    case USB_DISCONNECTED:
        is_usb_powered_   = false;
        is_usb_connected_ = false;
        if (is_ble_connected()) {
            select_ble();
        }
        break;

    case BLE_ADVERTISING_START:
      bmp_indicator_set(INDICATOR_ADVERTISING, 0);
      break;

    case BLE_ADVERTISING_STOP:
      bmp_indicator_set(INDICATOR_TURN_OFF, 0);

      if (!is_usb_powered()) {
          sleep_enter_counter = 1;
      }
      break;

    case BLE_CONNECTED:
        is_ble_connected_ = true;
        if (!is_usb_connected()) {
            select_ble();
        }
        bmp_indicator_set(INDICATOR_CONNECTED, 0);
        break;

    case BLE_DISCONNECTED:
        is_ble_connected_ = false;
        // Disable below code because BLE could be disconnected unintentionally
        // if (is_usb_connected()) {
        //     select_usb();
        // }
        break;

    default:
      break;
  }

  bmp_state_change_cb_kb(event);

  return BMP_OK;
}

static void bmp_hid_raw_receive_cb(const uint8_t * data, uint8_t len) {
    // xprintf("<hidraw>receive %d bytes", len);
    static uint8_t via_data[32];
    if (len > sizeof(via_data) + 1) {
        xprintf("<hidraw>Too large packet");
        return;
    }

    memcpy(via_data, data, len - 1);

    bmp_via_receive_cb(via_data, len - 1, BMPAPI->usb.raw_send);
}

static void bmp_ble_raw_receive_cb(const uint8_t * data, uint8_t len) {
    xprintf("<hidraw>receive %d bytes\n", len);
    static uint8_t via_data[32];
    if (len > sizeof(via_data)) {
        xprintf("<hidraw>Too large packet");
        return;
    }

    memcpy(via_data, data, len);

    bmp_via_receive_cb(via_data, len, BMPAPI->ble.raw_send);
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

__attribute__((weak)) bool checkSafemodeFlag(bmp_api_config_t const * const config)
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

__attribute__((weak)) bool bmp_config_overwrite(
    bmp_api_config_t const* const config_on_storage,
    bmp_api_config_t* const       keyboard_config) {
    return false;
}

static bool has_ble = true;
static bool has_usb = true;
static bool is_safe_mode_ = false;

bool is_safe_mode() { return is_safe_mode_; }

const bmp_api_config_t default_config = {
    .version     = CONFIG_VERSION,
    .mode        = BMP_DEFAULT_MODE == 0   ? SINGLE
                   : BMP_DEFAULT_MODE == 1 ? SPLIT_MASTER
                   : BMP_DEFAULT_MODE == 2 ? SPLIT_SLAVE
                                           : SINGLE,
    .device_info = {PRODUCT_ID, VENDOR_ID, STR(PRODUCT), STR(MANUFACTURER),
                    STR(DESCRIPTION)},
    .matrix =
        {
            .rows            = MATRIX_ROWS_DEFAULT,
            .cols            = MATRIX_COLS_DEFAULT,
            .device_rows     = THIS_DEVICE_ROWS,
            .device_cols     = THIS_DEVICE_COLS,
            .debounce        = 1,
            .is_left_hand    = IS_LEFT_HAND ? 1 : 0,
            .diode_direction = DIODE_DIRECTION == ROW2COL ? 1 : 0,
            .row_pins        = MATRIX_ROW_PINS,
            .col_pins        = MATRIX_COL_PINS,
            .layout          = MATRIX_LAYOUT,
        },
    .param_peripheral = {60, 30, 7},
    .param_central    = {60, 30, 7},
    .led              = {.pin = RGB_DI_PIN, .num = RGBLED_NUM_DEFAULT},
    .keymap = {.locale = KEYMAP_PRIOR_LOCALE, .use_ascii = KEYMAP_ASCII},
#ifdef CONFIG_RESERVED
    .reserved = CONFIG_RESERVED
#endif
};

void bmp_init()
{

  if (BMPAPI->api_version != API_VERSION)
  {
    BMPAPI->bootloader_jump();
  }

  BMPAPI->logger.init();
  BMPAPI->logger.info("logger init");

  is_safe_mode_ = (BMPAPI->app.init(&default_config) > 0);

  const bmp_api_config_t * config = BMPAPI->app.get_config();


  if (checkSafemodeFlag(config) || BMP_FORCE_SAFE_MODE)
  {
    // start in safe mode
    BMPAPI->app.set_config(&default_config);
    config = &default_config;
    is_safe_mode_ = true;
  }


  bmp_api_config_t keyboard_config = default_config;

  if (bmp_config_overwrite(config, &keyboard_config)) {
    BMPAPI->app.set_config(&keyboard_config);
    config = &keyboard_config;
  }

  BMPAPI->usb.set_msc_write_cb(msc_write_callback);
  BMPAPI->app.set_state_change_cb(bmp_state_change_cb);
  BMPAPI->usb.set_raw_receive_cb(bmp_hid_raw_receive_cb);
  BMPAPI->ble.set_raw_receive_cb(bmp_ble_raw_receive_cb);

  uint16_t vcc_percent = BMPAPI->app.get_vcc_percent();
  int32_t battery_level = 1;

  if (vcc_percent > 70) {
    battery_level = 3;
  }
  else if (vcc_percent > 30) {
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
  BMPAPI->ble.set_user_data_cb(bmp_user_data_recv_cb_kb);

  load_ex_keycode_file(); // load exkc before tapping_term
  load_tapping_term_file();
  load_eeprom_emulation_file();
  load_encoder_config_file();
  bmp_macro_load_file();

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
void select_ble(void) {
    if (usb_enabled) {
        report_keyboard_t report_keyboard = {0};
        report_mouse_t    rep_mouse       = {0};
        host_keyboard_send(&report_keyboard);
        host_mouse_send(&rep_mouse);
    }
    ble_enabled = true;
    usb_enabled = false;
}
void select_usb(void) {
    if (ble_enabled) {
        report_keyboard_t report_keyboard = {0};
        report_mouse_t    rep_mouse       = {0};
        host_keyboard_send(&report_keyboard);
        host_mouse_send(&rep_mouse);
    }
    ble_enabled = false;
    usb_enabled = true;
}

extern bool stop_reentrant_process_exkc;
static void process_record_ex(uint16_t kc, keyrecord_t *record) {
    action_t action = action_for_keycode(kc);
    dprint("ACTION: ");
    debug_action(action);
    dprint(" layer_state: ");
    layer_debug();
    dprint(" default_layer_state: ");
    default_layer_debug();
    dprintln();

    if (!process_record_quantum_keycode(kc, record)) {
        return;
    }
    process_action(record, action);
}

void tap_code_ex(uint16_t kc, keyevent_t keyevent) {
    keyrecord_t record;
    stop_reentrant_process_exkc = true;
    record.event                = keyevent;
    record.event.pressed        = true;
    record.tap.count            = 1;
    process_record_ex(kc, &record);
    record.event.time    = (record.event.time + 1) | 1;
    record.event.pressed = false;
    process_record_ex(kc, &record);
    stop_reentrant_process_exkc = false;
}

void register_code_ex(uint16_t kc, keyevent_t keyevent) {
    keyrecord_t record;
    stop_reentrant_process_exkc = true;
    record.event                = keyevent;
    record.event.pressed        = true;
    process_record_ex(kc, &record);
    stop_reentrant_process_exkc = false;
}

void unregister_code_ex(uint16_t kc, keyevent_t keyevent) {
    keyrecord_t record;
    stop_reentrant_process_exkc = true;
    record.event                = keyevent;
    record.event.pressed        = false;
    process_record_ex(kc, &record);
    stop_reentrant_process_exkc = false;
}

extern bool via_keymap_update_flag;

bool process_record_user_bmp(uint16_t keycode, keyrecord_t* record) {
    char str[16];

    switch (keycode) {
        case KC_INS: {
            static uint32_t insert_pressed_time;
            if (record->event.pressed) {
                insert_pressed_time = timer_read32();
            } else {
                if (via_keymap_update_flag && insert_pressed_time > 0 &&
                    timer_elapsed32(insert_pressed_time) > 3000) {
                    if (save_keymap() == 0) {
                        via_keymap_update_flag = false;
                    }
                }
                insert_pressed_time = 0;
            }
        }
            return true;
            break;
        case xEISU:
            if (record->event.pressed) {
                if (keymap_config.swap_lalt_lgui == false) {
                    register_code(KC_LANG2);
                } else {
                    SEND_STRING(SS_LALT("`"));
                }
            } else {
                unregister_code(KC_LANG2);
            }
            return false;
            break;

        case xKANA:
            if (record->event.pressed) {
                if (keymap_config.swap_lalt_lgui == false) {
                    register_code(KC_LANG1);
                } else {
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
                select_ble();
                return false;
            case SEL_USB:
                select_usb();
                return false;
            case ADV_ID0 ... ADV_ID7:
                BMPAPI->ble.advertise(keycode - ADV_ID0);
                return false;
            case AD_WO_L:
                BMPAPI->ble.advertise(255);
                return false;
            case DEL_ID0 ... DEL_ID7:
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
    } else if (!record->event.pressed) {
        switch (keycode) {
            case ENT_SLP:
                sleep_enter_counter = 10;
                return false;
        }
    }

    return true;
}

__attribute__((weak)) uint32_t keymaps_len() { return 0; }

__attribute__((weak)) void bmp_enter_sleep(void) {
    bmp_before_sleep();
    BMPAPI->app.enter_sleep_mode();
}

__attribute__((weak)) void bmp_before_sleep() {}
