#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "led.h"
#include "keymap.h"
#include "timer.h"

/*

# Why this Layout

This layout was based on Kinesis layout and other ErgoDox user layouts
available. It's target to be used on a MacOS but I'm pretty sure it can be
addapted to Windows and/or Linux easily.

## Function Key

The `fn` key work almost like it would in any other keyboard with the exception
it has a semi-sticky behavior. What does that mean?

Well, if you press the `fn` and release it, the keyboard will be put on the
_function layout_ and the next key stroke will be processed as if the `fn` key
was pressed. Aftwards, the leyout get back to _normal_. If you hold `fn` and
press any other key, when you release them, the keyboard leyout is back to
_normal_.

While pressing the `fn` with the left hand and strikeing the other keys on the
right hand is farly easy, the same cannot being said for the other keys on the
left side. So, instead of trying to do contorcionism with my left hand, I
decided to do a semi-sticky version of `fn`. This way, I can press the  `fn`
key with my pinky, release it and press the `1` key to issue an `F1` to the
operating system.

## Key-Pad Key

The `key pad` key is a layout switch key. If pressed, it will put the keyboard
on the _key pad layout_ and stay there until key is pressed again.

This is used to make the keyboard behave mostly like a **num pad keyboard**.

## Notes
- Regardless in which layout you are, keys from other layouts are not
  accessible. This means that if you are on the _key pad layout_, the left hand
  will be pretty much unusable.
  Of course that like anything else, there are exceptions to this rule.
  Modifiers should remain accessible throughout the layers.
- The _shift key_ is, like the _function key_, also configured to have a sticky
  behavior.
- All sticky keys have a timeout of 3 seconds.

*/
#define BASE   0
#define KEYPAD 1
#define FN     2

#define MACRO_TMUX_ESC        10
#define MACRO_TMUX_PASTE      11
#define MACRO_OSX_COPY        12
#define MACRO_OSX_PASTE       13

#define M_TESC   M(MACRO_TMUX_ESC)
#define M_TPASTE M(MACRO_TMUX_PASTE)
#define M_OSXCPY M(MACRO_OSX_COPY)
#define M_OSXPST M(MACRO_OSX_PASTE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |        `~ |   1  |   2  |   3  |   4  |   5  | ESC  |           | Pwr  |   6  |   7  |   8  |   9  |   0  | - _       |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Tab       |   Q  |   W  |   E  |   R  |   T  | F16  |           | F17  |   Y  |   U  |   I  |   O  |   P  | = +       |
 * |-----------+------+------+------+------+------| Meh  |           | Meh  |------+------+------+------+------+-----------|
 * | \ (Ctrl)  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | ' " (Ctrl)|
 * |-----------+------+------+------+------+------| F18  |           | F19  |------+------+------+------+------+-----------|
 * |  LShift   |   Z  |   X  |   C  |   V  |   B  | Hyper|           | Hyper|   N  |   M  |   ,  |   .  |   /  |   RShift  |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     | FN    | KPAD |LCtrl | LAlt | LGui |                                       | RGui | RAlt | RCtrl| KPAD |    FN |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | M(0) | M(1) |           | M(2) | M(3) |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | Home |           | PgUp |      |      |
 *                                  |Backsp| Del  |------|           |------| Enter| Space|
 *                                  |      |      | End  |           | PgDn |      |      |
 *                                  `--------------------'           `--------------------'
 *
 * M(0) = Ctrk+A Esc
 *        (this is used to issue the Esc key to the Tmux application)
 * M(1) = Ctrk+A P
 *        (this is used to issue the Paste key to the Tmux application)
 * M(2) = Cmd+C
 * M(3) = Cmd+V
 */
