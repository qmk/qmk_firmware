/* Copyright 2022 bojiguard (@bojiguard)
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


enum layer_names {
		SAM1,
		SAM2,
		SAM3,
		SAM4
};





#define SFCTLNO MT(MOD_LCTL|MOD_LSFT,KC_NO) 

#define SFCT_S  MT(MOD_LCTL|MOD_LSFT,KC_S)
#define CT_D    MT(MOD_LCTL,KC_D)
#define SF_F    MT(MOD_LSFT,KC_F)

#define SF_J    MT(MOD_RSFT,KC_J)
#define CT_K    MT(MOD_RCTL,KC_K)

#define MTC_F7   MT(MOD_LCTL|MOD_LSFT, KC_F7)
#define MTC_F8   MT(MOD_LCTL, KC_F8)      
#define MTC_F9   MT(MOD_LSFT, KC_F9)

#define MTC_K   MT(MOD_RCTL, KC_K)      
#define MTC_J   MT(MOD_RSFT, KC_J)

#define MTC_8   MT(MOD_RCTL, KC_8)      
#define MTC_7   MT(MOD_RSFT, KC_7)

//#define MTLC_8   MT(MOD_LCTL, KC_8)      
#define MTLC_9   MT(MOD_LSFT, KC_9)

#define LSFT_CAPS    MT(MOD_LSFT,KC_CAPS)
#define RSFT_CAPS    MT(MOD_RSFT,KC_CAPS)
#define LT2SPC    LT(SAM2, KC_SPC)
#define LT3SPC    LT(SAM3, KC_SPC)
#define LGUSPC    MT(MOD_LGUI, KC_SPC)
#define RGUSPC    MT(MOD_RGUI, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE
   * ,------------------------------------------------.                                ,------------------------------------------------.
   * |   ~  |   1  |   2  |   3  |   4  |   5  | ESC  |                                |  BS  |   6  |   7  |   8  |   9  |   [  |   \  |
   * |------+------+------+------+------+------+------|                                |-------------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |  `   |                                |   \  |   Y  |   U  |   I  |   O  |   P  | Tab  |
   * |------+------+------+------+------+------+------|                                |-------------+------+------+------+------+------|
   * | ctrl |   A  |   S  |   D  |   F  |   G  |  [   |                                |  ]   |   H  |   J  |   K  |   L  |   ;  | ctrl |
   * |------+------+------+------+------+------+------|                                |------|------+------+------+------+------+------|
   * | shift|   Z  |   X  |   C  |   V  |  B   |  3   |  -     | 7     ||  1   |   2   |  =   |  4   |   N  |   M  |   ,  |   .  |shift |
   * |------+------+------+------+------+------+------|                                |------+------+------+------+------+------+------|
   * |  1   |  2   |   3  |  4   |     alt     | spc  |  MO(1) |enter  ||enter | MO(0) |  spc |     alt     |  1   |   2  |   3  |  4   |
   * `------------------------------------------------'                                ------------------------------------------------'
   */
