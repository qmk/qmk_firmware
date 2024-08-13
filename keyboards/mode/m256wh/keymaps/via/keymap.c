/* Copyright 2022 Gondolindrim
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
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_65_ansi_blocker( /* Base */
    KC_ESC , KC_1   , KC_2   , KC_3   , KC_4  , KC_5    , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_DEL ,
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R  , KC_T    , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
    KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F  , KC_G    , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT , KC_PGDN,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V  , KC_B    , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, KC_UP  , KC_END ,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC ,                   KC_RALT, MO(1)  , KC_LEFT, KC_DOWN, KC_RGHT
),
[1] = LAYOUT_65_ansi_blocker(
    QK_BOOT, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_TRNS, KC_MUTE,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS 
)
};

bool is_second_rgb_row_active;

enum via_secondrow_enable {
    id_is_second_rgb_row_active = 0
};

// Sets the second RGB row on or off; done by setting effect range.
void set_second_rgb_row(bool is_active) {
    rgblight_disable_noeeprom();
    switch (is_active)
    {
        case true:
        {
            rgblight_set_effect_range(0,30);
            break;
        }
        case false:
        {
            rgblight_set_effect_range(0,15);
            break;
        }
    }
    rgblight_enable_noeeprom();
}

// At the keyboard start, retrieves PMEM stored configs
void keyboard_post_init_user(void) {
    rgblight_disable_noeeprom();
    wait_ms(20);
    eeconfig_read_user_datablock(&is_second_rgb_row_active);
    set_second_rgb_row(is_second_rgb_row_active);
    rgblight_reload_from_eeprom();
    rgblight_set();
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    // rgblight_disable(); // Enable RGB by default
    // Define the defualt value and write it to EEPROM
    is_second_rgb_row_active = true;
    set_second_rgb_row(is_second_rgb_row_active);
    eeconfig_update_user_datablock(&is_second_rgb_row_active);

    // Disable rgblight by default on EEPROM initialization
    rgblight_disable();
}

void secondrow_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_is_second_rgb_row_active:
        {
            is_second_rgb_row_active = (bool) *value_data;
            break;
        }
        default:
        {
            is_second_rgb_row_active = true;
        }
    }
    set_second_rgb_row(is_second_rgb_row_active);
}

void secondrow_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
         case id_is_second_rgb_row_active:
         {
             *value_data = is_second_rgb_row_active;
              break;
         }
         default:
         {
             *value_data = false;
         }
     }
}

void secondrow_config_save(void)
{
    eeconfig_update_user_datablock(&is_second_rgb_row_active);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id == id_custom_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                secondrow_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                secondrow_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                secondrow_config_save();
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}
