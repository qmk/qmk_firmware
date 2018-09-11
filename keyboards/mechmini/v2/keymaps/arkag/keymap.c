#include QMK_KEYBOARD_H

// Start: Written by konstantin: vomindoraan
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void send_unicode_hex_string(const char *str) {
        if (!str) { return; } // Saftey net
        while (*str) {
                // Find the next code point (token) in the string
                for (; *str == ' '; str++);
                size_t n = strcspn(str, " "); // Length of the current token
                char code_point[n+1];
                strncpy(code_point, str, n);
                code_point[n] = '\0'; // Make sure it's null-terminated

                // Normalize the code point: make all hex digits lowercase
                for (char *p = code_point; *p; p++) {
                        *p = tolower(*p);
                }

                // Send the code point as a Unicode input string
                unicode_input_start();
                send_string(code_point);
                unicode_input_finish();
                str += n; // Move to the first ' ' (or '\0') after the current token
        }
}
// End: Written by konstantin: vomindoraan

#define _BASE    0
#define _RAISE   1
#define _LOWER   2
#define _KEEB    3
#define _MEDIA   4

#define MOD_CTL_MASK (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))
#define MOD_GUI_MASK (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))
#define MOD_SFT_MASK (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))

#define LED_FLASH_DELAY 150

#define EECONFIG_USERSPACE (uint8_t *)20

#define LRALT       TD(TD_LALT_RALT)
#define QUOTE       TD(TD_SING_DOUB)
#define GRAVE       TD(TD_GRV_3GRV)
#define OPENBRACK   TD(TD_BRCK_PARN_O)
#define CLOSEBRACK  TD(TD_BRCK_PARN_C)
#define THREE       TD(TD_3_GRV_ACT)
#define STRIKE      TD(TD_STRK_SHOT)
#define HYPHEN      TD(TD_HYPH_UNDR)
#define CEDILLA     TD(TD_C_CED)
#define HTTPS       TD(TD_SLSH_HTTP)
#define SPECIAL     TD(TD_SPECIAL)
#define KEEB        MO(3)
#define LOWER       MO(2)
#define RAISE       MO(1)
#define MEDIA       MO(4)

typedef enum {
        OS_MAC, // Don't assign values
        OS_WIN,
        OS_NIX,
        _OS_COUNT,
} OS;

typedef struct {
        uint16_t  h;
        uint8_t   s;
        uint8_t   v;
} Color;

typedef enum {
        always_on = 0,
        flash_begin,
        flash_off,
        flash_on,
        reset_underglow,
} RGBState;

uint8_t   current_os, mod_primary_mask, num_extra_flashes_off = 0;
uint16_t  timer_one, timer_two, elapsed;
bool      loop = false, paste_ready = false;
Color     underglow, hsv_none = {0,0,0}, hsv_white = {0,0,127}, flash_color;
RGBState  current_state = always_on;

enum custom_keycodes {
        M_PMOD = SAFE_RANGE,
        M_SMOD,
        M_P_B,
        M_C_A_D,
        M_CALC,
        M_OS,
        M_TF,
        M_TM,
        M_GGT,
        M_LOD,
        M_BOLD,
        M_ITAL,
        M_ULIN,
        M_SNIPENT,
        M_REPO,
        M_SHRUG,
        M_UF,
};

enum tapdances {
        TD_3_GRV_ACT = 0,
        TD_C_CED,
        TD_GRV_3GRV,
        TD_SLSH_HTTP,
        TD_SING_DOUB,
        TD_HYPH_UNDR,
        TD_STRK_SHOT,
        TD_SPECIAL,
        TD_BRCK_PARN_O,
        TD_BRCK_PARN_C,
        TD_LALT_RALT,
};

Color mod_color(Color current_color, bool should_add, uint16_t change_amount) {
        uint16_t addlim = 359 - change_amount;
        uint16_t sublim = change_amount;
        uint16_t leftovers;
        if (should_add) {
                if (current_color.h <= addlim) {
                        current_color.h += change_amount;
                } else {
                        leftovers = (359 + change_amount) % 359;
                        current_color.h  = 0 + leftovers;
                }
        } else {
                if (current_color.h >= sublim) {
                        current_color.h -= change_amount;
                } else {
                        leftovers = change_amount - current_color.h;
                        current_color.h  = 359 - leftovers;
                }
        }
        return current_color;
}

