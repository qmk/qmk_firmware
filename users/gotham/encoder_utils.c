#include "encoder_utils.h"

static pin_t encoders_pad[] = ENCODERS_PAD_A;
#define NUMBER_OF_ENCODERS (sizeof(encoders_pad) / sizeof(pin_t))

#ifdef SPLIT_KEYBOARD
static encoder_mode_t encoder_modes[NUMBER_OF_ENCODERS * 2] = {ENC_MODE_VOLUME};
#else
static encoder_mode_t encoder_modes[NUMBER_OF_ENCODERS] = {ENC_MODE_VOLUME};
#endif

__attribute__((weak)) void encoder_init_keymap(void) {}

__attribute__((weak)) void encoder_update_keymap(int8_t index, bool clockwise) {
    encoder_action(encoder_mode_get(index), clockwise);
}

__attribute__((weak)) bool process_record_keymap_encoder(uint16_t keycode, keyrecord_t *record) { return true; }

void encoder_init_user(void) {
    encoder_init_keymap();
}

void encoder_update_user(int8_t index, bool clockwise) {
#ifdef OLED_DRIVER_ENABLE
    oled_sleep_timer_reset();
#endif
    encoder_update_keymap(index, clockwise);
}

void encoder_mode_set(uint8_t index, encoder_mode_t mode) {
    encoder_modes[index] = mode;
#ifdef CONSOLE_ENABLE
    uprintf("EncModes: [%d, %d], [%d, %d]\n", encoder_modes[0], encoder_modes[1], encoder_mode_get(0), encoder_mode_get(1));
#endif
}

encoder_mode_t encoder_mode_get(uint8_t index) {
    return encoder_modes[index];
}

#ifdef SPLIT_KEYBOARD
void encoder_get_modes_raw(encoder_mode_t* target_list) {
    memcpy(target_list, encoder_modes, sizeof(encoder_mode_t) * NUMBER_OF_ENCODERS);
}

void encoder_set_modes_raw(encoder_mode_t* source_list) {
    memcpy(encoder_modes, source_list, sizeof(encoder_mode_t) * NUMBER_OF_ENCODERS);
}
#endif

void encoder_mode_next(uint8_t index) {
    encoder_mode_set(index, (encoder_mode_get(index) + 1) % _ENC_MODE_COUNT);
}

void encoder_mode_previous(uint8_t index) {
    encoder_mode_set(index, (encoder_mode_get(index) + _ENC_MODE_COUNT - 1) % _ENC_MODE_COUNT);
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
