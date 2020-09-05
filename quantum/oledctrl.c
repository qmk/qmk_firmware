/* Copyright 2020 Albert Diserholt (Drauthius)
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

#ifdef RAW_ENABLE
#   include "raw_hid.h"
#endif

#ifndef OLED_DRIVER_ENABLE
#    error "OLED_DRIVER_ENABLE is not enabled"
#endif

#include <stdio.h>
#include <string.h>

#include "quantum.h"

#include "oledctrl.h"

#ifndef MAX
#    define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif

#ifndef MIN
#    define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define SCREEN_BUFFER_LEN \
    MAX(((OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH) * (OLED_DISPLAY_HEIGHT / OLED_FONT_HEIGHT))\
       ,((OLED_DISPLAY_HEIGHT / OLED_FONT_WIDTH) * (OLED_DISPLAY_WIDTH / OLED_FONT_HEIGHT)))

// The current text shown on the screen.
static char front_buffer[SCREEN_BUFFER_LEN + 1] = {0};
// The buffer containing the text to show when presenting.
static char back_buffer[SCREEN_BUFFER_LEN + 1] = {0};
// Whether the front buffer contains variables.
static bool buffer_has_variables = false;
// Buffer for substituting variables with text.
static char var_buffer[MAX(OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH, OLED_DISPLAY_HEIGHT / OLED_FONT_WIDTH)];

// Checks whether the OS has set any content.
bool oledctrl_has_content(void) {
    return front_buffer[0] != 0;
}

// Override in keyboard-level code to translate the current layer to a name.
__attribute__((weak)) const char *read_layer_state(void) {
    static char layer_state_str[24];
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: %ld", layer_state);
    return layer_state_str;
}

/**
 * Write the front buffer to the OLED screen.
 * This method supports some simple substitutions of variables inside the
 * lines. For example, "%l" will be replaced with the result of the
 * read_layer_state() function, which if undefined will be "Layer: " followed
 * by a number.
 * Note that if the line becomes too long for it to fit on the screen, text
 * will be cut off at the end.
 *
 * Current handled variables:
 *   %l  -  Layer information
 */
bool oledctrl_draw(void) {
    if (!oledctrl_has_content()) {
        return false;
    }

    if (!buffer_has_variables) {
        oled_write(front_buffer, false);
        return true;
    }

    // Handle variables.
    // A bit convoluted, but it works.
    for (int row = 0; row < oled_max_lines(); ++row) {
        for (int col = 0, i = row * oled_max_chars(); col < oled_max_chars(); ++col, ++i) {
            // Don't write the final null character, or screen might scroll up.
            if (front_buffer[i] == 0) {
                break;
            } else if (front_buffer[i] == '%' && i + 1 < sizeof(front_buffer)) {
                int len = 0;
                switch (front_buffer[i+1]) {
                    case 'l': {
                        len = snprintf(var_buffer, sizeof(var_buffer), read_layer_state());
                        break;
                    }
                    /* Add other substitutions here. */
                }

                if (len > 0) {
                    // A substitution occurred. The content of the var_buffer will
                    // either be printed in full, or until the end of the line.
                    len = MIN(MIN(len, oled_max_chars() - col), sizeof(var_buffer) - 1);
                    var_buffer[len] = 0; // Chop if off if necessary.
                    oled_write(var_buffer, false);
                    col += len - 1; // Will be incremented once more by the loop.
                    ++i; // Skip the variable character.
                    continue;
                }
            }

            // Write the character normally to the screen.
            oled_write_char(front_buffer[i], false);
        }
    }

    return true;
}

// Send an event over HID raw.
void oledctrl_send_event(uint8_t event, uint8_t *args, uint8_t args_len) {
    uint8_t event_buffer[32] = { OLEDCTRL_MSG_EVENT, event };
    memcpy(&event_buffer[2], args, MIN(args_len, sizeof(event_buffer) - 3));

    raw_hid_send(event_buffer, sizeof(event_buffer));
}

