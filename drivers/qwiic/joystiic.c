/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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
#include "joystiic.h"
#include "print.h"
#include "action.h"

#define JOYSTIIC_DEFAULT_ADDR       0x20
#define JOYSTIIC_COMMAND_HORIZONTAL 0x00
#define JOYSTIIC_COMMAND_VERTICAL   0x02
#define JOYSTIIC_COMMAND_BUTTON     0x04

#define JOYSTIIC_CENTER 512
#define JOYSTIIC_DEADZONE 200

uint16_t joystiic_horizontal;
uint16_t joystiic_vertical;
bool joystiic_button;

uint8_t joystiic_tx[1];
uint8_t joystiic_rx_horizontal[2];
uint8_t joystiic_rx_vertical[2];
uint8_t joystiic_rx_button[1];

enum {
  JOYSTIIC_LEFT,
  JOYSTIIC_RIGHT,
  JOYSTIIC_UP,
  JOYSTIIC_DOWN,
  JOYSTIIC_PRESS
};

bool joystiic_triggered[5] = {0};

void joystiic_init(void) {
  i2c_init();
  i2c_start(JOYSTIIC_DEFAULT_ADDR);
}

void joystiic_update(uint16_t horizontal, uint16_t vertical, bool button) {
  joystiic_update_kb(horizontal, vertical, button);
  joystiic_update_user(horizontal, vertical, button);
}

void joystiic_update_kb(uint16_t horizontal, uint16_t vertical, bool button) {

}

void joystiic_update_user(uint16_t horizontal, uint16_t vertical, bool button) {

}

void joystiic_trigger(uint8_t trigger, bool active) {
  joystiic_trigger_kb(trigger, active);
  joystiic_trigger_user(trigger, active);
}

void joystiic_trigger_kb(uint8_t trigger, bool active) {
  switch (trigger) {
    case JOYSTIIC_LEFT: active ? register_code(KC_L) : unregister_code(KC_L); break;
  }
}

void joystiic_trigger_user(uint8_t trigger, bool active) {

}

void joystiic_task(void) {
  // get horizontal axis
  joystiic_tx[0] = JOYSTIIC_COMMAND_HORIZONTAL;

  if (MSG_OK != i2c_transmit_receive(JOYSTIIC_DEFAULT_ADDR << 1,
    joystiic_tx, 1,
    joystiic_rx_horizontal, 2
  )) {
    printf("error hori\n");
  }

  joystiic_horizontal = ((uint16_t)joystiic_rx_horizontal[0] << 8) | joystiic_rx_horizontal[1];

  if (joystiic_horizontal > (JOYSTIIC_CENTER + JOYSTIIC_DEADZONE)) {
    if (!joystiic_triggered[JOYSTIIC_LEFT]) {
      joystiic_triggered[JOYSTIIC_LEFT] = true;
      joystiic_trigger(JOYSTIIC_LEFT, true);
    }
  } else {
    if (joystiic_triggered[JOYSTIIC_LEFT]) {
      joystiic_triggered[JOYSTIIC_LEFT] = false;
      joystiic_trigger(JOYSTIIC_LEFT, false);
    }
  }

  if (joystiic_horizontal < (JOYSTIIC_CENTER - JOYSTIIC_DEADZONE)) {
    if (!joystiic_triggered[JOYSTIIC_RIGHT]) {
      joystiic_triggered[JOYSTIIC_RIGHT] = true;
      joystiic_trigger(JOYSTIIC_RIGHT, true);
    }
  } else {
    if (joystiic_triggered[JOYSTIIC_RIGHT]) {
      joystiic_triggered[JOYSTIIC_RIGHT] = false;
      joystiic_trigger(JOYSTIIC_RIGHT, false);
    }
  }

  // get vertical axis
  joystiic_tx[0] = JOYSTIIC_COMMAND_VERTICAL;
  if (MSG_OK != i2c_transmit_receive(JOYSTIIC_DEFAULT_ADDR << 1,
    joystiic_tx, 1,
    joystiic_rx_vertical, 2
  )) {
    printf("error vert\n");
  }

  joystiic_vertical = ((uint16_t)joystiic_rx_vertical[0] << 8) | joystiic_rx_vertical[1];

  if (joystiic_vertical > (JOYSTIIC_CENTER + JOYSTIIC_DEADZONE)) {
    if (!joystiic_triggered[JOYSTIIC_UP]) {
      joystiic_triggered[JOYSTIIC_UP] = true;
      joystiic_trigger(JOYSTIIC_UP, true);
    }
  } else {
    if (joystiic_triggered[JOYSTIIC_UP]) {
      joystiic_triggered[JOYSTIIC_UP] = false;
      joystiic_trigger(JOYSTIIC_UP, false);
    }
  }

  if (joystiic_vertical < (JOYSTIIC_CENTER - JOYSTIIC_DEADZONE)) {
    if (!joystiic_triggered[JOYSTIIC_DOWN]) {
      joystiic_triggered[JOYSTIIC_DOWN] = true;
      joystiic_trigger(JOYSTIIC_DOWN, true);
    }
  } else {
    if (joystiic_triggered[JOYSTIIC_DOWN]) {
      joystiic_triggered[JOYSTIIC_DOWN] = false;
      joystiic_trigger(JOYSTIIC_DOWN, false);
    }
  }

  // get button press
  joystiic_tx[0] = JOYSTIIC_COMMAND_BUTTON;
  if (MSG_OK != i2c_transmit_receive(JOYSTIIC_DEFAULT_ADDR << 1,
    joystiic_tx, 1,
    joystiic_rx_button, 1
  )) {
    printf("error vert\n");
  }

  joystiic_button = joystiic_rx_button[0];

  if (joystiic_button) {
    if (!joystiic_triggered[JOYSTIIC_PRESS]) {
      joystiic_triggered[JOYSTIIC_PRESS] = true;
      joystiic_trigger(JOYSTIIC_PRESS, true);
    }
  } else {
    if (joystiic_triggered[JOYSTIIC_PRESS]) {
      joystiic_triggered[JOYSTIIC_PRESS] = false;
      joystiic_trigger(JOYSTIIC_PRESS, false);
    }
  }

  joystiic_update(joystiic_horizontal, joystiic_vertical, joystiic_button);

  //printf("%d\n", joystiic[0]);

  // SEND_STRING("H: ");
  // send_word(joystiic_rx_horizontal[0]);
  // tap_code(KC_SPACE);
  // send_word(joystiic_rx_horizontal[1]);
  // tap_code(KC_SPACE);
}