[BASE]=LAYOUT_ergodox(//left half
              KC_GRV,         KC_1,       KC_2,     KC_3,           KC_4,       KC_5,     KC_ESC,
              KC_TAB,         KC_Q,       KC_W,     KC_E,           KC_R,       KC_T,     MEH_T(KC_F16),
              CTL_T(KC_BSLS), KC_A,       KC_S,     KC_D,           KC_F,       KC_G,
              KC_FN2,         KC_Z,       KC_X,     KC_C,           KC_V,       KC_B,     ALL_T(KC_F18),
              KC_FN1,         TG(KEYPAD), KC_LCTRL, KC_LALT,        KC_LGUI,
                                                                                M_TESC,   M_TPASTE,
                                                                                          KC_HOME,
                                                                    KC_BSPC,    KC_DEL,   KC_END,
              //right half
              KC_POWER,       KC_6,       KC_7,     KC_8,           KC_9,       KC_0,     KC_MINS,
              MEH_T(KC_F17),  KC_Y,       KC_U,     KC_I,           KC_O,       KC_P,     KC_EQL,
                              KC_H,       KC_J,     KC_K,           KC_L,       KC_SCLN,  CTL_T(KC_QUOT),
              ALL_T(KC_F19),  KC_N,       KC_M,     KC_COMM,        KC_DOT,     KC_SLSH,  KC_FN2,
                              KC_RGUI,    KC_RALT,  CTL_T(KC_LBRC), LT(KEYPAD, KC_RBRC),  KC_FN1,
              M_OSXCPY,       M_OSXPST,
              KC_PGUP,
              KC_PGDN,        KC_ENT,     KC_SPC),

/* Keymap 1: KeyPad Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      | LClk | RClk | MClk |      |      |           | BTab | Clear|   /  |   *  |   ^  |   (  |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | M.Accel 2 |      |ScrlUp|  U   |ScrlDn|      |      |           | Tab  |   7  |   8  |   9  |   +  |   )  |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | M.Accel 1 |      |   L  |  D   |  R   |      |------|           |------|   4  |   5  |   6  |   -  |      |           |
 * |-----------+------+------+------+------+------|      |           |Return|------+------+------+------+------+-----------|
 * | M.Accel 0 |      |ScrlL |      |ScrlR |      |      |           |      |   1  |   2  |   3  |   =  |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       | XXXX |      |      |      |                                       |   0  |   .  |   ,  | XXXX |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      | XXXX |      |
 *                                  |      |      |------|           |------| XXXX |      |
 *                                  |      |      |      |           |      | XXXX |      |
 *                                  `--------------------'           `--------------------'
 */
[KEYPAD]=LAYOUT_ergodox(//left half
                KC_NO,        KC_NO,    KC_MS_BTN1,    KC_MS_BTN2,     KC_MS_BTN3,     KC_NO,   KC_NO,
                KC_MS_ACCEL2, KC_NO,    KC_MS_WH_UP,   KC_MS_U,        KC_MS_WH_DOWN,  KC_NO,   KC_NO,
                KC_MS_ACCEL1, KC_NO,    KC_MS_L,       KC_MS_D,        KC_MS_R,        KC_NO,
                KC_MS_ACCEL0, KC_NO,    KC_MS_WH_LEFT, KC_NO,          KC_MS_WH_RIGHT, KC_NO,   KC_NO,
                KC_NO,        KC_TRNS,  KC_NO,         KC_NO,          KC_NO,
                                                                                       KC_NO,   KC_NO,
                                                                                                KC_NO,
                                                                       KC_NO,          KC_NO,   KC_NO,
                //right half
                LSFT(KC_TAB), KC_CLEAR, KC_KP_SLASH,   KC_KP_ASTERISK, KC_CIRCUMFLEX,  KC_LPRN, KC_NO,
                KC_TAB,       KC_KP_7,  KC_KP_8,       KC_KP_9,        KC_KP_PLUS,     KC_RPRN, KC_NO,
                              KC_KP_4,  KC_KP_5,       KC_KP_6,        KC_KP_MINUS,    KC_NO,   KC_NO,
                KC_KP_ENTER,  KC_KP_1,  KC_KP_2,       KC_KP_3,        KC_KP_EQUAL,    KC_NO,   KC_NO,
                                        KC_KP_0,       KC_KP_DOT,      KC_KP_COMMA,    KC_TRNS, KC_NO,
                KC_NO,        KC_NO,
                KC_NO,
                KC_NO,        KC_TRNS,  KC_NO),

/* Keymap 2: Functions Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  Vol. Up  |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           | Stop |  Rw  |  Rec |  FF  |      | XXXX |           | XXXX |      |      |      |      |      | Vol. Down |
 * |-----------+------+------+------+------+------| XXXX |           | XXXX |------+------+------+------+------+-----------|
 * |  CapsLock | Eject| Prev | Play | Next |      |------|           |------| Left | Down |  Up  | Right|      |   Mute    |
 * |-----------+------+------+------+------+------| XXXX |           | XXXX |------+------+------+------+------+-----------|
 * |  L Shift  |      |      |      |      |      | XXXX |           | XXXX |      |      |      |      |      |  R Shift  |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     | XXXXX |      | XXXX | XXXX | XXXX |                                       | XXXX | XXXX | XXXX |      | XXXXX |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 *
 * XXX = These keys are transparent keys that, when pressed, they issue the key from the previous layer.
 */
