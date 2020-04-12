/* Copyright 2020 Michele Ferri <zomgsako@gmail.com>
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
#include "paddino03.h"
#include "tmk_core/common/eeprom.h"
#include "print.h"

void keyboard_pre_init_kb(void) {
  // Set the layer LED IO as outputs
  setPinOutput(LAYER_INDICATOR_LED_0);
  setPinOutput(LAYER_INDICATOR_LED_1);
  setPinOutput(LAYER_INDICATOR_LED_2);
  setPinOutput(LAYER_INDICATOR_LED_3);
  keyboard_pre_init_user();
}

void shutdown_user() {
  // Shutdown all layer LEDs
  writePinLow(LAYER_INDICATOR_LED_0);
  writePinLow(LAYER_INDICATOR_LED_1);
  writePinLow(LAYER_INDICATOR_LED_2);
  writePinLow(LAYER_INDICATOR_LED_3);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
  // Turn on LED of current layer
  uint8_t layer = biton32(state);
  writePin(LAYER_INDICATOR_LED_0, layer == 0);
  writePin(LAYER_INDICATOR_LED_1, layer == 1);
  writePin(LAYER_INDICATOR_LED_2, layer == 2);
  writePin(LAYER_INDICATOR_LED_3, layer == 3);
  return layer_state_set_user(state);
}

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  for (int i = 0; i < 4; i++) {
    writePin(LAYER_INDICATOR_LED_0, true);
    writePin(LAYER_INDICATOR_LED_1, false);
    writePin(LAYER_INDICATOR_LED_2, false);
    writePin(LAYER_INDICATOR_LED_3, false);
    wait_ms(100);
    writePin(LAYER_INDICATOR_LED_0, false);
    writePin(LAYER_INDICATOR_LED_1, true);
    writePin(LAYER_INDICATOR_LED_2, false);
    writePin(LAYER_INDICATOR_LED_3, false);
    wait_ms(100);
    writePin(LAYER_INDICATOR_LED_0, false);
    writePin(LAYER_INDICATOR_LED_1, false);
    writePin(LAYER_INDICATOR_LED_2, true);
    writePin(LAYER_INDICATOR_LED_3, false);
    wait_ms(100);
    writePin(LAYER_INDICATOR_LED_0, false);
    writePin(LAYER_INDICATOR_LED_1, false);
    writePin(LAYER_INDICATOR_LED_2, false);
    writePin(LAYER_INDICATOR_LED_3, true);
    wait_ms(100);
  }

  writePin(LAYER_INDICATOR_LED_0, true);
  writePin(LAYER_INDICATOR_LED_1, false);
  writePin(LAYER_INDICATOR_LED_2, false);
  writePin(LAYER_INDICATOR_LED_3, false);

  matrix_init_user();
}

uint8_t selected_layer = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ENCODER_PRESS:
      if (record->event.pressed) {
        // Do something when pressed
      } else {
        // Do something else when release
        if (selected_layer < 3) {
            selected_layer ++;
        }
        else {
            selected_layer = 0;
        }
        layer_move(selected_layer);
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

void encoder_update_kb(uint8_t index, bool clockwise) {
    uint16_t keycode = get_encoder_key(clockwise ? ENCODER_CW : ENCODER_CCW);
    tap_code(keycode);
}

uint16_t get_encoder_key(uint8_t rotation) {
    // TODO look for the mapped keycode on this layer
    uint16_t keycode = 0;
    switch (rotation) {
        case ENCODER_CW:
            keycode = KC_AUDIO_VOL_UP;
            break;
            // TODO get keycode at row0, col8
        default:
            keycode = KC_AUDIO_VOL_DOWN;
            break;
            // TODO get keycode at row0, col7
    }
    return keycode;
}

void raw_hid_receive_kb( uint8_t *data, uint8_t length )
{
  uint8_t *command_id = &(data[0]);
  uint8_t *command_data = &(data[1]);

  print("inside raw_hid_receive_kb\n");
  xprintf("%d command_id\n", command_id);
  xprintf("%d command_data\n", command_data);

  switch ( *command_id )
  {
    case id_get_keyboard_value:
    {
        switch(command_data[0]) {
            case 0: {
                uint16_t keycode = get_custom_encoder_config(ENCODER_CW);
                command_data[2] =  keycode >> 8;
                command_data[3] = keycode & 0xFF;
                keycode = get_custom_encoder_config(ENCODER_CCW);
                command_data[4] =  keycode >> 8;
                command_data[5] = keycode & 0xFF;
                break;
            }
            default: {
                *command_id = id_unhandled;
                break;
            }
        }
        break;
    }
    case id_set_keyboard_value:
    {
      switch(command_data[0]) {
        case 0: {
          uint8_t rotation = command_data[2];
          uint16_t keycode = (command_data[3] << 8) | command_data[4];
          set_custom_encoder_config(rotation, keycode);
          break;
        }
        default: {
          *command_id = id_unhandled;
          break;
        }
      }
      break;
    }
    default:
    {
      // Unhandled message.
      *command_id = id_unhandled;
      break;
    }
  }
  // DO NOT call raw_hid_send(data,length) here, let caller do this
}

uint16_t get_custom_encoder_config(uint8_t rotation){
    void* addr = (void*)(EEPROM_ENCODER_VALUES + (selected_layer * 4) + (rotation * 2));
    //big endian
    uint16_t keycode = eeprom_read_byte(addr) << 8;
    keycode |= eeprom_read_byte(addr + 1);
    return keycode;
}

void set_custom_encoder_config(uint8_t rotation, uint16_t new_code){
    void* addr = (void*)(EEPROM_ENCODER_VALUES + (selected_layer * 4) + (rotation * 2));
    eeprom_update_byte(addr, (uint8_t)(new_code >> 8));
    eeprom_update_byte(addr + 1, (uint8_t)(new_code & 0xFF));
}
