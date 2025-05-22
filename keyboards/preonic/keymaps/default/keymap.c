
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
 
// Key combo ctrl-shift-/ enables midi mode with the layout:

//  Octave 6 (C6–B6):
// ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
// │ Q│ W│ E│ R│ T│ Y│ U│ I│ O│ P│[ │] │
// └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘

// Octave 5 (C5–B5):
// ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
// │ A│ S│ D│ F│ G│ H│ J│ K│ L│ ;│ '│\ │
// └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘

// Octave 4 (C4–B4):
// ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
// │ Z│ X│ C│ V│ B│ N│ M│ ,│ .│ /│
// └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘

// Key combo ctrl-shift-/ returns to Qwerty

#include QMK_KEYBOARD_H
#include "midi.h"

// Layer definitions
enum layer_names {
    _BASE,
};

// Custom keycodes
enum custom_keycodes {
    MIDI_TOG = SAFE_RANGE,
};

// Track MIDI mode
bool midi_mode = false;

// MIDI device
midi_device_t midi_device = {
    .cable_number = 0,
    .port = MIDIPORT_USB
};

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_preonic_grid(
        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
        KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,
        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,
        KC_ESC, KC_TAB, KC_LCTL,KC_LSFT,KC_LALT,KC_SPC, KC_ENT, KC_BSPC,KC_DEL, KC_RGUI,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,MIDI_TOG
    ),
};

// Process key events
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == MIDI_TOG && record->event.pressed) {
        midi_mode = !midi_mode;
        if (midi_mode) {
            uprintf("MIDI mode enabled\n");
        } else {
            uprintf("MIDI mode disabled\n");
        }
        return false;
    }

    if (midi_mode && record->event.pressed) {
        switch (keycode) {
            case KC_A ... KC_Z:
            case KC_1 ... KC_0:
                midi_send_noteon(&midi_device, 0, 60 + (keycode % 40), 127);
                return false;
        }
    }

    return true;
}

// Combo: Ctrl + Shift + / → Toggle MIDI
const uint16_t PROGMEM midi_combo[] = {KC_LCTL, KC_LSFT, KC_SLSH, COMBO_END};
combo_t key_combos[] = {
    COMBO(midi_combo, MIDI_TOG),
};
