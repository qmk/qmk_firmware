/* Copyright 2017 Mathias Andersson <wraul@dbox.se>
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
#include "tkc1800.h"
#include "LUFA/Drivers/Peripheral/TWI.h"
#include "i2c.h"
#include "ssd1306.h"

#define MODS_SHFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)|MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))
#define MODS_GUI_MASK   (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))

// Custom macros
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define HPR_TAB     ALL_T(KC_TAB)               // Tap for Tab, hold for Hyper (Super+Ctrl+Shift+Alt)
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift

// Helpful defines
#define ______ KC_TRNS
#define XXXXXX KC_NO

//Layers

enum {
	QWERTY = 0,
	COLEMAK,
	DVORAK,
	FUNCTION,
};

//13 characters max without re-writing the "Layer: " format in iota_gfx_task_user()
static char layer_lookup[][14] = {"Qwerty","Dvorak","Function"};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap QWERTY: (Qwerty Layer) Default Layer
   * ,-------------------------------------------------------.     ,-------------------.
   * |Esc| F1| F2| F3| F4| | F5| F6| F7| F8| | F9|F10|F11|F12|     |Ins |Home|PgUp|PrSc|
   * `-------------------------------------------------------'     |-------------------|
   *                                                               |Del |End |PgDn|ScrL|
   * ,-----------------------------------------------------------. |-------------------|
   * | ~ | 1 |  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |NumL| /  | *  |Paus|
   * |-----------------------------------------------------------| |-------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | | 7  | 8  | 9  | -  |
   * |-----------------------------------------------------------| |-------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return | | 4  | 5  | 6  | +  |
   * |-----------------------------------------------------------' |-------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift  | Up | 1  | 2  | 3  | Ent|
   * |--------------------------------------------------------'----`--------------|    |
   * |Ctrl|Gui |Alt |      Space           |Alt |Gui|Ctr|Left |Down|Rght| 0  | .  |    |
   * `---------------------------------------------------------------------------------'
   */
	[QWERTY] = LAYOUT(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_HOME, KC_PGUP, KC_PSCR, \
		                                                                                               KC_DEL, KC_END,  KC_PGDN, KC_SLCK, \
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV, KC_NLCK, KC_PSLS, KC_PAST, KC_PAUS, \
		HPR_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, KC_P7, KC_P8, KC_P9, KC_PMNS, \
		CTL_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, XXXXXX, KC_ENT, KC_P4, KC_P5, KC_P6, KC_PPLS, \
		KC_LSFT, XXXXXX, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,KC_SLSH, SFT_ENT, KC_UP, KC_P1, KC_P2, KC_P3, XXXXXX, \
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(FUNCTION), KC_RCTL,                KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PENT
	),
  /* Keymap COLEMAK: (Colemak Layer) Default Layer
   * ,-------------------------------------------------------.     ,-------------------.
   * |Esc| F1| F2| F3| F4| | F5| F6| F7| F8| | F9|F10|F11|F12|     |Ins |Home|PgUp|PrSc|
   * `-------------------------------------------------------'     |-------------------|
   *                                                               |Del |End |PgDn|ScrL|
   * ,-----------------------------------------------------------. |-------------------|
   * | ~ | 1 |  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |NumL| /  | *  |Paus|
   * |-----------------------------------------------------------| |-------------------|
   * |Tab  |  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]|  \  | | 7  | 8  | 9  | -  |
   * |-----------------------------------------------------------| |-------------------|
   * |CAPS   |  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '|Return | | 4  | 5  | 6  | +  |
   * |-----------------------------------------------------------' |-------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  K|  M|  ,|  .|  /|Shift  | Up | 1  | 2  | 3  | Ent|
   * |--------------------------------------------------------'----`--------------|    |
   * |Ctrl|Gui |Alt |      Space           |Alt |Gui|Ctr|Left |Down|Rght| 0  | .  |    |
   * `---------------------------------------------------------------------------------'
   */
	[COLEMAK] = LAYOUT(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_HOME, KC_PGUP, KC_PSCR, \
		                                                                                               KC_DEL, KC_END,  KC_PGDN, KC_SLCK, \
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV, KC_NLCK, KC_PSLS, KC_PAST, KC_PAUS, \
		HPR_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y,  KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC, KC_P7, KC_P8, KC_P9, KC_PMNS, \
		CTL_ESC, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, XXXXXX, KC_ENT, KC_P4, KC_P5, KC_P6, KC_PPLS, \
		KC_LSFT, XXXXXX, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT,KC_SLSH, SFT_ENT, KC_UP, KC_P1, KC_P2, KC_P3, XXXXXX, \
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(FUNCTION), KC_RCTL,                KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PENT
	),
  /* Keymap DVORAK: (Dvorak Layer) Default Layer
   * ,-------------------------------------------------------.     ,-------------------.
   * |Esc| F1| F2| F3| F4| | F5| F6| F7| F8| | F9|F10|F11|F12|     |Ins |Home|PgUp|PrSc|
   * `-------------------------------------------------------'     |-------------------|
   *                                                               |Del |End |PgDn|ScrL|
   * ,-----------------------------------------------------------. |-------------------|
   * | ~ | 1 |  2|  3|  4|  5|  6|  7|  8|  9|  0|  [|  ]|  \| ~ | |NumL| /  | *  |Paus|
   * |-----------------------------------------------------------| |-------------------|
   * |Tab  |  '|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|  BS | | 7  | 8  | 9  | -  |
   * |-----------------------------------------------------------| |-------------------|
   * |CAPS   |  A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -|Return | | 4  | 5  | 6  | +  |
   * |-----------------------------------------------------------' |-------------------|
   * |Shift   |  ;|  Q|  J|  K|  X|  B|  M|  W|  V|  Z|Shift  | Up | 1  | 2  | 3  | Ent|
   * |--------------------------------------------------------'----`--------------|    |
   * |Ctrl|Gui |Alt |      Space           |Alt |Gui|Ctr|Left |Down|Rght| 0  | .  |    |
   * `---------------------------------------------------------------------------------'
   */
	[DVORAK] = LAYOUT(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_HOME, KC_PGUP, KC_PSCR, \
		                                                                                               KC_DEL, KC_END,  KC_PGDN, KC_SLCK, \
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV, KC_NLCK, KC_PSLS, KC_PAST, KC_PAUS, \
		HPR_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, KC_EQL, KC_BSPC, KC_P7, KC_P8, KC_P9, KC_PMNS, \
		CTL_ESC, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, XXXXXX, KC_ENT, KC_P4, KC_P5, KC_P6, KC_PPLS, \
		KC_LSFT, XXXXXX, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, SFT_ENT, KC_UP, KC_P1, KC_P2, KC_P3, XXXXXX, \
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(FUNCTION), KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PENT
	),
	[FUNCTION] = LAYOUT(
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_INS, KC_HOME, KC_PGUP, KC_PSCR, \
		                                                                                                        KC_DEL, KC_END,  KC_PGDN, KC_SLCK, \
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, RESET, KC_NLCK, KC_PSLS, KC_PAST, KC_PAUS, \
		______, ______, ______, ______, ______, ______, ______, QWERTY, COLEMAK,DVORAK, ______, ______, ______, ______, KC_P7, KC_P8, KC_P9, KC_PMNS, \
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, XXXXXX, ______, KC_P4, KC_P5, KC_P6, KC_PPLS, \
		______, XXXXXX, RGB_TOG,RGB_MOD,RGB_HUI,RGB_HUD,RGB_SAI,RGB_SAD,RGB_VAI,RGB_VAD, BL_STEP,______, ______, KC_UP, KC_P1, KC_P2, KC_P3, XXXXXX, \
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, ______, KC_RCTL,                                  KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PENT
	),
};

// const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<DVORAK);
      }
      return false;
      break;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

}
void matrix_init_user(void) {
  #ifdef USE_I2C
    i2c_master_init();
  #ifdef SSD1306OLED
  // calls code for the SSD1306 OLED
        _delay_ms(400);
        TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
        iota_gfx_init();   // turns on the display
  #endif
  #endif
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

void matrix_scan_user(void) {
    #ifdef SSD1306OLED
     iota_gfx_task();  // this is what updates the display continuously
    #endif
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  struct CharacterMatrix matrix;

  matrix_clear(&matrix);
  matrix_write_P(&matrix, PSTR("TKC1800"));

  uint8_t layer = biton32(layer_state);

  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%d", layer);
  matrix_write_P(&matrix, PSTR("\nLayer: "));
  matrix_write(&matrix, layer_lookup[layer]);

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(&matrix, led);
  matrix_update(&display, &matrix);
}
