#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum custom_keycodes {
    DE_AE = SAFE_RANGE, // Ä
    DE_OE,              // Ö
    DE_UE,              // Ü
    DE_SS,              // ß
    DE_EURO,
    DE_PARA
};

// Left-hand home row mods
#define HOME_GRV RALT_T(KC_GRV)
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LSFT_T(KC_S)
#define HOME_T LCTL_T(KC_T)
#define HOME_G HYPR_T(KC_G)

// Right-hand home row mods
#define HOME_M HYPR_T(KC_M)
#define HOME_N RCTL_T(KC_N)
#define HOME_E LSFT_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)
#define HOME_QUOT RALT_T(KC_QUOT)

// Right-hand home row mods layer 1
#define HOME_LEFT HYPR_T(KC_LEFT)
#define HOME_DOWN RCTL_T(KC_DOWN)
#define HOME_UP LSFT_T(KC_UP)
#define HOME_RIGHT LALT_T(KC_RIGHT)

// Left-hand home row mods layer 2
#define HOME_1 LGUI_T(KC_1)
#define HOME_2 LALT_T(KC_2)
#define HOME_3 LSFT_T(KC_3)
#define HOME_4 LCTL_T(KC_4)
#define HOME_5 HYPR_T(KC_5)

// Right-hand home row mods layer 2
#define HOME_MINS HYPR_T(KC_MINS)
#define HOME_EQL RCTL_T(KC_EQL)
#define HOME_LBRC LSFT_T(KC_LBRC)
#define HOME_RBRC LALT_T(KC_RBRC)
#define HOME_BSLS RGUI_T(KC_BSLS)

// Left-hand home row mods layer 2
// #define HOME_1 LGUI_T(KC_1)
#define HOME_MUTE LALT_T(KC_MUTE)
#define HOME_VOLD LSFT_T(KC_VOLD)
#define HOME_VOLU LCTL_T(KC_VOLU)

// Right-hand home row mods layer 2
#define HOME_MPRV RCTL_T(KC_MPRV)
#define HOME_MPLY LSFT_T(KC_MPLY)
#define HOME_MNXT LALT_T(KC_MNXT)
// #define HOME_BSLS RGUI_T(KC_BSLS)

// One-shot modifiers
#define OSM_RALT OSM(MOD_RALT)
#define OSM_LSFT OSM(MOD_LSFT)

// Space and enter
#define LT_ENT LT(1,KC_ENT)
#define LT_RALT LT(1, OSM_RALT)
#define LT_TAB LT(2,KC_TAB)

enum combo_events {
    AE_COMBO,
    OE_COMBO,
    UE_COMBO,
    SS_COMBO
};

const uint16_t PROGMEM combo_ae_seq[] = {HOME_R, HOME_S, COMBO_END}; // A+R = Ä
const uint16_t PROGMEM combo_oe_seq[] = {HOME_E, HOME_I, COMBO_END}; // I+O = Ö
const uint16_t PROGMEM combo_ue_seq[] = {KC_U,   KC_Y,   COMBO_END}; // L+U = Ü
const uint16_t PROGMEM combo_ss_seq[] = {HOME_S, HOME_T, COMBO_END}; // S+T = ß

