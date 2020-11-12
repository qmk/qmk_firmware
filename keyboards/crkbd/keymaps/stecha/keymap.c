#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NUM 1
#define _SYM 2

enum custom_keycodes { QWERTY = SAFE_RANGE, NUM, SYM, ALT_TAB, DSKP_LEFT, DSKP_RIGHT };

enum macro_keycodes {
    KC_SAMPLEMACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, LCTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, LSFT_T(KC_BSLS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, DSKP_LEFT, NUM, KC_SPC, KC_ENT, SYM, DSKP_RIGHT),

    [_NUM] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, LCTL_T(KC_TAB), KC_LT, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_GT, KC_TAB, LSFT_T(KC_GRV), KC_UNDS, KC_LPRN, KC_DEL, KC_MINS, KC_LBRC, KC_RBRC, KC_EQL, KC_INS, KC_RPRN, KC_PLUS, KC_RSFT, DSKP_LEFT, NUM, KC_SPC, KC_ENT, SYM, DSKP_RIGHT),

    [_SYM] = LAYOUT(KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LSFT_T(KC_GRV), RGB_MOD, RESET, RGB_HUD, RGB_SAD, RGB_VAD, RGB_VAI, RGB_SAI, RGB_HUI, KC_NO, RGB_TOG, KC_RSFT, DSKP_LEFT, NUM, KC_SPC, KC_ENT, SYM, DSKP_RIGHT)};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
// SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb());  // turns on the display
#endif
}

// SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) { iota_gfx_task(); }

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        // If you want to change the display of OLED, you need to change here
        matrix_write_ln(matrix, read_layer_state());
        matrix_write_ln(matrix, read_keylog());
        // matrix_write_ln(matrix, read_keylogs());
        // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
        // matrix_write_ln(matrix, read_host_led_state());
        // matrix_write_ln(matrix, read_timelog());
    } else {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif  // SSD1306OLED

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef SSD1306OLED
        set_keylog(keycode, record);
#endif
        // set_timelog();
    }

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL << _QWERTY);
            }
            return false;
        case NUM:
            if (record->event.pressed) {
                layer_on(_NUM);
            } else {
                layer_off(_NUM);
            }
            return false;
        case SYM:
            if (record->event.pressed) {
                layer_on(_SYM);
            } else {
                layer_off(_SYM);
            }
            return false;
        case DSKP_LEFT:
            if (record->event.pressed) {  // key down
                key_timer = timer_read();
                register_mods(MOD_BIT(KC_LGUI));
            } else {                                   // key up
                if (timer_elapsed(key_timer) < 200) {  // up before 200ms considered a tap
                    tap_code16(C(KC_LEFT));
                }
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
        case DSKP_RIGHT:
            if (record->event.pressed) {  // key down
                key_timer = timer_read();
                register_mods(MOD_BIT(KC_LALT));
            } else {
                unregister_mods(MOD_BIT(KC_LALT));     // key up
                if (timer_elapsed(key_timer) < 200) {  // up before 200ms considered a tap
                    tap_code16(C(G(KC_RIGHT)));
                }
            }
            return false;
        case ALT_TAB:
            if (record->event.pressed) {  // key down
                key_timer = timer_read();
                register_mods(MOD_BIT(KC_LCTL));
            } else {  // key up
                unregister_mods(MOD_BIT(KC_LCTL));
                if (timer_elapsed(key_timer) < 200) {  // up before 200ms considered a tap
                    tap_code16(LALT(KC_TAB));
                }
            }
            return false;
        case RGB_MOD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;

#ifdef RGBLIGHT_ENABLE
#endif
            break;
    }
    return true;
}
