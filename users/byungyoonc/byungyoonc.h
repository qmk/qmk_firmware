#pragma once

enum custom_keycodes {
    KC_SEC1 = SAFE_RANGE,
    KC_SEC2
};

#define KC_TASK LCTL(LSFT(KC_ESC))
#define KC_MMUT LSG(KC_A)

bool process_record_user_kb(uint16_t keycode, keyrecord_t *record);
