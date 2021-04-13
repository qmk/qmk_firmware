#include "keymap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   KC_APP,  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [_RGB_VOL] = LAYOUT( /* RGB and Volume controls */
         TO(2) , TO(3)  , XXXXXXX, XXXXXXX, XXXXXXX, DM_REC1, DM_PLY1, DM_REC2, DM_PLY2, DM_RSTP, XXXXXXX, XXXXXXX, XXXXXXX,            KC_MPRV, KC_MPLY, KC_MNXT, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_MUTE, XXXXXXX, KC_VOLU, \
        BL_BRTG, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, XXXXXXX, U_T_AUTO,U_T_AGCR,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, KC_VOLD, \
        XXXXXXX, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX \
    ),
    [_NUMPAD] = LAYOUT( /* My Numpad layer (And FW flashing button in case of emergency) */
         TO(0) , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_0  ,              KC_1 ,   KC_2 ,   KC_3 , \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,     KC_4 ,   KC_5 ,   KC_6 , \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,     KC_7 ,   KC_8 ,   KC_9 , \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX,                              KC_NLCK, \
        MD_BOOT, XXXXXXX, XXXXXXX,                   XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            KC_LEFT, XXXXXXX, KC_RGHT \
    ),
    [_CODE] = LAYOUT( /* VSCode shortcuts*/
         TO(0) , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  GREMTE, CLS_FDR, XXXXXXX, XXXXXXX, XXXXXXX, \
        OPN_FLD, XXXXXXX, XXXXXXX, EXTNSH ,  GRESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  GCHECK, MDPrev , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  GFETCH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   GLOG , XXXXXXX, XXXXXXX, XXXXXXX, \
        STTNGS , XXXXXXX, XXXXXXX,  GCLONE, XXXXXXX,  GBRANH, XXXXXXX,  GMERGE, XXXXXXX, XXXXXXX,  SD_BR , XXXXXXX,                            GPUSH, \
        XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, GPULL, XXXXXXX \
    )
};

#define RED {HSV_RED}
#define VSCODE {148,255,255}
#define GIT {19,255,255}
#define NOCLR {0,0,0}
#define PSSTHR {1,1,1}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_MAIN] = {
         PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,             PSSTHR,  PSSTHR,  PSSTHR,
         PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,    PSSTHR,  PSSTHR,  PSSTHR,
         PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,    PSSTHR,  PSSTHR,  PSSTHR,
         PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,
         PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,                               PSSTHR,
         PSSTHR,  PSSTHR,  PSSTHR,                    PSSTHR,                             PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,             PSSTHR,  PSSTHR,  PSSTHR,
    },
    [_RGB_VOL] = {
         PSSTHR,  PSSTHR,  NOCLR ,  NOCLR ,  NOCLR ,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  NOCLR ,  NOCLR ,  NOCLR ,           PSSTHR,  PSSTHR,  PSSTHR,
         NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  PSSTHR,  NOCLR ,  PSSTHR,
         NOCLR ,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  PSSTHR,
         NOCLR ,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,
         NOCLR ,  NOCLR ,  PSSTHR,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,                             NOCLR ,
         NOCLR ,  NOCLR ,  NOCLR ,                    NOCLR ,                             NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,           NOCLR ,  NOCLR ,  NOCLR ,
    },
    [_NUMPAD] = {
         PSSTHR,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  PSSTHR,           PSSTHR,  PSSTHR,  PSSTHR,
         NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,  PSSTHR,
         NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  PSSTHR,  PSSTHR,  PSSTHR,
         NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  PSSTHR,
         NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  PSSTHR,  PSSTHR,  NOCLR ,  NOCLR ,                             PSSTHR,
          RED  ,  NOCLR ,  NOCLR ,                    NOCLR ,                             NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,           PSSTHR,  PSSTHR,  PSSTHR,
    },
    [_CODE] = {
         PSSTHR,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,           NOCLR,  NOCLR,  NOCLR,
         NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,   GIT  ,  VSCODE,  NOCLR,  NOCLR,  NOCLR,
         VSCODE,  NOCLR ,  NOCLR ,  VSCODE,   GIT  ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,   GIT  ,  VSCODE,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR,  NOCLR,  NOCLR,
         NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,   GIT  ,  NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,   GIT  ,  NOCLR ,  NOCLR ,  NOCLR,
         VSCODE,  NOCLR ,  NOCLR ,   GIT  ,  NOCLR ,   GIT  ,  NOCLR ,   GIT  ,  NOCLR ,  NOCLR ,  VSCODE,  NOCLR ,                             GIT ,
         NOCLR ,  NOCLR ,  NOCLR ,                    NOCLR ,                             NOCLR ,  NOCLR ,  NOCLR ,  NOCLR ,           NOCLR,   GIT ,  NOCLR,
    },
};

void set_layer_color(int layer) {
    if (layer == 0) { return; }
    for (int i = 0; i < DRIVER_LED_TOTAL; i++)
    {
        HSV hsv = {
            .h = ledmap[layer][i][0],
            .s = ledmap[layer][i][1],
            .v = ledmap[layer][i][2],
        };
        if ((ledmap[layer][i][0] == 1) && (ledmap[layer][i][1] == 1) && (ledmap[layer][i][2] == 1)){}
        else{
            RGB rgb = hsv_to_rgb(hsv);
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        }
    }
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // Enable or disable debugging
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    debug_mouse=true;
};

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    set_layer_color(get_highest_layer(layer_state));
};

static const char* cmd_strings[] = {
    "git clone ",
    "git reset ",
    "git rebase ",
    "git branch -b \"",
    "git checkout ",
    "git merge ",
    "git remote add ",
    "git fetch ",
    "git pull ",
    "git push ",
    "git log ",
};


#define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT    (get_mods() & MOD_MASK_ALT)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        case MDPrev:
        if (record->event.pressed)
        {
            SEND_STRING(SS_LCTL("kv"));
        }
        return false;
        case OPN_FLD:
        if (record->event.pressed)
        {
            SEND_STRING(SS_LCTL("ko"));
        }
        return false;
        case STTNGS:
        if (record->event.pressed)
        {
            SEND_STRING(SS_LCTL(","));
        }
        return false;
        case EXTNSH:
        if (record->event.pressed)
        {
            SEND_STRING(SS_LCTL(SS_LSFT("x")));
        }
        return false;
        case SD_BR:
        if (record->event.pressed)
        {
            SEND_STRING(SS_LCTL("b"));
        }
        return false;
        case CLS_FDR:
        if (record->event.pressed)
        {
            SEND_STRING(SS_LCTL("w"));
        }
        return false;
        case GCLONE ... GLOG:
        if (record->event.pressed)
        {
            send_string_with_delay(cmd_strings[keycode - GCLONE], 5);
            return false;
        }
        default:
            return true; //Process all other keycodes normally
    }
}
