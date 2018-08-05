#include "m10a.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "version.h"

extern keymap_config_t keymap_config;

enum layers {
  _NUMPAD = 0,
  _MACROS = 1
};

enum m10a_keycodes {
    EMAIL = SAFE_RANGE,
    ADDRESS
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define LAYER1 LT(1, KC_5)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* .-----------.  .-----------.  .-----------.  .-----------.  .-----------.
  *  |  7|  8|  9|  |  +|  -|  *|  |  ^|  &|  !|  |VLU|Ver|WFD|  |VLU|NXT|FFD|
  *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
  *  |  4|  5|  6|  |  /|  %|  ,|  |  D|  E|  F|  |MUT|C-W|CHR|  |MUT|STP|PLY|
  *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
  *  |  1|  2|  3|  |  .|  =|Ent|  |  A|  B|  C|  |VLD|CMP|WBK|  |VLD|PRV|RWD|
  *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
  *  |L0 |  _L9/0|  |L1 |  _L9  |  |L2 |  _L9  |  |L3 |  _L9  |  |L4 |  _L9  |
  *  *-----------*  *-----------*  *-----------*  *-----------*  *-----------*
  *  .-----------.  .-----------.  .-----------.  .-----------.  .-----------.
  *  |   |   |   |  |   |   |   |  |MP1|   |MP2|  |   |   |RST|  |_L6|_L7|_L8|
  *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
  *  |   |   |   |  |   |   |   |  |   |MRS|   |  |   |   |   |  |_L3|_L4|_L5|
  *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
  *  |   |   |   |  |   |   |   |  |MR1|   |MR2|  |   |   |   |  |_L0|_L1|_L2|
  *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
  *  |L5 |  _L9  |  |L6 |  _L9  |  |L7 |  _L9  |  |L8 |  _L9  |  |L9 |       |
  *  *-----------*  *-----------*  *-----------*  *-----------*  *-----------*
  */
  [_NUMPAD] = {{ KC_7,    KC_8,    KC_9    }, { KC_4,    LAYER1,  KC_6    }, {KC_1,    KC_2,    KC_3    }, { XXXXXXX, XXXXXXX, KC_0    }},
  [_MACROS] = {{ EMAIL,   ADDRESS, XXXXXXX }, { XXXXXXX, XXXXXXX, XXXXXXX }, {XXXXXXX, XXXXXXX, XXXXXXX }, { XXXXXXX, XXXXXXX, F(0)   }}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case EMAIL:
        SEND_STRING("nick.christus@gmail.com");
        return false;
      case ADDRESS:
        SEND_STRING("9705 N Virginia Ave\nKansas City MO 64155");
        return false;
    }
  }
  return true;
}

const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_FUNCTION(0),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case 0:
    if (record->event.pressed) {
      SEND_STRING ("Keyboard: " QMK_KEYBOARD " / QMK Version: " QMK_VERSION " / Keymap: " QMK_KEYMAP "");
    }
    break;
  }
}