combo_t key_combos[] = {
    [AE_COMBO] = COMBO(combo_ae_seq, DE_AE),
    [OE_COMBO] = COMBO(combo_oe_seq, DE_OE),
    [UE_COMBO] = COMBO(combo_ue_seq, DE_UE),
    [SS_COMBO] = COMBO(combo_ss_seq, DE_SS)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3_ex2(
        KC_LBRC, KC_Q,   KC_W,     KC_F,     KC_P,   KC_B,   KC_DEL,   KC_SLEP,  KC_J,    KC_L,     KC_U,    KC_Y,    KC_SCLN, KC_RBRC,
        KC_GRV,  HOME_A, HOME_R,   HOME_S,   HOME_T, KC_G,   KC_LSFT,  KC_RALT,  KC_M,    HOME_N,   HOME_E,  HOME_I,  HOME_O,  KC_QUOT,
        KC_LPRN, KC_Z,   KC_X,     KC_C,     KC_D,   KC_V,                       KC_K,    KC_H,     KC_COMM, KC_DOT,  KC_SLSH, KC_RPRN,
                                   KC_ESC,   KC_SPC, LT_TAB,                     LT_ENT,  OSM_LSFT, KC_BSPC
    ),
    [1] = LAYOUT_split_3x6_3_ex2(
        KC_NO, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,    KC_PGUP, KC_6,      KC_7,      KC_8,    KC_9,       KC_0,    KC_NO,
        KC_NO, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_NO,   KC_NO,    KC_PGDN, KC_LEFT,   HOME_DOWN, HOME_UP, HOME_RIGHT, KC_RGUI, KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_NO,     KC_NO,     KC_COMM, KC_DOT,     KC_NO,   KC_NO,
                                 KC_TRNS, KC_TRNS, MO(3),                      KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
    [2] = LAYOUT_split_3x6_3_ex2(
        DE_PARA, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_NO,    KC_NO, KC_CIRC,   KC_AMPR,  KC_ASTR,   KC_LPRN,   KC_RPRN,   DE_EURO,
        KC_NO,   KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_NO,   KC_NO,    KC_NO, KC_MINS,   HOME_EQL, HOME_LBRC, HOME_RBRC, HOME_BSLS, KC_GRV,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                    KC_UNDS,   KC_PLUS,  KC_LCBR,   KC_RCBR,   KC_PIPE,   KC_TILD,
                                   KC_TRNS, KC_TRNS, KC_TRNS,                  MO(3),     KC_TRNS,  KC_TRNS
    ),
    [3] = LAYOUT_split_3x6_3_ex2(
        KC_F1,   KC_F2,   KC_F3,     KC_F4,     KC_F5,     KC_F6, KC_NO,    QK_BOOT, KC_F7,   KC_F8,     KC_F9,     KC_F10,    KC_F11,  KC_F12,
        RGB_VAI, KC_LGUI, HOME_MUTE, HOME_VOLD, HOME_VOLU, KC_NO, KC_TRNS,  KC_TRNS, KC_NO,   HOME_MPRV, HOME_MPLY, HOME_MNXT, KC_RGUI, KC_NO,
        RGB_VAD, RGB_MOD, RGB_TOG,   KC_NO,     KC_NO,     KC_NO,                    KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,
                                     KC_NO,     KC_NO,     KC_TRNS,                  KC_TRNS, KC_NO,     KC_NO
    ),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x6_3_ex2(
        'L', 'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*',            '*', '*', '*'
    );

#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case AE_COMBO:
        case OE_COMBO:
        case UE_COMBO:
        case SS_COMBO:
            return 30;
    }

    return COMBO_TERM;
}
#endif

