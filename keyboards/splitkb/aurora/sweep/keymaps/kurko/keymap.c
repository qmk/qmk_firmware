/* Copyright 2023 Alex Oliveira <@kurko>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * The Sweep is a very small keyboard with 34 keys. It doesn't have a lot of
 * room for lots of keys everywhere, so we have to be creative and configure
 * multiple functionalities for each key.
 *
 * Here are some of the specific tactics employed to get the most out of this
 * keyboard layout with so few keys:
 *
 * - The basic functionality is inspired by @benvallack's layout which can be
 *   seen in https://www.youtube.com/watch?v=8wZ8FRwOzhU. The idea is to have a
 *   layer for writing, a layer for symbols and numbers, and a layer for
 *   navigating with mouse and arrow keys.
 *
 *   Some keys aspects involve rolling into layers and keys more than keeping
 *   keys held down. For example, we don't keep the key for layer2 down with the
 *   thumb in order to reach some key such as Enter or Backspace, instead we go
 *   there, tap and then tap back to Layer1. That means we're applying less
 *   force to the thumb, and making it more ergonomic for longer usage.
 *
 * - Some very important keys like - and ' are in Layer2, so there's a sequence
 *   of keys necessary to (a) get to Layer2, (b) type the key, and (c) get back
 *   to Layer1. In that sense, it feels a lot like Vim where we need to be
 *   constantly returning to Normal model. Important improvements can be made by
 *   making usage of tap-and-hold keys, such as holding j down to get Cmd. I've
 *   done that to the number rows, as well as right thumb being Esc on tap and
 *   LCtrl on hold.
 *
 *   Another example is slash and backslack. One tap on / outputs /, but two
 *   taps outputs \. That way I don't need to go to layer two to get to the
 *   backslash.
 */
#include QMK_KEYBOARD_H

enum layers {
    _LAYER1 = 0,
    _LAYER2,
    _LAYER3,
    _LAYER4,
};


/**
 * CUSTOM KEYCODES
 *
 * These are the keycodes that are used for the tap-hold functionality. They
 * must be in the range of SAFE_RANGE to END_CUSTOM_KEYCODES. For example, we
 * want to tap Q for Q, and hold Q for 1 because this keyboard doesn't have the
 * numbers row.
 */
enum custom_keycodes {
    // this is the sequence on the numerical rows
    Q_1 = SAFE_RANGE,
    W_2,
    E_3,
    R_4,
    T_5,
    Y_6,
    U_7,
    I_8,
    O_9,
    P_0,
    A_OR_HOLD_TAB,
    G_OR_HOLD_QUOT,
    SEMICOLON_OR_HOLD_ENTER,
    //...
    END_CUSTOM_KEYCODES, // Always keep this one at the end!
};

// Replace 10 with the number of custom keycodes we have
#define CUSTOM_KEYCODES_LENGTH (END_CUSTOM_KEYCODES - SAFE_RANGE)

/**
 * Custom keycodes
 *
 * This keeps a mapping of the custom keycodes to their respective 'letter' and
 * 'number' keycodes. The 'letter' keycode is sent when the key is tapped,
 * whereas the 'number' keycode is sent when the key is held for longer than
 * TAPPING_TERM.
 */
uint16_t custom_keys[CUSTOM_KEYCODES_LENGTH][2] = {
    {KC_Q, KC_1},
    {KC_W, KC_2},
    {KC_E, KC_3},
    {KC_R, KC_4},
    {KC_T, KC_5},
    {KC_Y, KC_6},
    {KC_U, KC_7},
    {KC_I, KC_8},
    {KC_O, KC_9},
    {KC_P, KC_0},
    {KC_A, KC_TAB},
    {KC_G, KC_QUOTE},
    {KC_SCLN, KC_ENTER},
};

// Basic state management for the tap-hold functionality
bool is_custom_key_pressed;
// Keeps track of which keys have been tapped so the timer doesn't try to
// trigger the tap-hold functionality for keys that have already been tapped.
bool custom_keys_tapped[CUSTOM_KEYCODES_LENGTH];
bool custom_keys_timer_initialized = false;
uint16_t custom_keys_timer[CUSTOM_KEYCODES_LENGTH];
// The index of the key that is currently being held down
uint16_t custom_key_down;

// Aliases for readability
#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define D_OR_LALT MT(MOD_LALT, KC_D)
#define D_OR_LALT MT(MOD_LALT, KC_D)
#define F_OR_LGUI MT(MOD_LGUI, KC_F)
#define J_OR_RGUI MT(MOD_RGUI, KC_J)
#define K_OR_RALT MT(MOD_RALT, KC_K)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)

/*
 * Tap Dance Declarations
 *
 * These are keys that behave one way when we press once, and a different way
 * when tapped twice.
 */