void set_color (Color new, bool update) {
        rgblight_sethsv_eeprom_helper(new.h, new.s, new.v, update);
}

void flash_rgb (void) {
        switch(current_state) {
        case always_on:
                return;

        case flash_begin:
                timer_one = timer_read();
                current_state = flash_off;

        case flash_off:
                timer_two = timer_read();
                elapsed = timer_two - timer_one;
                if (elapsed >= LED_FLASH_DELAY) {
                        set_color(hsv_none, false);
                        timer_one = timer_read();
                        current_state = flash_on;
                }
                return;

        case flash_on:
                timer_two = timer_read();
                elapsed = timer_two - timer_one;
                if (elapsed >= LED_FLASH_DELAY) {
                        set_color(flash_color, false);
                        timer_one = timer_read();
                        if (loop) {
                                current_state = flash_off;
                        } else if (num_extra_flashes_off > 0) {
                                current_state = flash_off;
                                num_extra_flashes_off--;
                        } else {
                                current_state = reset_underglow;
                        }
                }
                return;

        case reset_underglow:
                set_color(underglow, false);
                current_state = always_on;
                return;
        }
}

void set_os (uint8_t os, bool update) {
        current_os = os;
        if (update) {
                eeprom_update_byte(EECONFIG_USERSPACE, current_os);
        }
        switch (os) {
        case OS_MAC:
                set_unicode_input_mode(UC_OSX);
                underglow = (Color){ 300, 255, 255 };
                mod_primary_mask = MOD_GUI_MASK;
                break;
        case OS_WIN:
                set_unicode_input_mode(UC_WINC);
                underglow = (Color){ 180, 255, 255 };
                mod_primary_mask = MOD_CTL_MASK;
                break;
        case OS_NIX:
                set_unicode_input_mode(UC_LNX);
                underglow = (Color){ 60, 255, 255 };
                mod_primary_mask = MOD_CTL_MASK;
                break;
        default:
                underglow = (Color){ 0, 0, 255 };
                mod_primary_mask = MOD_CTL_MASK;
        }
        set_color(underglow, update);
        flash_color = underglow;
        current_state = flash_begin;
        num_extra_flashes_off = 0;
}

void set_paste_ready(void) {
        paste_ready = true;
        set_color(hsv_white, false);
        flash_color = hsv_white;
        current_state = flash_begin;
        num_extra_flashes_off = 2;
}

void tap_key(uint8_t keycode) {
        register_code(keycode);
        unregister_code(keycode);
}

// register GUI if Mac or Ctrl if other
void pri_mod(bool press) {
        if (press) {
                if (current_os == OS_MAC) {
                        register_code(KC_LGUI);
                } else {
                        register_code(KC_LCTL);
                }
        } else {
                if (current_os == OS_MAC) {
                        unregister_code(KC_LGUI);
                } else {
                        unregister_code(KC_LCTL);
                }
        }
}

// register Ctrl if Mac or GUI if other
void sec_mod(bool press) {
        if (press) {
                if (current_os == OS_MAC) {
                        register_code(KC_LCTL);
                } else {
                        register_code(KC_LGUI);
                }
        } else {
                if (current_os == OS_MAC) {
                        unregister_code(KC_LCTL);
                } else {
                        unregister_code(KC_LGUI);
                }
        }
}

void surround_type(uint8_t num_of_chars, uint16_t keycode, bool use_shift) {
        if (use_shift) {
                register_code(KC_LSFT);
        }
        for (int i = 0; i < num_of_chars; i++) {
                tap_key(keycode);
        }
        if (use_shift) {
                unregister_code(KC_LSFT);
        }
        for (int i = 0; i < (num_of_chars/2); i++) {
                tap_key(KC_LEFT);
        }
}

void long_keystroke(size_t num_of_keys, uint16_t keys[]) {
        for (int i = 0; i < num_of_keys-1; i++) {
                register_code(keys[i]);
        }
        tap_key(keys[num_of_keys-1]);
        for (int i = 0; i < num_of_keys-1; i++) {
                unregister_code(keys[i]);
        }
}

