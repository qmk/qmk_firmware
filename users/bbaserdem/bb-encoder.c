/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "bb-encoder.h"

// Need this to call velocikey activation
#ifdef VELOCIKEY_ENABLE
#   include "velocikey.h"
#endif // VELOCIKEY_ENABLE
// Need memcpy and memcmp from string.h along with transfer stuff
#ifdef OLED_ENABLE
#   include <string.h>
#endif // OLED_ENABLE

/* ROTARY ENCODER
 * This contains my general rotary encoder code
 * Encoders each have a list of different modes they can be in.
 * Each mode also have an on click action as well.
 * Modes can be cycled using either shift-click or ctrl-click
 * Modes can be reset using OS click
 * Some modes are only accessible through some keymap layers
 */

// Default state for the encoders
void reset_encoder_state(void) {
    userspace_config.e0base = 0;
    userspace_config.e0point = 0;
    userspace_config.e0rgb = 0;
    userspace_config.e1base = 1;
    userspace_config.e1point = 1;
    userspace_config.e1rgb = 1;
}

// Encoder scroll functionality
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t this_number;
    // Differentiate layer roles
    switch (get_highest_layer(layer_state)) {
#       ifdef RGB_MATRIX_ENABLE
        case _MEDI:
            // Get correct index
            if (index == 0) {
                this_number = userspace_config.e0rgb;
            } else if (index == 1) {
                this_number = userspace_config.e1rgb;
            } else {
                this_number = 128;
            }
            switch(this_number) {
                case 0: // Effect the RGB mode
                    if (clockwise) {
                        rgb_matrix_step_noeeprom();
                    } else {
                        rgb_matrix_step_reverse_noeeprom();
                    }
                    break;
                case 1: // Effect the RGB hue
                    if (clockwise) {
                        rgb_matrix_increase_hue_noeeprom();
                    } else {
                        rgb_matrix_decrease_hue_noeeprom();
                    }
                    break;
                case 2: // Effect the RGB saturation
                    if (clockwise) {
                        rgb_matrix_increase_sat_noeeprom();
                    } else {
                        rgb_matrix_decrease_sat_noeeprom();
                    }
                    break;
                case 3: // Effect the RGB brightness
                    if (clockwise) {
                        rgb_matrix_increase_val_noeeprom();
                    } else {
                        rgb_matrix_decrease_val_noeeprom();
                    }
                    break;
                case 4: // Effect the RGB effect speed
                    if (clockwise) {
                        rgb_matrix_increase_speed_noeeprom();
                    } else {
                        rgb_matrix_decrease_speed_noeeprom();
                    }
                    break;
            }
            break;
#       endif // RGB_MATRIX_ENABLE
#       ifdef MOUSEKEY_ENABLE
        case _MOUS:
            // Get correct index
            if (index == 0) {
                this_number = userspace_config.e0point;
            } else if (index == 1) {
                this_number = userspace_config.e1point;
            } else {
                this_number = 128;
            }
            switch(this_number) {
                case 0: // Move mouse on horizontal axis
                    if (clockwise) {
                        tap_code(KC_MS_R);
                    } else {
                        tap_code(KC_MS_L);
                    }
                    break;
                case 1: // Move mouse on vertical axis
                    if (clockwise) {
                        tap_code(KC_MS_D);
                    } else {
                        tap_code(KC_MS_U);
                    }
                    break;
                case 2: // Move mouse wheel on vertical axis
                    if (clockwise) {
                        tap_code(KC_WH_D);
                    } else {
                        tap_code(KC_WH_U);
                    }
                    break;
                case 3: // Move mouse on horizontal axis
                    if (clockwise) {
                        tap_code(KC_WH_R);
                    } else {
                        tap_code(KC_WH_L);
                    }
                    break;
            }
            break;
#       endif // MOUSEKEY_ENABLE
        default:
            // Get correct index
            if (index == 0) {
                this_number = userspace_config.e0base;
            } else if (index == 1) {
                this_number = userspace_config.e1base;
            } else {
                this_number = 128;
            }
            switch(this_number) {
                case 0: // Volume
                    if (clockwise) {
                        tap_code16(KC_VOLU);
                    } else {
                        tap_code16(KC_VOLD);
                    }
                    break;
                case 1: // Song change
                    if (clockwise) {
                        tap_code16(KC_MNXT);
                    } else {
                        tap_code16(KC_MPRV);
                    }
                    break;
                case 2: // Move to audio sink
                    if (clockwise) {
                        tap_code16(KC_F13);
                    } else {
                        tap_code16(S(KC_F13));
                    }
                    break;
                case 3: // Volume of source
                    if (clockwise) {
                        tap_code16(S(KC_VOLU));
                    } else {
                        tap_code16(C(KC_VOLD));
                    }
                    break;
                case 4: // Move to audio source
                    if (clockwise) {
                        tap_code16(C(KC_F13));
                    } else {
                        tap_code16(C(S(KC_F13)));
                    }
                    break;
                case 5: // Left-right
                    if (clockwise) {
                        tap_code16(KC_RGHT);
                    } else {
                        tap_code16(KC_LEFT);
                    }
                    break;
                case 6: // Up-down
                    if (clockwise) {
                        tap_code16(KC_DOWN);
                    } else {
                        tap_code16(KC_UP);
                    }
                    break;
                case 7: // Page Up-down
                    if (clockwise) {
                        tap_code16(KC_PGDN);
                    } else {
                        tap_code16(KC_PGUP);
                    }
                    break;
                case 8: // Delete 
                    if (clockwise) {
                        tap_code16(KC_DEL);
                    } else {
                        tap_code16(KC_BSPC);
                    }
                    break;
            }
            break;
    }
    return false;
}

