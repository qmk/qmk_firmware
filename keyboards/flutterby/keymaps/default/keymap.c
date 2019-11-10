#include "flutterby.h"
#include "action_layer.h"
#include "pincontrol.h"
#ifdef MOUSEKEY_ENABLE
#include "mousekey.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
enum layer_id {
  BASE = 0,
  RAISE,
  LOWER,
};

// Macro ids for use with M(n)
enum macro_id {
  MCOPY = 1,
  MCUT,
  MPASTE,
};

// Function ids for use with F(n)
enum function_id {
  FNCOPYCUT,
  FNOSTOGGLE,
  FNTHUMBSTICKMODE,
};

static bool is_mac = false;

#define ____ KC_TRNS
#define CTL(k)  ACTION_MODS_KEY(MOD_LCTL, k)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = { /* Qwerty */
        {KC_Q,          KC_W,    KC_E,    KC_R,          KC_T,                      KC_Y,          KC_U,          KC_I,    KC_O,    KC_P},
	    {KC_A,          KC_S,    KC_D,    KC_F,          KC_G,                      KC_H,          KC_J,          KC_K,    KC_L,    KC_SCLN},
	    {KC_Z,          KC_X,    KC_C,    KC_V,          KC_B,                      KC_N,          KC_M,          KC_COMM, KC_DOT,  KC_SLSH},
	    {ALT_T(KC_ESC), KC_LGUI, KC_LALT, LT(LOWER,KC_SPC),  CTL_T(KC_BSPC),            SFT_T(KC_SPC), LT(RAISE,KC_TAB),  TG(4),   F(FNTHUMBSTICKMODE),  KC_SFTENT}
    },
	[RAISE] = { /* Layer 1 */
        {KC_EXLM,       KC_AT,   KC_HASH, KC_DLR,        KC_PERC,                   KC_EQL,        KC_7,          KC_8,    KC_9,    KC_0},
	    {KC_CIRC,       KC_AMPR, KC_UNDS, KC_DQUO,       KC_QUOT,                   KC_SLSH,      KC_4,          KC_5,    KC_6,    KC_MINS},
	    {KC_PIPE,       KC_BSLS, KC_TILD, KC_GRV,        KC_CALC,                   KC_ASTR,      KC_1,          KC_2,    KC_3,    KC_PLUS},
	    {KC_TRNS,       KC_TRNS, KC_TRNS, LT(3,KC_TRNS), KC_TRNS,                   KC_TRNS,      KC_TRNS,       KC_0,    KC_DOT,  KC_TRNS}
    },
	[LOWER] = { /* Layer 2 */
        {KC_VOLU,       KC_HOME, KC_UP,   KC_END,        KC_PGUP,                   KC_WBAK,      KC_WFWD,       KC_LPRN,   KC_RPRN,   KC_WH_U},
	    {KC_VOLD,       KC_LEFT, KC_DOWN, KC_RGHT,       KC_PGDN,                   KC_NO,        KC_NO,         KC_LBRC,   KC_RBRC,   KC_WH_D},
	    {KC_MUTE,       KC_CAPS, KC_SLCK, KC_INS,        KC_PSCR,                   KC_NO,        KC_NO,         KC_LCBR,   KC_RCBR,   KC_MYCM},
	    {KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,                   KC_TRNS,      LT(3,KC_TRNS), KC_TRNS, KC_TRNS, KC_TRNS}
    },
	[3] = { /* Function Layer */
        {RGB_HUI,       RGB_SAI, RGB_SPI, RGB_VAI,       RGB_MOD,                   RESET,        KC_F7,         KC_F8,   KC_F9,   KC_F10},
	    {RGB_HUD,       RGB_SAD, RGB_SPD, RGB_VAD,       RGB_RMOD,                  KC_SLEP,      KC_F4,         KC_F5,   KC_F6,   KC_F11},
	    {RGB_M_P,       RGB_M_R, RGB_M_K, RGB_M_B,       RGB_TOG,                   LCA(KC_DEL),  KC_F1,         KC_F2,   KC_F3,   KC_F12},
	    {KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,                   KC_TRNS,      KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS}
    },
	[4] = { /* Mouse Layer */
		{KC_MUTE,       KC_WH_L,  KC_MS_U, KC_WH_R,       KC_WH_U,                   KC_BTN3,      KC_WH_U,       KC_VOLD, KC_VOLU, KC_MUTE},
	 	{KC_VOLU,       KC_MS_L,  KC_MS_D, KC_MS_R,       KC_WH_D,                   KC_MS_L,      KC_MS_D,       KC_MS_U, KC_MS_R, KC_BTN1},
		{KC_VOLD,       KC_BTN1,  KC_BTN2, KC_BTN3,       KC_FIND,                   KC_WH_L,      KC_WH_D,       KC_WH_R, KC_F11, KC_BTN2},
		{KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,                   KC_TRNS,      KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS}
    }
};


