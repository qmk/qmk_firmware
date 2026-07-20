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
#define HM_A LGUI_T(KC_A)
#define HM_R LALT_T(KC_R)
#define HM_S LSFT_T(KC_S)
#define HM_T LCTL_T(KC_T)

// Right-hand home row mods
#define HM_N RCTL_T(KC_N)
#define HM_E LSFT_T(KC_E)
#define HM_I LALT_T(KC_I)
#define HM_O RGUI_T(KC_O)

// Left-hand home row mods layer 1
#define HM_0 LGUI_T(KC_0)
#define HM_4 LALT_T(KC_4)
#define HM_5 LSFT_T(KC_5)
#define HM_6 LCTL_T(KC_6)

// Right-hand home row mods layer 1
#define HM_DOWN RCTL_T(KC_DOWN)
#define HM_UP LSFT_T(KC_UP)
#define HM_RIGHT LALT_T(KC_RIGHT)

// Right-hand home row mods layer 2
#define HM_MINS RCTL_T(KC_MINS)
#define HM_EQL LSFT_T(KC_EQL)
#define HM_BSLS LALT_T(KC_BSLS)

// Left-hand home row mods layer 3
#define HM_MUTE LALT_T(KC_MUTE)
#define HM_VOLD LSFT_T(KC_VOLD)
#define HM_VOLU LCTL_T(KC_VOLU)

// Right-hand home row mods layer 3
#define HM_MPRV RCTL_T(KC_MPRV)
#define HM_MPLY LSFT_T(KC_MPLY)
#define HM_MNXT LALT_T(KC_MNXT)

// One-shot modifiers
#define OSM_RALT OSM(MOD_RALT)
#define OSM_LSFT OSM(MOD_LSFT)

// Space and enter
#define LT_ENT LT(1,KC_ENT)
#define LT_TAB LT(2,KC_TAB)

// Extras
#define TM_MUTE LGUI(LSFT(KC_M))

enum combo_events {
    AE_COMBO,
    OE_COMBO,
    UE_COMBO,
    SS_COMBO
};

const uint16_t PROGMEM combo_ae_seq[] = {HM_R, HM_S, COMBO_END}; // A+R = Ä
const uint16_t PROGMEM combo_oe_seq[] = {HM_E, HM_I, COMBO_END}; // I+O = Ö
const uint16_t PROGMEM combo_ue_seq[] = {KC_U,   KC_Y,   COMBO_END}; // L+U = Ü
const uint16_t PROGMEM combo_ss_seq[] = {HM_S, HM_T, COMBO_END}; // S+T = ß

combo_t key_combos[] = {
    [AE_COMBO] = COMBO(combo_ae_seq, DE_AE),
    [OE_COMBO] = COMBO(combo_oe_seq, DE_OE),
    [UE_COMBO] = COMBO(combo_ue_seq, DE_UE),
    [SS_COMBO] = COMBO(combo_ss_seq, DE_SS)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3_ex2(
        KC_LBRC, KC_Q, KC_W, KC_F,   KC_P,   KC_B,   KC_DEL,   KC_SLEP,  KC_J,   KC_L,     KC_U,    KC_Y,   KC_SCLN, KC_RBRC,
        KC_GRV,  HM_A, HM_R, HM_S,   HM_T,   KC_G,   TG(1),    KC_RALT,  KC_M,   HM_N,     HM_E,    HM_I,   HM_O,    KC_QUOT,
        KC_LPRN, KC_Z, KC_X, KC_C,   KC_D,   KC_V,                       KC_K,   KC_H,     KC_COMM, KC_DOT, KC_SLSH, KC_RPRN,
                             KC_ESC, KC_SPC, LT_TAB,                     LT_ENT, OSM_LSFT, KC_BSPC
    ),
    [1] = LAYOUT_split_3x6_3_ex2(
        KC_NO, KC_SLSH, KC_1, KC_2,    KC_3,    KC_ASTR, KC_TRNS, KC_PGUP, KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,
        KC_NO, HM_0,    HM_4, HM_5,    HM_6,    KC_PLUS, KC_TRNS, KC_PGDN, KC_LEFT, HM_DOWN, HM_UP,   HM_RIGHT, KC_RGUI, KC_NO,
        KC_NO, KC_NO,   KC_7, KC_8,    KC_9,    KC_MINS,                   KC_NO,   KC_NO,   KC_COMM, KC_DOT,   KC_NO,   KC_NO,
                              KC_TRNS, KC_TRNS, MO(3),                     KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT_split_3x6_3_ex2(
        KC_NO, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_NO, KC_NO, KC_CIRC, KC_AMPR, KC_ASTR, DE_EURO, DE_PARA, KC_NO,
        KC_NO, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_NO,   KC_NO, KC_NO, KC_NO,   HM_MINS, HM_EQL,  HM_BSLS, KC_RGUI, KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                 KC_NO,   KC_UNDS, KC_PLUS, KC_PIPE, KC_NO,   KC_NO,
                                 KC_TRNS, KC_TRNS, KC_TRNS,               MO(3),   KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_split_3x6_3_ex2(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_NO, QK_BOOT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_NO,   KC_LGUI, HM_MUTE, HM_VOLD, HM_VOLU, KC_NO, KC_NO, KC_NO,   KC_NO,   HM_MPRV, HM_MPLY, HM_MNXT, KC_RGUI, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                   KC_NO,   KC_NO,   KC_TRNS,               KC_TRNS, KC_NO,   KC_NO
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
        case UE_COMBO:
        case SS_COMBO:
        case OE_COMBO:
        case AE_COMBO:
            return 20;
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
