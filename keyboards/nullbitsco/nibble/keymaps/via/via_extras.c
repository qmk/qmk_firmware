/* Copyright 2020 Jay Greco
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

#include "via_extras.h"

// Encoder Behavior
extern uint8_t encoder_value;
extern uint8_t encoder_mode;
extern uint8_t enabled_encoder_modes;

void raw_hid_receive_kb( uint8_t *data, uint8_t length )
{
  uint8_t *command_id = &(data[0]);
  uint8_t *command_data = &(data[1]);
  dprintf("raw hid recv! command_id: %u\n",*command_id);
  switch ( *command_id )
  {
    case id_get_keyboard_value:
    {
      switch( command_data[0])
      {
        case id_encoder_modes:
        {
          command_data[1] = enabled_encoder_modes;
          dprintf("[read] enabled_encoder_modes: %u\n", enabled_encoder_modes);
        }
        break;

        case id_encoder_custom:
        {
          uint8_t custom_encoder_idx = command_data[1];
          uint16_t keycode = retrieve_custom_encoder_config(custom_encoder_idx, ENC_CUSTOM_CW);
          command_data[2] =  keycode >> 8;
          command_data[3] = keycode & 0xFF;
          keycode = retrieve_custom_encoder_config(custom_encoder_idx, ENC_CUSTOM_CCW);
          command_data[4] =  keycode >> 8;
          command_data[5] = keycode & 0xFF;
          keycode = retrieve_custom_encoder_config(custom_encoder_idx, ENC_CUSTOM_PRESS);
          command_data[6] =  keycode >> 8;
          command_data[7] = keycode & 0xFF;
        }
        break;

        default:
        {
          *command_id = id_unhandled;
        }
        break;
      }
    }
    break;
    case id_set_keyboard_value:
    {
      switch(command_data[0]){
        case id_encoder_modes:
        {
          enabled_encoder_modes = command_data[1];
          dprintf("[write] enabled_encoder_modes: %u\n", enabled_encoder_modes);
          eeprom_update_byte((uint8_t*)EEPROM_ENABLED_ENCODER_MODES, enabled_encoder_modes);
        }
        break;

        case id_encoder_custom:
        {
          uint8_t custom_encoder_idx = command_data[1];
          uint8_t encoder_behavior = command_data[2];
          uint16_t keycode = (command_data[3] << 8) | command_data[4];
          set_custom_encoder_config(custom_encoder_idx, encoder_behavior, keycode);
        }
        break;

        default:
        {
          *command_id = id_unhandled;
        }
        break;
      }
    }
    break;

    default:
    {
      // Unhandled message.
      *command_id = id_unhandled;
    }
    break;
  }
}

void encoder_update_kb(uint8_t index, bool clockwise) {
  if (layer_state_is(1)) {
    change_encoder_mode(clockwise);
    return;
  }
  uint16_t mapped_code = 0;
  if (clockwise) {
    mapped_code = handle_encoder_cw();
  } else {
    mapped_code = handle_encoder_ccw();
  }
  if(mapped_code != 0){
    tap_code16(mapped_code);
  }
}

void custom_config_load(void){
#ifdef DYNAMIC_KEYMAP_ENABLE
  enabled_encoder_modes = eeprom_read_byte((uint8_t*)EEPROM_ENABLED_ENCODER_MODES);
#endif
}

void via_init_kb(void)
{
  dprintf("VIA is enabled.\n");
  custom_config_load();
}
