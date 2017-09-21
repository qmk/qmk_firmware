#include "clueboard_66.h"

// Helpful defines
#define _______ KC_TRNS
#define xxxxxxx KC_NO

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0 // BASE Layer
#define _FL 1 // Function Layer
#define _ME 2 // Media Layer
#define _CL 3 // Control Layer
#define _ML 4 // Mouse Layer
#if defined(MIDI_ENABLE)
  #define _MI 5 // MIDI Layer
  #define TO_MIDI TO(_MI)
#else
  #define TO_MIDI _______
#endif

// go back to base layer
#define TO_BASE TO(_BL)

// switch to function layer while helde
#define MO_FUNC MO(_FL)

// switch to media layer  while held
#define   MEDIA MO(_ME)

// switch to Control layer while helde
#define  MO_CTL MO(_CL)

// switch to mouse layer if held, else space
#define L_MOUSE LT(_ML, KC_SPC)

// Function key when held, else ESC
#define ESC_FUN LT(_FL, KC_ESC)

// Hyper (CTRL+ALT+SHIFT+SUPER) when held, TAB when tapped
#define HPR_TAB ALL_T(KC_TAB)

// CTRL when held, ESC when tapped
#define CTL_ESC CTL_T(KC_ESC)

// Reset RGB mode to layer signalling
#define RGB_RST F(0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer) */
  [_BL] = KEYMAP(
    KC_GESC,    KC_1,    KC_2,   KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0, KC_MINS,   KC_EQL, _______, KC_BSPC,          KC_INS,  \
    HPR_TAB,    KC_Q,    KC_W,   KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P, KC_LBRC,  KC_RBRC, KC_BSLS,                   KC_DEL,  \
    ESC_FUN,    KC_A,    KC_S,   KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, KC_QUOT,  KC_NUHS,  KC_ENT,                            \
    KC_LSFT, KC_NUBS,    KC_Z,   KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,   KC_DOT, KC_SLSH,  _______, KC_RSFT,          KC_UP,            \
    KC_LCTL, KC_LGUI, KC_LALT,_______,                    L_MOUSE, L_MOUSE,                    _______, KC_RALT,  KC_RCTL, MO_FUNC, KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function layer */
  [_FL] = KEYMAP(
     KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12, _______, _______,          BL_STEP, \
    _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______,  KC_PAUS, _______,  _______, _______,                   _______, \
    _______, _______,  MO_CTL, _______, _______, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  _______, _______,  _______, _______,                            \
    KC_LSPO, _______, _______, _______, _______, _______, _______, _______,   MEDIA, _______,  _______, TO_MIDI,  _______, KC_RSPC,          KC_PGUP,          \
    _______, _______, _______, _______,                   _______, _______,                    _______, _______,  _______, MO_FUNC, KC_HOME, KC_PGDN, KC_END),

  /* Keymap _ME: Media layer */
  [_ME] = KEYMAP(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______, KC_MUTE,          KC_VOLU, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                   KC_VOLD, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                            \
    _______, _______, _______, _______, _______, _______, _______, _______,   MEDIA, _______,  _______, _______,  _______, _______,          _______,          \
    _______, _______, _______, _______,                   _______, _______,                    _______, _______,  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT),

  /* Keymap _CL: Control layer */
  [_CL] = KEYMAP(
    _______, RGB_RST, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______, RGB_TOG,          RGB_VAI, \
    _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                   RGB_VAD, \
    _______, _______,  MO_CTL, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                            \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,          RGB_SAI,          \
    _______, _______, _______, _______,                   RGB_MOD, RGB_MOD,                    _______, _______,  _______, _______, RGB_HUD, RGB_SAD, RGB_HUI),

  /* Keymap _ML: Mouse layer */
  [_ML] = KEYMAP(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______, _______,          _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                   _______, \
    _______, _______, KC_BTN2, KC_BTN3, KC_BTN1, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,  _______, _______,  _______, _______,                            \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,          KC_MS_U,          \
    _______, _______, _______, _______,                   L_MOUSE, L_MOUSE,                    _______, KC_BTN1,  KC_BTN3, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_R),

#if defined(MIDI_ENABLE) && defined(MIDI_ADVANCED)
  /* Keymap _MI: MIDI layer (Advanced)*/
  [_MI] = KEYMAP(
    TO_BASE,MI_VEL_1,MI_VEL_2,MI_VEL_3,MI_VEL_4,MI_VEL_5,MI_VEL_6,MI_VEL_7,MI_VEL_8,MI_VEL_9,MI_VEL_10,  MI_CHD,   MI_CHU, xxxxxxx, xxxxxxx,          xxxxxxx, \
    xxxxxxx, xxxxxxx,   MI_Cs,   MI_Ds, xxxxxxx,   MI_Fs,   MI_Gs,   MI_As, xxxxxxx, MI_Cs_1,  MI_Ds_1, xxxxxxx,  MI_Fs_1, xxxxxxx,                   xxxxxxx, \
     MI_MOD,    MI_C,    MI_D,    MI_E,    MI_F,    MI_G,    MI_A,    MI_B,  MI_C_1,  MI_D_1,   MI_E_1,  MI_F_1,   MI_G_1, xxxxxxx,                            \
     MI_SUS, xxxxxxx, MI_OCTD, MI_OCTU,MI_MODSD,MI_MODSU, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, MI_TRNSD,MI_TRNSU,MI_TRNS_0,  MI_SUS,          xxxxxxx,          \
    xxxxxxx, xxxxxxx, xxxxxxx,xxxxxxx,                 MI_ALLOFF, MI_ALLOFF,                   xxxxxxx, xxxxxxx,  xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx),
#elif defined(MIDI_ENABLE) && defined(MIDI_BASIC)
  /* Keymap _MI: MIDI layer (Basic)*/
  [_MI] = KEYMAP(
    TO_BASE, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  xxxxxxx, xxxxxxx,  xxxxxxx, xxxxxxx, xxxxxxx,          xxxxxxx, \
    xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  xxxxxxx, xxxxxxx,  xxxxxxx, xxxxxxx,                   xxxxxxx, \
    xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  xxxxxxx, xxxxxxx,  xxxxxxx, xxxxxxx,                            \
    xxxxxxx, xxxxxxx,   MI_ON,  MI_OFF, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  xxxxxxx, xxxxxxx,  xxxxxxx, xxxxxxx,          xxxxxxx,          \
    xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,                   xxxxxxx, xxxxxxx,                    xxxxxxx, xxxxxxx,  xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx),
#endif
};

