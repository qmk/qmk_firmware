/*
  Copyright (c) 2020 Fred Silberberg

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include QMK_KEYBOARD_H
#include "333fred.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_5x6_5(
     KC_GRV,        KC_1,        KC_2,  KC_3,  KC_4,    KC_5,                                                           KC_6,   KC_7,     KC_8,         KC_9,   KC_0,           KC_MINS,
     KC_TAB,        KC_Q,        KC_W,  KC_E,  KC_R,    KC_T,                                                           KC_Y,   KC_U,     KC_I,         KC_O,   KC_P,           KC_BSLS,
     KC_ESC,        KC_A,        KC_S,  KC_D,  KC_F,    KC_G,                                                           KC_H,   KC_J,     KC_K,         KC_L,   KC_SCLN,        KC_QUOT,
     OSM(MOD_LSFT), CTL_T(KC_Z), KC_X,  KC_C,  KC_V,    KC_B,                                                           KC_N,   KC_M,     KC_COMM,      KC_DOT, CTL_T(KC_SLSH), OSM(MOD_RSFT),
                                 KC_F4,        KC_LALT, KC_BSPC, TD(TD_SYM_VIM), KC_DEL,               KC_UP,   KC_ENT, KC_SPC, OSL(VIM),               KC_EQL,
                                                                 KC_LGUI,        TD(TD_COPY_PASTE),    KC_DOWN, OSM(MOD_RCTL)
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

uint32_t quote_timer;

void keyboard_post_init_user(void) { quote_timer = 0; }

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
    uint8_t mods = get_mods() | get_oneshot_mods();
    bool    ctrl = mods & MOD_MASK_CTRL;
    bool    shft = mods & MOD_MASK_SHIFT;
    bool    alt  = mods & MOD_MASK_ALT;
    bool    gui  = mods & MOD_MASK_GUI;

    oled_write_P(ctrl ? PSTR("CTRL ") : PSTR("     "), false);
    oled_write_P(shft ? PSTR("SHIFT ") : PSTR("      "), false);
    oled_write_P(alt ? PSTR("ALT ") : PSTR("    "), false);
    oled_write_ln_P(gui ? PSTR("GUI ") : PSTR("    "), false);
}

#define MAX_LINES 8

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

        render_mods_status();
        render_led_status();
    } else {
        if ((quote_timer != 0 && timer_elapsed32(quote_timer) < 300000 /* 5 minutes */) || !is_oled_on()) {
            return;
        }

        srand(timer_read32());
        int currentQuote = rand() % 63;
        quote_timer  = timer_read32();

        // Max character count on my screen is 20 characters per line.
        // Quotes are from various fantasy books, mostly either from
        // The Stormlight Archive or from The Wheel of Time.
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
                write_quote(PSTR(" You surrender when \n"
                                 " you are dead. Many \n"
                                 "a man has been given\n"
                                 "       less."),
                            4);
                break;
            case 13:
                write_quote(PSTR(" Kneel and swear to \n"
                                 " the Lord Dragon,...\n"
                                 "   or you will be   \n"
                                 "      knelt."),
                            4);
                break;
            case 14:
                write_quote(PSTR("I'm right, anyway. I\n"
                                 "wish I wasn't, but I\n"
                                 "  am. I bloody am."),
                            3);
                break;
            case 15:
                write_quote(PSTR(" Death rides on my  \n"
                                 "  shoulder,. Death  \n"
                                 "    walks in my     \n"
                                 "  footsteps. I am   \n"
                                 "       death."),
                            5);
                break;
            case 16:
                write_quote(PSTR("  The Golden Crane  \n"
                                 "  flies for Tarmon  \n"
                                 "      Gai'don"),
                            3);
                break;
            case 17:
                write_quote(PSTR("You humans are very \n"
                                 "     excitable"),
                            2);
                break;
            case 18:
                write_quote(PSTR("       Phaw!"), 1);
                break;
            case 19:
                write_quote(PSTR("I may be a fool, but\n"
                                 "  I intend to be a  \n"
                                 "     live fool."),
                            3);
                break;
            case 20:
                write_quote(PSTR(" Anyone who claimed \n"
                                 "  that old age had  \n"
                                 "    brought them    \n"
                                 "patience was either \n"
                                 "  lying or senile."),
                            5);
                break;
            case 21:
                write_quote(PSTR("Death is light as a \n"
                                 "feather; duty, heavy\n"
                                 "   as a mountain"),
                            3);
                break;
            case 22:
                write_quote(PSTR("Dovie'andi se tovya \n"
                                 "      sagain."),
                            2);
                break;
            case 23:
                write_quote(PSTR(" Carai an Caldazar! \n"
                                 "Carai an Ellisande! \n"
                                 "   Al Ellisande!"),
                            3);
                break;
            case 24:
                write_quote(PSTR("    Mia dovienya    \n"
                                 "  nesodhin soende."),
                            2);
                break;
            case 25:
                write_quote(PSTR(" The Wheel of Time  \n"
                                 "turns, and Ages come\n"
                                 " and pass, leaving  \n"
                                 "memories that become\n"
                                 "      legend."),
                            5);
                break;
            case 26:
                write_quote(PSTR("  Legend fades to   \n"
                                 "myth, and even myth \n"
                                 " is long forgotten  \n"
                                 " when the Age that  \n"
                                 "gave it birth comes \n"
                                 "       again."),
                            6);
                break;
            case 27:
                write_quote(PSTR(" What is too absurd \n"
                                 "   to believe is    \n"
                                 "believed because it \n"
                                 "is too absurd to be \n"
                                 "       a lie."),
                            5);
                break;
            case 28:
                write_quote(PSTR("And you gave me the \n"
                                 "  way out! Chew on  \n"
                                 "that bitterness for \n"
                                 "lunch, you flaming, \n"
                                 "burning, misbegotten\n"
                                 "       liars!"),
                            6);
                break;
            case 29:
                write_quote(PSTR("  He was going to   \n"
                                 "start having, 'I am \n"
                                 "not a bloody Lord', \n"
                                 " embroidered on his \n"
                                 "       coats."),
                            5);
                break;
            case 30:
                write_quote(PSTR("All was not lost, of\n"
                                 "  course. All was   \n"
                                 " never lost as long \n"
                                 " as you were alive."),
                            4);
                break;
            case 31:
                write_quote(PSTR(" Everything is just \n"
                                 "    bloody fine!"),
                            2);
                break;
            case 32:
                write_quote(PSTR("The wheel weaves as \n"
                                 "  the wheel wills"),
                            2);
                break;
            case 33:
                write_quote(PSTR("  Time to toss the  \n"
                                 "        dice"),
                            2);
                break;
            case 34:
                write_quote(PSTR("Always plan for the \n"
                                 " worst, child, that \n"
                                 "    way all your    \n"
                                 "   surprises are    \n"
                                 "   pleasant ones."),
                            5);
                break;
            case 35:
                write_quote(PSTR("'Pessimism, she is a\n"
                                 "   fond friend of   \n"
                                 "yours, yes?' 'That's\n"
                                 "  uncalled for. I   \n"
                                 "  barely know her.  \n"
                                 "Mere acquaintances, \n"
                                 "     at best.'"),
                            7);
                break;
            case 36:
                write_quote(PSTR("   Do not trouble   \n"
                                 "trouble till trouble\n"
                                 "   troubles you."),
                            3);
                break;
            case 37:
                write_quote(PSTR("If your enemy offers\n"
                                 "  you two targets,  \n"
                                 " strike at a third."),
                            3);
                break;
            case 38:
                write_quote(PSTR("The wind was not the\n"
                                 "beginning. There are\n"
                                 " neither beginnings \n"
                                 " nor endings to the \n"
                                 "   turning of the   \n"
                                 " Wheel of Time. But \n"
                                 "     it was _a_     \n"
                                 "     beginning."),
                            8);
                break;
            case 39:
                write_quote(PSTR("Bloody flaming ashes"), 1);
                break;
            case 40:
                write_quote(PSTR("Then follow Lord Mat\n"
                                 " whenever he calls  \n"
                                 "To dance with Jak O'\n"
                                 "    the Shadows."),
                            4);
                break;
            case 41:
                write_quote(PSTR("    There are no    \n"
                                 " endings, and never \n"
                                 "will be endings, to \n"
                                 " the turning of the \n"
                                 " Wheel of Time. But \n"
                                 " it was an ending."),
                            6);
                break;
            case 42:
                write_quote(PSTR(" TAI'SHAR MALKIER!"), 1);
                break;
            case 43:
                write_quote(PSTR("I would not mind you\n"
                                 " in my head, if you \n"
                                 "were not so clearly \n"
                                 "        mad."),
                            4);
                break;
            case 44:
                write_quote(PSTR("  ILYENA, MY LOVE,  \n"
                                 "    FORGIVE ME!"),
                            2);
                break;
            case 45:
                write_quote(PSTR(" Oh, Light. That's  \n"
                                 "impossible! We can't\n"
                                 "  use it! Cast it   \n"
                                 "away! That is death \n"
                                 " we hold, death and \n"
                                 "betrayal. It is HIM."),
                            6);
                break;
            case 46:
                write_quote(PSTR("Nothing ever goes as\n"
                                 " you expect. Expect \n"
                                 "  nothing, and you  \n"
                                 "    will not be     \n"
                                 " surprised. Expect  \n"
                                 " nothing. Hope for  \n"
                                 " nothing. Nothing."),
                            7);
                break;
            case 47:
                write_quote(PSTR("  Distant Weeping"), 1);
                break;
            case 48:
                write_quote(PSTR("Are you real? Am I?"), 1);
                break;
            case 49:
                write_quote(PSTR("  I'm just an old   \n"
                                 "gleeman, who could I\n"
                                 "    possibly be     \n"
                                 "   dangerous to?"),
                            4);
                break;
            case 50:
                write_quote(PSTR(" Mat bloody Cauthon \n"
                                 " is no bloody hero!"),
                            2);
                break;
            case 51:
                write_quote(PSTR("You are a coward and\n"
                                 " a tyrant. I'd name \n"
                                 " you Darkfriend as  \n"
                                 "well, but I suspect \n"
                                 " that the Dark One  \n"
                                 "  would perhaps be  \n"
                                 "   embarrassed to   \n"
                                 "associate with you."),
                            8);
                break;
            case 52:
                write_quote(PSTR(" I win again, Lews  \n"
                                 "      Therin."),
                            2);
                break;
            case 53:
                write_quote(PSTR("May you always find \n"
                                 "  water and shade."),
                            2);
                break;
            case 54:
                write_quote(PSTR(" I will never serve \n"
                                 "you, Father of Lies.\n"
                                 "In a thousand lives,\n"
                                 "I never have. I know\n"
                                 " that. I'm sure of  \n"
                                 "it. Come. It is time\n"
                                 "      to die."),
                            7);
                break;
            case 55:
                write_quote(PSTR(" There may be more  \n"
                                 "than one way to skin\n"
                                 " a cat, but the cat \n"
                                 "isn't going to like \n"
                                 "    any of them."),
                            5);
                break;
            case 56:
                write_quote(PSTR("Please see that they\n"
                                 " know, although the \n"
                                 "word Black may brand\n"
                                 "my name forever, my \n"
                                 "soul is Brown. Tell \n"
                                 "      them..."),
                            6);
                break;
            case 57:
                write_quote(PSTR(" 'Your soul is of a \n"
                                 "pure white, Verin,' \n"
                                 "Egwene said softly. \n"
                                 "  'Like the Light   \n"
                                 "      itself.'"),
                            5);
                break;
            case 58:
                write_quote(PSTR("  Asha'man, Kill!"), 1);
                break;
            case 59:
                write_quote(PSTR("  Let the lord of   \n"
                                 "    chaos rule."),
                            2);
                break;
            case 60:
                write_quote(PSTR("   There's always   \n"
                                 "  another secret."),
                            2);
                break;
            case 61:
                write_quote(PSTR(" You see the great  \n"
                                 "thing about madness \n"
                                 "is that it's all in \n"
                                 "     your head."),
                            4);
                break;
            case 62:
                write_quote(PSTR(" In one Age, called \n"
                                 "  the Third Age by  \n"
                                 "some, an Age yet to \n"
                                 " come, an Age long  \n"
                                 " past, a wind rose  \n"
                                 "      above..."),
                            6);
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