void matrix_init_user(void) {
}

static const macro_t mac_cut[] PROGMEM = { D(LGUI), T(X), U(LGUI), END };
static const macro_t win_cut[] PROGMEM = { D(LSFT), T(DELT), U(LSFT), END };

static const macro_t mac_copy[] PROGMEM = { D(LGUI), T(C), U(LGUI), END };
static const macro_t win_copy[] PROGMEM = { D(LCTL), T(INS), U(LCTL), END };

static const macro_t mac_paste[] PROGMEM = { D(LGUI), T(V), U(LGUI), END };
static const macro_t win_paste[] PROGMEM = { D(LSFT), T(INS), U(LSFT), END };

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (!record->event.pressed) {
    return MACRO_NONE;
  }

  switch (id) {
  case MCUT:
    return is_mac ? mac_cut : win_cut;
  case MCOPY:
    return is_mac ? mac_copy : win_copy;
  case MPASTE:
    return is_mac ? mac_paste : win_paste;
  default:
    return MACRO_NONE;
  }
}

// Using F(n) causes the firmware to lookup what to do from this table
const uint16_t PROGMEM fn_actions[] = {
  [FNCOPYCUT] = ACTION_FUNCTION(FNCOPYCUT),
  [FNOSTOGGLE] = ACTION_FUNCTION(FNOSTOGGLE),
  [FNTHUMBSTICKMODE] = ACTION_FUNCTION(FNTHUMBSTICKMODE),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    // The OS-Toggle function toggles our concept of mac or windows
    case FNOSTOGGLE:
      if (IS_RELEASED(record->event)) {
        is_mac = !is_mac;
        flutterby_blink_led(is_mac ? 3 : 1);
      }
      return;

    // The copy-cut function sends the copy key sequence for mac or windows
    // when it is pressed.  If shift is held down, it will send the cut key
    // sequence instead, and cancels the shift modifier.
    case FNCOPYCUT:
      if (IS_RELEASED(record->event)) {
        int8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

        // Implicitly release the shift key so that it doesn't
        // mess with the macro that we play back
        unregister_mods(shifted);

        if (shifted) {
          action_macro_play(is_mac ? mac_cut : win_cut);
        } else {
          action_macro_play(is_mac ? mac_copy : win_copy);
        }
      }
      return;

    case FNTHUMBSTICKMODE:
      if (IS_RELEASED(record->event)) {
        switch (flutterby_thumbstick_get_mode()){
          case ThumbStickMovesPointer:
            flutterby_thumbstick_set_mode(ThumbStickPanning);
            flutterby_blink_led(2);
            break;
          case ThumbStickPanning:
            flutterby_thumbstick_set_mode(ThumbStickMovesPointer);
            flutterby_blink_led(4);
            break;
          default:
            flutterby_blink_led(7);
            break;
        }
      }
      return;
  }
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {
}
