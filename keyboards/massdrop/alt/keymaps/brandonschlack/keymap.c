#include QMK_KEYBOARD_H
#include "brandonschlack.h"

enum alt_keycodes {
    L_BRI = KEYMAP_SAFE_RANGE, //LED Brightness Increase                                   //Working
    L_BRD,                     //LED Brightness Decrease                                   //Working
    L_PTN,                     //LED Pattern Select Next                                   //Working
    L_PTP,                     //LED Pattern Select Previous                               //Working
    L_PSI,                     //LED Pattern Speed Increase                                //Working
    L_PSD,                     //LED Pattern Speed Decrease                                //Working
    L_T_MD,                    //LED Toggle Mode                                           //Working
    L_T_ONF,                   //LED Toggle On / Off                                       //Broken
    L_ON,                      //LED On                                                    //Broken
    L_OFF,                     //LED Off                                                   //Broken
    L_T_BR,                    //LED Toggle Breath Effect                                  //Working
    L_T_PTD,                   //LED Toggle Scrolling Pattern Direction                    //Working
    U_T_AGCR,                  //USB Toggle Automatic GCR control                          //Working
    DBG_TOG,                   //DEBUG Toggle On / Off                                     //
    DBG_MTRX,                  //DEBUG Toggle Matrix Prints                                //
    DBG_KBD,                   //DEBUG Toggle Keyboard Prints                              //
    DBG_MOU,                   //DEBUG Toggle Mouse Prints                                 //
    MD_BOOT                    //Restart into bootloader after hold timeout                //Working
};

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /***********
     *  MacOS  *
     ***********/
    /* Base Layer: Mac
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Backs|Del|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Hom|
     * |---------------------------------------------------------------|
     * |HyCap |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |PgU|
     * |---------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Ctl |Alt |Gui |         Space         |Gui |FnPy|  |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [LB_MAC] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        HY_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MM_FN_M, KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    /* Function Layer: Mac
     * ,---------------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|    Del|SLP|
     * |---------------------------------------------------------------|
     * |     |   |   |   |DFU|   |   |   |   |   |F13|F14|F15|  LHP|End|
     * |---------------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   | TgMagic|BrU|
     * |---------------------------------------------------------------|
     * |        |LTM|   |   |   |   |   |MKE|   |   |   |MutSft|VlU|BrD|
     * |---------------------------------------------------------------|
     * |    |    |    |                       |    |    |  |Prv|VlD|Nxt|
     * `---------------------------------------------------------------'
     */
    [LF_MAC] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  MC_SLPD, \
        _______, _______, _______, _______, MD_BOOT, _______, _______, _______, _______, _______, KC_F13,  KC_F14,  KC_F15,  MC_LHPD, KC_END,  \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TG_MAGC, KC_BRMU, \
        _______, L_T_MD,  _______, _______, _______, _______, _______, MD_MAKE, _______, _______, _______, MM_RSFT,          KC_VOLU, KC_BRMD, \
        _______, _______, _______,                            _______,                            _______, _______, KC_MRWD, KC_VOLD, KC_MFFD  \
    ),

    /***********
     * Windows *
     ***********/
    /* Base Layer: Windows
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Backs|Del|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Hom|
     * |---------------------------------------------------------------|
     * |HyCap |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |PgU|
     * |---------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Ctl |Alt |Gui |         Space         |Gui |FnPy|  |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [LB_WIN] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        HY_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MM_FN_W, KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    /* Function Layer: Windows
     * ,---------------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|    Del|LCK|
     * |---------------------------------------------------------------|
     * |     |   |   |   |DFU|   |   |   |   |   |PtS|SLk|Pau|  TSK|End|
     * |---------------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   | TgMagic|BrU|
     * |---------------------------------------------------------------|
     * |        |LTM|   |   |   |   |   |MKE|   |   |   |MutSft|VlU|BrD|
     * |---------------------------------------------------------------|
     * |    |    |    |                       |    |    |  |Prv|VlD|Nxt|
     * `---------------------------------------------------------------'
     */
    [LF_WIN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  WN_LOCK, \
        _______, _______, _______, _______, MD_BOOT, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, WN_TSKM, KC_END,  \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TG_MAGC, KC_BRIU, \
        _______, L_T_MD,  _______, _______, _______, _______, _______, MD_MAKE, _______, _______, _______, MM_RSFT,          KC_VOLU, KC_BRID, \
        _______, _______, _______,                            _______,                            _______, _______, KC_MPRV, KC_VOLD, KC_MNXT  \
    ),

    /***********
     *  Magic  *
     ***********/
    /* Keyboard Layer: Magic
     * ,---------------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |   |
     * |---------------------------------------------------------------|
     * |LBr  |LS-|LB+|LS+|   |   |   |   |GCR|   |   |   |   |     |   |
     * |---------------------------------------------------------------|
     * |LPD   |LP-|LB-|LP+|   |   |   |   |   |   |   |   | TgMagic|   |
     * |---------------------------------------------------------------|
     * |        |LTM|LTO|   |   |   |KRO|   |Mac|Win|   |      |   |   |
     * |---------------------------------------------------------------|
     * |    |    |    |                       |    |    |  |   |   |   |
     * `---------------------------------------------------------------'
     */
    [LK_MGC] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        L_T_BR,  L_PSD,   L_BRI,   L_PSI,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, U_T_AGCR,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        L_T_PTD, L_PTP,   L_BRD,   L_PTN,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          TG_MAGC, XXXXXXX, \
        XXXXXXX, L_T_MD,  L_T_ONF, XXXXXXX, XXXXXXX, XXXXXXX, TG_NKRO, XXXXXXX, OS_MAC,  OS_WIN,  XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    led_lighting_mode = LED_MODE_INDICATORS_ONLY;
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case L_BRI:
            if (record->event.pressed) {
                if (LED_GCR_STEP > LED_GCR_MAX - gcr_desired) gcr_desired = LED_GCR_MAX;
                else gcr_desired += LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_BRD:
            if (record->event.pressed) {
                if (LED_GCR_STEP > gcr_desired) gcr_desired = 0;
                else gcr_desired -= LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_PTN:
            if (record->event.pressed) {
                if (led_animation_id == led_setups_count - 1) led_animation_id = 0;
                else led_animation_id++;
            }
            return false;
        case L_PTP:
            if (record->event.pressed) {
                if (led_animation_id == 0) led_animation_id = led_setups_count - 1;
                else led_animation_id--;
            }
            return false;
        case L_PSI:
            if (record->event.pressed) {
                led_animation_speed += ANIMATION_SPEED_STEP;
            }
            return false;
        case L_PSD:
            if (record->event.pressed) {
                led_animation_speed -= ANIMATION_SPEED_STEP;
                if (led_animation_speed < 0) led_animation_speed = 0;
            }
            return false;
        case L_T_MD:
            if (record->event.pressed) {
                led_lighting_mode++;
                if (led_lighting_mode > LED_MODE_MAX_INDEX) led_lighting_mode = LED_MODE_NORMAL;
            }
            return false;
        case L_T_ONF:
            if (record->event.pressed) {
                led_enabled = !led_enabled;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_ON:
            if (record->event.pressed) {
                led_enabled = 1;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_OFF:
            if (record->event.pressed) {
                led_enabled = 0;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_T_BR:
            if (record->event.pressed) {
                led_animation_breathing = !led_animation_breathing;
                if (led_animation_breathing) {
                    gcr_breathe = gcr_desired;
                    led_animation_breathe_cur = BREATHE_MIN_STEP;
                    breathe_dir = 1;
                }
            }
            return false;
        case L_T_PTD:
            if (record->event.pressed) {
                led_animation_direction = !led_animation_direction;
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
        default:
            return true; //Process all other keycodes normally
    }
}

led_instruction_t led_instructions[] = {
    //Please see ../default_md/keymap.c for examples

    //All LEDs use the user's selected pattern (this is the factory default)
    //  { .flags = LED_FLAG_USE_ROTATE_PATTERN },

    // MiTo Laser Lighting
    // On Base Layer, all LEDs use purple
    // On Function Layer, all LEDS use pink
    // On Function Layer, all LEDS use white
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, .id0 = 0xFFFFFFFF, .id1 = 0xFFFFFFFF, .id2 = 0xFFFFFFFF, .id3 = 0x000003FF, .r = 60, .g = 22, .b = 140, .layer = LB_MAC },
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, .id0 = 0xFFFFFFFF, .id1 = 0xFFFFFFFF, .id2 = 0xFFFFFFFF, .id3 = 0x000003FF, .r = 242, .g = 27, .b = 127, .layer = LF_MAC },
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, .id0 = 0xFFFFFFFF, .id1 = 0xFFFFFFFF, .id2 = 0xFFFFFFFF, .id3 = 0x000003FF, .r = 35, .g = 27, .b = 89, .layer = LB_WIN },
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, .id0 = 0xFFFFFFFF, .id1 = 0xFFFFFFFF, .id2 = 0xFFFFFFFF, .id3 = 0x000003FF, .r = 47, .g = 193, .b = 225, .layer = LF_WIN },
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, .id0 = 0xFFFFFFFF, .id1 = 0xFFFFFFFF, .id2 = 0xFFFFFFFF, .id3 = 0x000003FF, .r = 255, .g = 255, .b = 255, .layer = LK_MGC },

    //end must be set to 1 to indicate end of instruction set
     { .end = 1 }
};