void dance_grv (qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1) {
                tap_key(KC_GRV);
        } else if (state->count == 2) {
                surround_type(2, KC_GRAVE, false);
        } else {
                surround_type(6, KC_GRAVE, false);
        }
}

void dance_quot (qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1) {
                tap_key(KC_QUOT);
        } else if (state->count == 2) {
                surround_type(2, KC_QUOTE, false);
        } else if (state->count == 3) {
                surround_type(2, KC_QUOTE, true);
        }
}

void dance_strk (qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1) {
                surround_type(4, KC_TILDE, true);
        } else if (state->count == 2) {
                if (current_os == OS_MAC) {
                        long_keystroke(3, (uint16_t[]){KC_LGUI, KC_LSFT, KC_4});
                } else if (current_os == OS_WIN) {
                        long_keystroke(3, (uint16_t[]){KC_LGUI, KC_LSFT, KC_S});
                }
        }
}

void send_https(void) {
        SEND_STRING("https://");
}

void send_http(void) {
        SEND_STRING("http://");
}

void dance_http (qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1) {
                tap_key(KC_SLSH);
        } else if (state->count == 2) {
                send_https();
        } else {
                send_http();
        }
}

void send_copy_paste (void) {
        pri_mod(true);
        if (!paste_ready) {
                SEND_STRING(SS_TAP(X_C));
                set_paste_ready();
                loop = true;
        }
        else {
                SEND_STRING(SS_TAP(X_V));
                paste_ready = false;
                loop = false;
        }
        pri_mod(false);
}

void send_cut_paste (void) {
        pri_mod(true);
        if (!paste_ready) {
                SEND_STRING(SS_TAP(X_X));
                set_paste_ready();
                loop = true;
        }
        else {
                SEND_STRING(SS_TAP(X_V));
                paste_ready = false;
                loop = false;
        }
        pri_mod(false);
}

void send_lod(void) {
        send_unicode_hex_string("0CA0 005F 005F 0CA0");
}

void dance_special (qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1) {
        } else if (state->count == 2) {
                send_copy_paste();
        } else if (state->count == 3) {
                send_cut_paste();
        } else {
                send_lod();
        }
}

void dance_3 (qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1) {
                register_code (KC_3);
        } else if (state->count == 2) {
                send_unicode_hex_string("00E8");
        } else if (state->count == 3) {
                send_unicode_hex_string("00E9");
        }
}

void dance_c (qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1) {
                register_code (KC_C);
        } else if (state->count == 2) {
                send_unicode_hex_string("00E7");
        }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_3_GRV_ACT]      = ACTION_TAP_DANCE_FN (dance_3),
        [TD_C_CED]          = ACTION_TAP_DANCE_FN (dance_c),
        [TD_GRV_3GRV]       = ACTION_TAP_DANCE_FN (dance_grv),
        [TD_SLSH_HTTP]      = ACTION_TAP_DANCE_FN (dance_http),
        [TD_SING_DOUB]      = ACTION_TAP_DANCE_FN (dance_quot),
        [TD_STRK_SHOT]      = ACTION_TAP_DANCE_FN (dance_strk),
        [TD_SPECIAL]        = ACTION_TAP_DANCE_FN (dance_special),
        [TD_HYPH_UNDR]      = ACTION_TAP_DANCE_DOUBLE (KC_MINS, LSFT(KC_MINS)),
        [TD_BRCK_PARN_O]    = ACTION_TAP_DANCE_DOUBLE (KC_LBRC, LSFT(KC_9)),
        [TD_BRCK_PARN_C]    = ACTION_TAP_DANCE_DOUBLE (KC_RBRC, LSFT(KC_0)),
        [TD_LALT_RALT]      = ACTION_TAP_DANCE_DOUBLE (KC_LALT, KC_RALT),
};

void matrix_init_user(void) {
        current_os = eeprom_read_byte(EECONFIG_USERSPACE);
        set_os(current_os, false);
}

