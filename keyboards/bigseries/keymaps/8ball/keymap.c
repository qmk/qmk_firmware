/*
Copyright 2018 Cole Markham

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../../bigseries.h"

static const char * const ANSWERS[] = {
// "Yes" answers
"It is certain\n",
"It is decidedly so\n",
"Without a doubt\n",
"Yes definitely\n",
"You may rely on it\n",
"As I see it, yes\n",
"Most likely\n",
"Outlook good\n",
"Yes\n",
"Signs point to yes\n",
// Uncertain answers, index 10
"Reply hazy try again\n",
"Ask again later\n",
"Better not tell you now\n",
"Cannot predict now\n",
"Concentrate and ask again\n",
// "No" answers, index 15
"Don't count on it\n",
"My reply is no\n",
"My sources say no\n",
"Outlook not so good\n",
"Very doubtful\n"
};

#define UNCERTAIN_BREAK 10
#define NO_BREAK 15
#define NUM_ANSWERS 20
// Timeout of answer color in ms
#define ANSWER_TIMEOUT 3000

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

KEYMAP(
    KC_A),
};


void reset_rgb(void);

bool initialized = 0;
uint32_t lastTime = 0;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE ;
}

void matrix_init_user(void) {
  if (!initialized){
      dprintf("Initializing in matrix_scan_user");
      rgblight_enable();
      reset_rgb();
      initialized = 1;
    }
}

void matrix_scan_user(void) {
  if (lastTime > 0 && timer_elapsed32(lastTime) > ANSWER_TIMEOUT) {
    lastTime = 0;
    reset_rgb();
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_A:
    if (record->event.pressed) {
      uint8_t num = rand() / (RAND_MAX / NUM_ANSWERS + 1);
      rgblight_mode(1);
      if (num < UNCERTAIN_BREAK) {
        rgblight_setrgb_green();
      } else if (num < NO_BREAK) {
        rgblight_setrgb_yellow();
      } else {
        rgblight_setrgb_red();
      }
      send_string(ANSWERS[num]);
      lastTime = timer_read32();
      return false;
    }
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_COMPOSE)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_KANA)) {

  } else {

  }

}

void reset_rgb(void) {
  // This gets called on init and after the timeout for the answer color
  // If you want to change the default color/mode, do it here
  rgblight_sethsv_blue();
  rgblight_mode(7);
}
