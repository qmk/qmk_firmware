/* Copyright 2019 Jason Williams (Wilba)
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

#ifndef RAW_ENABLE
#    error "RAW_ENABLE is not enabled"
#endif

#ifndef DYNAMIC_KEYMAP_ENABLE
#    error "DYNAMIC_KEYMAP_ENABLE is not enabled"
#endif

// If VIA_CUSTOM_LIGHTING_ENABLE is not defined, then VIA_QMK_BACKLIGHT_ENABLE is set
// if BACKLIGHT_ENABLE is set, so handling of QMK Backlight values happens here by default.
// if VIA_CUSTOM_LIGHTING_ENABLE is defined, then VIA_QMK_BACKLIGHT_ENABLE must be explicitly
// set in keyboard-level config.h, so handling of QMK Backlight values happens here
#if defined(BACKLIGHT_ENABLE) && !defined(VIA_CUSTOM_LIGHTING_ENABLE)
#    define VIA_QMK_BACKLIGHT_ENABLE
#endif

// If VIA_CUSTOM_LIGHTING_ENABLE is not defined, then VIA_QMK_RGBLIGHT_ENABLE is set
// if RGBLIGHT_ENABLE is set, so handling of QMK RGBLIGHT values happens here by default.
// If VIA_CUSTOM_LIGHTING_ENABLE is defined, then VIA_QMK_RGBLIGHT_ENABLE must be explicitly
// set in keyboard-level config.h, so handling of QMK RGBLIGHT values happens here
#if defined(RGBLIGHT_ENABLE) && !defined(VIA_CUSTOM_LIGHTING_ENABLE)
#    define VIA_QMK_RGBLIGHT_ENABLE
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(VIA_QMK_RGBLIGHT_ENABLE) && !defined(VIA_CUSTOM_LIGHTING_ENABLE)
#    define VIA_QMK_RGB_MATRIX_ENABLE
#endif

#include "quantum.h"

#include "via.h"

#include "raw_hid.h"
#include "dynamic_keymap.h"
#include "eeprom.h"
#include "version.h" // for QMK_BUILDDATE used in EEPROM magic
#include "via_ensure_keycode.h"

// Forward declare some helpers.
#if defined(VIA_QMK_BACKLIGHT_ENABLE)
void via_qmk_backlight_set_value(uint8_t *data);
void via_qmk_backlight_get_value(uint8_t *data);
#endif

#if defined(VIA_QMK_RGBLIGHT_ENABLE)
void via_qmk_rgblight_set_value(uint8_t *data);
void via_qmk_rgblight_get_value(uint8_t *data);
#endif

#if defined(VIA_QMK_RGB_MATRIX_ENABLE)
#    include <lib/lib8tion/lib8tion.h>
void via_qmk_rgb_matrix_set_value(uint8_t *data);
void via_qmk_rgb_matrix_get_value(uint8_t *data);
void eeconfig_update_rgb_matrix(void);
#endif

// Can be called in an overriding via_init_kb() to test if keyboard level code usage of
// EEPROM is invalid and use/save defaults.
bool via_eeprom_is_valid(void) {
    char *  p      = QMK_BUILDDATE; // e.g. "2019-11-05-11:29:54"
    uint8_t magic0 = ((p[2] & 0x0F) << 4) | (p[3] & 0x0F);
    uint8_t magic1 = ((p[5] & 0x0F) << 4) | (p[6] & 0x0F);
    uint8_t magic2 = ((p[8] & 0x0F) << 4) | (p[9] & 0x0F);

    return (eeprom_read_byte((void *)VIA_EEPROM_MAGIC_ADDR + 0) == magic0 && eeprom_read_byte((void *)VIA_EEPROM_MAGIC_ADDR + 1) == magic1 && eeprom_read_byte((void *)VIA_EEPROM_MAGIC_ADDR + 2) == magic2);
}

// Sets VIA/keyboard level usage of EEPROM to valid/invalid
// Keyboard level code (eg. via_init_kb()) should not call this
void via_eeprom_set_valid(bool valid) {
    char *  p      = QMK_BUILDDATE; // e.g. "2019-11-05-11:29:54"
    uint8_t magic0 = ((p[2] & 0x0F) << 4) | (p[3] & 0x0F);
    uint8_t magic1 = ((p[5] & 0x0F) << 4) | (p[6] & 0x0F);
    uint8_t magic2 = ((p[8] & 0x0F) << 4) | (p[9] & 0x0F);

    eeprom_update_byte((void *)VIA_EEPROM_MAGIC_ADDR + 0, valid ? magic0 : 0xFF);
    eeprom_update_byte((void *)VIA_EEPROM_MAGIC_ADDR + 1, valid ? magic1 : 0xFF);
    eeprom_update_byte((void *)VIA_EEPROM_MAGIC_ADDR + 2, valid ? magic2 : 0xFF);
}

// Override this at the keyboard code level to check
// VIA's EEPROM valid state and reset to defaults as needed.
// Used by keyboards that store their own state in EEPROM,
// for backlight, rotary encoders, etc.
// The override should not set via_eeprom_set_valid(true) as
// the caller also needs to check the valid state.
__attribute__((weak)) void via_init_kb(void) {}

// Called by QMK core to initialize dynamic keymaps etc.
void via_init(void) {
    // Let keyboard level test EEPROM valid state,
    // but not set it valid, it is done here.
    via_init_kb();
    via_set_layout_options_kb(via_get_layout_options());

    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM.
    if (!via_eeprom_is_valid()) {
        eeconfig_init_via();
    }
}

void eeconfig_init_via(void) {
    // set the magic number to false, in case this gets interrupted
    via_eeprom_set_valid(false);
    // This resets the layout options
    via_set_layout_options(VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT);
    // This resets the keymaps in EEPROM to what is in flash.
    dynamic_keymap_reset();
    // This resets the macros in EEPROM to nothing.
    dynamic_keymap_macro_reset();
    // Save the magic number last, in case saving was interrupted
    via_eeprom_set_valid(true);
}

// This is generalized so the layout options EEPROM usage can be
// variable, between 1 and 4 bytes.
uint32_t via_get_layout_options(void) {
    uint32_t value = 0;
    // Start at the most significant byte
    void *source = (void *)(VIA_EEPROM_LAYOUT_OPTIONS_ADDR);
    for (uint8_t i = 0; i < VIA_EEPROM_LAYOUT_OPTIONS_SIZE; i++) {
        value = value << 8;
        value |= eeprom_read_byte(source);
        source++;
    }
    return value;
}

__attribute__((weak)) void via_set_layout_options_kb(uint32_t value) {}

void via_set_layout_options(uint32_t value) {
    via_set_layout_options_kb(value);
    // Start at the least significant byte
    void *target = (void *)(VIA_EEPROM_LAYOUT_OPTIONS_ADDR + VIA_EEPROM_LAYOUT_OPTIONS_SIZE - 1);
    for (uint8_t i = 0; i < VIA_EEPROM_LAYOUT_OPTIONS_SIZE; i++) {
        eeprom_update_byte(target, value & 0xFF);
        value = value >> 8;
        target--;
    }
}

// Called by QMK core to process VIA-specific keycodes.
bool process_record_via(uint16_t keycode, keyrecord_t *record) {
    // Handle macros
    if (record->event.pressed) {
        if (keycode >= MACRO00 && keycode <= MACRO15) {
            uint8_t id = keycode - MACRO00;
            dynamic_keymap_macro_send(id);
            return false;
        }
    }

    // TODO: ideally this would be generalized and refactored into
    // QMK core as advanced keycodes, until then, the simple case
    // can be available here to keyboards using VIA
    switch (keycode) {
        case FN_MO13:
            if (record->event.pressed) {
                layer_on(1);
                update_tri_layer(1, 2, 3);
            } else {
                layer_off(1);
                update_tri_layer(1, 2, 3);
            }
            return false;
            break;
        case FN_MO23:
            if (record->event.pressed) {
                layer_on(2);
                update_tri_layer(1, 2, 3);
            } else {
                layer_off(2);
                update_tri_layer(1, 2, 3);
            }
            return false;
            break;
    }
    return true;
}

// Keyboard level code can override this to handle custom messages from VIA.
// See raw_hid_receive() implementation.
// DO NOT call raw_hid_send() in the override function.
__attribute__((weak)) void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    *command_id         = id_unhandled;
}

// VIA handles received HID messages first, and will route to
// raw_hid_receive_kb() for command IDs that are not handled here.
// This gives the keyboard code level the ability to handle the command
// specifically.
//
// raw_hid_send() is called at the end, with the same buffer, which was
// possibly modified with returned values.
void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t *command_id   = &(data[0]);
    uint8_t *command_data = &(data[1]);
    switch (*command_id) {
        case id_get_protocol_version: {
            command_data[0] = VIA_PROTOCOL_VERSION >> 8;
            command_data[1] = VIA_PROTOCOL_VERSION & 0xFF;
            break;
        }
        case id_get_keyboard_value: {
            switch (command_data[0]) {
                case id_uptime: {
                    uint32_t value  = timer_read32();
                    command_data[1] = (value >> 24) & 0xFF;
                    command_data[2] = (value >> 16) & 0xFF;
                    command_data[3] = (value >> 8) & 0xFF;
                    command_data[4] = value & 0xFF;
                    break;
                }
                case id_layout_options: {
                    uint32_t value  = via_get_layout_options();
                    command_data[1] = (value >> 24) & 0xFF;
                    command_data[2] = (value >> 16) & 0xFF;
                    command_data[3] = (value >> 8) & 0xFF;
                    command_data[4] = value & 0xFF;
                    break;
                }
                case id_switch_matrix_state: {
#if ((MATRIX_COLS / 8 + 1) * MATRIX_ROWS <= 28)
                    uint8_t i = 1;
                    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                        matrix_row_t value = matrix_get_row(row);
#    if (MATRIX_COLS > 24)
                        command_data[i++] = (value >> 24) & 0xFF;
#    endif
#    if (MATRIX_COLS > 16)
                        command_data[i++] = (value >> 16) & 0xFF;
#    endif
#    if (MATRIX_COLS > 8)
                        command_data[i++] = (value >> 8) & 0xFF;
#    endif
                        command_data[i++] = value & 0xFF;
                    }
#endif
                    break;
                }
                default: {
                    raw_hid_receive_kb(data, length);
                    break;
                }
            }
            break;
        }
        case id_set_keyboard_value: {
            switch (command_data[0]) {
                case id_layout_options: {
                    uint32_t value = ((uint32_t)command_data[1] << 24) | ((uint32_t)command_data[2] << 16) | ((uint32_t)command_data[3] << 8) | (uint32_t)command_data[4];
                    via_set_layout_options(value);
                    break;
                }
                default: {
                    raw_hid_receive_kb(data, length);
                    break;
                }
            }
            break;
        }
        case id_dynamic_keymap_get_keycode: {
            uint16_t keycode = dynamic_keymap_get_keycode(command_data[0], command_data[1], command_data[2]);
            command_data[3]  = keycode >> 8;
            command_data[4]  = keycode & 0xFF;
            break;
        }
        case id_dynamic_keymap_set_keycode: {
            dynamic_keymap_set_keycode(command_data[0], command_data[1], command_data[2], (command_data[3] << 8) | command_data[4]);
            break;
        }
        case id_dynamic_keymap_reset: {
            dynamic_keymap_reset();
            break;
        }
        case id_lighting_set_value: {
#if defined(VIA_QMK_BACKLIGHT_ENABLE)
            via_qmk_backlight_set_value(command_data);
#endif
#if defined(VIA_QMK_RGBLIGHT_ENABLE)
            via_qmk_rgblight_set_value(command_data);
#endif
#if defined(VIA_QMK_RGB_MATRIX_ENABLE)
            via_qmk_rgb_matrix_set_value(command_data);
#endif
#if defined(VIA_CUSTOM_LIGHTING_ENABLE)
            raw_hid_receive_kb(data, length);
#endif
#if !defined(VIA_QMK_BACKLIGHT_ENABLE) && !defined(VIA_QMK_RGBLIGHT_ENABLE) && !defined(VIA_CUSTOM_LIGHTING_ENABLE) && !defined(VIA_QMK_RGB_MATRIX_ENABLE)
            // Return the unhandled state
            *command_id = id_unhandled;
#endif
            break;
        }
        case id_lighting_get_value: {
#if defined(VIA_QMK_BACKLIGHT_ENABLE)
            via_qmk_backlight_get_value(command_data);
#endif
#if defined(VIA_QMK_RGBLIGHT_ENABLE)
            via_qmk_rgblight_get_value(command_data);
#endif
#if defined(VIA_QMK_RGB_MATRIX_ENABLE)
            via_qmk_rgb_matrix_get_value(command_data);
#endif
#if defined(VIA_CUSTOM_LIGHTING_ENABLE)
            raw_hid_receive_kb(data, length);
#endif
#if !defined(VIA_QMK_BACKLIGHT_ENABLE) && !defined(VIA_QMK_RGBLIGHT_ENABLE) && !defined(VIA_CUSTOM_LIGHTING_ENABLE) && !defined(VIA_QMK_RGB_MATRIX_ENABLE)
            // Return the unhandled state
            *command_id = id_unhandled;
#endif
            break;
        }
        case id_lighting_save: {
#if defined(VIA_QMK_BACKLIGHT_ENABLE)
            eeconfig_update_backlight_current();
#endif
#if defined(VIA_QMK_RGBLIGHT_ENABLE)
            eeconfig_update_rgblight_current();
#endif
#if defined(VIA_QMK_RGB_MATRIX_ENABLE)
            eeconfig_update_rgb_matrix();
#endif
#if defined(VIA_CUSTOM_LIGHTING_ENABLE)
            raw_hid_receive_kb(data, length);
#endif
#if !defined(VIA_QMK_BACKLIGHT_ENABLE) && !defined(VIA_QMK_RGBLIGHT_ENABLE) && !defined(VIA_CUSTOM_LIGHTING_ENABLE) && !defined(VIA_QMK_RGB_MATRIX_ENABLE)
            // Return the unhandled state
            *command_id = id_unhandled;
#endif
            break;
        }
#ifdef VIA_EEPROM_ALLOW_RESET
        case id_eeprom_reset: {
            via_eeprom_set_valid(false);
            eeconfig_init_via();
            break;
        }
#endif
        case id_dynamic_keymap_macro_get_count: {
            command_data[0] = dynamic_keymap_macro_get_count();
            break;
        }
        case id_dynamic_keymap_macro_get_buffer_size: {
            uint16_t size   = dynamic_keymap_macro_get_buffer_size();
            command_data[0] = size >> 8;
            command_data[1] = size & 0xFF;
            break;
        }
        case id_dynamic_keymap_macro_get_buffer: {
            uint16_t offset = (command_data[0] << 8) | command_data[1];
            uint16_t size   = command_data[2]; // size <= 28
            dynamic_keymap_macro_get_buffer(offset, size, &command_data[3]);
            break;
        }
        case id_dynamic_keymap_macro_set_buffer: {
            uint16_t offset = (command_data[0] << 8) | command_data[1];
            uint16_t size   = command_data[2]; // size <= 28
            dynamic_keymap_macro_set_buffer(offset, size, &command_data[3]);
            break;
        }
        case id_dynamic_keymap_macro_reset: {
            dynamic_keymap_macro_reset();
            break;
        }
        case id_dynamic_keymap_get_layer_count: {
            command_data[0] = dynamic_keymap_get_layer_count();
            break;
        }
        case id_dynamic_keymap_get_buffer: {
            uint16_t offset = (command_data[0] << 8) | command_data[1];
            uint16_t size   = command_data[2]; // size <= 28
            dynamic_keymap_get_buffer(offset, size, &command_data[3]);
            break;
        }
        case id_dynamic_keymap_set_buffer: {
            uint16_t offset = (command_data[0] << 8) | command_data[1];
            uint16_t size   = command_data[2]; // size <= 28
            dynamic_keymap_set_buffer(offset, size, &command_data[3]);
            break;
        }
        default: {
            // The command ID is not known
            // Return the unhandled state
            *command_id = id_unhandled;
            break;
        }
    }

    // Return the same buffer, optionally with values changed
    // (i.e. returning state to the host, or the unhandled state).
    raw_hid_send(data, length);
}

#if defined(VIA_QMK_BACKLIGHT_ENABLE)

#    if BACKLIGHT_LEVELS == 0
#        error BACKLIGHT_LEVELS == 0
#    endif

void via_qmk_backlight_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_qmk_backlight_brightness: {
            // level / BACKLIGHT_LEVELS * 255
            value_data[0] = ((uint16_t)get_backlight_level() * UINT8_MAX) / BACKLIGHT_LEVELS;
            break;
        }
        case id_qmk_backlight_effect: {
#    ifdef BACKLIGHT_BREATHING
            value_data[0] = is_backlight_breathing() ? 1 : 0;
#    else
            value_data[0] = 0;
#    endif
            break;
        }
    }
}

void via_qmk_backlight_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_qmk_backlight_brightness: {
            // level / 255 * BACKLIGHT_LEVELS
            backlight_level_noeeprom(((uint16_t)value_data[0] * BACKLIGHT_LEVELS) / UINT8_MAX);
            break;
        }
        case id_qmk_backlight_effect: {
#    ifdef BACKLIGHT_BREATHING
            if (value_data[0] == 0) {
                backlight_disable_breathing();
            } else {
                backlight_enable_breathing();
            }
#    endif
            break;
        }
    }
}

#endif // #if defined(VIA_QMK_BACKLIGHT_ENABLE)

#if defined(VIA_QMK_RGBLIGHT_ENABLE)
#    ifndef RGBLIGHT_LIMIT_VAL
#        define RGBLIGHT_LIMIT_VAL 255
#    endif

void via_qmk_rgblight_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_qmk_rgblight_brightness: {
            value_data[0] = ((uint16_t)rgblight_get_val() * UINT8_MAX) / RGBLIGHT_LIMIT_VAL;
            break;
        }
        case id_qmk_rgblight_effect: {
            value_data[0] = rgblight_get_mode();
            break;
        }
        case id_qmk_rgblight_effect_speed: {
            value_data[0] = rgblight_get_speed();
            break;
        }
        case id_qmk_rgblight_color: {
            value_data[0] = rgblight_get_hue();
            value_data[1] = rgblight_get_sat();
            break;
        }
    }
}

void via_qmk_rgblight_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_qmk_rgblight_brightness: {
            rgblight_sethsv_noeeprom(rgblight_get_hue(), rgblight_get_sat(), ((uint16_t)value_data[0] * RGBLIGHT_LIMIT_VAL) / UINT8_MAX);
            break;
        }
        case id_qmk_rgblight_effect: {
            rgblight_mode_noeeprom(value_data[0]);
            if (value_data[0] == 0) {
                rgblight_disable_noeeprom();
            } else {
                rgblight_enable_noeeprom();
            }
            break;
        }
        case id_qmk_rgblight_effect_speed: {
            rgblight_set_speed_noeeprom(value_data[0]);
            break;
        }
        case id_qmk_rgblight_color: {
            rgblight_sethsv_noeeprom(value_data[0], value_data[1], rgblight_get_val());
            break;
        }
    }
}

#endif // #if defined(VIA_QMK_RGBLIGHT_ENABLE)

#if defined(VIA_QMK_RGB_MATRIX_ENABLE)

#    if !defined(RGB_MATRIX_MAXIMUM_BRIGHTNESS) || RGB_MATRIX_MAXIMUM_BRIGHTNESS > UINT8_MAX
#        undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#        define RGB_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX
#    endif

// VIA supports only 4 discrete values for effect speed; map these to some
// useful speed values for RGB Matrix.
enum speed_values {
    RGBLIGHT_SPEED_0 = UINT8_MAX / 16, // not 0 to avoid really slow effects
    RGBLIGHT_SPEED_1 = UINT8_MAX / 4,
    RGBLIGHT_SPEED_2 = UINT8_MAX / 2,     // matches the default value
    RGBLIGHT_SPEED_3 = UINT8_MAX / 4 * 3, // UINT8_MAX is really fast
};

static uint8_t speed_from_rgblight(uint8_t rgblight_speed) {
    switch (rgblight_speed) {
        case 0:
            return RGBLIGHT_SPEED_0;
        case 1:
            return RGBLIGHT_SPEED_1;
        case 2:
        default:
            return RGBLIGHT_SPEED_2;
        case 3:
            return RGBLIGHT_SPEED_3;
    }
}

static uint8_t speed_to_rgblight(uint8_t rgb_matrix_speed) {
    if (rgb_matrix_speed < ((RGBLIGHT_SPEED_0 + RGBLIGHT_SPEED_1) / 2)) {
        return 0;
    } else if (rgb_matrix_speed < ((RGBLIGHT_SPEED_1 + RGBLIGHT_SPEED_2) / 2)) {
        return 1;
    } else if (rgb_matrix_speed < ((RGBLIGHT_SPEED_2 + RGBLIGHT_SPEED_3) / 2)) {
        return 2;
    } else {
        return 3;
    }
}

void via_qmk_rgb_matrix_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_qmk_rgblight_brightness:
            value_data[0] = ((uint16_t)rgb_matrix_get_val() * UINT8_MAX) / RGB_MATRIX_MAXIMUM_BRIGHTNESS;
            break;
        case id_qmk_rgblight_effect:
            value_data[0] = rgb_matrix_get_mode();
            break;
        case id_qmk_rgblight_effect_speed:
            value_data[0] = speed_to_rgblight(rgb_matrix_get_speed());
            break;
        case id_qmk_rgblight_color:
            value_data[0] = rgb_matrix_get_hue();
            value_data[1] = rgb_matrix_get_sat();
            break;
    }
}

void via_qmk_rgb_matrix_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_qmk_rgblight_brightness:
            rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), scale8(value_data[0], RGB_MATRIX_MAXIMUM_BRIGHTNESS));
            break;
        case id_qmk_rgblight_effect:
            rgb_matrix_mode_noeeprom(value_data[0]);
            if (value_data[0] == 0) {
                rgb_matrix_disable_noeeprom();
            } else {
                rgb_matrix_enable_noeeprom();
            }
            break;
        case id_qmk_rgblight_effect_speed:
            rgb_matrix_set_speed_noeeprom(speed_from_rgblight(value_data[0]));
            break;
        case id_qmk_rgblight_color:
            rgb_matrix_sethsv_noeeprom(value_data[0], value_data[1], rgb_matrix_get_val());
            break;
    }
}

#endif // #if defined(VIA_QMK_RGB_MATRIX_ENABLE)
