#include "the_ruler.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DEFAULT 0
#define _FN_1 1
#define _FN_2 2

enum custom_keycodes {
  DEFAULT = SAFE_RANGE,
  FN_1,
  FN_2
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Default Layer
 * ,-----------------------------------------------.
 * |  FN_2 |   2   |TSKMGR |CALTDEL|  ESC  |  FN_1 |
 * `-----------------------------------------------'
 */
[_DEFAULT] = KEYMAP( \
  MO(_FN_2), KC_2, TSKMGR, CALTDEL, KC_ESC, MO(_FN_1)
),

/* FN 1 Layer
 * ,-----------------------------------------------.
 * |RGB_TOG|RGB_HUD|RGB_HUI|RGB_SAD|RGB_SAI|  FN_1 |
 * `-----------------------------------------------'
 */
[_FN_1] = KEYMAP( \
  RGB_TOG, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, _______
),

/* FN 2 Layer
 * ,-----------------------------------------------.
 * |  FN_2 |RGB_VAD|RGB_VAI|RGB_MOD|TSKMGR | RESET |
 * `-----------------------------------------------'
 */
[_FN_2] = KEYMAP( \
  _______, RGB_VAD, RGB_VAI, RGB_MOD, TSKMGR, RESET
)

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // NONE
  }
  return true;
}