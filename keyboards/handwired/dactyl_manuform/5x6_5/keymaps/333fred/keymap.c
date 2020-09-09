#include QMK_KEYBOARD_H
#include "333fred.h"

char wpm_str[8];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_5x6_5(
     KC_GRV,        KC_1,        KC_2,  KC_3,  KC_4,    KC_5,                                                    KC_6,   KC_7,     KC_8,         KC_9,   KC_0,           KC_MINS,
     KC_TAB,        KC_Q,        KC_W,  KC_E,  KC_R,    KC_T,                                                    KC_Y,   KC_U,     KC_I,         KC_O,   KC_P,           KC_BSLS,
     KC_ESC,        KC_A,        KC_S,  KC_D,  KC_F,    KC_G,                                                    KC_H,   KC_J,     KC_K,         KC_L,   KC_SCLN,        KC_QUOT,
     OSM(MOD_LSFT), CTL_T(KC_Z), KC_X,  KC_C,  KC_V,    KC_B,                                                    KC_N,   KC_M,     KC_COMM,      KC_DOT, CTL_T(KC_SLSH), OSM(MOD_RSFT),
                                 KC_F4,        KC_LALT, KC_BSPC, TD(TD_SYM_VIM),    KC_DEL,     KC_UP,   KC_ENT, KC_SPC, OSL(VIM),               KC_EQL,
                                                                 TD(TD_COPY_PASTE), KC_LCTL,    KC_DOWN, KC_RGUI
  ),

  [SYMB] = LAYOUT_5x6_5(
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                          KC_F6,   KC_F7,   KC_F8,    KC_F9,  KC_F10,  KC_F11,
     _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_PIPE,                                        _______, KC_7,    KC_8,     KC_9,   _______, KC_F12,
     _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,                                         _______, KC_4,    KC_5,     KC_6,   _______, _______,
     _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                                        _______, KC_1,    KC_2,     KC_3,   _______, _______,
                       KC_F7,            _______, _______, _______, _______,    KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,  KC_ENT,
                                                           _______, _______,    KC_VOLD, _______
  ),

  [VIM] = LAYOUT_5x6_5(
     _______, RESET,   _______, _______, _______, _______,                                         _______, _______, _______, _______, RESET,   _______,
     _______, _______, _______, _______, KC_LSFT, _______,                                         _______, _______, _______, _______, _______, _______,
     _______, DLEFT,   DRIGHT,  KC_LCTL, KC_LGUI, _______,                                         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
     _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
                       _______,          _______, _______,_______, _______,     TG(GAME), _______, _______, _______,          _______,
                                                          _______, _______,     _______,  _______
  ),

  [GAME] = LAYOUT_5x6_5(
     KC_ESC, KC_1,    KC_2,    KC_3,  KC_4,    KC_5,                                          KC_6,    KC_7,     KC_8,         KC_9,   KC_0,    KC_MINS,
     KC_T,   KC_TAB,  KC_Q,    KC_W,  KC_E,    KC_R,                                          KC_Y,    KC_U,     KC_I,         KC_O,   KC_P,    KC_BSLS,
     KC_G,   KC_LCTL, KC_A,    KC_S,  KC_D,    KC_F,                                          KC_H,    KC_J,     KC_K,         KC_L,   KC_SCLN, KC_QUOT,
     KC_B,   KC_LSFT, KC_Z,    KC_X,  KC_C,    KC_V,                                          KC_N,    KC_M,     KC_COMM,      KC_DOT, KC_SLSH, KC_RSFT,
                      KC_LOCK,        KC_LALT, KC_SPC, KC_ENT,  KC_GRV,    TG(GAME), _______, _______, _______,                KC_EQL,
                                                       KC_BSPC, KC_F5,     KC_F6,    _______
  ),
};

uint16_t quote_timer;
uint8_t currentQuote = 0;

void keyboard_post_init_user(void) {
    quote_timer = timer_read();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_process_keycode(keycode);
    return !try_handle_macro(keycode, record);
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}

void render_led_status(void) {
    led_t led_state = host_keyboard_led_state();
    if (led_state.num_lock || led_state.caps_lock || led_state.scroll_lock) {
        oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
        oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
        oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    }
}

