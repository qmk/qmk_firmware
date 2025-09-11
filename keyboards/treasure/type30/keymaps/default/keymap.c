/* Copyright 2025 Treasure
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// define combo names
enum combos {
    COMBO_TRSPC,
    COMBO_TRHME,
    COMBO_TREND,
    COMBO_TRENT,
    COMBO_RVAL,
    COMBO_RVALD,
    COMBO_LENGTH
};

// Define a custom keycode
enum custom_keycodes {
    TAP_KC_LSFT = SAFE_RANGE
};

uint16_t COMBO_LEN = COMBO_LENGTH;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t shift_timer; // Timer to differentiate tap vs. hold

    switch (keycode) {
        case TAP_KC_LSFT:
            if (record->event.pressed) {
                shift_timer = timer_read(); // Start timer on key press
                register_code(KC_LSFT);    // Register Shift immediately for hold behavior
            } else {
                unregister_code(KC_LSFT);  // Unregister Shift on key release
                if (timer_elapsed(shift_timer) < TAPPING_TERM) {
                    // If released quickly, treat as tap and send Space
                    tap_code(KC_SPC);
                }
            }
            return false; // Skip further processing for this key
    }
    return true; // Process other keys normally
}
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        TAP_KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, MO(1), KC_SPC,
        KC_LCTL, KC_LALT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_RGUI, KC_UP, KC_DOWN
    ),
    [1] = LAYOUT(
        KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
        KC_TRNS, KC_PLUS, KC_MINUS, KC_SLASH, KC_KP_ASTERISK, KC_LBRC, KC_RBRC,KC_BACKSLASH, KC_SCLN, KC_QUOT, KC_TRNS, KC_ENT,
        KC_TRNS, KC_TRNS, KC_EQL, RM_TOGG,RM_HUEU, RM_NEXT,  KC_GRAVE, KC_COMMA,  KC_DOT, KC_TRNS, KC_LEFT, KC_RIGHT
    )
};

// define keys that make up combos
const uint16_t PROGMEM fd_combo1[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM fd_combo2[] = {KC_UP, KC_DOWN, COMBO_END};
const uint16_t PROGMEM fd_combo3[] = {KC_LEFT, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM fd_combo7[] = {MO(1), KC_SPC, COMBO_END};

const uint16_t PROGMEM fd_combo8[] = {RGB_TOG, RGB_HUI, COMBO_END};
const uint16_t PROGMEM fd_combo9[] = {RGB_HUI, RGB_MOD, COMBO_END};



// map combo names to their keys and the key they trigger
combo_t key_combos[] = {
    [COMBO_TRSPC] = COMBO(fd_combo1, KC_SPC),
    [COMBO_TRHME] = COMBO(fd_combo2, KC_ENT),
    [COMBO_TREND] = COMBO(fd_combo3, KC_END),
    [COMBO_TRENT] = COMBO(fd_combo7, KC_ENT),
    [COMBO_RVAL] = COMBO(fd_combo8, KC_NO),
    [COMBO_RVALD] = COMBO(fd_combo9, KC_NO),

    // more here...
};

// Custom combo event handler
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case COMBO_RVAL:
            if (pressed) {
                rgblight_decrease_val(); // Decrease brightness
            }
            break;

        case COMBO_RVALD:
            if (pressed) {
                rgblight_increase_val(); // Decrease brightness
            }
            break;
    }
}