/*
  [BASE] = LAYOUT(
    KC_GRV,     KC_1,     KC_2,    KC_3,    KC_4,     KC_5,    KC_ESC,                                                              KC_BSPC,  KC_6,  KC_7,   KC_8,    KC_9,    KC_0,    KC_NO,
    KC_TAB,     KC_Q,     KC_W,    KC_E,    KC_R,     KC_T,    KC_MINS,                                                             KC_EQL,   KC_Y,  KC_U,   KC_I,    KC_O,    KC_P,    KC_TAB,
    KC_NO,      KC_A,     SFCT_S,  CT_D,    SF_F,     KC_G,    KC_LBRC,                                                             KC_RBRC,  KC_H,  MTC_J,  MTC_K,   KC_L,    KC_SCLN, KC_NO,
    KC_LCTL,    KC_Z,     KC_X,    KC_C,    KC_V,     KC_B,    KC_BSLS,  LM(F3LAY, MOD_LSFT), KC_NO,   KC_NO,  LM(F3LAY, MOD_RSFT), KC_QUOT,  KC_N,  KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
    KC_NO,      TT(SAM1), KC_NO,   KC_LALT,    KC_LSHIFT,      KC_SPC,   MO(F3LAY),           KC_ENT,  KC_ENT, TT(F3LAY),           KC_SPC,     KC_RSHIFT,   KC_RALT, KC_NO,   TT(SAM1),TG(F4LAY)
  ),
*/
  /* BASE
   * ,------------------------------------------------.                                ,------------------------------------------------.
   * |   ~  |   1  |   2  |   3  |   4  |   5  | ESC  |                                |  BS  |   6  |   7  |   8  |   9  |   [  |   \  |
   * |------+------+------+------+------+------+------|                                |-------------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |  `   |                                | DEL  | HOME |  UP  | END  |   O  |   P  | Tab  |
   * |------+------+------+------+------+------+------|                                |-------------+------+------+------+------+------|
   * | ctrl |   A  |   S  |   D  |   F  |   G  |  [   |                                | INS  | LEFT | DOWN | RIGHT|   L  |   ;  | ctrl |
   * |------+------+------+------+------+------+------|                                |------|------+------+------+------+------+------|
   * | shift|   Z  |   X  | ctr+C|ctr+V |  B   |  3   |  -     | 7     ||  1   |   2   |  NO  | PGUP |  NO  | PGDN |   ,  |   .  |shift |
   * |------+------+------+------+------+------+------|                                |------+------+------+------+------+------+------|
   * |  1   |  2   |   3  |  4   |     alt     | spc  |  MO(1) |enter  ||enter | MO(0) |  spc |     alt     |  1   |   2  |   3  |  4   |
   * `------------------------------------------------'                                ------------------------------------------------'
   */