void encoder_click_action(uint8_t index) {
    uint8_t this_number;
    // Differentiate layer roles
    switch (get_highest_layer(layer_state)) {
#       ifdef RGB_MATRIX_ENABLE
        case _MEDI:
            // Get correct index
            if (index == 0) {
                this_number = userspace_config.e0rgb;
            } else if (index == 1) {
                this_number = userspace_config.e1rgb;
            } else {
                this_number = 128;
            }
            switch(this_number) {
                case 0: // Return to no animation
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                    break;
                case 1:
                case 2:
                case 3: // Toggle
                    rgb_matrix_increase_val_noeeprom();
                    break;
                case 4: // Toggle velocikey
#                   ifdef VELOCIKEY_ENABLE
                    velocikey_toggle();
#                   endif // VELOCIKEY_ENABLE
                    break;
            }
            break;
#       endif // RGB_MATRIX_ENABLE
#       ifdef MOUSEKEY_ENABLE
        case _MOUS:
            // Get correct index
            if (index == 0) {
                this_number = userspace_config.e0point;
            } else if (index == 1) {
                this_number = userspace_config.e1point;
            } else {
                this_number = 128;
            }
            switch(this_number) {
                case 0: // Left click
                    tap_code16(KC_BTN1);
                    break;
                case 1: // Right click
                    tap_code16(KC_BTN2);
                    break;
                case 2:
                case 3: // Middle click
                    tap_code16(KC_BTN2);
                    break;
            }
            break;
#       endif // MOUSEKEY_ENABLE
        default:
            // Get correct index
            if (index == 0) {
                this_number = userspace_config.e0base;
            } else if (index == 1) {
                this_number = userspace_config.e1base;
            } else {
                this_number = 128;
            }
            switch(this_number) {
                case 0: // Toggle mute
                case 2:
                    tap_code16(KC_MUTE);
                    break;
                case 1: // Pause
                    tap_code16(KC_MPLY);
                    break;
                case 3: // Mute source
                case 4:
                    tap_code16(A(KC_MUTE));
                    break;
                case 5: // Insert
                    tap_code16(KC_INS);
                    break;
                case 6: // Capslock
                    tap_code16(KC_CAPS);
                    break;
                case 7: // Redo
                    tap_code16(BB_REDO);
                    break;
                case 8: // Undo
                    tap_code16(BB_UNDO);
                    break;
            }
            break;
    }
}