[FN]=LAYOUT_ergodox(//left half
            KC_NO,   KC_F1,          KC_F2,               KC_F3,               KC_F4,                 KC_F5,  KC_F6,
            KC_NO,   KC_MEDIA_STOP,  KC_MEDIA_REWIND,     KC_MEDIA_SELECT,     KC_MEDIA_FAST_FORWARD, KC_NO,  KC_TRNS,
            KC_CAPS, KC_MEDIA_EJECT, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK,   KC_NO,
            KC_LSFT, KC_NO,          KC_NO,               KC_NO,               KC_NO,                 KC_NO,  KC_TRNS,
            KC_TRNS, KC_NO,          KC_TRNS,             KC_TRNS,             KC_TRNS,
                                                                                                      KC_NO,  KC_NO,
                                                                                                              KC_NO,
                                                                               KC_NO,                 KC_NO,  KC_NO,
            //right half
            KC_F7,   KC_F8,          KC_F9,               KC_F10,              KC_F11,                KC_F12, KC_VOLU,
            KC_TRNS, KC_NO,          KC_NO,               KC_NO,               KC_NO,                 KC_NO,  KC_VOLD,
                     KC_LEFT,        KC_DOWN,             KC_UP,               KC_RIGHT,              KC_NO,  KC_MUTE,
            KC_TRNS, KC_NO,          KC_NO,               KC_NO,               KC_NO,                 KC_NO,  KC_RSFT,
                                     KC_TRNS,             KC_TRNS,             KC_TRNS,               KC_NO,  KC_TRNS,
            KC_NO,   KC_NO,
            KC_NO,
            KC_NO,   KC_NO,          KC_NO)};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_ONESHOT(FN),
  [2] = ACTION_MODS_ONESHOT(MOD_LSFT),  // Sticky shift light. Tap for the next keypress to be shifted. Hold for regular shift.
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch(id) {
    case MACRO_TMUX_ESC:
      if (record->event.pressed) {
        return MACRO(D(LCTRL), T(A), U(LCTRL), D(ESC), END);
      }
      return MACRO(U(ESC), END);
    case MACRO_TMUX_PASTE:
      if (record->event.pressed) {
        return MACRO(D(LCTRL), T(A), U(LCTRL), D(P), END);
      }
      return MACRO(U(P), END);
    case MACRO_OSX_COPY:
      if (record->event.pressed) {
        return MACRO(D(LGUI), D(C), END);
      }
      return MACRO(U(C), U(LGUI), END);
    case MACRO_OSX_PASTE:
      if (record->event.pressed) {
        return MACRO(D(LGUI), D(V), END);
      }
      return MACRO(U(V), U(LGUI), END);
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

uint8_t current_layer = BASE;

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  ergodox_led_all_off();
  ergodox_led_all_set(LED_BRIGHTNESS_LO);

  switch (layer) {
  case BASE:
    current_layer = BASE;
    break;
  case KEYPAD:
    current_layer = KEYPAD;
    break;
  default:
    // none
    break;
  }

  // layer leds
  if (current_layer == KEYPAD) {
    ergodox_right_led_3_on();
  }

  // capslock
  if (host_keyboard_leds() & (3<<USB_LED_CAPS_LOCK)) {
    ergodox_right_led_1_on();
  }

  // Temporary leds

  // The function layer takes over other layers and we need to reflect that on the leds.
  // If the current layer is the BASE, we simply turn on the FN led, but if the current
  // layer is the KEYPAD, than we must turn it off before turning on the FN led.
  if (layer == FN && !has_oneshot_layer_timed_out()) {
    ergodox_right_led_3_off();
    ergodox_right_led_2_on();
  }

  // if the shifted is pressed I show the case led in a brighter color. This is nice to
  // differenciate the shift from the capslock.
  // Notice that I make sure that we're not using the shift on a chord shortcut (pressing
  // shift togather with other modifiers).
  if((keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) &&                                 // is shift pressed and there is no other
      !(keyboard_report->mods & (~MOD_BIT(KC_LSFT) & ~MOD_BIT(KC_RSFT)))) ||                           //    modifier being pressed as well
     (get_oneshot_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) && !has_oneshot_mods_timed_out())) {  // or the one shot shift didn't timed out
    ergodox_right_led_1_set(LED_BRIGHTNESS_HI);
    ergodox_right_led_1_on();
  }
};