/* This is a list of user defined functions. F(N) corresponds to item N
   of this list.
 */
const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_FUNCTION(0),  // Calls action_function()
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case 0:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(206, 255, 255);
      }
  }
}

enum layer_id {
  LAYER_BASE,
  LAYER_FUNCTION,
  LAYER_MEDIA,
  LAYER_CONTROL,
  LAYER_MOUSE,
#if defined(MIDI_ENABLE)
  LAYER_MIDI
#endif
};

void clueboard_set_led(uint8_t id, uint8_t val) {
  switch (id) {
    case LAYER_BASE:
      rgblight_sethsv_noeeprom(0, 0, val);
      break;
    case LAYER_FUNCTION:
      rgblight_sethsv_noeeprom(46, 255, val);
      break;
    case LAYER_MEDIA:
      rgblight_sethsv_noeeprom(86, 255, val);
      break;
    case LAYER_CONTROL:
      rgblight_sethsv_noeeprom(346, 255, val);
      break;
    case LAYER_MOUSE:
      rgblight_sethsv_noeeprom(206, 255, val);
      break;
#if defined(MIDI_ENABLE)
    case LAYER_MIDI:
      rgblight_sethsv_noeeprom(316, 255, val);
      break;
#endif
  }
};

const uint16_t oct_hues[10] = {
  0,
  30,
  60,
  90,
  120,
  150,
  180,
  210,
  240,
  300
};

#define MAX_OCT  9

void clueboard_set_midi_led(uint8_t base_oct, uint8_t val)
{
  uint8_t sat = 255;

  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    sethsv(oct_hues[base_oct], sat, val, (LED_TYPE *)&led[i]);
  }

  uint8_t next_oct = base_oct < MAX_OCT ? base_oct + 1 : base_oct;

  uint16_t next_hue = base_oct < MAX_OCT ? oct_hues[next_oct] : 0;
  uint8_t next_val = base_oct < MAX_OCT ? val : 0;
  uint8_t next_sat = base_oct < MAX_OCT ? sat : 0;


  for (uint8_t i = 0; i < 3; i++) {
    sethsv(next_hue, next_sat, next_val, (LED_TYPE *)&led[i]);
  }

  for (uint8_t i = 11; i < 14; i++) {
    sethsv(next_hue, next_sat, next_val, (LED_TYPE *)&led[i]);
  }

  rgblight_set();
}

void matrix_scan_user(void) {
    rgblight_config_t rgblight_config;
    rgblight_config.raw = eeconfig_read_rgblight();

    if (!rgblight_config.enable || rgblight_config.mode != 1) { return; }

    uint32_t layer = layer_state;
    uint8_t val = rgblight_config.val;

    if (layer & (1<<_FL)) {
      if (layer & (1<<_ME)) {
        clueboard_set_led(LAYER_MEDIA, val);
      } else if (layer & (1<<_CL)) {
        clueboard_set_led(LAYER_CONTROL, val);
      } else {
        clueboard_set_led(LAYER_FUNCTION, val);
      }
    } else if (layer & (1<<_ML)) {
      clueboard_set_led(LAYER_MOUSE, val);
#if defined(MIDI_ENABLE)
    } else if (layer & (1<<_MI)) {
      clueboard_set_midi_led(midi_config.octave, val);
#endif
    } else {
        clueboard_set_led(LAYER_BASE, val);
    }
};
