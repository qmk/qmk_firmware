#include QMK_KEYBOARD_H
#include "os_detection.h"
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
        KC_GRV,  HM_A, HM_R, HM_S,   HM_T,   KC_G,   TG(1),    KC_LGUI,  KC_M,   HM_N,     HM_E,    HM_I,   HM_O,    KC_QUOT,
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

bool process_detected_host_os_user(os_variant_t detected_os) {
    if (detected_os == OS_LINUX) {
        set_unicode_input_mode(UNICODE_MODE_LINUX);
    }
    return true;
}

// Treat "unsure" as macOS so there's no gap right after boot before
// detection completes.
static inline bool host_is_mac(void) {
    os_variant_t os = detected_host_os();
    return os != OS_WINDOWS && os != OS_LINUX;
}

static uint16_t kp_digit_keycode(uint8_t digit) {
    switch (digit) {
        case 0: return KC_KP_0;
        case 1: return KC_KP_1;
        case 2: return KC_KP_2;
        case 3: return KC_KP_3;
        case 4: return KC_KP_4;
        case 5: return KC_KP_5;
        case 6: return KC_KP_6;
        case 7: return KC_KP_7;
        case 8: return KC_KP_8;
        default: return KC_KP_9;
    }
}

static void send_windows_alt_code(uint8_t code) {
    bool num_lock_was_on = host_keyboard_led_state().num_lock;
    if (!num_lock_was_on) {
        tap_code(KC_NUM_LOCK);
        wait_ms(20);
    }

    register_code(KC_LALT);
    wait_ms(10);
    tap_code(kp_digit_keycode(0)); // leading zero forces the ANSI codepage
    wait_ms(10);
    tap_code(kp_digit_keycode((code / 100) % 10));
    wait_ms(10);
    tap_code(kp_digit_keycode((code / 10) % 10));
    wait_ms(10);
    tap_code(kp_digit_keycode(code % 10));
    wait_ms(10);
    unregister_code(KC_LALT);

    if (!num_lock_was_on) {
        wait_ms(20);
        tap_code(KC_NUM_LOCK);
    }
}

// Works out upper/lowercase from held+one-shot shift XOR caps state, and
// consumes any pending one-shot shift so it doesn't leak into the next key.
static bool resolve_uppercase_and_consume_oneshot(void) {
    uint8_t mods    = get_mods();
    uint8_t os_mods = get_oneshot_mods();
    bool is_shifted = (mods | os_mods) & MOD_MASK_SHIFT;
    bool is_caps    = host_keyboard_led_state().caps_lock || is_caps_word_on();

    if (os_mods & MOD_MASK_SHIFT) {
        del_oneshot_mods(MOD_MASK_SHIFT);
    }

    return is_shifted ^ is_caps;
}

static void send_umlaut_mac(uint16_t target_keycode, bool send_upper) {
    uint8_t mods = get_mods();

    if (mods & MOD_MASK_SHIFT) {
        unregister_code(KC_LSFT);
        unregister_code(KC_RSFT);
    }

    register_code(KC_RALT);
    tap_code(KC_U);
    unregister_code(KC_RALT);

    if (send_upper) {
        register_code(KC_LSFT);
        tap_code(target_keycode);
        unregister_code(KC_LSFT);
    } else {
        tap_code(target_keycode);
    }

    if (mods & MOD_MASK_SHIFT) {
        set_mods(mods);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DE_AE:
        case DE_OE:
        case DE_UE:
            if (record->event.pressed) {
                bool send_upper = resolve_uppercase_and_consume_oneshot();

                if (host_is_mac()) {
                    uint16_t target_keycode;
                    switch (keycode) {
                        case DE_AE: target_keycode = KC_A; break;
                        case DE_OE: target_keycode = KC_O; break;
                        default:    target_keycode = KC_U; break;
                    }
                    send_umlaut_mac(target_keycode, send_upper);
                } else if (detected_host_os() == OS_WINDOWS) {
                    uint8_t lower_code, upper_code;
                    switch (keycode) {
                        case DE_AE: lower_code = 228; upper_code = 196; break;
                        case DE_OE: lower_code = 246; upper_code = 214; break;
                        default:    lower_code = 252; upper_code = 220; break;
                    }
                    send_windows_alt_code(send_upper ? upper_code : lower_code);
                } else { // Linux
                    uint32_t lower_cp, upper_cp;
                    switch (keycode) {
                        case DE_AE: lower_cp = 0x00E4; upper_cp = 0x00C4; break;
                        case DE_OE: lower_cp = 0x00F6; upper_cp = 0x00D6; break;
                        default:    lower_cp = 0x00FC; upper_cp = 0x00DC; break;
                    }
                    register_unicode(send_upper ? upper_cp : lower_cp);
                }
            }
            return false;

        case DE_SS:
            if (record->event.pressed) {
                uint8_t mods    = get_mods();
                bool send_upper = resolve_uppercase_and_consume_oneshot();
                bool is_caps    = host_keyboard_led_state().caps_lock || is_caps_word_on();

                if (host_is_mac()) {
                    if (send_upper) {
                        if (!is_caps) {
                            register_code(KC_LSFT);
                        } else if (mods & MOD_MASK_SHIFT) {
                            unregister_code(KC_LSFT);
                            unregister_code(KC_RSFT);
                        }
                        tap_code(KC_S);
                        if (!is_caps) {
                            unregister_code(KC_LSFT);
                        } else if (mods & MOD_MASK_SHIFT) {
                            set_mods(mods);
                        }
                    } else {
                        if (mods & MOD_MASK_SHIFT) {
                            unregister_code(KC_LSFT);
                            unregister_code(KC_RSFT);
                        }
                        register_code(KC_RALT);
                        tap_code(KC_S);
                        unregister_code(KC_RALT);
                        if (mods & MOD_MASK_SHIFT) {
                            set_mods(mods);
                        }
                    }
                } else if (detected_host_os() == OS_WINDOWS) {
                    if (send_upper) {
                        tap_code(KC_S); // capital ẞ isn't in this codepage
                    } else {
                        send_windows_alt_code(223); // ß
                    }
                } else { // Linux
                    if (send_upper) {
                        tap_code(KC_S);
                    } else {
                        register_unicode(0x00DF); // ß
                    }
                }
            }
            return false;

        case DE_EURO:
            if (record->event.pressed) {
                if (host_is_mac()) {
                    uint8_t mods = get_mods();
                    if (mods & MOD_MASK_SHIFT) {
                        unregister_code(KC_LSFT);
                        unregister_code(KC_RSFT);
                    }
                    register_code(KC_RALT);
                    register_code(KC_LSFT);
                    tap_code(KC_2);
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RALT);
                    if (mods & MOD_MASK_SHIFT) {
                        set_mods(mods);
                    }
                } else if (detected_host_os() == OS_WINDOWS) {
                    send_windows_alt_code(128); // €
                } else {
                    register_unicode(0x20AC);
                }
            }
            return false;

        case DE_PARA:
            if (record->event.pressed) {
                if (host_is_mac()) {
                    uint8_t mods = get_mods();
                    if (mods & MOD_MASK_SHIFT) {
                        unregister_code(KC_LSFT);
                        unregister_code(KC_RSFT);
                    }
                    register_code(KC_RALT);
                    tap_code(KC_6);
                    unregister_code(KC_RALT);
                    if (mods & MOD_MASK_SHIFT) {
                        set_mods(mods);
                    }
                } else if (detected_host_os() == OS_WINDOWS) {
                    send_windows_alt_code(167); // §
                } else {
                    register_unicode(0x00A7);
                }
            }
            return false;
    }
    return true;
}
