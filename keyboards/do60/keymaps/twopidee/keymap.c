#include QMK_KEYBOARD_H

#define RGBLIGHT_ANIMATIONS


//Helpful defines
#define _L0 0
#define _L1 1
#define _L2 2
#define _ML 3

//Macros
enum custom_keycodes {
  M_SEAL = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  [_L0] = LAYOUT_all(
      KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_NO,    KC_DEL,   \
      KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,           KC_BSLS,  \
      KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_NO,             KC_ENT,   \
      KC_LSPO,  KC_NO,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_RSPC,  KC_NO,   KC_UP,    KC_SLSH,  \
      KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC, TT(2),  KC_BSPC,                 KC_RGUI, TT(1),    KC_LEFT, KC_DOWN,  KC_RIGHT),

  // 1: Function Layer
  [_L1] = LAYOUT_all(
      KC_ESC,  KC_F1,   KC_F2,     KC_F3,     KC_F4,      KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,  KC_F11,   KC_F12,  KC_NO,    KC_TRNS,   \
      KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_PSCR, KC_SLCK,  KC_PAUS,           M_SEAL,    \
      KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_NO,             KC_ENT,    \
      KC_LSFT, KC_NO,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_RSFT,  KC_NO  , KC_PGUP,  KC_INS,    \
      KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPC, KC_TRNS,  KC_DEL,                                  KC_RGUI, KC_TRNS,  KC_HOME, KC_PGDOWN,KC_END),

  // 1: RGB/Audio Layer
  [_L2] = LAYOUT_all(
      KC_ESC,  RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN,  RGB_M_K,  RGB_M_X,  RGB_M_G, KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_NO,   KC_NO,      \
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,           KC_TRNS,    \
      KC_TRNS, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD, KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_NO,             KC_MPLY,    \
      KC_LSFT, KC_NO,   KC_TRNS, KC_APP,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_RSFT,  KC_NO  , KC_VOLU,  KC_NO,    \
      RGB_RMOD,KC_LGUI, RGB_MOD,                    KC_BSPC,KC_TRNS,KC_DEL,                            KC_TRNS,   KC_TRNS,  KC_MPRV, KC_VOLD,  KC_MNXT),

#if defined(MIDI_ENABLE) && defined(MIDI_ADVANCED)

  // _ML: Midi Layer
  [_ML] = LAYOUT_all(
      TG(_ML), MI_VEL_1, MI_VEL_2, MI_VEL_3, MI_VEL_4, MI_VEL_5, MI_VEL_6, MI_VEL_7, MI_VEL_8, MI_VEL_9, MI_VEL_10, KC_NO,      KC_NO, KC_NO, KC_NO,   \
      MI_CHU,  KC_NO,    MI_Cs,    MI_Ds,    KC_NO,    MI_Fs,    MI_Gs,    MI_As,    KC_NO,    MI_Cs_1,  MI_Ds_1,   KC_NO,      KC_NO,        KC_NO,   \
      MI_MOD,  MI_C,     MI_D,     MI_E,     MI_F,     MI_G,     MI_A,     MI_B,     MI_C_1,   MI_D_1,   MI_E_1,    MI_F_1,     KC_NO,        KC_NO,    \
      MI_SUS,  KC_NO,    MI_OCTD,  MI_OCTU,  MI_MODSD, MI_MODSU, KC_NO,    KC_NO,    KC_NO,    MI_TRNSD, MI_TRNSU,  MI_TRANS_0, KC_NO, KC_NO, KC_NO,    \
      KC_LCTL, KC_LGUI,  KC_LALT,                   MI_ALLOFF, KC_NO,  MI_ALLOFF,                  KC_RGUI, TT(1),  KC_LEFT,    KC_DOWN,      KC_RIGHT),

#elif defined(MIDI_ENABLE) && defined(MIDI_BASIC)

// _ML: Midi Layer
  [_ML] = LAYOUT_all(
     TG(_ML), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,   \
     KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO,   \
     KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO,    \
     KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MI_ON,  KC_NO,    \
     KC_NO,   KC_NO, KC_NO,                   KC_NO, TO(0),  KC_NO,          KC_NO, KC_NO, KC_NO, MI_OFF, KC_NO),

   #endif
};

// Custom Actions


 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_SEAL:
      if (record->event.pressed) {
        // when keycode M_SEAL is pressed
        SEND_STRING("What the fuck did you just fucking say about me, you little bitch? I'll have you know I graduated top of my class in the Navy Seals, and I've been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills. I am trained in gorilla warfare and I'm the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with saying that shit to me over the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You're fucking dead, kid. I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that's just with my bare hands. Not only am I extensively trained in unarmed combat, but I have access to the entire arsenal of the United States Marine Corps and I will use it to its full extent to wipe your miserable ass off the face of the continent, you little shit. If only you could have known what unholy retribution your little clever comment was about to bring down upon you, maybe you would have held your fucking tongue. But you couldn't, you didn't, and now you're paying the price, you goddamn idiot. I will shit fury all over you and you will drown in it. You're fucking dead, kiddo.");
      } else {
        // when keycode M_SEAL is released
      }
      break;

  }
  return true;
};

// ***Bryan S. SUX, Kelly K. ROX***


// Macros
/*
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) { register_code(KC_RSFT); }
      else { unregister_code(KC_RSFT); }
      break;
  }

  return MACRO_NONE;
};
*/
// Loop
void matrix_scan_user(void) {
  // Empty
};
