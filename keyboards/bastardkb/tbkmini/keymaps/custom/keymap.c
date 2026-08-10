// qmk compile -kb bastardkb/tbkmini/promicro -km custom -e CONVERT_TO=rp2040_ce
//
// DUAL-OS VERSION of the crkbd "custom" keymap - same five layers, same key
// positions, switchable at runtime between Windows and macOS.
//
// OS switch: hold ENTER + SPACE (either order) to reach the TERMINAL layer,
//            then tap the top-right corner key to flip Windows <-> macOS.
// The choice is stored in EEPROM and survives unplugging.
//
// DESIGN
// ------
// The keymap below is written in *macOS* terms, exactly as the crkbd keymap is.
// Windows mode is produced by rewriting one modifier:
//
//     Cmd (LGUI)  ->  Ctrl (LCTL)
//
// That is the only structural difference between the two modes. The left thumb
// is Ctrl in both, so <C-w> and every other Ctrl chord is the same physical
// gesture on both systems.
//
// Where a plain Cmd->Ctrl swap would produce the wrong shortcut, a custom
// keycode translates per-OS instead - see WT_MOD/WT_MOD2 (WezTerm), CTRL_SPC
// (Spotlight vs Search), the SNAP_* screenshot keys, and APP_SW.

#include QMK_KEYBOARD_H

// Layer definitions
enum layer_names { _BASE = 0, _LOWER, _RAISE, _FUNCTION, _TERMINAL };

// ============================================================================
// Encoder Configuration (if present)
// ============================================================================
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]     = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LOWER]    = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [_RAISE]    = {ENCODER_CCW_CW(KC_BRID, KC_BRIU)},
    [_FUNCTION] = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
    [_TERMINAL] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif

// ============================================================================
// OS Mode - persisted in EEPROM
// ============================================================================
typedef union {
    uint32_t raw;
    struct {
        bool mac_mode : 1;
    };
} user_config_t;

static user_config_t user_config;

#define IS_MAC (user_config.mac_mode)

// The left thumb TAB hold is LCTL_T(KC_TAB) and mod_config() never rewrites
// LCTL, so it is a real Ctrl in both OS modes. That is what the RAISE-layer
// HJKL arrows and CTRL_SPC test for.
//
// Note: in Windows mode the right thumb ESC hold is also Ctrl, so it can
// trigger these too. Harmless in practice.
#define NAV_MOD_MASK MOD_MASK_CTRL

// Send one of two keycodes depending on the active OS mode.
static void tap_os(uint16_t win_code, uint16_t mac_code) {
    tap_code16(IS_MAC ? mac_code : win_code);
}

// ============================================================================
// WezTerm modifier groups
//
// Mirrors dotfiles/wezterm/.config/wezterm/wezterm.lua:15-17, which branches on
// is_mac:
//     mod  = SUPER        (mac) | CTRL|SHIFT (win)
//     mod2 = SUPER|SHIFT  (mac) | CTRL|ALT   (win)
//
// On macOS these are byte-identical to the crkbd keymap's LCMD(...) bindings,
// so the Mac behaviour is unchanged; Windows gets the combo WezTerm expects
// there. Keep in sync if the wezterm config changes.
// ============================================================================
#define WT_MOD(kc) tap_os(LCTL(LSFT(kc)), LCMD(kc))
#define WT_MOD2(kc) tap_os(LCTL(LALT(kc)), LCMD(LSFT(kc)))

