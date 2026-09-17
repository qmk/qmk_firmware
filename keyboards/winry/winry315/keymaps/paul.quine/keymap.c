#include QMK_KEYBOARD_H
#include "pq_color.h"
#include "pq_strings.h"
#include "rgb_matrix_map.h"
#include "keymap_uk.h"
#include "sendstring_uk.h"

bool encoder_zoom(bool clockwise);
bool encoder_back_forward(bool clockwise);
bool encoder_up_down(bool clockwise);
void pq_toggle_rgb(void);

bool pq_is_rgb_enabled = false;

enum my_keycodes {
    SS_CUSTOM_STRING_1 = SAFE_RANGE,
    SS_CUSTOM_STRING_2,
    SS_CUSTOM_STRING_3,
    SS_CUSTOM_STRING_4,
    SS_CUSTOM_STRING_5,
    SS_CUSTOM_SAFE_STING_1,
    SS_CUSTOM_SAFE_STING_2,
    SS_CUSTOM_SAFE_STING_3,
    SS_CUSTOM_SAFE_STING_4,
    SS_CUSTOM_SAFE_STING_5,
    SS_CUSTOM_SAFE_STING_6,
    LED_OFF
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_top(
            KC_NO,      LCTL(LSFT(KC_M)),     LCTL(LSFT(KC_O)),
        LCTL(LALT(KC_DEL)),    SS_CUSTOM_STRING_1,    SS_CUSTOM_STRING_2,    SS_CUSTOM_STRING_3,    SS_CUSTOM_STRING_4,
        SS_CUSTOM_SAFE_STING_5,    SS_CUSTOM_SAFE_STING_6,    SS_CUSTOM_STRING_5,    KC_NO,    KC_NO,
        OSL(1),    SS_CUSTOM_SAFE_STING_1,    SS_CUSTOM_SAFE_STING_2,    SS_CUSTOM_SAFE_STING_4,    SS_CUSTOM_SAFE_STING_3
    ),

    [1] = LAYOUT_top(
            LED_OFF,      KC_NO,     KC_NO,
        QK_BOOT,   KC_F13,    KC_F14,    KC_F15,    KC_F16,
        KC_F17,    KC_F18,    KC_F19,    KC_F20,    KC_F21,
        KC_TRNS,  KC_F22,    KC_F23,    KC_F24,    KC_NO
    ),
};
// clang-format on

bool encoder_zoom(bool clockwise) {
    if (clockwise) {
        tap_code16(LCTL(KC_MINS));
    } else {
        tap_code16(LCTL(KC_EQUAL));
    }
    return true;
}

bool encoder_back_forward(bool clockwise) {
    if (clockwise) {
        tap_code(KC_LEFT);
    } else {
        tap_code(KC_RGHT);
    }
    return true;
}

bool encoder_up_down(bool clockwise) {
    if (clockwise) {
        tap_code(KC_PGUP);
    } else {
        tap_code(KC_PGDN);
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case 0:
            encoder_back_forward(clockwise);
            break;
        case 1:
            encoder_zoom(clockwise);
            break;
        case 2:
            encoder_up_down(clockwise);
            break;
    }
    return false;
}

void pq_toggle_rgb(void) {
    pq_is_rgb_enabled = !pq_is_rgb_enabled;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SS_CUSTOM_STRING_1:
            if (record->event.pressed) {
                send_string(pq_custom_string_1());
            }
            return false;
        case SS_CUSTOM_STRING_2:
            if (record->event.pressed) {
                send_string(pq_custom_string_2());
            }
            return false;
        case SS_CUSTOM_STRING_3:
            if (record->event.pressed) {
                send_string(pq_custom_string_3());
            }
            return false;
        case SS_CUSTOM_STRING_4:
            if (record->event.pressed) {
                send_string(pq_custom_string_4());
            }
            return false;
        case SS_CUSTOM_STRING_5:
            if (record->event.pressed) {
                send_string(pq_custom_string_5());
            }
            return false;
        case LED_OFF:
            if (record->event.pressed) {
                pq_toggle_rgb();
            }
            return false;
        case SS_CUSTOM_SAFE_STING_1:
            if (record->event.pressed) {
                send_string(pq_custom_safe_string_1());
            }
            return false;
        case SS_CUSTOM_SAFE_STING_2:
            if (record->event.pressed) {
                send_string(pq_custom_safe_string_2());
            }
            return false;
        case SS_CUSTOM_SAFE_STING_3:
            if (record->event.pressed) {
                send_string(pq_custom_safe_string_3());
            }
            return false;
        case SS_CUSTOM_SAFE_STING_4:
            if (record->event.pressed) {
                send_string(pq_custom_safe_string_4());
            }
            return false;
        case SS_CUSTOM_SAFE_STING_5:
            if (record->event.pressed) {
                send_string(pq_custom_safe_string_5());
            }
            return false;
        case SS_CUSTOM_SAFE_STING_6:
            if (record->event.pressed) {
                send_string(pq_custom_safe_string_6());
            }
            return false;
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
void pq_rgb(const uint8_t array[], size_t pq_size, uint8_t colour) {
    int red;
    int green;
    int blue;

    switch (colour) {
        case PQ_BLACK: // black
            red   = 0x00;
            green = 0x00;
            blue  = 0x00;
            break;
        case PQ_WHITE: // white
        default:
            red   = 0xFF;
            green = 0xFF;
            blue  = 0xFF;
            break;
        case PQ_BLUE: // blue
            red   = 0x00;
            green = 0x80;
            blue  = 0xFF;
            break;
        case PQ_RED: // red
            red   = 0xFF;
            green = 0x05;
            blue  = 0x05;
            break;
        case PQ_YELLOW: // yellow
            red   = 0xFF;
            green = 0xEF;
            blue  = 0x00;
            break;
    }
    for (uint8_t i = 0; i < pq_size; i++) {
        rgb_matrix_set_color(array[i], red, green, blue);
    }
}
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    pq_rgb(LED_LIST_BLACK, ARRAYSIZE(LED_LIST_BLACK), PQ_BLACK);

    if (!pq_is_rgb_enabled) {
        pq_rgb(LED_ALL, ARRAYSIZE(LED_ALL), PQ_BLACK);
        return false;
    }

    pq_rgb(LED_ALL, ARRAYSIZE(LED_ALL), PQ_WHITE);

    switch(get_highest_layer(layer_state)){
        case 0:
            pq_rgb(LED_LIST_REDS, ARRAYSIZE(LED_LIST_REDS), PQ_RED);
            pq_rgb(LED_LIST_YELLOW, ARRAYSIZE(LED_LIST_YELLOW), PQ_YELLOW);
            pq_rgb(LED_LIST_BLUE, ARRAYSIZE(LED_LIST_BLUE), PQ_BLUE);
            break;
        case 1:
            pq_rgb(LED_ALL, ARRAYSIZE(LED_ALL), PQ_BLACK);
            pq_rgb(LED_LAYER_1_WHITE, ARRAYSIZE(LED_LAYER_1_WHITE), PQ_WHITE);
            pq_rgb(LED_LAYER_1_RED, ARRAYSIZE(LED_LAYER_1_RED), PQ_RED);
            pq_rgb(LED_LAYER_1_BLUE, ARRAYSIZE(LED_LAYER_1_BLUE), PQ_BLUE);
            pq_rgb(LED_LAYER_1_YELLOW, ARRAYSIZE(LED_LAYER_1_YELLOW), PQ_YELLOW);
            break;
    }

    return false;
}
#endif