void matrix_scan_user(void) {
        flash_rgb();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
        switch (keycode) {
        case M_PMOD:
                if (record->event.pressed) {
                        pri_mod(true);
                } else {
                        pri_mod(false);
                }
                return false;

        case M_SMOD:
                if (record->event.pressed) {
                        sec_mod(true);
                } else {
                        sec_mod(false);
                }
                return false;

        case M_P_B:
                if (record->event.pressed) {
                        if (current_os == OS_WIN) {
                                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_PAUSE) SS_UP(X_LGUI));
                        } else {
                        }
                }
                return false;

        case M_C_A_D:
                if (record->event.pressed) {
                        if (current_os == OS_WIN) {
                                SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LALT) SS_TAP(X_DELETE) SS_UP(X_LALT) SS_UP(X_LCTRL));
                        } else {
                        }
                }
                return false;

        case M_CALC:
                if (record->event.pressed) {
                        if (current_os == OS_WIN) {
                                SEND_STRING(SS_TAP(X_CALCULATOR));
                                // SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_R) SS_UP(X_LGUI) "calc.exe" SS_TAP(X_ENTER));
                        } else if (current_os == OS_MAC) {
                                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_SPACE) SS_UP(X_LGUI) "calculator" SS_TAP(X_ENTER));
                        }
                }
                return false;

        case M_OS:
                if (record->event.pressed) {
                        set_os((current_os+1) % _OS_COUNT, true);
                }
                return false;

        case M_LOD:
                if (record->event.pressed) {
                        send_lod();
                }
                return false;

        case M_TF:
                if (record->event.pressed) {
                        send_unicode_hex_string("0028 256F 2035 0414 2032 0029 256F 5F61 253B 2501 253B");
                }
                return false;

        case M_UF:
                if (record->event.pressed) {
                        send_unicode_hex_string("252C 2500 252C 30CE 0028 0020 00BA 0020 005F 0020 00BA 0020 30CE 0029");
                }
                return false;

        case M_SHRUG:
                if (record->event.pressed) {
                        send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
                }
                return false;

        case M_TM:
                if (record->event.pressed) {
                        send_unicode_hex_string("2122");
                }
                return false;

        case M_REPO:
                if (record->event.pressed) {
                        SEND_STRING("https://github.com/arkag/qmk_firmware/tree/master/keyboards/mechmini/v2/keymaps/arkag");
                }
                return false;

        case M_GGT:
                if (record->event.pressed) {
                        SEND_STRING("@GrahamGoldenTech.com");
                }
                return false;

        case M_SNIPENT:
                if (record->event.pressed) {
                        surround_type(6, KC_GRAVE, false);
                        pri_mod(true);
                        register_code(KC_V);
                        unregister_code(KC_V);
                        pri_mod(false);
                        SEND_STRING(SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_TAP(X_ENTER));
                        paste_ready = false;
                }
                return false;

        case M_BOLD:
                if (record->event.pressed) {
                        surround_type(4, KC_8, true);
                }
                return false;

        case M_ITAL:
                if (record->event.pressed) {
                        surround_type(2, KC_8, true);
                }
                return false;

        case M_ULIN:
                if (record->event.pressed) {
                        surround_type(4, KC_MINS, true);
                }
                return false;

        case KC_LSFT:
                if (record->event.pressed) {
                        set_color(mod_color(underglow, true, 50), false);
                        SEND_STRING(SS_DOWN(X_LSHIFT));
                } else {
                        set_color(underglow, false);
                        SEND_STRING(SS_UP(X_LSHIFT));
                }
                return false;

        case KEEB:
        case RAISE:
        case LOWER:
                return true;
                break;

        case KC_BSPC:
                if (record->event.pressed) {
                        underglow = mod_color(underglow, false, 10);
                        set_color(underglow, false);
                        SEND_STRING(SS_DOWN(X_BSPACE));
                } else {
                        SEND_STRING(SS_UP(X_BSPACE));
                }
                return false;

        default:
                if (record->event.pressed) {
                        underglow = mod_color(underglow, true, 10);
                        set_color(underglow, false);
                }
                return true;
        }
}

