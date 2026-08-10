// qmk compile -kb bastardkb/tbkmini/promicro -km custom -e CONVERT_TO=rp2040_ce -e EEPROM_CLEAR=yes

// ============================================================================
// Encoder Configuration (if present)
// ============================================================================
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, [_LOWER] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)}, [_RAISE] = {ENCODER_CCW_CW(KC_BRID, KC_BRIU)}, [_FUNCTION] = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT)}, [_TERMINAL] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif

#include QMK_KEYBOARD_H

// Layer definitions
enum layer_names { _BASE = 0, _LOWER, _RAISE, _FUNCTION, _TERMINAL };

// Custom keycodes
enum custom_keycodes {
    CTRL_SPC = SAFE_RANGE,
    CTRL_H,
    CTRL_J,
    CTRL_K,
    CTRL_L,
    SYM_1,     // ! only
    W_AT,      // W normally, @ when shifted
    SYM_3,     // # only
    SYM_4,     // $ only
    SYM_5,     // % only
    SYM_6,     // ^ only
    SYM_7,     // & only
    SYM_8,     // * only
    SYM_9,     // ( only
    SYM_0,     // ) only
    QUOT_APOS, // " normally, ' when shifted

    // Terminal control keycodes (fixed for macOS)
    TERM_NEW_TAB,
    TERM_CLOSE_TAB,
    TERM_CLOSE_WIN,
    TERM_NEXT_TAB,
    TERM_PREV_TAB,
    TERM_TAB_1,
    TERM_TAB_2,
    TERM_TAB_3,
    TERM_TAB_4,
    TERM_TAB_5,
    TERM_SPLIT_H,
    TERM_SPLIT_V,
    TERM_WIN_LEFT,
    TERM_WIN_DOWN,
    TERM_WIN_UP,
    TERM_WIN_RIGHT,
    TERM_NEXT_WIN,
    TERM_PREV_WIN,
    TERM_ZOOM,
    TERM_FULLSCREEN,
    TERM_SCROLL_UP,
    TERM_SCROLL_DN,
    TERM_HOME,
    TERM_END,
    TERM_CLEAR_LINE,
    TERM_CLEAR_SCRN,
    TERM_FONT_INC,
    TERM_FONT_DEC,
    TERM_FONT_RST,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // ============================================================================
    // BASE LAYER - QWERTY with Alt access and ergonomic improvements
    // Left thumb: TAB → SHIFT → ENTER | Right thumb: SPACE ← BACKSPACE ← CMD+ESC
    // ============================================================================
    [_BASE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        LCTL_T(KC_TAB), KC_LSFT, LT(_LOWER, KC_ENT), LT(_RAISE, KC_SPC), KC_BSPC, LCMD_T(KC_ESC)
        //`--------------------------'  `--------------------------'
        ),

    // ============================================================================
    // LOWER LAYER - Numbers & Navigation for Coding
    // ============================================================================
    [_LOWER] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, KC_1, KC_2, KC_3, KC_4, KC_5, MS_BTN1, MS_WHLU, MS_BTN2, KC_DEL, KC_INS, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_6, KC_7, KC_8, KC_9, KC_0, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, KC_PGUP, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, LCMD(KC_Z), LCMD(KC_X), LCMD(KC_C), LCMD(KC_V), LCMD(KC_B), MS_BTN3, MS_WHLD, KC_HOME, KC_END, KC_PGDN, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_LSFT, _______, _______, KC_BSPC, KC_LCMD
        //`--------------------------'  `--------------------------'
        ),

    // ============================================================================
    // RAISE LAYER - Programming Symbols (Numbers available in LOWER layer)
    // Top row: !@#$%^&*() - symbols only
    // Punctuation: ,.;/ naturally shift to <>:? (NO duplicate symbols)
    // Backtick and tilde as separate keys in good positions
    // HJKL: Normal symbols, or arrow keys when Ctrl is held
    // CTRL+SEMICOLON: Spotlight (CMD+SPACE) when Ctrl is held
    // ============================================================================
    [_RAISE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, SYM_1, W_AT, SYM_3, SYM_4, SYM_5, SYM_6, SYM_7, SYM_8, SYM_9, SYM_0, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_EQL, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, CTRL_H, CTRL_J, CTRL_K, CTRL_L, CTRL_SPC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_GRV, KC_BSLS, KC_PIPE, KC_TILD, QUOT_APOS, KC_PLUS, KC_QUOT, KC_COMM, KC_DOT, LALT_T(KC_SLSH), XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        LCTL_T(KC_TAB), KC_LSFT, MO(_TERMINAL), _______, KC_BSPC, KC_LCMD
        //`--------------------------'  `--------------------------'
        ),

    // ============================================================================
    // FUNCTION LAYER - F-keys & Mac System Controls (Ergonomic Layout)
    // ============================================================================
    [_FUNCTION] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_F11, KC_F12, KC_BRID, KC_BRIU, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LCMD(LSFT(KC_3)), LCMD(LSFT(KC_4)), LCMD(LSFT(KC_5)), XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, XXXXXXX, XXXXXXX, KC_SPC, KC_BSPC, KC_LCMD
        //`--------------------------'  `--------------------------'
        ),

    // ============================================================================
    // TERMINAL LAYER - Direct Terminal Control (LOWER + RAISE)
    // Fixed for macOS Terminal/iTerm2/Kitty compatibility + Neovim split resizing
    // Left hand: Window/Tab/Split management | Right hand: Navigation + Neovim
    // Hold Shift + HJKL for Neovim split resizing
    // ============================================================================
    [_TERMINAL] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, TERM_TAB_1, TERM_TAB_2, TERM_TAB_3, TERM_TAB_4, TERM_TAB_5, TERM_SCROLL_UP, TERM_FONT_INC, TERM_FONT_DEC, TERM_FONT_RST, TERM_CLEAR_SCRN, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, TERM_NEW_TAB, TERM_SPLIT_H, TERM_SPLIT_V, TERM_NEXT_TAB, TERM_PREV_TAB, TERM_WIN_LEFT, TERM_WIN_DOWN, TERM_WIN_UP, TERM_WIN_RIGHT, TERM_SCROLL_DN, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, TERM_ZOOM, TERM_CLOSE_WIN, TERM_CLOSE_TAB, TERM_FULLSCREEN, XXXXXXX, TERM_HOME, TERM_PREV_WIN, TERM_NEXT_WIN, TERM_END, TERM_CLEAR_LINE, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        TG(_FUNCTION), _______, _______, _______, _______, KC_RSFT
        //`--------------------------'  `--------------------------'
        )};

