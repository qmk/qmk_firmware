#include "encoder_util.h"

void encoder_utils_init(void) {
    encoder_mode  = ENC_MODE_LEFT_RIGHT;
}

void cycle_encoder_mode(bool reverse) {
    encoder_mode_t mode = encoder_mode;
    if (reverse) {
        mode = (mode == 0) ? (_ENC_MODE_LAST - 1) : (mode - 1);
    } else {
        mode = (mode == (_ENC_MODE_LAST - 1)) ? 0 : (mode + 1);
    }
    encoder_mode = mode;
}

void encoder_shift(bool pressed) {
    if (pressed) {
        encoder_mode = ENC_MODE_UP_DOWN;
    } else {
        encoder_mode = ENC_MODE_WORD_NAV;
    }
}

void encoder_action_volume(uint8_t clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}

void encoder_action_word_nav(uint8_t clockwise) {
    if (clockwise) {
        tap_code16(RALT(KC_RIGHT));
    } else {
        tap_code16(RALT(KC_LEFT));
    }
}

void encoder_action_left_right(uint8_t clockwise) {
    if (clockwise) {
        tap_code(KC_RIGHT);
    } else {
        tap_code(KC_LEFT);
    }
}

void encoder_action_up_down(uint8_t clockwise) {
    if (clockwise) {
        tap_code(KC_DOWN);
    } else {
        tap_code(KC_UP);
    }
}

void encoder_action_paging(uint8_t clockwise) {
    if (clockwise) {
        tap_code(KC_PGDN);
    } else {
        tap_code(KC_PGUP);
    }
}

void encoder_action(uint8_t clockwise) {
    switch (encoder_mode) {
        case ENC_MODE_VOLUME:
            encoder_action_volume(clockwise);
            break;
        case ENC_MODE_WORD_NAV:
            encoder_action_word_nav(clockwise);
            break;
        case ENC_MODE_LEFT_RIGHT:
            encoder_action_left_right(clockwise);
            break;
        case ENC_MODE_UP_DOWN:
            encoder_action_up_down(clockwise);
            break;
        case ENC_MODE_PAGING:
            encoder_action_paging(clockwise);
            break;
        default:
            encoder_action_volume(clockwise);
    }
}
