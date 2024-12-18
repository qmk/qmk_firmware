/* Copyright 2023 Acliad
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

#ifdef RGB_IDLE_ENABLE
typedef struct {
    uint8_t mode;
    uint8_t speed;
    HSV     hsv;
} rgb_matrix_state_t;

_Static_assert(sizeof(rgb_matrix_state_t) == 5, "Invalid size for rgb_matrix_state_t");

typedef struct {
    rgb_matrix_state_t active_rgb_matrix;
    rgb_matrix_state_t idle_rgb_matrix;
} kb_config_t;

_Static_assert(sizeof(kb_config_t) == EECONFIG_KB_DATA_SIZE, "Invalid size for kb_config_t");

bool                      rgb_idle_mode      = false;
bool                      rgb_idle_edit_mode = false;
static rgb_matrix_state_t active_rgb_matrix;
static rgb_matrix_state_t idle_rgb_matrix;
static kb_config_t        config;

// Returns true if current RGB matrix mode is idle
bool rgb_matrix_idle_mode(void) {
    return rgb_idle_mode;
}

// Stores the current mode, HSV, and speed of the RGB matrix into state
void rgb_matrix_state_save(rgb_matrix_state_t* state) {
    state->mode  = rgb_matrix_get_mode();
    state->hsv   = rgb_matrix_get_hsv();
    state->speed = rgb_matrix_get_speed();
}

// Restores the mode, HSV, and speed of the RGB matrix from previous state
void rgb_matrix_state_restore(rgb_matrix_state_t* state) {
    HSV hsv = state->hsv;
    rgb_matrix_mode_noeeprom(state->mode);
    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
    rgb_matrix_set_speed_noeeprom(state->speed);
}
#endif

void housekeeping_task_kb(void) {
#ifdef RGB_IDLE_ENABLE
    // Check if enough time has passed since last keypress to go into idle mode
    if (last_input_activity_elapsed() > RGB_IDLE_TIMEOUT_MS && !rgb_idle_mode) {
        rgb_matrix_state_save(&active_rgb_matrix);
        rgb_idle_mode = true;

        rgb_matrix_state_restore(&idle_rgb_matrix);
    }
#endif
};

layer_state_t layer_state_set_kb(layer_state_t state) {
#ifdef RGB_IDLE_ENABLE
    // Track if the last layer was the RGB edit layer
    static bool rgb_was_on = false;

    if (IS_LAYER_ON_STATE(state, LAYER_RGB)) {
        rgb_was_on = true;
    }

    // Not in RGB edit layer, but previously were
    if (!IS_LAYER_ON_STATE(state, LAYER_RGB) && rgb_was_on) {
        rgb_was_on = false;
        if (rgb_idle_edit_mode) {
            // If we were editing the RGB idle mode, we are done now.
            // Restore to active mode
            rgb_idle_edit_mode = false;
            rgb_matrix_state_restore(&active_rgb_matrix);
        }
        // Done changing stuff, save settings in "EEPROM"
        config.active_rgb_matrix = active_rgb_matrix;
        config.idle_rgb_matrix   = idle_rgb_matrix;
        eeconfig_update_kb_datablock(&config);
    }
#endif

    return layer_state_set_user(state);
}

// Process custom keycodes
bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
#ifdef RGB_IDLE_ENABLE
    // If we were idling and a key was pressed, restore active RGB
    if (record->event.pressed) {
        if (rgb_idle_mode) {
            rgb_matrix_state_restore(&active_rgb_matrix);
            rgb_idle_mode = false;
        }
    }
#endif

    switch (keycode) {
#ifdef RGB_IDLE_ENABLE
        // Handle all the RGB settings
        case RGB_DEF:
            if (record->event.pressed) {
                // Change the RGB matrix state to active if editing idle
                if (rgb_idle_edit_mode) {
                    rgb_matrix_state_restore(&active_rgb_matrix);
                    rgb_idle_edit_mode = false;
                }
                rgb_matrix_step_noeeprom();
                rgb_matrix_state_save(&active_rgb_matrix);
            }
            return false;
        case RGB_IEF:
            if (record->event.pressed) {
                // Change the RGB matrix state to idle
                if (!rgb_idle_edit_mode) {
                    rgb_matrix_state_restore(&idle_rgb_matrix);
                    rgb_idle_edit_mode = true;
                } else {
                    rgb_matrix_step_noeeprom();
                    rgb_matrix_state_save(&idle_rgb_matrix);
                }
            }
            return false;
        case RGB_SAI:
            if (record->event.pressed) {
                rgb_matrix_increase_sat_noeeprom();
                rgb_idle_edit_mode ? rgb_matrix_state_save(&idle_rgb_matrix) : rgb_matrix_state_save(&active_rgb_matrix);
            }
            return false;
        case RGB_SAD:
            if (record->event.pressed) {
                rgb_matrix_decrease_sat_noeeprom();
                rgb_idle_edit_mode ? rgb_matrix_state_save(&idle_rgb_matrix) : rgb_matrix_state_save(&active_rgb_matrix);
            }
            return false;
        case RGB_VAI:
            if (record->event.pressed) {
                rgb_matrix_increase_val_noeeprom();
                rgb_idle_edit_mode ? rgb_matrix_state_save(&idle_rgb_matrix) : rgb_matrix_state_save(&active_rgb_matrix);
            }
            return false;
        case RGB_VAD:
            if (record->event.pressed) {
                rgb_matrix_decrease_val_noeeprom();
                rgb_idle_edit_mode ? rgb_matrix_state_save(&idle_rgb_matrix) : rgb_matrix_state_save(&active_rgb_matrix);
            }
            return false;
        case RGB_HUI:
            if (record->event.pressed) {
                rgb_matrix_increase_hue_noeeprom();
                rgb_idle_edit_mode ? rgb_matrix_state_save(&idle_rgb_matrix) : rgb_matrix_state_save(&active_rgb_matrix);
            }
            return false;
        case RGB_HUD:
            if (record->event.pressed) {
                rgb_matrix_decrease_hue_noeeprom();
                rgb_idle_edit_mode ? rgb_matrix_state_save(&idle_rgb_matrix) : rgb_matrix_state_save(&active_rgb_matrix);
            }
            return false;
        case RGB_SPI:
            if (record->event.pressed) {
                rgb_matrix_increase_speed_noeeprom();
                rgb_idle_edit_mode ? rgb_matrix_state_save(&idle_rgb_matrix) : rgb_matrix_state_save(&active_rgb_matrix);
            }
            return false;
        case RGB_SPD:
            if (record->event.pressed) {
                rgb_matrix_decrease_speed_noeeprom();
                rgb_idle_edit_mode ? rgb_matrix_state_save(&idle_rgb_matrix) : rgb_matrix_state_save(&active_rgb_matrix);
            }
            return false;
#endif
    }
    return process_record_user(keycode, record);
};

void keyboard_post_init_kb(void) {
#ifdef RGB_IDLE_ENABLE
    // Read in the RGB Matrices from before
    eeconfig_read_kb_datablock(&config);
    active_rgb_matrix = config.active_rgb_matrix;
    idle_rgb_matrix   = config.idle_rgb_matrix;
    // Restore the active matrix
    rgb_matrix_state_restore(&active_rgb_matrix);
#endif

    keyboard_post_init_user();
}

// Setup default EEPROM config values
void eeconfig_init_kb_datablock(void) {
#ifdef RGB_IDLE_ENABLE
    rgb_matrix_state_t default_active_rgb_matrix;
    rgb_matrix_state_t default_idle_rgb_matrix;

    default_active_rgb_matrix.mode  = RGB_MATRIX_GRADIENT_UP_DOWN;
    default_active_rgb_matrix.hsv   = (HSV){127, 255, 100};
    default_active_rgb_matrix.speed = 127;

    default_idle_rgb_matrix.mode  = RGB_MATRIX_BREATHING;
    default_idle_rgb_matrix.hsv   = (HSV){127, 255, 100};
    default_idle_rgb_matrix.speed = 127;

    config.active_rgb_matrix = default_active_rgb_matrix;
    config.idle_rgb_matrix   = default_idle_rgb_matrix;

    eeconfig_update_kb_datablock(&config);

#    if (EECONFIG_USER_DATA_SIZE) > 0
    eeconfig_init_user_datablock();
#    endif // EECONFIG_USER_DATA_SIZE
#endif     // RGB_IDLE_ENABLE
}