// ============================================================================
// Runtime modifier remapping
//
// QMK calls mod_config() on every mod-tap, LCMD(kc)-style keycode and
// layer-mod that comes out of the keymap (quantum/keymap_common.c), and it is
// a weak symbol - so overriding it remaps the whole keymap for Windows without
// needing a second set of layers.
//
// The keymap is authored for macOS, so Mac mode is the identity. Windows mode
// turns Cmd into Ctrl and leaves everything else alone.
//
// IMPORTANT: mod_config() is NOT called for plain modifier keycodes (KC_LCMD,
// KC_LCTL, ...) - keymap_common.c routes MODIFIER_KEYCODE_RANGE straight to
// ACTION_KEY. The bare Cmd thumbs therefore use the TH_RMOD custom keycode
// below, which picks the mod at press time.
//
// It is also NOT called by tap_code16() (register_code16 uses
// extract_mod_bits), which is why the literal Ctrl+w in the TERM_WIN_* keys
// stays Ctrl+w in Mac mode instead of becoming Cmd+w.
// ============================================================================
uint8_t mod_config(uint8_t mod) {
    if (IS_MAC) {
        return mod;
    }
    // Bit 4 of the packed 5-bit mods marks right-hand mods; leave those alone.
    if (mod & 0x10) {
        return mod;
    }
    if (mod & MOD_LGUI) {
        mod = (mod & ~MOD_LGUI) | MOD_LCTL;
    }
    return mod;
}

// Custom keycodes
enum custom_keycodes {
    CTRL_H = SAFE_RANGE,
    CTRL_J,
    CTRL_K,
    CTRL_L,
    CTRL_SPC,  // ; normally, Spotlight / Windows Search when Ctrl is held
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

    OSMODE_TOG, // toggle Windows <-> macOS
    UE_LIVE,    // Unreal Live Coding recompile
    APP_SW,     // app switcher: Alt+Tab on Windows, Cmd+Tab on macOS

    // Screenshots. Cmd+Shift+N on macOS has no Ctrl+Shift+N equivalent on
    // Windows, so these translate per-OS rather than going through mod_config.
    SNAP_FULL, // whole screen
    SNAP_AREA, // selected region
    SNAP_REC,  // screenshot/record UI

    // Terminal control. WT_MOD/WT_MOD2 keep the macOS behaviour identical to
    // the crkbd keymap while emitting the right combo on Windows.
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
    TERM_WIN_LEFT, // Neovim split resizing
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

