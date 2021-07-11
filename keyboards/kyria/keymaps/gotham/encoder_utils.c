#include "encoder_utils.h"

void encoder_utils_init(void) {
    encoder_left_mode  = ENC_MODE_VOLUME;
    encoder_right_mode = ENC_MODE_LEFT_RIGHT;
}

void set_encoder_mode(bool left, encoder_mode_t mode) {
    if (left) {
        encoder_left_mode = mode;
    } else {
        encoder_right_mode = mode;
    }
}

encoder_mode_t get_encoder_mode(bool left) {
    if (left) {
        return encoder_left_mode;
    } else {
        return encoder_right_mode;
    }
}

void cycle_encoder_mode(bool left, bool reverse) {
    encoder_mode_t mode = get_encoder_mode(left);
    if (reverse) {
        mode = (mode == 0) ? (_ENC_MODE_LAST - 1) : (mode - 1);
    } else {
        mode = (mode == (_ENC_MODE_LAST - 1)) ? 0 : (mode + 1);
    }
    set_encoder_mode(left, mode);
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
        tap_code16(C(KC_RIGHT));
    } else {
        tap_code16(C(KC_LEFT));
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
        tap_code(KC_UP);
    } else {
        tap_code(KC_DOWN);
    }
}

void encoder_action_paging(uint8_t clockwise) {
    if (clockwise) {
        tap_code(KC_PGUP);
    } else {
        tap_code(KC_PGDN);
    }
}

void encoder_action(encoder_mode_t mode, uint8_t clockwise) {
    switch (mode) {
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