enum {
    TD_SLSH_BSLS = 0,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SLSH_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
};
/* This shortcut is using for toggling input sources from e.g US to US
 * International. It's using HYPR because it's very unlikely that that would be
 * set in a new system, so there are less chances that this would cause trouble
 * in new computers.
 */
#define CHANGE_SOURCE HYPR(KC_S)
/*
 * Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
 * The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
 * produces the key `tap` when tapped (i.e. pressed and released).
 */
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

/*
 * This is the configuration of each key. Some of the keys codes are custom,
 * such as Q_1, which is defined in the enum custom_keycodes above.
 */
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * KC stands for keycode, and usually is easy to read. For example, KC_A is
     * just A. A few of these are custom, such a Q_1, which is defined in the
     * enum custom_keycodes above.
     */
    /*
     * Normal Layer: this is the layer used for writing. The keyboard always gets
     * back to this layer (usually automatically).
     */
    [_LAYER1] = LAYOUT(
        Q_1,           W_2,  E_3,       R_4,       T_5,             Y_6,  U_7,       I_8,       O_9,    P_0,
        A_OR_HOLD_TAB, KC_S, D_OR_LALT, F_OR_LGUI, G_OR_HOLD_QUOT,  KC_H, J_OR_RGUI, K_OR_RALT, KC_L,   SEMICOLON_OR_HOLD_ENTER,
        KC_Z,          KC_X, KC_C,      KC_V,      KC_B,            KC_N, KC_M,      KC_COMM,   KC_DOT, TD(TD_SLSH_BSLS),

        // Thumb keys
        MEH_T(KC_SPC), OSM(MOD_LSFT), CTL_ESC, TO(_LAYER2)
    ),

    /*
     * Symbols and Numbers Layer:
     */
    [_LAYER2] = LAYOUT(
        KC_ESCAPE, KC_AT, KC_NO, KC_NO, KC_NO,               KC_CIRC, KC_AMPR,               KC_ASTR,               KC_COLON, KC_BSPC,
        KC_TAB,    KC_NO, MOD_LALT, OSM(MOD_LGUI), KC_QUOTE, KC_MINS, MT(MOD_RGUI, KC_EQL),  MT(MOD_RALT, KC_LBRC), KC_RBRC,  KC_ENTER,
        KC_GRV,    KC_NO, KC_NO, KC_NO, KC_NO,               KC_LBRC, KC_LPRN,               KC_RPRN,               KC_NO,    TO(_LAYER4),

        // Thumb keys
        TO(_LAYER1), OSM(MOD_LSFT), CTL_ESC, TO(_LAYER3)
    ),

    [_LAYER3] = LAYOUT(
        KC_ESCAPE, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, LSFT(KC_MINS),      KC_MINS, KC_7, KC_8, KC_9, KC_BSPC,
        KC_TAB,    KC_MUTE,             KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,     LSFT(KC_EQL),       KC_EQL,  KC_4, KC_5, KC_6, KC_ENTER,
        KC_LSFT,   KC_KP_ASTERISK,      KC_BRIGHTNESS_DOWN,  KC_BRIGHTNESS_UP,    KC_KP_DOT,          KC_0,    KC_1, KC_2, KC_3, TO(_LAYER4),

        // Thumb keys
        TO(_LAYER1), KC_LGUI, KC_RALT, TO(_LAYER2)
    ),

    [_LAYER4] = LAYOUT(
        KC_ESCAPE, KC_MS_WH_LEFT, KC_MS_UP,    KC_MS_WH_RIGHT, KC_Q,        LGUI(KC_LBRC),  LCTL(LSFT(KC_TAB)), RCTL(KC_TAB), LGUI(KC_RBRC), KC_BSPC,
	    KC_TAB,    KC_MS_LEFT,    KC_MS_DOWN,  KC_MS_RIGHT,    KC_NO,       KC_LEFT,        KC_DOWN,            KC_UP,        KC_RIGHT,      KC_ENTER,
        KC_GRV,    KC_MS_BTN1,    KC_MS_WH_UP, KC_MS_WH_DOWN,  KC_MS_BTN2,  KC_MS_BTN1,     KC_MS_ACCEL0,       KC_MS_ACCEL1, KC_MS_ACCEL2,  KC_NO,

        // Thumb keys
        TO(_LAYER1), KC_LGUI, KC_RALT, TO(_LAYER2)
    ),

 /*
  * Layer template
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
  /* [_LAYERINDEX] = LAYOUT(
   *   _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
   *   _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
   *   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   *                              _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
   * ),
   */
};

void keyboard_post_init_user(void) {
    /*
     * Initialize the custom keycodes timer array. This is used to keep track of
     * how long a key has been held down for.
     */
    for (int i = 0; i < CUSTOM_KEYCODES_LENGTH; i++) {
        custom_keys_tapped[i] = true;
        custom_keys_timer[i] = 0;
    }
    custom_keys_timer_initialized = true;

#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    /*
     * Starts out with a dark green color.
     */
    rgblight_sethsv_noeeprom(85, 255, 60);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#endif
}