    // Bare Cmd thumb on LOWER/RAISE/FUNCTION. Plain KC_* mod keycodes bypass
    // mod_config(), so this resolves the mod itself and follows the OS toggle.
    TH_RMOD, // right thumb: Cmd on macOS, Ctrl on Windows
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // ============================================================================
    // BASE LAYER - QWERTY
    // Left thumb: TAB(Ctrl hold) → SHIFT → ENTER(LOWER)
    // Right thumb: SPACE(RAISE) ← BACKSPACE ← ESC(Cmd/Ctrl hold)
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
    // Cut/copy/paste follow the OS: Cmd+ZXCV on macOS, Ctrl+ZXCV on Windows
    // B position = Unreal Live Coding recompile
    // ============================================================================
    [_LOWER] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, KC_1, KC_2, KC_3, KC_4, KC_5, MS_BTN1, MS_WHLU, MS_BTN2, KC_DEL, KC_INS, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_6, KC_7, KC_8, KC_9, KC_0, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, KC_PGUP, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, LCMD(KC_Z), LCMD(KC_X), LCMD(KC_C), LCMD(KC_V), UE_LIVE, MS_BTN3, MS_WHLD, KC_HOME, KC_END, KC_PGDN, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_LSFT, _______, _______, KC_BSPC, TH_RMOD
        //`--------------------------'  `--------------------------'
        ),

    // ============================================================================
    // RAISE LAYER - Programming Symbols (Numbers available in LOWER layer)
    // Top row: !@#$%^&*() - symbols only
    // HJKL: Normal symbols, or arrow keys when the left thumb Ctrl is held
    // CTRL+SEMICOLON: Spotlight (macOS) / Windows Search when Ctrl is held
    // ============================================================================
    [_RAISE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, SYM_1, W_AT, SYM_3, SYM_4, SYM_5, SYM_6, SYM_7, SYM_8, SYM_9, SYM_0, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_EQL, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, CTRL_H, CTRL_J, CTRL_K, CTRL_L, CTRL_SPC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_GRV, KC_BSLS, KC_PIPE, KC_TILD, QUOT_APOS, KC_PLUS, KC_QUOT, KC_COMM, KC_DOT, LALT_T(KC_SLSH), XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        LCTL_T(KC_TAB), KC_LSFT, MO(_TERMINAL), _______, KC_BSPC, TH_RMOD
        //`--------------------------'  `--------------------------'
        ),

    // ============================================================================
    // FUNCTION LAYER - F-keys & System Controls (reached via TG on TERMINAL)
    // Screenshots follow the OS: Cmd+Shift+3/4/5 on macOS, PrtSc / Win+Shift+S
    // / Game Bar on Windows.
    // ============================================================================
    [_FUNCTION] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_F11, KC_F12, KC_BRID, KC_BRIU, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SNAP_FULL, SNAP_AREA, SNAP_REC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, XXXXXXX, XXXXXXX, KC_SPC, KC_BSPC, TH_RMOD
        //`--------------------------'  `--------------------------'
        ),

    // ============================================================================
    // TERMINAL LAYER - Direct Terminal Control (hold LOWER + RAISE)
    // Left hand: Window/Tab/Split management | Right hand: Navigation + Neovim
    // Home row HJKL = Neovim split resizing
    // Top-right corner = toggle Windows <-> macOS
    // B position = app switcher
    // ============================================================================
    [_TERMINAL] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, TERM_TAB_1, TERM_TAB_2, TERM_TAB_3, TERM_TAB_4, TERM_TAB_5, TERM_SCROLL_UP, TERM_FONT_INC, TERM_FONT_DEC, TERM_FONT_RST, TERM_CLEAR_SCRN, OSMODE_TOG,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, TERM_NEW_TAB, TERM_SPLIT_H, TERM_SPLIT_V, TERM_NEXT_TAB, TERM_PREV_TAB, TERM_WIN_LEFT, TERM_WIN_DOWN, TERM_WIN_UP, TERM_WIN_RIGHT, TERM_SCROLL_DN, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, TERM_ZOOM, TERM_CLOSE_WIN, TERM_CLOSE_TAB, TERM_FULLSCREEN, APP_SW, TERM_HOME, TERM_PREV_WIN, TERM_NEXT_WIN, TERM_END, TERM_CLEAR_LINE, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        TG(_FUNCTION), _______, _______, _______, _______, KC_RSFT
        //`--------------------------'  `--------------------------'
        )};

// ============================================================================
// Layer State Management
//
// Tri-layer: holding LOWER and RAISE together activates TERMINAL. This is
// driven by the layer bitmask, not by press order, so ENTER-then-SPACE and
// SPACE-then-ENTER both work.
// ============================================================================
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _TERMINAL);
}

// ============================================================================
// Tap-hold resolution for the thumb layer keys
//
// PERMISSIVE_HOLD alone only resolves a tap-hold early when the interrupting
// key is *released* first. Holding the opposite thumb down therefore left the
// first key undecided for the full TAPPING_TERM, so ENTER + SPACE only reached
// TERMINAL reliably in one order. Resolving these two to hold the moment any
// other key goes down makes every order - and both pressed together - work
// immediately.
//
// Scoped to the thumbs on purpose: applying this globally would make fast
// typing rolls fire layers instead of letters.
// ============================================================================
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_LOWER, KC_ENT):
        case LT(_RAISE, KC_SPC):
            return true;
        default:
            return false;
    }
}