/*
  [F3LAY] = LAYOUT(
    KC_F11,     KC_F1,      KC_F2,       KC_F3,        KC_F4,        KC_F5,   KC_ESC,                                                              KC_BSPC, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F12,
    KC_TAB,     KC_1,       KC_2,        KC_3,         KC_4,         KC_5,    KC_CAPS,                                                             KC_CAPS, KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_TAB,
    KC_NO,      KC_NO,      SFCTLNO,     KC_LCTL,      KC_LSFT,      KC_PAUS, KC_PSCR,                                                             KC_BSPC, KC_DEL,  KC_HOME, KC_UP,   KC_END,   KC_PGUP, KC_NO,
    KC_LCTL,    LCTL(KC_Z), LCTL(KC_X),  LCTL(KC_C),   LCTL(KC_V),   KC_NO,   KC_NO,    LM(F3LAY, MOD_LSFT), KC_NO,   KC_NO,  LM(F3LAY, MOD_RSFT), KC_NO,   KC_INS,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_RCTL,
    KC_NO,      KC_NO,      KC_NO,       KC_LALT,           KC_LSHIFT,        KC_SPC,   MO(F3LAY),           KC_ENT,  KC_ENT, TT(F3LAY),           KC_SPC,     KC_RSHIFT,     KC_RALT, KC_NO,    KC_NO,   TG(F4LAY),
                                                                                                             KC_BTN2, KC_BTN1
  ),


  [F4LAY] = LAYOUT(
    KC_F11,     KC_F1,      KC_F2,       KC_F3,        KC_F4,        KC_F5,   KC_ESC,                                                              KC_BSPC, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F12,
    KC_TAB,     KC_NO,      KC_NO,       KC_NO,        KC_NO,        KC_NO,   KC_CAPS,                                                             KC_CAPS, KC_DEL,  KC_HOME, KC_UP,   KC_END,   KC_NO,   KC_TAB,
    KC_NO,      KC_NO,      SFCTLNO,     KC_LCTL,      KC_LSFT,      KC_PAUS, KC_PSCR,                                                             KC_BSPC, KC_INS,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO,   KC_NO,
    KC_LCTL,    LCTL(KC_Z), LCTL(KC_X),  LCTL(KC_C),   LCTL(KC_V),   KC_NO,   KC_NO,    LM(F3LAY, MOD_LSFT), KC_NO,   KC_NO,  LM(F3LAY, MOD_RSFT), KC_NO,   KC_INS,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_RCTL,
    KC_NO,      KC_NO,      KC_NO,       KC_LALT,           KC_LSHIFT,        KC_SPC,   MO(F3LAY),           KC_ENT,  KC_ENT, TT(F3LAY),           KC_SPC,     KC_RSHIFT,     KC_RALT, KC_NO,    KC_NO,   TG(F4LAY),
                                                                                                             KC_BTN2, KC_BTN1
  ),
*/
  
  /*
    [TEST] = LAYOUT(
    KC_GRV,     KC_1,   KC_2,    KC_3,    KC_4,     KC_5,    KC_ESC,                                                KC_BSPC,  KC_6,    KC_7,    KC_8,      KC_9,   KC_0,    KC_NO,
    KC_TAB,     KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,    KC_MINS,                                               KC_EQL,   KC_Y,    KC_U,    KC_I,      KC_O,   KC_P,    KC_TAB,
    KC_LSFT,    KC_A,   KC_S,    KC_D,    KC_F,     KC_G,    KC_LBRC,                                               KC_RBRC,  KC_H,    KC_J,    KC_K,      KC_L,   KC_SCLN, KC_RSFT,
    KC_LCTL,    KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    KC_BSLS,  KC_LCTL,        KC_NO,   KC_NO,  TG(F4LAY),  KC_QUOT,  KC_N,    KC_M,    KC_COMM,   KC_DOT, KC_SLSH, KC_RCTL,
    KC_NO,      KC_NO,  KC_NO,   KC_LALT,    KC_LSHIFT,      KC_SPC,   MO(F3LAY),      KC_ENT,  KC_ENT, TT(F3LAY),  KC_SPC,      KC_RSHIFT,     KC_RALT,   KC_NO,  KC_NO,   KC_NO,
                                                                                                             KC_BTN2, KC_BTN1
  ),
  */
  
  //--------------------------------------------------------NEW-----------------------------------------------
  //SAM1을 기반으로 새로운 모드
  // A(KC_LEFT) : BROWER BACKWARD, A(KC_RIGHT): BROWER FORWARD
  // KC_LANGUAGE_1 	KC_LNG1 	Hangul/English
  // KC_LANGUAGE_2 	KC_LNG2 	Hanja
  // 0번 레이어의 캡스락을 시프트키로 변경, 캡스락은 1번 오른쪽 레어어만 사용.  22.10.24
  // 왼쪽 컨트롤,시프트키 조합(에스 키)는 삭제함, 오타발생이 많아서 기능키가 작동됨. 22.10.27
  // RSFT_CAPS 추가
  // 언어변경후 클리어 콤보기능 추가 -> 왼쪽 컨트롤키 + 오른쪽 랭기지

    [SAM1] = LAYOUT(
    KC_NO,      KC_1,        A(KC_LEFT), KC_ENT,       LSFT_CAPS,    KC_BSPC, KC_ESC,                                                 KC_ESC,   KC_BSPC, RSFT_CAPS,   KC_ENT,    KC_LNG1,    KC_0,     KC_NO,
    KC_NO,      KC_Q,        KC_W,       KC_E,         KC_R,         KC_T,    KC_BSPC,                                                KC_BSPC,    KC_Y,  KC_U,   KC_I,    KC_O,    KC_P,     KC_NO,
    KC_TAB,     KC_A,        KC_S,       CT_D,         SF_F,         KC_G,    LSFT_CAPS,                                              RSFT_CAPS,  KC_H,  MTC_J,  MTC_K,   KC_L,    KC_SCLN,  KC_TAB,
    KC_LCTL,    KC_Z,        KC_X,       KC_C,         KC_V,         KC_B,    A(KC_LEFT),   TT(SAM3), TT(SAM4),  TT(SAM4), TT(SAM2),  KC_LNG1,    KC_N,  KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RCTL,
    KC_NO,      TT(SAM1),    KC_NO,      KC_LALT,             KC_SPC,         TT(SAM2),     KC_LCTL,  KC_LGUI,     KC_PSCR,    KC_RCTL,   TT(SAM3),     KC_SPC,      KC_RALT, KC_NO,   KC_8,     KC_9,
                                                                                                             KC_BTN1, KC_BTN2
  ),
  
    [SAM2] = LAYOUT(
    DF(SAM1),   KC_NO,      KC_NO,       KC_NO,        KC_NO,        KC_NO,   LALT(LCTL(KC_DEL)),                                     KC_ESC,  LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),  LCTL(KC_Z), KC_NO,    DF(SAM1),
    KC_NO,      KC_F1,      KC_F2,       KC_F3,        KC_F4,        KC_F5,   KC_F11,                                                 KC_BSPC, KC_DEL,     KC_HOME,    KC_UP,       KC_END,     KC_PGUP,  KC_NO,
    KC_TAB,     KC_F6,      KC_F7,       MTC_F8,       MTC_F9,       KC_F10,  KC_F12,                                                 KC_CAPS, KC_INS,     KC_LEFT,    KC_DOWN,     KC_RIGHT,   KC_PGDN,  KC_TAB,
    KC_LCTL,    LCTL(KC_Z), LCTL(KC_X),  LCTL(KC_C),   LCTL(KC_V),   KC_NO,   A(KC_RIGHT),  TT(SAM3),  TT(SAM4),  TT(SAM4), TT(SAM2), KC_LNG2, KC_BSLS,    KC_QUOT,    KC_LBRC,     KC_RBRC,    KC_GRV,   KC_RCTL,
    KC_NO,      TT(SAM1),   KC_NO,       KC_LALT,             KC_SPC,         TT(SAM2),     KC_LCTL,   KC_LGUI,     KC_PSCR,    KC_RCTL,  TT(SAM3),       KC_SPC,          KC_RALT,     KC_NO,      TT(SAM1), KC_NO,
                                                                                                             KC_BTN1, KC_BTN2
  ),  

    [SAM3] = LAYOUT(
    DF(SAM1),   KC_NO,      KC_NO,       KC_NO,        KC_NO,        KC_NO,   LALT(LCTL(KC_DEL)),                                  KC_ESC,  KC_NO,   KC_NO,     KC_NO,   KC_NO,    KC_NO,    DF(SAM1),
    KC_NO,      KC_1,       KC_2,        KC_3,         KC_4,         KC_5,    KC_BSPC,                                             KC_BSPC, KC_1,    KC_2,      KC_3,    KC_4,     KC_5,     KC_NO,
    KC_TAB,     KC_6,       KC_7,        KC_8,         MTLC_9,       KC_0,    KC_DOT,                                              KC_DOT,  KC_6,    MTC_7,     MTC_8,   KC_9,     KC_0,     KC_TAB,
    KC_LCTL,    KC_PSLS,    KC_PAST,     KC_MINS,      KC_PPLS,      KC_EQL,  KC_COMM,  TT(SAM3),  TT(SAM4),  TT(SAM4), TT(SAM2),  KC_COMM, KC_EQL,  KC_PPLS,   KC_PMNS, KC_PAST,  KC_PSLS,  KC_RCTL,
    KC_NO,      TT(SAM1),   KC_NO,       KC_LALT,             KC_SPC,         TT(SAM2), KC_LCTL,   KC_LGUI,     MOD_RGUI,    KC_PSCR,   TT(SAM3),    KC_SPC,         KC_RALT, KC_NO,    TT(SAM1), KC_NO,
                                                                                                             KC_BTN1, KC_BTN2
  ),


    [SAM4] = LAYOUT(
    DF(SAM1),   KC_NO,      KC_NO,       KC_NO,        KC_NO,        KC_NO,   KC_ESC,                                             KC_ESC,   KC_NO,     KC_NO,   KC_NO,   KC_NO,    KC_NO,    DF(SAM1),
    KC_NO,      KC_NO,      KC_NO,       KC_WH_U,      KC_BTN2,      KC_BTN1, KC_NO,                                              KC_NO,    KC_ACL0,   KC_BTN1, KC_BTN2, KC_BTN3,  KC_BTN4,  KC_NO,
    KC_NO,      KC_NO,      KC_WH_L,     KC_WH_D,      KC_WH_R,      KC_NO,   KC_NO,                                              KC_NO,    KC_ACL1,   KC_MS_L, KC_MS_D, KC_MS_U,  KC_MS_R,  KC_TAB,
    KC_NO,      KC_NO,      KC_ACL0,     KC_ACL1,      KC_ACL2,      KC_NO,   KC_NO,    TT(SAM3),  TT(SAM4), TT(SAM4), TT(SAM2),  KC_NO,    KC_ACL2,   KC_WH_L, KC_WH_D, KC_WH_U,  KC_WH_R,  KC_RCTL,
    KC_NO,      TT(SAM1),   KC_NO,       KC_LALT,             KC_SPC,         TT(SAM2), KC_LCTL,   KC_LGUI,    MOD_RGUI,    KC_PSCR,   TT(SAM3),       KC_SPC,       KC_RALT, KC_NO,    TT(SAM1), KC_NO,
                                                                                                             KC_BTN1, KC_BTN2
  )
};

