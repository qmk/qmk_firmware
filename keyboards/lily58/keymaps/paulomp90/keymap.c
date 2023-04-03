#include QMK_KEYBOARD_H
#include "keymap_portuguese.h"
#include "features/custom_shift_keys.h"

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

/* tap dance shifts */
typedef struct {
    bool is_press_action;
    int  state;
} tap;

enum {
    SINGLE_TAP  = 1,
    SINGLE_HOLD = 2,
};

enum { LEFT_SHIFT = 0, RIGHT_SHIFT = 1 };

const custom_shift_key_t custom_shift_keys[] = {
    {KC_BSPC, KC_DEL},
};

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  '?  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  +*  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ç  | BACK |
    * |------+------+------+------+------+------|  <>   |    |  ´`   |------+------+------+------+------+------|
    * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |Shift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `-------------------''-------'           '------''--------------------'
    */
    [_QWERTY] = LAYOUT(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        TD(LEFT_SHIFT),  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_BSPC,
        KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_GRV,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  TD(RIGHT_SHIFT),
                            KC_LALT, KC_LGUI, LOWER, KC_SPC,   KC_ENT,   RAISE,  KC_RGUI, KC_RALT
    ),

    /* LOWER
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      | BRG- | BRG+ | VOL- | VOL+ |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      | MUTE | PREV | PLAY | NEXT |      |-------.    ,-------|      |      |  \|  |  ºª  |  ~^  |      |
    * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
    * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `-------------------''-------'           '------''--------------------'
    */

    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
        _______, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, _______,                   _______, _______, _______, _______, _______, _______,
        _______, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, _______,                   _______, _______, KC_BSLS, KC_LBRC, KC_QUOT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______,
                                    _______, _______, _______, _______, _______,  _______, _______, _______
    ),

    /* RAISE
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |  F1  |      |      |      |      |      |                    |      |      |  Up  |      |      | F12  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      | End  | Home | PGDN | PGUP |      |-------.    ,-------|      | Left | Down |Right |      |      |
    * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
    * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `-------------------''-------'           '------''--------------------'
    */

    [_RAISE] = LAYOUT(
        _______, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, _______,
        KC_F1,   _______, _______, _______, _______, _______,                   _______, XXXXXXX, KC_UP,  XXXXXXX, _______,  KC_F12,
        _______, KC_END, KC_HOME, KC_PGDN, KC_PGUP, _______,                   XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______,  _______, _______, _______, _______,
                                    _______, _______, _______,  _______, _______,  _______, _______, _______
    ),

    /* ADJUST
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |RGB ON| HUE+ | SAT+ | VAL+ |      |      |-------.    ,-------|      |      |      |      |      |      |
    * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
    * | MODE | HUE- | SAT- | VAL- |      |      |-------|    |-------|      |      |      |      |      |      |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt | 
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `----------------------------'           '------''--------------------'
    */

    [_ADJUST] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    _______, _______, _______, _______, _______,  _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_ln(read_layer_state(), false);
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
    } else {
        oled_write(read_logo(), false);
    }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    if (record->event.pressed) {
#ifdef OLED_ENABLE
        set_keylog(keycode, record);
#endif
    }
    return true;
}

/* Tap dance shifts */
int cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed)
            return SINGLE_HOLD;
        else
            return SINGLE_TAP;
    } else
        return 0;
}

static tap lshifttap_state = {.is_press_action = true, .state = 0};

static tap rshifttap_state = {.is_press_action = true, .state = 0};

void lshift_finished(tap_dance_state_t *state, void *user_data) {
    lshifttap_state.state = cur_dance(state);
    switch (lshifttap_state.state) {
        case SINGLE_TAP:
            register_code16(LALT(KC_LEFT));
            break;
        case SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
    }
}

void lshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (lshifttap_state.state) {
        case SINGLE_TAP:
            unregister_code16(LALT(KC_LEFT));
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LSFT);
            break;
    }
    lshifttap_state.state = 0;
}

void rshift_finished(tap_dance_state_t *state, void *user_data) {
    rshifttap_state.state = cur_dance(state);
    switch (rshifttap_state.state) {
        case SINGLE_TAP:
            register_code16(LALT(KC_RGHT));
            break;
        case SINGLE_HOLD:
            register_code(KC_RSFT);
            break;
    }
}

void rshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (rshifttap_state.state) {
        case SINGLE_TAP:
            unregister_code16(LALT(KC_RGHT));
            break;
        case SINGLE_HOLD:
            unregister_code(KC_RSFT);
            break;
    }
    rshifttap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [LEFT_SHIFT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lshift_finished, lshift_reset),
    [RIGHT_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset),
};