// ============================================================================
// EEPROM - load / initialise the OS mode
// ============================================================================
void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) {
    user_config.raw      = 0;
    user_config.mac_mode = false; // default to Windows
    eeconfig_update_user(user_config.raw);
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
        // ============================================================================
        // OS mode switching
        // ============================================================================
        case OSMODE_TOG:
            if (record->event.pressed) {
                // Drop any held mods first, so nothing stays stuck across the remap.
                clear_mods();
                clear_weak_mods();
                user_config.mac_mode = !user_config.mac_mode;
                eeconfig_update_user(user_config.raw);
            }
            return false;

        // ============================================================================
        // Bare Cmd thumb (LOWER/RAISE/FUNCTION), OS-aware.
        // macOS: Cmd. Windows: Ctrl - the one modifier that differs between modes.
        // ============================================================================
        case TH_RMOD: {
            uint8_t mod = IS_MAC ? MOD_LGUI : MOD_LCTL;
            if (record->event.pressed) {
                register_mods(mod);
            } else {
                unregister_mods(mod);
            }
            return false;
        }

        // ============================================================================
        // App switcher. The left thumb is Ctrl in both modes, so there is no Alt
        // there to make Alt+Tab out of - it lives here instead.
        // ============================================================================
        case APP_SW:
            if (record->event.pressed) {
                tap_os(LALT(KC_TAB), LCMD(KC_TAB));
            }
            return false;

        // ============================================================================
        // Screenshots
        // ============================================================================
        case SNAP_FULL:
            if (record->event.pressed) {
                tap_os(KC_PSCR, LCMD(LSFT(KC_3)));
            }
            return false;

        case SNAP_AREA:
            if (record->event.pressed) {
                tap_os(LGUI(LSFT(KC_S)), LCMD(LSFT(KC_4)));
            }
            return false;

        case SNAP_REC:
            if (record->event.pressed) {
                tap_os(LGUI(KC_G), LCMD(LSFT(KC_5)));
            }
            return false;

        // ============================================================================
        // OS-dependent application shortcuts
        // ============================================================================
        case UE_LIVE:
            if (record->event.pressed) {
                // Unreal Live Coding recompile
                tap_os(LCTL(LALT(KC_F11)), LCMD(LALT(KC_F11)));
            }
            return false;

        // ============================================================================
        // Symbol keys - symbols only (numbers available in LOWER layer)
        // ============================================================================
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
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_QUOT);
                    set_mods(mods);
                } else {
                    tap_code16(KC_DQT);
                }
            }
            return false;

        // ============================================================================
        // HJKL arrow keys when the left thumb TAB hold (Ctrl) is held
        // Normal taps produce symbols: - _ { }
        // ============================================================================
        case CTRL_H:
            if (record->event.pressed) {
                if (get_mods() & NAV_MOD_MASK) {
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_LEFT);
                    set_mods(mods);
                } else {
                    tap_code(KC_MINS); // -
                }
            }
            return false;

        case CTRL_J:
            if (record->event.pressed) {
                if (get_mods() & NAV_MOD_MASK) {
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_DOWN);
                    set_mods(mods);
                } else {
                    tap_code16(KC_UNDS); // _
                }
            }
            return false;

        case CTRL_K:
            if (record->event.pressed) {
                if (get_mods() & NAV_MOD_MASK) {
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_UP);
                    set_mods(mods);
                } else {
                    tap_code16(KC_LCBR); // {
                }
            }
            return false;

        case CTRL_L:
            if (record->event.pressed) {
                if (get_mods() & NAV_MOD_MASK) {
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_RIGHT);
                    set_mods(mods);
                } else {
                    tap_code16(KC_RCBR); // }
                }
            }
            return false;

        case CTRL_SPC:
            if (record->event.pressed) {
                if (get_mods() & NAV_MOD_MASK) {
                    // Clear the held mod, then launch search: Spotlight on macOS,
                    // Windows Search on Windows.
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_os(LGUI(KC_S), LCMD(KC_SPC));
                    set_mods(mods);
                } else {
                    tap_code(KC_SCLN);
                }
            }
            return false;

        // ============================================================================
        // TERMINAL LAYER - tabs
        // ============================================================================
        case TERM_NEW_TAB: // mod+t
            if (record->event.pressed) WT_MOD(KC_T);
            return false;

        case TERM_CLOSE_TAB: // mod+w
            if (record->event.pressed) WT_MOD(KC_W);
            return false;

        case TERM_CLOSE_WIN: // mod2+w - closes the current pane
            if (record->event.pressed) WT_MOD2(KC_W);
            return false;

        case TERM_NEXT_TAB: // mod2+]
            if (record->event.pressed) WT_MOD2(KC_RBRC);
            return false;

        case TERM_PREV_TAB: // mod2+[
            if (record->event.pressed) WT_MOD2(KC_LBRC);
            return false;

        case TERM_TAB_1:
            if (record->event.pressed) WT_MOD(KC_1);
            return false;

        case TERM_TAB_2:
            if (record->event.pressed) WT_MOD(KC_2);
            return false;

        case TERM_TAB_3:
            if (record->event.pressed) WT_MOD(KC_3);
            return false;

        case TERM_TAB_4:
            if (record->event.pressed) WT_MOD(KC_4);
            return false;

        case TERM_TAB_5:
            if (record->event.pressed) WT_MOD(KC_5);
            return false;

        // ============================================================================
        // TERMINAL LAYER - splits and panes
        // wezterm's SplitVertical puts the new pane BELOW, SplitHorizontal to the
        // RIGHT. Names kept from the crkbd keymap.
        // ============================================================================
        case TERM_SPLIT_H: // mod+d
            if (record->event.pressed) WT_MOD(KC_D);
            return false;

        case TERM_SPLIT_V: // mod2+d
            if (record->event.pressed) WT_MOD2(KC_D);
            return false;

        case TERM_NEXT_WIN: // mod+]
            if (record->event.pressed) WT_MOD(KC_RBRC);
            return false;

        case TERM_PREV_WIN: // mod+[
            if (record->event.pressed) WT_MOD(KC_LBRC);
            return false;

        case TERM_ZOOM: // mod2+Enter
            if (record->event.pressed) WT_MOD2(KC_ENT);
            return false;

        // Fullscreen is the one wezterm binding that does not follow mod/mod2:
        // SUPER|CTRL on macOS, CTRL|SHIFT on Windows.
        case TERM_FULLSCREEN:
            if (record->event.pressed) {
                tap_os(LCTL(LSFT(KC_F)), LCTL(LCMD(KC_F)));
            }
            return false;

        // ============================================================================
        // NEOVIM SPLIT RESIZING (HJKL on the TERMINAL layer)
        // Ctrl+w is Ctrl+w on both Windows and macOS, so these need no tap_os().
        // tap_code16() bypasses mod_config(), so LCTL stays LCTL in Mac mode.
        // ============================================================================
        case TERM_WIN_LEFT:
            if (record->event.pressed) {
                // Ctrl+w < - narrower
                tap_code16(LCTL(KC_W));
                tap_code16(LSFT(KC_COMM));
            }
            return false;

        case TERM_WIN_DOWN:
            if (record->event.pressed) {
                // Ctrl+w - - shorter
                tap_code16(LCTL(KC_W));
                tap_code(KC_MINS);
            }
            return false;

        case TERM_WIN_UP:
            if (record->event.pressed) {
                // Ctrl+w + - taller
                tap_code16(LCTL(KC_W));
                tap_code16(LSFT(KC_EQL));
            }
            return false;

        case TERM_WIN_RIGHT:
            if (record->event.pressed) {
                // Ctrl+w > - wider
                tap_code16(LCTL(KC_W));
                tap_code16(LSFT(KC_DOT));
            }
            return false;

        // ============================================================================
        // TERMINAL LAYER - scrollback, line editing, font
        // The Ctrl+A / Ctrl+E / Ctrl+K here are readline bindings - literal Ctrl
        // on both systems, so they use tap_code16 rather than WT_MOD.
        // ============================================================================
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
                tap_code16(LCTL(KC_K));
            }
            return false;

        case TERM_CLEAR_SCRN: // mod+k
            if (record->event.pressed) WT_MOD(KC_K);
            return false;

        // '=' rather than '+' - both are bound in wezterm, and '=' avoids a
        // shifted-key clash with mod's own CTRL|SHIFT on Windows.
        case TERM_FONT_INC:
            if (record->event.pressed) WT_MOD(KC_EQL);
            return false;

        case TERM_FONT_DEC:
            if (record->event.pressed) WT_MOD(KC_MINS);
            return false;

        case TERM_FONT_RST:
            if (record->event.pressed) WT_MOD(KC_0);
            return false;

        default:
            return true;
    }
}
