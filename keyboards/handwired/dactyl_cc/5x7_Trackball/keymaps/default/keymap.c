#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN     1
#define _NUMPAD 2
#define _SHIFT  3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        // left hand
        KC_EQL,    KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   TG(_FN),
        KC_ESC,    KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_CUT,
        KC_TAB,    KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_CALC,
        KC_CAPS,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
        TG(_FN),   KC_LCTL, KC_LEFT, KC_RGHT,KC_LALT,
                                    KC_LCTL, KC_HOME,
                                    KC_END,
                                    KC_DEL, KC_BSPC, KC_LSFT,
                                    KC_MUTE,
        // right hand
                      TG(_NUMPAD), KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_MINS,
                          KC_COPY, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,
                          KC_PSTE, KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
                                   KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  MO(_NUMPAD),
                                            KC_ESC,  KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
             KC_RSFT, KC_SPC, KC_ENT,
             MS_BTN1, MS_BTN1, MS_BTN1, MS_BTN2, KC_LGUI

    ),

    [_FN] = LAYOUT(
        // left hand
        _______,   KC_F1,     KC_F2,      KC_F3,    KC_F4,     KC_F5,    KC_F6,
        _______,   _______,   _______,    KC_UP,    _______,   _______,  _______,
        _______,   _______,   KC_LEFT,    KC_DOWN,  KC_RGHT,   _______,  QK_BOOT,
        _______,   _______,   _______,   _______,   _______,   _______,
        TG(_FN),   _______,   KC_MPRV,   KC_MNXT,   _______,
                                    _______, _______,
                                    _______,
                                    _______, _______, _______,
                                    _______,
        // right hand
                          KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    _______,
                          _______,   _______,   _______,   _______,   _______,   _______,   _______,
                          _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                     _______,   _______,   _______,   _______,   _______,   _______,
                                                _______,   _______,   _______,   _______,   _______,
             _______, _______, _______,

             _______, _______, _______, _______, _______
    ),

    [_NUMPAD] = LAYOUT(
        // left hand
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,
                                    _______, _______,
                                    _______,
                                    _______, _______, _______,
                                    _______,
        // right hand
                          _______,   _______,   KC_NUM,    KC_PSLS,   KC_PAST,   KC_PMNS,   RGB_MOD,
                          _______,   _______,   KC_P7,     KC_P8,     KC_P9,     KC_PPLS,   RGB_RMOD,
                          _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PPLS,   _______,
                                     _______,   KC_P1,     KC_P2,     KC_P3,     KC_PENT,   MO(_NUMPAD),
                                                KC_P0,     KC_P0,     KC_PDOT,   KC_PENT,   RGB_TOG,
             _______, KC_P0,   KC_PENT,

             _______, _______, _______, _______, _______
    ),

        [_SHIFT] = LAYOUT(
        // left hand
        TO(_QWERTY),_______,   _______,   _______,   _______,   _______,  _______,
        _______,    _______,   _______,   _______,   _______,   _______,  _______,
        _______,    _______,   _______,   _______,   _______,   _______,  _______,
        _______,    _______,   _______,   _______,   _______,   _______,
        _______,    _______,   _______,   _______,   _______,
                                    _______, _______,
                                    _______,
                                    _______, _______, _______,
                                    _______,
        // right hand
                          _______,   _______,   _______,   _______,   _______,   _______,   _______,
                          _______,   _______,   _______,   _______,   _______,   _______,   _______,
                          _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                     _______,   _______,   _______,   _______,   _______,   _______,
                                                _______,   _______,   _______,   _______,   _______,

             _______, _______, _______,
             _______, _______, _______, _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [1] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [2] = { ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [3] = { ENCODER_CCW_CW(UG_PREV, UG_NEXT)}
};
#endif

/*
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(_QWERTY, _RAISE, _LOWER, _ADJUST);
}
*/

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);
const char *read_rgb_info(void);

const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

bool oled_task_user() {
    //rgblight_get_mode(led_state_reader(), false);
    led_t led_state = host_keyboard_led_state();
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_rgb_info(), false);
    oled_write_ln(read_layer_state(), false);
    //oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(led_state.caps_lock ? PSTR("Caps Lock On") : PSTR("Caps Lock Off"), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);

    // Host Keyboard LED Status
    //led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);

    //rgblight_get_mode(led_state_reader(), false);

    return false;
    }

#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
