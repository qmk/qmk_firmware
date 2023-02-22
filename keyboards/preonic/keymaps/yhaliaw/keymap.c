/* Copyright 2021 Andrew Liaw
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
#include QMK_KEYBOARD_H

enum preonic_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum preonic_keycodes {
  L_RESET = SAFE_RANGE,
};

#ifdef AUDIO_ENABLE
float planck_sound[][2] = SONG(PLANCK_SOUND);
#endif

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Leader| Ctrl | Alt  | GUI  | Lower| Enter| Space| Raise| GUI  | Alt  | Ctrl | Del  |
     * `-----------------------------------------------------------------------------------'
     */
    [_BASE] = LAYOUT_preonic_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        QK_LEAD, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_ENT,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, KC_DEL
    ),

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Caps |      |      |      |      |      | Left | Down |  Up  | Right|      |  \   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      | Home | End  | Pg Up| Pg Dn|      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_preonic_grid(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_BSLS,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_END,  KC_PGUP, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Raise
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  |   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   _  |   +  |   {  |   }  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Adjust (Lower + Raise)
     * ,-----------------------------------------------------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | Reset| Debug| Clear|  RGB | HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |Aud on|Audoff| Swap | Norm |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |Mus on|Musoff| NKRO | 6KRO |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_preonic_grid(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, L_RESET, DB_TOGG, EE_CLR,  RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
        _______, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  AG_SWAP, AG_NORM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, MU_ON,   MU_OFF,  NK_ON,   NK_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

const rgblight_segment_t PROGMEM base_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 9, 0, 0, 0});

const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_RED});

const rgblight_segment_t PROGMEM raise_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_GREEN});

const rgblight_segment_t PROGMEM adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_BLUE});

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 5, HSV_WHITE});

// Later layers take precedence.
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base_layer,
    lower_layer,
    raise_layer,
    adjust_layer,
    capslock_layer
);

bool audio_disable = false;

void keyboard_pre_init_user(void) {
    // If the audio is off during hardware init,
    // it causes problem when the audio is turn on later.
    // The workaround is to always set the audio on during hardware init,
    // then toggle audio back to the setting.
#ifdef AUDIO_ENABLE
    if (!is_audio_on()) {
        audio_disable = true;
        audio_on();
    }
#endif
}

void matrix_init_user(void) {
    // To fix a audio related problem. See comments in keyboard_pre_init_user().
#ifdef AUDIO_ENABLE
    if (audio_disable) {
        audio_off();
    }
#endif
}

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
    rgblight_set_layer_state(0, true);
}

bool leader_found;
LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading      = false;
        leader_found = false;
        SEQ_ONE_KEY(L_RESET) {
            leader_found = true;
            reset_keyboard();
        }
        else
            SEQ_ONE_KEY(KC_DEL) {
            leader_found = true;
            layer_clear();
        }
        else
            SEQ_ONE_KEY(LOWER) {
            leader_found = true;
            layer_on(_LOWER);
        }
        else
            SEQ_ONE_KEY(RAISE) {
            leader_found = true;
            layer_on(_RAISE);
        }
        leader_end();
    }
}

void leader_end(void) {
    // Plays sound on if leader sequence found.
    if (leader_found) {
#ifdef AUDIO_ENABLE
        PLAY_SONG(planck_sound);
#endif
    }
}

bool led_update_user(led_t led_state) {
    // Turn on RBG for capslock.
    rgblight_set_layer_state(4, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Set RBG layer according to active keymap layer.
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 1) && layer_state_cmp(state, 2));
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
