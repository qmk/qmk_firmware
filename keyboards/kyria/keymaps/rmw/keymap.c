/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "tapdances.cpp"

#define _______ KC_TRNS
#define SFTENT SFT_T(KC_ENT)

enum layers {
    QWERTY = 0
   ,NUMPAD 
   ,EDIT 
   ,FSYM 
   ,JSYM 
   ,MEDIA 
   ,MINIMAK4 // does this work up here? or does it need to be lower?
   ,ADJUST 
};

// Tap Dance enum
enum {
 SHCAP = 0
 ,TDGUI
 ,SHENT
 ,SHNTC
 ,FRBK
 ,FRBK2
 ,UMOD
 ,UMOD2
 ,GCA 
 ,AGC 
 ,SGCA
 ,CTLALL 
 ,GUCTL 
 ,CTLAND
};

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE
  ,OS_GSFT = OSM(MOD_LSFT | MOD_LGUI)
  ,OS_CALT = OSM(MOD_LCTL | MOD_LALT)
  ,OS_ALT  = OSM(MOD_LALT)
  ,OS_CTL  = OSM(MOD_LCTL)
  ,OS_CMD  = OSM(MOD_LGUI)
  ,R_UNDO = LGUI(KC_Z)
  ,R_REDO = LGUI(KC_Y)
  ,R_CUT = LGUI(KC_X)
  ,R_COPY = LGUI(KC_C)
  ,R_PASTE = LGUI(KC_V)
  ,DEL_WRD = LALT(KC_BSPACE)
  ,MVW_LEFT = LALT(KC_LEFT) 
  ,MVW_RIGHT = LALT(KC_RIGHT)
  ,SELW_LEFT = LALT(S(KC_LEFT))
  ,SELW_RIGHT = LALT(S(KC_RIGHT))
  ,NEW_TAB = LGUI(KC_T)
  ,TASK_MAN = LGUI(LALT(KC_ESCAPE))
  ,SEL_HOME = S(LGUI(KC_LEFT))
  ,SEL_END = S(LGUI(KC_RIGHT))
  ,R_HOME = LGUI(KC_LEFT)
  ,R_END = LGUI(KC_RIGHT)
  ,FORM_GET
  ,FORM_PUT
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [SHCAP]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps, shift_reset)
   ,[TDGUI]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftgui, gui_reset)
   ,[SHENT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftenter, shift_reset)
   ,[SHNTC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftentercaps, shift_reset)
   ,[FRBK]   = ACTION_TAP_DANCE_DOUBLE(KC_WWW_BACK,KC_WWW_FORWARD)
   ,[FRBK2]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, forward_back_mac, ubermod_reset)
   ,[GCA]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ubermod_mac, ubermod_reset) // GUI->CTL->ALT
   ,[AGC]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ubermod2_mac, ubermod_reset) // ALT->GUI->CTL
   ,[SGCA]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_and_mac, CASG_reset) // SG->SC->SA
   ,[CTLALL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_all_mac, ubermod_reset) // C->CG->CA->CAG
   ,[GUCTL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guictl, ubermod_reset) 
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*  [QWERTY] = LAYOUT(
    KC_TAB   , KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                                          KC_Y,    KC_U,       KC_I, KC_O,      KC_P,        KC_BSLS,
    OSL(EDIT), KC_A, LT(NUMPAD,KC_S), KC_D, LT(FSYM,KC_F), KC_G,                                              KC_H, LT(JSYM,KC_J), KC_K, KC_L, LT(EDIT,KC_SCLN), KC_QUOT,
    TD(FRBK2)  , KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,  TO(EDIT), KC_ESCAPE,         KC_DEL, TO(NUMPAD),  KC_N, KC_M,     KC_COMM, KC_DOT, LT(MEDIA,KC_SLSH), KC_MS_BTN1,
                           TO(ADJUST), TD(SGCA), TD(AGC), KC_BSPACE, TD(SHNTC),          SFTENT,  KC_SPC,   TD(GCA), TD(CTLALL), KC_CAPS
    ),*/
  [QWERTY] = LAYOUT_STACK(
    KC_TAB   , KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                             
    OSL(EDIT), KC_A, LT(NUMPAD,KC_S), KC_D, LT(FSYM,KC_F), KC_G,                 
    TD(FRBK2)  , KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,  TO(EDIT), KC_ESCAPE,     
                           TO(ADJUST), TD(SGCA), TD(AGC), KC_BSPACE, TD(SHNTC),  

                               KC_Y,    KC_U,       KC_I, KC_O,      KC_P,        KC_BSLS,
                               KC_H, LT(JSYM,KC_J), KC_K, KC_L, LT(EDIT,KC_SCLN), KC_QUOT,
          KC_DEL, TO(NUMPAD),  KC_N, KC_M,     KC_COMM, KC_DOT, LT(MEDIA,KC_SLSH), KC_MS_BTN1,
          SFTENT,  KC_SPC,   TD(GCA), TD(CTLALL), KC_CAPS
    ),

  [NUMPAD] = LAYOUT(
    _______, _______, _______,  _______, _______,  _______,                                            _______, KC_7,  KC_8,  KC_9, KC_KP_MINUS, _______,
    _______, _______, _______,  _______, _______, _______,                                             _______, KC_4,  KC_5,  KC_6, KC_KP_PLUS , _______, 
    _______, _______, _______,  _______, _______,  _______, TO(QWERTY), _______,    _______, TO(EDIT), _______, KC_1,  KC_2,  KC_3, KC_KP_SLASH, _______,
                                 _______, _______, _______, _______, _______,       _______,  _______, KC_0, KC_DOT, _______
    ),

  [EDIT] = LAYOUT(
    _______, TASK_MAN, _______, SELW_LEFT, SELW_RIGHT, _______,                                                NEW_TAB , KC_PGUP, KC_UP, KC_PGDOWN, KC_PSCREEN, _______, 
    _______, _______ , LGUI(KC_GRV), MVW_LEFT,  MVW_RIGHT , _______,                                                R_HOME  , KC_LEFT, KC_DOWN, KC_RIGHT, R_END, _______, 
    _______, R_UNDO, R_CUT  , R_COPY , R_PASTE, R_REDO ,      TO(NUMPAD), FORM_GET,      FORM_PUT, TO(QWERTY), SEL_HOME, S(KC_LEFT), S(KC_DOWN), S(KC_RIGHT), SEL_END, _______, 
                                       _______, _______, _______, DEL_WRD, _______,       _______, _______, _______, _______, _______
    ),

  [ADJUST] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,                                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, 
    TO(QWERTY), TO(EDIT), TO(NUMPAD), TO(JSYM), TO(FSYM), TO(MEDIA),                                   _______, _______, _______, _______, _______,  _______,
    DF(MINIMAK4), DF(QWERTY), RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
    ),

  [FSYM] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                                                KC_CIRC,  KC_AMPR , KC_ASTR, KC_GRV ,  _______, _______, 
    _______, _______, KC_TILD, KC_EXLM, _______, _______,                                                KC_EQUAL, KC_MINUS, KC_UNDS, KC_PIPE, KC_COLON, KC_DQT,
    _______, _______, TO(QWERTY), _______, _______, _______, _______, _______,         _______, _______, _______, KC_PLUS,  KC_BSLS, KC_SLSH, _______, _______, 
                               _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______ 
    ), 
    
  [JSYM] = LAYOUT(
    _______, KC_GRV,  KC_AT  , KC_LCBR,     KC_RCBR,     _______,                                             _______, _______, _______, _______,  _______, _______, 
    _______, KC_HASH, KC_DLR , KC_LPRN,     KC_RPRN,     KC_LEFT,                                             _______, _______, KC_QUES, KC_SLSH, KC_COLON, _______,
    _______, KC_PERC, KC_CIRC, KC_LBRACKET, KC_RBRACKET, _______, _______, _______,         _______, _______, _______, _______, _______, TO(QWERTY), _______, _______, 
                                       _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______
    ), 
    
  [MEDIA] = LAYOUT(
    _______, KC_MS_WH_UP, KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, _______,                                            _______, _______, _______, _______,  _______, _______, 
    _______, KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______,                                              _______, _______, _______, _______, _______, _______,
    _______, _______, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, _______, _______, _______,         _______, _______, _______, _______, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, _______,
                                              _______, _______, _______, _______, _______,         KC_MS_BTN1, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_REWIND, KC_MEDIA_FAST_FORWARD, KC_AUDIO_MUTE 
  ),

  [MINIMAK4] = LAYOUT(
    KC_TAB   , KC_Q,   KC_W,   KC_D,   KC_R,   KC_K,                                                              KC_Y,    KC_U,       KC_I, KC_O,      KC_P,        KC_PIPE,
    OSL(EDIT), KC_A, LT(NUMPAD,KC_S), KC_T, LT(FSYM,KC_F), KC_G,                                                  KC_H, LT(JSYM,KC_J), KC_E, KC_L, LT(EDIT,KC_SCLN), KC_QUOT,
    OSM(MOD_LSFT)  , KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,  TO(EDIT), KC_ESCAPE,            KC_DEL, TO(NUMPAD),   KC_N, KC_M,     KC_COMM, KC_DOT, LT(MEDIA,KC_SLSH), KC_MINS,
                           _______, TO(ADJUST), TD(SGCA), KC_BSPACE, TD(SHNTC),          SFTENT,  KC_SPC,   TD(GCA), TD(CTLALL), _______
    )
};
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     )