bool is_flow_tap_key(uint16_t keycode) {
    switch (keycode) {
        case LT_ENT:
        case LT_TAB:
            return false;
        default:
            return true;
    }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_TAB:
        case LT_ENT:
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSFT:
        case OSM(MOD_LSFT):
            return TAPPING_TERM_SHIFT;
        case LT_TAB:
        case LT_ENT:
            return TAPPING_TERM_THUMB;
        default:
            return TAPPING_TERM;
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 3:
                rgb_matrix_set_color(i, RGB_YELLOW);
                break;
            case 2:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case 1:
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            default:
                break;
        }
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(i, RGB_RED);
        }
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DE_AE:
        case DE_OE:
        case DE_UE:
            if (record->event.pressed) {
                // 1. GET SHIFT STATE (Held OR One-Shot)
                uint8_t mods = get_mods();
                uint8_t os_mods = get_oneshot_mods();

                // Combine them to see if we should capitalize
                bool is_shifted = (mods | os_mods) & MOD_MASK_SHIFT;

                // Caps is active if OS Caps Lock is on OR QMK Caps Word is on
                bool is_caps = host_keyboard_led_state().caps_lock || is_caps_word_on();

                // XOR Logic: Capitalize if Shift OR Caps is on, but not both (Inversion)
                bool send_upper = is_shifted ^ is_caps;

                // 2. CLEAR SHIFT INTERFERENCE
                // If physical shift is held, we must release it for the Opt+u shortcut
                if (mods & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RSFT);
                }

                // If One-Shot Shift is pending, we must "consume" it manually
                if (os_mods & MOD_MASK_SHIFT) {
                    del_oneshot_mods(MOD_MASK_SHIFT);
                }

                // 3. SEND DEAD KEY (Option + u)
                register_code(KC_RALT);
                tap_code(KC_U);
                unregister_code(KC_RALT);

                // 4. DETERMINE LETTER
                uint16_t target_keycode;
                switch(keycode) {
                    case DE_AE: target_keycode = KC_A; break;
                    case DE_OE: target_keycode = KC_O; break;
                    case DE_UE: target_keycode = KC_U; break;
                }

                // 5. SEND LETTER
                if (send_upper) {
                    register_code(KC_LSFT);
                    tap_code(target_keycode);
                    unregister_code(KC_LSFT);
                } else {
                    tap_code(target_keycode);
                }

                // 6. RESTORE HELD SHIFT
                // Only restore if it was physically held. Do NOT restore One-Shot shift.
                if (mods & MOD_MASK_SHIFT) {
                    set_mods(mods);
                }
            }
            return false;

        case DE_SS:
            if (record->event.pressed) {
                // 1. GET SHIFT STATE (Held OR One-Shot)
                uint8_t mods = get_mods();
                uint8_t os_mods = get_oneshot_mods();

                // Combine them to see if we should capitalize
                bool is_shifted = (mods | os_mods) & MOD_MASK_SHIFT;

                // Caps is active if OS Caps Lock is on OR QMK Caps Word is on
                bool is_caps = host_keyboard_led_state().caps_lock || is_caps_word_on();

                // XOR Logic: Capitalize if Shift OR Caps is on, but not both (Inversion)
                bool send_upper = is_shifted ^ is_caps;

                // 2. CLEANUP ONE-SHOT SHIFT
                // We must always consume this so it doesn't affect the NEXT key
                if (os_mods & MOD_MASK_SHIFT) {
                    del_oneshot_mods(MOD_MASK_SHIFT);
                }

                if (send_upper) {
                    // --- SEND "S" ---
                    // If Caps is OFF, we need to manually hold Shift to get "S"
                    if (!is_caps) {
                        register_code(KC_LSFT);
                    }
                    // If Caps is ON, and we are holding Shift (Inversion),
                    // we must Release Shift to get "S" (because Shift+Caps = lowercase)
                    else if (mods & MOD_MASK_SHIFT) {
                        unregister_code(KC_LSFT);
                        unregister_code(KC_RSFT);
                    }

                    tap_code(KC_S);

                    // Restore state
                    if (!is_caps) {
                        unregister_code(KC_LSFT);
                    } else if (mods & MOD_MASK_SHIFT) {
                        set_mods(mods); // Restore held shift
                    }

                } else {
                    // --- SEND "ß" (Option + s) ---
                    // We must remove Shift, otherwise Opt+Shift+s might trigger other symbols
                    if (mods & MOD_MASK_SHIFT) {
                        unregister_code(KC_LSFT);
                        unregister_code(KC_RSFT);
                    }

                    register_code(KC_RALT);
                    tap_code(KC_S);
                    unregister_code(KC_RALT);

                    // Restore held shift
                    if (mods & MOD_MASK_SHIFT) {
                        set_mods(mods);
                    }
                }
            }
            return false;
        case DE_EURO:
            if (record->event.pressed) {
                // 1. Save current Shift state
                uint8_t mods = get_mods();

                // 2. Clear held Shift
                // We do this to ensure we control exactly when Shift is pressed
                // for the shortcut logic below.
                if (mods & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RSFT);
                }

                // 3. Send the Shortcut: Option (RALT) + Shift + 2
                register_code(KC_RALT); // Option
                register_code(KC_LSFT); // Shift
                tap_code(KC_2);         // 2
                unregister_code(KC_LSFT);
                unregister_code(KC_RALT);

                // 4. Restore Shift if it was originally held
                if (mods & MOD_MASK_SHIFT) {
                    set_mods(mods);
                }
            }
            return false;
        case DE_PARA:
            if (record->event.pressed) {
                // 1. Save current Shift state
                uint8_t mods = get_mods();

                // 2. Clear held Shift
                // We must force Shift OFF, because Option+Shift+6 often produces '‚' (low single quote)
                if (mods & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RSFT);
                }

                // 3. Send the Shortcut: Option (RALT) + 6
                register_code(KC_RALT);
                tap_code(KC_6);
                unregister_code(KC_RALT);

                // 4. Restore Shift if it was originally held
                if (mods & MOD_MASK_SHIFT) {
                    set_mods(mods);
                }
            }
            return false;
    }
    return true;
}
