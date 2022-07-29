/* Copyright 2022 Christopher Swenson
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

enum planck_layers {
    _ENIGMA,
    _QWERTY,
    _FN,
    _LOWER,
    _RAISE
};

enum planck_normal_keycodes {
    QWERTY = SAFE_RANGE,
    ENIGMA,
    EN_A,
    EN_B,
    EN_C,
    EN_D,
    EN_E,
    EN_F,
    EN_G,
    EN_H,
    EN_I,
    EN_J,
    EN_K,
    EN_L,
    EN_M,
    EN_N,
    EN_O,
    EN_P,
    EN_Q,
    EN_R,
    EN_S,
    EN_T,
    EN_U,
    EN_V,
    EN_W,
    EN_X,
    EN_Y,
    EN_Z,
    EN_RES,
    EN_TEST,
    EN_DIAG,
    EN_BSPC,
    EN_SREF,
    EN_SROT,
    EN_SPOS,
    EN_SRIN,
    EN_SPLU
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Enigma
    * ,-----------------------------------------------------------------------------------.
    * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |  Fn  | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
    * `-----------------------------------------------------------------------------------'
    */
    [_ENIGMA] = LAYOUT_planck_mit(
        QK_GESC, EN_Q,    EN_W,    EN_E,    EN_R,       EN_T,    EN_Y, EN_U,       EN_I,    EN_O,    EN_P,    KC_BSPC,
        KC_TAB,  EN_A,    EN_S,    EN_D,    EN_F,       EN_G,    EN_H, EN_J,       EN_K,    EN_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, EN_Z,    EN_X,    EN_C,    EN_V,       EN_B,    EN_N, EN_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_LCTL, MO(_FN), KC_LGUI, KC_LALT, MO(_LOWER),    KC_SPC,     MO(_RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    /* Qwerty
    * ,-----------------------------------------------------------------------------------.
    * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |  Fn  | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
    * `-----------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT_planck_mit(
        QK_GESC, KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,    KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,      KC_G,    KC_H,    KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,    KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_LCTL, MO(_FN), KC_LGUI, KC_LALT, MO(_LOWER),    KC_SPC,       MO(_RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    /* Function
    * ,-----------------------------------------------------------------------------------.
    * | Boot | Reset| Diag |      |      |      |      |      |      |      | Test |Revers|
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |      |Reflec|Rotors|Posn.s|Rings |Plugs |      |      |Enigma|Qwerty|      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_FN] = LAYOUT_planck_mit(
        QK_BOOT, EN_RES,  EN_DIAG, _______, _______, _______, _______, _______, _______, _______, EN_TEST, EN_BSPC,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, EN_SREF, EN_SROT, EN_SPOS, EN_SRIN, EN_SPLU, _______, _______, QWERTY,  ENIGMA,  _______, _______,
        _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
    ),
    /* Lower
    * ,-----------------------------------------------------------------------------------.
    * | ~    |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Shift|      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |  Fn  | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
    * `-----------------------------------------------------------------------------------'
    */
    [_LOWER] = LAYOUT_planck_mit(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,  KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, 
        _______, _______, _______, _______, _______, _______, _______, KC_UNDS,  KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, 
        KC_LSFT, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, 
        KC_LCTL, _______, KC_LGUI, KC_LALT, _______,       KC_SPC,      _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    /* RAISE
    * ,-----------------------------------------------------------------------------------.
    * | `    |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Shift|      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |  Fn  | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
    * `-----------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT_planck_mit(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, 
        _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, 
        KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        KC_LCTL, _______, KC_LGUI, KC_LALT, _______,      KC_SPC,      _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
};

char rotor_definitions[5][26] = {
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",
    "ESOVPZJAYQUIRHXLNFTGKDCMWB",
    "VZBRGITYUPSDNHLXAWMJQOFECK" 
};

char reflector_definitions[3][26] = {
    "EJMZALYXVBWFCRQUONTSPIKHGD",
    "YRUHQSLDPXNGOKMIEBFZCWVJAT",
    "FVPJIAOYEDRZXWGCTKUQSBNMHL"
};

char notch[5] = "QEVJZ";

typedef struct Settings {
    char rotor_order[3];
    char rotor_rings[3];
    char rotor_positions[3];
    char plugs[25];
    int plug_count;
    char reflector;
} Settings;

typedef struct KeyboardState {
    bool is_setting_reflector;
    bool is_setting_rotors;
    bool is_setting_rotor_positions;
    bool is_setting_rotor_rings;
    bool is_setting_plugs;
    char setting_progress[26];
    int setting_index;
    Settings current_settings;
    Settings default_settings;
} KeyboardState;

int bound(int letter) {
    return ((letter % 26) + 26) % 26;
}

char to_char(int letter) {
    return 'A' + letter;
}

int to_int(char letter) {
    return letter - 'A';
}

char encipher(char letter, Settings *settings) {
    int rotor_2_step = settings->rotor_positions[2] == notch[settings->rotor_order[2] - 1];
    int rotor_1_step = settings->rotor_positions[1] == notch[settings->rotor_order[1] - 1];
      
    // Advance the third rotor
    settings->rotor_positions[2]++;
    if (settings->rotor_positions[2] > 'Z') {
      settings->rotor_positions[2] -= 26;
    }

    // Maybe advance the second rotor, including double steps
    if (rotor_2_step || rotor_1_step) {
        settings->rotor_positions[1]++;
        if (settings->rotor_positions[1] > 'Z') {
            settings->rotor_positions[1] -= 26;
        }
    }

    // Maybe advance the first rotor
    if (rotor_1_step) {
        settings->rotor_positions[0]++;
        if (settings->rotor_positions[0] > 'Z') {
            settings->rotor_positions[0] -= 26;
        }
    }

    // Swap letters on plugboard
    for (int i = 0; i < settings->plug_count * 2; i += 2) {
        if (letter == settings->plugs[i]) {
            letter = settings->plugs[i + 1];
        } else if (letter == settings->plugs[i + 1]) {
            letter = settings->plugs[i];
        }  
    }

    // Rotors (right to left)
    for (int rotor_index = 2; rotor_index >= 0; rotor_index--) {
        char *rotor_definition = rotor_definitions[settings->rotor_order[rotor_index] - 1];
        int position = to_int(settings->rotor_positions[rotor_index]);
        int ring = to_int(settings->rotor_rings[rotor_index]);
        int char_index = to_int(letter);
        letter = to_char(bound(
            to_int(rotor_definition[bound(char_index + position - ring)]) + ring - position
        ));
    }

    // Swap via reflector
    letter = reflector_definitions[to_int(settings->reflector)][to_int(letter)];

    // Rotors in reverse (left to right)
    for (int rotor_index = 0; rotor_index < 3; rotor_index++) {
        char *rotor_definition = rotor_definitions[settings->rotor_order[rotor_index] - 1];
        int position = to_int(settings->rotor_positions[rotor_index]);
        int ring = to_int(settings->rotor_rings[rotor_index]);
        int search_index;
        for (search_index = 0; search_index < 26; search_index++) {
            if (
                rotor_definition[search_index] 
                == to_char(bound(to_int(letter) - ring + position))
            ) {
                break;
            }
        }
        letter = to_char(bound(search_index - position + ring));
    }
    
    // Plugboard again
    for (int i = 0; i < settings->plug_count * 2; i += 2) {
        if (letter == settings->plugs[i]) {
            letter = settings->plugs[i + 1];
        } else if (letter == settings->plugs[i + 1]) {
            letter = settings->plugs[i];
        }
    }

    return letter;
}

void init_enigma_default(Settings *settings) {
    settings->rotor_order[0] = 1;
    settings->rotor_rings[0] = 'A';
    settings->rotor_positions[0] = 'A';

    settings->rotor_order[1] = 2;
    settings->rotor_rings[1] = 'A';
    settings->rotor_positions[1] = 'A';

    settings->rotor_order[2] =  3;
    settings->rotor_rings[2] = 'A';
    settings->rotor_positions[2] = 'A';

    strcpy(settings->plugs, "");
    settings->plug_count = 0;

    settings->reflector = 'B';
}

void copy_settings(Settings *from, Settings *to) {
    to->rotor_order[0] = from->rotor_order[0];
    to->rotor_rings[0] = from->rotor_rings[0];
    to->rotor_positions[0] = from->rotor_positions[0];

    to->rotor_order[1] = from->rotor_order[1];
    to->rotor_rings[1] = from->rotor_rings[1];
    to->rotor_positions[1] = from->rotor_positions[1];

    to->rotor_order[2] = from->rotor_order[2];
    to->rotor_rings[2] = from->rotor_rings[2];
    to->rotor_positions[2] = from->rotor_positions[2];

    strncpy(to->plugs, from->plugs, from->plug_count * 2);
    to->plug_count = from->plug_count;

    to->reflector = from->reflector;
}

char *rotor_name(int rotor_number) {
    if (rotor_number == 1) {
        return "I";
    } else if (rotor_number == 2) {
        return "II";
    } else if (rotor_number == 3) {
        return "III";
    } else if (rotor_number == 4) {
        return "IV";
    } else if (rotor_number == 5) {
        return "V";
    }
    return "?";
}

void rotors_reverse(Settings *settings) {
    int rotor_2_step = settings->rotor_positions[2] 
        == to_char(bound(to_int(notch[settings->rotor_order[2] - 1]) + 1));
    int rotor_1_step = settings->rotor_positions[1] 
        == to_char(bound(to_int(notch[settings->rotor_order[1] - 1]) + 1));
      
    // Reverse third rotor
    settings->rotor_positions[2]--;
    if (settings->rotor_positions[2] < 'A') {
        settings->rotor_positions[2] += 26;
    }

    // Maybe reverse second rotor (including double steps)
    if (rotor_2_step || rotor_1_step) {
        settings->rotor_positions[1]--;
        if (settings->rotor_positions[1] < 'A') {
            settings->rotor_positions[1] += 26;
        }
    }

    // Maybe recerse first rotor
    if (rotor_1_step) {
        settings->rotor_positions[0]--;
        if (settings->rotor_positions[0] < 'A') {
            settings->rotor_positions[0] += 26;
        }
    }
}

void reset_settings(KeyboardState *state) {
  copy_settings(&state->default_settings, &state->current_settings);
}

void set_layer(uint8_t default_layer) {
    default_layer_set((layer_state_t)1 << default_layer);
}

void set_backlight(uint8_t mode, uint8_t hue, uint8_t sat, uint8_t val) {
    #ifdef RGBLIGHT_ENABLE
        rgblight_enable_noeeprom(); 
        rgblight_mode_noeeprom(mode);
        rgblight_sethsv_noeeprom(hue, sat, val);
    #endif
}

void clear_working_settings(KeyboardState *state) {
    state->is_setting_reflector = false;
    state->is_setting_rotors = false;
    state->is_setting_rotor_positions = false;
    state->is_setting_rotor_rings = false;
    state->is_setting_plugs = false;
    state->setting_index = 0;
    set_layer(_ENIGMA);
    set_backlight(RGBLIGHT_MODE_STATIC_LIGHT, HSV_RED);
}

void send_settings_string(Settings *settings) {
    send_char(settings->reflector);
    send_string(". ");
    send_string(rotor_name(settings->rotor_order[0]));
    send_char(settings->rotor_rings[0]);
    send_string("-");
    send_string(rotor_name(settings->rotor_order[1]));
    send_char(settings->rotor_rings[1]);
    send_string("-");
    send_string(rotor_name(settings->rotor_order[2]));
    send_char(settings->rotor_rings[2]);
    send_string(" (");
    send_char(settings->rotor_positions[0]);
    send_string(", ");
    send_char(settings->rotor_positions[1]);
    send_string(", ");
    send_char(settings->rotor_positions[2]);
    send_string(") ");
    for (int i = 0; i < settings->plug_count; i++) {
        send_char(settings->plugs[i * 2]);
        send_char(settings->plugs[i * 2 + 1]);
        send_string(" ");
    }
    send_string("\n");
}

void perform_test(Settings *settings) {
    for (int i = 0; i < 1000; i++) {
        send_char(encipher('A', settings) - ('A' - 'a'));
    }
}

void commit_plug_settings(KeyboardState *state) {
    state->default_settings.plug_count = state->setting_index / 2; 
    for (int i = 0; i < state->default_settings.plug_count; i++) {
        state->default_settings.plugs[i * 2] = state->setting_progress[i * 2];
        state->default_settings.plugs[i * 2 + 1] = state->setting_progress[i * 2 + 1];
    }
    reset_settings(state);
    clear_working_settings(state);
}

void handle_set_reflector(char letter, KeyboardState *state) {
    if (letter >= 'A' && letter <= 'C') {
        state->default_settings.reflector = letter;
        reset_settings(state);
        clear_working_settings(state);
    }
}

bool handle_set_rotor(char letter, KeyboardState *state) {
    bool is_valid = letter >= 'A' && letter <= 'E' && state->setting_index < 3;
    if (is_valid) {
        state->setting_progress[state->setting_index] = to_int(letter) + 1;
        state->setting_index += 1;
        if (state->setting_index == 3) {
            state->default_settings.rotor_order[0] = state->setting_progress[0];
            state->default_settings.rotor_order[1] = state->setting_progress[1];
            state->default_settings.rotor_order[2] = state->setting_progress[2];
            reset_settings(state);
            clear_working_settings(state);
        }
    }
    return is_valid;
}

bool handle_set_rotor_position(char letter, KeyboardState *state) {
    bool is_valid = state->setting_index < 3; // Guaranteed to be A-Z already
    if (is_valid) {
        state->setting_progress[state->setting_index] = letter;
        state->setting_index += 1;
        if (state->setting_index == 3) {
            state->default_settings.rotor_positions[0] = state->setting_progress[0];
            state->default_settings.rotor_positions[1] = state->setting_progress[1];
            state->default_settings.rotor_positions[2] = state->setting_progress[2]; 
            reset_settings(state);
            clear_working_settings(state);
        }
    }
    return is_valid;
}

bool handle_set_rotor_ring(char letter, KeyboardState *state) {
    bool is_valid = state->setting_index < 3;
    if (is_valid) {
        state->setting_progress[state->setting_index] = letter;
        state->setting_index += 1;
        if (state->setting_index == 3) {
            state->default_settings.rotor_rings[0] = state->setting_progress[0];
            state->default_settings.rotor_rings[1] = state->setting_progress[1];
            state->default_settings.rotor_rings[2] = state->setting_progress[2];
            reset_settings(state);
            clear_working_settings(state);
        }
    }
    return is_valid;
}

bool handle_set_plug(char letter, KeyboardState *state) {
    bool is_valid = state->setting_index < 26;
    if (is_valid) {
        state->setting_progress[state->setting_index] = letter;
        state->setting_index += 1;
    }
    return is_valid;
}

void handle_enigma_keypress(char letter, bool any_mods, KeyboardState *state) {
    bool settings_valid = true;
    if (letter) {
        if (any_mods) {
            tap_code(KC_A + to_int(letter));
        } else if (state->is_setting_reflector) {
            handle_set_reflector(letter, state);
        } else if (state->is_setting_rotors) {
            settings_valid = handle_set_rotor(letter, state);
        } else if (state->is_setting_rotor_positions) {
            settings_valid = handle_set_rotor_position(letter, state);
        } else if (state->is_setting_rotor_rings) {
            settings_valid = handle_set_rotor_ring(letter, state);
        } else if (state->is_setting_plugs) {
            settings_valid = handle_set_plug(letter, state);
        } else {
            char c2 = encipher(letter, &state->current_settings);
            send_char(c2 - ('A' - 'a'));
        }
    }
    if (!settings_valid) {
        clear_working_settings(state);
    }
}

KeyboardState STATE;

void keyboard_pre_init_user(void) {
    init_enigma_default(&STATE.default_settings);
    init_enigma_default(&STATE.current_settings);
    clear_working_settings(&STATE);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t letter_index;
    bool letter_found = false;
    if (record->event.pressed) {
        switch (keycode) {
          case QWERTY:
              set_layer(_QWERTY);
              set_backlight(RGBLIGHT_MODE_RAINBOW_SWIRL + 4, HSV_PURPLE);
              break;
          case ENIGMA:
              set_layer(_ENIGMA);
              set_backlight(RGBLIGHT_MODE_STATIC_LIGHT, HSV_RED);
              break;
          case EN_SREF:
              reset_settings(&STATE);
              STATE.is_setting_reflector = true;
              set_layer(_ENIGMA);
              set_backlight(RGBLIGHT_MODE_SNAKE, HSV_RED);
              break;
          case EN_SROT:
              reset_settings(&STATE);
              STATE.is_setting_rotors = true;
              STATE.setting_index = 0;
              set_layer(_ENIGMA);
              set_backlight(RGBLIGHT_MODE_SNAKE, 10, 255, 255);
              break;
          case EN_SPOS:
              reset_settings(&STATE);
              STATE.is_setting_rotor_positions = true;
              STATE.setting_index = 0;
              set_layer(_ENIGMA);
              set_backlight(RGBLIGHT_MODE_SNAKE, HSV_ORANGE);
              break;
          case EN_SRIN:
              reset_settings(&STATE);
              STATE.is_setting_rotor_rings = true;
              STATE.setting_index = 0;
              set_layer(_ENIGMA);
              set_backlight(RGBLIGHT_MODE_SNAKE, HSV_GREEN);
              break;
          case EN_SPLU:
              reset_settings(&STATE);
              STATE.is_setting_plugs = true;
              STATE.setting_index = 0;
              set_layer(_ENIGMA);
              set_backlight(RGBLIGHT_MODE_SNAKE, HSV_BLUE);
              break;
          case QK_GESC:
              if (
                  STATE.is_setting_reflector
                  || STATE.is_setting_rotors
                  || STATE.is_setting_rotor_positions
                  || STATE.is_setting_rotor_rings
                  || STATE.is_setting_plugs
              ) {
                  clear_working_settings(&STATE);
                  return false;
              }
              break;
          case KC_ENT:
              if (STATE.is_setting_plugs) { 
                  commit_plug_settings(&STATE);
                  return false;
              }
              break;
          case EN_A ... EN_Z:
              letter_index = keycode - EN_A;
              letter_found = true;
              break;
          case EN_RES:
              reset_settings(&STATE);
              break;
          case EN_TEST:
              perform_test(&STATE.current_settings);
              break;
          case EN_DIAG:
              send_settings_string(&STATE.current_settings);
              break;
          case EN_BSPC:
              rotors_reverse(&STATE.current_settings);
              tap_code(KC_BSPC);
              break;
      }
    }
    char letter = letter_found ? 'A' + letter_index : 0;
    uint8_t mods = get_mods();
    bool any_mods = (mods & MOD_MASK_CTRL) || (mods & MOD_MASK_ALT) || (mods & MOD_MASK_GUI);
    handle_enigma_keypress(letter, any_mods, &STATE);
    return true;
}

void keyboard_post_init_user(void) {
    set_layer(_QWERTY);
    set_backlight(RGBLIGHT_MODE_RAINBOW_SWIRL + 4, HSV_PURPLE);
}