/**
 * Tap-hold declarations
 *
 *
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_ESC:
            return 130;
        default:
            return TAPPING_TERM;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    bool is_custom_keycode = keycode >= Q_1 && keycode < END_CUSTOM_KEYCODES;
    /**
     * TAP-HOLD: CANCEL HOLD ON ANOTHER KEY ON FAST SEQUENCE
     *
     * If we're holding a tap-hold custom key and another key is pressed, we
     * should cancel the hold on the custom key.
     *
     * For example, Q tapped is Q and Q held is 1. If we are holding Q and
     * immediately type U, we cancel the hold on Q, send Q instead of 1, and
     * send U.
     *
     * Note that this wouldn't work with modifiers like CTRL (because we want to
     * keep the modifier held). That's why we're not using modified for this
     * custom tap-held code. For those we use `MT(MOD_LCTL, KC_ESC)`.
     */
    if (
            is_custom_key_pressed &&
            custom_key_down >= 0 &&
            record->event.pressed
       ) {
        tap_code(custom_keys[custom_key_down][0]);
        custom_keys_tapped[custom_key_down] = true;
        custom_keys_timer[custom_key_down] = 0;
        custom_key_down = 0;
        is_custom_key_pressed = false;
    }

    /**
     * TAP-HOLD: HANDLE CUSTOM KEYCODES
     *
     * Handle the keycode if it's within the custom keycodes range. It works in
     * tandem with matrix_scan_user(), which will send the 'letter' keycode when
     * the timer is greater than TAPPING_TERM.
     */
    if (is_custom_keycode) {
        int keyIndex = keycode - Q_1;
        /**
         * When pressed, just start a timer.
         */
        if (record->event.pressed) {
            is_custom_key_pressed = true;
            custom_key_down = keyIndex;
            custom_keys_timer[keyIndex] = timer_read();
            custom_keys_tapped[keyIndex] = false;

        /**
         * When released and not yet processed by matrix_scan_user() (which sets
         * custom_keys_tapped), it means that the key was tapped before
         * TAPPING_TERM, so we send the 'letter' keycode.
         */
        } else if(!custom_keys_tapped[keyIndex]) {
            tap_code(custom_keys[keyIndex][0]);
            is_custom_key_pressed = false;
            custom_keys_timer[keyIndex] = 0;
            custom_keys_tapped[keyIndex] = true;
        }
        return false; // Skip all further processing of this key
    }

    return true; // Process all other keycodes normally
}

/**
 * The matrix_scan_user function in QMK is called at a regular interval (every
 * matrix scan), allowing for custom code to be executed repeatedly while the
 * keyboard is on. In the context of your custom functionality, it's used to
 * check if the custom keys have been held down for longer than the tapping
 * term. If they have, it triggers the sending of the 'number' keycode, ensuring
 * that the hold action is recognized and executed even before the key is
 * released.
 */
void matrix_scan_user(void) {

    /**
     * Don't do anything unless we have initialized the system and some custom
     * key is pressed.
     */
    if (custom_keys_timer_initialized && is_custom_key_pressed) {
        for (uint16_t keyIndex = 0; keyIndex < CUSTOM_KEYCODES_LENGTH; keyIndex++) {
            if (
                    timer_elapsed(custom_keys_timer[keyIndex]) > TAPPING_TERM &&
                    !custom_keys_tapped[keyIndex]
               ) {

                tap_code_delay(custom_keys[keyIndex][1], 250);
                custom_keys_timer[keyIndex] = 0;
                custom_keys_tapped[keyIndex] = true;
                is_custom_key_pressed = false;
            }
        }
    }
}

/*
 * Sets the RGB colors for each layer.
 */
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
      case _LAYER1:
          rgblight_sethsv_noeeprom(85, 255, 60);
          break;
      case _LAYER2:
          //rgb_matrix_set_color_all(0,0,0);
          rgblight_sethsv_noeeprom(85, 255, 100);
          break;
      case _LAYER3:
          rgblight_sethsv_noeeprom(148, 255, 100);
          break;
      case _LAYER4:
          rgblight_sethsv_noeeprom(148, 255, 130);
          break;
      default:
          rgblight_sethsv_noeeprom(0, 255, 100);
          break;
    }
#endif
    return state;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (get_highest_layer(layer_state) == 0) {
            // L/R arrows
            if (clockwise) {
                tap_code(KC_DOWN);
            } else {
                tap_code(KC_UP);
            }
        } else if (get_highest_layer(layer_state) == 1) {
            // U/D arrows
            if (clockwise) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
            }
        } else if (get_highest_layer(layer_state) == 2) {
            // Page up/Page down
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
        }
    } else if (index == 1) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}
#endif
