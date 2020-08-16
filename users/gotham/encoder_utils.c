#include "encoder_utils.h"

static pin_t encoders_pad[] = ENCODERS_PAD_A;
#define NUMBER_OF_ENCODERS (sizeof(encoders_pad) / sizeof(pin_t))

#ifdef SPLIT_KEYBOARD
static encoder_mode_t encoder_modes[NUMBER_OF_ENCODERS * 2] = {ENC_MODE_VOLUME};
#else
static encoder_mode_t encoder_modes[NUMBER_OF_ENCODERS] = {ENC_MODE_VOLUME};
#endif

__attribute__((weak)) void encoder_init_keymap(void) {}

__attribute__((weak)) void encoder_update_keymap(int8_t index, bool clockwise) { encoder_action(encoder_mode_get(index), clockwise); }

__attribute__((weak)) bool process_record_keymap_encoder(uint16_t keycode, keyrecord_t* record) { return true; }

bool process_record_user_encoder(uint16_t keycode, keyrecord_t* record) { return process_record_keymap_encoder(keycode, record); }

void encoder_init_user(void) { encoder_init_keymap(); }

void encoder_update_user(int8_t index, bool clockwise) {
    encoder_update_keymap(index, clockwise);
#if defined(OLED_DRIVER_ENABLE) && (OLED_CUSTOM_TIMEOUT > 0)
    oled_sleep_timer_reset();
#endif
}

void encoder_mode_set(uint8_t index, encoder_mode_t mode) { encoder_modes[index] = mode; }

encoder_mode_t encoder_mode_get(uint8_t index) { return encoder_modes[index]; }

void encoder_mode_next(uint8_t index) { encoder_mode_set(index, (encoder_mode_get(index) + 1) % _ENC_MODE_COUNT); }

void encoder_mode_previous(uint8_t index) { encoder_mode_set(index, (encoder_mode_get(index) + _ENC_MODE_COUNT - 1) % _ENC_MODE_COUNT); }

void encoder_get_modes_raw(encoder_mode_t* target_list) {
#    ifdef SPLIT_KEYBOARD
    memcpy(target_list, encoder_modes, sizeof(encoder_mode_t) * NUMBER_OF_ENCODERS * 2);
#    else
    memcpy(target_list, encoder_modes, sizeof(encoder_mode_t) * NUMBER_OF_ENCODERS);
#    endif
}

void encoder_set_modes_raw(encoder_mode_t* source_list) {
#    ifdef SPLIT_KEYBOARD
    memcpy(encoder_modes, source_list, sizeof(encoder_mode_t) * NUMBER_OF_ENCODERS * 2);
#    else
    memcpy(encoder_modes, source_list, sizeof(encoder_mode_t) * NUMBER_OF_ENCODERS);
#    endif
}

void encoder_action(encoder_mode_t mode, uint8_t clockwise) {
    switch (mode) {
        case ENC_MODE_VOLUME:
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
            break;
        case ENC_MODE_WORD_NAV:
            tap_code16(clockwise ? C(KC_RIGHT) : C(KC_LEFT));
            break;
        case ENC_MODE_LEFT_RIGHT:
            tap_code(clockwise ? KC_RIGHT : KC_LEFT);
            break;
        case ENC_MODE_UP_DOWN:
            tap_code(clockwise ? KC_UP : KC_DOWN);
            break;
        case ENC_MODE_PAGING:
            tap_code(clockwise ? KC_PGUP : KC_PGDN);
            break;
        default:
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
    }
}
