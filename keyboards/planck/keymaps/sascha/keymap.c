#include "backlight.h"
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_planck_grid(
        /* ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
         * │ Esc  │   Q  │   W  │   E  │   R  │   T  │   Z  │   U  │   I  │   O  │   P  │ Bksp │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Tab  │   A  │   S  │   D  │   F  │   G  │   H  │   J  │   K  │   L  │ ;  : │ Entr │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Shft │   Y  │   X  │   C  │   V  │   B  │   N  │   M  │ ,  < │ .  > │ /  ? │ '  " │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Ctrl │ Alt  │ `  ~ │ -  _ │ =  + │ Spce │ \  | │   (  │   )  │ [  { │ ]  } │ Lr 1 │
         * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
         */
        KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R   , KC_T   , KC_Z    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC,
        KC_TAB  , KC_A    , KC_S    , KC_D    , KC_F   , KC_G   , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_ENT,
        KC_LSFT , KC_Y    , KC_X    , KC_C    , KC_V   , KC_B   , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_QUOT,
        KC_LCTL , KC_LALT , KC_GRV  , KC_MINS , KC_EQL , KC_SPC , KC_BSLS , KC_LPRN , KC_RPRN , KC_LBRC , KC_RBRC , MO(1)
    ),
[1] = LAYOUT_planck_grid(
        /* ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
         * │   ~  │   1  │   2  │   3  │   4  │   5  │   6  │   7  │   8  │   9  │   0  │ DEL  │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │   `  │   !  │   @  │   #  │   $  │   %  │   ^  │   &  │   *  │   ü  │   ö  │   ä  │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ SINS │   …  │   ’  │   “  │   ”  │   ←  │   →  │   €  │   ß  │   Ü  │   Ö  │   Ä  │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Rset │ BLSt │  F1  │ Home │ End  │ PgUp │ PgDn │ Left │ Down │  Up  │ Rght │      │
         * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
         */
        KC_TILD   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5      , KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_DEL,
        KC_GRV    , KC_EXLM  , KC_AT    , KC_HASH  , KC_DLR   , KC_PERC   , KC_CIRC  , KC_AMPR  , KC_ASTR  , UC(L'ü') , UC(L'ö') , UC(L'ä'),
        S(KC_INS) , UC(L'…') , UC(L'’') , UC(L'“') , UC(L'”') , UC(L'←')  , UC(L'→') , UC(L'€') , UC(L'ß') , UC(L'Ü') , UC(L'Ö') , UC(L'Ä'),
        RESET     , BL_STEP  , KC_F1    , KC_HOME  , KC_END   , KC_PGUP   , KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_TRNS
    )
};

void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX);
};