bool process_record_encoder(uint16_t keycode, keyrecord_t *record) {
    // Check if and which encoder
    int encoder_index = -1;
    
    // Get the pressed encoder
    switch (keycode) {
        case BB_ENC0:
            encoder_index = 0;
            break;
        case BB_ENC1:
            encoder_index = 1;
            break;
    }

    // Activate encoder function of button
    if ((encoder_index >= 0) & (!record->event.pressed)) {
        // If shifted, move mode one point forward
        if (get_mods() & MOD_MASK_SHIFT) {
            switch (get_highest_layer(layer_state)) {
#               ifdef RGB_MATRIX_ENABLE
                case _MEDI:
                    if (encoder_index == 0) {
                        userspace_config.e0rgb = (userspace_config.e0rgb + 1) % 5;
                    } else {
                        userspace_config.e1rgb = (userspace_config.e1rgb + 1) % 5;
                    }
                    break;
#               endif // RGB_MATRIX_ENABLE
#               ifdef MOUSEKEY_ENABLE
                case _MOUS:
                    if (encoder_index == 0) {
                        userspace_config.e0point = (userspace_config.e0point + 1) % 4;
                    } else {
                        userspace_config.e1point = (userspace_config.e1point + 1) % 4;
                    }
                    break;
#               endif // MOUSEKEY_ENABLE
                default:
                    if (encoder_index == 0) {
                        userspace_config.e0base = (userspace_config.e0base + 1) % 9;
                    } else {
                        userspace_config.e1base = (userspace_config.e1base + 1) % 9;
                    }
                    break;
            }
        // If ctrl is active, move mode one point backwards
        } else if (get_mods() & MOD_MASK_CTRL) {
            switch (get_highest_layer(layer_state)) {
#               ifdef RGB_MATRIX_ENABLE
                case _MEDI:
                    if (encoder_index == 0) {
                        userspace_config.e0rgb = (userspace_config.e0rgb + 5 - 1) % 5;
                    } else {
                        userspace_config.e1rgb = (userspace_config.e1rgb + 5 - 1) % 5;
                    }
                    break;
#               endif // RGB_MATRIX_ENABLE
#               ifdef MOUSEKEY_ENABLE
                case _MOUS:
                    if (encoder_index == 0) {
                        userspace_config.e0point = (userspace_config.e0point + 4 - 1) % 4;
                    } else {
                        userspace_config.e1point = (userspace_config.e1point + 4 - 1) % 4;
                    }
                    break;
#               endif // MOUSEKEY_ENABLE
                default:
                    if (encoder_index == 0) {
                        userspace_config.e0base = (userspace_config.e0base + 9 - 1) % 9;
                    } else {
                        userspace_config.e1base = (userspace_config.e1base + 9 - 1) % 9;
                    }
                    break;
            }
        // If meta is active, reset the encoder states
        } else if (get_mods() & MOD_MASK_GUI) {
            reset_encoder_state();
            eeconfig_update_user(userspace_config.raw);
        // If nothing else; just perform the click action
        } else {
            encoder_click_action(encoder_index);
        }
    }
    return true;
}

// For printing status to OLED
#ifdef OLED_ENABLE
void encoder_state_string(uint8_t index, uint8_t layer, char* buffer) {
    uint8_t this_number;
    // Get the layer straight from the main function
    switch (layer) {
        // If RGB control mode is enabled
#       ifdef RGB_MATRIX_ENABLE
        case _MEDI:
            // Get correct index
            if (index == 0) {
                this_number = userspace_config.e0rgb;
            } else if (index == 1) {
                this_number = userspace_config.e1rgb;
            } else {
                this_number = 128;
            }
            switch (this_number) {
                case 0:
                    strcpy(buffer, "ani mode");
                    break;
                case 1:
                    strcpy(buffer, "hue     ");
                    break;
                case 2:
                    strcpy(buffer, "saturat.");
                    break;
                case 3:
                    strcpy(buffer, "bright. ");
                    break;
                case 4:
                    strcpy(buffer, "ani. spd");
                    break;
                default:
                    strcpy(buffer, " -N/A-  ");
                    break;
            }
            break;
#       endif // RGB_MATRIX_ENABLE
        // If pointer control is enabled
#       ifdef MOUSEKEY_ENABLE
        case _MOUS:
            // Get correct index
            if (index == 0) {
                this_number = userspace_config.e0point;
            } else if (index == 1) {
                this_number = userspace_config.e1point;
            } else {
                this_number = 128;
            }
            switch (this_number) {
                case 0:
                    strcpy(buffer, "Lateral ");
                    break;
                case 1:
                    strcpy(buffer, "Vertical");
                    break;
                case 2:
                    strcpy(buffer, "Scr. Ver");
                    break;
                case 3:
                    strcpy(buffer, "Scr. Lat");
                    break;
                default:
                    strcpy(buffer, " -N/A-  ");
                    break;
            }
            break;
#       endif // MOUSEKEY_ENABLE
        default:
            // Get correct index
            if (index == 0) {
                this_number = userspace_config.e0base;
            } else if (index == 1) {
                this_number = userspace_config.e1base;
            } else {
                this_number = 128;
            }
            switch (this_number) {
                case 0:
                    strcpy(buffer, "Volume  ");
                    break;
                case 1:
                    strcpy(buffer, "Song    ");
                    break;
                case 2:
                    strcpy(buffer, "Sink    ");
                    break;
                case 3:
                    strcpy(buffer, "Src. Vol");
                    break;
                case 4:
                    strcpy(buffer, "Source  ");
                    break;
                case 5:
                    strcpy(buffer, "Arrow LR");
                    break;
                case 6:
                    strcpy(buffer, "Arrow UD");
                    break;
                case 7:
                    strcpy(buffer, "Page U/D");
                    break;
                case 8:
                    strcpy(buffer, "Erase   ");
                    break;
                default:
                    strcpy(buffer, " -N/A-  ");
                    break;
            }
            break;
    }
}
#endif // OLED_ENABLE
