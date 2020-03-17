#include "custom_mousekey.h"

extern uint8_t mk_time_to_max, mk_wheel_time_to_max, mk_max_speed, mk_wheel_max_speed, mk_delay, mk_interval;

uint8_t pressed_wheel_key_count = 0;

bool process_mousekey_accel (uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case KC_MS_ACCEL0:
        if (record->event.pressed) {
            mk_max_speed = MOUSEKEY_MAX_SPEED;
            mk_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
            mk_time_to_max = 0;
            mk_wheel_time_to_max = 0;
        } else {
            mk_max_speed = MOUSEKEY_MAX_SPEED;
            mk_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
            mk_time_to_max = MOUSEKEY_TIME_TO_MAX;
            mk_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;
        }
        return false;
      case KC_MS_WH_UP: case KC_MS_WH_DOWN: case KC_MS_WH_LEFT: case KC_MS_WH_RIGHT:
        if (record->event.pressed) {
            if (!pressed_wheel_key_count) {
                mk_delay = MOUSEKEY_WHEEL_DELAY / 10;
                mk_interval = MOUSEKEY_WHEEL_INTERVAL;
            }
            pressed_wheel_key_count++;
        } else {
            pressed_wheel_key_count--;
            if (!pressed_wheel_key_count) {
                mk_delay = MOUSEKEY_DELAY / 10;
                mk_interval = MOUSEKEY_INTERVAL;
            }
        }
        return true;
    }
    return true;
}