// ============================================================================
// Layer State Management
// ============================================================================
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _TERMINAL);
}

// ============================================================================
// Key Combo Definitions (Optional - for advanced users)
// ============================================================================
#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_esc[]   = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_tab[]   = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo_enter[] = {KC_L, KC_SCLN, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_esc, KC_ESC),
    COMBO(combo_tab, KC_TAB),
    COMBO(combo_enter, KC_ENT),
};
#endif

// ============================================================================
// Custom Key Processing
// ============================================================================
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTRL_SPC:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_CTRL) {
                    // Clear Ctrl modifier temporarily, send CMD+SPACE, then restore
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code16(LCMD(KC_SPC));
                    set_mods(mods);
                } else {
                    // Otherwise send semicolon
                    tap_code(KC_SCLN);
                }
            }
            return false;

        // Symbol keys - symbols only (numbers available in LOWER layer)
        case SYM_1:
            if (record->event.pressed) {
                tap_code16(KC_EXLM); // !
            }
            return false;

        case W_AT:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // Clear shift temporarily, send @, then restore
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code16(KC_AT);
                    set_mods(mods);
                } else {
                    // Send W
                    tap_code(KC_W);
                }
            }
            return false;

        case SYM_3:
            if (record->event.pressed) {
                tap_code16(KC_HASH); // #
            }
            return false;

        case SYM_4:
            if (record->event.pressed) {
                tap_code16(KC_DLR); // $
            }
            return false;

        case SYM_5:
            if (record->event.pressed) {
                tap_code16(KC_PERC); // %
            }
            return false;

        case SYM_6:
            if (record->event.pressed) {
                tap_code16(KC_CIRC); // ^
            }
            return false;

        case SYM_7:
            if (record->event.pressed) {
                tap_code16(KC_AMPR); // &
            }
            return false;

        case SYM_8:
            if (record->event.pressed) {
                tap_code16(KC_ASTR); // *
            }
            return false;

        case SYM_9:
            if (record->event.pressed) {
                tap_code16(KC_LPRN); // (
            }
            return false;

        case SYM_0:
            if (record->event.pressed) {
                tap_code16(KC_RPRN); // )
            }
            return false;

        case QUOT_APOS:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // Clear shift temporarily, send ', then restore
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_QUOT);
                    set_mods(mods);
                } else {
                    // Send "
                    tap_code16(KC_DQT);
                }
            }
            return false;

        case CTRL_H:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_CTRL) {
                    // Clear Ctrl modifier temporarily, send Left arrow, then restore
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_LEFT);
                    set_mods(mods);
                } else {
                    // Otherwise send - (minus)
                    tap_code(KC_MINS);
                }
            }
            return false;

        case CTRL_J:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_CTRL) {
                    // Clear Ctrl modifier temporarily, send Down arrow, then restore
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_DOWN);
                    set_mods(mods);
                } else {
                    // Otherwise send _ (underscore)
                    tap_code16(KC_UNDS);
                }
            }
            return false;

        case CTRL_K:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_CTRL) {
                    // Clear Ctrl modifier temporarily, send Up arrow, then restore
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_UP);
                    set_mods(mods);
                } else {
                    // Otherwise send { (left curly brace)
                    tap_code16(KC_LCBR);
                }
            }
            return false;

        case CTRL_L:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_CTRL) {
                    // Clear Ctrl modifier temporarily, send Right arrow, then restore
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_RIGHT);
                    set_mods(mods);
                } else {
                    // Otherwise send } (right curly brace)
                    tap_code16(KC_RCBR);
                }
            }
            return false;

        // Terminal control keys - Fixed for macOS compatibility
        case TERM_NEW_TAB:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_T));
            }
            return false;

        case TERM_CLOSE_TAB:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_W));
            }
            return false;

        case TERM_CLOSE_WIN:
            if (record->event.pressed) {
                tap_code16(LCMD(LSFT(KC_W)));
            }
            return false;

        case TERM_NEXT_TAB:
            if (record->event.pressed) {
                tap_code16(LCMD(LSFT(KC_RBRC)));
            }
            return false;

        case TERM_PREV_TAB:
            if (record->event.pressed) {
                tap_code16(LCMD(LSFT(KC_LBRC)));
            }
            return false;

        case TERM_TAB_1:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_1));
            }
            return false;

        case TERM_TAB_2:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_2));
            }
            return false;

        case TERM_TAB_3:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_3));
            }
            return false;

        case TERM_TAB_4:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_4));
            }
            return false;

        case TERM_TAB_5:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_5));
            }
            return false;

        case TERM_SPLIT_H:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_D));
            }
            return false;

        case TERM_SPLIT_V:
            if (record->event.pressed) {
                tap_code16(LCMD(LSFT(KC_D)));
            }
            return false;

        // ============================================================================
        // NEOVIM SPLIT RESIZING (HJKL in terminal layer)
        // ============================================================================
        case TERM_WIN_LEFT:
            if (record->event.pressed) {
                // Neovim: Resize split left (make current split narrower)
                // Ctrl+w <
                tap_code16(LCTL(KC_W));
                tap_code16(LSFT(KC_COMM)); // < key
            }
            return false;

        case TERM_WIN_DOWN:
            if (record->event.pressed) {
                // Neovim: Resize split down (make current split shorter)
                // Ctrl+w -
                tap_code16(LCTL(KC_W));
                tap_code(KC_MINS);
            }
            return false;

        case TERM_WIN_UP:
            if (record->event.pressed) {
                // Neovim: Resize split up (make current split taller)
                // Ctrl+w +
                tap_code16(LCTL(KC_W));
                tap_code16(LSFT(KC_EQL)); // + key
            }
            return false;

        case TERM_WIN_RIGHT:
            if (record->event.pressed) {
                // Neovim: Resize split right (make current split wider)
                // Ctrl+w >
                tap_code16(LCTL(KC_W));
                tap_code16(LSFT(KC_DOT)); // > key
            }
            return false;

        case TERM_NEXT_WIN:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_RBRC));
            }
            return false;

        case TERM_PREV_WIN:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_LBRC));
            }
            return false;

        case TERM_ZOOM:
            if (record->event.pressed) {
                // Toggle maximize for current pane (iTerm2/Kitty)
                tap_code16(LCMD(LSFT(KC_ENT)));
            }
            return false;

        case TERM_FULLSCREEN:
            if (record->event.pressed) {
                // macOS standard fullscreen toggle
                tap_code16(LCTL(LCMD(KC_F)));
            }
            return false;

        case TERM_SCROLL_UP:
            if (record->event.pressed) {
                tap_code(KC_PGUP);
            }
            return false;

        case TERM_SCROLL_DN:
            if (record->event.pressed) {
                tap_code(KC_PGDN);
            }
            return false;

        case TERM_HOME:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_A));
            }
            return false;

        case TERM_END:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_E));
            }
            return false;

        case TERM_CLEAR_LINE:
            if (record->event.pressed) {
                // Clear from cursor to end of line
                tap_code16(LCTL(KC_K));
            }
            return false;

        case TERM_CLEAR_SCRN:
            if (record->event.pressed) {
                // Clear screen and scrollback
                tap_code16(LCMD(KC_K));
            }
            return false;

        case TERM_FONT_INC:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_PLUS));
            }
            return false;

        case TERM_FONT_DEC:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_MINS));
            }
            return false;

        case TERM_FONT_RST:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_0));
            }
            return false;

        default:
            return true;
    }
}