// Handle a command.
void oledctrl_handle_cmd(uint8_t *data, uint8_t length) {
    if (!data || length < 1) {
        // No data.
        return;
    }

    // First byte becomes the result code.
    enum oledctrl_result_id *result = &data[0];

    if (length < 4 || data[0] != OLEDCTRL_MSG_COMMAND) {
        // Incomplete header or invalid message.
        *result = OLEDCTRL_RES_FAILURE;
        return;
    }

    // The next two bytes are the command and screen, followed by any data.
    uint8_t command = data[1];
    enum oledctrl_screen_id screen = data[2];
    uint8_t *command_data = &data[3];
    uint8_t command_length = length - 4;

    if (screen == OLEDCTRL_SCR_SLAVE && is_keyboard_master()) {
#ifdef OLEDCTRL_SPLIT
        // This is a command for the slave. Send it over.
        oledctrl_send_msg(data, length);
        *result = OLEDCTRL_RES_SUCCESS; // No way to know whether it was successfully received.
#endif // OLEDCTRL_SPLIT
    } else if (screen == OLEDCTRL_SCR_MASTER || (screen == OLEDCTRL_SCR_SLAVE && !is_keyboard_master())) {
        switch (command) {
            case OLEDCTRL_CMD_SET_UP: // Return the size of the OLED screen.
                if (command_length < 2) {
                    // No room to fill in the return values.
                    *result = OLEDCTRL_RES_FAILURE;
                    return;
                }
                command_data[0] = oled_max_chars();
                command_data[1] = oled_max_lines();
                // Fall through
            case OLEDCTRL_CMD_CLEAR: // Clear the buffers and screens
                memset(front_buffer, 0, sizeof(front_buffer));
                memset(back_buffer, ' ', sizeof(back_buffer));
                oled_clear();
                oled_interpret_newline(command == OLEDCTRL_CMD_CLEAR); // Let userspace use all the characters in the font.
                *result = OLEDCTRL_RES_SUCCESS;
                break;
            case OLEDCTRL_CMD_SET_LINE: { // Set a line of text.
                if (command_length < 2) {
                    // Missing arguments.
                    *result = OLEDCTRL_RES_FAILURE;
                    return;
                }
                uint8_t line = command_data[0];
                char *text = (char*)&command_data[1];
                if (line >= oled_max_lines()) {
                    // Line out of bounds
                    *result = OLEDCTRL_RES_FAILURE;
                    return;
                }

                uint8_t len = MIN(strnlen(text, command_length), oled_max_chars());
                memcpy(&back_buffer[line * oled_max_chars()], text, len);
                if (len < oled_max_chars()) {
                    // Erase everything else until the end of the line.
                    memset(&back_buffer[line * oled_max_chars() + len], ' ', oled_max_chars() - len);
                }
                *result = OLEDCTRL_RES_SUCCESS;
                break;
            }
            case OLEDCTRL_CMD_SET_CHARS:
                if (command_length < 3) {
                    // Missing arguments.
                    *result = OLEDCTRL_RES_FAILURE;
                    return;
                }
                uint8_t offset = command_data[0];
                uint8_t len = command_data[1];
                char *text = (char*)&command_data[2];
                if (offset >= sizeof(back_buffer)) {
                    // Offset out of bounds
                    *result = OLEDCTRL_RES_FAILURE;
                    return;
                } else if (len > command_length - 3) {
                    // Length too big
                    *result = OLEDCTRL_RES_FAILURE;
                    return;
                }

                memcpy(&back_buffer[offset], text, MIN(len, sizeof(back_buffer) - offset - 1));
                *result = OLEDCTRL_RES_SUCCESS;
                break;
            case OLEDCTRL_CMD_PRESENT: // Copy the content of the back buffer to the front buffer.
                memcpy(front_buffer, back_buffer, SCREEN_BUFFER_LEN);
                front_buffer[sizeof(front_buffer) - 1] = 0;
                *result = OLEDCTRL_RES_SUCCESS;
                buffer_has_variables = strchr(front_buffer, '%');
                break;
            default:
                *result = OLEDCTRL_RES_FAILURE;
                break;
        }
    } else {
        // Unknown screen.
        *result = OLEDCTRL_RES_FAILURE;
    }
}

// Define OLEDCTRL_CUSTOM_HID_RECEIVE to handle HID messages in keyboard-level code.
#ifndef OLEDCTRL_CUSTOM_HID_RECEIVE

#   ifdef VIA_ENABLE
#       define raw_hid_receive raw_hid_receive_kb
#   endif

// Handle raw HID messages.
void raw_hid_receive(uint8_t *data, uint8_t length) {
    oledctrl_handle_cmd(data, length);

    // VIA code will take care of responding if enabled.
#   ifndef VIA_ENABLE
    if (!is_keyboard_master()) {
        return; // Slave cannot answer to HID messages
    }

    // Return the same buffer, presumably with values changed.
    raw_hid_send(data, length);
#   endif // !VIA_ENABLE
}

#endif // !OLEDCTRL_CUSTOM_HID_RECEIVE

#ifdef OLEDCTRL_SPLIT

// Message from the master to the slave.
static uint8_t oled_ctrl_msg[OLEDCTRL_MSG_MAX_LEN];
// Whether a message is ready to be sent.
static bool oled_ctrl_pending;

/* for split keyboard master side */
void oledctrl_send_msg(const uint8_t *msg, uint8_t len) {
    memcpy(oled_ctrl_msg, msg, MIN(sizeof(oled_ctrl_msg), len));
    oled_ctrl_pending = true;
}

bool oledctrl_is_msg_pending(void) { return oled_ctrl_pending; }

void oledctrl_clear_msg_pending(void) { oled_ctrl_pending = false; }

void oledctrl_get_syncinfo(oledctrl_syncinfo_t *syncinfo) {
    memcpy(syncinfo->msg, oled_ctrl_msg, OLEDCTRL_MSG_MAX_LEN);
}

/* for split keyboard slave side */
void oledctrl_update_sync(oledctrl_syncinfo_t *syncinfo) {
    oledctrl_receive_msg(syncinfo->msg, OLEDCTRL_MSG_MAX_LEN);
}

// Process any message from the master.
void oledctrl_receive_msg(uint8_t *msg, uint8_t len) {
    oledctrl_handle_cmd(msg, len);
}

#endif // OLEDCTRL_SPLIT
