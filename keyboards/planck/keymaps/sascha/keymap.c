#include "backlight.h"
#include "planck.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = {
        /* ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
         * │ Esc  │   Q  │   W  │   E  │   R  │   T  │   Y  │   U  │   I  │   O  │   P  │ Bksp │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Ctrl │   A  │   S  │   D  │   F  │   G  │   H  │   J  │   K  │   L  │ ;  : │ Entr │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Shft │   Z  │   X  │   C  │   V  │   B  │   N  │   M  │ ,  < │ .  > │ /  ? │ '  " │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Alt  │ GUI  │ \  | │ -  _ │ =  + │ Spce │ Spce │   (  │   )  │ [  { │ ]  } │ Lr 1 │
         * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
         */
        { KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R   , KC_T     , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC  } ,
        { KC_LCTL , KC_A    , KC_S    , KC_D    , KC_F   , KC_G     , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_ENT   } ,
        { KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V   , KC_B     , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_QUOT  } ,
        { KC_LALT , KC_LGUI , KC_BSLS , KC_MINS , KC_EQL , KC_SPC   , KC_SPC  , KC_LPRN , KC_RPRN , KC_LBRC , KC_RBRC , MO(1)    }
    },
[1] = {
        /* ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
         * │   ~  │   1  │   2  │   3  │   4  │   5  │   6  │   7  │   8  │   9  │   0  │ DEL  │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │   `  │   !  │   @  │   #  │   $  │   %  │   *  │   &  │ BL+  │ BL-  │ BLTg │ BLBr │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Caps │ Home │ End  │ PgUp │ PgDn │  F1  │  F2  │  F3  │ Left │ Down │  Up  │ Rght │
         * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
         * │ Powr │ Rset │ VoUp │ VoDn │ Play │ Stop │ Prev │ Next │ Alt  │ Ctrl │ GUI  │      │
         * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
         */
        { KC_TILD , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0     , KC_DEL  } ,
        { KC_GRV  , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , BL_INC  , BL_DEC  , BL_TOGG  , BL_BRTG } ,
        { KC_CAPS , KC_HOME , KC_END  , KC_PGUP , KC_PGDN , KC_F1   , KC_F2   , KC_F3   , KC_LEFT , KC_DOWN , KC_UP    , KC_RGHT } ,
        { KC_PWR  , RESET   , KC_VOLU , KC_VOLD , KC_MPLY , KC_MSTP , KC_MPRV , KC_MNXT , KC_RALT , KC_RCTL , KC_RGUI  , KC_TRNS }
    }
};
