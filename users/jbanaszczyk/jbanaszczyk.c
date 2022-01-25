#include "quantum.h"
#include "jbanaszczyk.h"
#include "do_not_sleep.h"

void keyboard_post_init_user(void) {
#ifndef NO_DEBUG
    debug_enable = true;
#endif
#ifdef DO_NOT_SLEEP
#    ifdef DO_NOT_SLEEP_START_LOCKED
    do_not_sleep_lock();
#    else
    do_not_sleep_enable();
#    endif
#endif
}

void matrix_scan_user(void) {
#ifdef DO_NOT_SLEEP
    do_not_sleep_scan();
#endif
}

void startup_user() {
#ifndef NO_DEBUG
    debug_enable = true;
#endif
}

void shutdown_user() {
#ifdef DO_NOT_SLEEP
    do_not_sleep_disable();
#endif
}

void suspend_power_down_user(void) {
#ifdef DO_NOT_SLEEP
    do_not_sleep_disable();
#endif
}

void suspend_wakeup_init_user(void) {
#ifdef DO_NOT_SLEEP
    do_not_sleep_enable();
#endif
}

static bool process_record_debug(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        dprintf("0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n", keycode, record->event.key.row, record->event.key.col, get_highest_layer(layer_state), record->event.pressed, get_mods(), get_oneshot_mods(), record->tap.count);
    }
    //    if (record->event.pressed) {
    //        dprintf("KL: kc: %u\n", keycode);
    //    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true

           && process_record_debug(keycode, record)
#ifdef DO_NOT_SLEEP
           && do_not_sleep_process(keycode, record)
#endif
        ;
}

/* Hooks: __attribute__((weak))
----------------------------------------
quantum.c:
//  bool process_record_user(uint16_t keycode, keyrecord_t *record) { return true; }
  void post_process_record_user(uint16_t keycode, keyrecord_t *record) {}
//  void startup_user() {}
//  void shutdown_user() {}
//  void suspend_power_down_user(void) {}
//  void suspend_wakeup_init_user(void) {}
----------------------------------------
matrix_common.c:
  void matrix_init_user(void) {}
//  void matrix_scan_user(void) {}
----------------------------------------
keyboard.c:
  void keyboard_pre_init_user(void) {}
//  void keyboard_post_init_user() {}
  void housekeeping_task_user(void) {}
----------------------------------------
matrix.c:
  void matrix_slave_scan_user(void) {}
----------------------------------------
action_layer.c:
  layer_state_t default_layer_state_set_user(layer_state_t state) { return state; }
  layer_state_t layer_state_set_user(layer_state_t state) { return state; }
----------------------------------------
eeconfig.c:
  void eeconfig_init_user(void) { eeconfig_update_user(0); }
----------------------------------------
action_util.c:
  void oneshot_locked_mods_changed_user(uint8_t mods) {}
  void oneshot_mods_changed_user(uint8_t mods) {}
  void oneshot_layer_changed_user(uint8_t layer) {}
----------------------------------------
dip_switch.c:
  bool dip_switch_update_user(uint8_t index, bool active) { return true; }
  bool dip_switch_update_mask_user(uint32_t state) { return true; }
----------------------------------------
encoder.c:
  bool encoder_update_user(uint8_t index, bool clockwise) { return true; }
----------------------------------------
led.c:
  void led_set_user(uint8_t usb_led) {}
  bool led_update_user(led_t led_state) { return true; }
----------------------------------------
pointing_device.c:
  void pointing_device_init_user(void) {}
  report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) { return mouse_report; }
----------------------------------------
wpm.c:
  bool wpm_keycode_user(uint16_t keycode) { ... }

----------------------------------------
led_matrix\led_matrix.c:
  void led_matrix_indicators_user(void) {}
  void led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {}
----------------------------------------
process_keycode\process_audio.c:
  void audio_on_user() {}
----------------------------------------
process_keycode\process_auto_shift.c:
  void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
  void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) { unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode); }
----------------------------------------
process_keycode\process_dynamic_macro.c:
  void dynamic_macro_record_start_user(void) { dynamic_macro_led_blink(); }
  void dynamic_macro_play_user(int8_t direction) { dynamic_macro_led_blink(); }
  void dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record) { dynamic_macro_led_blink(); }
  void dynamic_macro_record_end_user(int8_t direction) { dynamic_macro_led_blink(); }
----------------------------------------
process_keycode\process_music.c:
  bool music_mask_kb(uint16_t keycode) { return music_mask_user(keycode); }
  bool music_mask_user(uint16_t keycode) { return keycode < 0xFF; }
  void music_on_user() {}
  void midi_on_user() {}
  void music_scale_user() {}
----------------------------------------
process_keycode\process_steno.c:
  bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) { return true; }
  bool postprocess_steno_user(uint16_t keycode, keyrecord_t *record, steno_mode_t mode, uint8_t chord[6], int8_t pressed) { return true; }
  bool process_steno_user(uint16_t keycode, keyrecord_t *record) { return true; }
----------------------------------------
process_keycode\process_ucis.c:
  void qk_ucis_start_user(void) {
----------------------------------------
rgb_matrix\rgb_matrix.c:
  void rgb_matrix_indicators_user(void) {}
  void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {}
----------------------------------------

*/
