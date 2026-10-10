
// Hardware note — why the converter exists:
//   The stock ferris/sweep board targets an AVR Pro Micro (ATmega32u4) and so
//   builds a .hex flashed over the caterina serial bootloader. Our physical
//   board is a generic RP2040 Pro Micro (USB-C) instead, which is flashed by
//   copying a .uf2 onto the RPI-RP2 mass-storage drive. The AVR -> RP2040 switch
//   is handled entirely by the "converter" entry in this keymap's keymap.json:
//   "rp2040_ce" — the "Community Edition" pinout that the generic RP2040 Pro
//   Micro clones follow. (NOT "promicro_rp2040": that name is deprecated and
//   targets the specific SparkFun board; for the Sweep the two are electrically
//   identical anyway, as the only pins that differ are RGB/VBUS pins this board
//   doesn't use.) The converter transparently remaps the Pro Micro pin names in
//   the board's keyboard.json (the direct matrix pins and the D2 split-serial
//   pin) onto the equivalent RP2040 GPIOs. No pin definitions need to change.

#include QMK_KEYBOARD_H

// Layer indices. Only one layer for now, but named (rather than a bare 0) so
// that future layers can be added without renumbering everything.
enum layers {
    _COLEMAK,
    _LAYER_PICKER,
    _NUMBERS,
    _FN_KEYS,
    _SECONDARY
};

// ──────────────────────────────────────────────────────────────
// Tap Dance
// ──────────────────────────────────────────────────────────────
// Indices into tap_dance_actions[]. Referenced from the keymap as TD(...).
enum tap_dances {
    TD_SCREENSHOT,
};

// ── Screenshot tap dance (Mac-only) ──
// This is a simplified port of the OS-aware screenshot tap dance from the
// Sofle (users/ninjaPixel/ninjaPixel_keymap.h). The Ferris Sweep is only
// ever used with a Mac, so the OS-detection branch and the Windows
// shortcuts have been dropped entirely:
//
//   1 tap  → Cmd+Shift+4  (selection screenshot — drag a region)
//   2 taps → Cmd+Shift+3  (full screen screenshot)
//   3 taps → Cmd+Shift+5  (screenshot/record toolbar)
//
// The key lives on _FN_KEYS, which is reached via TO(_FN_KEYS) — a
// persistent layer toggle. (It deliberately does NOT live on the one-shot
// _LAYER_PICKER layer: QMK clears a one-shot layer on the first keypress,
// which breaks multi-tap dances.)

// Called once when QMK resolves the dance (tapping term expired, or another
// key interrupted it). Sends the Mac screenshot shortcut for the tap count.
void td_screenshot_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            // Mac selection screenshot — crosshair to drag a region.
            tap_code16(LGUI(LSFT(KC_4)));
            break;
        case 2:
            // Mac full screen screenshot — captures the entire display.
            tap_code16(LGUI(LSFT(KC_3)));
            break;
        case 3:
            // Mac screenshot toolbar — the floating screenshot/record UI.
            tap_code16(LGUI(LSFT(KC_5)));
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    // Screenshot: fires on dance completion only, so the simple FN variant
    // (on_dance_finished callback, nothing on each tap / reset) is enough.
    [TD_SCREENSHOT] = ACTION_TAP_DANCE_FN(td_screenshot_finished),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base layer — standard Colemak (not Colemak-DH), MacOS-oriented.
    // note: the style `key1_T(key2)` is a mod tap. Tap for key2 and hold for key1
    [_COLEMAK] = LAYOUT(
        KC_Q,         KC_W,        KC_F,         KC_P,                  KC_B,                    KC_J,               KC_L,                   KC_U,         KC_Y,        KC_BSLS,
        HYPR_T(KC_A), MEH_T(KC_R), LCTL_T(KC_S), LGUI_T(KC_T),          LALT_T(KC_G),            RALT_T(KC_M),       RGUI_T(KC_N),           RCTL_T(KC_E), MEH_T(KC_I), HYPR_T(KC_O),
        KC_Z,         KC_X,        KC_C,         KC_D,                  KC_V,                    KC_K,               KC_H,                   KC_COMM,      KC_DOT,      MT(MOD_RSFT, KC_SLSH),
                                                 MT(MOD_RSFT, KC_BSPC), LT(_NUMBERS, KC_ENT),   OSL(_LAYER_PICKER), LT(_SECONDARY, KC_SPC)
    ),



    // Layer picker layer and sticky modifiers
    [_LAYER_PICKER] = LAYOUT(
        KC_L,    _______, _______, _______,       QK_BOOT,             _______,      _______,        _______,      _______, _______,
        CW_TOGG, _______, _______, _______,       _______,             _______,      TO(_NUMBERS),   TO(_FN_KEYS), _______, _______,
        _______, _______, KC_LCTL, KC_LGUI,       KC_LALT,             _______,      _______,        _______,      _______, _______,
                                   _______,       _______,             TO(_COLEMAK), _______
    ),


    [_NUMBERS] = LAYOUT(
        KC_N,    _______, _______, _______, XXXXXXX,            _______,      KC_7,     KC_8, KC_9, _______,
        _______, _______, _______, _______, _______,            _______,      KC_4,     KC_5, KC_6, _______,
        _______, _______, KC_PLUS, KC_EQL,  KC_DOT,             KC_0,         KC_1,     KC_2, KC_3, _______,
                                   _______, _______,            TO(_COLEMAK), LT(_SECONDARY, KC_SPC)
    ),

    // F-keys layer. The 'z' position holds the Mac screenshot tap dance
    // (1 tap = selection, 2 taps = full screen, 3 taps = screenshot toolbar).
    [_FN_KEYS] = LAYOUT(
        KC_F,              _______, _______, _______, XXXXXXX,            _______,      KC_F7,     KC_F8, KC_F9, KC_F12,
        _______,           _______, _______, _______, _______,            _______,      KC_F4,     KC_F5, KC_F6, KC_F11,
        TD(TD_SCREENSHOT), _______, _______, _______, _______,            _______,      KC_F1,     KC_F2, KC_F3, KC_F10,
                                             _______, _______,            TO(_COLEMAK), _______
    ),

    // Quick access layer
    [_SECONDARY] = LAYOUT(
        KC_ESC,         KC_LBRC,      KC_LPRN,      KC_LCBR,       KC_GRV,              _______,       KC_RCBR,       KC_RPRN, KC_RBRC, LALT(KC_BSPC),
        LALT(KC_DEL),   KC_DEL,       KC_QUOTE,     KC_SEMICOLON,  KC_LALT,             KC_MINUS,      KC_LEFT,       KC_DOWN, KC_UP,   KC_RIGHT,
        KC_TAB,         LSG(KC_LBRC), LSG(KC_RBRC), OSL(_NUMBERS), _______,             KC_RGUI,       LGUI(KC_LEFT), KC_PGDN, KC_PGUP, LGUI(KC_RIGHT),
                                                    _______,       LALT(KC_TAB),        TO(_COLEMAK),  _______
    )
    // Template
    // [_FOO] = LAYOUT(
    //     KC_T,    _______, _______, _______, XXXXXXX,      _______,      _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______,      _______,      _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______,      _______,      _______, _______, _______, _______,
    //                                _______, _______,      TO(_COLEMAK), _______
    // )
};
// clang-format on