void render_mods_status(void) {
    bool ctrl = keyboard_report->mods & MOD_BIT(KC_LCTL) || keyboard_report->mods & MOD_BIT(KC_RCTL);
    bool shft = keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT);
    bool alt  = keyboard_report->mods & MOD_BIT(KC_LALT) || keyboard_report->mods & MOD_BIT(KC_RALT);
    bool gui  = keyboard_report->mods & MOD_BIT(KC_LGUI) || keyboard_report->mods & MOD_BIT(KC_RGUI);

    oled_write_P(ctrl ? PSTR("CTRL ") : PSTR("     "), false);
    oled_write_P(shft ? PSTR("SHIFT ") : PSTR("      "), false);
    oled_write_P(alt ? PSTR("ALT ") : PSTR("    "), false);
    oled_write_ln_P(gui ? PSTR("GUI ") : PSTR("    "), false);
}

#define MAX_LINES 9

void write_quote(const char* data, const uint8_t num_lines) {
    uint8_t current_line = 0;
    for (; current_line < (MAX_LINES - num_lines) / 2; current_line++) {
        oled_advance_page(true);
    }

    oled_write_ln_P(data, false);

    for (current_line += num_lines; current_line < MAX_LINES; current_line++)
    {
        oled_advance_page(true);
    }
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_logo();
        oled_advance_page(/* clearPageRemainder */ true);
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case BASE:
                oled_write_ln_P(PSTR("Base"), false);
                break;
            case SYMB:
                oled_write_ln_P(PSTR("Symbols"), false);
                break;
            case VIM:
                oled_write_ln_P(PSTR("Vim"), false);
                break;
            case GAME:
                oled_write_ln_P(PSTR("Gaming"), false);
                break;
        }

        snprintf(wpm_str, 8, "WPM: %03d", get_current_wpm());
        oled_write_ln(wpm_str, false);

        render_mods_status();
        render_led_status();
    } else {
        if (timer_elapsed(quote_timer) > 300000 /* 5 minutes */) {
            srand(timer_read());
            currentQuote = rand() % 13;
            quote_timer  = timer_read();
        }

        // Max character count on my screen is 20 characters per line.
        switch (currentQuote) {
            case 0:
                write_quote(PSTR("  Life before Death \n"
                                 "  Strength before   \n"
                                 "      Weakness      \n"
                                 "   Journey before   \n"
                                 "    Destination"),
                            5);
                break;
            case 1:
                write_quote(PSTR(" Honor is dead, but \n"
                                 "I'll see what I can \n"
                                 "        do."),
                            3);
                break;
            case 2:
                write_quote(PSTR(" You cannot have my \n"
                                 "       pain!"),
                            2);
                break;
            case 3:
                write_quote(PSTR(" Pride doesn't win  \n"
                                 "     battles"),
                            2);
                break;
            case 4:
                write_quote(PSTR("  I have practice   \n"
                                 " following fools in \n"
                                 "   their reckless   \n"
                                 "      pursuits."),
                            4);
                break;
            case 5:
                write_quote(PSTR("  What is the most  \n"
                                 "  important step a  \n"
                                 "    man can take?"),
                            3);
                break;
            case 6:
                write_quote(PSTR(" It's the next one. \n"
                                 "  Always the next   \n"
                                 "   step, Dalinar."),
                            3);
                break;
            case 7:
                write_quote(PSTR("    NO MATING."), 1);
                break;
            case 8:
                write_quote(PSTR("   Inappropriate?   \n"
                                 "Such as... dividing \n"
                                 "     by zero?"),
                            3);
                break;
            case 9:
                write_quote(PSTR("   I am a stick!"), 1);
                break;
            case 10:
                write_quote(PSTR("  But you could be  \n"
                                 "       fire!"),
                            1);
                break;
            case 11:
                write_quote(PSTR("    Sometimes a     \n"
                                 "   hyprocrite is    \n"
                                 " nothing more than  \n"
                                 " than a man in the  \n"
                                 "process of changing"),
                            5);
                break;
            case 12:
                write_quote(PSTR("    Oh, Light!"), 1);
                break;
        }
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    // On the left, control the volume. On the right, scroll the page
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    } else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
