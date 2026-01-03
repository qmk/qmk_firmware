/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include "rev1.h"
#include "transactions.h"
#include "split_util.h"

#define NUMBER_OF_TOUCH_ENCODERS 2
#define TOUCH_ENCODER_OPTIONS TOUCH_SEGMENTS + 2

typedef struct PACKED {
    uint8_t r;
    uint8_t c;
} encodermap_t;

const encodermap_t touch_encoder_map[NUMBER_OF_TOUCH_ENCODERS][TOUCH_ENCODER_OPTIONS] =
{
    { { 1, 7 }, { 0, 7 }, { 2, 7 }, {  5, 6 }, {  5, 7 }, }, // Touch Encoder 0 matrix entries
    { { 7, 7 }, { 6, 7 }, { 8, 7 }, { 11, 6 }, { 11, 7 }, }  // Touch Encoder 1 matrix entries
};

static bool limit_lightning = true;

RGB rgb_matrix_hsv_to_rgb(hsv_t hsv) {
    if (limit_lightning) hsv.v /= 2;
    return hsv_to_rgb(hsv);
}

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active))
        return false;

    switch(index) {
        case 0: {
            limit_lightning = active;
            break;
        }
        case 1: {
            // Handle RGB Encoder switch press
            action_exec(MAKE_KEYEVENT(isLeftHand ? 4 : 10, 6, active));
            break;
        }
    }
    return false;
}

static void process_encoder_matrix(encodermap_t pos) {
    action_exec(MAKE_KEYEVENT(pos.r, pos.c, true));
#if TAP_CODE_DELAY > 0
    wait_ms(TAP_CODE_DELAY);
#endif
    action_exec(MAKE_KEYEVENT(pos.r, pos.c, false));
}

bool touch_encoder_update_kb(uint8_t index, bool clockwise) {
    if (!touch_encoder_update_user(index, clockwise))
        return false;

    // Mapping clockwise (typically increase) to zero, and counter clockwise (decrease) to 1
    process_encoder_matrix(touch_encoder_map[index][clockwise ? 0 : 1]);
    return false;
}

bool touch_encoder_tapped_kb(uint8_t index, uint8_t section) {
    if (!touch_encoder_tapped_user(index, section))
        return false;

    process_encoder_matrix(touch_encoder_map[index][section + 2]);
    return false;
}

void matrix_slave_scan_kb(void) {
    dip_switch_read(false);
    matrix_slave_scan_user();
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_increase_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_UNDERGLOW: {
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            }
            break;
        default: {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            }
            break;
    }
}
#endif


__attribute__((weak))
void render_layer_status(void) {
    // Keymap specific, expected to be overridden
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer"), false);
    oled_write_ln_P(PSTR("Undef"), false);
}

__attribute__((weak))
void render_leds_status(void)
{
    // Host Keyboard LED Status
    static const char PROGMEM led_icon[] = {
        0x0F,0x3A,0
    };
    oled_write_P(led_icon, false);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(   led_state.num_lock ? PSTR("N") : PSTR(" "), false);
    oled_write_P(  led_state.caps_lock ? PSTR("C") : PSTR(" "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("S") : PSTR(" "), false);
}

__attribute__((weak))
void render_touch_status(void)
{
    // Host Touch LED Status
    static const char PROGMEM touch_icon[] = {
        0x12,0x3A,0
    };
    oled_write_P(touch_icon, false);
    oled_write_P(         touch_encoder_is_on() ? PSTR("T") : PSTR(" "), false);
    oled_write_P(touch_encoder_is_calibrating() ? PSTR("C") : PSTR(" "), false);
    oled_write_P(PSTR(" "), false);
}

__attribute__((weak))
void render_audio_status(void)
{
    // Host Audio Status
    static const char PROGMEM audio_icon[] = {
        0x0E,0x3A,0
    };
    oled_write_P(audio_icon, false);
    oled_write_P( audio_is_on() ? PSTR("A")  : PSTR(" "), false);
    oled_write_P(is_clicky_on() ? PSTR("C")  : PSTR(" "), false);
    oled_write_P( is_music_on() ? PSTR("M")  : PSTR(" "), false);
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    // Sol 3 uses OLED_ROTATION_270 for default rotation on both halves
    return oled_init_user(OLED_ROTATION_270);
}

bool oled_task_kb(void) {
    if (!oled_task_user())
        return false;

    if (is_keyboard_left()) {
        render_icon();
        oled_write_P(PSTR("     "), false);
        render_layer_status();
        oled_write_P(PSTR("     "), false);
        render_leds_status();
        oled_write_P(PSTR("     "), false);
        render_touch_status();
        oled_write_P(PSTR("     "), false);
        render_audio_status();
    }
    else {
        render_icon();
        oled_write_P(PSTR("     "), false);
        render_rgb_menu();
    }
    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record))
        return false;

    switch(keycode) {
#ifdef RGB_MATRIX_ENABLE
        case QK_RGB_MATRIX_TOGGLE:
            if (record->event.pressed) {
                rgb_matrix_increase_flags();
            }
            return false;
#endif
    }
    return true;
};

void keyboard_post_init_kb(void) {
    touch_encoder_init();
    transaction_register_rpc(TOUCH_ENCODER_SYNC, touch_encoder_slave_sync);
    transaction_register_rpc(RGB_MENU_SYNC, rgb_menu_slave_sync);
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    touch_encoder_update(TOUCH_ENCODER_SYNC);
    rgb_menu_update(RGB_MENU_SYNC);
}
