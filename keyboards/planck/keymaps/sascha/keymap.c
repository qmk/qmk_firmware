#include "backlight.h"
#include "planck.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = {
        /* ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
         * │ Esc  │   Q  │   W  │   E  │   R  │   T  │   Z  │   U  │   I  │   O  │   P  │ Bksp │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Tab  │   A  │   S  │   D  │   F  │   G  │   H  │   J  │   K  │   L  │ ;  : │ Entr │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Shft │   Y  │   X  │   C  │   V  │   B  │   N  │   M  │ ,  < │ .  > │ /  ? │ '  " │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Ctrl │ Alt  │ GUI  │ -  _ │ =  + │ Spce │ \  | │   (  │   )  │ [  { │ ]  } │ Lr 1 │
         * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
         */
        { KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R   , KC_T   , KC_Z    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC  } ,
        { KC_TAB  , KC_A    , KC_S    , KC_D    , KC_F   , KC_G   , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_ENT   } ,
        { KC_LSFT , KC_Y    , KC_X    , KC_C    , KC_V   , KC_B   , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_QUOT  } ,
        { KC_LCTL , KC_LALT , KC_LGUI , KC_MINS , KC_EQL , KC_SPC , KC_BSLS , KC_LPRN , KC_RPRN , KC_LBRC , KC_RBRC , MO(1)    }
    },
[1] = {
        /* ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
         * │   ~  │   1  │   2  │   3  │   4  │   5  │   6  │   7  │   8  │   9  │   0  │ DEL  │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │   `  │   !  │   @  │   #  │   $  │   %  │   ^  │   &  │   *  │   ü  │   ö  │   ä  │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Caps │ Home │ End  │ PgUp │ PgDn │ INS  │  F1  │   ß  │ Left │ Down │  Up  │ Rght │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Powr │ Rset │ VoUp │ VoDn │ BLTg │ BLSt │ BLBr │ Shft │ Alt  │ Ctrl │ GUI  │      │
         * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
         */
        { KC_TILD , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7     , KC_8    , KC_9     , KC_0     , KC_DEL   } ,
        { KC_GRV  , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR  , KC_ASTR , UC(L'ü') , UC(L'ö') , UC(L'ä') } ,
        { KC_CAPS , KC_HOME , KC_END  , KC_PGUP , KC_PGDN , KC_INS  , KC_F1   , UC(L'ß') , KC_LEFT , KC_DOWN  , KC_UP    , KC_RGHT  } ,
        { KC_PWR  , RESET   , KC_VOLU , KC_VOLD , BL_TOGG , BL_STEP , BL_BRTG , KC_RSFT  , KC_RALT , KC_RCTL  , KC_RGUI  , KC_TRNS  }
    }
};

void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX);
};