//layer_state_t layer_state_set_user(layer_state_t state) {
//    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
//}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

/*static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}
*/
static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
/*    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }
*/
    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
//        render_kyria_logo();
    }
}
#endif


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case EDIT:
                // Move whole words. Hold shift to select while moving.
                if (clockwise) {
                    tap_code16(C(KC_RGHT));
                } else {
                    tap_code16(C(KC_LEFT));
                }
                break;
            //case QWERTY:
            default:
                // History scrubbing. For Adobe products, hold shift while moving
                // backward to go forward instead.
                if (clockwise) {
                    tap_code16(C(KC_Z));
                } else {
                    tap_code16(C(KC_Y));
                }
                break;
        }
    } else if (index == 1) {
        switch (biton32(layer_state)) {
            case QWERTY:
                // Scrolling with PageUp and PgDn.
                if (clockwise) {
                    tap_code(KC_MS_WH_DOWN);
                } else {
                    tap_code(KC_MS_WH_UP);
                }
                break;
            default:
                // Volume control.
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
}
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FORM_GET:
      if (record->event.pressed) {
        //click KC_MS_BTN1
        //register_code16(KC_BTN1);
        //unregister_code16(KC_BTN1);
        tap_code16(KC_MS_BTN1);
        SEND_STRING(SS_LGUI("a"));
        SEND_STRING(SS_LGUI("c"));
      }
      return false;
      break;
    case FORM_PUT:
      if (record->event.pressed) {
        tap_code16(KC_MS_BTN1);
        SEND_STRING(SS_LGUI("a"));
        SEND_STRING(SS_LGUI("v"));
      }
      return false;
      break;
  }
  return true;
}