/*

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [SAM1] =  { { KC_UP, KC_DOWN }  },
    [SAM2] =  { { KC_PGUP, KC_PGDN } },
    [SAM3] =  { { KC_VOLU, KC_VOLD } },
    [SAM4] =  { { KC_MS_WH_UP, KC_MS_WH_DOWN } }
};
#endif

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [1] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [2] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [3] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
    [4] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
    [5] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
    [6] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)}
};
#endif

*/




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
//    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 

    switch (keycode) {
		case KC_LNG1:
			// Detect the activation of only Left shift
			if ((get_mods() & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {

				unregister_code(KC_LCTL);
				register_code(KC_LCTL);
				register_code(KC_LSFT);
				tap_code16(KC_LEFT);
				unregister_code(KC_LCTL);
				unregister_code(KC_LSFT);
				tap_code16(KC_BSPC);
				//tap_code16(KC_LNG1);
			}
			// Else, let QMK process the KC_ESC keycode as usual
			return true;
    }
  return true;
}


// encoder

#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), },
    [1] = { ENCODER_CCW_CW(KC_UP, KC_DOWN), },
    [2] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN), },
    [3] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), },
};
#endif

/*
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 0:
            if (clockwise) {
                    tap_code(KC_MS_WH_DOWN);
                } else {
                    tap_code(KC_MS_WH_UP);
                }
            break;

        case 1:
            if (clockwise) {
                    tap_code(KC_DOWN);
                } else {
                    tap_code(KC_UP);
                }
            break;

        case 2:
            if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
            break;

        case 3:
            if (clockwise) {
                    tap_code(KC_RIGHT);
                } else {
                    tap_code(KC_LEFT);
                }
            break;

    }
    return false;
}
*/

/*
enum combo_events {
  LANG_CLEAR,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!
const uint16_t PROGMEM lang_clear_combo[] = {KC_RCTL, KC_LNG1, COMBO_END};


combo_t key_combos[] = {
  [LANG_CLEAR] = COMBO_ACTION(lang_clear_combo),
  //[BSPC_LSFT_CLEAR] = COMBO_ACTION(clear_line_combo),
};
*/

/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

/*
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
	  
    //case LANG_CLEAR:
    //  if (pressed) {
    //    SEND_STRING("john.doe@example.com");
    //  }
    //  break;
	  
    case LANG_CLEAR:
      if (pressed) {
        //tap_code16(KC_END);
		//tap_code16(SC(KC_HOME));
		
		register_code(KC_RCTL);
		register_code(KC_RSHIFT);
        tap_code16(KC_LEFT);
		unregister_code(KC_RCTL);
		unregister_code(KC_RSHIFT);
		tap_code16(KC_BSPC);
		tap_code16(KC_LNG1);
      }
      break;
  }
}
*/
