#include QMK_KEYBOARD_H

enum plaid_layers {
    _QWERTY,
    _DVORAK,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _FUNCTION,
};

enum plaid_keycodes { QWERTY = SAFE_RANGE, COLEMAK, DVORAK, LED };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define LED_ON 1
#define LED_OFF 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | LS/( |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | LGUI | Alt  |   [  |Lower |    Space    |Raise |   ]  | RGUI |   \  | RS/) |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_planck_mit(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, KC_LCTL, KC_LGUI, KC_LALT, KC_LBRC, LOWER, KC_SPC, RAISE, KC_RBRC, KC_RGUI, KC_BSLS, KC_RSPC),

    /* Colemak
     * ,-----------------------------------------------------------------------------------.
     * | Esc  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Tab  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | LS/( |   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | LGUI | Alt  |   [  |Lower |    Space    |Raise |   ]  | RGUI |   \  | RS/) |
     * `-----------------------------------------------------------------------------------'
     */

    [_COLEMAK] = LAYOUT_planck_mit(KC_ESC, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC, KC_TAB, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, KC_LCTL, KC_RALT, KC_LALT, KC_LGUI, LOWER, KC_SPC, RAISE, KC_RBRC, KC_RGUI, KC_BSLS, KC_RSPC),

    /* Dvorak
     * ,-----------------------------------------------------------------------------------.
     * | Esc  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Tab  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | LGUI | Alt  |   [  |Lower |    Space    |Raise |   ]  | RGUI |   \  | RS/) |
     * `-----------------------------------------------------------------------------------'
     */

    [_DVORAK] = LAYOUT_planck_mit(KC_ESC, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC, KC_TAB, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_SLSH, KC_LSPO, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_ENT, KC_LCTL, KC_RALT, KC_LALT, KC_LGUI, LOWER, KC_SPC, RAISE, KC_RBRC, KC_RGUI, KC_BSLS, KC_RSPC),

    /* LOWER
     * ,----------------------------------------------------------------------------.
     * |      |      | MPRV | MPLY | MNXT |     |     |     | PGUP| UP  | PGDN|PSCR |
     * |------+------+------+------+------+-----+-----+-----+-----+-----------+-----+
     * |      |      | MUTE | VOLD | VOLU |     |     |     | LEFT| DOWN|RIGHT|     |
     * |------+------+------+------+------+-----+-----+-----+-----+-----+-----+-----+
     * |      |      | MAIL | WBAK | WFWD |     |     |     | HOME|     | END |     |
     * |------+------+------+------+------+-----+-----+-----+-----+-----------+-----+
     * |      |      |      |      |      |    DEL    |     |     |     |     |     |
     * `----------------------------------------------------------------------------'
     */

    [_LOWER] = LAYOUT_planck_mit(KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_UP, KC_PGDN, KC_PSCR, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_MAIL, KC_WBAK, KC_WFWD, KC_NO, KC_NO, KC_NO, KC_HOME, KC_NO, KC_END, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

    /* RAISE
     * ,--------------------------------------------------------------------------------.
     * | NLCK |  1   |  2   |  3   |  -   |     |     |     |  !   |  #   |  $   |  +   |
     * |------+------+------+------+------+-----+-----+-----+------+------+------+------+
     * |   /  |  4   |  5   |  6   |  +   |     |     |     |  %   |  !   |  !   |  =   |
     * |------+------+------+------+------+-----+-----+-----+------+------+------+------+
     * |   *  |  7   |  8   |  9   |  ,   |     |     |     |  _   |  -   |  @   |  ~   |
     * |------+------+------+------+------+-----+-----+-----+------+------+------+------+
     * |      |  0   |  .   | Ent  |  =   |           |     |      |      |      |  `   |
     * `--------------------------------------------------------------------------------'
     */

    [_RAISE] = LAYOUT_planck_mit(KC_NLCK, KC_P1, KC_P2, KC_P3, KC_PMNS, KC_NO, KC_NO, KC_NO, KC_EXLM, KC_HASH, KC_DLR, KC_PLUS, KC_PSLS, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_NO, KC_NO, KC_NO, KC_PERC, KC_ASTR, KC_AMPR, KC_EQL, KC_PAST, KC_P7, KC_P8, KC_P9, KC_PCMM, KC_NO, KC_NO, KC_NO, KC_UNDS, KC_MINS, KC_AT, KC_TILDE, KC_NO, KC_P0, KC_PDOT, KC_PENT, KC_PEQL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GRV),

    /* Function (Lower + Raise)
     * ,-----------------------------------------------------------------------------------------------------------------------.
     * | RESET| LCA_T(F1)  | LCA_T(F2) | LCA_T(F3) | LCA_T(F4) | LCA_T(F5) | LCA_T(F6) | LCA_T(F7) |      |      |      |      |
     * |------+------------+-----------+-----------+-----------+-----------+-----------+-----------+------+------+------+------+
     * |      |            |           |           |           | QWERTY    | DVORAK    | COLEMAK   |      |      |      |      |
     * |------+------------+-----------+-----------+-----------+-----------+-----------+-----------+------+------+------+------+
     * |      |            |           |           |           |           |           |           |      |      |      |      |
     * |------+------------+-----------+-----------+-----------+-----------+-----------+-----------+------+------+------+------+
     * |      |            |           |           |           |          LED          |           |      |      |      |      |
     * `-----------------------------------------------------------------------------------------------------------------------'
     */

    [_FUNCTION] = LAYOUT_planck_mit(RESET, LCA_T(KC_F1), LCA_T(KC_F2), LCA_T(KC_F3), LCA_T(KC_F4), LCA_T(KC_F5), LCA_T(KC_F6), LCA_T(KC_F7), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QWERTY, DVORAK, COLEMAK, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LED, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)};

// constants to toggle LED behavior

// Setup config struct for LED
typedef union {
    uint32_t raw;
    struct {
        bool red_mode : 1;
        bool green_mode : 1;
    };
} led_config_t;
led_config_t led_config;

void keyboard_post_init_user(void) { led_config.raw = eeconfig_read_user(); }

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    led_config.raw        = 0;
    led_config.red_mode   = LED_ON;
    led_config.green_mode = LED_ON;
    eeconfig_update_user(led_config.raw);
    eeconfig_update_user(led_config.raw);
}

// When LOWER and RAISE are held together, go to the FUNCTION layer
layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _FUNCTION); }

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    switch (layer) {
        case _LOWER:
            writePinHigh(LED_RED);
            break;
        case _RAISE:
            writePinHigh(LED_GREEN);
            break;
        default:
            writePinLow(LED_GREEN);
            writePinLow(LED_RED);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
            break;
        case LED:
            if (record->event.pressed) {
                if (led_config.red_mode == LED_ON && led_config.green_mode == LED_ON) {
                    led_config.red_mode   = LED_OFF;
                    led_config.green_mode = LED_OFF;
                } else if (led_config.red_mode == LED_OFF && led_config.green_mode == LED_OFF) {
                    led_config.red_mode   = LED_ON;
                    led_config.green_mode = LED_ON;
                }
            }
            eeconfig_update_user(led_config.raw);
            return false;
            break;
    }
    return true;
}
