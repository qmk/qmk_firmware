#include "hhkb.h"

// Layer names
#define BASE 0
#define DEV 1
#define MOUSE 2
#define MEDIA 3

// Required for leader function. Measured in ms
// #define LEADER_TIMEOUT 300

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE Level: Default Layer
     |-----------+-------+--------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------+----|
     |     `     |  1    | 2      | 3     |   4   |   5   |   6   | 7     | 8     | 9     | 0     | -     | =     | Bksp |Lead|
     |-----------+-------+--------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------+----|
     |    Tab    |  Q    | W      | E     |   R   |   T   |   Y   |  U    | I     | O     | P     | [     | ]     |      | \  |
     |-----------+-------+--------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------+----|
     | Esc/Hyper |   A   | S      | D     |   F   |   G   |   H   |  J    | K     | L     |;/Media| '     | Enter |      |    |
     |-----------+-------+--------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------+----|
     |   Shift   | Z/Ctl | X/Alt  | C/Gui |   V   |   B   |   N   |  M    | ,/Gui | ./Alt | //Ctl | Shift | Dev   |      |    |
     |-----------+-------+--------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------+----|
     TODO: Maybe add a photoshop layer for when I need to hold spacebar down. Maybe just make it a layer that you
                 |------+------+-----------------------+------+------|
                 | Dev  |Mouse | ******* Space ******* | Dev  |Mouse |
                 |------+------+-----------------------+------+------|
    */

  [BASE] = KEYMAP(  //  default layer
  KC_GRV,        KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,    KC_BSPC,  KC_LEAD,                          \
  KC_TAB,        KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC,   KC_BSLS,                                    \
  ALL_T(KC_ESC), KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,     LT(MEDIA, KC_SCLN),  KC_QUOT,  ALL_T(KC_ENT),                              \
  KC_LSFT,       CTL_T(KC_Z),  ALT_T(KC_X),  GUI_T(KC_C),  KC_V,  KC_B,  KC_N,     KC_M,  GUI_T(KC_COMM),  ALT_T(KC_DOT),  CTL_T(KC_SLSH), KC_RSFT,  TG(DEV), \
      TG(DEV), TG(MOUSE),                              LT(DEV, KC_SPC), TG(MOUSE),              TG(DEV)),

    /* Layer DEV: DEV mode (DEV Fn)
      TODO: Add a cmd/tab function to the developer layer for quick switching between different applications when debugging
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |        |                |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |        |                |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      | F1  | F2  | F3  | F4 | F5 | Left   |  Down          | Up           | Right     |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |        |                |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|

                 |------+------+----------------------+------+------+
                 | **** | **** | ******************** | **** | **** |
                 |------+------+----------------------+------+------+
     */

  [DEV] = KEYMAP(
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, \
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,          \
  KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_LEFT, KC_DOWN,  KC_UP,   KC_RIGHT, KC_TRNS,  KC_TRNS,  KC_TRNS,                    \
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, TG(DEV),                 \
                     KC_TRNS, KC_TRNS,           KC_TRNS,              KC_TRNS, KC_TRNS),

    /* Layer MOUSE: MOUSE mode (MOUSE Fn)
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |        |                |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |        |                |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |        |                |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |        |                |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|

                 |------+------+----------------------+------+------+
                 | **** | **** | ******************** | **** | **** |
                 |------+------+----------------------+------+------+
     */

  [MOUSE] = KEYMAP(
  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_D, KC_WH_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            \
  KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(DEV),                    \
                     KC_TRNS, KC_TRNS,           KC_TRNS,                KC_TRNS, KC_TRNS),

    /* Layer MEDIA: mode (Hold Semi-colon)
      |------+-----+-----+-----+----+----+----+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |    |                |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+----+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |    |                |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+----+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |    |  Previous      | Next         |           |  Play/Pause |     |       |       |     |
      |------+-----+-----+-----+----+----+----+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |     |     |     |    |    |    |  Volume Down   | Volume Up    | Mute      |             |     |       |       |     |
      |------+-----+-----+-----+----+----+----+----------------+--------------+-----------+-------------+-----+-------+-------+-----|

                 |------+------+----------------------+------+------+
                 | **** | **** | ******************** | **** | **** |
                 |------+------+----------------------+------+------+

     */

  [MEDIA] = KEYMAP(
  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  \
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,          \
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_TRNS,  KC_MPLY,  KC_TRNS,                    \
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_VOLD,  KC_VOLU,   KC_TRNS,  KC_TRNS,  KC_TRNS, TG(DEV),                    \
                     KC_TRNS, KC_TRNS,           KC_TRNS,                KC_TRNS, KC_TRNS)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