uint32_t layer_state_set_user(uint32_t state) {
        Color layer = underglow;
        switch (biton32(state)) {
        case _MEDIA:
                layer = mod_color(layer, true, 150);
                break;
        case _KEEB:
                layer = mod_color(layer, false, 150);
                break;
        case _LOWER:
                layer = mod_color(layer, false, 100 );
                break;
        case _RAISE:
                layer = mod_color(layer, true, 100);
                break;
        default:
                break;
        }
        set_color(layer, false);
        return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        [_BASE] = LAYOUT_2u_space_ortho(
                KC_ESC,   KC_Q,       KC_W,       KC_E,     KC_R,          KC_T, KC_Y,          KC_U,     KC_I,     KC_O,       KC_P,       KC_BSPC,
                KC_TAB,   KC_A,       KC_S,       KC_D,     KC_F,          KC_G, KC_H,          KC_J,     KC_K,     KC_L,       KC_SCLN,    QUOTE,
                KC_LSFT,  KC_Z,       KC_X,       KC_C,     KC_V,          KC_B, KC_N,          KC_M,     KC_COMM,  KC_DOT,     KC_UP,      KC_ENT,
                M_PMOD,   LRALT,      M_SMOD,     LOWER,    RAISE,           KC_SPC,            KC_SLSH,  SPECIAL,  KC_LEFT,    KC_DOWN,    KC_RGHT),

        [_RAISE] = LAYOUT_2u_space_ortho(
                GRAVE,    KC_1,       KC_2,       THREE,    KC_4,       KC_5,     KC_6,         KC_7,     KC_8,     KC_9,       KC_0,       _______,
                _______,  OPENBRACK,  CLOSEBRACK, KC_BSLS,  HYPHEN,     KC_EQL,   _______,      KC_4,     KC_5,     KC_6,       _______,    KC_NLCK,
                _______,  _______,    _______,    CEDILLA,  _______,    KC_COMM,  KC_PDOT,      KC_1,     KC_2,     KC_3,       KC_PPLS,    KC_PENT,
                _______,  _______,    _______,    KEEB,     _______,         _______,           HTTPS,    M_OS,     KC_PSLS,    KC_PMNS,    KC_PAST),

        [_LOWER] = LAYOUT_2u_space_ortho(
                _______,  _______,    _______,    _______,  _______,    M_TM,    _______,       M_ULIN,   M_ITAL,   _______,    M_P_B,      M_C_A_D,
                _______,  _______,    STRIKE,     _______,  _______,    M_GGT,   _______,       M_UF,     M_REPO,   M_SNIPENT,  _______,    _______,
                _______,  KC_DEL,     _______,    _______,  _______,    M_BOLD,  _______,       M_TF,     M_SHRUG,  M_LOD,      KC_PGUP,    _______,
                _______,  _______,    _______,    _______,  _______,          MEDIA,            _______,  M_CALC,   KC_HOME,    KC_PGDOWN,  KC_END),

        [_KEEB] = LAYOUT_2u_space_ortho(
                KC_F1,    KC_F2,      KC_F3,      KC_F4,    KC_F5,      KC_F6,    KC_F7,        KC_F8,    KC_F9,    KC_F10,     KC_F11,     KC_F12,
                _______,  BL_TOGG,    BL_STEP,    BL_INC,   BL_DEC,     BL_BRTG,  _______,      _______,  _______,  _______,    _______,    _______,
                _______,  RGB_TOG,    RGB_MOD,    RGB_VAI,  RGB_VAD,    RGB_HUI,  RGB_HUD,      RGB_SAI,  RGB_SAD,  _______,    _______,    _______,
                RESET,    _______,    _______,    _______,  _______,         _______,           _______,  _______,  _______,    _______,    _______),

        [_MEDIA] = LAYOUT_2u_space_ortho(
                _______,  _______,    _______,    _______,  _______,    _______,    _______,    _______,  _______,  _______,    _______,    _______,
                _______,  _______,    _______,    _______,  _______,    _______,    _______,    _______,  _______,  _______,    _______,    _______,
                _______,  _______,    _______,    _______,  _______,    _______,    _______,    _______,  _______,  KC_MPLY,    KC_VOLU,    KC_MUTE,
                _______,  _______,    _______,    _______,  _______,         _______,           _______,  _______,  KC_MPRV,    KC_VOLD,    KC_MNXT),
};
